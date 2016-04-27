/**
* Titanium.UI.AlertDialog for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/AlertDialog.hpp"
#include "Titanium/API.hpp"
#include <windows.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Popups;
		using namespace Windows::Foundation;

		std::vector<std::shared_ptr<AlertDialog>> AlertDialog::dialog_queue__;

		AlertDialog::AlertDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::UI::AlertDialog(js_context)
		{
			TITANIUM_LOG_DEBUG("AlertDialog::ctor");
		}

		void AlertDialog::JSExportInitialize()
		{
			JSExport<AlertDialog>::SetClassVersion(1);
			JSExport<AlertDialog>::SetParent(JSExport<Titanium::UI::AlertDialog>::Class());
		}

		void AlertDialog::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
		{
			dialog__ = ref new Windows::UI::Popups::MessageDialog("");

			on_click__ = [this](IUICommand^ command) {
				std::int32_t index = 0;
				if (command != nullptr) {
					const auto casted = dynamic_cast<IPropertyValue^>(command->Id);
					if (casted != nullptr) {
						index = casted->GetInt32();
					}
				}
				const JSContext ctx = get_context();
				JSObject eventArgs = ctx.CreateObject();
				eventArgs.SetProperty("index", ctx.CreateNumber(index));
				eventArgs.SetProperty("cancel", ctx.CreateBoolean(index == get_cancel()));
				fireEvent("click", eventArgs);

				dialog_queue__.erase(dialog_queue__.begin());

				if (dialog_queue__.size() > 0) {
					const auto next = dialog_queue__.at(0);
					concurrency::create_task(next->dialog__->ShowAsync()).then(next->on_click__);
				}
			};
		}

		void AlertDialog::show() TITANIUM_NOEXCEPT
		{
			const std::string title   = get_title();
			const std::string message = get_message();

			dialog__->Content = TitaniumWindows::Utility::ConvertUTF8String(message);
			dialog__->Title = TitaniumWindows::Utility::ConvertUTF8String(title);
			dialog__->DefaultCommandIndex = 0;

			const auto cancelIndex = get_cancel();
			if (cancelIndex >= 0) {
				dialog__->CancelCommandIndex = get_cancel();
			}

			auto maxButtons = buttonNames__.size();
			if (buttonNames__.size() > MaxButtonCount) {
				const auto Titanium_property = get_context().get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
				const auto Titanium = static_cast<JSObject>(Titanium_property);

				const auto Object_property = Titanium.GetProperty("API");
				TITANIUM_ASSERT(Object_property.IsObject());  // precondition
				const auto api = static_cast<JSObject>(Object_property);
				const auto native_api = api.GetPrivate<Titanium::API>();
				native_api->error("Number of buttons exceeds platform maximum (" + std::to_string(MaxButtonCount) + "), list will be truncated.");
				maxButtons = MaxButtonCount;
			}
			for (size_t i = 0; i < maxButtons; i++) {
				dialog__->Commands->Append(ref new Windows::UI::Popups::UICommand(TitaniumWindows::Utility::ConvertUTF8String(buttonNames__[i]), nullptr, PropertyValue::CreateInt32(i)));
			}

			try {
				dialog_queue__.push_back(get_object().GetPrivate<AlertDialog>());

				// show first dialog and then proceed to next after finishing click event
				if (dialog_queue__.size() == 1) {
					dialog_task__ = dialog__->ShowAsync();
					concurrency::create_task(dialog_task__).then(on_click__);
				}

			} catch (::Platform::COMException^ ce) {
				// Typically would have happened on phone if we supplied more than max buttons allowed
				detail::ThrowRuntimeError("Ti.UI.AlertDialog", "Exception during show(): " + Utility::ConvertUTF8String(ce->Message));
			} catch (...) {
				detail::ThrowRuntimeError("Ti.UI.AlertDialog", "Exception during show()");
			}
		}

		void AlertDialog::hide() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			if (IS_WINDOWS_MOBILE) {
				TITANIUM_MODULE_LOG_WARN("AlertDialog::hide() is not supported on Windows 10 Mobile");
				return;
			}
#elif defined(IS_WINDOWS_PHONE)
			TITANIUM_MODULE_LOG_WARN("AlertDialog::hide() is not supported on Windows Phone");
			return;
#endif
			if (dialog_task__ != nullptr) {
				dialog_task__->Cancel();
				if (dialog_queue__.size() > 0) {
					dialog_queue__.erase(dialog_queue__.begin());
				}
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
