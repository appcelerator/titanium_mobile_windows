/**
* Titanium.UI.View for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_SCROLLVIEW_HPP_
#define _TITANIUMWINDOWS_UI_SCROLLVIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows {
namespace UI {

using namespace HAL;

/*!
  @class

  @discussion This is the Titanium.UI.ScrollView implementation for
  Windows.
  */
class TITANIUMWINDOWS_UI_EXPORT ScrollView final : public Titanium::UI::ScrollView, public JSExport<ScrollView>, public ViewBase {
 public:
  ScrollView(const JSContext& js_context) TITANIUM_NOEXCEPT;
  ScrollView(const ScrollView&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

  virtual ~ScrollView() = default;
  ScrollView(const ScrollView&) = default;
  ScrollView& operator=(const ScrollView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  ScrollView(ScrollView&&) = default;
  ScrollView& operator=(ScrollView&&) = default;
#endif

  virtual std::string defaultHeight() const override {
    return Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL);
  }

  virtual std::string defaultWidth() const override {
    return Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL);
  }

  virtual void add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT override;
  virtual bool setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;
  virtual bool setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;
  virtual bool setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;
  virtual bool setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;
  virtual bool setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;
  virtual bool setBottomArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;
  virtual bool setRightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;
  virtual bool setLayoutArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override;

  virtual void scrollTo(double x, double y) TITANIUM_NOEXCEPT override;
  virtual void scrollToBottom() TITANIUM_NOEXCEPT override;
  virtual JSValue getContentWidth() const TITANIUM_NOEXCEPT override;
  virtual JSValue getContentHeight() const TITANIUM_NOEXCEPT override;
  virtual bool setContentWidth(const JSValue& width) TITANIUM_NOEXCEPT override;
  virtual bool setContentHeight(const JSValue& height) TITANIUM_NOEXCEPT override;
  virtual bool getScrollingEnabled() const TITANIUM_NOEXCEPT;
  virtual bool setScrollingEnabled(bool enabled) TITANIUM_NOEXCEPT;
  virtual bool getShowHorizontalScrollIndicator() const TITANIUM_NOEXCEPT;
  virtual bool setShowHorizontalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT;
  virtual bool getShowVerticalScrollIndicator() const TITANIUM_NOEXCEPT;
  virtual bool setShowVerticalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT;

  static void JSExportInitialize();

 private:
  Windows::UI::Xaml::Controls::ScrollViewer ^ scroll_viewer__;
  JSObject contentView__;

  void setupViewer();
};
}
}  // namespace TitaniumWindows { namespace UI {

#endif  // _TITANIUMWINDOWS_UI_SCROLLVIEW_HPP_
