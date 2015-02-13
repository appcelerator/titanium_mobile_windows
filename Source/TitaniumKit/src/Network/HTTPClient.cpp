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
		HTTPClient::HTTPClient(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Module(js_context),
		      timeout__(js_context.CreateString()),
		      onload_callback__(js_context.CreateObject()),
		      onerror_callback__(js_context.CreateObject()),
		      ondatastream_callback__(js_context.CreateObject()),
		      onsendstream_callback__(js_context.CreateObject()),
		      onreadystatechange_callback__(js_context.CreateObject())
		{
		}

		void HTTPClient::JSExportInitialize()
		{
			JSExport<HTTPClient>::SetClassVersion(1);
			JSExport<HTTPClient>::SetParent(JSExport<Module>::Class());

			JSExport<HTTPClient>::AddValueProperty("LOADING", std::mem_fn(&HTTPClient::js_getLOADING));
			JSExport<HTTPClient>::AddValueProperty("OPENED", std::mem_fn(&HTTPClient::js_getOPENED));
			JSExport<HTTPClient>::AddValueProperty("DONE", std::mem_fn(&HTTPClient::js_getDONE));
			JSExport<HTTPClient>::AddValueProperty("UNSENT", std::mem_fn(&HTTPClient::js_getUNSENT));
			JSExport<HTTPClient>::AddValueProperty("HEADERS_RECEIVED", std::mem_fn(&HTTPClient::js_getHEADERS_RECEIVED));

			JSExport<HTTPClient>::AddValueProperty("timeout", std::mem_fn(&HTTPClient::js_getTimeout), std::mem_fn(&HTTPClient::js_setTimeout));
			JSExport<HTTPClient>::AddValueProperty("responseText", std::mem_fn(&HTTPClient::js_getResponseText));
			JSExport<HTTPClient>::AddValueProperty("responseData", std::mem_fn(&HTTPClient::js_getResponseData));
			JSExport<HTTPClient>::AddValueProperty("allResponseHeaders", std::mem_fn(&HTTPClient::js_getAllResponseHeaders));
			JSExport<HTTPClient>::AddValueProperty("readyState", std::mem_fn(&HTTPClient::js_getReadyState));
			JSExport<HTTPClient>::AddValueProperty("status", std::mem_fn(&HTTPClient::js_getStatus));
			JSExport<HTTPClient>::AddValueProperty("statusText", std::mem_fn(&HTTPClient::js_getStatusText));
			JSExport<HTTPClient>::AddValueProperty("onload", std::mem_fn(&HTTPClient::js_getOnLoad), std::mem_fn(&HTTPClient::js_setOnLoad));
			JSExport<HTTPClient>::AddValueProperty("onerror", std::mem_fn(&HTTPClient::js_getOnError), std::mem_fn(&HTTPClient::js_setOnError));
			JSExport<HTTPClient>::AddValueProperty("ondatastream", std::mem_fn(&HTTPClient::js_getOnDataStream), std::mem_fn(&HTTPClient::js_setOnDataStream));
			JSExport<HTTPClient>::AddValueProperty("onsendstream", std::mem_fn(&HTTPClient::js_getOnSendStream), std::mem_fn(&HTTPClient::js_setOnSendStream));
			JSExport<HTTPClient>::AddValueProperty("onreadystate", std::mem_fn(&HTTPClient::js_getOnReadyStateChange), std::mem_fn(&HTTPClient::js_setOnReadyStateChange));

			JSExport<HTTPClient>::AddFunctionProperty("open", std::mem_fn(&HTTPClient::js_open));
			JSExport<HTTPClient>::AddFunctionProperty("send", std::mem_fn(&HTTPClient::js_send));
			JSExport<HTTPClient>::AddFunctionProperty("abort", std::mem_fn(&HTTPClient::js_abort));
			JSExport<HTTPClient>::AddFunctionProperty("setRequestHeader", std::mem_fn(&HTTPClient::js_setRequestHeader));
			JSExport<HTTPClient>::AddFunctionProperty("getResponseHeader", std::mem_fn(&HTTPClient::js_getResponseHeader));
			JSExport<HTTPClient>::AddFunctionProperty("clearCookies", std::mem_fn(&HTTPClient::js_clearCookies));
		}

		// constant properties
		JSValue HTTPClient::js_getLOADING() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(N_REQUEST_STATE_LOADING);
		}

		JSValue HTTPClient::js_getOPENED() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(N_REQUEST_STATE_OPENED);
		}

		JSValue HTTPClient::js_getDONE() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(N_REQUEST_STATE_DONE);
		}

		JSValue HTTPClient::js_getUNSENT() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(N_REQUEST_STATE_UNSENT);
		}

		JSValue HTTPClient::js_getHEADERS_RECEIVED() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(N_REQUEST_STATE_HEADERS_RECEIVED);
		}

		// properties
		void HTTPClient::setTimeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::setTimeout: Unimplemented");
		}

		bool HTTPClient::js_setTimeout(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			double d = static_cast<double>(argument);
			std::chrono::milliseconds timeout((long long)d);
			setTimeout(timeout);
			timeout__ = argument;
			return true;
		}

		JSValue HTTPClient::js_getTimeout() const TITANIUM_NOEXCEPT
		{
			return timeout__;
		}

		std::string HTTPClient::getResponseText() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getResponseText: Unimplemented");
			return std::string();  // empty
		}

		JSValue HTTPClient::js_getResponseText() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(getResponseText());
		}

		std::vector<unsigned char> HTTPClient::getResponseData() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getResponseData: Unimplemented");
			return std::vector<unsigned char>();  //empty
		}

		JSValue HTTPClient::js_getResponseData() const TITANIUM_NOEXCEPT
		{
			auto Blob = get_context().CreateObject(JSExport<Titanium::Blob>::Class());
			auto blob = Blob.CallAsConstructor();
			auto blob_ptr = blob.GetPrivate<Titanium::Blob>();

			// ToDo hookup to blob object
			blob_ptr->construct(getResponseData());

			return blob;
		}

		std::string HTTPClient::getAllResponseHeaders() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getAllResponseHeaders: Unimplemented");
			return std::string();  // empty
		}

		JSValue HTTPClient::js_getAllResponseHeaders() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(getAllResponseHeaders());
		}

		std::uint32_t HTTPClient::getReadyState() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getReadyState: Unimplemented");
			return std::uint32_t();
		}

		JSValue HTTPClient::js_getReadyState() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(getReadyState());
		}

		std::uint32_t HTTPClient::getStatus() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getStatus: Unimplemented");
			return std::uint32_t();
		}

		JSValue HTTPClient::js_getStatus() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(getStatus());
		}

		std::string HTTPClient::getStatusText() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getStatusText: Unimplemented");
			return std::string();
		}

		JSValue HTTPClient::js_getStatusText() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(getStatusText());
		}

		bool HTTPClient::js_setOnLoad(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			loaded.connect(std::bind(&HTTPClient::onload, this, _1, _2, _3));

			onload_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		JSValue HTTPClient::js_getOnLoad() const TITANIUM_NOEXCEPT
		{
			return onload_callback__;
		}

		bool HTTPClient::js_setOnError(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			error.connect(std::bind(&HTTPClient::onerror, this, _1, _2, _3));

			onerror_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		JSValue HTTPClient::js_getOnError() const TITANIUM_NOEXCEPT
		{
			return onerror_callback__;
		}

		bool HTTPClient::js_setOnDataStream(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			datastream.connect(std::bind(&HTTPClient::ondatastream, this, _1));

			ondatastream_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		JSValue HTTPClient::js_getOnDataStream() const TITANIUM_NOEXCEPT
		{
			return ondatastream_callback__;
		}

		bool HTTPClient::js_setOnSendStream(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			sendstream.connect(std::bind(&HTTPClient::onsendstream, this, _1));

			onsendstream_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		JSValue HTTPClient::js_getOnSendStream() const TITANIUM_NOEXCEPT
		{
			return onsendstream_callback__;
		}

		bool HTTPClient::js_setOnReadyStateChange(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			using namespace std::placeholders;
			TITANIUM_ASSERT(static_cast<JSObject>(argument).IsFunction());

			// connect the slot
			readystatechange.connect(std::bind(&HTTPClient::onreadystatechange, this, _1));

			onreadystatechange_callback__ = static_cast<JSObject>(argument);
			return true;
		}

		JSValue HTTPClient::js_getOnReadyStateChange() const TITANIUM_NOEXCEPT
		{
			return onreadystatechange_callback__;
		}

		// methods
		void HTTPClient::open(const std::string& method, const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::open: Unimplemented");
		}

		JSValue HTTPClient::js_open(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_0.IsString() && _1.IsString());
			const auto method = static_cast<std::string>(_0);
			const auto url = static_cast<std::string>(_1);
			open(method, url);
			return get_context().CreateUndefined();
		}

		void HTTPClient::send() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send: Unimplemented");
		}

		void HTTPClient::send(const std::map<std::string, std::vector<unsigned char>>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send<data>: Unimplemented");
		}

		void HTTPClient::send(const std::string& postDataStr) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::send<data string>: Unimplemented");
		}

		JSValue HTTPClient::js_send(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (!arguments.empty()) {
				TITANIUM_ASSERT(arguments.at(0).IsObject() || arguments.at(0).IsString());

				if (arguments.at(0).IsString()) {
					std::string postDataString = static_cast<std::string>(arguments.at(0));
					send(postDataString);
				} else {
					bool useMultipartForm = false;
					std::map<std::string, std::vector<unsigned char>> map;
					JSObject sendArgs = static_cast<JSObject>(arguments.at(0));
					for (const auto& property_name : static_cast<std::vector<JSString>>(sendArgs.GetPropertyNames())) {
						TITANIUM_ASSERT(sendArgs.GetProperty(property_name).IsObject() || sendArgs.GetProperty(property_name).IsString());
						JSValue prop = sendArgs.GetProperty(property_name);
						if (prop.IsString()) {
							std::string str = static_cast<std::string>(prop);
							std::vector<unsigned char> data(str.begin(), str.end());
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

		void HTTPClient::abort() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::abort: Unimplemented");
		}

		JSValue HTTPClient::js_abort(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			abort();
			return get_context().CreateUndefined();
		}

		void HTTPClient::setRequestHeader(const std::string& name, const std::string& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::setRequestHeader: Unimplemented");
		}

		JSValue HTTPClient::js_setRequestHeader(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_0.IsString() && _1.IsString());
			const auto name = static_cast<std::string>(_0);
			const auto value = static_cast<std::string>(_1);
			setRequestHeader(name, value);
			return get_context().CreateUndefined();
		}

		std::string HTTPClient::getResponseHeader(const std::string& name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::getResponseHeader: Unimplemented");
			return std::string();  // empty
		}

		JSValue HTTPClient::js_getResponseHeader(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto name = static_cast<std::string>(_0);
			return get_context().CreateString(getResponseHeader(name));
		}

		void HTTPClient::clearCookies(const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("HTTPClient::clearCookies: Unimplemented");
		}

		JSValue HTTPClient::js_clearCookies(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto url = static_cast<std::string>(_0);
			clearCookies(url);
			return get_context().CreateUndefined();
		}

		////// slots
		void HTTPClient::onload(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT
		{
			const JSContext ctx = get_context();

			JSObject eventArgs = ctx.CreateObject();
			eventArgs.SetProperty("id", ctx.CreateNumber(id));
			eventArgs.SetProperty("error", ctx.CreateString(error));
			eventArgs.SetProperty("success", ctx.CreateBoolean(success));

			std::vector<JSValue> arguments;
			arguments.push_back(eventArgs);

			//onload_callback__.CallAsFunction(arguments, this);
		}

		void HTTPClient::onerror(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT
		{
			const JSContext ctx = get_context();

			JSObject eventArgs = ctx.CreateObject();
			eventArgs.SetProperty("id", ctx.CreateNumber(id));
			eventArgs.SetProperty("error", ctx.CreateString(error));
			eventArgs.SetProperty("success", ctx.CreateBoolean(success));

			std::vector<JSValue> arguments;
			arguments.push_back(eventArgs);

			//onerror_callback__.CallAsFunction(arguments, this);
		}

		void HTTPClient::ondatastream(const std::uint32_t progress) TITANIUM_NOEXCEPT
		{
			const JSContext ctx = get_context();

			JSObject eventArgs = ctx.CreateObject();
			eventArgs.SetProperty("progress", ctx.CreateNumber(progress));

			std::vector<JSValue> arguments;
			arguments.push_back(eventArgs);

			//ondatastream_callback__.CallAsFunction(arguments, this);
		}

		void HTTPClient::onsendstream(const std::uint32_t progress) TITANIUM_NOEXCEPT
		{
			const JSContext ctx = get_context();

			JSObject eventArgs = ctx.CreateObject();
			eventArgs.SetProperty("progress", ctx.CreateNumber(progress));

			std::vector<JSValue> arguments;
			arguments.push_back(eventArgs);

			//ondatastream_callback__.CallAsFunction(arguments, this);
		}

		void HTTPClient::onreadystatechange(const std::uint32_t state) TITANIUM_NOEXCEPT
		{
			const JSContext ctx = get_context();

			JSObject eventArgs = ctx.CreateObject();
			eventArgs.SetProperty("readyState", ctx.CreateNumber(state));

			std::vector<JSValue> arguments;
			arguments.push_back(eventArgs);

			//onreadystate_callback__.CallAsFunction(arguments, this);
		}
	}
}
