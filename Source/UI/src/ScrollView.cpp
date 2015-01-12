/**
* Titanium.UI.ScrollView for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/ScrollView.hpp"
#include "TitaniumWindows/UI/View.hpp"

namespace TitaniumWindows { namespace UI {

  void ScrollView::setupViewer() {
    using namespace Windows::UI::Xaml::Controls;
    scroll_viewer__->HorizontalScrollBarVisibility = ScrollBarVisibility::Auto;
    scroll_viewer__->VerticalScrollBarVisibility = ScrollBarVisibility::Auto;
    scroll_viewer__->HorizontalScrollMode = ScrollMode::Enabled;
    scroll_viewer__->VerticalScrollMode = ScrollMode::Enabled;

    contentView__.SetProperty("top", get_context().CreateNumber(0));
    contentView__.SetProperty("left", get_context().CreateNumber(0));
    contentView__.SetProperty("width", get_context().CreateString("Ti.UI.FILL"));
    contentView__.SetProperty("height", get_context().CreateString("Ti.UI.FILL"));

    auto content = contentView__.GetPrivate<TitaniumWindows::UI::View>();
    scroll_viewer__->Content = content->getComponent();

    View::add(contentView__, get_context().CreateObject());
  }

  ScrollView::ScrollView(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::ScrollView(js_context)
    , scroll_viewer__(ref new Windows::UI::Xaml::Controls::ScrollViewer())
    , contentView__(js_context.CreateObject(JSExport<TitaniumWindows::UI::View>::Class()).CallAsConstructor())
  {
    TITANIUM_LOG_DEBUG("ScrollView::ctor Initialize");
  }

  ScrollView::ScrollView(const ScrollView& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::UI::ScrollView(rhs, arguments)
    , scroll_viewer__(ref new Windows::UI::Xaml::Controls::ScrollViewer()) 
    , contentView__(get_context().CreateObject(JSExport<TitaniumWindows::UI::View>::Class()).CallAsConstructor())
  {
    TITANIUM_LOG_DEBUG("ScrollView::ctor CallAsConstructor");
    setupViewer();
    setComponent(scroll_viewer__);
  }

  void ScrollView::JSExportInitialize() {
    JSExport<ScrollView>::SetClassVersion(1);
    JSExport<ScrollView>::SetParent(JSExport<Titanium::UI::ScrollView>::Class());
  }

  void ScrollView::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT {
    auto content = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(contentView__.GetPrivate<Titanium::UI::View>());
    content->add(view, this_object);
  }

  bool ScrollView::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString());
    std::string backgroundColorName = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setBackgroundColorArgumentValidator: backgroundColor = ", backgroundColorName);
    const auto backgroundColor = ColorForName(backgroundColorName);
    scroll_viewer__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
    set_backgroundColor(argument);
    return true;
  }

  bool ScrollView::setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setTopArgumentValidator: top = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, value);
    set_top(argument);
    return true;
  }

  bool ScrollView::setBottomArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setBottomArgumentValidator: bottom = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, value);
    set_bottom(argument);
    return true;
  }

  bool ScrollView::setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setLeftArgumentValidator: left = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, value);
    set_left(argument);
    return true;
  }

  bool ScrollView::setRightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setRightArgumentValidator: right = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, value);
    set_right(argument);
    return true;
  }

  bool ScrollView::setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setWidthArgumentValidator: width = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, value);
    set_width(argument);
    return true;
  }

  bool ScrollView::setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setHeightArgumentValidator: height = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, value);
    set_height(argument);
    return true;
  }

  bool ScrollView::setLayoutArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("ScrollView::setLayoutArgumentValidator: layout = ", value);
    setLayout(value);
    set_layout(argument);
    result = true;
    return result;
  }

  void ScrollView::scrollTo(double x, double y) {
    scroll_viewer__->ChangeView(
      ref new Platform::Box<double>(x),
      ref new Platform::Box<double>(y),
      nullptr,
      false
      );
  }

  void ScrollView::scrollToBottom() {
    scroll_viewer__->ChangeView(nullptr, ref new Platform::Box<double>(scroll_viewer__->ScrollableHeight), nullptr);
  }

  JSValue ScrollView::getContentWidth() const {
    auto content = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(contentView__.GetPrivate<Titanium::UI::View>());
    return content->get_width();
  }
  JSValue ScrollView::getContentHeight() const {
    auto content = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(contentView__.GetPrivate<Titanium::UI::View>());
    return content->get_height();
  }
  bool ScrollView::setContentWidth(const JSValue& width) {
    auto content = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(contentView__.GetPrivate<Titanium::UI::View>());
    bool result = false;
    if (width.IsNumber()) {
      content->getComponent()->Width = static_cast<double>(width);
      result = true;
    } else {
      TITANIUM_LOG_WARN("ScrollView::setContentWidth from auto - Unimplemented");
    }
    return result;
  }
  bool ScrollView::setContentHeight(const JSValue& height) {
    auto content = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(contentView__.GetPrivate<Titanium::UI::View>());
    bool result = false;
    if (height.IsNumber()) {
      content->getComponent()->Height = static_cast<double>(height);
      result = true;
    } else {
      TITANIUM_LOG_WARN("ScrollView::setContentWidth from auto - Unimplemented");
    }
    return result;
  }

  bool ScrollView::getScrollingEnabled() const TITANIUM_NOEXCEPT {
    return scroll_viewer__->HorizontalScrollMode != Windows::UI::Xaml::Controls::ScrollMode::Disabled;
  }

  bool ScrollView::setScrollingEnabled(bool enabled) TITANIUM_NOEXCEPT {
    if (enabled) {
      scroll_viewer__->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Auto;
    } else {
      scroll_viewer__->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled;
    }
    return true;
  }

  bool ScrollView::getShowHorizontalScrollIndicator() const TITANIUM_NOEXCEPT {
    return scroll_viewer__->HorizontalScrollBarVisibility != Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
  }

  bool ScrollView::setShowHorizontalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT {
    if (enabled) {
      scroll_viewer__->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto;
    } else {
      scroll_viewer__->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
    }
    return true;
  }

  bool ScrollView::getShowVerticalScrollIndicator() const TITANIUM_NOEXCEPT {
    return scroll_viewer__->VerticalScrollBarVisibility != Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
  }

  bool ScrollView::setShowVerticalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT {
    if (enabled) {
      scroll_viewer__->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto;
    } else {
      scroll_viewer__->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
    }
    return true;
  }

}}  // namespace TitaniumWindows { namespace UI {
