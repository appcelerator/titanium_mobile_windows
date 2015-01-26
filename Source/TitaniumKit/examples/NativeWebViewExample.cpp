/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeWebViewExample.hpp"

NativeWebViewExample::NativeWebViewExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::WebView(js_context)
{
	TITANIUM_LOG_DEBUG("NativeWebViewExample:: ctor 1 ", this);
}

NativeWebViewExample::NativeWebViewExample(const NativeWebViewExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::WebView(rhs, arguments)
{
	TITANIUM_LOG_DEBUG("NativeWebViewExample:: ctor 2 ", this);
}

NativeWebViewExample::~NativeWebViewExample() TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeWebViewExample:: dtor ", this);
}

bool NativeWebViewExample::canGoBack() TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeWebViewExample::canGoBack");
	return false;
}

void NativeWebViewExample::JSExportInitialize()
{
	JSExport<NativeWebViewExample>::SetClassVersion(1);
	JSExport<NativeWebViewExample>::SetParent(JSExport<Titanium::UI::WebView>::Class());
}
