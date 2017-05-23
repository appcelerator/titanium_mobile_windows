/**
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_SOCKET_UDP_HPP_
#define _TITANIUMWINDOWS_SOCKET_UDP_HPP_

#include "TitaniumWindows_Network_EXPORT.h"
#include "Titanium/Network/Socket/UDP.hpp"
#include "Titanium/Buffer.hpp"

namespace TitaniumWindows
{
	namespace Network
	{
		namespace Socket
		{
			using namespace HAL;

			/*!
			  @class UDP
			  @ingroup Titanium.Network.Socket.UDP
			  @discussion This is the Titanium.Network.Socket.UDP implementation for Windows.
			*/
			class TITANIUMWINDOWS_NETWORK_EXPORT UDP final : public Titanium::Network::Socket::UDP, public JSExport<UDP>
			{
			public:

				UDP(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~UDP();
				UDP(const UDP&) = default;
				UDP& operator=(const UDP&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				UDP(UDP&&) = default;
				UDP& operator=(UDP&&) = default;
#endif

				static void JSExportInitialize();

				virtual void start(const std::uint32_t& port, const std::string& host) TITANIUM_NOEXCEPT override;
				virtual void stop() TITANIUM_NOEXCEPT override;
				virtual void sendString(const std::uint32_t& port, const std::string& host, const std::string& data) TITANIUM_NOEXCEPT override;
				virtual void sendBytes(const std::uint32_t& port, const std::string& host, std::vector<std::uint8_t> data) TITANIUM_NOEXCEPT override;

				virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

				void error(const std::string& message) TITANIUM_NOEXCEPT;
			private:
#pragma warning(push)
#pragma warning(disable : 4251)
				Windows::Networking::Sockets::DatagramSocket^ socket__;
#pragma warning(pop)
			};
		} // namespace Socket
	} // namespace Network
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_SOCKET_UDP_HPP_