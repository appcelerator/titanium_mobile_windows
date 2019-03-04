/**
 * TitaniumKit Titanium.Network.Socket
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_SOCKET_HPP_
#define _TITANIUM_SOCKET_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Network
	{

		using namespace HAL;

		namespace Socket {
			enum class State
			{
				Initialized,
				Connected,
				Listening,
				Closed,
				Error
			};
		} // namespace Socket

		/*!
		  @class
		  @discussion This is the Titanium Socket Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Network.Socket
		*/
		class TITANIUMKIT_EXPORT SocketModule : public Module, public JSExport<SocketModule>
		{

		public:

			SocketModule(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~SocketModule() = default;
			SocketModule(const SocketModule&) = default;
			SocketModule& operator=(const SocketModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			SocketModule(SocketModule&&)                 = default;
			SocketModule& operator=(SocketModule&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(INITIALIZED);
			TITANIUM_PROPERTY_READONLY_DEF(CONNECTED);
			TITANIUM_PROPERTY_READONLY_DEF(LISTENING);
			TITANIUM_PROPERTY_READONLY_DEF(CLOSED);
			TITANIUM_PROPERTY_READONLY_DEF(ERROR);
			TITANIUM_PROPERTY_READONLY_DEF(TCP);
			TITANIUM_PROPERTY_READONLY_DEF(UDP);

			TITANIUM_FUNCTION_DEF(createTCP);
			TITANIUM_FUNCTION_DEF(createUDP);

			SocketModule& TCPClass(const JSClass&) TITANIUM_NOEXCEPT;
			SocketModule& UDPClass(const JSClass&) TITANIUM_NOEXCEPT;
		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			JSClass tcp__;
			JSClass udp__;
#pragma warning(pop)
		};

	} // namespace Network
} // namespace Titanium
#endif // _TITANIUM_SOCKET_HPP_