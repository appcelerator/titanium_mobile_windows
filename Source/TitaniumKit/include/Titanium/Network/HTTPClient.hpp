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
			  @abstract setTimeout
			  @discussion Set the duration allowed for the HTTP request to succeed.
			*/
			virtual void setTimeout(const std::chrono::milliseconds& timeout) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getResponseText
			  @discussion Get the text value of the HTTP response.
			*/
			virtual std::string getResponseText() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getResponseData
			  @discussion Get the binary value of the HTTP response.
			*/
			virtual std::vector<unsigned char> getResponseData() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getAllResponseHeaders
			  @discussion Get the response header values as a collection of key:value pairs.
			*/
			virtual std::string getAllResponseHeaders() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getReadyState
			  @discussion Get the state of the HTTP request.
			*/
			virtual std::uint32_t getReadyState() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getStatus
			  @discussion Get the status of the HTTP request as returned from the server.
			*/
			virtual std::uint32_t getStatus() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getStatus
			  @discussion Get the status as text of the HTTP request as returned from the server.
			*/
			virtual std::string getStatusText() const TITANIUM_NOEXCEPT;

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
			virtual void send(const std::map<std::string, std::vector<unsigned char>>& postDataPairs, const bool& useMultipartForm) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract send
			  @discussion Do an HTTP POST or PUT request with data type text in body.
			*/
			virtual void send(const std::string& postDataStr) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract abort
			  @discussion Cancel the current HTTP request.
			*/
			virtual void abort() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract setRequestHeader
			  @discussion Set the header key:value pair sent to the server.
			*/
			virtual void setRequestHeader(const std::string& key, const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getResponseHeader
			  @discussion Get the header based on the key name.
			*/
			virtual std::string getResponseHeader(const std::string& key) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract clearCookies
			  @discussion Delete all cookies associated with the domain (url).
			*/
			virtual void clearCookies(const std::string& url) TITANIUM_NOEXCEPT;

			HTTPClient(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~HTTPClient() = default;
			HTTPClient(const HTTPClient&) = default;
			HTTPClient& operator=(const HTTPClient&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			HTTPClient(HTTPClient&&) = default;
			HTTPClient& operator=(HTTPClient&&) = default;
#endif

			static void JSExportInitialize();

			/////// constant properties
			virtual JSValue js_getLOADING() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOPENED() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getDONE() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getUNSENT() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHEADERS_RECEIVED() const TITANIUM_NOEXCEPT final;

			/////// properties
			virtual bool js_setTimeout(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getTimeout() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getResponseText() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getResponseData() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getAllResponseHeaders() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getReadyState() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getStatus() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getStatusText() const TITANIUM_NOEXCEPT final;
			virtual bool js_setOnLoad(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOnLoad() const TITANIUM_NOEXCEPT final;
			virtual bool js_setOnError(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOnError() const TITANIUM_NOEXCEPT final;
			virtual bool js_setOnDataStream(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOnDataStream() const TITANIUM_NOEXCEPT final;
			virtual bool js_setOnSendStream(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOnSendStream() const TITANIUM_NOEXCEPT final;
			virtual bool js_setOnReadyStateChange(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOnReadyStateChange() const TITANIUM_NOEXCEPT final;

			/////// methods
			virtual JSValue js_open(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_send(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_abort(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setRequestHeader(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getResponseHeader(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_clearCookies(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

			/////// slots
			virtual void onload(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT final;
			virtual void onerror(const std::uint32_t id, const std::string error, const bool success) TITANIUM_NOEXCEPT final;
			virtual void ondatastream(const std::uint32_t progress) TITANIUM_NOEXCEPT final;
			virtual void onsendstream(const std::uint32_t progress) TITANIUM_NOEXCEPT final;
			virtual void onreadystatechange(const std::uint32_t state) TITANIUM_NOEXCEPT final;

			/////// signals
#pragma warning(push)
#pragma warning(disable: 4251)
			boost::signals2::signal<void(const std::uint32_t id, const std::string error, const bool success)> loaded;
			boost::signals2::signal<void(const std::uint32_t id, const std::string error, const bool success)> error;
			boost::signals2::signal<void(const std::uint32_t progress)> datastream;
			boost::signals2::signal<void(const std::uint32_t progress)> sendstream;
			boost::signals2::signal<void(const std::uint32_t state)> readystatechange;
#pragma warning(pop)

		private:
			JSValue timeout__;
			JSObject onload_callback__;
			JSObject onerror_callback__;
			JSObject ondatastream_callback__;
			JSObject onsendstream_callback__;
			JSObject onreadystatechange_callback__;
		};
	} // namespace Network
} // namespace Titanium

#endif  // _TITANIUM_NETWORK_HTTPCLIENT_HPP_
