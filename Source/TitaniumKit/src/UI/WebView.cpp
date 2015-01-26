/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/WebView.hpp"
#include <type_traits>

namespace Titanium
{
	namespace UI
	{
		WebView::WebView(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context)
		{
		}

		WebView::WebView(const WebView& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : View(rhs, arguments)
		{
		}

		void WebView::JSExportInitialize()
		{
			JSExport<WebView>::SetClassVersion(1);
			JSExport<WebView>::SetParent(JSExport<View>::Class());
			JSExport<WebView>::AddFunctionProperty("getUrl", std::mem_fn(&WebView::js_getUrl));
			JSExport<WebView>::AddFunctionProperty("setUrl", std::mem_fn(&WebView::js_setUrl));
			JSExport<WebView>::AddValueProperty("url", std::mem_fn(&WebView::js_get_url), std::mem_fn(&WebView::js_set_url));

			JSExport<WebView>::AddFunctionProperty("getUserAgent", std::mem_fn(&WebView::js_getUserAgent));
			JSExport<WebView>::AddFunctionProperty("setUserAgent", std::mem_fn(&WebView::js_setUserAgent));
			JSExport<WebView>::AddValueProperty("userAgent", std::mem_fn(&WebView::js_get_userAgent), std::mem_fn(&WebView::js_set_userAgent));

			JSExport<WebView>::AddFunctionProperty("getData", std::mem_fn(&WebView::js_getData));
			JSExport<WebView>::AddFunctionProperty("setData", std::mem_fn(&WebView::js_setData));
			JSExport<WebView>::AddValueProperty("data", std::mem_fn(&WebView::js_get_data), std::mem_fn(&WebView::js_set_data));

			JSExport<WebView>::AddFunctionProperty("getHtml", std::mem_fn(&WebView::js_getHtml));
			JSExport<WebView>::AddFunctionProperty("setHtml", std::mem_fn(&WebView::js_setHtml));
			JSExport<WebView>::AddValueProperty("html", std::mem_fn(&WebView::js_get_html), std::mem_fn(&WebView::js_set_html));

			JSExport<WebView>::AddFunctionProperty("getLoading", std::mem_fn(&WebView::js_getLoading));
			JSExport<WebView>::AddFunctionProperty("setLoading", std::mem_fn(&WebView::js_setLoading));
			JSExport<WebView>::AddValueProperty("loading", std::mem_fn(&WebView::js_get_loading), std::mem_fn(&WebView::js_set_loading));

			JSExport<WebView>::AddFunctionProperty("canGoBack", std::mem_fn(&WebView::js_canGoBack));
			JSExport<WebView>::AddFunctionProperty("canGoForward", std::mem_fn(&WebView::js_canGoForward));
			JSExport<WebView>::AddFunctionProperty("evalJS", std::mem_fn(&WebView::js_evalJS));
			JSExport<WebView>::AddFunctionProperty("goBack", std::mem_fn(&WebView::js_goBack));
			JSExport<WebView>::AddFunctionProperty("goForward", std::mem_fn(&WebView::js_goForward));
			JSExport<WebView>::AddFunctionProperty("reload", std::mem_fn(&WebView::js_goForward));
			JSExport<WebView>::AddFunctionProperty("setBasicAuthentication", std::mem_fn(&WebView::js_setBasicAuthentication));
		}

		std::string WebView::get_url() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::get_url: Unimplemented");
			return "";
		}
		void WebView::set_url(const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::set_url: Unimplemented");
		}
		std::string WebView::get_userAgent() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::get_url: Unimplemented");
			return "";
		}
		void WebView::set_userAgent(const std::string& userAgent) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::set_userAgent: Unimplemented");
		}
		std::string WebView::get_html() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::get_html: Unimplemented");
			return "";
		}
		void WebView::set_html(const std::string& html) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::set_html: Unimplemented");
		}
		std::string WebView::get_data() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::get_data: Unimplemented");
			return "";
		}
		void WebView::set_data(const std::string& html) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::set_data: Unimplemented");
		}
		bool WebView::get_loading() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::get_loading: Unimplemented");
			return "";
		}
		void WebView::set_loading(const bool loading) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::set_loading: Unimplemented");
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
		std::string WebView::evalJS(std::string script) TITANIUM_NOEXCEPT
		{
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
		void WebView::setBasicAuthentication(std::string username, std::string password) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView:::setBasicAuthentication Unimplemented");
		}
		
		JSValue WebView::js_getUrl(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			return js_get_url();
		}

		JSValue WebView::js_setUrl(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(arguments.size() >= 1);
			js_set_url(arguments.at(0));
			return get_context().CreateUndefined();
		}

		JSValue WebView::js_get_url() const TITANIUM_NOEXCEPT {
			return get_context().CreateString(get_url());
		}
		bool WebView::js_set_url(const JSValue& argument) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(argument.IsString());
			const auto url = static_cast<std::string>(argument);
			set_url(url);
			return true;
		}

		JSValue WebView::js_getUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			return js_get_userAgent();
		}
		JSValue WebView::js_setUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(arguments.size() >= 1);
			js_set_userAgent(arguments.at(0));
			return get_context().CreateUndefined();
		}
		JSValue WebView::js_get_userAgent() const TITANIUM_NOEXCEPT {
			return get_context().CreateString(get_userAgent());
		}
		bool WebView::js_set_userAgent(const JSValue& argument) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(argument.IsString());
			const auto userAgent = static_cast<std::string>(argument);
			set_userAgent(userAgent);
			return true;
		}

		JSValue WebView::js_getData(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			return js_get_data();
		}
		JSValue WebView::js_setData(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(arguments.size() >= 1);
			js_set_data(arguments.at(0));
			return get_context().CreateUndefined();
		}
		JSValue WebView::js_get_data() const TITANIUM_NOEXCEPT {
			return get_context().CreateString(get_data());
		}
		bool WebView::js_set_data(const JSValue& argument) TITANIUM_NOEXCEPT {
			if (argument.IsString()) {
				const auto data = static_cast<std::string>(argument);
				set_data(data);
			} else {
				// TODO: Add support for Ti.Filesystem.File and Ti.Blog
				return false;
			}
			return true;
		}

		JSValue WebView::js_getHtml(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			return js_get_html();
		}
		JSValue WebView::js_setHtml(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(arguments.size() >= 1);
			js_set_html(arguments.at(0));
			return get_context().CreateUndefined();
		}
		JSValue WebView::js_get_html() const TITANIUM_NOEXCEPT {
			return get_context().CreateString(get_html());
		}
		bool WebView::js_set_html(const JSValue& argument) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(argument.IsString());
			const auto html = static_cast<std::string>(argument);
			set_html(html);
			return true;
		}

		JSValue WebView::js_getLoading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			return js_get_loading();
		}
		JSValue WebView::js_setLoading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(arguments.size() >= 1);
			js_set_loading(arguments.at(0));
			return get_context().CreateUndefined();
		}
		JSValue WebView::js_get_loading() const TITANIUM_NOEXCEPT {
			return get_context().CreateBoolean(get_loading());
		}
		bool WebView::js_set_loading(const JSValue& argument) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(argument.IsString());
			const auto loading = static_cast<bool>(argument);
			set_loading(loading);
			return true;
		}

		JSValue WebView::js_canGoBack(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			return get_context().CreateBoolean(canGoBack());
		}
		JSValue WebView::js_canGoForward(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			return get_context().CreateBoolean(canGoForward());
		}
		JSValue WebView::js_evalJS(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(arguments.size() >= 1);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto script = static_cast<std::string>(_0);
			return get_context().CreateString(evalJS(script));
		}
		JSValue WebView::js_goBack(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			goBack();
			return get_context().CreateUndefined();
		}
		JSValue WebView::js_goForward(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			goForward();
			return get_context().CreateUndefined();
		}
		JSValue WebView::js_reload(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			reload();
			return get_context().CreateUndefined();
		}
		JSValue WebView::js_setBasicAuthentication(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			TITANIUM_ASSERT(arguments.size() >= 2);
			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_0.IsString());
			TITANIUM_ASSERT(_1.IsString());
			const auto username = static_cast<std::string>(_0);
			const auto password = static_cast<std::string>(_1);
			setBasicAuthentication(username, password);
			return get_context().CreateUndefined();
		}
	} // namespace UI
}  // namespace Titanium
