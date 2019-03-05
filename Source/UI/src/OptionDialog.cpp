/**
 * Titanium.UI.OptionDialog for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/OptionDialog.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"
#include "Titanium/API.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include <ppltasks.h>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Popups;
		using namespace Windows::Foundation;

		OptionDialog::OptionDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::OptionDialog(js_context)
		{
			TITANIUM_LOG_DEBUG("OptionDialog::ctor Initialize");
		}

		void OptionDialog::JSExportInitialize() {
			JSExport<OptionDialog>::SetClassVersion(1);
			JSExport<OptionDialog>::SetParent(JSExport<Titanium::UI::OptionDialog>::Class());
		}

		void OptionDialog::show(const Titanium::UI::OptionDialogShowParams& params) TITANIUM_NOEXCEPT
		{
			std::string title = get_title();

			Windows::UI::Popups::MessageDialog^ dialog = ref new MessageDialog(TitaniumWindows::Utility::ConvertUTF8String(title));
			dialog->DefaultCommandIndex = get_selectedIndex();

			const auto cancelIndex = get_cancel();
			if (cancelIndex >= 0) {
				dialog->CancelCommandIndex = get_cancel();
			}
			auto maxButtons = options__.size();
			if (options__.size() > MaxButtonCount) {
				auto Titanium_property = get_context().get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
				auto Titanium = static_cast<JSObject>(Titanium_property);

				auto Object_property = Titanium.GetProperty("API");
				TITANIUM_ASSERT(Object_property.IsObject());  // precondition
				auto api = static_cast<JSObject>(Object_property);
				auto native_api = api.GetPrivate<Titanium::API>();
				native_api->error("Number of buttons exceeds platform maximum (" + std::to_string(MaxButtonCount) + "), list will be truncated.");
				maxButtons = MaxButtonCount;
			}
			for (size_t i = 0; i < maxButtons; i++) {
				dialog->Commands->Append(ref new Windows::UI::Popups::UICommand(TitaniumWindows::Utility::ConvertUTF8String(options__[i]), nullptr, PropertyValue::CreateInt32(i)));
			}

			try {
				concurrency::create_task(dialog->ShowAsync()).then([this](IUICommand^ command) {
					TITANIUM_EXCEPTION_CATCH_START {
						std::int32_t index = 0;
						if (command != nullptr) {
							auto casted = dynamic_cast<IPropertyValue^>(command->Id);
							if (casted != nullptr) {
								index = casted->GetInt32();
							}
						}
						const JSContext ctx = get_context();
						JSObject eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("index", ctx.CreateNumber(index));
						eventArgs.SetProperty("cancel", ctx.CreateBoolean(index == get_cancel()));
						eventArgs.SetProperty("destructive", ctx.CreateNumber(get_destructive()));
						fireEvent("click", eventArgs);
					} TITANIUMWINDOWS_EXCEPTION_CATCH_END
				});
			} catch (::Platform::Exception^ ce) {
				// Typically would have happened on phone if we supplied more than max buttons allowed
				detail::ThrowRuntimeError("Ti.UI.OptionDialog", "Exception during show(): " + Utility::ConvertUTF8String(ce->Message));
			} catch (...) {
				detail::ThrowRuntimeError("Ti.UI.OptionDialog", "Exception during show()");
			}
		}

	}  // namespace UI
}  // namespace TitaniumWindows