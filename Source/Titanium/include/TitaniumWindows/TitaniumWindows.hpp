/**
 * Titanium for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _APPLICATION_TITANIUMWINDOWS_HPP_
#define _APPLICATION_TITANIUMWINDOWS_HPP_

#include "HAL/HAL.hpp"
#include "TitaniumWindows/TitaniumApplicationCallback.hpp"
#include <unordered_map>

namespace Titanium
{
	class Application;
}

namespace TitaniumWindows
{
	public ref class Application sealed : public Windows::UI::Xaml::Application
	{
	public:
		Application();
		Application(::Platform::String^ seed);
		virtual ~Application();

		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) override;
		void OnSuspending(Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
		void OnResuming(Object ^sender, Object ^args);

		event TitaniumModulePreloadHandler^ TitaniumModulePreload;
		event TitaniumModuleNamesHandler^   TitaniumModuleNames;

		// Used just for saving reference to TitaniumWindows_Native::RequireHook to prevent from GC
		void SaveRequireHook(Object^ requireHook) {
			this->requireHook__ = requireHook;
		}

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		virtual void OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs^ args) override;
#endif

	private:
		void OnUnhandledException(Object^ sender, Windows::UI::Xaml::UnhandledExceptionEventArgs^ arg);

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		// This code is for Windows phone apps only.
		void RootFrame_FirstNavigated(::Platform::Object^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);

		Windows::UI::Xaml::Media::Animation::TransitionCollection^ transitions__;
		Windows::Foundation::EventRegistrationToken first_navigated_token__;
#endif

		HAL::JSContextGroup js_context_group__;
		HAL::JSContext js_context__;
		std::shared_ptr<Titanium::Application> application__;

		Object^ requireHook__;
	};

}  // namespace TitaniumWindows

#endif  // _APPLICATION_TITANIUMWINDOWS_HPP_
