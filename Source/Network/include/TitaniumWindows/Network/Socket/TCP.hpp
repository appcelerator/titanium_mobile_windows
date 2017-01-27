/**
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_SOCKET_TCP_HPP_
#define _TITANIUMWINDOWS_SOCKET_TCP_HPP_

#include "TitaniumWindows_Network_EXPORT.h"
#include "Titanium/Network/Socket/TCP.hpp"
#include "Titanium/Buffer.hpp"

using Windows::Networking::Sockets::StreamSocket;
using Windows::Networking::Sockets::StreamSocketListener;
using Windows::Networking::HostName;
using Windows::Storage::Streams::DataReader;
using Windows::Storage::Streams::DataWriter;

namespace TitaniumWindows
{
	namespace Network
	{
		namespace Socket
		{
			using namespace HAL;

			/*!
			  @class TCP
			  @ingroup Titanium.Network.Socket.TCP
			  @discussion This is the Titanium.Network.Socket.TCP implementation for Windows.
			*/
			class TITANIUMWINDOWS_NETWORK_EXPORT TCP final : public Titanium::Network::Socket::TCP, public JSExport<TCP>
			{
			public:

				TCP(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~TCP();
				TCP(const TCP&) = default;
				TCP& operator=(const TCP&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				TCP(TCP&&) = default;
				TCP& operator=(TCP&&) = default;
#endif

				static void JSExportInitialize();

				void construct(StreamSocket^ socket);

				virtual void close() TITANIUM_NOEXCEPT override;
				virtual void connect() TITANIUM_NOEXCEPT override;
				virtual void listen() TITANIUM_NOEXCEPT override;
				virtual void accept(const Titanium::Network::Socket::AcceptDict& options) TITANIUM_NOEXCEPT override;

				virtual std::int32_t read(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length) override;
				virtual void readAsync(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const Titanium::ErrorResponse&, const std::int32_t&)>&) override;

				virtual std::uint32_t write(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length) override;
				virtual void writeAsync(const std::shared_ptr<Titanium::Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const Titanium::ErrorResponse&, const std::int32_t&)>& callback) override;

				void accepted(StreamSocket^ socket);

				void error(const std::string& message);
			private:
#pragma warning(push)
#pragma warning(disable : 4251)
				StreamSocket^ socket__;
				StreamSocketListener^ listener__;
				std::vector<StreamSocket^> listener_queue__;
				bool has_accept__{ false };
				HostName^ hostname__;
#pragma warning(pop)
			};
		} // namespace Socket
	} // namespace Network
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_SOCKET_TCP_HPP_