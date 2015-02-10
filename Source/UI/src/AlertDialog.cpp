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
		AlertDialog::AlertDialog(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Titanium::UI::AlertDialog(js_context, arguments),
			  buttons__()
		{
			TITANIUM_LOG_DEBUG("AlertDialog::ctor");
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
			std::string title = get_title();
			std::string message = get_message();
			Windows::UI::Popups::MessageDialog^ dialog = ref new Windows::UI::Popups::MessageDialog(ref new Platform::String(std::wstring(message.begin(), message.end()).c_str()), ref new Platform::String(std::wstring(title.begin(), title.end()).c_str()));
			
			// Set up buttons
			if (buttons__.size() > 0) {
				// TODO If user set no custom buttons, we still need to hook click listeners to the defaults!
				const JSContext ctx = this->get_context();
				for (std::vector<std::string>::size_type i = 0; i != buttons__.size(); i++) {
					std::string buttonName = buttons__[i];

					// TODO Take into account the click_event_count?
					auto command_invoked_handler = ref new Windows::UI::Popups::UICommandInvokedHandler([this, ctx, i](Windows::UI::Popups::IUICommand^ command) {
						JSObject eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("index", ctx.CreateNumber(i));

						this->fireEvent("click", eventArgs);
					});

					// The alert's "buttons" are UICommand, they take a title and an action.
					const std::wstring wButtonName = std::wstring(buttonName.begin(), buttonName.end());
					dialog->Commands->Append(ref new Windows::UI::Popups::UICommand(ref new Platform::String(wButtonName.c_str()), command_invoked_handler));
				}
			}
			dialog->ShowAsync();
		}

		void AlertDialog::addButton(const std::string& buttonName) TITANIUM_NOEXCEPT
		{
			buttons__.push_back(buttonName);
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
