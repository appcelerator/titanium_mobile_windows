/**
 * Titanium.UI.WebView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_WEBVIEW_HPP_
#define _TITANIUMWINDOWS_UI_WEBVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/WebView.hpp"
#include <unordered_set>
#include <collection.h>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class WebView
		  @ingroup Titanium.UI.WebView
 		  @discussion This is the Titanium.UI.WebView implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT WebView final : public Titanium::UI::WebView, public JSExport<WebView>
		{
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(data);
			TITANIUM_PROPERTY_UNIMPLEMENTED(scalesPageToFit);
			TITANIUM_FUNCTION_UNIMPLEMENTED(setBasicAuthentication);

			WebView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~WebView();
			WebView(const WebView&)            = default;
			WebView& operator=(const WebView&) = default;
		#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WebView(WebView&&)                 = default;
			WebView& operator=(WebView&&)      = default;
		#endif

			static void JSExportInitialize();
			static Windows::Foundation::Collections::IMap<::Platform::String^, ::Platform::String^>^ LocalHostKeys;
			static std::string InjectLocalScript(const std::string& content);

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual std::string evalJS(const std::string& code, JSObject& callback) TITANIUM_NOEXCEPT override;

			virtual void _executeListener(const std::string& name, const std::string& data) TITANIUM_NOEXCEPT override;

		protected:
			virtual void enableEvent(const std::string& event_name)  TITANIUM_NOEXCEPT;
			virtual	void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT;

			Titanium::UI::URL_ERROR getUrlError(const Windows::Web::WebErrorStatus status) const TITANIUM_NOEXCEPT;
			void initWebViewListeners() TITANIUM_NOEXCEPT;

			virtual void set_html(const std::string& html) TITANIUM_NOEXCEPT override;
			virtual std::string get_url() const TITANIUM_NOEXCEPT override;
			virtual void set_url(const std::string& url) TITANIUM_NOEXCEPT override;
			virtual bool setHtml(const std::string& html, const std::unordered_map<std::string, std::string>& options) TITANIUM_NOEXCEPT override;

			virtual bool canGoBack() TITANIUM_NOEXCEPT override;
			virtual bool canGoForward() TITANIUM_NOEXCEPT override;
			virtual void goBack() TITANIUM_NOEXCEPT override;
			virtual void goForward() TITANIUM_NOEXCEPT override;
			virtual void reload() TITANIUM_NOEXCEPT override;
			virtual void stopLoading(const bool& hardStop) TITANIUM_NOEXCEPT override;

			void getInnerHTML() TITANIUM_NOEXCEPT;
			void handleBaseURL() TITANIUM_NOEXCEPT;

			bool error_event_enabled__ { false };
			bool load_event_enabled__  { false };
			bool beforeload_event_enabled__  { false };

			bool baseURL_loading__{ false };

			Windows::UI::Xaml::Controls::WebView^ webview__ { nullptr };

			Windows::Foundation::EventRegistrationToken load_event__;
			Windows::Foundation::EventRegistrationToken beforeload_event__;
			Windows::Foundation::EventRegistrationToken script_event__;

			Windows::Web::IUriToStreamResolver^ streamResolver__;
#pragma warning(push)
#pragma warning(disable : 4251)
			std::unordered_set<std::string> app_event_names__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium
#endif // _TITANIUMWINDOWS_UI_WEBVIEW_HPP_
