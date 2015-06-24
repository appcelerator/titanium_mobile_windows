/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/TiModule.hpp"

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

	void TiModule::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
	{
		Titanium::TiModule::postCallAsConstructor(js_context, arguments);
		version__ = loadVersion(js_context, "__TITANIUM_VERSION__");
	}

	void TiModule::JSExportInitialize()
	{
		JSExport<TiModule>::SetClassVersion(1);
		JSExport<TiModule>::SetParent(JSExport<Titanium::TiModule>::Class());
	}

	std::string TiModule::loadVersion(const JSContext& context, const std::string& defaultValue)
	{
		// FIXME Code copied from AppModule!!!
		// Statically create json JSValue to load _app_info_.json once
		static JSValue json = context.CreateUndefined();

		// Statically create loadJson javascript function
		static JSFunction loadJson = context.CreateFunction(
			"var file = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory+Ti.Filesystem.separator+'_app_info_.json');"
			"if (file.exists()) return JSON.parse(file.read().text);"
			);

		// Statically create readJson javascript function
		static JSFunction readJson = context.CreateFunction(
			"if (json != undefined && property in json) return json[property];"
			"return null;",
			{ "json", "property" }
		);

		// Load _app_info_.json
		if (json.IsUndefined()) json = loadJson(context.get_global_object());

		// Read property
		std::vector<JSValue> args = { json, context.CreateString("sdkVersion") };
		auto result = readJson(args, context.get_global_object());

		// Return property value if it exists
		if (!result.IsNull()) {
			return static_cast<std::string>(result);
		} else {
			return defaultValue;
		}
	}

	std::string TiModule::version() const TITANIUM_NOEXCEPT
	{
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
