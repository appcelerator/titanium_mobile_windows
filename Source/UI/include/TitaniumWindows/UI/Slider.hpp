/**
* Titanium.UI.Slider for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_SLIDER_HPP_
#define _TITANIUMWINDOWS_UI_SLIDER_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Slider.hpp"

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
		class TITANIUMWINDOWS_UI_EXPORT Slider final : public Titanium::UI::Slider, public JSExport<Slider>
		{
		public:
			Slider(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Slider() = default;
			Slider(const Slider&) = default;
			Slider& operator=(const Slider&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Slider(Slider&&) = default;
			Slider& operator=(Slider&&) = default;
#endif

			static void JSExportInitialize();
			
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_max(const double& max) TITANIUM_NOEXCEPT override final;
			virtual void set_min(const double& min) TITANIUM_NOEXCEPT override final;
			virtual double get_value() const TITANIUM_NOEXCEPT override final;
			virtual void set_value(const double& value) TITANIUM_NOEXCEPT override final;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:
			Windows::UI::Xaml::Controls::Slider^ slider__;

			// Event handlers
			Windows::Foundation::EventRegistrationToken change_event_;
			Windows::Foundation::EventRegistrationToken click_event_;
			Windows::Foundation::EventRegistrationToken start_event_;
			Windows::Foundation::EventRegistrationToken stop_event_;
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_SLIDER_HPP_
