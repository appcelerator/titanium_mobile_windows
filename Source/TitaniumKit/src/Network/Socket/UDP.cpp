/**
 * TitaniumKit Titanium.Network.Socket.UDP
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Network/Socket/UDP.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Network
	{
		namespace Socket
		{

			UDP::UDP(const JSContext& js_context) TITANIUM_NOEXCEPT
				: IOStream(js_context, "Ti.Network.Socket.UDP")
				, port__(0)
				, started__(js_context.CreateNull())
				, data__(js_context.CreateNull())
				, error__(js_context.CreateNull())
			{
			}

			TITANIUM_PROPERTY_READWRITE(UDP, std::uint32_t, port)

			void UDP::start(const std::uint32_t& port, const std::string& host) TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("UDP::start: Unimplemented");
			}

			void UDP::stop() TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("UDP::stop: Unimplemented");
			}

			void UDP::sendString(const std::uint32_t& port, const std::string& host, const std::string& data) TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("UDP::sendString: Unimplemented");
			}

			void UDP::sendBytes(const std::uint32_t& port, const std::string& host, std::vector<std::uint8_t> data) TITANIUM_NOEXCEPT
			{
				TITANIUM_LOG_WARN("UDP::sendBytes: Unimplemented");
			}

			void UDP::JSExportInitialize()
			{
				JSExport<UDP>::SetClassVersion(1);
				JSExport<UDP>::SetParent(JSExport<Module>::Class());

				TITANIUM_ADD_PROPERTY(UDP, port);
				TITANIUM_ADD_PROPERTY(UDP, started);
				TITANIUM_ADD_PROPERTY(UDP, data);
				TITANIUM_ADD_PROPERTY(UDP, error);

				TITANIUM_ADD_FUNCTION(UDP, start);
				TITANIUM_ADD_FUNCTION(UDP, stop);
				TITANIUM_ADD_FUNCTION(UDP, sendString);
				TITANIUM_ADD_FUNCTION(UDP, sendBytes);
				TITANIUM_ADD_FUNCTION(UDP, getPort);
				TITANIUM_ADD_FUNCTION(UDP, setPort);
				TITANIUM_ADD_FUNCTION(UDP, getStarted);
				TITANIUM_ADD_FUNCTION(UDP, setStarted);
				TITANIUM_ADD_FUNCTION(UDP, getData);
				TITANIUM_ADD_FUNCTION(UDP, setData);
				TITANIUM_ADD_FUNCTION(UDP, getError);
				TITANIUM_ADD_FUNCTION(UDP, setError);
			}

			TITANIUM_PROPERTY_GETTER_UINT(UDP, port)
			TITANIUM_PROPERTY_SETTER_UINT(UDP, port)

			TITANIUM_PROPERTY_GETTER(UDP, started)
			{
				return started__;
			}

			TITANIUM_PROPERTY_SETTER(UDP, started)
			{
				started__ = argument;
				return true;
			}

			TITANIUM_PROPERTY_GETTER(UDP, data)
			{
				return data__;
			}

			TITANIUM_PROPERTY_SETTER(UDP, data)
			{
				data__ = argument;
				return true;
			}

			TITANIUM_PROPERTY_GETTER(UDP, error)
			{
				return error__;
			}

			TITANIUM_PROPERTY_SETTER(UDP, error)
			{
				error__ = argument;
				return true;
			}

			TITANIUM_FUNCTION(UDP, start)
			{
				ENSURE_OPTIONAL_UINT_AT_INDEX(port, 0, 0);
				ENSURE_OPTIONAL_STRING_AT_INDEX(host, 1, "");
				start(port, host);
				return get_context().CreateUndefined();
			}

			TITANIUM_FUNCTION(UDP, stop)
			{
				stop();
				return get_context().CreateUndefined();
			}

			TITANIUM_FUNCTION(UDP, sendString)
			{
				ENSURE_OPTIONAL_UINT_AT_INDEX(port, 0, 0);
				ENSURE_OPTIONAL_STRING_AT_INDEX(host, 1, "");
				ENSURE_OPTIONAL_STRING_AT_INDEX(data, 2, "");

				sendString(port, host, data);
				return get_context().CreateUndefined();
			}

			TITANIUM_FUNCTION(UDP, sendBytes)
			{
				ENSURE_OPTIONAL_UINT_AT_INDEX(port, 0, 0);
				ENSURE_OPTIONAL_STRING_AT_INDEX(host, 1, "");
				ENSURE_OPTIONAL_ARRAY_AT_INDEX(js_data, 2);

				std::vector<std::uint8_t> data;
				const auto length = js_data.GetLength();
				for (uint32_t i = 0; i < length; i++) {
					data.push_back(static_cast<std::uint8_t>(static_cast<std::uint32_t>(js_data.GetProperty(i))));
				}

				sendBytes(port, host, data);
				return get_context().CreateUndefined();
			}

			TITANIUM_FUNCTION_AS_GETTER(UDP, getPort, port)
			TITANIUM_FUNCTION_AS_SETTER(UDP, setPort, port)
			TITANIUM_FUNCTION_AS_GETTER(UDP, getStarted, started)
			TITANIUM_FUNCTION_AS_SETTER(UDP, setStarted, started)
			TITANIUM_FUNCTION_AS_GETTER(UDP, getData, data)
			TITANIUM_FUNCTION_AS_SETTER(UDP, setData, data)
			TITANIUM_FUNCTION_AS_GETTER(UDP, getError, error)
			TITANIUM_FUNCTION_AS_SETTER(UDP, setError, error)

		} // namespace Socket
	} // namespace Network
} // namespace Titanium
