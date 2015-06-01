/**
 * NativeModuleLoader for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/detail/GlobalBase.hpp"
#include "TitaniumWindows/NativeModuleLoader.hpp"

/* NATIVE_MODULE_INCLUDES_START */
/*
<% for(var i=0; i<native_module_includes.length; i++) { -%>
#include "<%= native_module_includes[i] %>"
<% } -%>
*/
/* NATIVE_MODULE_INCLUDES_END */

namespace TitaniumWindows
{
	using namespace HAL;

	void NativeModuleLoader::preload(const JSContext& js_context) 
	{
		/*
		 * Preload modules here
		 *
		 * module_cache__.emplace("Windows.UI.Xaml.Controls.Button", js_context.CreateObject(JSExport<TitaniumWindows::Windows.UI.Xaml.Controls.Button>::Class()));
		 */
		 
		/* NATIVE_MODULE_PRELOAD_START */
/*
<% for(var i=0; i<native_modules.length; i++) { -%>
  <% if (native_modules[i].preload) { -%>
  		module_cache__.emplace("<%= native_modules[i].name %>", js_context.CreateObject(JSExport<<%= native_modules[i].className %>>::Class()));
  <% } -%>
<% } -%>
*/
		/* NATIVE_MODULE_PRELOAD_END */

	}

	bool NativeModuleLoader::exists(const JSContext& js_context, const std::string& moduleId) 
	{
		// check if it's already cached
		if (module_cache__.find(moduleId) != module_cache__.end()) {
			return true;
		}

		/*
		 * Return true when moduleId is supported
		 *	
		 * if (moduleId == "Windows.UI.Xaml.Controls.Button") {
		 *	return true;
		 * }
		 */

		/* NATIVE_MODULE_EXISTS_START */
 /*
<% for(var i=0; i<native_modules.length; i++) { -%>
		if (moduleId == "<%= native_modules[i].name %>") {
			return true;
		}
<% } -%>
*/
		/* NATIVE_MODULE_EXISTS_END */

		return false;
	}

	JSValue NativeModuleLoader::load(const JSContext& js_context, const std::string& moduleId) 
	{
		if (module_cache__.find(moduleId) != module_cache__.end()) {
			return module_cache__.at(moduleId);
		}

		/*
		 * Load the module, cahce and return the value
		 * 
		 * if (moduleId == "Windows.UI.Xaml.Controls.Button") {
		 *	auto module = js_context.CreateObject(JSExport<TitaniumWindows::Windows.UI.Xaml.Controls.Button>::Class());
		 *	module_cache__.emplace("Windows.UI.Xaml.Controls.Button", module);
		 *	return module;
		 * }
		 */

		/* NATIVE_MODULE_LOAD_START */
 /*
<% for(var i=0; i<native_modules.length; i++) { -%>
		if (moduleId == "<%= native_modules[i].name %>") {
			auto module = js_context.CreateObject(JSExport<<%= native_modules[i].className %>>::Class());
			module_cache__.emplace("<%= native_modules[i].name %>", module);
			return module;
		}
<% } -%>
*/
		/* NATIVE_MODULE_LOAD_END */

		// No module is loaded...which means "exists()" return true but no one handles that
		TITANIUM_LOG_WARN("NativeModuleLoader::load: Nothing loaded for ", moduleId);
		return js_context.CreateUndefined();
	}

}  // namespace TitaniumWindows

