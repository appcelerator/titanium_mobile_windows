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
		class TITANIUMWINDOWS_UI_EXPORT View : public Titanium::UI::View, public JSExport<View>
		{

		public:
			View(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~View() = default;
			View(const View&) = default;
			View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&) = default;
			View& operator=(View&&) = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

			virtual Windows::UI::Xaml::FrameworkElement^ getComponent() TITANIUM_NOEXCEPT;

		private:
			Windows::UI::Xaml::Controls::Canvas^ canvas__;

			// Event handlers
			Windows::Foundation::EventRegistrationToken click_event_;
			Windows::Foundation::EventRegistrationToken focus_event_;
			Windows::Foundation::EventRegistrationToken touch_start_event_;
			Windows::Foundation::EventRegistrationToken touch_end_event_;
			Windows::Foundation::EventRegistrationToken touch_move_event_;
			Windows::Foundation::EventRegistrationToken touch_cancel_event_;
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_VIEW_HPP_
