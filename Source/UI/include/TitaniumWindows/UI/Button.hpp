/**
* Titanium.UI.Button for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_BUTTON_HPP_
#define _TITANIUMWINDOWS_UI_BUTTON_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows
{
namespace UI
{
using namespace HAL;

/*!
  @class

  @discussion This is the Titanium.UI.Button implementation for
  Windows.
  */
class TITANIUMWINDOWS_UI_EXPORT Button final : public Titanium::UI::Button, public JSExport<Button>, public ViewBase
{
   public:
	Button(const JSContext& js_context) TITANIUM_NOEXCEPT;
	Button(const Button&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

	virtual ~Button() = default;
	Button(const Button&) = default;
	Button& operator=(const Button&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	Button(Button&&) = default;
	Button& operator=(Button&&) = default;
#endif

	static void JSExportInitialize();

	virtual bool setTitleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;

	virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

   private:
	Windows::UI::Xaml::Controls::Button ^ button__;

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

#endif  // _TITANIUMWINDOWS_UI_BUTTON_HPP_
