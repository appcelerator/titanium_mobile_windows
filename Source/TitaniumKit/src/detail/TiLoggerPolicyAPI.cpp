/**
 * TiLoggerPolicyAPI
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiLoggerPolicyAPI.hpp"
#include "Titanium/API.hpp"

namespace Titanium
{
	namespace detail
	{
		TiLoggerPolicyAPI::TiLoggerPolicyAPI(const JSContext& js_context) :
			js_context__(js_context)
		{
			try {
				auto api = js_context__.JSEvaluateScript("Titanium.API");
				if (api.IsObject()) {
					api__ = static_cast<JSObject>(api).GetPrivate<Titanium::API>();
				}
			} catch (...) {
				// make sure logging does not throw any exception
			}
		}

		void TiLoggerPolicyAPI::Write(const std::string& message)
		{
			if (api__) {
				api__->log(message);
			} else {
				// defaults to std::clog
				std::clog << message << std::endl;
			}
		}
	} // namespace detail
}  // namespace Titanium
