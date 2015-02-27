/**
 * Titanium.UI.EmailDialog for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/EmailDialog.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		EmailDialog::EmailDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::EmailDialog(js_context),
			attachments__()
		{
			TITANIUM_LOG_DEBUG("EmailDialog::ctor Initialize");
		}

		void EmailDialog::JSExportInitialize() {
			JSExport<EmailDialog>::SetClassVersion(1);
			JSExport<EmailDialog>::SetParent(JSExport<Titanium::UI::EmailDialog>::Class());
		}

		void EmailDialog::addAttachment(const JSObject& attachment) TITANIUM_NOEXCEPT
		{
			attachments__.push_back(attachment);
		}

		bool EmailDialog::isSupported() TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
			return true;
#else
			return false;
#endif
		}

		void EmailDialog::open(const JSObject& properties) TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
			Windows::ApplicationModel::Email::EmailMessage^ email_message = ref new Windows::ApplicationModel::Email::EmailMessage();

			// Set up all the fields!
			email_message->Body = TitaniumWindows::Utility::ConvertString(messageBody());
			email_message->Subject = TitaniumWindows::Utility::ConvertString(subject());
			setRecipients(static_cast<JSObject>(toRecipients()), email_message->To);
			setRecipients(static_cast<JSObject>(ccRecipients()), email_message->CC);
			setRecipients(static_cast<JSObject>(bccRecipients()), email_message->Bcc);
			// TODO Hook up attachments!

			auto composer = Windows::ApplicationModel::Email::EmailManager::ShowComposeNewEmailAsync(email_message);
			if (complete_event_count__ > 0) {
				const JSContext ctx = this->get_context();
				// NOTE this ends up firing the complete event immediately after dialog opens, not after we actually finish the dialog/send the email!
				composer->Completed = ref new Windows::Foundation::AsyncActionCompletedHandler([this, ctx](Windows::Foundation::IAsyncAction^ action, Windows::Foundation::AsyncStatus status) {
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("code", ctx.CreateNumber(0));
					eventArgs.SetProperty("error", ctx.CreateUndefined());
					eventArgs.SetProperty("result", Titanium::UI::EmailDialog::SENT());
					eventArgs.SetProperty("success", ctx.CreateBoolean(true));

					this->fireEvent("complete", eventArgs);
				});
			}
#else
			TITANIUM_LOG_WARN("[WARN] EmailDialog not supported on Windows Store apps.");
#endif
		}

		void EmailDialog::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			if (event_name == "complete") {
				++complete_event_count__;
				return;
			}
		}

		// Common code for getting/setting recipients on To/Bcc/Cc

#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
		void EmailDialog::setRecipients(const JSObject& arg, Windows::Foundation::Collections::IVector<Windows::ApplicationModel::Email::EmailRecipient^>^ recipients) {
			// clear out an existing entries so we fully replace with new
			recipients->Clear();
			// should be one array arg
			const auto parameters = (arg.IsArray() ? arg.GetPropertyNames().GetCount() : 1);
			// loop through array, each entry should be an email address as string
			for (size_t j = 0; j < parameters; j++) {
				const auto parameter = arg.GetProperty(j);
				if (parameter.IsString()) {
					const auto address = static_cast<std::string>(parameter);
					const auto emailRecipient = ref new Windows::ApplicationModel::Email::EmailRecipient(TitaniumWindows::Utility::ConvertString(address));
					recipients->Append(emailRecipient); 
				}
			}
		}
#endif
	}  // namespace UI
}  // namespace TitaniumWindows