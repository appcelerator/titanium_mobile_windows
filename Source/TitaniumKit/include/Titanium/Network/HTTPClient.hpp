/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_NETWORK_HTTPCLIENT_HPP_
#define _TITANIUM_NETWORK_HTTPCLIENT_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/Network/Constants.hpp"

#define BOOST_BIND_NO_PLACEHOLDERS
#include <boost/signals2/signal.hpp>

namespace Titanium
{
	namespace Network
	{
		enum class RequestState {
			Unsent,
			Opened,
			Headers_Received,
			Loading,
			Done
		};

		enum class RequestMethod {
			Get,
			Put,
			Post,
			Delete,
			Head,
			Patch,
			Options
		};

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium.Network.HTTPClient module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Network.HTTPClient
		*/
		class TITANIUMKIT_EXPORT HTTPClient : public Module, public JSExport<HTTPClient>
		{
		public:

			/*!
			  @property
			  @abstract allResponseHeaders
			  @discussion All of the response headers.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, allResponseHeaders);

			/*!
			  @property
			  @abstract autoEncodeUrl
			  @discussion Determines whether automatic encoding is enabled for the specified URL.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, autoEncodeUrl);

			/*!
			  @property
			  @abstract autoRedirect
			  @discussion Determines whether automatic automatic handling of HTTP redirects is enabled.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, autoRedirect);

			/*!
			  @property
			  @abstract connected
			  @discussion Indicates whether the response was successful.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(bool, connected);

			/*!
			  @property
			  @abstract connectionType
			  @discussion Connection type, normally either `GET` or `POST`.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, connectionType);

			/*!
			  @property
			  @abstract domain
			  @discussion Sets the domain parameter for authentication credentials.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, domain);

			/*!
			  @property
			  @abstract enableKeepAlive
			  @discussion Determines whether the client should attempt to keep a persistent connection.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, enableKeepAlive);

			/*!
			  @property
			  @abstract file
			  @discussion Target local file to receive data.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, file);

			/*!
			  @property
			  @abstract location
			  @discussion Absolute URL of the request.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, location);


			/*!
			  @property
			  @abstract password
			  @discussion Sets the password parameter for authentication credentials.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, password);

			/*!
			  @property
			  @abstract readyState
			  @discussion The current ready state of this HTTP request.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(RequestState, readyState);

			/*!
			  @property
			  @abstract responseData
			  @discussion Response data as a `Blob` object.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::uint8_t>, responseData);

			/*!
			  @property
			  @abstract responseText
			  @discussion Response as text.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, responseText);

			/*!
			  @property
			  @abstract status
			  @discussion Response HTTP status code.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::uint32_t, status);

			/*!
			  @property
			  @abstract statusText
			  @discussion Human-readable status message associated with the status code.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, statusText);

			/*!
			  @property
			  @abstract timeout
			  @discussion Timeout in milliseconds when the connection should be aborted.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::chrono::milliseconds, timeout);

			/*!
			  @property
			  @abstract username
			  @discussion Sets the username parameter for authentication credentials.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, username);

			/*!
			  @property
			  @abstract validatesSecureCertificate
			  @discussion Determines how SSL certification validation is performed on connection.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, validatesSecureCertificate);

			/*!
			  @property
			  @abstract withCredentials
			  @discussion Determines whether the request should include any cookies and HTTP authentication information.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, withCredentials);

			/*!
			  @property
			  @abstract tlsVersion
			  @discussion Sets the TLS version to use for handshakes.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TLS_VERSION, tlsVersion);

			/*!
			  @property
			  @abstract cache
			  @discussion Determines whether HTTP responses are cached.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, cache);

			// ----------------------------------------- Methods

			/*!
			  @method
			  @abstract abort
			  @discussion Cancel the current HTTP request.
			*/
			virtual void abort() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract clearCookies
			  @discussion Delete all cookies associated with the domain (url).
			*/
			virtual void clearCookies(const std::string& url) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getResponseHeader
			  @discussion Get the header based on the key name.
			*/
			virtual std::string getResponseHeader(const std::string& key) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract open
			  @discussion Initiate the connect between the client and the server.
			*/
			virtual void open(const std::string& method, const std::string& url) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract send
			  @discussion Do an HTTP GET request.
			*/
			virtual void send() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract send
			  @discussion Do an HTTP POST or PUT request with data URL encoded or contained in multipart form.
			*/
			virtual void send(const std::map<std::string, JSValue>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract send
			  @discussion Do an HTTP POST or PUT request with data type text in body.
			*/
			virtual void send(const std::string& postDataStr) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract setRequestHeader
			  @discussion Set the header key:value pair sent to the server.
			*/
			virtual void setRequestHeader(const std::string& key, const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract _waitForResponse
			  @discussion Wait for response for the request. Blocks until server responses.
			*/
			virtual void _waitForResponse() TITANIUM_NOEXCEPT;

			HTTPClient(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~HTTPClient() = default;
			HTTPClient(const HTTPClient&) = default;
			HTTPClient& operator=(const HTTPClient&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			HTTPClient(HTTPClient&&) = default;
			HTTPClient& operator=(HTTPClient&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(autoEncodeUrl);
			TITANIUM_PROPERTY_DEF(autoRedirect);
			TITANIUM_PROPERTY_DEF(cache);
			TITANIUM_PROPERTY_DEF(domain);
			TITANIUM_PROPERTY_DEF(enableKeepAlive);
			TITANIUM_PROPERTY_DEF(file);
			TITANIUM_PROPERTY_DEF(ondatastream);
			TITANIUM_PROPERTY_DEF(onerror);
			TITANIUM_PROPERTY_DEF(onload);
			TITANIUM_PROPERTY_DEF(onreadystatechange);
			TITANIUM_PROPERTY_DEF(onsendstream);
			TITANIUM_PROPERTY_DEF(password);
			TITANIUM_PROPERTY_DEF(securityManager);
			TITANIUM_PROPERTY_DEF(timeout);
			TITANIUM_PROPERTY_DEF(tlsVersion);
			TITANIUM_PROPERTY_DEF(username);
			TITANIUM_PROPERTY_DEF(validatesSecureCertificate);
			TITANIUM_PROPERTY_DEF(withCredentials);
			TITANIUM_PROPERTY_READONLY_DEF(DONE);
			TITANIUM_PROPERTY_READONLY_DEF(HEADERS_RECEIVED);
			TITANIUM_PROPERTY_READONLY_DEF(LOADING);
			TITANIUM_PROPERTY_READONLY_DEF(OPENED);
			TITANIUM_PROPERTY_READONLY_DEF(UNSENT);
			TITANIUM_PROPERTY_READONLY_DEF(allResponseHeaders);
			TITANIUM_PROPERTY_READONLY_DEF(connected);
			TITANIUM_PROPERTY_READONLY_DEF(connectionType);
			TITANIUM_PROPERTY_READONLY_DEF(location);
			TITANIUM_PROPERTY_READONLY_DEF(readyState);
			TITANIUM_PROPERTY_READONLY_DEF(responseData);
			TITANIUM_PROPERTY_READONLY_DEF(responseText);
			TITANIUM_PROPERTY_READONLY_DEF(responseXML);
			TITANIUM_PROPERTY_READONLY_DEF(status);
			TITANIUM_PROPERTY_READONLY_DEF(statusText);

			TITANIUM_FUNCTION_DEF(abort);
			TITANIUM_FUNCTION_DEF(addAuthFactory);
			TITANIUM_FUNCTION_DEF(addKeyManager);
			TITANIUM_FUNCTION_DEF(addTrustManager);
			TITANIUM_FUNCTION_DEF(clearCookies);
			TITANIUM_FUNCTION_DEF(getAllResponseHeaders);
			TITANIUM_FUNCTION_DEF(getAutoEncodeUrl);
			TITANIUM_FUNCTION_DEF(getAutoRedirect);
			TITANIUM_FUNCTION_DEF(getCache);
			TITANIUM_FUNCTION_DEF(getConnected);
			TITANIUM_FUNCTION_DEF(getConnectionType);
			TITANIUM_FUNCTION_DEF(getDomain);
			TITANIUM_FUNCTION_DEF(getEnableKeepAlive);
			TITANIUM_FUNCTION_DEF(getFile);
			TITANIUM_FUNCTION_DEF(getLocation);
			TITANIUM_FUNCTION_DEF(getOndatastream);
			TITANIUM_FUNCTION_DEF(getOnerror);
			TITANIUM_FUNCTION_DEF(getOnload);
			TITANIUM_FUNCTION_DEF(getOnreadystatechange);
			TITANIUM_FUNCTION_DEF(getOnsendstream);
			TITANIUM_FUNCTION_DEF(getPassword);
			TITANIUM_FUNCTION_DEF(getReadyState);
			TITANIUM_FUNCTION_DEF(getResponseData);
			TITANIUM_FUNCTION_DEF(getResponseHeader);
			TITANIUM_FUNCTION_DEF(getResponseText);
			TITANIUM_FUNCTION_DEF(getResponseXML);
			TITANIUM_FUNCTION_DEF(getSecurityManager);
			TITANIUM_FUNCTION_DEF(getStatus);
			TITANIUM_FUNCTION_DEF(getStatusText);
			TITANIUM_FUNCTION_DEF(getTimeout);
			TITANIUM_FUNCTION_DEF(getTlsVersion);
			TITANIUM_FUNCTION_DEF(getUsername);
			TITANIUM_FUNCTION_DEF(getValidatesSecureCertificate);
			TITANIUM_FUNCTION_DEF(getWithCredentials);
			TITANIUM_FUNCTION_DEF(open);
			TITANIUM_FUNCTION_DEF(send);
			TITANIUM_FUNCTION_DEF(setAutoEncodeUrl);
			TITANIUM_FUNCTION_DEF(setAutoRedirect);
			TITANIUM_FUNCTION_DEF(setCache);
			TITANIUM_FUNCTION_DEF(setDomain);
			TITANIUM_FUNCTION_DEF(setEnableKeepAlive);
			TITANIUM_FUNCTION_DEF(setFile);
			TITANIUM_FUNCTION_DEF(setOndatastream);
			TITANIUM_FUNCTION_DEF(setOnerror);
			TITANIUM_FUNCTION_DEF(setOnload);
			TITANIUM_FUNCTION_DEF(setOnreadystatechange);
			TITANIUM_FUNCTION_DEF(setOnsendstream);
			TITANIUM_FUNCTION_DEF(setPassword);
			TITANIUM_FUNCTION_DEF(setRequestHeader);
			TITANIUM_FUNCTION_DEF(setSecurityManager);
			TITANIUM_FUNCTION_DEF(setTimeout);
			TITANIUM_FUNCTION_DEF(setTlsVersion);
			TITANIUM_FUNCTION_DEF(setUsername);
			TITANIUM_FUNCTION_DEF(setValidatesSecureCertificate);
			TITANIUM_FUNCTION_DEF(setWithCredentials);
			TITANIUM_FUNCTION_DEF(_waitForResponse);

			/////// slots
			void ondatastream(const double progress) TITANIUM_NOEXCEPT;
			void onerror(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT;
			void onload(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT;
			void onreadystatechange(const RequestState& state) TITANIUM_NOEXCEPT;
			void onsendstream(const double progress) TITANIUM_NOEXCEPT;
			
#pragma warning(push)
#pragma warning(disable: 4251)
			/////// signals
			boost::signals2::signal<void(const double progress)> datastream;
			boost::signals2::signal<void(const std::uint32_t code, const std::string error, const bool success)> error;
			boost::signals2::signal<void(const std::uint32_t code, const std::string error, const bool success)> loaded;
			boost::signals2::signal<void(const RequestState& state)> readystatechange;
			boost::signals2::signal<void(const double progress)> sendstream;
#pragma warning(pop)

		protected:
#pragma warning(push)
#pragma warning(disable: 4251)
			JSValue ondatastream__;
			JSValue onerror__;
			JSValue onload__;
			JSValue onreadystatechange__;
			JSValue onsendstream__;
			std::chrono::milliseconds timeout__;

			std::map<uint32_t, std::string> httpStatusPhrase__;

			JSValue done__;
			JSValue headers_received__;
			JSValue loading__;
			JSValue opened__;
			JSValue unsent__;

			std::string allResponseHeaders__;
			bool autoEncodeUrl__;
			bool autoRedirect__;
			bool connected__;
			std::string connectionType__;
			std::string domain__;
			bool enableKeepAlive__;
			std::string file__;
			std::string location__;
			std::string password__;
			RequestState readyState__;
			std::vector<std::uint8_t> responseData__;
			JSValue securityManager__;
			std::uint32_t status__;
			std::string statusText__;
			std::string username__;
			bool validatesSecureCertificate__;
			bool withCredentials__;
			TLS_VERSION tlsVersion__;
			bool cache__;
#pragma warning(pop)

			void setHTTPStatusPhrase();
		};
	} // namespace Network
} // namespace Titanium

#endif  // _TITANIUM_NETWORK_HTTPCLIENT_HPP_
