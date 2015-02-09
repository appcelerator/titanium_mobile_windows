/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeButtonExample.hpp"

NativeButtonExample::NativeButtonExample(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::Button(js_context), Titanium::UI::UIBase(js_context)
{
	TITANIUM_LOG_DEBUG("NativeButtonExample:: ctor ", this);
}

NativeButtonExample::~NativeButtonExample() TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeButtonExample:: dtor ", this);
}

void NativeButtonExample::JSExportInitialize()
{
	JSExport<NativeButtonExample>::SetClassVersion(1);
	JSExport<NativeButtonExample>::SetParent(JSExport<Titanium::UI::Button>::Class());
}

void NativeButtonExample::set_title(const std::string& title) TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_WARN("NativeButtonExample::set_title");
}
