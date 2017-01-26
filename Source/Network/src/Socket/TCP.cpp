/**
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/Network/Socket/TCP.hpp"
#include "TitaniumWindows/Utility.hpp"

#include <ppl.h>

namespace TitaniumWindows
{
	namespace Network
	{
		namespace Socket
		{

			TCP::TCP(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Network::Socket::TCP(js_context)
			{
				TITANIUM_LOG_DEBUG("TitaniumWindows::Network::Socket::TCP::ctor");
			}

			TCP::~TCP()
			{
				TITANIUM_LOG_DEBUG("TitaniumWindows::Network::Socket::TCP::dtor");
			}

			void TCP::JSExportInitialize()
			{
				JSExport<TCP>::SetClassVersion(1);
				JSExport<TCP>::SetParent(JSExport<Titanium::Network::Socket::TCP>::Class());
			}

			void TCP::construct(StreamSocket^ socket) {
				socket__ = socket;
				state__ = Titanium::Network::Socket::State::Connected;
				modes__.emplace(Titanium::Filesystem::MODE::READ);
				modes__.emplace(Titanium::Filesystem::MODE::WRITE);
			}

			void TCP::connect() TITANIUM_NOEXCEPT
			{
				if (!socket__) {
					socket__ = ref new StreamSocket();
					hostname__ = ref new HostName(TitaniumWindows::Utility::ConvertString(host__));
					const auto port = TitaniumWindows::Utility::ConvertString(std::to_string(port__));

					concurrency::create_task(socket__->ConnectAsync(hostname__, port)).then(
						[this](concurrency::task<void> task) {
							try {
								task.get();

								state__ = Titanium::Network::Socket::State::Connected;

								// set stream to read/write
								modes__.emplace(Titanium::Filesystem::MODE::READ);
								modes__.emplace(Titanium::Filesystem::MODE::WRITE);

								// call connected callback
								if (connected__.IsObject()) {
									auto connected_obj = static_cast<JSObject>(connected__);
									if (connected_obj.IsFunction()) {
										auto args = get_context().CreateObject();
										args.SetProperty("socket", get_object());
										try {
											connected_obj({args}, get_object());
										} catch (std::exception e) {
											HAL::detail::ThrowRuntimeError("TCP::connected", std::string(e.what()));
										}
									}
								}
							} catch(Platform::Exception^ e) {
								error("could not connect");
								TITANIUM_LOG_ERROR("TCP::connect: Titanium::Network::Socket::TCP: Could not connect");
							}
						}
					);
				} else if (state__ == Titanium::Network::Socket::State::Connected ||
						   state__ == Titanium::Network::Socket::State::Listening) {
					error("socket is already listening or connected");
					TITANIUM_LOG_ERROR("TCP::accept: Titanium::Network::Socket::TCP: Socket is already connected or listening");
				}
			}

			void TCP::listen() TITANIUM_NOEXCEPT
			{
				if (state__  == Titanium::Network::Socket::State::Listening ||
					state__ == Titanium::Network::Socket::State::Connected) {
					state__ = Titanium::Network::Socket::State::Error;
					error("socket is already listening or connected");
					TITANIUM_LOG_ERROR("TCP::listen: Titanium::Network::Socket::TCP: Socket is already connected or listening");

				} else {
					using Windows::Networking::Sockets::StreamSocketListenerConnectionReceivedEventArgs;
					using Windows::Foundation::TypedEventHandler;

					listener__ = ref new StreamSocketListener();
					listener__->ConnectionReceived += ref new TypedEventHandler<StreamSocketListener^, StreamSocketListenerConnectionReceivedEventArgs^>(
						[this](StreamSocketListener^ listener, StreamSocketListenerConnectionReceivedEventArgs^ object) {
							if (listener_queue__.size() < listenQueueSize__) {
								listener_queue__.push_back(object->Socket);

								// only accept connections once accept() has been called
								if (has_accept__) {
									accepted(object->Socket);
								}
							}
						}
					);

					// bind listener to port
					const auto port = TitaniumWindows::Utility::ConvertString(std::to_string(port__));
					concurrency::create_task(listener__->BindServiceNameAsync(port)).then(
						[this](concurrency::task<void> task) {
							try {
								task.get();
								state__ = Titanium::Network::Socket::State::Listening;
							} catch (Platform::Exception^ exception) {
								error("could not bind to port");
								TITANIUM_LOG_ERROR("TCP::listen: Titanium::Network::Socket::TCP: Could not bind to port " + std::to_string(port__));
							}
						}
					);
				}
			}

			void TCP::accept(const Titanium::Network::Socket::AcceptDict& options) TITANIUM_NOEXCEPT
			{
				if (state__ != Titanium::Network::Socket::State::Listening) {
					error("socket is not in listening state");
					TITANIUM_LOG_ERROR("TCP::accept: Titanium::Network::Socket::TCP: Socket is not in listening state");
					return;
				}
				if (!has_accept__) {
					// accept all listener queue connections
					for (auto socket : listener_queue__) {
						accepted(socket);
					}
					has_accept__ = true;
				}
			}

			void TCP::accepted(StreamSocket^ socket) {

				if (accepted__.IsObject()) {

					// create Titanium.Network.Socket.TCP object
					auto tcp_obj = get_context().CreateObject(JSExport<TCP>::Class());
					const auto tcp_js = tcp_obj.CallAsConstructor();
					const auto tcp = tcp_obj.GetPrivate<TCP>();

					// construct using accepted socket
					tcp->construct(socket);

					// call accepted callback
					auto accepted_obj = static_cast<JSObject>(accepted__);
					if (accepted_obj.IsFunction()) {
						auto args = get_context().CreateObject();
						args.SetProperty("inbound", tcp_obj);
						args.SetProperty("socket", get_object());
						accepted_obj({args}, get_object());
					}
				}
			}

			void TCP::close() TITANIUM_NOEXCEPT
			{
				if (state__ == Titanium::Network::Socket::State::Connected ||
					state__ == Titanium::Network::Socket::State::Listening) {
					delete socket__;
				} else {
					error("socket is not in connected or listening state");
					TITANIUM_LOG_ERROR("TCP::close: Titanium::Network::Socket::TCP: Socket is not in connected or listening state");
				}
			}

			std::int32_t TCP::read(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length)
			{
				const auto reader = ref new DataReader(socket__->InputStream);
				reader->InputStreamOptions = Windows::Storage::Streams::InputStreamOptions::Partial;
				std::vector<uint8_t> data;

				concurrency::event evt;
				concurrency::create_task(reader->LoadAsync(offset+length)).then(
					[this, &evt, offset, length, &data, reader](unsigned int size) {
						if (offset + length < size) {
							concurrency::cancel_current_task();
							error("read input greater than buffer");
							TITANIUM_LOG_ERROR("TCP::read: Titanium::Network::Socket::TCP: Read input greater than buffer");
							return;
						}
						if (offset > 0) {
							reader->ReadBuffer(offset);
						}
						data.resize(size);
						reader->ReadBytes(::Platform::ArrayReference<std::uint8_t>(data.data(), size));
						evt.set();
					}, concurrency::task_continuation_context::use_arbitrary()
				);
				evt.wait();
				reader->DetachStream();

				buffer->construct(data);
				return totalBytesProcessed__ = data.size();
			}

			void TCP::readAsync(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const Titanium::ErrorResponse&, const std::int32_t&)>& callback)
			{
				concurrency::create_task([=]() {
					Titanium::ErrorResponse error;
					const auto count = read(buffer, offset, length);
					TitaniumWindows::Utility::RunOnUIThread([=] {
						callback(error, count);
					});
				}, concurrency::task_continuation_context::use_arbitrary());
			}

			std::uint32_t TCP::write(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length)
			{
				const auto writer = ref new DataWriter(socket__->OutputStream);

				if (offset + length > buffer->get_length()) {
					return 0;
				}
				writer->WriteBytes(::Platform::ArrayReference<std::uint8_t>(&buffer->get_data()[offset], length));

				std::uint32_t count = 0;
				concurrency::event evt;
				concurrency::create_task(writer->StoreAsync()).then(
					[this, &evt, &count](concurrency::task<unsigned int> task) {
						try {
							count = task.get();
						} catch (Platform::Exception^ e) {
							error("could not send data");
							TITANIUM_LOG_ERROR("TCP::write: Titanium::Network::Socket::TCP: Could not send data");
						}
						evt.set();
					}, concurrency::task_continuation_context::use_arbitrary()
				);
				evt.wait();
				writer->DetachStream();

				return count;
			}

			void TCP::writeAsync(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const Titanium::ErrorResponse&, const std::int32_t&)>& callback)
			{
				concurrency::create_task([=]() {
					Titanium::ErrorResponse error;
					const auto count = write(buffer, offset, length);
					TitaniumWindows::Utility::RunOnUIThread([=] {
						callback(error, count);
					});
				}, concurrency::task_continuation_context::use_arbitrary());
			}

			void TCP::error(const std::string& message)
			{
				if (error__.IsObject()) {
					auto error_obj = static_cast<JSObject>(error__);
					if (error_obj.IsFunction()) {
						const auto ctx = get_context();
						auto args = get_context().CreateObject();
						args.SetProperty("code", ctx.CreateNumber(-1));
						args.SetProperty("error", ctx.CreateString(message));
						args.SetProperty("socket", get_object());
						args.SetProperty("success", ctx.CreateBoolean(false));
						error_obj({args}, get_object());
					}
				}
			}
		}
	}
}
