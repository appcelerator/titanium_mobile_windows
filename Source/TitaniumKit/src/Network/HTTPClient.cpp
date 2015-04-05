/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Network/HTTPClient.hpp"
#include "Titanium/Blob.hpp"

namespace Titanium
{
	namespace Network
	{
		HTTPClient::HTTPClient(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context),
		      onload_callback__(js_context.CreateObject()),
		      onerror_callback__(js_context.CreateObject()),
			  ondatastream_callback__(js_context.CreateObject()),
		      onsendstream_callback__(js_context.CreateObject()),
		      onreadystatechange_callback__(js_context.CreateObject())
		{
			setHTTPStatusPhrase();
		}

		std::chrono::milliseconds HTTPClient::get_timeout() const TITANIUM_NOEXCEPT
		{
			return timeout__;
		}

		void HTTPClient::set_timeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT
		{
			timeout__ = timeout;
		}

		std::string HTTPClient::get_responseText() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::get_responseText: Unimplemented");
			return "";
		}

		std::vector<std::uint8_t> HTTPClient::get_responseData() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::get_responseData: Unimplemented");
			return std::vector<std::uint8_t>();  //empty
		}

		std::string HTTPClient::get_allResponseHeaders() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::get_allResponseHeaders: Unimplemented");
			return "";
		}

		std::uint32_t HTTPClient::get_readyState() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getReadyState: Unimplemented");
			return N_REQUEST_STATE_UNSENT;
		}

		std::uint32_t HTTPClient::get_status() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getStatus: Unimplemented");
			return 200;
		}

		std::string HTTPClient::get_statusText() const TITANIUM_NOEXCEPT
		{
			auto it = httpStatusPhrase__.find(get_status());
			if (it != httpStatusPhrase__.end()) {
				return it->second;
			}

			return "HTTP Status Phrase Not Found";
		}

		// Methods
		void HTTPClient::abort() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::abort: Unimplemented");
		}

		void HTTPClient::clearCookies(const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::clearCookies: Unimplemented");
		}

		std::string HTTPClient::getResponseHeader(const std::string& name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getResponseHeader: Unimplemented");
			return "";
		}

		void HTTPClient::open(const std::string& method, const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::open: Unimplemented");
		}

		void HTTPClient::send() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send: Unimplemented");
		}

		void HTTPClient::send(const std::map<std::string, std::vector<std::uint8_t>>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send<data>: Unimplemented");
		}

		void HTTPClient::send(const std::string& postDataStr) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send<data string>: Unimplemented");
		}
		
		void HTTPClient::setRequestHeader(const std::string& name, const std::string& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::setRequestHeader: Unimplemented");
		}

		void HTTPClient::JSExportInitialize()
		{
			JSExport<HTTPClient>::SetClassVersion(1);
			JSExport<HTTPClient>::SetParent(JSExport<Module>::Class());
			// constants
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, LOADING);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, OPENED);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, DONE);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, UNSENT);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, HEADERS_RECEIVED);
			// properties
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, allResponseHeaders);
			TITANIUM_ADD_PROPERTY(HTTPClient, ondatastream);
			TITANIUM_ADD_PROPERTY(HTTPClient, onerror);
			TITANIUM_ADD_PROPERTY(HTTPClient, onload);
			TITANIUM_ADD_PROPERTY(HTTPClient, onreadystatechange);
			TITANIUM_ADD_PROPERTY(HTTPClient, onsendstream);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, readyState);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, responseData);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, responseText);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, status);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, statusText);
			TITANIUM_ADD_PROPERTY(HTTPClient, timeout);
			// methods
			TITANIUM_ADD_FUNCTION(HTTPClient, open);
			TITANIUM_ADD_FUNCTION(HTTPClient, send);
			TITANIUM_ADD_FUNCTION(HTTPClient, abort);
			TITANIUM_ADD_FUNCTION(HTTPClient, setRequestHeader);
			TITANIUM_ADD_FUNCTION(HTTPClient, getResponseHeader);
			TITANIUM_ADD_FUNCTION(HTTPClient, clearCookies);

			// accessors
			TITANIUM_ADD_FUNCTION(HTTPClient, getAllResponseHeaders);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOndatastream);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOndatastream);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnerror);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnerror);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnload);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnload);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnreadystatechange);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnreadystatechange);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnsendstream);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnsendstream);
			TITANIUM_ADD_FUNCTION(HTTPClient, getReadyState);
			TITANIUM_ADD_FUNCTION(HTTPClient, getResponseData);
			TITANIUM_ADD_FUNCTION(HTTPClient, getResponseText);
			TITANIUM_ADD_FUNCTION(HTTPClient, getStatus);
			TITANIUM_ADD_FUNCTION(HTTPClient, getStatusText);
			TITANIUM_ADD_FUNCTION(HTTPClient, getTimeout);
			TITANIUM_ADD_FUNCTION(HTTPClient, setTimeout);
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, LOADING)
		{
			return get_context().CreateNumber(N_REQUEST_STATE_LOADING);
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, OPENED)
		{
			return get_context().CreateNumber(N_REQUEST_STATE_OPENED);
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, DONE)
		{
			return get_context().CreateNumber(N_REQUEST_STATE_DONE);
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, UNSENT)
		{
			return get_context().CreateNumber(N_REQUEST_STATE_UNSENT);
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, HEADERS_RECEIVED)
		{
			return get_context().CreateNumber(N_REQUEST_STATE_HEADERS_RECEIVED);
		}

		// Methods
		TITANIUM_FUNCTION(HTTPClient, abort)
		{
			abort();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(HTTPClient, clearCookies)
		{
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto url = static_cast<std::string>(_0);
			clearCookies(url);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(HTTPClient, getResponseHeader)
		{
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto name = static_cast<std::string>(_0);
			return get_context().CreateString(getResponseHeader(name));
		}

		TITANIUM_FUNCTION(HTTPClient, open)
		{
			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_0.IsString() && _1.IsString());
			const auto method = static_cast<std::string>(_0);
			const auto url = static_cast<std::string>(_1);
			open(method, url);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(HTTPClient, send)
		{
			if (!arguments.empty()) {
				TITANIUM_ASSERT(arguments.at(0).IsObject() || arguments.at(0).IsString());

				if (arguments.at(0).IsString()) {
					std::string postDataString = static_cast<std::string>(arguments.at(0));
					send(postDataString);
				} else {
					bool useMultipartForm = false;
					std::map<std::string, std::vector<std::uint8_t>> map;
					JSObject sendArgs = static_cast<JSObject>(arguments.at(0));
					for (const auto& property_name : static_cast<std::vector<JSString>>(sendArgs.GetPropertyNames())) {
						TITANIUM_ASSERT(sendArgs.GetProperty(property_name).IsObject() || sendArgs.GetProperty(property_name).IsString());
						JSValue prop = sendArgs.GetProperty(property_name);
						if (prop.IsString()) {
							std::string str = static_cast<std::string>(prop);
							std::vector<std::uint8_t> data(str.begin(), str.end());
							map.insert(std::make_pair(property_name, data));
						} else {
							useMultipartForm = true;
							auto blob_ptr = static_cast<JSObject>(prop).GetPrivate<Titanium::Blob>();
							map.insert(std::make_pair(property_name, blob_ptr->getData()));
						}
					}
					send(map, useMultipartForm);
				}
			} else {
				send();
			}

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(HTTPClient, setRequestHeader)
		{
			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_0.IsString() && _1.IsString());
			const auto name = static_cast<std::string>(_0);
			const auto value = static_cast<std::string>(_1);
			setRequestHeader(name, value);
			return get_context().CreateUndefined();
		}

		// properties
		TITANIUM_PROPERTY_GETTER(HTTPClient, allResponseHeaders)
		{
			return get_context().CreateString(get_allResponseHeaders());
		}

		TITANIUM_FUNCTION(HTTPClient, getAllResponseHeaders)
		{
			return js_get_allResponseHeaders();
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, readyState)
		{
			return get_context().CreateNumber(get_readyState());
		}

		TITANIUM_FUNCTION(HTTPClient, getReadyState)
		{
			return js_get_readyState();
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, responseData)
		{
			auto Blob = get_context().CreateObject(JSExport<Titanium::Blob>::Class());
			auto blob = Blob.CallAsConstructor();
			auto blob_ptr = blob.GetPrivate<Titanium::Blob>();

			blob_ptr->construct(get_responseData());

			return blob;
		}

		TITANIUM_FUNCTION(HTTPClient, getResponseData)
		{
			return js_get_responseData();
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, responseText)
		{
			return get_context().CreateString(get_responseText());
		}

		TITANIUM_FUNCTION(HTTPClient, getResponseText)
		{
			return js_get_responseText();
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, status)
		{
			return get_context().CreateNumber(get_status());
		}
			
		TITANIUM_FUNCTION(HTTPClient, getStatus)
		{
			return js_get_status();
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, statusText)
		{
			return get_context().CreateString(get_statusText());
		}

		TITANIUM_FUNCTION(HTTPClient, getStatusText)
		{
			return js_get_statusText();
		}

		TITANIUM_PROPERTY_SETTER(HTTPClient, ondatastream)
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			datastream.connect(std::bind(&HTTPClient::ondatastream, this, _1));

			ondatastream_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, ondatastream)
		{
			return ondatastream_callback__;
		}

		TITANIUM_FUNCTION(HTTPClient, getOndatastream)
		{
			return js_get_ondatastream();
		}

		TITANIUM_FUNCTION(HTTPClient, setOndatastream)
		{
			if (arguments.size() >= 1) {
				js_set_ondatastream(arguments.at(0));
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(HTTPClient, onerror)
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			error.connect(std::bind(&HTTPClient::onerror, this, _1, _2, _3));

			onerror_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onerror)
		{
			return onerror_callback__;
		}

		TITANIUM_FUNCTION(HTTPClient, getOnerror)
		{
			return js_get_onerror();
		}

		TITANIUM_FUNCTION(HTTPClient, setOnerror)
		{
			if (arguments.size() >= 1) {
				js_set_onerror(arguments.at(0));
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(HTTPClient, onload)
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			loaded.connect(std::bind(&HTTPClient::onload, this, _1, _2, _3));

			onload_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onload)
		{
			return onload_callback__;
		}

		TITANIUM_FUNCTION(HTTPClient, getOnload)
		{
			return js_get_onload();
		}

		TITANIUM_FUNCTION(HTTPClient, setOnload)
		{
			if (arguments.size() >= 1) {
				js_set_onload(arguments.at(0));
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(HTTPClient, onreadystatechange)
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			readystatechange.connect(std::bind(&HTTPClient::onreadystatechange, this, _1));

			onreadystatechange_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onreadystatechange)
		{
			return onreadystatechange_callback__;
		}

		TITANIUM_FUNCTION(HTTPClient, getOnreadystatechange)
		{
			return js_get_onreadystatechange();
		}

		TITANIUM_FUNCTION(HTTPClient, setOnreadystatechange)
		{
			if (arguments.size() >= 1) {
				js_set_onreadystatechange(arguments.at(0));
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(HTTPClient, onsendstream)
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			sendstream.connect(std::bind(&HTTPClient::onsendstream, this, _1));

			onsendstream_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onsendstream)
		{
			return onsendstream_callback__;
		}

		TITANIUM_FUNCTION(HTTPClient, getOnsendstream)
		{
			return js_get_onsendstream();
		}

		TITANIUM_FUNCTION(HTTPClient, setOnsendstream)
		{
			if (arguments.size() >= 1) {
				js_set_onsendstream(arguments.at(0));
			}
			return this_object.get_context().CreateUndefined();
		}
			
		TITANIUM_PROPERTY_GETTER(HTTPClient, timeout)
		{
			return get_context().CreateNumber(static_cast<double>(get_timeout().count()));
		}

		TITANIUM_PROPERTY_SETTER(HTTPClient, timeout)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			double d = static_cast<double>(argument);
			std::chrono::milliseconds timeout((long long)d);
			set_timeout(timeout);
			return true;
		}

		TITANIUM_FUNCTION(HTTPClient, getTimeout)
		{
			return js_get_timeout();
		}

		TITANIUM_FUNCTION(HTTPClient, setTimeout)
		{
			if (arguments.size() >= 1) {
				js_set_timeout(arguments.at(0));
			}
			return this_object.get_context().CreateUndefined();
		}

		////// slots
		void HTTPClient::onload(const std::uint32_t code, const std::string error, const bool success) TITANIUM_NOEXCEPT
		{
			if (onload_callback__.IsFunction()) {
				const JSContext ctx = get_context();

				JSObject this_object = get_object();

				JSObject eventArgs = ctx.CreateObject();
				eventArgs.SetProperty("code", ctx.CreateNumber(code));
				eventArgs.SetProperty("error", ctx.CreateString(error));
				eventArgs.SetProperty("success", ctx.CreateBoolean(success));

				std::vector<JSValue> arguments;
				arguments.push_back(eventArgs);

				onload_callback__(arguments, this_object);
			}
		}

		void HTTPClient::onerror(const std::uint32_t code, const std::string error, const bool success) TITANIUM_NOEXCEPT
		{
			if (onerror_callback__.IsFunction()) {
				const JSContext ctx = get_context();

				JSObject this_object = get_object();

				JSObject eventArgs = ctx.CreateObject();
				eventArgs.SetProperty("code", ctx.CreateNumber(code));
				eventArgs.SetProperty("error", ctx.CreateString(error));
				eventArgs.SetProperty("success", ctx.CreateBoolean(success));

				std::vector<JSValue> arguments;
				arguments.push_back(eventArgs);

				onerror_callback__(arguments, this_object);
			}
		}

		void HTTPClient::ondatastream(const double progress) TITANIUM_NOEXCEPT
		{
			if (ondatastream_callback__.IsFunction()) {
				const JSContext ctx = get_context();

				JSObject this_object = get_object();

				JSObject eventArgs = ctx.CreateObject();
				eventArgs.SetProperty("progress", ctx.CreateNumber(progress));

				std::vector<JSValue> arguments;
				arguments.push_back(eventArgs);

				ondatastream_callback__(arguments, this_object);
			}
		}

		void HTTPClient::onsendstream(const double progress) TITANIUM_NOEXCEPT
		{
			if (onsendstream_callback__.IsFunction()) {
				const JSContext ctx = get_context();

				JSObject this_object = get_object();

				JSObject eventArgs = ctx.CreateObject();
				eventArgs.SetProperty("progress", ctx.CreateNumber(progress));

				std::vector<JSValue> arguments;
				arguments.push_back(eventArgs);

				onsendstream_callback__(arguments, this_object);
			}
		}

		void HTTPClient::onreadystatechange(const std::uint32_t state) TITANIUM_NOEXCEPT
		{
			if (onreadystatechange_callback__.IsFunction()) {
				const JSContext ctx = get_context();

				JSObject this_object = get_object();

				JSObject eventArgs = ctx.CreateObject();
				eventArgs.SetProperty("readyState", ctx.CreateNumber(state));

				std::vector<JSValue> arguments;
				arguments.push_back(eventArgs);

				onreadystatechange_callback__(arguments, this_object);
			}
		}

		void HTTPClient::setHTTPStatusPhrase()
		{
			httpStatusPhrase__[100] = "Continue";
			httpStatusPhrase__[101] = "Processing";
			httpStatusPhrase__[102] = "Processing";
			httpStatusPhrase__[200] = "OK";
			httpStatusPhrase__[201] = "Created";
			httpStatusPhrase__[202] = "Accepted";
			httpStatusPhrase__[203] = "Non-Authoritative Information";
			httpStatusPhrase__[204] = "No Content";
			httpStatusPhrase__[205] = "Reset Content";
			httpStatusPhrase__[206] = "Partial Content";
			httpStatusPhrase__[207] = "Multi-Status";
			httpStatusPhrase__[300] = "Multiple Choices";
			httpStatusPhrase__[301] = "Moved Permanently";
			httpStatusPhrase__[302] = "Moved Temporarily";
			httpStatusPhrase__[303] = "See Other";
			httpStatusPhrase__[304] = "Not Modified";
			httpStatusPhrase__[305] = "Use Proxy";
			httpStatusPhrase__[307] = "Temporary Redirect";
			httpStatusPhrase__[400] = "Bad Request";
			httpStatusPhrase__[401] = "Unauthorized";
			httpStatusPhrase__[402] = "Payment Required";
			httpStatusPhrase__[403] = "Forbidden";
			httpStatusPhrase__[404] = "Not Found";
			httpStatusPhrase__[405] = "Method Not Allowed";
			httpStatusPhrase__[406] = "Not Acceptable";
			httpStatusPhrase__[407] = "Proxy Authentication Required";
			httpStatusPhrase__[408] = "Request Time-out";
			httpStatusPhrase__[409] = "Conflict";
			httpStatusPhrase__[410] = "Gone";
			httpStatusPhrase__[411] = "Length Required";
			httpStatusPhrase__[412] = "Precondition Failed";
			httpStatusPhrase__[413] = "Request Entity Too Large";
			httpStatusPhrase__[414] = "Request-URI Too Large";
			httpStatusPhrase__[415] = "Unsupported Media Type";
			httpStatusPhrase__[416] = "Requested Range Not Satisfiable";
			httpStatusPhrase__[417] = "Expectation Failed";
			httpStatusPhrase__[418] = "I'm a teapot";
			httpStatusPhrase__[422] = "Unprocessable Entity";
			httpStatusPhrase__[423] = "Locked";
			httpStatusPhrase__[424] = "Failed Dependency";
			httpStatusPhrase__[425] = "Unordered Collection";
			httpStatusPhrase__[426] = "Upgrade Required";
			httpStatusPhrase__[428] = "Precondition Required";
			httpStatusPhrase__[429] = "Too Many Requests";
			httpStatusPhrase__[431] = "Request Header Fields Too Large";
			httpStatusPhrase__[500] = "Internal Server Error";
			httpStatusPhrase__[501] = "Not Implemented";
			httpStatusPhrase__[502] = "Bad Gateway";
			httpStatusPhrase__[503] = "Service Unavailable";
			httpStatusPhrase__[504] = "Gateway Time-out";
			httpStatusPhrase__[505] = "HTTP Version Not Supported";
			httpStatusPhrase__[506] = "Variant Also Negotiates";
			httpStatusPhrase__[507] = "Insufficient Storage";
			httpStatusPhrase__[509] = "Bandwidth Limit Exceeded";
			httpStatusPhrase__[510] = "Not Extended";
			httpStatusPhrase__[511] = "Network Authentication Required";
		}
	}
}
