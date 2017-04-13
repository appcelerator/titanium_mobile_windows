/**
* Require Hook
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUM_MOBILE_WINDOWS_REQUIREHOOK_HPP_
#define _TITANIUM_MOBILE_WINDOWS_REQUIREHOOK_HPP_

#include <cstdint>
#include "WindowsNativeModuleLoader.hpp"

namespace TitaniumWindows_Native
{
	public ref class RequireHook sealed
	{
	public:
		RequireHook();
		virtual ~RequireHook();

		Windows::Foundation::Collections::IVector<Platform::String^>^ OnTitaniumModuleNames(std::intptr_t js_context_ref);
		std::intptr_t OnTitaniumModuleRequire(std::intptr_t js_context_ref, Platform::String^ moduleId);
		std::intptr_t OnTitaniumModulePreload(std::intptr_t js_context_ref);
		std::intptr_t OnNativeUIWrap(std::intptr_t js_context_ref, std::intptr_t js_object_ref);

		void Register(TitaniumWindows::Application^ app);

	private:
		Windows::Foundation::EventRegistrationToken preload__;
		Windows::Foundation::EventRegistrationToken require__;
		Windows::Foundation::EventRegistrationToken names__;
		Windows::Foundation::EventRegistrationToken ui_cast__;
		TitaniumWindows::Application^ app__;

#pragma warning(push)
#pragma warning(disable : 4251)
		std::shared_ptr<TitaniumWindows::WindowsNativeModuleLoader> native_module_loader__;
#pragma warning(pop)	
	};
}  // namespace TitaniumWindows

#endif  // _TITANIUM_MOBILE_WINDOWS_REQUIREHOOK_HPP_
