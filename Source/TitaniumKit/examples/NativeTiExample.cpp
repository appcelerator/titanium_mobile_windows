/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTiExample.hpp"
#include <iostream>

NativeTiExample::NativeTiExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::TiModule(js_context)
{
	setUserAgent(get_context().CreateString("__TITANIUM_USER_AGENT__"));
}

NativeTiExample::NativeTiExample(const NativeTiExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::TiModule(rhs, arguments)
{
}

std::string NativeTiExample::version() const TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeTiExample::version");
	return "__TITANIUM_VERSION__";
}

std::string NativeTiExample::buildDate() const TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeTiExample::buildDate");
	return "__TITANIUM_BUILD_DATE__";
}

std::string NativeTiExample::buildHash() const TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeTiExample::buildHash");
	return "__TITANIUM_BUILD_HASH__";
}

void NativeTiExample::JSExportInitialize()
{
	JSExport<NativeTiExample>::SetClassVersion(1);
	JSExport<NativeTiExample>::SetParent(JSExport<Titanium::TiModule>::Class());
}
