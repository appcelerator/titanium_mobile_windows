/**
 * TitaniumKit Titanium.UI.WebView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/WebView.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Filesystem/File.hpp"

namespace Titanium
{
	namespace UI
	{

		WebView::WebView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.WebView")
			, onlink__(js_context.CreateNull())
		{
		}

		void WebView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::View::postCallAsConstructor(js_context, arguments);

			//
			// _executeListener is a callback for internal use that listens to Ti.App events.
			// Since there's no way to find "this" webview object when App callback is fired,
			// we do little cheat here: attach "this" object to the function.
			//
			auto executeListener_prop = get_object().GetProperty("_executeListener");
			TITANIUM_ASSERT(executeListener_prop.IsObject());
			auto executeListener = static_cast<JSObject>(executeListener_prop);
			executeListener.SetProperty("webview", get_object());
		}

		void WebView::set_data(const std::shared_ptr<Titanium::Blob>& data) TITANIUM_NOEXCEPT {
			data__ = data;
			set_html(data->get_text());
		}

		std::shared_ptr<Titanium::Blob> WebView::get_data() const TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("WebView::get_data: Not Implemented");
			return nullptr;
		}

		TITANIUM_PROPERTY_READWRITE(WebView, std::vector<std::string>, blacklistedURLs)
		TITANIUM_PROPERTY_READWRITE(WebView, std::string, html)

		bool WebView::setHtml(const std::string& html, const std::unordered_map<std::string, std::string>& options) TITANIUM_NOEXCEPT
		{
			set_html(html);
			return true;
		}

		TITANIUM_PROPERTY_READWRITE(WebView, bool, loading)

		TITANIUM_PROPERTY_READWRITE(WebView, bool, scalesPageToFit)

		TITANIUM_PROPERTY_READWRITE(WebView, std::string, url)

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

		std::string WebView::evalJS(const std::string& code, JSObject& callback) TITANIUM_NOEXCEPT
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
			JSExport<WebView>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(WebView, data);
			TITANIUM_ADD_PROPERTY(WebView, html);
			TITANIUM_ADD_PROPERTY(WebView, loading);
			TITANIUM_ADD_PROPERTY(WebView, scalesPageToFit);
			TITANIUM_ADD_PROPERTY(WebView, url);
			TITANIUM_ADD_PROPERTY(WebView, blacklistedURLs);
			TITANIUM_ADD_PROPERTY(WebView, onlink);
			TITANIUM_ADD_FUNCTION(WebView, canGoBack);
			TITANIUM_ADD_FUNCTION(WebView, canGoForward);
			TITANIUM_ADD_FUNCTION(WebView, evalJS);
			TITANIUM_ADD_FUNCTION(WebView, goBack);
			TITANIUM_ADD_FUNCTION(WebView, goForward);
			TITANIUM_ADD_FUNCTION(WebView, reload);
			TITANIUM_ADD_FUNCTION(WebView, setBasicAuthentication);
			TITANIUM_ADD_FUNCTION(WebView, stopLoading);
			TITANIUM_ADD_FUNCTION(WebView, getBlacklistedURLs);
			TITANIUM_ADD_FUNCTION(WebView, setBlacklistedURLs);
			TITANIUM_ADD_FUNCTION(WebView, getData);
			TITANIUM_ADD_FUNCTION(WebView, setData);
			TITANIUM_ADD_FUNCTION(WebView, getHtml);
			TITANIUM_ADD_FUNCTION(WebView, setHtml);
			TITANIUM_ADD_FUNCTION(WebView, getLoading);
			TITANIUM_ADD_FUNCTION(WebView, setLoading);
			TITANIUM_ADD_FUNCTION(WebView, getScalesPageToFit);
			TITANIUM_ADD_FUNCTION(WebView, setScalesPageToFit);
			TITANIUM_ADD_FUNCTION(WebView, getUrl);
			TITANIUM_ADD_FUNCTION(WebView, setUrl);
			TITANIUM_ADD_FUNCTION(WebView, _executeListener);
		}

		TITANIUM_PROPERTY_SETTER(WebView, data)
		{
			const auto data = static_cast<JSObject>(argument);
			const auto blob_ptr = data.GetPrivate<Titanium::Blob>();
			if (blob_ptr) {
				set_data(blob_ptr);
			} else {
				const auto file_ptr = data.GetPrivate<Titanium::Filesystem::File>();
				if (file_ptr) {
					const auto blob_ptr = file_ptr->read();
					if (blob_ptr) {
						set_data(blob_ptr);
					}
				}
			}
			return true;
		}

		TITANIUM_PROPERTY_GETTER(WebView, data)
		{
			const auto data = get_data();
			if (data) {
				return data->get_object();
			}
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_GETTER(WebView, html)
		{
			return get_context().CreateString(get_html());
		}

		TITANIUM_PROPERTY_SETTER(WebView, html)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_html(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(WebView, loading)
		{
			return get_context().CreateBoolean(get_loading());
		}

		TITANIUM_PROPERTY_SETTER(WebView, loading)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_loading(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(WebView, scalesPageToFit)
		{
			return get_context().CreateBoolean(get_scalesPageToFit());
		}

		TITANIUM_PROPERTY_SETTER(WebView, scalesPageToFit)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_scalesPageToFit(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(WebView, url)
		{
			return get_context().CreateString(get_url());
		}

		TITANIUM_PROPERTY_SETTER(WebView, url)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_url(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION(WebView, setHtml)
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

		TITANIUM_FUNCTION(WebView, canGoBack)
		{
			return get_context().CreateBoolean(canGoBack());
		}

		TITANIUM_FUNCTION(WebView, canGoForward)
		{
			return get_context().CreateBoolean(canGoForward());
		}

		TITANIUM_FUNCTION(WebView, evalJS)
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			}

			ENSURE_STRING_AT_INDEX(code, 0);
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(callback, 1);

			return get_context().CreateString(evalJS(code, callback));
		}

		TITANIUM_FUNCTION(WebView, goBack)
		{
			goBack();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, goForward)
		{
			goForward();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, reload)
		{
			reload();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, setBasicAuthentication)
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

		TITANIUM_FUNCTION(WebView, stopLoading)
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

		TITANIUM_FUNCTION_AS_GETTER(WebView, getData, data);
		TITANIUM_FUNCTION_AS_SETTER(WebView, setData, data);

		TITANIUM_PROPERTY_SETTER(WebView, onlink)
		{
			onlink__ = argument; // allow setting to null/undefined
			return true;
		}

		TITANIUM_PROPERTY_GETTER(WebView, onlink)
		{
			return onlink__;
		}

		TITANIUM_PROPERTY_GETTER_STRING_ARRAY(WebView, blacklistedURLs);
		TITANIUM_PROPERTY_SETTER_STRING_ARRAY(WebView, blacklistedURLs);
		TITANIUM_FUNCTION_AS_GETTER(WebView, getBlacklistedURLs, blacklistedURLs);
		TITANIUM_FUNCTION_AS_SETTER(WebView, setBlacklistedURLs, blacklistedURLs);

		void WebView::_executeListener(const std::string& name, const std::string& data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::_executeListener: Unimplemented for event ", name);
		}

		//
		// _executeListener is internal function for Ti.App event callback.
		//
		TITANIUM_FUNCTION(WebView, _executeListener)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_OBJECT_AT_INDEX(callee, 1);
			auto webview = callee.GetProperty("webview");
			if (!webview.IsObject()) {
				TITANIUM_LOG_WARN("WebView._executeListener: Can't find this object");
				return get_context().CreateUndefined();
			}
			auto webview_ptr = static_cast<JSObject>(webview).GetPrivate<Titanium::UI::WebView>();
			TITANIUM_ASSERT(webview_ptr);

			ENSURE_OBJECT_AT_INDEX(data, 0);
			webview_ptr->_executeListener(
				static_cast<std::string>(data.GetProperty("type")),
				static_cast<std::string>(static_cast<JSValue>(data).ToJSONString()));

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(WebView, getHtml, html)

		TITANIUM_FUNCTION_AS_GETTER(WebView, getLoading, loading)
		TITANIUM_FUNCTION_AS_SETTER(WebView, setLoading, loading)

		TITANIUM_FUNCTION_AS_GETTER(WebView, getScalesPageToFit, scalesPageToFit)
		TITANIUM_FUNCTION_AS_SETTER(WebView, setScalesPageToFit, scalesPageToFit)

		TITANIUM_FUNCTION_AS_GETTER(WebView, getUrl, url)
		TITANIUM_FUNCTION_AS_SETTER(WebView, setUrl, url)

	} // namespace UI
}  // namespace Titanium
