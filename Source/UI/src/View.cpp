/**
 * Titanium.UI.View for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/View.hpp"

namespace TitaniumWindows { namespace UI {

  View::View(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::View(js_context)
    , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {
    TITANIUM_LOG_DEBUG("View::ctor Initialize");
  }

  View::View(const View& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::View(rhs, arguments)
    , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {

	setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
	setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

    setComponent(canvas__);
	
    TITANIUM_LOG_DEBUG("View::ctor CallAsConstructor");
  }

  void View::JSExportInitialize() {
    JSExport<View>::SetClassVersion(1);
    JSExport<View>::SetParent(JSExport<Titanium::UI::View>::Class());
  }

  void View::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT {
    auto nativeView = dynamic_cast<Windows::UI::Xaml::Controls::Panel^>(getComponent());

    if (nativeView == nullptr) {
      TITANIUM_LOG_DEBUG("View::add: nativeView = nullptr");
      return;
    }

    auto view_ptr = view.GetPrivate<Titanium::UI::View>();
    auto newView = std::dynamic_pointer_cast<TitaniumWindows::UI::ViewBase>(view_ptr);
    auto nativeChildView = newView->getComponent();
    if (nativeChildView != nullptr) {
      Titanium::LayoutEngine::nodeAddChild(layout_node_, newView->layout_node_);
      if (isLoaded()) {
        auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
        if (root) {
          Titanium::LayoutEngine::nodeLayout(root);
        }
      }

      canvas__->Children->Append(nativeChildView);
    }
    else {
      TITANIUM_LOG_DEBUG("View::add: nativeChildView = nullptr");
    }
  }

  void View::hide(JSObject& this_object) TITANIUM_NOEXCEPT{
	getComponent()->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
  }

  void View::show(JSObject& this_object) TITANIUM_NOEXCEPT{
	getComponent()->Visibility = Windows::UI::Xaml::Visibility::Visible;
  }

  bool View::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT{
    TITANIUM_ASSERT(argument.IsString());
    bool result = false;
    std::string backgroundColorName = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("View::setBackgroundColorArgumentValidator: backgroundColor = ", backgroundColorName);
    const auto backgroundColor = ColorForName(backgroundColorName);
    canvas__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
    set_backgroundColor(argument);
    result = true;
    return result;
  }

  bool View::setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("View::setTopArgumentValidator: top = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, static_cast<std::string>(argument));
    set_top(argument);
    result = true;
    return result;
  }

  bool View::setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("View::setLeftArgumentValidator: left = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, static_cast<std::string>(argument));
    set_left(argument);
    result = true;
    return result;
  }

  bool View::setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("View::setWidthArgumentValidator: width = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, static_cast<std::string>(argument));
    set_width(argument);
    result = true;
    return result;
  }

  bool View::setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("View::setHeightArgumentValidator: height = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, static_cast<std::string>(argument));
    set_height(argument);
    result = true;
    return result;
  }

  bool View::setBottomArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT{
	TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
	bool result = false;
	std::string value = static_cast<std::string>(argument);
	TITANIUM_LOG_INFO("View::setBottomArgumentValidator: bottom = ", value);
	setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, static_cast<std::string>(argument));
	set_bottom(argument);
	result = true;
	return result;
  }

  bool View::setRightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT{
	TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
	bool result = false;
	std::string value = static_cast<std::string>(argument);
	TITANIUM_LOG_INFO("View::setRightArgumentValidator: right = ", value);
	setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, static_cast<std::string>(argument));
	set_right(argument);
	result = true;
	return result;
  }

  bool View::setLayoutArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT{
	  TITANIUM_ASSERT(argument.IsString());
	  bool result = false;
	  std::string value = static_cast<std::string>(argument);
	  TITANIUM_LOG_INFO("View::setLayoutArgumentValidator: layout = ", value);
	  setLayout(value);
	  set_layout(argument);
	  result = true;
	  return result;
  }

  void View::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_DEBUG("View::enableEvent: (event name '", event_name, "'");
    
    const JSContext  ctx = this->get_context();

    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml;

    if (event_name == "touchmove") {
      if (touch_move_event_count_ == 0) {
        getComponent()->ManipulationMode = ManipulationModes::All;
        touch_move_event_ = getComponent()->ManipulationDelta += ref new ManipulationDeltaEventHandler([ctx, this](Platform::Object ^ sender, ManipulationDeltaRoutedEventArgs ^ e) {
          JSObject  delta = ctx.CreateObject();
          delta.SetProperty("x", ctx.CreateNumber(e->Delta.Translation.X));
          delta.SetProperty("y", ctx.CreateNumber(e->Delta.Translation.Y));

          JSObject  eventArgs = ctx.CreateObject();
          eventArgs.SetProperty("x", ctx.CreateNumber(e->Position.X));
          eventArgs.SetProperty("y", ctx.CreateNumber(e->Position.Y));
          eventArgs.SetProperty("delta", delta);

          this->fireEvent("touchmove", eventArgs);
        });
      }

      ++touch_move_event_count_;

      return;
    }
  }

}}  // namespace TitaniumWindows { namespace UI {
