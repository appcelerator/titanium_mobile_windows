/**
* Titanium.UI.Label for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_LABEL_HPP_
#define _TITANIUMWINDOWS_UI_LABEL_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows {
namespace UI {

using namespace HAL;

/*!
  @class

  @discussion This is the Titanium.UI.Label implementation for
  Windows.
  */
class TITANIUMWINDOWS_UI_EXPORT Label final : public Titanium::UI::Label, public JSExport<Label>, public ViewBase {
 public:
  Label(const JSContext& js_context) TITANIUM_NOEXCEPT;
  Label(const Label&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

  virtual ~Label() = default;
  Label(const Label&) = default;
  Label& operator=(const Label&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  Label(Label&&) = default;
  Label& operator=(Label&&) = default;
#endif

  static void JSExportInitialize();

  virtual void set_color(const JSValue& color) TITANIUM_NOEXCEPT override final;
  virtual void set_text(const JSValue& text) TITANIUM_NOEXCEPT override final;
  virtual void set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT override final;
  virtual void set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT override final;
  virtual void set_wordWrap(const JSValue& wordWrap) TITANIUM_NOEXCEPT override final;
  virtual void set_fontFamily(const JSValue& family) TITANIUM_NOEXCEPT override final;
  virtual void set_fontSize(const JSValue& size) TITANIUM_NOEXCEPT override final;
  virtual void set_fontStyle(const JSValue& style) TITANIUM_NOEXCEPT override final;
  virtual void set_fontWeight(const JSValue& weight) TITANIUM_NOEXCEPT override final;
  virtual void set_textStyle(const Titanium::UI::TEXT_STYLE& style) TITANIUM_NOEXCEPT override final;

  virtual bool setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
  virtual bool setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
  virtual bool setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
  virtual bool setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;

  virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

 private:
  Windows::UI::Xaml::Controls::TextBlock ^ label__;

  // Event handlers
  Windows::Foundation::EventRegistrationToken click_event_;
  unsigned int click_event_count_{0};
  Windows::Foundation::EventRegistrationToken touch_start_event_;
  unsigned int touch_start_event_count_{0};
  Windows::Foundation::EventRegistrationToken touch_end_event_;
  unsigned int touch_end_event_count_{0};
  Windows::Foundation::EventRegistrationToken touch_move_event_;
  unsigned int touch_move_event_count_{0};
  Windows::Foundation::EventRegistrationToken touch_cancel_event_;
  unsigned int touch_cancel_event_count_{0};
  unsigned int post_layout_event_count_{0};
};
}
}  // namespace TitaniumWindows { namespace UI {

#endif  // _TITANIUMWINDOWS_UI_LABEL_HPP_
