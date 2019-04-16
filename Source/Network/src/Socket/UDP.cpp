/**
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/Network/Socket/UDP.hpp"
#include "Titanium/Blob.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

#include <ppltasks.h>
#include <concrt.h>

using namespace Windows::Foundation;
using namespace Windows::Security::Cryptography;
using namespace Windows::Storage::Streams;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;

namespace TitaniumWindows
{
	namespace Network
	{
		namespace Socket
		{

			UDP::UDP(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Network::Socket::UDP(js_context)
			{

			}

			UDP::~UDP()
			{
				socket__ = nullptr;
			}

			void UDP::JSExportInitialize()
			{
				JSExport<UDP>::SetClassVersion(1);
				JSExport<UDP>::SetParent(JSExport<Titanium::Network::Socket::UDP>::Class());
			}

			void UDP::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
			{
				Titanium::Network::Socket::UDP::postCallAsConstructor(js_context, arguments);

				socket__ = ref new DatagramSocket();
				socket__->MessageReceived += ref new TypedEventHandler<DatagramSocket^, DatagramSocketMessageReceivedEventArgs^>
					([this](Platform::Object^ sender, DatagramSocketMessageReceivedEventArgs^ e) {
					if (data__.IsObject()) {
						TitaniumWindows::Utility::RunOnUIThread([this, e]() {
							try {
								auto callback = static_cast<JSObject>(data__);
								if (callback.IsFunction()) {
									const auto ctx = get_context();
									auto args = get_context().CreateObject();

									const auto reader = e->GetDataReader();
									std::vector<std::uint8_t> data(reader->UnconsumedBufferLength);
									if (!data.empty()) {
										auto data_ref = Platform::ArrayReference<std::uint8_t>(&data[0], static_cast<std::uint32_t>(data.size()));
										reader->ReadBytes(data_ref);

										const auto buffer = CryptographicBuffer::CreateFromByteArray(data_ref);
										const auto decoded = CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, buffer);

										auto blob = get_context().CreateObject(JSExport<Titanium::Blob>::Class()).CallAsConstructor();
										auto blob_ptr = blob.GetPrivate<Titanium::Blob>();
										blob_ptr->construct(data);

										args.SetProperty("stringData", ctx.CreateString(TitaniumWindows::Utility::ConvertUTF8String(decoded)));
										args.SetProperty("bytesData", blob);
									} else {
										args.SetProperty("stringData", ctx.CreateString(""));
										args.SetProperty("bytesData", ctx.CreateNull());
									}


									args.SetProperty("address", ctx.CreateString(TitaniumWindows::Utility::ConvertUTF8String(e->RemoteAddress->DisplayName)));
									args.SetProperty("port", ctx.CreateString(TitaniumWindows::Utility::ConvertUTF8String(e->RemotePort)));
									callback({ args }, get_object());
								}
							} catch (Platform::COMException^ e) {
								error(TitaniumWindows::Utility::ConvertUTF8String(e->Message));
							} catch (...) {
								error("Ti.Network.UDP.data: Unknown error");
							}
						});
					}
				});
			}

			void UDP::start(const std::uint32_t& port, const std::string& host) TITANIUM_NOEXCEPT
			{
				if (socket__) {
					port__ = port;
					host__ = host;

					Platform::String^ hostname = TitaniumWindows::Utility::ConvertString(host);
					const auto portname = TitaniumWindows::Utility::ConvertString(std::to_string(port));
					if (host.empty()) {
						const auto hostnames = Connectivity::NetworkInformation::GetHostNames();
						if (hostnames->Size > 0) {
							hostname = hostnames->GetAt(0)->CanonicalName;
						}
					}
					JSValueProtect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
					concurrency::create_task(socket__->BindEndpointAsync(ref new HostName(hostname), portname)).then([this, hostname, port](concurrency::task<void> task) {
						try {
							task.get();

							if (started__.IsObject()) {
								TitaniumWindows::Utility::RunOnUIThread([this, hostname, port]() {
									auto callback = static_cast<JSObject>(started__);
									if (callback.IsFunction()) {
										const auto ctx = get_context();
										auto args = ctx.CreateObject();
										args.SetProperty("address", ctx.CreateString(TitaniumWindows::Utility::ConvertUTF8String(hostname)));
										args.SetProperty("port", ctx.CreateNumber(port));
										callback({ args }, get_object());
									}
									JSValueUnprotect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
								});
							}
						} catch (Platform::COMException^ e) {
							error(TitaniumWindows::Utility::ConvertUTF8String(e->Message));
							JSValueUnprotect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
						} catch (...) {
							error("Ti.Network.UDP.start: Unknown error");
							JSValueUnprotect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
						}
					});
				}
			}

			void UDP::stop() TITANIUM_NOEXCEPT
			{
#if defined(IS_WINDOWS_10)
				if (socket__) {
					concurrency::create_task(socket__->CancelIOAsync()).then([this](concurrency::task<void> task) {
						try {
							task.get();
						} catch (...) {
							// do nothing
						}
						socket__ = nullptr;
					});
				}
#else
				socket__ = nullptr;
#endif
			}

			void UDP::sendString(const std::uint32_t& port, const std::string& host, const std::string& str) TITANIUM_NOEXCEPT
			{
				const auto source = TitaniumWindows::Utility::ConvertUTF8String(str);
				const auto buffer = CryptographicBuffer::ConvertStringToBinary(source, BinaryStringEncoding::Utf8);
				const auto data = TitaniumWindows::Utility::GetContentFromBuffer(buffer);

				sendBytes(port, host, data);
			}

			void UDP::sendBytes(const std::uint32_t& port, const std::string& host, std::vector<std::uint8_t> data) TITANIUM_NOEXCEPT
			{
				if (socket__) {

					const auto hostname = ref new HostName(TitaniumWindows::Utility::ConvertString(host));
					const auto portname = TitaniumWindows::Utility::ConvertString(std::to_string(port));

					JSValueProtect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
					concurrency::create_task(socket__->ConnectAsync(hostname, portname)).then([this, data](concurrency::task<void> task) {
						try {
							task.get();

							const auto writer = ref new DataWriter(socket__->OutputStream);
							std::vector<std::uint8_t> read_data = const_cast<std::vector<std::uint8_t>&>(data);
							writer->WriteBytes(::Platform::ArrayReference<std::uint8_t>(&read_data[0], static_cast<std::uint32_t>(read_data.size())));
							concurrency::create_task(writer->StoreAsync()).then([this, writer](concurrency::task<unsigned int> task) {
								try {
									task.get();
								} catch (Platform::COMException^ e) {
									error(TitaniumWindows::Utility::ConvertUTF8String(e->Message));
								} catch (...) {
									error("Ti.Network.UDP.sendByte: Unknown error");
								}
								return writer->FlushAsync();
							}).then([this](concurrency::task<bool> task) {
								try {
									task.get();
								} catch (Platform::COMException^ e) {
									error(TitaniumWindows::Utility::ConvertUTF8String(e->Message));
								} catch (...) {
									error("Ti.Network.UDP.sendByte: Unknown error");
								}
								JSValueUnprotect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
							});
						} catch (Platform::COMException^ e) {
							error(TitaniumWindows::Utility::ConvertUTF8String(e->Message));
							JSValueUnprotect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
						} catch (...) {
							error("Ti.Network.UDP.sendByte: Unknown error");
							JSValueUnprotect(static_cast<JSContextRef>(get_context()), static_cast<JSValueRef>(get_object()));
						}
					});
				}
			}

			void UDP::error(const std::string& message) TITANIUM_NOEXCEPT
			{
				try {
					if (error__.IsObject()) {
						TitaniumWindows::Utility::RunOnUIThread([this, message]() {
							auto callback = static_cast<JSObject>(error__);
							if (callback.IsFunction()) {
								const auto ctx = get_context();
								auto args = get_context().CreateObject();
								args.SetProperty("code", ctx.CreateNumber(-1));
								args.SetProperty("error", ctx.CreateString(message));
								args.SetProperty("success", ctx.CreateBoolean(false));
								callback({ args }, get_object());
							}
						});
					}
				} catch (...) {
					// do nothing...
				}
			}

		}

	}
}
