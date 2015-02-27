/**
 * Titanium.UI.EmailDialog for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_EMAILDIALOG_HPP_
#define _TITANIUMWINDOWS_EMAILDIALOG_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include <vector>
#include <Windows.h>

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.EmailDialog implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT EmailDialog final : public Titanium::UI::EmailDialog, public JSExport<EmailDialog>
		{

		public:
			EmailDialog(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~EmailDialog()                  = default;
			EmailDialog(const EmailDialog&)            = default;
			EmailDialog& operator=(const EmailDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			EmailDialog(EmailDialog&&)                 = default;
			EmailDialog& operator=(EmailDialog&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void addAttachment(const JSObject& attachment) TITANIUM_NOEXCEPT override final;
			virtual bool isSupported() TITANIUM_NOEXCEPT override final;
			virtual void open(const JSObject& properties) TITANIUM_NOEXCEPT override final;
			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

		private:

#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
			void setRecipients(const JSObject& arg, Windows::Foundation::Collections::IVector<Windows::ApplicationModel::Email::EmailRecipient^>^ recipients);
#endif

#pragma warning(push)
#pragma warning(disable : 4251)
			std::vector<JSObject> attachments__;
#pragma warning(pop)

			// Event handlers
			Windows::Foundation::EventRegistrationToken complete_event__;
			unsigned int complete_event_count__{0};
		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_EMAILDIALOG_HPP_