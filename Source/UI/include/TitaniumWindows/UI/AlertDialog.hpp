/**
* Titanium.UI.AlertDialog for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_ALERTDIALOG_HPP_
#define _TITANIUMWINDOWS_UI_ALERTDIALOG_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.AlertDialog implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT AlertDialog final : public Titanium::UI::AlertDialog, public JSExport<AlertDialog>, public ViewBase
		{
		public:
			AlertDialog(const JSContext& js_context) TITANIUM_NOEXCEPT;
			AlertDialog(const AlertDialog&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

			virtual ~AlertDialog() = default;
			AlertDialog(const AlertDialog&) = default;
			AlertDialog& operator=(const AlertDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			AlertDialog(AlertDialog&&) = default;
			AlertDialog& operator=(AlertDialog&&) = default;
#endif

			static void JSExportInitialize();

			virtual void hide(JSObject& this_object) TITANIUM_NOEXCEPT;
			virtual void show(JSObject& this_object) TITANIUM_NOEXCEPT;

			virtual void addButton(const std::string& buttonName) TITANIUM_NOEXCEPT override final;
			virtual void set_message(const std::string& message) TITANIUM_NOEXCEPT override final;
			virtual void set_title(const std::string& title) TITANIUM_NOEXCEPT override final;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:
			Windows::UI::Popups::MessageDialog^ dialog__;

			// Event handlers
			Windows::Foundation::EventRegistrationToken click_event_;
			unsigned int click_event_count_{0};
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_ALERTDIALOG_HPP_
