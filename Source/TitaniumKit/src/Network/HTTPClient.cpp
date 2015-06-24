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
			: Module(js_context)
			, onload__(js_context.CreateNull())
			, onerror__(js_context.CreateNull())
			, ondatastream__(js_context.CreateNull())
			, onsendstream__(js_context.CreateNull())
			, onreadystatechange__(js_context.CreateNull())
			, done__(js_context.CreateNumber(static_cast<uint32_t>(RequestState::Done)))
			, headers_received__(js_context.CreateNumber(static_cast<uint32_t>(RequestState::Headers_Received)))
			, loading__(js_context.CreateNumber(static_cast<uint32_t>(RequestState::Loading)))
			, opened__(js_context.CreateNumber(static_cast<uint32_t>(RequestState::Opened)))
			, unsent__(js_context.CreateNumber(static_cast<uint32_t>(RequestState::Unsent)))
			, securityManager__(js_context.CreateNull())
			, status__(200)
			, readyState__(RequestState::Unsent)
		{
			setHTTPStatusPhrase();
		}

		TITANIUM_PROPERTY_READWRITE(HTTPClient, std::chrono::milliseconds, timeout)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, std::string, file)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, std::string, username)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, std::string, password)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, std::string, domain)
		TITANIUM_PROPERTY_READ(HTTPClient, std::string, location)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, bool, cache)

		TITANIUM_PROPERTY_READWRITE(HTTPClient, bool, autoEncodeUrl)
		TITANIUM_PROPERTY_READ(HTTPClient, RequestState, readyState)
		TITANIUM_PROPERTY_READ(HTTPClient, std::string, allResponseHeaders)
		TITANIUM_PROPERTY_READ(HTTPClient, std::uint32_t, status)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, TLS_VERSION, tlsVersion)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, bool, autoRedirect)
		TITANIUM_PROPERTY_READ(HTTPClient, bool, connected)
		TITANIUM_PROPERTY_READ(HTTPClient, std::string, connectionType) 
		TITANIUM_PROPERTY_READWRITE(HTTPClient, bool, enableKeepAlive)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, bool, validatesSecureCertificate)
		TITANIUM_PROPERTY_READWRITE(HTTPClient, bool, withCredentials)
		TITANIUM_PROPERTY_READ(HTTPClient, std::vector<std::uint8_t>, responseData);

		std::string HTTPClient::get_responseText() const TITANIUM_NOEXCEPT
		{
			auto data = get_responseData();
			return std::string(data.begin(), data.end());
		}

		std::string HTTPClient::get_statusText() const TITANIUM_NOEXCEPT
		{
			auto it = httpStatusPhrase__.find(get_status());
			if (it != httpStatusPhrase__.end()) {
				return it->second;
			}

			return "HTTP Status Phrase Not Found";
		}

		void HTTPClient::abort() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::abort: unimplemented");
		}

		void HTTPClient::clearCookies(const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::clearCookies: unimplemented");
		}

		std::string HTTPClient::getResponseHeader(const std::string& name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getResponseHeader: unimplemented");
			return "";
		}

		void HTTPClient::open(const std::string& method, const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::open: unimplemented");
		}

		void HTTPClient::send() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send: unimplemented");
		}

		void HTTPClient::send(const std::map<std::string, std::vector<std::uint8_t>>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send<data>: unimplemented");
		}

		void HTTPClient::send(const std::string& postDataStr) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send<data string>: unimplemented");
		}
		
		void HTTPClient::setRequestHeader(const std::string& name, const std::string& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::setRequestHeader: unimplemented");
		}

		void HTTPClient::JSExportInitialize()
		{
			JSExport<HTTPClient>::SetClassVersion(1);
			JSExport<HTTPClient>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(HTTPClient, autoEncodeUrl);
			TITANIUM_ADD_PROPERTY(HTTPClient, autoRedirect);
			TITANIUM_ADD_PROPERTY(HTTPClient, cache);
			TITANIUM_ADD_PROPERTY(HTTPClient, domain);
			TITANIUM_ADD_PROPERTY(HTTPClient, enableKeepAlive);
			TITANIUM_ADD_PROPERTY(HTTPClient, file);
			TITANIUM_ADD_PROPERTY(HTTPClient, ondatastream);
			TITANIUM_ADD_PROPERTY(HTTPClient, onerror);
			TITANIUM_ADD_PROPERTY(HTTPClient, onload);
			TITANIUM_ADD_PROPERTY(HTTPClient, onreadystatechange);
			TITANIUM_ADD_PROPERTY(HTTPClient, onsendstream);
			TITANIUM_ADD_PROPERTY(HTTPClient, password);
			TITANIUM_ADD_PROPERTY(HTTPClient, securityManager);
			TITANIUM_ADD_PROPERTY(HTTPClient, timeout);
			TITANIUM_ADD_PROPERTY(HTTPClient, tlsVersion);
			TITANIUM_ADD_PROPERTY(HTTPClient, username);
			TITANIUM_ADD_PROPERTY(HTTPClient, validatesSecureCertificate);
			TITANIUM_ADD_PROPERTY(HTTPClient, withCredentials);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, DONE);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, HEADERS_RECEIVED);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, LOADING);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, OPENED);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, UNSENT);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, allResponseHeaders);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, connected);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, connectionType);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, location);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, readyState);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, responseData);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, responseText);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, responseXML);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, status);
			TITANIUM_ADD_PROPERTY_READONLY(HTTPClient, statusText);

			TITANIUM_ADD_FUNCTION(HTTPClient, abort);
			TITANIUM_ADD_FUNCTION(HTTPClient, addAuthFactory);
			TITANIUM_ADD_FUNCTION(HTTPClient, addKeyManager);
			TITANIUM_ADD_FUNCTION(HTTPClient, addTrustManager);
			TITANIUM_ADD_FUNCTION(HTTPClient, clearCookies);
			TITANIUM_ADD_FUNCTION(HTTPClient, getAllResponseHeaders);
			TITANIUM_ADD_FUNCTION(HTTPClient, getAutoEncodeUrl);
			TITANIUM_ADD_FUNCTION(HTTPClient, getAutoRedirect);
			TITANIUM_ADD_FUNCTION(HTTPClient, getCache);
			TITANIUM_ADD_FUNCTION(HTTPClient, getConnected);
			TITANIUM_ADD_FUNCTION(HTTPClient, getConnectionType);
			TITANIUM_ADD_FUNCTION(HTTPClient, getDomain);
			TITANIUM_ADD_FUNCTION(HTTPClient, getEnableKeepAlive);
			TITANIUM_ADD_FUNCTION(HTTPClient, getFile);
			TITANIUM_ADD_FUNCTION(HTTPClient, getLocation);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOndatastream);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnerror);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnload);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnreadystatechange);
			TITANIUM_ADD_FUNCTION(HTTPClient, getOnsendstream);
			TITANIUM_ADD_FUNCTION(HTTPClient, getPassword);
			TITANIUM_ADD_FUNCTION(HTTPClient, getReadyState);
			TITANIUM_ADD_FUNCTION(HTTPClient, getResponseData);
			TITANIUM_ADD_FUNCTION(HTTPClient, getResponseHeader);
			TITANIUM_ADD_FUNCTION(HTTPClient, getResponseText);
			TITANIUM_ADD_FUNCTION(HTTPClient, getResponseXML);
			TITANIUM_ADD_FUNCTION(HTTPClient, getSecurityManager);
			TITANIUM_ADD_FUNCTION(HTTPClient, getStatus);
			TITANIUM_ADD_FUNCTION(HTTPClient, getStatusText);
			TITANIUM_ADD_FUNCTION(HTTPClient, getTimeout);
			TITANIUM_ADD_FUNCTION(HTTPClient, getTlsVersion);
			TITANIUM_ADD_FUNCTION(HTTPClient, getUsername);
			TITANIUM_ADD_FUNCTION(HTTPClient, getValidatesSecureCertificate);
			TITANIUM_ADD_FUNCTION(HTTPClient, getWithCredentials);
			TITANIUM_ADD_FUNCTION(HTTPClient, open);
			TITANIUM_ADD_FUNCTION(HTTPClient, send);
			TITANIUM_ADD_FUNCTION(HTTPClient, setAutoEncodeUrl);
			TITANIUM_ADD_FUNCTION(HTTPClient, setAutoRedirect);
			TITANIUM_ADD_FUNCTION(HTTPClient, setCache);
			TITANIUM_ADD_FUNCTION(HTTPClient, setDomain);
			TITANIUM_ADD_FUNCTION(HTTPClient, setEnableKeepAlive);
			TITANIUM_ADD_FUNCTION(HTTPClient, setFile);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOndatastream);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnerror);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnload);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnreadystatechange);
			TITANIUM_ADD_FUNCTION(HTTPClient, setOnsendstream);
			TITANIUM_ADD_FUNCTION(HTTPClient, setPassword);
			TITANIUM_ADD_FUNCTION(HTTPClient, setRequestHeader);
			TITANIUM_ADD_FUNCTION(HTTPClient, setSecurityManager);
			TITANIUM_ADD_FUNCTION(HTTPClient, setTimeout);
			TITANIUM_ADD_FUNCTION(HTTPClient, setTlsVersion);
			TITANIUM_ADD_FUNCTION(HTTPClient, setUsername);
			TITANIUM_ADD_FUNCTION(HTTPClient, setValidatesSecureCertificate);
			TITANIUM_ADD_FUNCTION(HTTPClient, setWithCredentials);

		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, LOADING)
		{
			return loading__;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, OPENED)
		{
			return opened__;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, DONE)
		{
			return done__;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, UNSENT)
		{
			return unsent__;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, HEADERS_RECEIVED)
		{
			return headers_received__;
		}

		TITANIUM_FUNCTION(HTTPClient, addAuthFactory)
		{
			TITANIUM_LOG_WARN("HTTPClient::addAuthFactory: unimplemented");
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(HTTPClient, addTrustManager)
		{
			TITANIUM_LOG_WARN("HTTPClient::addTrustManager: unimplemented");
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(HTTPClient, addKeyManager)
		{
			TITANIUM_LOG_WARN("HTTPClient::addKeyManager: unimplemented");
			return get_context().CreateUndefined();
		}

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
			TITANIUM_ASSERT(_0.IsString());
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_1.IsString() || _1.IsNull());
			const auto name = static_cast<std::string>(_0);
			std::string value;
			if (!_1.IsNull()) {
				value = static_cast<std::string>(_1);
			}
			setRequestHeader(name, value);
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, allResponseHeaders)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getAllResponseHeaders, allResponseHeaders)
		TITANIUM_PROPERTY_GETTER_UINT(HTTPClient, readyState)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getReadyState, readyState)

		TITANIUM_PROPERTY_GETTER(HTTPClient, responseData)
		{
			auto Blob = get_context().CreateObject(JSExport<Titanium::Blob>::Class());
			auto blob = Blob.CallAsConstructor();
			auto blob_ptr = blob.GetPrivate<Titanium::Blob>();

			blob_ptr->construct(get_responseData());

			return blob;
		}

		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getResponseData, responseData)
		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, responseText)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getResponseText, responseText)

		TITANIUM_PROPERTY_GETTER(HTTPClient, responseXML)
		{
			auto text = js_get_responseText();
			if (text.IsNull()) {
				return text;
			}

			auto global_object = get_context().get_global_object();

			auto ti = global_object.GetProperty("Titanium");
			auto Titanium = static_cast<JSObject>(ti);
			auto xml = Titanium.GetProperty("XML");
			auto XML = static_cast<JSObject>(xml);

			auto parseString = XML.GetProperty("parseString");
			auto parseStringObject = static_cast<JSObject>(parseString);
			std::vector<JSValue> arguments = { text };
			auto result = parseStringObject(arguments, global_object);

			return result;
		}

		TITANIUM_FUNCTION(HTTPClient, getResponseXML)
		{
			return js_get_responseXML();
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, securityManager)
		{
			return securityManager__;
		}

		TITANIUM_PROPERTY_SETTER(HTTPClient, securityManager)
		{
			TITANIUM_ASSERT(argument.IsObject());
			securityManager__ = static_cast<JSObject>(argument);
			return true;
		}

		TITANIUM_FUNCTION(HTTPClient, getSecurityManager)
		{
			return js_get_securityManager();
		}

		TITANIUM_FUNCTION(HTTPClient, setSecurityManager)
		{
			ENSURE_OBJECT_AT_INDEX(object, 0);
			js_set_securityManager(object);
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER_ENUM(HTTPClient, tlsVersion)
		TITANIUM_PROPERTY_SETTER_ENUM(HTTPClient, tlsVersion, TLS_VERSION)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getTlsVersion, tlsVersion)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setTlsVersion, tlsVersion)

		TITANIUM_PROPERTY_GETTER_BOOL(HTTPClient, autoEncodeUrl)
		TITANIUM_PROPERTY_SETTER_BOOL(HTTPClient, autoEncodeUrl)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getAutoEncodeUrl, autoEncodeUrl)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setAutoEncodeUrl, autoEncodeUrl)

		TITANIUM_PROPERTY_GETTER_BOOL(HTTPClient, autoRedirect)
		TITANIUM_PROPERTY_SETTER_BOOL(HTTPClient, autoRedirect)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getAutoRedirect, autoRedirect)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setAutoRedirect, autoRedirect)

		TITANIUM_PROPERTY_GETTER_BOOL(HTTPClient, connected)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getConnected, connected)

		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, connectionType)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getConnectionType, connectionType)

		TITANIUM_PROPERTY_GETTER_BOOL(HTTPClient, enableKeepAlive)
		TITANIUM_PROPERTY_SETTER_BOOL(HTTPClient, enableKeepAlive)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getEnableKeepAlive, enableKeepAlive)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setEnableKeepAlive, enableKeepAlive)

		TITANIUM_PROPERTY_GETTER_BOOL(HTTPClient, validatesSecureCertificate)
		TITANIUM_PROPERTY_SETTER_BOOL(HTTPClient, validatesSecureCertificate)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getValidatesSecureCertificate, validatesSecureCertificate)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setValidatesSecureCertificate, validatesSecureCertificate)

		TITANIUM_PROPERTY_GETTER_BOOL(HTTPClient, withCredentials)
		TITANIUM_PROPERTY_SETTER_BOOL(HTTPClient, withCredentials)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getWithCredentials, withCredentials)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setWithCredentials, withCredentials)

		TITANIUM_PROPERTY_GETTER_UINT(HTTPClient, status)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getStatus, status)
		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, statusText)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getStatusText, statusText)

		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, file)	
		TITANIUM_PROPERTY_SETTER_STRING(HTTPClient, file)	
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getFile, file)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setFile, file)

		TITANIUM_PROPERTY_GETTER_BOOL(HTTPClient, cache)	
		TITANIUM_PROPERTY_SETTER_BOOL(HTTPClient, cache)	
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getCache, cache)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setCache, cache)

		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, domain)	
		TITANIUM_PROPERTY_SETTER_STRING(HTTPClient, domain)	
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getDomain, domain)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setDomain, domain)

		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, location)	
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getLocation, location)

		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, username)	
		TITANIUM_PROPERTY_SETTER_STRING(HTTPClient, username)	
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getUsername, username)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setUsername, username)

		TITANIUM_PROPERTY_GETTER_STRING(HTTPClient, password)	
		TITANIUM_PROPERTY_SETTER_STRING(HTTPClient, password)	
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getPassword, password)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setPassword, password)

		TITANIUM_PROPERTY_SETTER(HTTPClient, ondatastream)
		{
			using namespace std::placeholders;

			ondatastream__ = argument;

			if (ondatastream__.IsObject() && static_cast<JSObject>(ondatastream__).IsFunction()) {
				datastream.connect(std::bind(&HTTPClient::ondatastream, this, _1));
			}

			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, ondatastream)
		{
			return ondatastream__;
		}

		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getOndatastream, ondatastream)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setOndatastream, ondatastream);

		TITANIUM_PROPERTY_SETTER(HTTPClient, onerror)
		{
			using namespace std::placeholders;

			onerror__ = argument;

			if (onerror__.IsObject() && static_cast<JSObject>(onerror__).IsFunction()) {
				error.connect(std::bind(&HTTPClient::onerror, this, _1, _2, _3));
			}

			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onerror)
		{
			return onerror__;
		}

		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getOnerror, onerror)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setOnerror, onerror)

		TITANIUM_PROPERTY_SETTER(HTTPClient, onload)
		{
			using namespace std::placeholders;

			onload__ = argument;

			if (onload__.IsObject() && static_cast<JSObject>(onload__).IsFunction()) {
				loaded.connect(std::bind(&HTTPClient::onload, this, _1, _2, _3));
			}

			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onload)
		{
			return onload__;
		}

		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getOnload, onload)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setOnload, onload)

		TITANIUM_PROPERTY_SETTER(HTTPClient, onreadystatechange)
		{
			using namespace std::placeholders;

			onreadystatechange__ = argument;

			if (onreadystatechange__.IsObject() && static_cast<JSObject>(onreadystatechange__).IsFunction()) {
				readystatechange.connect(std::bind(&HTTPClient::onreadystatechange, this, _1));
			}

			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onreadystatechange)
		{
			return onreadystatechange__;
		}

		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getOnreadystatechange, onreadystatechange)
		TITANIUM_FUNCTION_AS_SETTER(HTTPClient, setOnreadystatechange, onreadystatechange)

		TITANIUM_PROPERTY_SETTER(HTTPClient, onsendstream)
		{
			using namespace std::placeholders;

			onsendstream__ = argument;

			if (onsendstream__.IsObject() && static_cast<JSObject>(onsendstream__).IsFunction()) {
				sendstream.connect(std::bind(&HTTPClient::onsendstream, this, _1));
			}

			return true;
		}

		TITANIUM_PROPERTY_GETTER(HTTPClient, onsendstream)
		{
			return onsendstream__;
		}

		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getOnsendstream, onsendstream)
		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, setOnsendstream, onsendstream)

		TITANIUM_PROPERTY_GETTER_TIME(HTTPClient, timeout)
		TITANIUM_PROPERTY_SETTER(HTTPClient, timeout)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			double d = static_cast<double>(argument);
			std::chrono::milliseconds timeout((std::int64_t)d);
			set_timeout(timeout);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(HTTPClient, getTimeout, timeout)

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
			if (onload__.IsObject()) {
				auto onload = static_cast<JSObject>(onload__);
				if (onload.IsFunction()) {
					const JSContext ctx = get_context();

					JSObject this_object = get_object();
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("code", ctx.CreateNumber(code));
					eventArgs.SetProperty("error", ctx.CreateString(error));
					eventArgs.SetProperty("success", ctx.CreateBoolean(success));

					std::vector<JSValue> arguments;
					arguments.push_back(eventArgs);

					onload(arguments, this_object);
				}
			}
		}

		void HTTPClient::onerror(const std::uint32_t code, const std::string error, const bool success) TITANIUM_NOEXCEPT
		{
			if (onerror__.IsObject()) {
				auto onerror = static_cast<JSObject>(onerror__);
				if (onerror.IsFunction()) {
					const JSContext ctx = get_context();

					JSObject this_object = get_object();
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("code", ctx.CreateNumber(code));
					eventArgs.SetProperty("error", ctx.CreateString(error));
					eventArgs.SetProperty("success", ctx.CreateBoolean(success));

					std::vector<JSValue> arguments;
					arguments.push_back(eventArgs);

					onerror(arguments, this_object);
				}
			}
		}

		void HTTPClient::ondatastream(const double progress) TITANIUM_NOEXCEPT
		{
			if (ondatastream__.IsObject()) {
				auto ondatastream = static_cast<JSObject>(ondatastream__);
				if (ondatastream.IsFunction()) {
					const JSContext ctx = get_context();

					JSObject this_object = get_object();
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("progress", ctx.CreateNumber(progress));

					std::vector<JSValue> arguments;
					arguments.push_back(eventArgs);

					ondatastream(arguments, this_object);
				}
			}
		}

		void HTTPClient::onsendstream(const double progress) TITANIUM_NOEXCEPT
		{
			if (onsendstream__.IsObject()) {
				auto onsendstream = static_cast<JSObject>(onsendstream__);
				if (onsendstream.IsFunction()) {
					const JSContext ctx = get_context();

					JSObject this_object = get_object();
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("progress", ctx.CreateNumber(progress));

					std::vector<JSValue> arguments;
					arguments.push_back(eventArgs);

					onsendstream(arguments, this_object);
				}
			}
		}

		void HTTPClient::onreadystatechange(const RequestState& state) TITANIUM_NOEXCEPT
		{
			if (onreadystatechange__.IsObject()) {
				auto onreadystatechange = static_cast<JSObject>(onreadystatechange__);
				if (onreadystatechange.IsFunction()) {
					const JSContext ctx = get_context();

					JSObject this_object = get_object();
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("readyState", ctx.CreateNumber(static_cast<std::uint32_t>(state)));

					std::vector<JSValue> arguments;
					arguments.push_back(eventArgs);

					onreadystatechange(arguments, this_object);
				}
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
