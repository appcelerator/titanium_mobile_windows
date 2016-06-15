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
#include <collection.h>
#include <ppltasks.h>
#include <concrt.h>
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "Titanium/UI/webview_js.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::Storage;

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
			// Make sure to remove all listeners of Ti.App for this WebView
			const auto ctx = get_context();
			const auto app = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App"));
			const auto callback = get_object().GetProperty("_executeListener");
			auto func = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App.removeEventListener"));

			for (const auto name : app_event_names) {
				std::vector<JSValue> args = { ctx.CreateString(name), callback };
				func(args, app);
			}
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

		std::string WebView::evalJS(const std::string& code, JSObject& callback) TITANIUM_NOEXCEPT
		{
			auto args = ref new Platform::Collections::Vector<Platform::String^>();
			args->Append(TitaniumWindows::Utility::ConvertUTF8String(code));

			concurrency::task<Platform::String^>(webview__->InvokeScriptAsync("eval", args)).then([this, callback](concurrency::task<Platform::String^> task){
				try {
					const auto result = task.get();
					if (callback.IsFunction()) {
						std::vector<JSValue> args = { get_context().CreateString(TitaniumWindows::Utility::ConvertUTF8String(result)) };
						static_cast<JSObject>(callback)(args, get_object());
					}
				} catch (Platform::COMException^ e) {
					TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(e->Message));
				}
			});

			// Always return empty string because WebView.InvokeScriptAsync only works with async on Windows
			return "";
		}

		/*
		 * Inject Titanium API over the local content
		 */
		void WebView::navigateWithLocalScript(const std::string& original)
		{
			localscript_navigating__ = true;

			std::string content = original;

			// common script for WebView-Titanium binding
			const std::string inject_script = webview_js;

			// In WebView content, we use Ti.App.notifyEvent to point to the platform-specific notify function
			const std::string windows_bind = ("Ti.App.notifyEvent = function(msg) { window.external.notify(msg); }; ");

			// attempt to inject in Titanium API bridge code
			// However, we do this only when content looks like HTML 
			const auto found = content.find_first_of("<html");
			if (found != std::string::npos) {
				const auto start = content.find_first_of(">", found);
				if (start != std::string::npos) {
					content.insert(start + 1, "<script id='__ti_injection'>" + inject_script + windows_bind + "</script>");
				}
			}

			webview__->NavigateToString(TitaniumWindows::Utility::ConvertUTF8String(content));
		}

		void WebView::initWebViewListeners() TITANIUM_NOEXCEPT 
		{
			using namespace std::placeholders;
			using namespace Windows::UI::Xaml::Controls;

			load_event__ = webview__->NavigationCompleted += ref new Windows::Foundation::TypedEventHandler
				<Windows::UI::Xaml::Controls::WebView^, WebViewNavigationCompletedEventArgs^>([this](Platform::Object^ sender, WebViewNavigationCompletedEventArgs^ e) {				
				localscript_navigating__ = false;
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
				// This means user navigates to local content via hyperlink
				if (!localscript_navigating__ && isLocalUri(e->Uri)) {
					e->Cancel = true;
					set_url(TitaniumWindows::Utility::ConvertString(e->Uri->AbsoluteUri));
					return;
				}

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
				const auto arg1 = args.at(1);
				// rest of arguments
				const auto arg2 = value.substr(command.length() + arg1.length() + 2);

				const auto ctx = get_context();

				// Invoke Titanium functions with explicit "this". 
				// May be safer than building scripts by just concatinating strings.
				if (command == "Ti.API.log") {
					const auto api = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.API"));
					auto func = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.API.log"));
					std::vector<JSValue> args = { ctx.CreateString(arg1), ctx.CreateString(arg2) };
					func(args, api);
				} else if (command == "Ti.App.fireEvent") {
					const auto app = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App"));
					auto func = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App.fireEvent"));
					std::vector<JSValue> args = { ctx.CreateString(arg1), ctx.CreateValueFromJSON(arg2) };
					func(args, app);
				} else if (command == "Ti.App.addEventListener" && app_event_names.find(arg1) == app_event_names.end()) {
					const auto app = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App"));
					auto func = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App.addEventListener"));
					std::vector<JSValue> args = { ctx.CreateString(arg1), get_object().GetProperty("_executeListener") };
					func(args, app);
					app_event_names.emplace(arg1);
				} else if (command == "Ti.App.removeEventListener") {
					const auto app = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App"));
					auto func = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App.removeEventListener"));
					std::vector<JSValue> args = { ctx.CreateString(arg1), get_object().GetProperty("_executeListener") };
					func(args, app);
				}
			});
		}

		void WebView::_executeListener(const std::string& name, const std::string& data) TITANIUM_NOEXCEPT
		{
			const auto script = (boost::format("Ti.App.executeListeners('%1%', %2%);") % name % data).str();
			evalJS(script, get_context().CreateObject());
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

		void WebView::set_html(const std::string& html) TITANIUM_NOEXCEPT
		{
			navigateWithLocalScript(html);
		}

		bool WebView::isLocalUri(Windows::Foundation::Uri^ uri) const TITANIUM_NOEXCEPT
		{
			const auto scheme = uri->SchemeName;
			return (scheme == "ms-appx" || scheme == "ms-appdata" || scheme == "ms-appx-web");
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
			Titanium::UI::WebView::set_url(url);

			const auto uri = TitaniumWindows::Utility::GetUriFromPath(boost::algorithm::replace_first_copy(url, "ms-appx-web://", "ms-appx://"));

			if (isLocalUri(uri)) {
				Windows::Storage::StorageFile^ file = nullptr;
				concurrency::event event;
				concurrency::task<StorageFile^>(StorageFile::GetFileFromApplicationUriAsync(uri)).then([&file, &event](concurrency::task<StorageFile^> task) {
					try {
						file = task.get();
					} catch (Platform::COMException^ ex) {
						file = nullptr;
					}
					event.set();
				}, concurrency::task_continuation_context::use_arbitrary());
				event.wait();

				if (file != nullptr) {
					const auto content = TitaniumWindows::Utility::GetContentFromFile(file);
					navigateWithLocalScript(std::string(content.begin(), content.end()));
				} else {
					HAL::detail::ThrowRuntimeError("TitaniumWindows::UI::WebView", "Ti.UI.WebView: Unable to load file content");
				}
			} else {
				webview__->Navigate(uri);
			}
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
