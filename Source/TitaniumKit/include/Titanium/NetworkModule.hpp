/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_NETWORK_HPP_
#define _TITANIUM_NETWORK_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Network/HTTPClient.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
      @class
      @discussion This is the Ti.Network Module.
      See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Network
    */
	class TITANIUMKIT_EXPORT NetworkModule : public Module, public JSExport<NetworkModule>
	{
	public:
		/*!
		  @method
		  @abstract createHTTPClient 
		  @discussion Returns a HTTP object allowing users to make http request and query the HTTP object.
		*/
		virtual JSObject createHTTPClient(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		NetworkModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

		virtual ~NetworkModule() = default;
		NetworkModule(const NetworkModule&) = default;
		NetworkModule& operator=(const NetworkModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		NetworkModule(NetworkModule&&) = default;
		NetworkModule& operator=(NetworkModule&&) = default;
#endif

		static void JSExportInitialize();

		JSObject js_createHTTPClient(const std::vector<JSValue>& arguments, JSObject& this_object);
	};
} // namespace Titanium

#endif  // _TITANIUM_NETWORK_HPP_
