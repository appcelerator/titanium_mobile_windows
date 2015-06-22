/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/TiModule.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>
#include <objbase.h>

namespace TitaniumWindows
{
	TiModule::TiModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::TiModule(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::TiModule::ctor");
		setUserAgent("__TITANIUM_USER_AGENT__");
	}

	TiModule::~TiModule()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::TiModule::dtor");
	}

	void TiModule::JSExportInitialize()
	{
		JSExport<TiModule>::SetClassVersion(1);
		JSExport<TiModule>::SetParent(JSExport<Titanium::TiModule>::Class());
	}

	std::string TiModule::version() const TITANIUM_NOEXCEPT
	{
		// lazily load the SDK version
		if (version__.empty()) {
			// FIXME Code copied from AppModule!!!
			// Statically create json JSValue to load _app_info_.json once
			static JSValue json = get_context().CreateUndefined();

			// Statically create loadJson javascript function
			static JSFunction loadJson = get_context().CreateFunction(
				"var file = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory+Ti.Filesystem.separator+'_app_info_.json');"
				"if (file.exists()) return JSON.parse(file.read().text);"
			);

			// Statically create readJson javascript function
			static JSFunction readJson = get_context().CreateFunction(
				"if (json != undefined && property in json) return json[property];"
				"return null;",
				{"json", "property"}
			);

			// Load _app_info_.json
			if (json.IsUndefined()) json = loadJson(get_context().get_global_object());

			// Read property
			std::vector<JSValue> args = {json, get_context().CreateString("sdkVersion")};
			auto result = readJson(args, get_context().get_global_object());
			
			// Return property value if it exists
			if (!result.IsNull()) {
				version__ = static_cast<std::string>(result);
				return version__;
			}
			return "__TITANIUM_VERSION__";
		}
		return version__;
	}

	std::string TiModule::buildDate() const TITANIUM_NOEXCEPT
	{
		return "__TITANIUM_BUILD_DATE__";
	}

	std::string TiModule::buildHash() const TITANIUM_NOEXCEPT
	{
		return "__TITANIUM_BUILD_HASH__";
	}

}  // namespace TitaniumWindows
