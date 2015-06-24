/**
 * Titanium.UI.Switch for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_SWITCH_HPP_
#define _TITANIUMWINDOWS_SWITCH_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Switch.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.Switch implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Switch final : public Titanium::UI::Switch, public JSExport<Switch>
		{

		public:
			Switch(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~Switch()                  = default;
			Switch(const Switch&)            = default;
			Switch& operator=(const Switch&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Switch(Switch&&)                 = default;
			Switch& operator=(Switch&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_value(const bool&) TITANIUM_NOEXCEPT;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:

			Windows::UI::Xaml::Controls::ToggleSwitch^ switch__ = { nullptr };

			Windows::Foundation::EventRegistrationToken change_event_;
			Windows::Foundation::EventRegistrationToken click_event_;
		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_SWITCH_HPP_