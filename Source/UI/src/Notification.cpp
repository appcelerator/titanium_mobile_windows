/**
 * Titanium.UI.Notification for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Notification.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		Notification::Notification(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::Notification(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("Notification::ctor Initialize");
		}

		void Notification::JSExportInitialize() {
			JSExport<Notification>::SetClassVersion(1);
			JSExport<Notification>::SetParent(JSExport<Titanium::UI::Notification>::Class());
		}

		void Notification::show() TITANIUM_NOEXCEPT
		{
			using namespace Windows::UI::Notifications;
			auto xml = ToastNotificationManager::GetTemplateContent(ToastTemplateType::ToastText02); // only 2 is supported on phone 8.1
			auto textNodes = xml->GetElementsByTagName("text");
			// TODO Should we auto split the message so first line gets inserted in as first text node (bold) and any others get in the second?
			textNodes->GetAt(0)->AppendChild(xml->CreateTextNode(TitaniumWindows::Utility::ConvertUTF8String(get_message())));
			textNodes->GetAt(1)->AppendChild(xml->CreateTextNode(""));
#if !defined(IS_WINDOWS_PHONE)
			// Specifying duration length is only supported on WinStore, phone always does short
			auto toast_node = xml->SelectSingleNode("/toast");
			auto attr = xml->CreateAttribute("duration");
			if (get_duration() == Titanium::UI::NOTIFICATION_DURATION::LONG) {
				attr->NodeValue = "long";
			} else {
				attr->NodeValue = "short";
			}
			toast_node->Attributes->SetNamedItem(attr);
#endif
			auto notification = ref new ToastNotification(xml);
			auto notifier = ToastNotificationManager::CreateToastNotifier();
			notifier->Show(notification);
		}

	}  // namespace UI
}  // namespace TitaniumWindows