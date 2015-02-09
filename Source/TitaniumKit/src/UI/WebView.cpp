/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/WebView.hpp"
#include <type_traits>

namespace Titanium
{
	namespace UI
	{
		WebView::WebView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : UIBase(js_context)
		{
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void WebView::JSExportInitialize()
		{
			JSExport<WebView>::SetClassVersion(1);
			JSExport<WebView>::SetParent(JSExport<UIBase>::Class());
		}
	} // namespace UI
}  // namespace Titanium
