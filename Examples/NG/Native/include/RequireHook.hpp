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

namespace TitaniumWindows_Native
{
	public ref class RequireHook sealed
	{
	public:
		RequireHook();
		virtual ~RequireHook();

		Windows::Foundation::Collections::IVector<Platform::String^>^ OnTitaniumModuleNames(std::intptr_t js_context_ref);
		std::intptr_t OnTitaniumModulePreload(std::intptr_t js_context_ref);

		void Register(TitaniumWindows::Application^ app);

	private:
		Windows::Foundation::EventRegistrationToken preload__;
		Windows::Foundation::EventRegistrationToken names__;
		TitaniumWindows::Application^ app__;
	};
}  // namespace TitaniumWindows

#endif  // _TITANIUM_MOBILE_WINDOWS_REQUIREHOOK_HPP_
