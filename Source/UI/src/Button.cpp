/**
* Titanium.UI.Button for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Button.hpp"

namespace TitaniumWindows { namespace UI {

  Button::Button(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::Button(js_context)
    , button__(ref new Windows::UI::Xaml::Controls::Button()) {
    TITANIUM_LOG_DEBUG("Button::ctor Initialize");
  }

  Button::Button(const Button& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::Button(rhs, arguments)
    , button__(ref new Windows::UI::Xaml::Controls::Button()) {
    setComponent(button__);
    TITANIUM_LOG_DEBUG("Button::ctor CallAsConstructor");
  }

  void Button::JSExportInitialize() {
    JSExport<Button>::SetClassVersion(1);
    JSExport<Button>::SetParent(JSExport<Titanium::UI::Button>::Class());
  }

  bool Button::setTitleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString());
    const std::string title = static_cast<std::string>(argument);
    button__->Content = ref new Platform::String(std::wstring(title.begin(), title.end()).c_str());
    TITANIUM_LOG_DEBUG("Button::setTitleArgumentValidator: title = ", title);
    set_title(argument);
    return true;
  }

  bool Button::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString());
    bool result = false;
    std::string backgroundColorName = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Button::setBackgroundColorArgumentValidator: backgroundColor = ", backgroundColorName);
    const auto backgroundColor = ColorForName(backgroundColorName);
    button__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
    set_backgroundColor(argument);
    result = true;
    return result;
  }

  bool Button::setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Button::setTopArgumentValidator: top = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, static_cast<std::string>(argument));
    set_top(argument);
    result = true;
    return result;
  }

  bool Button::setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Button::setLeftArgumentValidator: left = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, static_cast<std::string>(argument));
    set_left(argument);
    result = true;
    return result;
  }

  bool Button::setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Button::setWidthArgumentValidator: width = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, static_cast<std::string>(argument));
    set_width(argument);
    result = true;
    return result;
  }

  bool Button::setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Button::setHeightArgumentValidator: height = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, static_cast<std::string>(argument));
    set_height(argument);
    result = true;
    return result;
  }

  void Button::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_DEBUG("Button::enableEvent: (event name '", event_name, "'");

    const JSContext  ctx = this->get_context();

    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml;

    if (event_name == "click") {
      if (click_event_count_ == 0) {
        click_event_ = getComponent()->Tapped += ref new TappedEventHandler([this, ctx](Platform::Object ^ sender, TappedRoutedEventArgs ^ e) {
          auto component = safe_cast<FrameworkElement^>(sender);
          auto position = e->GetPosition(component);

          JSObject  eventArgs = ctx.CreateObject();
          eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
          eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

          this->fireEvent("click", eventArgs);
        });
      }

      ++click_event_count_;

      return;
    }
  }

}}  // namespace TitaniumWindows { namespace UI {
