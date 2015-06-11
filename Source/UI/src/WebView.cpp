/**
 * Titanium.UI.WebView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/WebView.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		WebView::WebView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::WebView(js_context)
		{
			TITANIUM_LOG_DEBUG("WebView::ctor Initialize");
		}

		void WebView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::WebView::postCallAsConstructor(js_context, arguments);	
			
			webview__ = ref new Windows::UI::Xaml::Controls::WebView();
			initWebViewListeners();

			Titanium::UI::WebView::setLayoutDelegate<WindowsViewLayoutDelegate>();

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(webview__);
		}

		WebView::~WebView() 
		{
			
		}

		void WebView::JSExportInitialize() 
		{
			JSExport<WebView>::SetClassVersion(1);
			JSExport<WebView>::SetParent(JSExport<Titanium::UI::WebView>::Class());
		}

		Titanium::UI::URL_ERROR WebView::getUrlError(const Windows::Web::WebErrorStatus status) const TITANIUM_NOEXCEPT
		{
			using namespace Windows::Web;
			if (status == WebErrorStatus::Unauthorized) {
				return Titanium::UI::URL_ERROR::AUTHENTICATION;
			} else if (status == WebErrorStatus::Timeout || status == WebErrorStatus::RequestTimeout || status == WebErrorStatus::GatewayTimeout) {
				return Titanium::UI::URL_ERROR::TIMEOUT;
			} else if (status == WebErrorStatus::CertificateCommonNameIsIncorrect || status == WebErrorStatus::CertificateContainsErrors || status == WebErrorStatus::CertificateExpired || status == WebErrorStatus::CertificateIsInvalid || status == WebErrorStatus::CertificateRevoked) {
				return Titanium::UI::URL_ERROR::SSL_FAILED;
			} else if (status == WebErrorStatus::RequestUriTooLong) {
				return Titanium::UI::URL_ERROR::BAD_URL;
			} else if (status == WebErrorStatus::CannotConnect || status == WebErrorStatus::ConnectionAborted || status == WebErrorStatus::ConnectionReset || status == WebErrorStatus::ConnectionReset) {
				return Titanium::UI::URL_ERROR::CONNECT;
			} else if (status == WebErrorStatus::NotFound) {
				return Titanium::UI::URL_ERROR::FILE_NOT_FOUND;
			} else if (status == WebErrorStatus::HostNameNotResolved) {
				return Titanium::UI::URL_ERROR::HOST_LOOKUP;
			} 
			return Titanium::UI::URL_ERROR::UNKNOWN;
		}

		void WebView::initWebViewListeners() TITANIUM_NOEXCEPT 
		{
			using namespace std::placeholders;
			using namespace Windows::UI::Xaml::Controls;

			load_event__ = webview__->NavigationCompleted += ref new Windows::Foundation::TypedEventHandler
				<Windows::UI::Xaml::Controls::WebView^, WebViewNavigationCompletedEventArgs^>([this](Platform::Object^ sender, WebViewNavigationCompletedEventArgs^ e) {
				loading__ = false;
				if (e->IsSuccess && load_event_enabled__) {
					JSObject obj = get_context().CreateObject();
					if (webview__->Source != nullptr) {
						obj.SetProperty("url", get_context().CreateString(TitaniumWindows::Utility::ConvertString(webview__->Source->ToString())));
					}
					fireEvent("load", obj);
				} else if (!e->IsSuccess && error_event_enabled__) {
					JSObject obj = get_context().CreateObject();
					obj.SetProperty("success", get_context().CreateBoolean(false));
					obj.SetProperty("url",  get_context().CreateString(get_url()));
					obj.SetProperty("code", get_context().CreateString(Titanium::UI::Constants::to_string(getUrlError(e->WebErrorStatus))));
					fireEvent("error", obj);
				}
			});

			beforeload_event__ = webview__->NavigationStarting += ref new Windows::Foundation::TypedEventHandler
				<Windows::UI::Xaml::Controls::WebView^, WebViewNavigationStartingEventArgs^>([this](Platform::Object^ sender, WebViewNavigationStartingEventArgs^ e) {
				loading__ = true;
				if (beforeload_event_enabled__) {
					JSObject obj = get_context().CreateObject();
					obj.SetProperty("url",  get_context().CreateString(get_url()));
					fireEvent("beforeload", obj);
				}
			});

			script_event__ = webview__->ScriptNotify += ref new NotifyEventHandler([this](Platform::Object^ sender, Windows::UI::Xaml::Controls::NotifyEventArgs^ e) {
				const auto value = TitaniumWindows::Utility::ConvertString(e->Value);
				std::vector<std::string> args;
	#pragma warning(push)
	#pragma warning(disable:4996)
				boost::split(args, value, boost::is_any_of(","));
	#pragma warning(pop)

				// we need at least 3 arguments
				if (args.size() < 3) {
					return;
				}

				// notify command
				const auto command = args.at(0);
				// first argument
				const auto arg1    = args.at(1);
				// rest of arguments
				const auto arg2    = value.substr(command.length() + arg1.length() + 2);

				if (command == "log") {
					const auto script = (boost::format("Ti.API.log('%1%', '%2%');\r\n") % arg1 % arg2).str();
					get_context().JSEvaluateScript(script);
				} else if (command == "event") {
					// Event execution shortcut: let's do just like the way Ti Blackberry does for now
					const auto script = (boost::format("Ti.App.fireEvent('%1%', %2%);\r\n") % arg1 % arg2).str();
					get_context().JSEvaluateScript(script);
				}
			});

		}

		void WebView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::WebView::enableEvent(event_name);

			if (event_name == "load") {
				load_event_enabled__ = true;
			} else if (event_name == "beforeload") {
				beforeload_event_enabled__ = true;
			} else if (event_name == "error") {
				error_event_enabled__ = true;
			}
		}

		void WebView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::WebView::disableEvent(event_name);
			
			if (event_name == "load") {
				load_event_enabled__ = false;
			} else if (event_name == "beforeload") {
				beforeload_event_enabled__ = false;
			} else if (event_name == "error") {
				error_event_enabled__ = false;
			}
		}

		bool WebView::setHtml(const std::string& html, const std::unordered_map<std::string, std::string>& options) TITANIUM_NOEXCEPT
		{
			webview__->NavigateToString(TitaniumWindows::Utility::ConvertUTF8String(html));
			return true;
		}

		std::string WebView::get_url() const TITANIUM_NOEXCEPT
		{
			if (webview__->Source != nullptr) {
				return TitaniumWindows::Utility::ConvertUTF8String(webview__->Source->ToString());
			} else {
				return "";
			}
		}

		void WebView::set_url(const std::string& url) TITANIUM_NOEXCEPT
		{
			webview__->Navigate(ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertUTF8String(url)));
		}

		bool WebView::canGoBack() TITANIUM_NOEXCEPT
		{
			return webview__->CanGoBack;
		}

		bool WebView::canGoForward() TITANIUM_NOEXCEPT
		{
			return webview__->CanGoForward;
		}

		void WebView::goBack() TITANIUM_NOEXCEPT
		{
			if (canGoBack()) {
				webview__->GoBack();
			}
		}

		void WebView::goForward() TITANIUM_NOEXCEPT
		{
			if (canGoForward()) {
				webview__->GoForward();
			}
		}

		void WebView::reload() TITANIUM_NOEXCEPT
		{
			webview__->Refresh();
		}

		void WebView::stopLoading(const bool& hardStop) TITANIUM_NOEXCEPT
		{
			webview__->Stop();
		}

	} // namespace UI
}  // namespace Titanium
