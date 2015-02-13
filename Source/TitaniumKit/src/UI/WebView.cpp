/**
 * TitaniumKit Titanium.UI.WebView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/WebView.hpp"

namespace Titanium
{
	namespace UI
	{

		WebView::WebView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: View(js_context, arguments)
		{
		}

		std::vector<unsigned char> WebView::getData() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getData: Unimplemented");
			return std::vector<unsigned char>();
		}

		bool WebView::setData(const std::vector<unsigned char>& data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setData: Unimplemented");
			return false;
		}

		std::string WebView::getHtml() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getHtml: Unimplemented");
			return "";
		}
		bool WebView::setHtml(const std::string& html, const std::unordered_map<std::string, std::string>& options) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setHtml: Unimplemented");
			return false;
		}

		bool WebView::getLoading() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getLoading: Unimplemented");
			return false;
		}

		bool WebView::setLoading(const bool& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setLoading: Unimplemented");
			return false;
		}

		bool WebView::getScalesPageToFit() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getScalesPageToFit: Unimplemented");
			return false;
		}

		bool WebView::setScalesPageToFit(const bool& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setScalesPageToFit: Unimplemented");
			return false;
		}

		std::string WebView::getUrl() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getUrl: Unimplemented");
			return "";
		}

		bool WebView::setUrl(const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setUrl: Unimplemented");
			return false;
		}

		bool WebView::canGoBack() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::canGoBack: Unimplemented");
			return false;
		}

		bool WebView::canGoForward() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::canGoForward: Unimplemented");
			return false;
		}

		std::string WebView::evalJS(const std::string& code) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::evalJS: Unimplemented");
			return "";
		}

		void WebView::goBack() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::goBack: Unimplemented");
		}

		void WebView::goForward() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::goForward: Unimplemented");
		}

		void WebView::reload() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::reload: Unimplemented");
		}

		bool WebView::setBasicAuthentication(const std::string& username, const std::string& password) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setBasicAuthentication: Unimplemented");
			return false;
		}

		void WebView::stopLoading(const bool& hardStop) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::stopLoading: Unimplemented");
		}

		void WebView::JSExportInitialize() {
			JSExport<WebView>::SetClassVersion(1);
			JSExport<WebView>::SetParent(JSExport<Module>::Class());

			JSExport<WebView>::AddValueProperty("data", std::mem_fn(&WebView::js_get_data));
			JSExport<WebView>::AddValueProperty("html", std::mem_fn(&WebView::js_get_html));
			JSExport<WebView>::AddValueProperty("loading", std::mem_fn(&WebView::js_get_loading), std::mem_fn(&WebView::js_set_loading));
			JSExport<WebView>::AddValueProperty("scalesPageToFit", std::mem_fn(&WebView::js_get_scalesPageToFit), std::mem_fn(&WebView::js_set_scalesPageToFit));
			JSExport<WebView>::AddValueProperty("url", std::mem_fn(&WebView::js_get_url), std::mem_fn(&WebView::js_set_url));
			JSExport<WebView>::AddFunctionProperty("canGoBack", std::mem_fn(&WebView::js_canGoBack));
			JSExport<WebView>::AddFunctionProperty("canGoForward", std::mem_fn(&WebView::js_canGoForward));
			JSExport<WebView>::AddFunctionProperty("evalJS", std::mem_fn(&WebView::js_evalJS));
			JSExport<WebView>::AddFunctionProperty("goBack", std::mem_fn(&WebView::js_goBack));
			JSExport<WebView>::AddFunctionProperty("goForward", std::mem_fn(&WebView::js_goForward));
			JSExport<WebView>::AddFunctionProperty("reload", std::mem_fn(&WebView::js_reload));
			JSExport<WebView>::AddFunctionProperty("setBasicAuthentication", std::mem_fn(&WebView::js_setBasicAuthentication));
			JSExport<WebView>::AddFunctionProperty("stopLoading", std::mem_fn(&WebView::js_stopLoading));
			JSExport<WebView>::AddFunctionProperty("getData", std::mem_fn(&WebView::js_getData));
			JSExport<WebView>::AddFunctionProperty("setData", std::mem_fn(&WebView::js_setData));
			JSExport<WebView>::AddFunctionProperty("getHtml", std::mem_fn(&WebView::js_getHtml));
			JSExport<WebView>::AddFunctionProperty("setHtml", std::mem_fn(&WebView::js_setHtml));
			JSExport<WebView>::AddFunctionProperty("getLoading", std::mem_fn(&WebView::js_getLoading));
			JSExport<WebView>::AddFunctionProperty("setLoading", std::mem_fn(&WebView::js_setLoading));
			JSExport<WebView>::AddFunctionProperty("getScalesPageToFit", std::mem_fn(&WebView::js_getScalesPageToFit));
			JSExport<WebView>::AddFunctionProperty("setScalesPageToFit", std::mem_fn(&WebView::js_setScalesPageToFit));
			JSExport<WebView>::AddFunctionProperty("getUrl", std::mem_fn(&WebView::js_getUrl));
			JSExport<WebView>::AddFunctionProperty("setUrl", std::mem_fn(&WebView::js_setUrl));
		}

		JSValue WebView::js_get_data() const TITANIUM_NOEXCEPT
		{
			// TODO Convert std::vector<unsigned char> to JSObject (Ti.Blob)
			TITANIUM_LOG_WARN("WebView.data is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_get_html() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(getHtml());
		}

		JSValue WebView::js_get_loading() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(getLoading());
		}

		bool WebView::js_set_loading(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return setLoading(static_cast<bool>(argument));
		}

		JSValue WebView::js_get_scalesPageToFit() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(getScalesPageToFit());
		}

		bool WebView::js_set_scalesPageToFit(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return setScalesPageToFit(static_cast<bool>(argument));
		}

		JSValue WebView::js_get_url() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(getUrl());
		}

		bool WebView::js_set_url(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			return setUrl(static_cast<std::string>(argument));
		}

		JSValue WebView::js_setHtml(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			std::unordered_map<std::string, std::string> options;
	    
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			}
	    
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			const auto html = static_cast<std::string>(_0);
	    
			if (arguments.size() >= 2) {
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsObject());
				const auto js_options = static_cast<JSObject>(_1);
				// extract JSObject into C++ unordered_map
				for (const auto& property_name : static_cast<std::vector<JSString>>(js_options.GetPropertyNames())) {
					options.emplace(property_name, static_cast<std::string>(js_options.GetProperty(property_name)));
				}
			}
			setHtml(html, options);
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_canGoBack(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(canGoBack());
		}

		JSValue WebView::js_canGoForward(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(canGoForward());
		}

		JSValue WebView::js_evalJS(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsString());
				const std::string code = static_cast<std::string>(_0);
				return get_context().CreateString(evalJS(code));
			}
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_goBack(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			goBack();
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_goForward(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			goForward();
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_reload(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			reload();
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_setBasicAuthentication(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 2) {
				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsString());

				const std::string username = static_cast<std::string>(_0);
				const std::string password = static_cast<std::string>(_1);

				setBasicAuthentication(username, password);
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsString());
				const std::string username = static_cast<std::string>(_0);
				setBasicAuthentication(username, "");
			}
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_stopLoading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				const bool hardStop = static_cast<bool>(_0);
				stopLoading(hardStop);
			}
			stopLoading(false);
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_getData(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_data();
		}

		JSValue WebView::js_setData(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto data = _0;
				// TODO Convert JSObject(Ti.Blob or Ti.File) to std::vector<unsigned char>
				// setData(data);
			}
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_getHtml(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(getHtml());
		}

		JSValue WebView::js_getLoading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(getLoading());
		}

		JSValue WebView::js_setLoading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				const bool loading = static_cast<bool>(_0);
				setLoading(loading);
			}
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_getScalesPageToFit(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(getScalesPageToFit());
		}

		JSValue WebView::js_setScalesPageToFit(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				const bool scalesPageToFit = static_cast<bool>(_0);
				setScalesPageToFit(scalesPageToFit);
			}
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_getUrl(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(getUrl());
		}

		JSValue WebView::js_setUrl(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsString());
				const std::string url = static_cast<std::string>(_0);
				setUrl(url);
			}
			return get_context().CreateUndefined();
		}
	} // namespace UI
}  // namespace Titanium