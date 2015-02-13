/**
 * Titanium.UI.WebView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_WEBVIEW_HPP_
#define _TITANIUMWINDOWS_UI_WEBVIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class
 		  @discussion This is the Titanium.UI.WebView implementation for Windows.
		*/
// Silence 4275 about ViewBase for now. We need to merge View and ViewBase and then remove this pragma! TIMOB-18422
#pragma warning(push)
#pragma warning(disable : 4275)
		class TITANIUMWINDOWS_UI_EXPORT WebView final : public Titanium::UI::WebView, public JSExport<WebView>, public ViewBase 
		{
#pragma warning(pop)
		public:
			WebView(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~WebView();
			WebView(const WebView&)            = default;
			WebView& operator=(const WebView&) = default;
		#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WebView(WebView&&)                 = default;
			WebView& operator=(WebView&&)      = default;
		#endif

			static void JSExportInitialize();

			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT override final;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override final;
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override final;
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT override final;
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT override final;
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT override final;
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override final;

		protected:
			virtual void enableEvent(const std::string& event_name)  TITANIUM_NOEXCEPT;
			virtual	void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT;

		private:

			Titanium::UI::URL_ERROR getUrlError(const Windows::Web::WebErrorStatus status) const TITANIUM_NOEXCEPT;
			void initWebViewListeners() TITANIUM_NOEXCEPT;

			virtual std::string getHtml() const TITANIUM_NOEXCEPT override;
			virtual bool setHtml(const std::string& html, const std::unordered_map<std::string, std::string>& options) TITANIUM_NOEXCEPT override;
			virtual bool getLoading() const TITANIUM_NOEXCEPT override;
			virtual std::string getUrl() const TITANIUM_NOEXCEPT override;
			virtual bool setUrl(const std::string& url) TITANIUM_NOEXCEPT override;

			virtual bool canGoBack() TITANIUM_NOEXCEPT override;
			virtual bool canGoForward() TITANIUM_NOEXCEPT override;
			virtual void goBack() TITANIUM_NOEXCEPT override;
			virtual void goForward() TITANIUM_NOEXCEPT override;
			virtual void reload() TITANIUM_NOEXCEPT override;
			virtual void stopLoading(const bool& hardStop) TITANIUM_NOEXCEPT override;

			bool navigating__ { false };
			bool error_event_enabled__ { false };
			bool load_event_enabled__  { false };
			bool beforeload_event_enabled__  { false };

			Windows::UI::Xaml::Controls::WebView^ webview__ { nullptr };

			Windows::Foundation::EventRegistrationToken load_event__;
			Windows::Foundation::EventRegistrationToken beforeload_event__;
			Windows::Foundation::EventRegistrationToken script_event__;
		};
	} // namespace UI
}  // namespace Titanium
#endif // _TITANIUMWINDOWS_UI_WEBVIEW_HPP_
