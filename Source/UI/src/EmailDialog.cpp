/**
 * Titanium.UI.EmailDialog for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/EmailDialog.hpp"
#include <windows.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		EmailDialog::EmailDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::EmailDialog(js_context)
		{
			TITANIUM_LOG_DEBUG("EmailDialog::ctor Initialize");
		}

		void EmailDialog::JSExportInitialize() {
			JSExport<EmailDialog>::SetClassVersion(1);
			JSExport<EmailDialog>::SetParent(JSExport<Titanium::UI::EmailDialog>::Class());
		}

		bool EmailDialog::isSupported() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			return true;
#else
			return false;
#endif
		}

		void EmailDialog::open(const bool& animated) TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			Windows::ApplicationModel::Email::EmailMessage^ email_message = ref new Windows::ApplicationModel::Email::EmailMessage();

			// Set up all the fields!
			email_message->Body = TitaniumWindows::Utility::ConvertUTF8String(get_messageBody());
			email_message->Subject = TitaniumWindows::Utility::ConvertUTF8String(get_subject());
			setRecipients(get_toRecipients(),  email_message->To);
			setRecipients(get_ccRecipients(),  email_message->CC);
			setRecipients(get_bccRecipients(), email_message->Bcc);
			// TODO Hook up attachments!

			auto composer = Windows::ApplicationModel::Email::EmailManager::ShowComposeNewEmailAsync(email_message);
			if (complete_event_count__ > 0) {
				const JSContext ctx = this->get_context();
				// NOTE this ends up firing the complete event immediately after dialog opens, not after we actually finish the dialog/send the email!
				composer->Completed = ref new Windows::Foundation::AsyncActionCompletedHandler([this, ctx](Windows::Foundation::IAsyncAction^ action, Windows::Foundation::AsyncStatus status) {
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("code", ctx.CreateNumber(0));
					eventArgs.SetProperty("error", ctx.CreateUndefined());
					eventArgs.SetProperty("result", Titanium::UI::EmailDialog::js_get_SENT());
					eventArgs.SetProperty("success", ctx.CreateBoolean(true));

					this->fireEvent("complete", eventArgs);
				});
			}
#else
			TITANIUM_MODULE_LOG_WARN("EmailDialog not supported on Windows Store apps.");
#endif
		}

		void EmailDialog::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::EmailDialog::enableEvent(event_name);

			if (event_name == "complete") {
				++complete_event_count__;
				return;
			}
		}

		// Common code for getting/setting recipients on To/Bcc/Cc

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
		void EmailDialog::setRecipients(const std::vector<std::string>& arg, Windows::Foundation::Collections::IVector<Windows::ApplicationModel::Email::EmailRecipient^>^ recipients) {
			// clear out an existing entries so we fully replace with new
			recipients->Clear();
			// loop through array, each entry should be an email address as string
			for (size_t j = 0; j < arg.size(); j++) {
				const auto address = arg.at(j);
				const auto emailRecipient = ref new Windows::ApplicationModel::Email::EmailRecipient(TitaniumWindows::Utility::ConvertUTF8String(address));
				recipients->Append(emailRecipient); 
			}
		}
#endif
	}  // namespace UI
}  // namespace TitaniumWindows
