/**
 * Titanium for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows.hpp"

#include "TitaniumWindows/GlobalObject.hpp"
#include "TitaniumWindows/UIModule.hpp"
#include "TitaniumWindows/TiModule.hpp"
#include "TitaniumWindows/API.hpp"
#include "TitaniumWindows/UI.hpp"
#include "TitaniumWindows/Utils.hpp"
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

#define GET_TITANIUM_APP(VARNAME) \
  JSValue Titanium_property = js_context__.get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue App_property = Titanium.GetProperty("App"); \
  TITANIUM_ASSERT(App_property.IsObject()); \
  std::shared_ptr<Titanium::AppModule> VARNAME = static_cast<JSObject>(App_property).GetPrivate<Titanium::AppModule>();

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
		                                                            .TiObject(js_context__.CreateObject(JSExport<TitaniumWindows::TiModule>::Class()))
		                                                            .UIObject(js_context__.CreateObject(JSExport<TitaniumWindows::UIModule>::Class()))
		                                                            .APIObject(js_context__.CreateObject(JSExport<TitaniumWindows::API>::Class()))
		                                                            .AppObject(js_context__.CreateObject(JSExport<TitaniumWindows::AppModule>::Class()))
		                                                            .PlatformObject(js_context__.CreateObject(JSExport<TitaniumWindows::Platform>::Class()))
		                                                            .GestureObject(js_context__.CreateObject(JSExport<TitaniumWindows::Gesture>::Class()))
		                                                            .AccelerometerObject(js_context__.CreateObject(JSExport<TitaniumWindows::Accelerometer>::Class()))
		                                                            .ViewObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::View>::Class()))
		                                                            .SwitchObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::Switch>::Class()))
		                                                            .UtilsObject(js_context__.CreateObject(JSExport<TitaniumWindows::Utils>::Class()))
		                                                            .PropertiesObject(js_context__.CreateObject(JSExport<TitaniumWindows::App::Properties>::Class()))
		                                                            .EmailDialogObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::EmailDialog>::Class()))
		                                                            .WindowObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::Window>::Class()))
		                                                            .ButtonObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::Button>::Class()))
		                                                            .AlertDialogObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::AlertDialog>::Class()))
		                                                            .ImageViewObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::ImageView>::Class()))
		                                                            .LabelObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::Label>::Class()))
		                                                            .ScrollViewObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::ScrollView>::Class()))
		                                                            .SliderObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::Slider>::Class()))
		                                                            .TextFieldObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::TextField>::Class()))
		                                                            .ListViewObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::ListView>::Class()))
		                                                            .BlobObject(js_context__.CreateObject(JSExport<TitaniumWindows::Blob>::Class()))
		                                                            .FilesystemObject(js_context__.CreateObject(JSExport<TitaniumWindows::FilesystemModule>::Class()))
		                                                            .FileObject(js_context__.CreateObject(JSExport<TitaniumWindows::Filesystem::File>::Class()))
		                                                            .NetworkObject(js_context__.CreateObject(JSExport<TitaniumWindows::NetworkModule>::Class()))
		                                                            .HTTPClientObject(js_context__.CreateObject(JSExport<TitaniumWindows::Network::HTTPClient>::Class()))
		                                                            .WebViewObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::WebView>::Class()))
		                                                            .MapViewObject(js_context__.CreateObject(JSExport<TitaniumWindows::Map::View>::Class()))
		                                                            .MapAnnotationObject(js_context__.CreateObject(JSExport<TitaniumWindows::Map::Annotation>::Class()))
		                                                            .TableViewObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::TableView>::Class()))
		                                                            .TableViewRowObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::TableViewRow>::Class()))
		                                                            .ActivityIndicatorObject(js_context__.CreateObject(JSExport<TitaniumWindows::UI::ActivityIndicator>::Class()))
		                                                            .build());

		Suspending += ref new Windows::UI::Xaml::SuspendingEventHandler(this, &Application::OnSuspending);
		Resuming += ref new Windows::Foundation::EventHandler<::Platform::Object ^>(this, &Application::OnResuming);

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

	void Application::OnResuming(Object ^sender, Object ^args) 
	{
		// Since we only have "resuming" event, we fires both resume and resumed event.
		GET_TITANIUM_APP(App);
		App->fireEvent("resume");
		App->fireEvent("resumed");
	}

	void Application::OnSuspending(Object ^ sender, Windows::ApplicationModel::SuspendingEventArgs ^ e)
	{
		// Since we only have "suspending" event, we fires both pause and paused event.
		GET_TITANIUM_APP(App);
		App->fireEvent("pause");
		App->fireEvent("paused");
	}

}  // namespace TitaniumWindows
