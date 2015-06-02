/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "WindowsNativeModuleLoader.hpp"
#include "Titanium/detail/TiBase.hpp"

// INSERT_INCLUDES
// END_INCLUDES

// FIXME This will only work if we generate _all_ type wrappers and include them here. Otherwise we need to move this into the user's app and limit to those types used...

namespace TitaniumWindows
{
	using namespace HAL;

	WindowsNativeModuleLoader::WindowsNativeModuleLoader()
	{
	}

	WindowsNativeModuleLoader::~WindowsNativeModuleLoader()
	{
	}

	void WindowsNativeModuleLoader::registerValue(const JSContext& context, const std::string& name, const JSValue& value) const
	{
		// FIXME If we've already hung a value at this name, we shouldn't do any of this!
		auto global = context.get_global_object();
		// Split type/path by '.', then build up the namespaces!
		JSObject current_object = global;

		std::stringstream stream(name);
		std::string segment;
		std::vector<std::string> parts;
		while(std::getline(stream, segment, '.'))
		{
		   parts.push_back(segment);
		}
		for (size_t i = 0, len = parts.size(); i < len - 1; i++) {
			auto part = parts.at(i);

			if (!current_object.HasProperty(part)) {
				auto child_object = context.CreateObject();
				current_object.SetProperty(part, child_object);
				current_object = child_object;
			} else {
				auto current_value = current_object.GetProperty(part);
				TITANIUM_ASSERT(current_value.IsObject());
				current_object = static_cast<JSObject>(current_value);
			}
		}
		// hang the actual value at the end!
		current_object.SetProperty(parts.at(parts.size() - 1), value);
	}

	void WindowsNativeModuleLoader::registerEnums(const JSContext& context, const std::string& type_name) const
	{
		// INSERT_ENUMS
		// END_ENUMS
	}

	JSValue WindowsNativeModuleLoader::registerNativeModule(const JSContext& context, const std::string& path) const
	{
		JSObject instantiated = context.CreateObject();
		// TODO Use a std::map that we populate once and just check for a key with that name?
		// INSERT_SWITCH
		// END_SWITCH

		registerValue(context, path, instantiated);

		return static_cast<JSValue>(instantiated);
	}

}  // namespace TitaniumWindows

