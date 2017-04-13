/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_WindowsNativeModuleLoader_HPP_
#define _TITANIUMWINDOWS_WindowsNativeModuleLoader_HPP_

#include "HAL/HAL.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	class WindowsNativeModuleLoader final
	{
	public:
		WindowsNativeModuleLoader();
		~WindowsNativeModuleLoader();

		JSValue registerNativeModule(const JSContext& context, const std::string& path) const;
		JSObject wrapNativeUI(const JSContext& context, const JSObject& object);

	private:
		void registerValue(const JSContext& context, const std::string& name, const JSValue& value) const;
		void registerEnums(const JSContext& context, const std::string& type_name) const;
	};
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_WindowsNativeModuleLoader_HPP_
