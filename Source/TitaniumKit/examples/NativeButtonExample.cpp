/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeButtonExample.hpp"

NativeButtonExample::NativeButtonExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::Button(js_context)
{
	TITANIUM_LOG_DEBUG("NativeButtonExample:: ctor 1 ", this);
}

NativeButtonExample::NativeButtonExample(const NativeButtonExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::Button(rhs, arguments)
{
	TITANIUM_LOG_DEBUG("NativeButtonExample:: ctor 1 ", this);
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

bool NativeButtonExample::setTitleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
{
	assert(argument.IsString());
	std::string title = static_cast<std::string>(argument);
	TITANIUM_LOG_WARN("NativeButtonExample::setTitleArgumentValidator: title = ", title);
	set_title(argument);
	return true;
}
