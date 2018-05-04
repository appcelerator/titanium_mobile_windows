/**
 * TitaniumKit Titanium.UI.EmailDialog
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
	class Blob;
	namespace Filesystem
	{
		class File;
	}

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
			TITANIUM_PROPERTY_READONLY_DEF(CANCELLED);

			/*!
			  @property
			  @abstract FAILED
			  @discussion Constant for the `FAILED` status result.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(FAILED);

			/*!
			  @property
			  @abstract SAVED
			  @discussion Constant for the `SAVED` status result. On Android, this property exists but is not used.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(SAVED);

			/*!
			  @property
			  @abstract SENT
			  @discussion Constant for the `SENT` status result.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(SENT);

			/*!
			  @property
			  @abstract bccRecipients
			  @discussion Recipients of the email included via the `BCC` (Blind Carbon Copy) field.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::string>, bccRecipients);

			/*!
			  @property
			  @abstract ccRecipients
			  @discussion Recipients of the email included via the `CC` (Carbon Copy) field.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::string>, ccRecipients);

			/*!
			  @property
			  @abstract html
			  @discussion Determines whether the email message, specifically the contents of [messageBody](Titanium.UI.EmailDialog.messageBody), should be sent as HTML content type rather than plain text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, html);

			/*!
			  @property
			  @abstract messageBody
			  @discussion Email message body.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, messageBody);

			/*!
			  @property
			  @abstract subject
			  @discussion Subject line for the email.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, subject);

			/*!
			  @property
			  @abstract toRecipients
			  @discussion Recipients of the email included via the main `TO` field.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::string>, toRecipients);

			/*!
			  @method
			  @abstract addAttachment
			  @discussion Adds an attachment.
			*/
			virtual void addAttachment(const std::shared_ptr<Titanium::Filesystem::File>& attachment) TITANIUM_NOEXCEPT;
			virtual void addAttachment(const std::shared_ptr<Titanium::Blob>& attachment) TITANIUM_NOEXCEPT;

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
			virtual void open(const bool& animated) TITANIUM_NOEXCEPT;

			EmailDialog(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~EmailDialog() = default;
			EmailDialog(const EmailDialog&) = default;
			EmailDialog& operator=(const EmailDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			EmailDialog(EmailDialog&&)                 = default;
			EmailDialog& operator=(EmailDialog&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(bccRecipients);
			TITANIUM_PROPERTY_DEF(ccRecipients);
			TITANIUM_PROPERTY_DEF(html);
			TITANIUM_PROPERTY_DEF(messageBody);
			TITANIUM_PROPERTY_DEF(subject);
			TITANIUM_PROPERTY_DEF(toRecipients);
			TITANIUM_FUNCTION_DEF(addAttachment);
			TITANIUM_FUNCTION_DEF(isSupported);
			TITANIUM_FUNCTION_DEF(open);
			TITANIUM_FUNCTION_DEF(getBccRecipients);
			TITANIUM_FUNCTION_DEF(setBccRecipients);
			TITANIUM_FUNCTION_DEF(getCcRecipients);
			TITANIUM_FUNCTION_DEF(setCcRecipients);
			TITANIUM_FUNCTION_DEF(getHtml);
			TITANIUM_FUNCTION_DEF(setHtml);
			TITANIUM_FUNCTION_DEF(getMessageBody);
			TITANIUM_FUNCTION_DEF(setMessageBody);
			TITANIUM_FUNCTION_DEF(getSubject);
			TITANIUM_FUNCTION_DEF(setSubject);
			TITANIUM_FUNCTION_DEF(getToRecipients);
			TITANIUM_FUNCTION_DEF(setToRecipients);

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			JSValue cancelled__;
			JSValue failed__;
			JSValue saved__;
			JSValue sent__;
			std::vector<std::string> bccRecipients__;
			std::vector<std::string> ccRecipients__;
			bool html__;
			std::string messageBody__;
			std::string subject__;
			std::vector<std::string> toRecipients__;
			std::vector<std::shared_ptr<Titanium::Blob>> attachments__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium

#ifdef _restore_FAILED_
#pragma pop_macro("FAILED")
#undef _restore_FAILED_
#endif

#endif // _TITANIUM_EMAILDIALOG_HPP_