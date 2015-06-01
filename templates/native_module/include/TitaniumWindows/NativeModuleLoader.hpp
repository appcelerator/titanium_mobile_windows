/**
 * NativeModuleLoader for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_NATIVE_MODULE_LOADER_HPP_
#define _TITANIUMWINDOWS_NATIVE_MODULE_LOADER_HPP_

#include "TitaniumWindows/detail/GlobalBase.hpp"
#include <unordered_map>

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the callback mechanism to laod up a native type using require!
	*/
	class TITANIUMWINDOWS_GLOBAL_EXPORT NativeModuleLoader
	{
	public:
		NativeModuleLoader() TITANIUM_NOEXCEPT = default;
		virtual ~NativeModuleLoader() = default;

		void    preload(const JSContext& js_context);
		bool    exists(const JSContext& js_context, const std::string& moduleId);
		JSValue load(const JSContext& js_context, const std::string& moduleId);

	private:
#pragma warning(push)
#pragma warning(disable : 4251)
		std::unordered_map<std::string, JSValue> module_cache__;
#pragma warning(pop)

	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_NATIVE_MODULE_LOADER_HPP_
