/**
 * Titanium for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows.hpp"

#include "TitaniumWindows/GlobalObject.hpp"
#include "TitaniumWindows/API.hpp"
#include "TitaniumWindows/UI.hpp"
#include "TitaniumWindows/Platform.hpp"
#include "TitaniumWindows/Gesture.hpp"
#include "TitaniumWindows/Accelerometer.hpp"
#include "TitaniumWindows/Filesystem.hpp"
#include "Blob.hpp"
#include "File.hpp"

#include <Windows.h>
#include <collection.h>

namespace TitaniumWindows {

  using namespace HAL;

  Application::Application()
    : application__(Titanium::ApplicationBuilder(std::make_shared<JSClass>(JSExport<TitaniumWindows::GlobalObject>::Class()))
    .APIClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::API>::Class()))
    .PlatformClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::Platform>::Class()))
    .GestureClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::Gesture>::Class()))
    .AccelerometerClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::Accelerometer>::Class()))
    .ViewClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::UI::View>::Class()))
    .WindowClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::UI::Window>::Class()))
    .ButtonClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::UI::Button>::Class()))
    .BlobClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::Blob>::Class()))
    .FilesystemClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::FilesystemModule>::Class()))
    .FileClass(std::make_shared<JSClass>(JSExport<TitaniumWindows::Filesystem::File>::Class()))
    .build()) {
  }

  Application::~Application() {
  }

  void Application::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) {
    Suspending += ref new Windows::UI::Xaml::SuspendingEventHandler(this, &Application::OnSuspending);

    // #if _DEBUG
    //  if (IsDebuggerPresent()) {
    //    DebugSettings -> EnableFrameRateCounter = true;
    //  }
    // #endif

    auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
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
      application__.Run("/app.js");
    }
    // Ensure the current Window is active.
    Windows::UI::Xaml::Window::Current->Activate();
  }

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
  // This code is for Windows phone apps only. Restore the content
  // transitions after the application has launched.
  void Application::RootFrame_FirstNavigated(::Platform::Object^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) {
    auto rootFrame = safe_cast<Windows::UI::Xaml::Controls::Frame^>(sender);

    Windows::UI::Xaml::Media::Animation::TransitionCollection^ newTransitions;
    if (transitions__ == nullptr) {
      newTransitions = ref new Windows::UI::Xaml::Media::Animation::TransitionCollection();
      newTransitions->Append(ref new Windows::UI::Xaml::Media::Animation::NavigationThemeTransition());
    }
    else {
      newTransitions = transitions__;
    }

    rootFrame->ContentTransitions = newTransitions;
    rootFrame->Navigated -= first_navigated_token__;
  }
#endif

  void Application::OnSuspending(Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e) {
  }

}  // namespace TitaniumWindows {
