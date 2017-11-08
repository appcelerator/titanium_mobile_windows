/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include <windows.h>
#include "TitaniumWindows/Network/HTTPClient.hpp"
#include "Titanium/detail/TiLogger.hpp"

#include <collection.h>
#include <ppl.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

using namespace concurrency;
using TitaniumWindows::Utility::RunOnUIThread;

#if defined(IS_WINDOWS_10)
#define CONTINUATION_CONTEXT task_continuation_context::use_synchronous_execution
#else
#define CONTINUATION_CONTEXT task_continuation_context::use_arbitrary
#endif

namespace TitaniumWindows
{
	namespace Network
	{
		HTTPClient::HTTPClient(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::Network::HTTPClient(js_context)
		    , cancellationTokenSource__(concurrency::cancellation_token_source())
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Network::HTTPClient::ctor");
		}

		HTTPClient::~HTTPClient()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Network::HTTPClient::dtor");

			filter__ = nullptr;
			httpClient__ = nullptr;
			dispatcherTimer__ = nullptr;
		}

		void HTTPClient::JSExportInitialize()
		{
			JSExport<HTTPClient>::SetClassVersion(1);
			JSExport<HTTPClient>::SetParent(JSExport<Titanium::Network::HTTPClient>::Class());
		}

		void HTTPClient::abort() TITANIUM_NOEXCEPT
		{
			cancellationTokenSource__.cancel();

			if (dispatcherTimer__ != nullptr && dispatcherTimer__->IsEnabled) {
				dispatcherTimer__->Stop();
			}
		}

		void HTTPClient::clearCookies(const std::string& location) TITANIUM_NOEXCEPT
		{
			auto filter = ref new Windows::Web::Http::Filters::HttpBaseProtocolFilter();

			Windows::Foundation::Uri ^ uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString(location));
			auto cookieCollection = filter->CookieManager->GetCookies(uri);

			Windows::Foundation::Collections::IIterator<Windows::Web::Http::HttpCookie^>^ iterator = cookieCollection->First();
			while (iterator->HasCurrent) {
				Windows::Web::Http::HttpCookie ^ cookie = iterator->Current;
				filter->CookieManager->DeleteCookie(cookie);
			}
		}

		std::string HTTPClient::getResponseHeader(const std::string& name) TITANIUM_NOEXCEPT
		{
			auto it = responseHeaders__.find(name.c_str());
			if (it != responseHeaders__.end()) {
				return it->second;
			} else {
				return "";
			}
		}

		void HTTPClient::open(const std::string& method, const std::string& location) TITANIUM_NOEXCEPT
		{
			method__ = Titanium::Network::RequestMethod::Get;
			if (method == "DELETE") {
				method__ = Titanium::Network::RequestMethod::Delete;
			} else if (method == "POST") {
				method__ = Titanium::Network::RequestMethod::Post;
			} else if (method == "PUT") {
				method__ = Titanium::Network::RequestMethod::Put;
			} else if (method == "HEAD") {
				method__ = Titanium::Network::RequestMethod::Head;
			} else if (method == "PATCH") {
				method__ = Titanium::Network::RequestMethod::Patch;
			} else if (method == "OPTIONS") {
				method__ = Titanium::Network::RequestMethod::Options;
			}

			responseData__.clear();
			responseDataLen__ = 0;

			location__ = location;
			filter__ = ref new Windows::Web::Http::Filters::HttpBaseProtocolFilter();
			httpClient__ = ref new Windows::Web::Http::HttpClient(filter__);
			cancellationTokenSource__ = concurrency::cancellation_token_source();
			filter__->AllowAutoRedirect = true;
			filter__->CacheControl->ReadBehavior = Windows::Web::Http::Filters::HttpCacheReadBehavior::MostRecent;

			if (!username__.empty()) {
				filter__->ServerCredential = ref new Windows::Security::Credentials::PasswordCredential(
					TitaniumWindows::Utility::ConvertString(location__),
					TitaniumWindows::Utility::ConvertString(username__),
					TitaniumWindows::Utility::ConvertString(password__));
			}

			addCookiesToRequest();

			auto user_agent = get_context().JSEvaluateScript("Ti.userAgent");
			setRequestHeader("User-Agent", static_cast<std::string>(user_agent));
		}

		void HTTPClient::send() TITANIUM_NOEXCEPT
		{
			Windows::Web::Http::IHttpContent^ postData;
			send(postData);
		}

		void HTTPClient::send(const std::map<std::string, JSValue>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT
		{
			Windows::Web::Http::IHttpContent^ postData;
			if (useMultipartForm) {
				postData = ref new Windows::Web::Http::HttpMultipartFormDataContent();

				for (auto pair : postDataPairs) {
					Platform::String^ name = TitaniumWindows::Utility::ConvertUTF8String(pair.first);
					const auto value = pair.second;
					if (value.IsObject()) {
						auto blob_ptr = static_cast<JSObject>(value).GetPrivate<Titanium::Blob>();
						if (blob_ptr != nullptr) {
							Windows::Web::Http::HttpBufferContent^ fileContent = ref new Windows::Web::Http::HttpBufferContent(charVecToBuffer(blob_ptr->getData()));
							const auto mimeType = blob_ptr->get_mimeType();
							if (!mimeType.empty()) {
								fileContent->Headers->ContentType = ref new Windows::Web::Http::Headers::HttpMediaTypeHeaderValue(TitaniumWindows::Utility::ConvertString(mimeType));
							}
							// Adding last arg (filename) makes it get treated as a file attachment like on Android
							std::string fileName = "unknown.tmp";
							const auto path = blob_ptr->get_nativePath();
							if (!path.empty()) {
								// grab last segment of path to use as filename!
								auto separator = path.find_last_of("\\");
								if (separator == std::string::npos) {
									fileName = path;
								}
								else {
									fileName = path.substr(separator + 1);
								}
							}
							else {
								// TODO Assume file extension by mime type?
							}
							static_cast<Windows::Web::Http::HttpMultipartFormDataContent^>(postData)->Add(fileContent, name, TitaniumWindows::Utility::ConvertUTF8String(fileName));
							continue;
						}
					}

					// Assume string
					std::string str = static_cast<std::string>(value);
					Platform::String^ converted = TitaniumWindows::Utility::ConvertUTF8String(str);
					static_cast<Windows::Web::Http::HttpMultipartFormDataContent^>(postData)->Add(ref new Windows::Web::Http::HttpStringContent(converted), name);
				}
			} else {
				auto keyValues = ref new Platform::Collections::Map<Platform::String^, Platform::String^>();
				for (auto pair : postDataPairs) {
					Platform::String^ name = TitaniumWindows::Utility::ConvertUTF8String(pair.first);
					Platform::String^ value = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(pair.second));
					keyValues->Insert(name, value);
				}

				postData = ref new Windows::Web::Http::HttpFormUrlEncodedContent(keyValues);
			}
			send(postData);
		}

		void HTTPClient::send(const std::string& postDataStr) TITANIUM_NOEXCEPT
		{
			Windows::Web::Http::IHttpContent^ postData = ref new Windows::Web::Http::HttpStringContent(TitaniumWindows::Utility::ConvertUTF8String(postDataStr));
			send(postData);
		}

		void HTTPClient::send(Windows::Web::Http::IHttpContent^ content)
		{
			auto uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString(location__));
			
			// Set up the request
			Windows::Web::Http::HttpRequestMessage^ request;
			if (method__ == Titanium::Network::RequestMethod::Post) {
				request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Post, uri);
				request->Content = content;
			} else if (method__ == Titanium::Network::RequestMethod::Put) {
				request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Put, uri);
				request->Content = content;
			} else if (method__ == Titanium::Network::RequestMethod::Delete) {
				request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Delete, uri);
			} else if (method__ == Titanium::Network::RequestMethod::Patch) {
				request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Patch, uri);
				request->Content = content;
			} else if (method__ == Titanium::Network::RequestMethod::Options) {
				request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Options, uri);
			} else if (method__ == Titanium::Network::RequestMethod::Head) {
				request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Head, uri);
			} else {
				request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Get, uri);
			}
			setRequestHeaders(request);

			auto operation = httpClient__->SendRequestAsync(request);

			// Startup a timer that will abort the request after the timeout period is reached.
			startDispatcherTimer();
			responseWaiter__.reset();

			// clang-format off
			const auto token = cancellationTokenSource__.get_token();
			create_task(operation, token)
				.then([this, token](Windows::Web::Http::HttpResponseMessage^ response) {
				interruption_point();
				readyState__ = Titanium::Network::RequestState::Opened;
				onreadystatechange(readyState__);

				SerializeHeaders(response);

				return create_task(response->Content->ReadAsInputStreamAsync(), token);
			}, CONTINUATION_CONTEXT())
				.then([this, token](Windows::Storage::Streams::IInputStream^ stream) {
				interruption_point();

				readyState__ = Titanium::Network::RequestState::Loading;
				onreadystatechange(readyState__);
				// FIXME Fire ondatastream/onsendstream callbacks throughout!

				return HTTPResultAsync(stream, token);
			}, CONTINUATION_CONTEXT())
				.then([this](task<Windows::Storage::Streams::IBuffer^> previousTask) {
				try {
					readyState__ = Titanium::Network::RequestState::Done;
					responseWaiter__.set();

					// Check if any previous task threw an exception.
					previousTask.get();

					if (!disposed__ && httpClient__) {
						onreadystatechange(readyState__);

						// Fire onerror only if there's an onerror handler registered and status code is 400-599.
						// Otherwise fire onload (so 400-599 fall back to onload if no onerror handler)
						if (onerror__ && onerror__.IsObject() && static_cast<JSObject>(onerror__).IsFunction() && status__ >= 400 && status__ <= 599) {
							RunOnUIThread([=]() {
								onerror(status__, "HTTP Error", false);
							});
       					} else {
							RunOnUIThread([this]() {
								onload(0, "Response has been loaded.", true);
							});
       					}

						onsendstream(1.0);
						ondatastream(1.0);
					}
				} catch (const task_canceled&) {
					if (!disposed__ && httpClient__) {
						RunOnUIThread([=]() {
							onerror(-1, "Session Cancelled", false);
						});
					}
				} catch (Platform::Exception^ ex) {
					if (!disposed__ && httpClient__) {
						RunOnUIThread([=]() {
							std::string error(TitaniumWindows::Utility::ConvertString(ex->Message));
							onerror(ex->HResult, error, false);
						});
					}
				} catch (const std::exception& e) {
					if (!disposed__ && httpClient__) {
						RunOnUIThread([=]() {
							std::string error(e.what());
							onerror(-1, error, false);
						});
					}
				} catch (...) {
					if (!disposed__ && httpClient__) {
						RunOnUIThread([=]() {
							onerror(-1, "Unknown error", false);
						});
					}
				}
			}, CONTINUATION_CONTEXT());
			// clang-format on
		}

		void HTTPClient::setRequestHeader(const std::string& key, const std::string& value) TITANIUM_NOEXCEPT
		{
			auto it = requestHeaders__.find(key);
			if (it != requestHeaders__.end()) {
				requestHeaders__.erase(it);
			}

			requestHeaders__.insert(std::make_pair(key, value));
		}

		// properties
		std::string HTTPClient::get_allResponseHeaders() const TITANIUM_NOEXCEPT
		{
			std::stringstream s_stream;
			for (auto it = responseHeaders__.begin(); it != responseHeaders__.end(); ++it) {
				s_stream << it->first.c_str() << ":" << it->second.c_str() << ";";
			}

			return s_stream.str();
		}

		void HTTPClient::set_timeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT
		{
			std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = timeout;
			timeoutSpan__.Duration = timer_interval_ticks.count();
		}

		// Native
		void HTTPClient::setRequestHeaders(Windows::Web::Http::HttpRequestMessage^ request)
		{
			// Set the default headers:
			// X-Titanium-Id
			auto app_guid = get_context().JSEvaluateScript("Ti.App.guid");
			request->Headers->Append("X-Titanium-Id", TitaniumWindows::Utility::ConvertString(static_cast<std::string>(app_guid)));

			// Set type safe headers. Content-Type is the most popular may need to set others.
			auto it = requestHeaders__.find("Content-Type");
			if (it != requestHeaders__.end()) {
				if (request->Content) {
					request->Content->Headers->ContentType =
						ref new Windows::Web::Http::Headers::HttpMediaTypeHeaderValue(TitaniumWindows::Utility::ConvertString(it->second));
				}
				requestHeaders__.erase(it);
			}
			// User Agent
			it = requestHeaders__.find("User-Agent");
			if (it != requestHeaders__.end()) {
				request->Headers->UserAgent->TryParseAdd(TitaniumWindows::Utility::ConvertString(it->second));
				requestHeaders__.erase(it);
			}

			for (it = requestHeaders__.begin(); it != requestHeaders__.end(); ++it) {
				auto key = TitaniumWindows::Utility::ConvertString(it->first);
				// ignore cookies they are added during open to the request filter.
				if (!key->Equals("Cookie")) {
					auto value = it->second;
					if (!value.empty()) {
						request->Headers->Append(key, TitaniumWindows::Utility::ConvertString(value));
					} else {
						if (request->Headers->HasKey(key)) {
							request->Headers->Remove(key);
						}
					}
				}
			}
		}

		task<Windows::Storage::Streams::IBuffer^> HTTPClient::HTTPResultAsync(Windows::Storage::Streams::IInputStream^ stream, concurrency::cancellation_token token)
		{
			Windows::Storage::Streams::IBuffer^ responseBuffer = ref new Windows::Storage::Streams::Buffer(1000); // Default size from MS samples
			// clang-format off
			return create_task(stream->ReadAsync(responseBuffer, responseBuffer->Capacity, Windows::Storage::Streams::InputStreamOptions::Partial), token)
				.then([=](task<Windows::Storage::Streams::IBuffer^> readTask) {

				if (token.is_canceled()) {
					cancel_current_task();
				}

				// Stop the timeout timer
				if (dispatcherTimer__ != nullptr && httpClient__ != nullptr) {
					RunOnUIThread([=] {
						dispatcherTimer__->Stop();
					});
				}

				if (contentLength__ != -1 && contentLength__ != 0) {
					ondatastream(responseBuffer->Length / contentLength__);
				} else {
					ondatastream(-1.0); // chunked encoding was used
				}

				if (responseBuffer->Length) {
					auto reader = ::Windows::Storage::Streams::DataReader::FromBuffer(responseBuffer);
					responseData__.resize(responseDataLen__ + responseBuffer->Length);
					reader->ReadBytes(
						::Platform::ArrayReference<std::uint8_t>(
						&responseData__[responseDataLen__], responseBuffer->Length));
					responseDataLen__ += responseBuffer->Length;
				}
				
				// FIXME How do we pass the token on in case of readTask?
				return responseBuffer->Length ? HTTPResultAsync(stream, token) : readTask;
			});
			// clang-format on
		}

		void HTTPClient::startDispatcherTimer()
		{
			RunOnUIThread([=] {
				if (dispatcherTimer__ == nullptr && timeoutSpan__.Duration > 0) {
					dispatcherTimer__ = ref new Windows::UI::Xaml::DispatcherTimer();
					dispatcherTimer__->Interval = timeoutSpan__;
					auto timeoutRegistrationToken__ = dispatcherTimer__->Tick += ref new Windows::Foundation::EventHandler<Platform::Object^>([this](Platform::Object^ sender, Platform::Object^ e) {
						try {
							responseWaiter__.set();
							cancellationTokenSource__.cancel();
							dispatcherTimer__->Stop();
							// re-create the CancellationTokenSource.
							cancellationTokenSource__ = cancellation_token_source();
						} catch (...) {
							TITANIUM_LOG_WARN("Error while HTTPClient::startDispatcherTimer");
						}
					});
					dispatcherTimer__->Start();
				}
			});
		}

		Windows::Storage::Streams::IBuffer^ HTTPClient::charVecToBuffer(std::vector<std::uint8_t> char_vector)
		{
			using namespace Windows::Storage;
			int size = char_vector.size();
			const auto writer = ref new Streams::DataWriter(ref new Streams::InMemoryRandomAccessStream());
			writer->WriteBytes(::Platform::ArrayReference<std::uint8_t>(&char_vector[0], size));
			return writer->DetachBuffer();
		}

		void HTTPClient::SerializeHeaders(Windows::Web::Http::HttpResponseMessage^ response)
		{
			status__ = static_cast<std::uint32_t>(response->StatusCode);

			SerializeHeaderCollection(response->Headers);
			SerializeHeaderCollection(response->Content->Headers);

			std::map<std::string, std::string>::iterator it;
			it = responseHeaders__.find("Content-Length");
			if (it != responseHeaders__.end()) {
				contentLength__ = atol(it->second.c_str());
			} else {
				contentLength__ = -1;  // chunked encoding
			}

			readyState__ = Titanium::Network::RequestState::Headers_Received;
			onreadystatechange(Titanium::Network::RequestState::Headers_Received);
		}

		void HTTPClient::SerializeHeaderCollection(Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<Platform::String^, Platform::String^>^>^ headers)
		{
			for each(Windows::Foundation::Collections::IKeyValuePair<Platform::String^, Platform::String^>^ pair in headers)
			{
				responseHeaders__.insert(std::make_pair(TitaniumWindows::Utility::ConvertString(pair->Key), TitaniumWindows::Utility::ConvertString(pair->Value)));
			}
		}

		void HTTPClient::addCookiesToRequest()
		{
			auto location = TitaniumWindows::Utility::ConvertString(location__);

			for (auto it = requestHeaders__.begin(); it != requestHeaders__.end(); ++it) {
				
				auto key   = TitaniumWindows::Utility::ConvertString(it->first);
				auto value = TitaniumWindows::Utility::ConvertString(it->second);

				if (key->Equals("Cookie")) {
					//////////////////////////////////////////////////////////////////
					try {
						auto cookie = ref new Windows::Web::Http::HttpCookie(key, location, "/");

						char* context = nullptr;
						char* pvalue = strtok_s((char*)it->second.c_str(), "=", &context);
						if (pvalue != nullptr) {
							std::string str = std::string(pvalue);
							cookie->Value = TitaniumWindows::Utility::ConvertString(str);
							cookie->Expires = nullptr;
							cookie->Secure = false;
							cookie->HttpOnly = true;
							filter__->CookieManager->SetCookie(cookie, false);
						}
					} catch (Platform::InvalidArgumentException^ ex) {
						RunOnUIThread([=]() {
							std::string error(TitaniumWindows::Utility::ConvertString(ex->Message));
							onerror(ex->HResult, error, false);
						});
					} catch (Platform::Exception^ ex) {
						RunOnUIThread([=]() {
							std::string error(TitaniumWindows::Utility::ConvertString(ex->Message));
							onerror(ex->HResult, error, false);

						});
					} catch (...) {
						RunOnUIThread([=]() {
							onerror(-1, "Unknown error", false);
						});
					}
				}
			}
		}

		void HTTPClient::_waitForResponse() TITANIUM_NOEXCEPT
		{
			responseWaiter__.wait();
		}
	}
}
