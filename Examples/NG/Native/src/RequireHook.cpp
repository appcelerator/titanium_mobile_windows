/**
* Titanium for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "RequireHook.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "HAL/HAL.hpp"
#include <collection.h>

namespace TitaniumWindows_Native
{
	using namespace HAL;

	RequireHook::RequireHook()
	{
	}

	RequireHook::~RequireHook()
	{
		app__->TitaniumModulePreload -= preload__;
		app__->TitaniumModuleNames   -= names__;
	}

	void RequireHook::Register(TitaniumWindows::Application^ app)
	{
		app__ = app;
		preload__ = app__->TitaniumModulePreload += ref new TitaniumWindows::TitaniumModulePreloadHandler(this, &TitaniumWindows_Native::RequireHook::OnTitaniumModulePreload);
		names__   = app__->TitaniumModuleNames   += ref new TitaniumWindows::TitaniumModuleNamesHandler(this, &TitaniumWindows_Native::RequireHook::OnTitaniumModuleNames);

		app__->SaveRequireHook(this);
	}

	// This should return pointer to JSObject (key-value) which consists of module name & preloaded JSObject
	std::intptr_t RequireHook::OnTitaniumModulePreload(std::intptr_t js_context_ref)
	{
		const auto js_context = JSContext(reinterpret_cast<JSContextRef>(js_context_ref));

		auto js_preloaded_module_map = js_context.CreateObject();

		//// TODO: native module initialization 
		//// js_preloaded_module_map.SetProperty("com.example.test", js_context.CreateObject(JSExport<Com::Example::Test>::Class()));
		// js_preloaded_module_map.SetProperty("hyperloop", js_context.CreateObject(JSExport<Hyperloop>::Class()));

		//// INITIALLIZE PRELOADED NATIVE MODULE START
		//// INITIALLIZE PRELOADED NATIVE MODULE END

		return reinterpret_cast<std::intptr_t>(static_cast<JSValueRef>(js_preloaded_module_map));
	}

	// This should return collections of supported name module names such as Windows.UI.Xaml.Controls.Button etc.
	Windows::Foundation::Collections::IVector<Platform::String^>^ RequireHook::OnTitaniumModuleNames(int js_context_ref)
	{
		auto names = ref new ::Platform::Collections::Vector<::Platform::String^>();

		//// INSERT SUPPORTED NATIVE MODULE NAMES START
		//// names->Append("com.example.test");
		names->Append("hyperloop");
		names->Append("System.Math");
		names->Append("System.Object");
		names->Append("System.String");
		names->Append("Windows.UI.Xaml.Controls.Button");
		names->Append("Windows.System.MemoryManager");
		//// INSERT SUPPORTED NATIVE MODULE NAMES END

		return names;
	}
} // namespace TitaniumWindows