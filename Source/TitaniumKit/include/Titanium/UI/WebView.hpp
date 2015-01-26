/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_WEBVIEW_HPP_
#define _TITANIUM_UI_WEBVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium.UI.WebView module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.WebView
		*/
		class TITANIUMKIT_EXPORT WebView : public View, public JSExport<WebView>
		{
		public:

			virtual std::string get_url() const TITANIUM_NOEXCEPT final;
			virtual void set_url(const std::string& url) TITANIUM_NOEXCEPT;

			virtual std::string get_userAgent() const TITANIUM_NOEXCEPT final;
			virtual void set_userAgent(const std::string& userAgent) TITANIUM_NOEXCEPT;

			virtual std::string get_data() const TITANIUM_NOEXCEPT final;
			virtual void set_data(const std::string& data) TITANIUM_NOEXCEPT;

			virtual std::string get_html() const TITANIUM_NOEXCEPT final;
			virtual void set_html(const std::string& html) TITANIUM_NOEXCEPT;

			virtual bool get_loading() const TITANIUM_NOEXCEPT final;
			virtual void set_loading(const bool loading) TITANIUM_NOEXCEPT;

			virtual bool canGoBack() TITANIUM_NOEXCEPT;
			virtual bool canGoForward() TITANIUM_NOEXCEPT;
			virtual std::string evalJS(std::string script) TITANIUM_NOEXCEPT;
			virtual void goBack() TITANIUM_NOEXCEPT;
			virtual void goForward() TITANIUM_NOEXCEPT;
			virtual void reload() TITANIUM_NOEXCEPT;
			virtual void setBasicAuthentication(std::string username, std::string password) TITANIUM_NOEXCEPT;

			WebView(const JSContext& js_context) TITANIUM_NOEXCEPT;
			WebView(const WebView&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

			virtual ~WebView() = default;
			WebView(const WebView&) = default;
			WebView& operator=(const WebView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WebView(WebView&&) = default;
			WebView& operator=(WebView&&) = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_getUrl(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setUrl(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_url() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_url(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_getUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_userAgent() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_userAgent(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_getData(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setData(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_data() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_data(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_getHtml(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHtml(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_html() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_html(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_getLoading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setLoading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_loading() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_loading(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_canGoBack(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_canGoForward(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_evalJS(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_goBack(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_goForward(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_reload(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setBasicAuthentication(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_WEBVIEW_HPP_
