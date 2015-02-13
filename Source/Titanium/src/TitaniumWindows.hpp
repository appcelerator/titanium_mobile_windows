/**
 * Titanium for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _APPLICATION_TITANIUMWINDOWS_HPP_
#define _APPLICATION_TITANIUMWINDOWS_HPP_

#include "Titanium/Titanium.hpp"

namespace TitaniumWindows
{
public
	ref class Application sealed : public Windows::UI::Xaml::Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) override;

	private:
		void OnSuspending(Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		// This code is for Windows phone apps only.
		void RootFrame_FirstNavigated(::Platform::Object^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);

		Windows::UI::Xaml::Media::Animation::TransitionCollection^ transitions__;
		Windows::Foundation::EventRegistrationToken first_navigated_token__;
#endif

		HAL::JSContextGroup js_context_group__;
		HAL::JSContext js_context__;
		std::shared_ptr<Titanium::Application> application__;
	};

}  // namespace TitaniumWindows

#endif  // _APPLICATION_TITANIUMWINDOWS_HPP_
