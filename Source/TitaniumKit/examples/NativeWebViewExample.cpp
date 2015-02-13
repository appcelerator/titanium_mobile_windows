/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeWebViewExample.hpp"

NativeWebViewExample::NativeWebViewExample(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::WebView(js_context, arguments)
{
	TITANIUM_LOG_DEBUG("NativeWebViewExample:: ctor ", this);
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
