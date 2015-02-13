/**
 * TitaniumKit Titanium.UI.WebView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_WEBVIEW_HPP_
#define _TITANIUM_UI_WEBVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include <unordered_map>

namespace Titanium 
{
	namespace UI 
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium WebView Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.WebView
		 */
		class TITANIUMKIT_EXPORT WebView : public View, public JSExport<WebView> 
		{

		public:

			/*!
			  @property
			  @abstract data
			  @discussion Web content to load.
			*/
			virtual std::vector<unsigned char> getData() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setData
			  @discussion
			*/
			virtual bool setData(const std::vector<unsigned char>& data) TITANIUM_NOEXCEPT;
			/*!
			  @property
			  @abstract html
			  @discussion HTML content of this web view.
			*/
			virtual std::string getHtml() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setHtml
			  @discussion Sets the value of [html](Titanium.UI.WebView.html) property.
			*/
			virtual bool setHtml(const std::string& html, const std::unordered_map<std::string, std::string>& options) TITANIUM_NOEXCEPT;
			/*!
			  @property
			  @abstract loading
			  @discussion Indicates if the webview is loading content.
			*/
			virtual bool getLoading() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setLoading
			  @discussion
			*/
			virtual bool setLoading(const bool& value) TITANIUM_NOEXCEPT;
			/*!
			  @property
			  @abstract getScalesPageToFit
			  @discussion If `true`, scale contents to fit the web view.
			*/
			virtual bool getScalesPageToFit() const TITANIUM_NOEXCEPT;
			/*!
			  @property
			  @abstract setScalesPageToFit
			  @discussion Sets the value of the scalesPageToFit property.
			*/
			virtual bool setScalesPageToFit(const bool& value) TITANIUM_NOEXCEPT;
			/*!
			  @property
			  @abstract getUrl
			  @discussion URL to the web document.
			*/
			virtual std::string getUrl() const TITANIUM_NOEXCEPT;
			/*!
			  @property
			  @abstract setUrl
			  @discussion Sets URL to the web document.
			*/
			virtual bool setUrl(const std::string& url) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract canGoBack
			  @discussion Returns `true` if the web view can go back in its history list.
			*/
			virtual bool canGoBack() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract canGoForward
			  @discussion Returns `true` if the web view can go forward in its history list.
			*/
			virtual bool canGoForward() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract evalJS
			  @discussion Evaluates a JavaScript expression inside the context of the web view andoptionally, returns a result.
			*/
			virtual std::string evalJS(const std::string& code) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract goBack
			  @discussion Goes back one entry in the web view's history list, to the previous page.
			*/
			virtual void goBack() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract goForward
			  @discussion Goes forward one entry in this web view's history list, if possible.
			*/
			virtual void goForward() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract reload
			  @discussion Reloads the current webpage.
			*/
			virtual void reload() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setBasicAuthentication
			  @discussion Sets the basic authentication for this web view to use on subsequent URl requests.
			*/
			virtual bool setBasicAuthentication(const std::string& username, const std::string& password) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract stopLoading
			  @discussion Stops loading a currently loading page.
			*/
			virtual void stopLoading(const bool& hardStop) TITANIUM_NOEXCEPT;

			WebView(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~WebView() = default;
			WebView(const WebView&) = default;
			WebView& operator=(const WebView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WebView(WebView&&)                 = default;
			WebView& operator=(WebView&&)      = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_data() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_html() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_loading() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_loading(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_scalesPageToFit() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_scalesPageToFit(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_url() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_url(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_canGoBack(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_canGoForward(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_evalJS(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_goBack(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_goForward(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_reload(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setBasicAuthentication(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_stopLoading(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getData(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setData(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHtml(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHtml(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getLoading(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setLoading(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getScalesPageToFit(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setScalesPageToFit(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getUrl(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setUrl(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		};
	} // namespace UI
}  // namespace Titanium
#endif // _TITANIUM_UI_WEBVIEW_HPP_