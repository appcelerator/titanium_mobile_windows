/**
 * Titanium.UI.Window for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Window.hpp"
#include "TitaniumWindows/UI/View.hpp"

namespace TitaniumWindows { namespace UI {

  Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::Window(js_context)
    , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {
    TITANIUM_LOG_DEBUG("Window::ctor Initialize");
  }

  Window::Window(const Window& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::Window(rhs, arguments)
    , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {

	setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
	setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

    setComponent(canvas__);
    TITANIUM_LOG_DEBUG("Window::ctor CallAsConstructor");
  }

  Window::~Window() {
  }

  void Window::hide(JSObject& this_object) TITANIUM_NOEXCEPT {
    getComponent()->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
  }

    void Window::show(JSObject& this_object) TITANIUM_NOEXCEPT {
    getComponent()->Visibility = Windows::UI::Xaml::Visibility::Visible;
  }

  void Window::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT {
    auto nativeView = dynamic_cast<Windows::UI::Xaml::Controls::Panel^>(getComponent());
    
    if (nativeView == nullptr) {
      TITANIUM_LOG_DEBUG("Window::add: nativeView = nullptr");
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
      TITANIUM_LOG_DEBUG("Window::add: nativeChildView = nullptr");
    }
  }

  void Window::open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT{
    TITANIUM_LOG_DEBUG("Window::open");

    auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
    rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
    auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
    page->Content = canvas__;
  }

  void Window::JSExportInitialize() {
    JSExport<Window>::SetClassVersion(1);
    JSExport<Window>::SetParent(JSExport<Titanium::UI::Window>::Class());
  }

  bool Window::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Window::setBackgroundColorArgumentValidator: backgroundColor = ", value);
    const auto backgroundColor = ColorForName(value);
    canvas__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
    set_backgroundColor(argument);
    result = true;
    return result;
  }

  bool Window::setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Window::setTopArgumentValidator: top = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, static_cast<std::string>(argument));
    set_top(argument);
    result = true;
    return result;
  }

  bool Window::setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Window::setLeftArgumentValidator: left = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, static_cast<std::string>(argument));
    set_left(argument);
    result = true;
    return result;
  }

  bool Window::setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Window::setWidthArgumentValidator: width = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, static_cast<std::string>(argument));
    set_width(argument);
    result = true;
    return result;
  }

  bool Window::setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Window::setHeightArgumentValidator: height = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, static_cast<std::string>(argument));
    set_height(argument);
    result = true;
    return result;
  }

  bool Window::setLayoutArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT{
    TITANIUM_ASSERT(argument.IsString());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Window::setLayoutArgumentValidator: layout = ", value);
    setLayout(value);
    set_layout(argument);
    result = true;
    return result;
  }

  ///////////////// Layout //////////////

  void Window::onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect) {
    if (layout_node_->parent) {
      ViewBase::onComponentSizeChange(rect);
      return;
    }

    layout_node_->element.measuredHeight = rect.height;
    layout_node_->element.measuredWidth = rect.width;
    auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
    if (root) {
      Titanium::LayoutEngine::nodeLayout(root);
    }

    // TODO: Check if EventPostLayout is set before creating this object
    /*
    Ti::Value val;
    val.setProperty("x", Ti::Value(rect.x));
    val.setProperty("y", Ti::Value(rect.y));
    val.setProperty("width", Ti::Value(rect.width));
    val.setProperty("height", Ti::Value(rect.height));
    fireEvent(Ti::Constants::EventPostLayout, val);
    */
  }

  void Window::onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name) {
    // We leave top level window alone unless the window is a child view
    if (layout_node_->parent) {
      ViewBase::onLayoutEngineCallback(rect, name);
      return;
    }
  }

}}  // namespace TitaniumWindows { namespace UI {
