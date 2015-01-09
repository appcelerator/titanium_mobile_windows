/**
* Titanium.UI.ImageView for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
#define _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>

namespace TitaniumWindows
{
namespace UI
{
using namespace HAL;

/*!
  @class

  @discussion This is the Titanium.UI.ImageView implementation for
  Windows.
  */
class TITANIUMWINDOWS_UI_EXPORT ImageView final : public Titanium::UI::ImageView, public JSExport<ImageView>, public ViewBase
{
   public:
	ImageView(const JSContext& js_context) TITANIUM_NOEXCEPT;
	ImageView(const ImageView&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

	virtual ~ImageView() = default;
	ImageView(const ImageView&) = default;
	ImageView& operator=(const ImageView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	ImageView(ImageView&&) = default;
	ImageView& operator=(ImageView&&) = default;
#endif

	static void JSExportInitialize();

	virtual bool setImageArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
	virtual bool setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;

	virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

   private:
	Windows::Foundation::EventRegistrationToken internal_load_event_;
	Windows::UI::Xaml::Controls::Image ^ image__;
	std::string path_;

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

#endif  // _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
