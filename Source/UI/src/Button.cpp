/**
 * Titanium.UI.Button for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Button.hpp"

namespace TitaniumWindows {
  namespace UI {

    Button::Button(const JSContext& js_context) TITANIUM_NOEXCEPT
      : Titanium::UI::Button(js_context)
      , button__(ref new Windows::UI::Xaml::Controls::Button()) {
      TITANIUM_LOG_DEBUG("Button::ctor Initialize");
    }

    Button::Button(const Button& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
      : Titanium::UI::Button(rhs, arguments)
      , button__(ref new Windows::UI::Xaml::Controls::Button()) {
      TITANIUM_LOG_DEBUG("Button::ctor CallAsConstructor");

      auto callback = [this](Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e) {
        JSObject  event = this->get_context().CreateObject();
        this->fireEvent("click", event);
      };

      click_event__ = button__->Tapped += ref new Windows::UI::Xaml::Input::TappedEventHandler(callback);
    }

    Button::~Button() {
      button__->Tapped -= click_event__;
      button__ = nullptr;
    }

    Windows::UI::Xaml::UIElement^ Button::get_UIElement() const TITANIUM_NOEXCEPT{
      return dynamic_cast<Windows::UI::Xaml::UIElement^>(button__);
    }

      void Button::JSExportInitialize() {
      JSExport<Button>::SetClassVersion(1);
      JSExport<Button>::SetParent(JSExport<Titanium::UI::Button>::Class());
    }

    bool Button::setTitleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT{
      TITANIUM_ASSERT(argument.IsString());
      const std::string title = static_cast<std::string>(argument);
      button__->Content = ref new Platform::String(std::wstring(title.begin(), title.end()).c_str());
      TITANIUM_LOG_DEBUG("Button::setTitleArgumentValidator: title = ", title);
      set_title(argument);
      return true;
    }

  }
}  // namespace TitaniumWindows { namespace UI {
