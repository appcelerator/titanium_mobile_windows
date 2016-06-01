/**
 * TitaniumKit Titanium.Network.Socket.TCP
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Network/Socket/TCP.hpp"
#include "Titanium/Network/Socket/AcceptDict.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Network
	{
		namespace Socket
		{
			TCP::TCP(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Module(js_context, "Ti.Network.Socket.TCP")
				, host__("")
				, port__(0)
				, listenQueueSize__(0)
				, timeout__(0)
				, state__(State::Closed)
				, connected__(js_context.CreateNull())
				, accepted__(js_context.CreateNull())
				, error__(js_context.CreateNull())
			{
			}

			TITANIUM_PROPERTY_READWRITE(TCP, std::string, host)

			TITANIUM_PROPERTY_READWRITE(TCP, std::uint32_t, port)
			TITANIUM_PROPERTY_READWRITE(TCP, std::uint32_t, listenQueueSize)
			TITANIUM_PROPERTY_READWRITE(TCP, std::chrono::milliseconds, timeout)

			TITANIUM_PROPERTY_READ(TCP, State, state);

			void TCP::close() TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("TCP::close: Unimplemented");
			}

			void TCP::connect() TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("TCP::connect: Unimplemented");
			}

			void TCP::listen() TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("TCP::listen: Unimplemented");
			}

			void TCP::accept(const AcceptDict& options) TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("TCP::accept: Unimplemented");
			}

			void TCP::JSExportInitialize()
			{
				JSExport<TCP>::SetClassVersion(1);
				JSExport<TCP>::SetParent(JSExport<Module>::Class());

				TITANIUM_ADD_PROPERTY(TCP, host);
				TITANIUM_ADD_PROPERTY(TCP, port);
				TITANIUM_ADD_PROPERTY(TCP, listenQueueSize);
				TITANIUM_ADD_PROPERTY(TCP, timeout);
				TITANIUM_ADD_PROPERTY(TCP, connected);
				TITANIUM_ADD_PROPERTY(TCP, error);
				TITANIUM_ADD_PROPERTY(TCP, accepted);
				TITANIUM_ADD_PROPERTY_READONLY(TCP, state);

				TITANIUM_ADD_FUNCTION(TCP, close);
				TITANIUM_ADD_FUNCTION(TCP, connect);
				TITANIUM_ADD_FUNCTION(TCP, listen);
				TITANIUM_ADD_FUNCTION(TCP, accept);
				TITANIUM_ADD_FUNCTION(TCP, getHost);
				TITANIUM_ADD_FUNCTION(TCP, setHost);
				TITANIUM_ADD_FUNCTION(TCP, getPort);
				TITANIUM_ADD_FUNCTION(TCP, setPort);
				TITANIUM_ADD_FUNCTION(TCP, getListenQueueSize);
				TITANIUM_ADD_FUNCTION(TCP, setListenQueueSize);
				TITANIUM_ADD_FUNCTION(TCP, getTimeout);
				TITANIUM_ADD_FUNCTION(TCP, setTimeout);
				TITANIUM_ADD_FUNCTION(TCP, getConnected);
				TITANIUM_ADD_FUNCTION(TCP, setConnected);
				TITANIUM_ADD_FUNCTION(TCP, getError);
				TITANIUM_ADD_FUNCTION(TCP, setError);
				TITANIUM_ADD_FUNCTION(TCP, getAccepted);
				TITANIUM_ADD_FUNCTION(TCP, setAccepted);
				TITANIUM_ADD_FUNCTION(TCP, getState);
			}

			TITANIUM_PROPERTY_GETTER_STRING(TCP, host)
			TITANIUM_PROPERTY_SETTER_STRING(TCP, host)

			TITANIUM_PROPERTY_GETTER_UINT(TCP, port)
			TITANIUM_PROPERTY_SETTER_UINT(TCP, port)

			TITANIUM_PROPERTY_GETTER_UINT(TCP, listenQueueSize)
			TITANIUM_PROPERTY_SETTER_UINT(TCP, listenQueueSize)

			TITANIUM_PROPERTY_GETTER_TIME(TCP, timeout)
			TITANIUM_PROPERTY_SETTER_TIME(TCP, timeout)

			TITANIUM_PROPERTY_GETTER_ENUM(TCP, state)

			TITANIUM_PROPERTY_GETTER(TCP, connected)
			{
				return connected__;
			}

			TITANIUM_PROPERTY_SETTER(TCP, connected)
			{
				connected__ = argument;
				return true;
			}

			TITANIUM_PROPERTY_GETTER(TCP, error)
			{
				return error__;
			}

			TITANIUM_PROPERTY_SETTER(TCP, error)
			{
				error__ = argument;
				return true;
			}

			TITANIUM_PROPERTY_GETTER(TCP, accepted)
			{
				return accepted__;
			}

			TITANIUM_PROPERTY_SETTER(TCP, accepted)
			{
				accepted__ = argument;
				return true;
			}

			TITANIUM_FUNCTION(TCP, close)
			{
				close();
				return get_context().CreateUndefined();
			}

			TITANIUM_FUNCTION(TCP, connect)
			{
				connect();
				return get_context().CreateUndefined();
			}
			TITANIUM_FUNCTION(TCP, listen)
			{
				listen();
				return get_context().CreateUndefined();
			}
			TITANIUM_FUNCTION(TCP, accept)
			{
				ENSURE_OBJECT_AT_INDEX(options, 0);
				accept(js_to_AcceptDict(options));
				return get_context().CreateUndefined();
			}

			TITANIUM_FUNCTION_AS_GETTER(TCP, getHost, host)
			TITANIUM_FUNCTION_AS_SETTER(TCP, setHost, host)
			TITANIUM_FUNCTION_AS_GETTER(TCP, getPort, port)
			TITANIUM_FUNCTION_AS_SETTER(TCP, setPort, port)
			TITANIUM_FUNCTION_AS_GETTER(TCP, getListenQueueSize, listenQueueSize)
			TITANIUM_FUNCTION_AS_SETTER(TCP, setListenQueueSize, listenQueueSize)
			TITANIUM_FUNCTION_AS_GETTER(TCP, getTimeout, timeout)
			TITANIUM_FUNCTION_AS_SETTER(TCP, setTimeout, timeout)
			TITANIUM_FUNCTION_AS_GETTER(TCP, getConnected, connected)
			TITANIUM_FUNCTION_AS_SETTER(TCP, setConnected, connected)
			TITANIUM_FUNCTION_AS_GETTER(TCP, getError, error)
			TITANIUM_FUNCTION_AS_SETTER(TCP, setError, error)
			TITANIUM_FUNCTION_AS_GETTER(TCP, getAccepted, accepted)
			TITANIUM_FUNCTION_AS_SETTER(TCP, setAccepted, accepted)
			TITANIUM_FUNCTION_AS_GETTER(TCP, getState, state)

		} // namespace Socket
	} // namespace Network
} // namespace Titanium
