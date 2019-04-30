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
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::Blob>, data);

			/*!
			  @property
			  @abstract html
			  @discussion HTML content of this web view.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, html);

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
			TITANIUM_PROPERTY_IMPL_DEF(bool, loading);

			/*!
			  @property
			  @abstract scalesPageToFit
			  @discussion If `true`, scale contents to fit the web view.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, scalesPageToFit);

			/*!
			  @property
			  @abstract url
			  @discussion URL to the web document.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, url);

			/*!
			  @property
			  @abstract blacklistedURLs
			  @discussion An array of url strings to blacklist.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::string>, blacklistedURLs);

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
			  @param code JavaScript code to evaluate
			  @param callback JavaScript function that is executed asynchronously
			  @discussion Evaluates a JavaScript expression inside the context of the web view and optionally, returns a result.
			*/
			virtual std::string evalJS(const std::string& code, JSObject& callback) TITANIUM_NOEXCEPT;

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

			WebView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~WebView() = default;
			WebView(const WebView&) = default;
			WebView& operator=(const WebView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WebView(WebView&&)                 = default;
			WebView& operator=(WebView&&)      = default;
#endif

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			TITANIUM_PROPERTY_DEF(data);
			TITANIUM_PROPERTY_DEF(html);
			TITANIUM_PROPERTY_DEF(loading);
			TITANIUM_PROPERTY_DEF(scalesPageToFit);
			TITANIUM_PROPERTY_DEF(url);
			TITANIUM_PROPERTY_DEF(blacklistedURLs);
			TITANIUM_PROPERTY_DEF(onlink);
			TITANIUM_FUNCTION_DEF(canGoBack);
			TITANIUM_FUNCTION_DEF(canGoForward);
			TITANIUM_FUNCTION_DEF(evalJS);
			TITANIUM_FUNCTION_DEF(goBack);
			TITANIUM_FUNCTION_DEF(goForward);
			TITANIUM_FUNCTION_DEF(reload);
			TITANIUM_FUNCTION_DEF(setBasicAuthentication);
			TITANIUM_FUNCTION_DEF(stopLoading);
			TITANIUM_FUNCTION_DEF(getData);
			TITANIUM_FUNCTION_DEF(setData);
			TITANIUM_FUNCTION_DEF(getHtml);
			TITANIUM_FUNCTION_DEF(setHtml);
			TITANIUM_FUNCTION_DEF(getLoading);
			TITANIUM_FUNCTION_DEF(setLoading);
			TITANIUM_FUNCTION_DEF(getScalesPageToFit);
			TITANIUM_FUNCTION_DEF(setScalesPageToFit);
			TITANIUM_FUNCTION_DEF(getUrl);
			TITANIUM_FUNCTION_DEF(setUrl);
			TITANIUM_FUNCTION_DEF(getBlacklistedURLs);
			TITANIUM_FUNCTION_DEF(setBlacklistedURLs);

			virtual void _executeListener(const std::string& name, const std::string& data) TITANIUM_NOEXCEPT;
			TITANIUM_FUNCTION_DEF(_executeListener);

			protected:
#pragma warning(push)
#pragma warning(disable : 4251)
				bool loading__ { false };
				bool scalesPageToFit__ { false };
				std::shared_ptr<Titanium::Blob> data__;
				std::string url__;
				std::string html__;
				std::vector<std::string> blacklistedURLs__;
				JSValue onlink__;
#pragma warning(pop)

		};
	} // namespace UI
}  // namespace Titanium
#endif // _TITANIUM_UI_WEBVIEW_HPP_