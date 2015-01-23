/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/WebViewErrorEvent.hpp"
#include <type_traits>

namespace Titanium
{
	namespace UI
	{
		WebViewErrorEvent::WebViewErrorEvent(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : JSExportObject(js_context),
		      error__(URL_ERROR::UNKNOWN)
		{
		}

		WebViewErrorEvent::WebViewErrorEvent(const WebViewErrorEvent& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : JSExportObject(rhs.get_context(), arguments),
		      error__(rhs.error__)
		{
		}

		URL_ERROR WebViewErrorEvent::get_error() const TITANIUM_NOEXCEPT
		{
			return error__;
		}

		void WebViewErrorEvent::set_error(const URL_ERROR& error) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebViewErrorEvent::set_error: Unimplemented");
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void WebViewErrorEvent::JSExportInitialize()
		{
			JSExport<WebViewErrorEvent>::SetClassVersion(1);
			JSExport<WebViewErrorEvent>::SetParent(JSExport<JSExportObject>::Class());
			JSExport<WebViewErrorEvent>::AddValueProperty("error", std::mem_fn(&WebViewErrorEvent::js_get_error), std::mem_fn(&WebViewErrorEvent::js_set_error));
		}

		JSValue WebViewErrorEvent::js_get_error() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<URL_ERROR>::type>(get_error()));
		}

		bool WebViewErrorEvent::js_set_error(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			error__ = Constants::to_URL_ERROR(static_cast<std::underlying_type<URL_ERROR>::type>(argument));
			set_error(error__);
			return true;
		}
	} // namespace UI
}  // namespace Titanium
