/**
 * TitaniumKit Titanium.Network.Socket.UDP
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UDP_HPP_
#define _TITANIUM_UDP_HPP_

#include "Titanium/IOStream.hpp"

namespace Titanium
{
	namespace Network
	{
		namespace Socket
		{

			using namespace HAL;

			/*!
			  @class
			  @discussion This is the Titanium UDP Module.
			  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Network.Socket.UDP
			*/
			class TITANIUMKIT_EXPORT UDP : public IOStream, public JSExport<UDP>
			{

			public:

				/*!
				  @property
				  @abstract port
				  @discussion The port to connect to or listen on.
				*/
				TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, port);

				/*!
				  @method
				  @abstract start
				  @discussion Will start up the local UDP socket.
				*/
				virtual void start(const std::uint32_t& port, const std::string& host) TITANIUM_NOEXCEPT;

				/*!
				  @method
				  @abstract stop
				  @discussion Will tear down the local UDP socket.
				*/
				virtual void stop() TITANIUM_NOEXCEPT;

				/*!
				  @method
				  @abstract sendString
				  @discussion Will send the string as a UDP packet to designated host and port.
				*/
				virtual void sendString(const std::uint32_t& port, const std::string& host, const std::string& data) TITANIUM_NOEXCEPT;

				/*!
				  @method
				  @abstract sendBytes
				  @discussion Will send the bytes as a UDP packet to designated host and port.
				*/
				virtual void sendBytes(const std::uint32_t& port, const std::string& host, std::vector<std::uint8_t> data) TITANIUM_NOEXCEPT;

				UDP(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~UDP() = default;
				UDP(const UDP&) = default;
				UDP& operator=(const UDP&) = default;
	#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				UDP(UDP&&)                 = default;
				UDP& operator=(UDP&&)      = default;
	#endif

				static void JSExportInitialize();

				TITANIUM_PROPERTY_DEF(port);
				TITANIUM_PROPERTY_DEF(started);
				TITANIUM_PROPERTY_DEF(data);
				TITANIUM_PROPERTY_DEF(error);

				TITANIUM_FUNCTION_DEF(start);
				TITANIUM_FUNCTION_DEF(stop);
				TITANIUM_FUNCTION_DEF(sendString);
				TITANIUM_FUNCTION_DEF(sendBytes);
				TITANIUM_FUNCTION_DEF(getPort);
				TITANIUM_FUNCTION_DEF(setPort);
				TITANIUM_FUNCTION_DEF(getStarted);
				TITANIUM_FUNCTION_DEF(setStarted);
				TITANIUM_FUNCTION_DEF(getData);
				TITANIUM_FUNCTION_DEF(setData);
				TITANIUM_FUNCTION_DEF(getError);
				TITANIUM_FUNCTION_DEF(setError);

			protected:
	#pragma warning(push)
	#pragma warning(disable : 4251)
				std::uint32_t port__;
				std::string host__;
				JSValue started__;
				JSValue data__;
				JSValue error__;
	#pragma warning(pop)
			};

		} // namespace Socket
	} // namespace Network
} // namespace Titanium
#endif // _TITANIUM_UDP_HPP_