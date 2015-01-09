/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativePlatformExample.hpp"
#include "NativePlatformDisplayCapsExample.hpp"
#include <iostream>

NativePlatformExample::NativePlatformExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::PlatformModule(js_context)
{
	setDisplayCaps(get_context().CreateObject(JSExport<NativePlatformDisplayCapsExample>::Class()));
}

NativePlatformExample::NativePlatformExample(const NativePlatformExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::PlatformModule(rhs, arguments)
{
}

std::string NativePlatformExample::osname() const TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("PlatformDelegateExample::osname");
	return "osx";
}

void NativePlatformExample::JSExportInitialize()
{
	JSExport<NativePlatformExample>::SetClassVersion(1);
	JSExport<NativePlatformExample>::SetParent(JSExport<Titanium::PlatformModule>::Class());
}
