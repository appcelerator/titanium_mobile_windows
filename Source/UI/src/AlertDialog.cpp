/**
* Titanium.UI.AlertDialog for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/AlertDialog.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		AlertDialog::AlertDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::UI::AlertDialog(js_context),
		      dialog__(ref new Windows::UI::Popups::MessageDialog(""))
		{
			TITANIUM_LOG_DEBUG("AlertDialog::ctor Initialize");
		}

		AlertDialog::AlertDialog(const AlertDialog& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Titanium::UI::AlertDialog(rhs, arguments),
		      dialog__(ref new Windows::UI::Popups::MessageDialog(""))
		{
			//setComponent(dialog__);
			TITANIUM_LOG_DEBUG("AlertDialog::ctor CallAsConstructor");
		}

		void AlertDialog::JSExportInitialize()
		{
			JSExport<AlertDialog>::SetClassVersion(1);
			JSExport<AlertDialog>::SetParent(JSExport<Titanium::UI::AlertDialog>::Class());
		}

		void AlertDialog::hide(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO Implement!
		}

		void AlertDialog::show(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO If we never set any button names, we need to set default buttons here now!
			dialog__->ShowAsync();
		}

		void AlertDialog::addButton(const std::string& buttonName) TITANIUM_NOEXCEPT
		{
			const JSContext ctx = this->get_context();
			const auto index = dialog__->Commands->Size;

			// TODO Take into account the click_event_count?
			auto command_invoked_handler = ref new Windows::UI::Popups::UICommandInvokedHandler([this, ctx, index](Windows::UI::Popups::IUICommand^ command) {
				JSObject eventArgs = ctx.CreateObject();
				eventArgs.SetProperty("index", ctx.CreateNumber(index));

				this->fireEvent("click", eventArgs);
			});

			// The alert's "buttons" are UICommand, they take a title and an
			// action.
			const std::wstring wButtonName = std::wstring(buttonName.begin(), buttonName.end());
			dialog__->Commands->Append(ref new Windows::UI::Popups::UICommand(ref new Platform::String(wButtonName.c_str()), command_invoked_handler));
		}

		void AlertDialog::set_message(const std::string& message) TITANIUM_NOEXCEPT
		{
			Titanium::UI::AlertDialog::set_message(message);
			dialog__->Content = ref new Platform::String(std::wstring(message.begin(), message.end()).c_str());
		}

		void AlertDialog::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			Titanium::UI::AlertDialog::set_title(title);
			dialog__->Title = ref new Platform::String(std::wstring(title.begin(), title.end()).c_str());
		}

		void AlertDialog::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog::enableEvent: (event name '", event_name, "'");

			if (event_name == "click") {
				++click_event_count_;
				return;
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
