/**
 * Titanium for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows.hpp"

#include "TitaniumWindows/GlobalObject.hpp"
#include "TitaniumWindows/TiModule.hpp"
#include "TitaniumWindows/API.hpp"
#include "TitaniumWindows/UI.hpp"
#include "TitaniumWindows/App.hpp"
#include "TitaniumWindows/Platform.hpp"
#include "TitaniumWindows/Gesture.hpp"
#include "TitaniumWindows/Accelerometer.hpp"
#include "TitaniumWindows/Filesystem.hpp"
#include "TitaniumWindows/Network.hpp"
#include "TitaniumWindows/Map.hpp"
#include "Blob.hpp"
#include "File.hpp"
#include "HTTPClient.hpp"

#include <Windows.h>
#include <collection.h>

namespace TitaniumWindows
{
	using namespace HAL;

	Application::Application()
	    : js_context__(js_context_group__.CreateContext(JSExport<TitaniumWindows::GlobalObject>::Class()))
	{
	}

	Application::~Application()
	{
	}

	void Application::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs ^ args)
	{
		application__ = std::make_shared<Titanium::Application>(Titanium::ApplicationBuilder(js_context__)
		                                                            .TiObject(js_context__.CreateObject<TitaniumWindows::TiModule>())
		                                                            .APIObject(js_context__.CreateObject<TitaniumWindows::API>())
		                                                            .PlatformObject(js_context__.CreateObject<TitaniumWindows::Platform>())
		                                                            .GestureObject(js_context__.CreateObject<TitaniumWindows::Gesture>())
		                                                            .AccelerometerObject(js_context__.CreateObject<TitaniumWindows::Accelerometer>())
		                                                            .ViewObject(js_context__.CreateObject<TitaniumWindows::UI::View>())
		                                                            .PropertiesObject(js_context__.CreateObject<TitaniumWindows::App::Properties>())
		                                                            .EmailDialogObject(js_context__.CreateObject<TitaniumWindows::UI::EmailDialog>())
		                                                            .WindowObject(js_context__.CreateObject<TitaniumWindows::UI::Window>())
		                                                            .ButtonObject(js_context__.CreateObject<TitaniumWindows::UI::Button>())
		                                                            .AlertDialogObject(js_context__.CreateObject<TitaniumWindows::UI::AlertDialog>())
		                                                            .ImageViewObject(js_context__.CreateObject<TitaniumWindows::UI::ImageView>())
		                                                            .LabelObject(js_context__.CreateObject<TitaniumWindows::UI::Label>())
		                                                            .ScrollViewObject(js_context__.CreateObject<TitaniumWindows::UI::ScrollView>())
		                                                            .SliderObject(js_context__.CreateObject<TitaniumWindows::UI::Slider>())
		                                                            .TextFieldObject(js_context__.CreateObject<TitaniumWindows::UI::TextField>())
		                                                            .ListViewObject(js_context__.CreateObject<TitaniumWindows::UI::ListView>())
		                                                            .BlobObject(js_context__.CreateObject<TitaniumWindows::Blob>())
		                                                            .FilesystemObject(js_context__.CreateObject<TitaniumWindows::FilesystemModule>())
		                                                            .FileObject(js_context__.CreateObject<TitaniumWindows::Filesystem::File>())
		                                                            .NetworkObject(js_context__.CreateObject<TitaniumWindows::NetworkModule>())
		                                                            .HTTPClientObject(js_context__.CreateObject<TitaniumWindows::Network::HTTPClient>())
		                                                            .WebViewObject(js_context__.CreateObject<TitaniumWindows::UI::WebView>())
		                                                            .MapViewObject(js_context__.CreateObject<TitaniumWindows::Map::View>())
		                                                            .build());

		Suspending += ref new Windows::UI::Xaml::SuspendingEventHandler(this, &Application::OnSuspending);

		// #if _DEBUG
		//  if (IsDebuggerPresent()) {
		//    DebugSettings -> EnableFrameRateCounter = true;
		//  }
		// #endif

		auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame ^>(Windows::UI::Xaml::Window::Current->Content);
		// Do not repeat initialization when the Window already has content,
		// just ensure that the window is active.
		if (rootFrame == nullptr) {
			rootFrame = ref new Windows::UI::Xaml::Controls::Frame();

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
			// This code is for Windows phone apps only. Remove the turnstile
			// navigation for startup.
			if (rootFrame->ContentTransitions != nullptr) {
				transitions__ = ref new Windows::UI::Xaml::Media::Animation::TransitionCollection();
				for (auto transition : rootFrame->ContentTransitions) {
					transitions__->Append(transition);
				}
			}

			rootFrame->ContentTransitions = nullptr;
			first_navigated_token__ = rootFrame->Navigated += ref new Windows::UI::Xaml::Navigation::NavigatedEventHandler(this, &Application::RootFrame_FirstNavigated);
#endif

			if (rootFrame->Content == nullptr) {
				TITANIUM_LOG_DEBUG("MDL: rootFrame -> Content == nullptr");
			}

			// Create a Frame to act as the navigation context and associate
			// it with a SuspensionManager key.

			// TODO: Change this value to a cache size that is appropriate for
			// your application.
			rootFrame->CacheSize = 1;

			if (args->PreviousExecutionState == Windows::ApplicationModel::Activation::ApplicationExecutionState::Terminated) {
				// TODO: Restore the saved session state only when appropriate,
				// scheduling the final launch steps after the restore is
				// complete.
			}

			// Place the frame in the current Window.
			Windows::UI::Xaml::Window::Current->Content = rootFrame;
			application__->Run("./app");
		}
		// Ensure the current Window is active.
		Windows::UI::Xaml::Window::Current->Activate();
	}

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
	// This code is for Windows phone apps only. Restore the content
	// transitions after the application has launched.
	void Application::RootFrame_FirstNavigated(::Platform::Object ^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
	{
		auto rootFrame = safe_cast<Windows::UI::Xaml::Controls::Frame ^>(sender);

		Windows::UI::Xaml::Media::Animation::TransitionCollection ^ newTransitions;
		if (transitions__ == nullptr) {
			newTransitions = ref new Windows::UI::Xaml::Media::Animation::TransitionCollection();
			newTransitions->Append(ref new Windows::UI::Xaml::Media::Animation::NavigationThemeTransition());
		} else {
			newTransitions = transitions__;
		}

		rootFrame->ContentTransitions = newTransitions;
		rootFrame->Navigated -= first_navigated_token__;
	}
#endif

	void Application::OnSuspending(Object ^ sender, Windows::ApplicationModel::SuspendingEventArgs ^ e)
	{
	}

}  // namespace TitaniumWindows
