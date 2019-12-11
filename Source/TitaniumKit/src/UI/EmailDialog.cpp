/**
 * TitaniumKit Titanium.UI.EmailDialog
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/EmailDialog.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/detail/TiImpl.hpp"

#ifdef FAILED
#pragma push_macro("FAILED")
#undef FAILED
#define _restore_FAILED_
#endif

namespace Titanium
{
	namespace UI
	{

		EmailDialog::EmailDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.EmailDialog"),
			cancelled__(js_context.CreateNumber(0)),
			failed__(js_context.CreateNumber(3)),
			saved__(js_context.CreateNumber(1)),
			sent__(js_context.CreateNumber(2)),
			html__(false),
			messageBody__(""),
			subject__("")
		{
			TITANIUM_LOG_DEBUG("EmailDialog:: ctor ", this);
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, CANCELLED)
		{
			return cancelled__;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, FAILED)
		{
			return failed__;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, SAVED)
		{
			return saved__;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, SENT)
		{
			return sent__;
		}

		TITANIUM_PROPERTY_READWRITE(EmailDialog, std::vector<std::string>, bccRecipients)

		TITANIUM_PROPERTY_READWRITE(EmailDialog, std::vector<std::string>, ccRecipients)

		TITANIUM_PROPERTY_READWRITE(EmailDialog, bool, html)

		TITANIUM_PROPERTY_READWRITE(EmailDialog, std::string, messageBody)

		TITANIUM_PROPERTY_READWRITE(EmailDialog, std::string, subject)

		TITANIUM_PROPERTY_READWRITE(EmailDialog, std::vector<std::string>, toRecipients)

		void EmailDialog::addAttachment(const std::shared_ptr<Titanium::Filesystem::File>& attachment) TITANIUM_NOEXCEPT
		{
			addAttachment(attachment->read());
		}

		void EmailDialog::addAttachment(const std::shared_ptr<Titanium::Blob>& attachment) TITANIUM_NOEXCEPT
		{
			attachments__.push_back(attachment);
		}

		bool EmailDialog::isSupported() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("EmailDialog::isSupported: Unimplemented");
			return false;
		}

		void EmailDialog::open(const bool& animated) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("EmailDialog::open: Unimplemented");
		}

		void EmailDialog::JSExportInitialize() {
			JSExport<EmailDialog>::SetClassVersion(1);
			JSExport<EmailDialog>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(EmailDialog, CANCELLED);
			TITANIUM_ADD_PROPERTY_READONLY(EmailDialog, FAILED);
			TITANIUM_ADD_PROPERTY_READONLY(EmailDialog, SAVED);
			TITANIUM_ADD_PROPERTY_READONLY(EmailDialog, SENT);
			TITANIUM_ADD_PROPERTY(EmailDialog, bccRecipients);
			TITANIUM_ADD_PROPERTY(EmailDialog, ccRecipients);
			TITANIUM_ADD_PROPERTY(EmailDialog, html);
			TITANIUM_ADD_PROPERTY(EmailDialog, messageBody);
			TITANIUM_ADD_PROPERTY(EmailDialog, subject);
			TITANIUM_ADD_PROPERTY(EmailDialog, toRecipients);

			TITANIUM_ADD_FUNCTION(EmailDialog, addAttachment);
			TITANIUM_ADD_FUNCTION(EmailDialog, isSupported);
			TITANIUM_ADD_FUNCTION(EmailDialog, open);
			TITANIUM_ADD_FUNCTION(EmailDialog, getBccRecipients);
			TITANIUM_ADD_FUNCTION(EmailDialog, setBccRecipients);
			TITANIUM_ADD_FUNCTION(EmailDialog, getCcRecipients);
			TITANIUM_ADD_FUNCTION(EmailDialog, setCcRecipients);
			TITANIUM_ADD_FUNCTION(EmailDialog, getHtml);
			TITANIUM_ADD_FUNCTION(EmailDialog, setHtml);
			TITANIUM_ADD_FUNCTION(EmailDialog, getMessageBody);
			TITANIUM_ADD_FUNCTION(EmailDialog, setMessageBody);
			TITANIUM_ADD_FUNCTION(EmailDialog, getSubject);
			TITANIUM_ADD_FUNCTION(EmailDialog, setSubject);
			TITANIUM_ADD_FUNCTION(EmailDialog, getToRecipients);
			TITANIUM_ADD_FUNCTION(EmailDialog, setToRecipients);
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, bccRecipients)
		{
			const auto js_context = get_context();
			const auto recipients = get_bccRecipients();
			std::vector<JSValue> args;
			for (auto r : recipients) {
				args.push_back(js_context.CreateString(r));
			}
			return js_context.CreateArray(args);
		}

		TITANIUM_PROPERTY_SETTER(EmailDialog, bccRecipients)
		{
			TITANIUM_ASSERT(argument.IsObject());
			const auto _0 = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(_0.IsArray());

			std::vector<std::string> recipients;
			const auto item_count = static_cast<JSArray>(_0).GetLength();
			for (uint32_t i = 0; i < item_count; ++i) {
				JSValue item = _0.GetProperty(i);
				TITANIUM_ASSERT(item.IsString());
				recipients.push_back(static_cast<std::string>(item));
			}

			set_bccRecipients(recipients);

			return true;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, ccRecipients)
		{
			const auto js_context = get_context();
			const auto recipients = get_ccRecipients();
			std::vector<JSValue> args;
			for (auto r : recipients) {
				args.push_back(js_context.CreateString(r));
			}
			return js_context.CreateArray(args);
		}

		TITANIUM_PROPERTY_SETTER(EmailDialog, ccRecipients)
		{
			TITANIUM_ASSERT(argument.IsObject());
			const auto _0 = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(_0.IsArray());

			std::vector<std::string> recipients;
			const auto item_count = static_cast<JSArray>(_0).GetLength();
			for (uint32_t i = 0; i < item_count; ++i) {
				JSValue item = _0.GetProperty(i);
				TITANIUM_ASSERT(item.IsString());
				recipients.push_back(static_cast<std::string>(item));
			}

			set_ccRecipients(recipients);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, html)
		{
			return get_context().CreateBoolean(get_html());
		}

		TITANIUM_PROPERTY_SETTER(EmailDialog, html)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_html(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, messageBody)
		{
			return get_context().CreateString(get_messageBody());
		}

		TITANIUM_PROPERTY_SETTER(EmailDialog, messageBody)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_messageBody(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, subject)
		{
			return get_context().CreateString(get_subject());
		}

		TITANIUM_PROPERTY_SETTER(EmailDialog, subject)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_subject(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(EmailDialog, toRecipients)
		{
			const auto js_context = get_context();
			const auto recipients = get_toRecipients();
			std::vector<JSValue> args;
			for (auto r : recipients) {
				args.push_back(js_context.CreateString(r));
			}
			return js_context.CreateArray(args);
		}

		TITANIUM_PROPERTY_SETTER(EmailDialog, toRecipients)
		{
			TITANIUM_ASSERT(argument.IsObject());
			const auto _0 = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(_0.IsArray());

			std::vector<std::string> recipients;
			const auto item_count = static_cast<JSArray>(_0).GetLength();
			for (uint32_t i = 0; i < item_count; ++i) {
				JSValue item = _0.GetProperty(i);
				TITANIUM_ASSERT(item.IsString());
				recipients.push_back(static_cast<std::string>(item));
			}

			set_toRecipients(recipients);

			return true;
		}

		TITANIUM_FUNCTION(EmailDialog, addAttachment)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto attachment = static_cast<JSObject>(_0);

				const auto file_ptr = attachment.GetPrivate<Titanium::Filesystem::File>();
				const auto blob_ptr = attachment.GetPrivate<Titanium::Blob>();

				if (file_ptr != nullptr) {
					addAttachment(file_ptr);
				} else if (blob_ptr != nullptr) {
					addAttachment(blob_ptr);
				} else {
					TITANIUM_LOG_WARN("EmailDialog::addAttachment: Can not attach unknown object");
				}
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(EmailDialog, isSupported)
		{
			return get_context().CreateBoolean(isSupported());
		}

		TITANIUM_FUNCTION(EmailDialog, open)
		{
			bool animated = true;
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto properties = static_cast<JSObject>(_0);

				if (properties.HasProperty("animated")) {
					animated = static_cast<bool>(properties.GetProperty("animated"));
				}
			}
			open(animated);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(EmailDialog, getBccRecipients, bccRecipients)
		TITANIUM_FUNCTION_AS_SETTER(EmailDialog, setBccRecipients, bccRecipients)

		TITANIUM_FUNCTION_AS_GETTER(EmailDialog, getCcRecipients, ccRecipients)
		TITANIUM_FUNCTION_AS_SETTER(EmailDialog, setCcRecipients, ccRecipients)

		TITANIUM_FUNCTION_AS_GETTER(EmailDialog, getHtml, html)
		TITANIUM_FUNCTION_AS_SETTER(EmailDialog, setHtml, html)

		TITANIUM_FUNCTION_AS_GETTER(EmailDialog, getMessageBody, messageBody)
		TITANIUM_FUNCTION_AS_SETTER(EmailDialog, setMessageBody, messageBody)

		TITANIUM_FUNCTION_AS_GETTER(EmailDialog, getSubject, subject)
		TITANIUM_FUNCTION_AS_SETTER(EmailDialog, setSubject, subject)

		TITANIUM_FUNCTION_AS_GETTER(EmailDialog, getToRecipients, toRecipients)
		TITANIUM_FUNCTION_AS_SETTER(EmailDialog, setToRecipients, toRecipients)

	} // namespace UI
} // namespace Titanium

#ifdef _restore_FAILED_
#pragma pop_macro("FAILED")
#undef _restore_FAILED_
#endif
