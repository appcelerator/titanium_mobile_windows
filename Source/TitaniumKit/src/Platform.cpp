/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Platform.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium {

	Platform::Platform(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context) {
	}

	Platform::Platform(const Platform& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Module(rhs, arguments) {
	}

	std::string Platform::osname() const TITANIUM_NOEXCEPT{
		return "Platform::osname: Unimplemented";
	}

	std::string Platform::createUUID() TITANIUM_NOEXCEPT{
		return "Platform::createUUID: Unimplemented";
	}

	// TODO: The following functions can automatically be generated from
	// the YAML Platform docs.

	JSValue Platform::get_osname_ArgumentValidator() const TITANIUM_NOEXCEPT {
		return get_context().CreateString(osname());
	}

	JSValue Platform::createUUIDArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT{
		return get_context().CreateString(createUUID());
	}

	void Platform::JSExportInitialize() {
	JSExport<Platform>::SetClassVersion(1);
	JSExport<Platform>::SetParent(JSExport<Module>::Class());
	JSExport<Platform>::AddValueProperty("osname", std::mem_fn(&Platform::get_osname_ArgumentValidator));
	JSExport<Platform>::AddFunctionProperty("createUUID", std::mem_fn(&Platform::createUUIDArgumentValidator));
	}

} // namespace Titanium
