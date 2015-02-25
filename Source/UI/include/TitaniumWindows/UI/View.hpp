/**
 * Titanium.UI.View for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_VIEW_HPP_
#define _TITANIUMWINDOWS_UI_VIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.View implementation for
		  Windows.
		*/
// Silence 4275 about ViewBase for now. We need to merge View and ViewBase and then remove this pragma! TIMOB-18422
#pragma warning(push)
#pragma warning(disable : 4275)
		class TITANIUMWINDOWS_UI_EXPORT View final : public Titanium::UI::View, public JSExport<View>, public ViewBase
		{
#pragma warning(pop)

		public:
			View(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~View() = default;
			View(const View&) = default;
			View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&) = default;
			View& operator=(View&&) = default;
#endif

			static void JSExportInitialize();

			virtual void add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT;

			virtual void hide(JSObject& this_object) TITANIUM_NOEXCEPT;
			virtual void show(JSObject& this_object) TITANIUM_NOEXCEPT;

			virtual void set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT override final;
			virtual void set_opacity(const double& opacity) TITANIUM_NOEXCEPT override final;
			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT override final;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override final;
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override final;
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT override final;
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT override final;
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT override final;
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override final;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:
			Windows::UI::Xaml::Controls::Canvas^ canvas__;

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
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_VIEW_HPP_
