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

using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;

namespace TitaniumWindows_UI
{
	public ref class StreamFromApplicationUriResolver sealed : public Windows::Web::IUriToStreamResolver
	{
	public:
		StreamFromApplicationUriResolver() { }
		virtual IAsyncOperation<Windows::Storage::Streams::IInputStream^>^ UriToStreamAsync(Uri^ uri)
		{
			if (uri == nullptr) {
				throw Platform::Exception::CreateException(0, "Uri should not be null");
			}

			if (TitaniumWindows::UI::WebView::LocalHostKeys->HasKey(uri->Host)) {
				const auto key = TitaniumWindows::UI::WebView::LocalHostKeys->Lookup(uri->Host);
				if (key->Equals("ms-appx://")) {
					// if host key points to uri scheme, just use the scheme and given path.
					Uri^ appDataUri = ref new Uri(key + uri->Path);
					return GetFileStreamFromApplicationUriAsync(appDataUri);
				} else {
					// host key points to the local sub folder
					Uri^ appDataUri = ref new Uri("ms-appdata:///local/" + key + uri->Path);
					return GetFileStreamFromApplicationUriAsync(appDataUri);
				}
			}

			throw Platform::Exception::CreateException(0, "Unexpected Uri");
		}

		IAsyncOperation<IInputStream^>^ GetFileStreamFromApplicationUriAsync(Uri^ uri)
		{
			return concurrency::create_async([this, uri]()->IInputStream^ {
				concurrency::task<StorageFile^> getFileTask(StorageFile::GetFileFromApplicationUriAsync(uri));
				concurrency::task<IInputStream^> getInputStreamTask = getFileTask.then([](StorageFile^ file) {
					try {
						// If this file points to HTML content, let's inject Titanium API.
						if (file->ContentType == "text/html") {
							IRandomAccessStream^ stream = ref new InMemoryRandomAccessStream();
							const auto data = ::TitaniumWindows::Utility::GetContentFromFile(file);
							const auto content = ::TitaniumWindows::Utility::ConvertUTF8String(::TitaniumWindows::UI::WebView::InjectLocalScript(std::string(data.begin(), data.end())));
							const auto writer = ref new Streams::DataWriter(stream);
							writer->WriteString(content);
							concurrency::event evt;
							concurrency::create_task(writer->StoreAsync()).then([stream, writer, &evt](concurrency::task<std::uint32_t> task) {
								try {
									task.get();
									concurrency::create_task(writer->FlushAsync()).then([&evt](concurrency::task<bool> task) {
										try {
											task.get();
										} catch (Platform::Exception^ e) {
											TITANIUM_LOG_WARN(::TitaniumWindows::Utility::ConvertString(e->Message));
										} catch (...) {
											TITANIUM_LOG_WARN("Unknown error at WebView FlushAsync");
										}
										evt.set();
									});
								} catch (Platform::Exception^ e) {
									TITANIUM_LOG_WARN(::TitaniumWindows::Utility::ConvertString(e->Message));
									evt.set();
								} catch (...) {
									TITANIUM_LOG_WARN("Unknown error at WebView StoreAsync");
									evt.set();
								}
							}, concurrency::task_continuation_context::use_arbitrary());
							evt.wait();
							writer->DetachStream();
							stream->Seek(0);
							return static_cast<IInputStream^>(stream);
						}
						IRandomAccessStream^ stream;
						concurrency::event evt;
						concurrency::create_task(file->OpenAsync(FileAccessMode::Read)).then([&evt, &stream](concurrency::task<IRandomAccessStream^> task) {
							try {
								stream = task.get();
							} catch (Platform::Exception^ e) {
								TITANIUM_LOG_WARN(::TitaniumWindows::Utility::ConvertString(e->Message));
							} catch (...) {
								TITANIUM_LOG_WARN("Unknown error at WebView OpenAsync");
							}
							evt.set();
						}, concurrency::task_continuation_context::use_arbitrary());
						evt.wait();

						return static_cast<IInputStream^>(stream);
					} catch (Platform::Exception^ e) {
						TITANIUM_LOG_WARN(::TitaniumWindows::Utility::ConvertString(e->Message));
					} catch (...) {
						TITANIUM_LOG_WARN("Unknown error at WebView GetFileFromApplicationUriAsync");
					}
					return static_cast<IInputStream^>(nullptr); // workaround of warning C4715
				});

				try {
					return getInputStreamTask.get();
				} catch (...) {
					HAL::detail::ThrowRuntimeError("TitaniumWindows::UI::WebView", "Ti.UI.WebView: Unable to read " + TitaniumWindows::Utility::ConvertString(uri->Path));
				}

				return nullptr;
			});
		}
	};
}

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::Storage;

		Windows::Foundation::Collections::IMap<::Platform::String^, ::Platform::String^>^ WebView::LocalHostKeys =
			ref new Platform::Collections::Map<Platform::String^, Platform::String^>();

		WebView::WebView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::WebView(js_context)
		{
			TITANIUM_LOG_DEBUG("WebView::ctor Initialize");
		}

		void WebView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::WebView::postCallAsConstructor(js_context, arguments);	
			
			webview__ = ref new Controls::WebView();
			streamResolver__ = ref new TitaniumWindows_UI::StreamFromApplicationUriResolver();

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

			for (const auto name : app_event_names__) {
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
				} catch (Platform::Exception^ e) {
					TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(e->Message));
				} catch (...) {
					TITANIUM_LOG_WARN("Unknown error at WebView.evalJS");
				}
			});

			// Always return empty string because WebView.InvokeScriptAsync only works with async on Windows
			return "";
		}

		/*
		 * Inject Titanium API over the local content
		 */
		std::string WebView::InjectLocalScript(const std::string& original)
		{
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

			return content;
		}

		void WebView::getInnerHTML() TITANIUM_NOEXCEPT
		{
			try {
				auto args = ref new Platform::Collections::Vector<Platform::String^>();
				args->Append("window.document.documentElement.innerHTML");

				concurrency::task<Platform::String^>(webview__->InvokeScriptAsync("eval", args)).then([this](concurrency::task<Platform::String^> task) {
					try {
						const auto result = task.get();
						if (result) {
							html__ = "<html>" + TitaniumWindows::Utility::ConvertUTF8String(result) + "</html>";
						}
					} catch (...) {
						// do nothing
					}
				});
			} catch (...) {
				// this method should not throw any exceptions
			}
		}

		void WebView::initWebViewListeners() TITANIUM_NOEXCEPT 
		{
			using namespace std::placeholders;

			load_event__ = webview__->NavigationCompleted += ref new Windows::Foundation::TypedEventHandler
				<Controls::WebView^, Controls::WebViewNavigationCompletedEventArgs^>([this](Platform::Object^ sender, Controls::WebViewNavigationCompletedEventArgs^ e) {				
				try {
					getInnerHTML();
					
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
						obj.SetProperty("url", get_context().CreateString(get_url()));
						obj.SetProperty("code", get_context().CreateString(Titanium::UI::Constants::to_string(getUrlError(e->WebErrorStatus))));
						fireEvent("error", obj);
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Erorr at WebView.load");
				}
			});
			beforeload_event__ = webview__->NavigationStarting += ref new Windows::Foundation::TypedEventHandler
				<Controls::WebView^, Controls::WebViewNavigationStartingEventArgs^>([this](Controls::WebView^, Controls::WebViewNavigationStartingEventArgs^ e) {
				try {
					if (e->Uri == nullptr) {
						return;
					}
					// blacklistedURLs
					const auto uri = TitaniumWindows::Utility::ConvertUTF8String(e->Uri->AbsoluteUri);
					const auto blacklisted = std::find(blacklistedURLs__.begin(), blacklistedURLs__.end(), uri);
					if (blacklisted != blacklistedURLs__.end()) {
						e->Cancel = true;
						JSObject obj = get_context().CreateObject();
						obj.SetProperty("url", get_context().CreateString(uri));
						fireEvent("blacklisturl", obj);
						return;
					}

					// onlink callback
					if (onlink__.IsObject()) {
						auto onlink = static_cast<JSObject>(onlink__);
						if (onlink.IsFunction()) {
							JSObject obj = get_context().CreateObject();
							obj.SetProperty("url", get_context().CreateString(uri));
							const std::vector<JSValue> args{ obj };
							const auto result = onlink(args, get_object());
							if (result.IsBoolean() && static_cast<bool>(result) == false) {
								e->Cancel = true;
								return;
							}
						}
					}

					loading__ = true;
					if (beforeload_event_enabled__) {
						JSObject obj = get_context().CreateObject();
						obj.SetProperty("url", get_context().CreateString(get_url()));
						fireEvent("beforeload", obj);
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Erorr at WebView.beforeload");
				}
			});

			script_event__ = webview__->ScriptNotify += ref new Controls::NotifyEventHandler([this](Platform::Object^ sender, Controls::NotifyEventArgs^ e) {
				try {
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
					} else if (command == "Ti.App.addEventListener" && app_event_names__.find(arg1) == app_event_names__.end()) {
						const auto app = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App"));
						auto func = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App.addEventListener"));
						std::vector<JSValue> args = { ctx.CreateString(arg1), get_object().GetProperty("_executeListener") };
						func(args, app);
						app_event_names__.emplace(arg1);
					} else if (command == "Ti.App.removeEventListener") {
						const auto app = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App"));
						auto func = static_cast<JSObject>(ctx.JSEvaluateScript("Ti.App.removeEventListener"));
						std::vector<JSValue> args = { ctx.CreateString(arg1), get_object().GetProperty("_executeListener") };
						func(args, app);
					}
				} catch (Platform::Exception^ ex) {
					TITANIUM_LOG_WARN("Error at WebView script: ", TitaniumWindows::Utility::ConvertString(ex->Message));
				} catch (...) {
					TITANIUM_LOG_WARN("Error at WebView script");
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
			webview__->NavigateToString(TitaniumWindows::Utility::ConvertUTF8String(InjectLocalScript(html)));
		}

		std::string WebView::get_url() const TITANIUM_NOEXCEPT
		{
			if (webview__ && webview__->Source != nullptr) {
				return TitaniumWindows::Utility::ConvertUTF8String(webview__->Source->ToString());
			} else {
				return "";
			}
		}

		void WebView::set_url(const std::string& url) TITANIUM_NOEXCEPT
		{
			Titanium::UI::WebView::set_url(url);

			const auto uri = TitaniumWindows::Utility::GetUriFromPath(url);
			const auto scheme = uri->SchemeName;

			if (scheme->Equals("ms-appdata")) {
				// Save host name for ms-local-stream.
				// Local content should be stored in /local/SUBFOLDER/actual_content,
				// and the host name for ms-local-stream will be built based on this SUBFOLDER. (ms-local-stream:://SUBFOLDER_KEY/actual_content).
				// So save the mapping here since there's no way to get SUBFOLDER string from SUBFOLDER_KEY.
				const auto fullpath = TitaniumWindows::Utility::ConvertString(uri->Path);
				if (fullpath.find_first_of("/local/") == 0) {
					const auto offset = fullpath.find_first_of("/", 7);
					if (offset != std::string::npos) {
						const auto hostname = TitaniumWindows::Utility::ConvertString(fullpath.substr(7, offset - 7));
						const auto path = TitaniumWindows::Utility::ConvertString(fullpath.substr(offset));
						const auto streamuri = webview__->BuildLocalStreamUri(hostname, path);
						WebView::LocalHostKeys->Insert(streamuri->Host, hostname);
						webview__->NavigateToLocalStreamUri(streamuri, streamResolver__);
						return;
					}
				}
				HAL::detail::ThrowRuntimeError("TitaniumWindows::UI::WebView", "Ti.UI.WebView: Unable to load file content");
			} else if (scheme->Equals("ms-appx") || scheme->Equals("ms-appx-web")) {
				// Use ms-local-stream for applicaiton resource too. In this case we use scheme name for host key
				const auto streamuri = webview__->BuildLocalStreamUri("ms-appx://", uri->Path);
				WebView::LocalHostKeys->Insert(streamuri->Host, "ms-appx://");
				webview__->NavigateToLocalStreamUri(streamuri, streamResolver__);
				return;
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
