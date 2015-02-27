/**
 * Titanium.UI.EmailDialog for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EMAILDIALOG_HPP_
#define _TITANIUM_EMAILDIALOG_HPP_

#include "Titanium/Module.hpp"

#ifdef FAILED
#pragma push_macro("FAILED")
#undef FAILED
#define _restore_FAILED_
#endif

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium EmailDialog Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.EmailDialog
		*/
		class TITANIUMKIT_EXPORT EmailDialog : public Module, public JSExport<EmailDialog>
		{

		public:

			/*!
			  @property
			  @abstract CANCELLED
			  @discussion Constant for the `CANCELLED` status result.
			*/
			virtual JSValue CANCELLED() const TITANIUM_NOEXCEPT final;

			/*!
			  @property
			  @abstract FAILED
			  @discussion Constant for the `FAILED` status result.
			*/
			virtual JSValue FAILED() const TITANIUM_NOEXCEPT final;

			/*!
			  @property
			  @abstract SAVED
			  @discussion Constant for the `SAVED` status result. On Android, this property exists but is not used.
			*/
			virtual JSValue SAVED() const TITANIUM_NOEXCEPT final;

			/*!
			  @property
			  @abstract SENT
			  @discussion Constant for the `SENT` status result.
			*/
			virtual JSValue SENT() const TITANIUM_NOEXCEPT final;

			/*!
			  @property
			  @abstract bccRecipients
			  @discussion Recipients of the email included via the `BCC` (Blind Carbon Copy) field.
			*/
			virtual JSValue bccRecipients() const TITANIUM_NOEXCEPT final;
			virtual void setBccRecipients(const JSObject& bcc) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract ccRecipients
			  @discussion Recipients of the email included via the `CC` (Carbon Copy) field.
			*/
			virtual JSValue ccRecipients() const TITANIUM_NOEXCEPT final;
			virtual void setCcRecipients(const JSObject& cc) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract html
			  @discussion Determines whether the email message, specifically the contents of [messageBody](Titanium.UI.EmailDialog.messageBody), should be sent as HTML content type rather than plain text.
			*/
			virtual bool html() const TITANIUM_NOEXCEPT final;
			virtual void setHtml(const bool& html) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract messageBody
			  @discussion Email message body.
			*/
			virtual std::string messageBody() const TITANIUM_NOEXCEPT final;
			virtual void setMessageBody(const std::string& body) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract subject
			  @discussion Subject line for the email.
			*/
			virtual std::string subject() const TITANIUM_NOEXCEPT final;
			virtual void setSubject(const std::string& subject) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract toRecipients
			  @discussion Recipients of the email included via the main `TO` field.
			*/
			virtual JSValue toRecipients() const TITANIUM_NOEXCEPT final;
			virtual void setToRecipients(const JSObject& toRecipients) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract addAttachment
			  @discussion Adds an attachment.
			*/
			virtual void addAttachment(const JSObject& attachment) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract isSupported
			  @discussion Indicates whether sending email is supported by the system.
			*/
			virtual bool isSupported() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract open
			  @discussion Opens this email dialog.
			*/
			virtual void open(const JSObject& properties) TITANIUM_NOEXCEPT;

			EmailDialog(const JSContext&) TITANIUM_NOEXCEPT;
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual ~EmailDialog() = default;
			EmailDialog(const EmailDialog&) = default;
			EmailDialog& operator=(const EmailDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			EmailDialog(EmailDialog&&)                 = default;
			EmailDialog& operator=(EmailDialog&&)      = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_bccRecipients() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_ccRecipients() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_html() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_messageBody() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_subject() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_toRecipients() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_addAttachment(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_isSupported(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_open(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getBccRecipients(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setBccRecipients(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getCcRecipients(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setCcRecipients(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHtml(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHtml(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getMessageBody(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setMessageBody(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getSubject(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setSubject(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getToRecipients(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setToRecipients(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			JSValue cancelled__;
			JSValue failed__;
			JSValue saved__;
			JSValue sent__;
			JSValue bccRecipients__;
			JSValue ccRecipients__;
			bool html__;
			std::string messageBody__;
			std::string subject__;
			JSValue toRecipients__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium

#ifdef _restore_FAILED_
#pragma pop_macro("FAILED")
#undef _restore_FAILED_
#endif

#endif // _TITANIUM_EMAILDIALOG_HPP_