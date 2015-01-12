/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeViewExample.hpp"

NativeViewExample::NativeViewExample(const JSContext& js_context) TITANIUM_NOEXCEPT
: Titanium::UI::View(js_context) {
	TITANIUM_LOG_DEBUG("NativeViewExample:: ctor 1 ", this);
}

NativeViewExample::NativeViewExample(const NativeViewExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
: Titanium::UI::View(rhs, arguments) {
	TITANIUM_LOG_DEBUG("NativeViewExample:: ctor 2 ", this);
}

NativeViewExample::~NativeViewExample() TITANIUM_NOEXCEPT {
	TITANIUM_LOG_DEBUG("NativeViewExample:: dtor ", this);
}

void NativeViewExample::JSExportInitialize() {
	JSExport<NativeViewExample>::SetClassVersion(1);
	JSExport<NativeViewExample>::SetParent(JSExport<Titanium::UI::View>::Class());
}

bool NativeViewExample::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
	assert(argument.IsString());
	bool result = false;
	std::string backgroundColor = static_cast<std::string>(argument);
	TITANIUM_LOG_INFO("NativeViewExample::setBackgroundColorArgumentValidator: backgroundColor = ", backgroundColor);
	set_backgroundColor(argument);
	result = true;
	return result;
}
