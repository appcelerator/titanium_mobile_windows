/**
* Titanium.UI.Slider for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_SLIDER_HPP_
#define _TITANIUMWINDOWS_UI_SLIDER_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.Slider implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Slider final : public Titanium::UI::Slider, public JSExport<Slider>, public ViewBase
		{
		public:
			Slider(const JSContext& js_context) TITANIUM_NOEXCEPT;
			Slider(const Slider&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

			virtual ~Slider() = default;
			Slider(const Slider&) = default;
			Slider& operator=(const Slider&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Slider(Slider&&) = default;
			Slider& operator=(Slider&&) = default;
#endif

			static void JSExportInitialize();

			virtual void set_max(const double& max) TITANIUM_NOEXCEPT override final;
			virtual void set_min(const double& min) TITANIUM_NOEXCEPT override final;
			virtual void set_value(const double& value) TITANIUM_NOEXCEPT override final;
			virtual void set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT override final;
			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT override final;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override final;
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override final;
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT override final;
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT override final;
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT override final;
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override final;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:
			Windows::UI::Xaml::Controls::Slider^ slider__;

			// Event handlers
			Windows::Foundation::EventRegistrationToken change_event_;
			unsigned int change_event_count_{0};
			Windows::Foundation::EventRegistrationToken click_event_;
			unsigned int click_event_count_{0};
			Windows::Foundation::EventRegistrationToken start_event_;
			unsigned int start_event_count_{0};
			Windows::Foundation::EventRegistrationToken stop_event_;
			unsigned int stop_event_count_{0};
			unsigned int post_layout_event_count_{0};
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_SLIDER_HPP_
