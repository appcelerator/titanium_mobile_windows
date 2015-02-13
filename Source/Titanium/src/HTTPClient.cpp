/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "HTTPClient.hpp"
#include "Titanium/detail/TiBase.hpp"

#include <collection.h>
#include <algorithm>

using namespace concurrency;

namespace TitaniumWindows
{
	namespace Network
	{
		HTTPClient::HTTPClient(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Titanium::Network::HTTPClient(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Network::HTTPClient::ctor Initialize");

			responseBuffer__ = ref new Windows::Storage::Streams::Buffer(1000);
			readyState__ = Titanium::Network::N_REQUEST_STATE_UNSENT;
		}

		HTTPClient::~HTTPClient()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Network::HTTPClient::dtor");
			filter__ = nullptr;
			httpClient__ = nullptr;
			dispatcherTimer__ = nullptr;
			responseBuffer__ = nullptr;
		}

		void HTTPClient::JSExportInitialize()
		{
			JSExport<HTTPClient>::SetClassVersion(1);
			JSExport<HTTPClient>::SetParent(JSExport<Titanium::Network::HTTPClient>::Class());
		}

		void HTTPClient::setTimeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT
		{
			std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = timeout;
			timeoutSpan__.Duration = timer_interval_ticks.count();
		}

		void HTTPClient::open(const std::string& method, const std::string& url) TITANIUM_NOEXCEPT
		{
			auto method__ = N_HTTPCLIENT_METHOD_GET;
			if (method == "DELETE") {
				method__ = N_HTTPCLIENT_METHOD_DELETE;
			} else if (method == "POST") {
				method__ = N_HTTPCLIENT_METHOD_POST;
			} else if (method == "PUT") {
				method__ = N_HTTPCLIENT_METHOD_PUT;
			}

			url__ = url;
			filter__ = ref new Windows::Web::Http::Filters::HttpBaseProtocolFilter();
			httpClient__ = ref new Windows::Web::Http::HttpClient(filter__);
			cancellationTokenSource__ = concurrency::cancellation_token_source();
			filter__->AllowAutoRedirect;
			filter__->CacheControl->ReadBehavior = Windows::Web::Http::Filters::HttpCacheReadBehavior::MostRecent;

			addCookiesToRequest();
		}

		void HTTPClient::send() TITANIUM_NOEXCEPT
		{
			std::wstring w_str(url__.begin(), url__.end());
			Windows::Foundation::Uri ^ uri = ref new Windows::Foundation::Uri(ref new Platform::String(w_str.c_str()));
			Windows::Web::Http::HttpRequestMessage ^ request = ref new Windows::Web::Http::HttpRequestMessage(Windows::Web::Http::HttpMethod::Get, uri);

			setRequestHeaders(request);

			// Startup a timer that will abort the request after the timeout period is reached.
			startDispatcherTimer();

			create_task(
			    httpClient__->SendRequestAsync(request, Windows::Web::Http::HttpCompletionOption::ResponseHeadersRead),
			    cancellationTokenSource__.get_token()).then([this](Windows::Web::Http::HttpResponseMessage ^ response) {
		  
				readyState__ = Titanium::Network::N_REQUEST_STATE_OPENED;
				onreadystatechange(Titanium::Network::N_REQUEST_STATE_OPENED);

				SerializeHeaders(response);

		  return create_task(response->Content->ReadAsInputStreamAsync(), cancellationTokenSource__.get_token()); }, task_continuation_context::use_current())
			    .then([this](Windows::Storage::Streams::IInputStream ^ stream) {
			  
			  readyState__ = Titanium::Network::N_REQUEST_STATE_LOADING;
			  onreadystatechange(Titanium::Network::N_REQUEST_STATE_LOADING);

		  return HTTPResultAsync(stream); }, task_continuation_context::use_current())
			    .then([this](task<Windows::Storage::Streams::IBuffer ^> previousTask) {
		  try {
			  // Check if any previous task threw an exception.
			  previousTask.get();

			  readyState__ = Titanium::Network::N_REQUEST_STATE_DONE;
			  onreadystatechange(Titanium::Network::N_REQUEST_STATE_DONE);
		  }
		  catch (const task_canceled&) {
			 onerror(0, "Session Cancelled", false);
		  }
		  catch (Platform::Exception^ ex) {
			  std::wstring werror = ex->Message->Data();
			  std::string error(werror.begin(), werror.end());
			  onerror(0, error, false);
		  } });
		}

		void HTTPClient::send(const std::map<std::string, std::vector<unsigned char>>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT
		{
			Windows::Web::Http::IHttpContent ^ postData;
			Windows::Foundation::IAsyncOperationWithProgress<Windows::Web::Http::HttpResponseMessage ^, Windows::Web::Http::HttpProgress> ^ operation;

			if (method__ == N_HTTPCLIENT_METHOD_GET) {
				TITANIUM_LOG_WARN("HTTPClient::send: Data found during a GET request. Data will be ignored.");
				send();
			}

			std::wstring w_str(url__.begin(), url__.end());
			Windows::Foundation::Uri ^ uri = ref new Windows::Foundation::Uri(ref new Platform::String(w_str.c_str()));

			// Startup a timer that will abort the request after the timeout period is reached.
			startDispatcherTimer();

			if (useMultipartForm) {
				postData = ref new Windows::Web::Http::HttpMultipartFormDataContent();

				for (auto pair : postDataPairs) {
					std::wstring w_str(pair.first.begin(), pair.first.end());
					Platform::String ^ name = ref new Platform::String(w_str.c_str());
					static_cast<Windows::Web::Http::HttpMultipartFormDataContent ^>(postData)->Add(ref new Windows::Web::Http::HttpBufferContent(charVecToBuffer(pair.second)), name);
				}
			} else {
				auto keyValues = ref new Platform::Collections::Map<Platform::String ^, Platform::String ^>();
				for (auto pair : postDataPairs) {
					std::wstring w_str(pair.first.begin(), pair.first.end());
					Platform::String ^ name = ref new Platform::String(w_str.c_str());

					std::wstringstream ws_stream;
					for (auto c : pair.second) {
						ws_stream << c;
					}
					w_str = ws_stream.str();

					Platform::String ^ value = ref new Platform::String(w_str.c_str());
					keyValues->Insert(name, value);
				}

				postData = ref new Windows::Web::Http::HttpFormUrlEncodedContent(keyValues);
			}

			if (method__ == N_HTTPCLIENT_METHOD_POST) {
				operation = httpClient__->PostAsync(uri, postData);
			} else {
				operation = httpClient__->PutAsync(uri, postData);
			}

			create_task(operation, cancellationTokenSource__.get_token()).then([this](Windows::Web::Http::HttpResponseMessage ^ response) {

				readyState__ = Titanium::Network::N_REQUEST_STATE_OPENED;
				onreadystatechange(Titanium::Network::N_REQUEST_STATE_OPENED);

				SerializeHeaders(response);

		  return response; }, task_continuation_context::use_current()).then([=](task<Windows::Web::Http::HttpResponseMessage ^> previousTask) {
		  try {
			  // Check if any previous task threw an exception.
			  previousTask.get();

			  readyState__ = Titanium::Network::N_REQUEST_STATE_DONE;
			  onreadystatechange(Titanium::Network::N_REQUEST_STATE_DONE);
		  }
		  catch (const task_canceled&) {
			  onerror(0, "Session Cancelled", false);
		  }
		  catch (Platform::Exception^ ex) {
			  std::wstring werror = ex->Message->Data();
			  std::string error(werror.begin(), werror.end());
			  onerror(0, error, false);
		  } }, task_continuation_context::use_current());
		}

		void HTTPClient::send(const std::string& postDataStr) TITANIUM_NOEXCEPT
		{
			Windows::Web::Http::IHttpContent ^ postData;
			Windows::Foundation::IAsyncOperationWithProgress<Windows::Web::Http::HttpResponseMessage ^, Windows::Web::Http::HttpProgress> ^ operation;

			if (method__ == N_HTTPCLIENT_METHOD_GET) {
				TITANIUM_LOG_WARN("HTTPClient::send: Data found during a GET request. Data will be ignored.");
				send();
			}

			std::wstring w_str(url__.begin(), url__.end());
			Windows::Foundation::Uri ^ uri = ref new Windows::Foundation::Uri(ref new Platform::String(w_str.c_str()));

			// Startup a timer that will abort the request after the timeout period is reached.
			startDispatcherTimer();

			w_str.assign(postDataStr.begin(), postDataStr.end());
			postData = ref new Windows::Web::Http::HttpStringContent(ref new Platform::String(w_str.c_str()));

			if (method__ == N_HTTPCLIENT_METHOD_POST) {
				operation = httpClient__->PostAsync(uri, postData);
			} else {
				operation = httpClient__->PutAsync(uri, postData);
			}

			create_task(operation, cancellationTokenSource__.get_token()).then([this](Windows::Web::Http::HttpResponseMessage ^ response) {

				SerializeHeaders(response);

				readyState__ = Titanium::Network::N_REQUEST_STATE_OPENED;
				onreadystatechange(Titanium::Network::N_REQUEST_STATE_OPENED);

			return response; }, task_continuation_context::use_current()).then([=](task<Windows::Web::Http::HttpResponseMessage ^> previousTask) {
					try {
						// Check if any previous task threw an exception.
						previousTask.get();

						readyState__ = Titanium::Network::N_REQUEST_STATE_DONE;
						onreadystatechange(Titanium::Network::N_REQUEST_STATE_DONE);
					}
					catch (const task_canceled&) {
						onerror(0, "Session Cancelled", false);
					}
					catch (Platform::Exception^ ex) {
						std::wstring werror = ex->Message->Data();
						std::string error(werror.begin(), werror.end());
						onerror(0, error, false);
					} }, task_continuation_context::use_current());
		}

		std::string HTTPClient::getResponseText() const TITANIUM_NOEXCEPT
		{
			unsigned char* bytes;
			Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
			Microsoft::WRL::ComPtr<IInspectable> insp(reinterpret_cast<IInspectable*>(responseBuffer__));
			HRESULT hr = insp.As(&bufferByteAccess);
			if (FAILED(hr)) {
				throw ::Platform::Exception::CreateException(hr);
			}
			hr = bufferByteAccess->Buffer(&bytes);
			if (FAILED(hr)) {
				throw ::Platform::Exception::CreateException(hr);
			}
			return std::string(reinterpret_cast<const char*>(bytes));
		}

		std::vector<unsigned char> HTTPClient::getResponseData() const TITANIUM_NOEXCEPT
		{
			unsigned char* bytes;
			Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
			Microsoft::WRL::ComPtr<IInspectable> insp(reinterpret_cast<IInspectable*>(responseBuffer__));
			HRESULT hr = insp.As(&bufferByteAccess);
			if (FAILED(hr)) {
				throw ::Platform::Exception::CreateException(hr);
			}
			hr = bufferByteAccess->Buffer(&bytes);
			if (FAILED(hr)) {
				throw ::Platform::Exception::CreateException(hr);
			}
			return std::vector<unsigned char>(bytes, bytes + responseBuffer__->Length);
		}

		void HTTPClient::abort() TITANIUM_NOEXCEPT
		{
			cancellationTokenSource__.cancel();
			dispatcherTimer__->Stop();
		}

		void HTTPClient::setRequestHeader(const std::string& key, const std::string& value) TITANIUM_NOEXCEPT
		{
			responseHeaders__.insert(std::make_pair(key, value));
		}

		std::string HTTPClient::getAllResponseHeaders() const TITANIUM_NOEXCEPT
		{
			std::stringstream s_stream;
			for (auto it = responseHeaders__.begin(); it != responseHeaders__.end(); ++it) {
				s_stream << it->first.c_str() << ":" << it->second.c_str() << ";";
			}

			return s_stream.str();
		}

		std::uint32_t HTTPClient::getReadyState() const TITANIUM_NOEXCEPT
		{
			return readyState__;
		}

		std::uint32_t HTTPClient::getStatus() const TITANIUM_NOEXCEPT
		{
			return requestStatus__;
		}

		std::string HTTPClient::getStatusText() const TITANIUM_NOEXCEPT
		{
			return requestStatusText__;
		}

		void HTTPClient::clearCookies(const std::string& url) TITANIUM_NOEXCEPT
		{
			auto filter = ref new Windows::Web::Http::Filters::HttpBaseProtocolFilter();

			std::wstring w_str(url.begin(), url.end());
			Windows::Foundation::Uri ^ uri = ref new Windows::Foundation::Uri(ref new Platform::String(w_str.c_str()));
			auto cookieCollection = filter->CookieManager->GetCookies(uri);

			Windows::Foundation::Collections::IIterator<Windows::Web::Http::HttpCookie ^> ^ iterator = cookieCollection->First();
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

		void HTTPClient::setRequestHeaders(Windows::Web::Http::HttpRequestMessage ^ request) TITANIUM_NOEXCEPT
		{
			// Set type safe headers. Content-Type is the most popular may need to set others.
			auto it = requestHeaders__.find("Content-Type");
			if (it != requestHeaders__.end()) {
				std::wstring w_str(it->second.begin(), it->second.end());
				request->Content->Headers->ContentType =
				    ref new Windows::Web::Http::Headers::HttpMediaTypeHeaderValue(ref new Platform::String(w_str.c_str()));
				requestHeaders__.erase(it);
			}

			for (it = requestHeaders__.begin(); it != requestHeaders__.end(); ++it) {
				std::wstring key(it->first.begin(), it->first.end());
				std::wstring value(it->second.begin(), it->second.end());

				// ignor cookies they are added during open to the request filter.
				std::wstring cmp(L"Cookie");

				if (key.compare(cmp) != 0) {
					request->Headers->Append(ref new Platform::String(key.c_str()),
					                         ref new Platform::String(value.c_str()));
				}
			}
		}

		task<Windows::Storage::Streams::IBuffer ^> HTTPClient::HTTPResultAsync(
		    Windows::Storage::Streams::IInputStream ^ stream)
		{
			return create_task(
			           stream->ReadAsync(responseBuffer__, responseBuffer__->Capacity, Windows::Storage::Streams::InputStreamOptions::Partial),
			           cancellationTokenSource__.get_token()).then([=](task<Windows::Storage::Streams::IBuffer ^> readTask) {

				// Stop the timeout timer
				dispatcherTimer__->Stop();

				if (contentLength__ != -1) {
					ondatastream(responseBuffer__->Length / contentLength__);
				}
				else {
					ondatastream(-1); // chunked encoding was used
				}

				if (!responseBuffer__->Length) {
					onload(0, "Response has been loaded.", true);
				}

				return responseBuffer__->Length ? HTTPResultAsync(stream) : readTask; }, task_continuation_context::use_current());
		}

		void HTTPClient::startDispatcherTimer()
		{
			if (dispatcherTimer__ == nullptr) {
				dispatcherTimer__ = ref new Windows::UI::Xaml::DispatcherTimer();
				dispatcherTimer__->Interval = timeoutSpan__;
				auto timeoutRegistrationToken__ =
				    dispatcherTimer__->Tick += ref new Windows::Foundation::EventHandler<Platform::Object ^>([this](Platform::Object ^ sender, Platform::Object ^ e) {
			  cancellationTokenSource__.cancel();
			  dispatcherTimer__->Stop();
			  // re-create the CancellationTokenSource.
			  cancellationTokenSource__ = cancellation_token_source();
					});
				dispatcherTimer__->Start();
			}
		}

		Windows::Storage::Streams::Buffer ^ HTTPClient::charVecToBuffer(std::vector<unsigned char> char_vector)
		{
			int size = char_vector.size();

			Windows::Storage::Streams::Buffer ^ buffer = ref new Windows::Storage::Streams::Buffer(size);
			buffer->Length = size;

			Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
			HRESULT hr = reinterpret_cast<IUnknown*>(buffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess));
			if (FAILED(hr)) {
				throw ref new Platform::Exception(hr);
			}

			unsigned char* data = (unsigned char*)&char_vector[0];
			hr = bufferByteAccess->Buffer(&data);
			if (FAILED(hr)) {
				throw ref new Platform::Exception(hr);
			}

			return buffer;
		}

		void HTTPClient::SerializeHeaders(Windows::Web::Http::HttpResponseMessage ^ response)
		{
			requestStatus__ = (std::uint32_t)response->StatusCode;
			std::wstring w_str = response->ReasonPhrase->Data();
			requestStatusText__ = std::string((const char*)&w_str[0], sizeof(wchar_t) / sizeof(char) * w_str.size());

			SerializeHeaderCollection(response->Headers);
			SerializeHeaderCollection(response->Content->Headers);

			std::map<std::string, std::string>::iterator it;
			it = responseHeaders__.find("Content-Length");
			if (it != responseHeaders__.end()) {
				contentLength__ = atol(it->second.c_str());
			} else {
				contentLength__ = -1;  // chunked encoding
			}

			readyState__ = Titanium::Network::N_REQUEST_STATE_HEADERS_RECEIVED;
			onreadystatechange(Titanium::Network::N_REQUEST_STATE_HEADERS_RECEIVED);
		}

		void HTTPClient::SerializeHeaderCollection(Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<Platform::String ^, Platform::String ^> ^> ^ headers)
		{
			for each(Windows::Foundation::Collections::IKeyValuePair<Platform::String ^, Platform::String ^> ^ pair in headers)
			{
				std::wstring w_str = pair->Key->Data();
				std::string key = std::string(w_str.begin(), w_str.end());
				w_str = std::wstring(pair->Value->Data());
				std::string value = std::string(w_str.begin(), w_str.end());
				responseHeaders__.insert(std::make_pair(key, value));
			}
		}

		void HTTPClient::addCookiesToRequest()
		{
			std::wstring w_url(url__.begin(), url__.end());

			for (auto it = requestHeaders__.begin(); it != requestHeaders__.end(); ++it) {
				std::wstring key(it->first.begin(), it->first.end());
				std::wstring value(it->second.begin(), it->second.end());

				std::wstring cmp(L"Cookie");

				if (key.compare(cmp) == 0) {
					//////////////////////////////////////////////////////////////////
					try {
						auto cookie = ref new Windows::Web::Http::HttpCookie(
						    ref new Platform::String(key.c_str()),
						    ref new Platform::String(w_url.c_str()),
						    "/");

						char* context = nullptr;
						char* pvalue = strtok_s((char*)it->second.c_str(), "=", &context);
						if (pvalue != nullptr) {
							std::string str = std::string(pvalue);
							std::wstring w_str(str.begin(), str.end());
							cookie->Value = ref new Platform::String(w_str.c_str());
							cookie->Expires = nullptr;
							cookie->Secure = false;
							cookie->HttpOnly = true;
							filter__->CookieManager->SetCookie(cookie, false);
						}
					} catch (Platform::InvalidArgumentException ^ ex) {
						std::wstring werror = ex->Message->Data();
						std::string error(werror.begin(), werror.end());
						onerror(0, error, false);
					} catch (Platform::Exception ^ ex) {
						std::wstring werror = ex->Message->Data();
						std::string error(werror.begin(), werror.end());
						onerror(0, error, false);
					}
				}
			}
		}
	}
}
