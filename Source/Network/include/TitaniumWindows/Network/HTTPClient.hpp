/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_HTTPCLIENT_HPP_
#define _TITANIUMWINDOWS_HTTPCLIENT_HPP_

#include "TitaniumWindows_Network_EXPORT.h"
#include "Titanium/Network/HTTPClient.hpp"
#include <ppltasks.h>
#include <Robuffer.h>
#include <boost/algorithm/string.hpp>
#include <concrt.h>

using namespace Concurrency;

namespace TitaniumWindows
{
	namespace Network
	{
		using namespace HAL;

		/*!
		  @class HTTPClient
		  @ingroup Titanium.Network.HTTPClient

		  @discussion This is the Titanium.Network.HTTPClient implementation for Windows.
	    */
		class TITANIUMWINDOWS_NETWORK_EXPORT HTTPClient final : public Titanium::Network::HTTPClient, public JSExport<HTTPClient>
		{
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(autoEncodeUrl);
			TITANIUM_PROPERTY_UNIMPLEMENTED(cache);
			TITANIUM_PROPERTY_UNIMPLEMENTED(domain);
			TITANIUM_PROPERTY_UNIMPLEMENTED(enableKeepAlive);
			TITANIUM_PROPERTY_UNIMPLEMENTED(file);
			TITANIUM_PROPERTY_UNIMPLEMENTED(securityManager);
			TITANIUM_PROPERTY_UNIMPLEMENTED(tlsVersion);
			TITANIUM_PROPERTY_UNIMPLEMENTED(validatesSecureCertificate);
			TITANIUM_PROPERTY_UNIMPLEMENTED(withCredentials);
			TITANIUM_PROPERTY_UNIMPLEMENTED(connected);
			TITANIUM_PROPERTY_UNIMPLEMENTED(connectionType);
			TITANIUM_FUNCTION_UNIMPLEMENTED(addAuthFactory);
			TITANIUM_FUNCTION_UNIMPLEMENTED(addKeyManager);
			TITANIUM_FUNCTION_UNIMPLEMENTED(addTrustManager);
			TITANIUM_FUNCTION_UNIMPLEMENTED(_waitForResponse);

			HTTPClient(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~HTTPClient();
			HTTPClient(const HTTPClient&) = default;
			HTTPClient& operator=(const HTTPClient&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			HTTPClient(HTTPClient&&) = default;
			HTTPClient& operator=(HTTPClient&&) = default;
#endif

			static void JSExportInitialize();
			// methods
			virtual void abort() TITANIUM_NOEXCEPT override final;
			virtual void clearCookies(const std::string& url) TITANIUM_NOEXCEPT override final;
			virtual std::string getResponseHeader(const std::string& name) TITANIUM_NOEXCEPT override final;
			virtual void open(const std::string& method, const std::string& url) TITANIUM_NOEXCEPT override final;
			virtual void send() TITANIUM_NOEXCEPT override final;
			virtual void send(const std::map<std::string, JSValue>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT override final;
			virtual void send(const std::string& postDataStr) TITANIUM_NOEXCEPT override final;
			virtual void setRequestHeader(const std::string& name, const std::string& value) TITANIUM_NOEXCEPT override final;
			virtual void _waitForResponse() TITANIUM_NOEXCEPT override final;

			// properties
			virtual std::string get_allResponseHeaders() const TITANIUM_NOEXCEPT override final;
			virtual void set_timeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT override final;
			
		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			concurrency::event responseWaiter__;

			// method_ - type of HTTP request (GET, POST, PUT)
			Titanium::Network::RequestMethod method__;
			// filter__ - controls the HTTP session and data flow
			Windows::Web::Http::Filters::HttpBaseProtocolFilter^ filter__;
			// httpClient__ - higher level HTTP client that provides WinRT API to HTTP sessions and communications
			Windows::Web::Http::HttpClient^ httpClient__;
			// cancellationTokenSource__ - HttpClient provides an asynchronous channel to handle HTTP reponses and
			// errors. Cancellation tokens allow the current HTTP
			concurrency::cancellation_token_source cancellationTokenSource__;
			//  timeoutRegistrationToken__ - used to remove the timeout handler
			Windows::Foundation::EventRegistrationToken timeoutRegistrationToken__;
			// dispatcherTimer__ - WinRT timer used to cancel a HTTP connection if timeout specified
			Windows::UI::Xaml::DispatcherTimer^ dispatcherTimer__;
			// responseStream__ - holds response string, the stream is not exposed
			Windows::Storage::Streams::IBuffer^ responseStream__;
			// responseDataLen__ - count of character contained in data vector
			long responseDataLen__ { 0 };
			// timeoutSpan__ - the span in milliseconds during which the request is active
			Windows::Foundation::TimeSpan timeoutSpan__;
			// responseHeaders__ - the collection of key value pairs returned from the server

			std::map<const std::string, std::string> responseHeaders__;
			// contentLength__ - the value in the Content-Length attribute of the response header
			// If no length is returned the server has returned the data using chunked encoding
			long contentLength__ { 0 }; // -1 if response is using chunked encoding

			struct lexicographicalComparator : public std::binary_function<std::string, std::string, bool> {
				bool operator()(const std::string &lhs, const std::string &rhs) const {
					return boost::algorithm::lexicographical_compare(lhs, rhs, boost::algorithm::is_iless());
				}
			};
			// requestHeaders__ - the case-insensitive collection of key value pairs to be sent to the server
			std::map<const std::string, std::string, lexicographicalComparator> requestHeaders__;

			bool disposed__ { false };
#pragma warning(pop)

			void startDispatcherTimer();
			task<Windows::Storage::Streams::IBuffer^> HTTPClient::HTTPResultAsync(Windows::Storage::Streams::IInputStream^ stream, concurrency::cancellation_token token);
			Windows::Storage::Streams::IBuffer^ charVecToBuffer(std::vector<std::uint8_t> char_vector);

			void SerializeHeaders(Windows::Web::Http::HttpResponseMessage^ response);
			void SerializeHeaderCollection(Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::String^>^>^ headers);
			void setRequestHeaders(Windows::Web::Http::HttpRequestMessage^ request);
			void addCookiesToRequest();

			void send(Windows::Web::Http::IHttpContent^ content);
		};
	} // namespace Network
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_FILE_HPP_
