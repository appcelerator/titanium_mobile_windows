/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_NETWORK_HTTPCLIENT_HPP_
#define _TITANIUM_NETWORK_HTTPCLIENT_HPP_

#include "Titanium/Module.hpp"

#define BOOST_BIND_NO_PLACEHOLDERS
#include <boost/signals2/signal.hpp>

namespace Titanium
{
	namespace Network
	{
		enum NATIVE_REQUEST_STATE {
			N_REQUEST_STATE_LOADING,
			N_REQUEST_STATE_OPENED,
			N_REQUEST_STATE_DONE,
			N_REQUEST_STATE_UNSENT,
			N_REQUEST_STATE_HEADERS_RECEIVED
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
			  @method
			  @abstract allResponseHeaders : String
			  @discussion All of the response headers.

			  Contains a single string, or an empty string if no headers are available.

			  See also: getResponseHeader.
			*/
			virtual std::string get_allResponseHeaders() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract readyState : Number
			  @discussion The current ready state of this HTTP request.

			  The ready state describes the current state of the request. The ready state is set to one of the five Titanium.Network.HTTPClient ready state constants. A typical HTTP request goes through the states in this order:

			  UNSENT
			  OPENED
			  HEADERS_RECEIVED
			  LOADING
			  DONE
			  The onreadystatechange callback is invoked each time the ready state changes.

			  This property can be assigned the following constants:

			  Titanium.Network.HTTPClient.UNSENT
			  Titanium.Network.HTTPClient.OPENED
			  Titanium.Network.HTTPClient.HEADERS_RECEIVED
			  Titanium.Network.HTTPClient.LOADING
			  Titanium.Network.HTTPClient.DONE
			*/
			// FIXME Use an enum for the value!
			virtual std::uint32_t get_readyState() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract responseData : Titanium.Blob
			  @discussion Response data as a Blob object.
			*/
			virtual std::vector<std::uint8_t> get_responseData() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract responseText : String
			  @discussion Response as text.
			*/
			virtual std::string get_responseText() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract status : Number
			  @discussion Response HTTP status code.
			*/
			virtual std::uint32_t get_status() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract statusText : String
			  @discussion Human-readable status message associated with the status code.
			*/
			virtual std::string get_statusText() const TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract timeout : Number

			  @discussion Timeout in milliseconds when the connection should be aborted.

			  On Mobile Web and Tizen, the timeout only works when making asynchronous requests.
			*/
			virtual std::chrono::milliseconds get_timeout() const TITANIUM_NOEXCEPT final;
			virtual void set_timeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT;

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
			virtual void send(const std::map<std::string, std::vector<std::uint8_t>>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT;

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

			HTTPClient(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~HTTPClient() = default;
			HTTPClient(const HTTPClient&) = default;
			HTTPClient& operator=(const HTTPClient&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			HTTPClient(HTTPClient&&) = default;
			HTTPClient& operator=(HTTPClient&&) = default;
#endif

			static void JSExportInitialize();

			/////// constant properties
			TITANIUM_PROPERTY_READONLY_DEF(LOADING);
			TITANIUM_PROPERTY_READONLY_DEF(OPENED);
			TITANIUM_PROPERTY_READONLY_DEF(DONE);
			TITANIUM_PROPERTY_READONLY_DEF(UNSENT);
			TITANIUM_PROPERTY_READONLY_DEF(HEADERS_RECEIVED);

			/////// properties
			TITANIUM_PROPERTY_READONLY_DEF(allResponseHeaders);
			TITANIUM_FUNCTION_DEF(getAllResponseHeaders);

			TITANIUM_PROPERTY_DEF(ondatastream);
			TITANIUM_FUNCTION_DEF(getOndatastream);
			TITANIUM_FUNCTION_DEF(setOndatastream);

			TITANIUM_PROPERTY_DEF(onerror);
			TITANIUM_FUNCTION_DEF(getOnerror);
			TITANIUM_FUNCTION_DEF(setOnerror);

			TITANIUM_PROPERTY_DEF(onload);
			TITANIUM_FUNCTION_DEF(getOnload);
			TITANIUM_FUNCTION_DEF(setOnload);

			TITANIUM_PROPERTY_DEF(onreadystatechange);
			TITANIUM_FUNCTION_DEF(getOnreadystatechange);
			TITANIUM_FUNCTION_DEF(setOnreadystatechange);

			TITANIUM_PROPERTY_DEF(onsendstream);
			TITANIUM_FUNCTION_DEF(getOnsendstream);
			TITANIUM_FUNCTION_DEF(setOnsendstream);

			TITANIUM_PROPERTY_READONLY_DEF(readyState);
			TITANIUM_FUNCTION_DEF(getReadyState);

			TITANIUM_PROPERTY_READONLY_DEF(responseData);
			TITANIUM_FUNCTION_DEF(getResponseData);

			TITANIUM_PROPERTY_READONLY_DEF(responseText);
			TITANIUM_FUNCTION_DEF(getResponseText);
			
			TITANIUM_PROPERTY_READONLY_DEF(status);
			TITANIUM_FUNCTION_DEF(getStatus);

			TITANIUM_PROPERTY_READONLY_DEF(statusText);
			TITANIUM_FUNCTION_DEF(getStatusText);

			TITANIUM_PROPERTY_DEF(timeout);
			TITANIUM_FUNCTION_DEF(getTimeout);
			TITANIUM_FUNCTION_DEF(setTimeout);

			/////// methods
			TITANIUM_FUNCTION_DEF(abort);
			TITANIUM_FUNCTION_DEF(clearCookies);
			TITANIUM_FUNCTION_DEF(getResponseHeader);
			TITANIUM_FUNCTION_DEF(open);
			TITANIUM_FUNCTION_DEF(send);
			TITANIUM_FUNCTION_DEF(setRequestHeader);

			/////// slots
			void ondatastream(const double progress) TITANIUM_NOEXCEPT;
			void onerror(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT;
			void onload(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT;
			void onreadystatechange(const std::uint32_t state) TITANIUM_NOEXCEPT;
		    void onsendstream(const double progress) TITANIUM_NOEXCEPT;
			
			/////// signals
#pragma warning(push)
#pragma warning(disable: 4251)
			boost::signals2::signal<void(const double progress)> datastream;
			boost::signals2::signal<void(const std::uint32_t code, const std::string error, const bool success)> error;
			boost::signals2::signal<void(const std::uint32_t code, const std::string error, const bool success)> loaded;
			boost::signals2::signal<void(const std::uint32_t state)> readystatechange;
			boost::signals2::signal<void(const double progress)> sendstream;
#pragma warning(pop)

		private:
#pragma warning(push)
#pragma warning(disable: 4251)
			JSObject ondatastream_callback__;
			JSObject onerror_callback__;
			JSObject onload_callback__;
			JSObject onreadystatechange_callback__;
			JSObject onsendstream_callback__;
			std::chrono::milliseconds timeout__;

			std::map<uint32_t, std::string> httpStatusPhrase__;
#pragma warning(pop)

			void setHTTPStatusPhrase();
		};
	} // namespace Network
} // namespace Titanium

#endif  // _TITANIUM_NETWORK_HTTPCLIENT_HPP_
