/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListViewExample.hpp"

NativeListViewExample::NativeListViewExample(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::ListView(js_context)
{
	TITANIUM_LOG_DEBUG("NativeListViewExample:: ctor ", this);
}

NativeListViewExample::~NativeListViewExample() TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeListViewExample:: dtor ", this);
}

void NativeListViewExample::JSExportInitialize()
{
	JSExport<NativeListViewExample>::SetClassVersion(1);
	JSExport<NativeListViewExample>::SetParent(JSExport<Titanium::UI::ListView>::Class());
}
