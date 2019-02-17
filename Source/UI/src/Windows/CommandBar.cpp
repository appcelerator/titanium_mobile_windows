/**
* Windows.CommandBar
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/CommandBar.hpp"
#include "TitaniumWindows/UI/Windows/AppBarButton.hpp"
#include "TitaniumWindows/UI/Windows/AppBarToggleButton.hpp"
#include "TitaniumWindows/UI/Windows/AppBarSeparator.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml {

			using namespace ::Windows::UI::Xaml;

			CommandBar::CommandBar(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.UI.Windows.CommandBar")
				, items__(js_context.CreateArray())
			{
				TITANIUM_LOG_DEBUG("CommandBar::ctor Initialize");
			}

			void CommandBar::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
			{
				TITANIUM_LOG_DEBUG("CommandBar::postCallAsConstructor");
				Titanium::Module::postCallAsConstructor(js_context, arguments);

				commandBar__ = ref new Controls::CommandBar();
			}

			void CommandBar::JSExportInitialize()
			{
				JSExport<CommandBar>::SetClassVersion(1);
				JSExport<CommandBar>::SetParent(JSExport<Titanium::Module>::Class());
				TITANIUM_ADD_PROPERTY(CommandBar, items);
			}

			TITANIUM_PROPERTY_GETTER(CommandBar, items)
			{
				return items__;
			}

			/*
			 * TODO: We should enable use of the secondary commands property too.
			 * Not sure if we want another property or we want to overload items,
			 * so that if it is an array containing two arrays,
			 * the first inner array is primary and second is secondary?
			 *
			 * May be more logical to have a second property?
			 */
			TITANIUM_PROPERTY_SETTER(CommandBar, items)
			{
				TITANIUM_ASSERT(argument.IsObject());
				items__ = argument;

				const auto itemsObj = static_cast<JSObject>(argument);
				TITANIUM_ASSERT(itemsObj.IsArray());
				const auto items = static_cast<std::vector<JSValue>>(static_cast<JSArray>(itemsObj));

				commandBar__->PrimaryCommands->Clear();

				for (auto item : items) {
					if (item.IsObject()) {
						const auto button       = static_cast<JSObject>(item).GetPrivate<TitaniumWindows::UI::WindowsXaml::AppBarButton>();
						const auto toggleButton = static_cast<JSObject>(item).GetPrivate<TitaniumWindows::UI::WindowsXaml::AppBarToggleButton>();
						const auto separator    = static_cast<JSObject>(item).GetPrivate<TitaniumWindows::UI::WindowsXaml::AppBarSeparator>();

						if (button != nullptr) {
							commandBar__->PrimaryCommands->Append(button->getComponent());
						} else if (toggleButton != nullptr) {
							commandBar__->PrimaryCommands->Append(toggleButton->getComponent());
						} else if (separator != nullptr) {
							commandBar__->PrimaryCommands->Append(separator->getComponent());
						}
					}
				}

				return true;
			}

		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
