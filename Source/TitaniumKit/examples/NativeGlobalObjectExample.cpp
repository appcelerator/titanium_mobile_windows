/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGlobalObjectExample.hpp"
#include "Titanium/detail/TiLogger.hpp"

void NativeGlobalObjectExample::add_require(const std::string& name, const std::string& body) TITANIUM_NOEXCEPT
{
	require_resource__.insert({name, body});
}

bool NativeGlobalObjectExample::requiredModuleExists(const std::string& path) const TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("GlobalObjectDelegateExample::requiredModuleExists for ", path);
	return (require_resource__.find(path) != require_resource__.end());
}

std::string NativeGlobalObjectExample::readRequiredModule(const JSObject& parent, const std::string& path) const
{
	TITANIUM_LOG_DEBUG("GlobalObjectDelegateExample::loadRequiredModule for ", path);
	if (require_resource__.find(path) == require_resource__.end()) {
		return "";
	}
	return require_resource__.at(path);
}

NativeGlobalObjectExample::NativeGlobalObjectExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::GlobalObject(js_context)
{
	TITANIUM_LOG_DEBUG("NativeGlobalObjectExample:: ctor ", this);
}

NativeGlobalObjectExample::~NativeGlobalObjectExample() TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeGlobalObjectExample:: dtor ", this);
}

void NativeGlobalObjectExample::JSExportInitialize()
{
	JSExport<NativeGlobalObjectExample>::SetClassVersion(1);
	JSExport<NativeGlobalObjectExample>::SetParent(JSExport<Titanium::GlobalObject>::Class());
}
