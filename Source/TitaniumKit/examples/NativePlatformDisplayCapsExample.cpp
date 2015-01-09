/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativePlatformDisplayCapsExample.hpp"
#include <iostream>

NativePlatformDisplayCapsExample::NativePlatformDisplayCapsExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::Platform::DisplayCaps(js_context)
{
	TITANIUM_LOG_DEBUG("NativePlatformDisplayCapsExample::ctor");
}

NativePlatformDisplayCapsExample::NativePlatformDisplayCapsExample(const NativePlatformDisplayCapsExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::Platform::DisplayCaps(rhs, arguments)
{
}

void NativePlatformDisplayCapsExample::JSExportInitialize()
{
	JSExport<NativePlatformDisplayCapsExample>::SetClassVersion(1);
	JSExport<NativePlatformDisplayCapsExample>::SetParent(JSExport<Titanium::Platform::DisplayCaps>::Class());
}
