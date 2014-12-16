/**
 * Titanium.UI.Window for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Window.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/Button.hpp"

namespace TitaniumWindows {
  namespace UI {

    Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
      : Titanium::UI::Window(js_context)
      , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {
      TITANIUM_LOG_DEBUG("Window::ctor Initialize");
    }

    Window::Window(const Window& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
      : Titanium::UI::Window(rhs, arguments)
      , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {
      TITANIUM_LOG_DEBUG("Window::ctor CallAsConstructor");
    }

    Window::~Window() {
    }

    void Window::open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT{
      TITANIUM_LOG_DEBUG("Window::open");

      TITANIUM_LOG_DEBUG("Window::get_UIElement:");
      for (auto view_ptr : get_native_children()) {
        const auto native_view_ptr = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(view_ptr);
        if (native_view_ptr) {
          TITANIUM_LOG_DEBUG("Window::get_UIElement: native_view_ptr = ", native_view_ptr);
          TITANIUM_ASSERT(native_view_ptr);
          canvas__->Children->Append(native_view_ptr->get_UIElement());
        }

        const auto native_button_ptr = std::dynamic_pointer_cast<TitaniumWindows::UI::Button>(view_ptr);
        if (native_button_ptr) {
          TITANIUM_LOG_DEBUG("Window::get_UIElement: native_button_ptr = ", native_button_ptr);
          canvas__->Children->Append(native_button_ptr->get_UIElement());
        }
      }

      auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
      rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
      auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
      page->Content = canvas__;

    }

      void Window::JSExportInitialize() {
      JSExport<Window>::SetClassVersion(1);
      JSExport<Window>::SetParent(JSExport<Titanium::UI::Window>::Class());
    }

  }
}  // namespace TitaniumWindows { namespace UI {
