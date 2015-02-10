/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_HTTPCLIENT_HPP_
#define _TITANIUMWINDOWS_HTTPCLIENT_HPP_

#include "detail/NetworkBase.hpp"
#include <ppltasks.h>
#include <Robuffer.h>

using namespace Concurrency;

namespace TitaniumWindows
{
	namespace Network
	{
		enum NATIVE_HTTPCLIENT_METHOD {
			N_HTTPCLIENT_METHOD_GET,
			N_HTTPCLIENT_METHOD_PUT,
			N_HTTPCLIENT_METHOD_POST,
			N_HTTPCLIENT_METHOD_DELETE,
			N_HTTPCLIENT_METHOD_HEAD
		};

		using namespace HAL;

		class TITANIUMWINDOWS_EXPORT HTTPClient final : public Titanium::Network::HTTPClient, public JSExport<HTTPClient>
		{
		public:
			HTTPClient(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~HTTPClient();
			HTTPClient(const HTTPClient&) = default;
			HTTPClient& operator=(const HTTPClient&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			HTTPClient(HTTPClient&&) = default;
			HTTPClient& operator=(HTTPClient&&) = default;
#endif

			static void JSExportInitialize();

			virtual void setTimeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT override final;
			virtual void open(const std::string& method, const std::string& url) TITANIUM_NOEXCEPT override final;
			virtual void send() TITANIUM_NOEXCEPT override final;
			virtual void send(const std::map<std::string, std::vector<unsigned char>>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT override final;
			virtual void send(const std::string& postDataStr) TITANIUM_NOEXCEPT override final;
			virtual std::string getResponseText() const TITANIUM_NOEXCEPT override final;
			virtual std::vector<unsigned char> getResponseData() const TITANIUM_NOEXCEPT override final;
			virtual void abort() TITANIUM_NOEXCEPT override final;
			virtual void setRequestHeader(const std::string& name, const std::string& value) TITANIUM_NOEXCEPT override final;
			virtual std::string getAllResponseHeaders() const TITANIUM_NOEXCEPT override final;
			virtual std::uint32_t getReadyState() const TITANIUM_NOEXCEPT override final;
			virtual std::string getResponseHeader(const std::string& name) TITANIUM_NOEXCEPT override final;
			virtual std::uint32_t getStatus() const TITANIUM_NOEXCEPT override final;
			virtual std::string getStatusText() const TITANIUM_NOEXCEPT override final;
			virtual void clearCookies(const std::string& url) TITANIUM_NOEXCEPT override final;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			// method_ - type of HTTP request (GET, POST, PUT)
			NATIVE_HTTPCLIENT_METHOD method__;
			// url__ - the full address of the HTTP request for example http://www.appcelerator.com
			std::string url__;
			// filter__ - controls the HTTP session and data flow
			Windows::Web::Http::Filters::HttpBaseProtocolFilter ^ filter__;
			// httpClient__ - higher level HTTP client that provides WinRT API to HTTP sessions and communications
			Windows::Web::Http::HttpClient ^ httpClient__;
			// cancellationTokenSource__ - HttpClient provides an asynchronous channel to handle HTTP reponses and
			// errors. Cancellation tokens allow the current HTTP
			concurrency::cancellation_token_source cancellationTokenSource__;
			//  timeoutRegistrationToken__ - used to remove the timeout handler
			Windows::Foundation::EventRegistrationToken timeoutRegistrationToken__;
			// dispatcherTimer__ - WinRT timer used to cancel a HTTP connection if timeout specified
			Windows::UI::Xaml::DispatcherTimer ^ dispatcherTimer__;
			// responseStream__ - holds response string, the stream is not exposed
			Windows::Storage::Streams::IBuffer ^ responseStream__;
			// responseBuffer__ - buffer used holds raw response data
			Windows::Storage::Streams::IBuffer ^ responseBuffer__;
			// timeoutSpan__ - the span in milliseconds during which the request is active
			Windows::Foundation::TimeSpan timeoutSpan__;
			// requestStatus__ - the http status returned from the server
			std::uint32_t requestStatus__;
			// requestStatus__ - the http status returned from the server in text from
			std::string requestStatusText__;
			// readyState__ - current state of the connection
			std::uint32_t readyState__;
			// responseHeaders__ - the collection of key value pairs returned from the server
			std::map<const std::string, std::string> responseHeaders__;
			// contentLength__ - the value in the Content-Length attribute of the response header
			// If no length is reutrned the server has returned the data using chunked encoding
			long contentLength__; // -1 if response is using chunked encoding
			// requestHeaders__ - the collection of key value pairs to be sent to the server
			std::map<const std::string, std::string> requestHeaders__;
#pragma warning(pop)

			void startDispatcherTimer();

			task<Windows::Storage::Streams::IBuffer ^> HTTPClient::HTTPResultAsync(
			    Windows::Storage::Streams::IInputStream ^ stream);

			Windows::Storage::Streams::Buffer ^ charVecToBuffer(std::vector<unsigned char> char_vector);

			void SerializeHeaders(Windows::Web::Http::HttpResponseMessage ^ response);
			void SerializeHeaderCollection(Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<::Platform::String ^, ::Platform::String ^> ^> ^ headers);
			void setRequestHeaders(Windows::Web::Http::HttpRequestMessage ^ request);
			void addCookiesToRequest();
		};
	} // namespace Network
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_FILE_HPP_
