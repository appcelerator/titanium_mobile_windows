/**
* Windows.AppBarToggleButton
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/AppBarToggleButton.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml {

			using namespace ::Windows::UI::Xaml;

			AppBarToggleButton::AppBarToggleButton(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.UI.Windows.AppBarToggleButton")
				, icon__(js_context.CreateNull())
			{
				TITANIUM_LOG_DEBUG("AppBarToggleButton::ctor Initialize");
			}

			void AppBarToggleButton::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
			{
				TITANIUM_LOG_DEBUG("AppBarToggleButton::postCallAsConstructor");
				Titanium::Module::postCallAsConstructor(js_context, arguments);

				button__ = ref new Controls::AppBarToggleButton();
			}

			void AppBarToggleButton::JSExportInitialize()
			{
				JSExport<AppBarToggleButton>::SetClassVersion(1);
				JSExport<AppBarToggleButton>::SetParent(JSExport<Titanium::Module>::Class());
				TITANIUM_ADD_PROPERTY(AppBarToggleButton, icon);
				TITANIUM_ADD_PROPERTY(AppBarToggleButton, checked);
				TITANIUM_ADD_PROPERTY(AppBarToggleButton, touchEnabled);
			}

			TITANIUM_PROPERTY_GETTER(AppBarToggleButton, icon)
			{
				return icon__;
			}

			TITANIUM_PROPERTY_SETTER(AppBarToggleButton, icon)
			{
				icon__ = argument;

				if (argument.IsNumber()) {
					button__->Icon = ref new Controls::SymbolIcon(static_cast<Controls::Symbol>(static_cast<std::uint32_t>(argument)));
				} else {
					TITANIUM_LOG_WARN("AppBarToggleButton::icon: Unknown icon specified");
				}
				return true;
			}

			TITANIUM_PROPERTY_GETTER(AppBarToggleButton, checked)
			{
				return get_context().CreateBoolean(button__->IsChecked->Value);
			}

			TITANIUM_PROPERTY_SETTER(AppBarToggleButton, checked)
			{
				TITANIUM_ASSERT(argument.IsBoolean());
				button__->IsChecked = static_cast<bool>(argument);
				return true;
			}

			TITANIUM_PROPERTY_GETTER(AppBarToggleButton, touchEnabled)
			{
				return get_context().CreateBoolean(button__->IsEnabled);
			}

			TITANIUM_PROPERTY_SETTER(AppBarToggleButton, touchEnabled)
			{
				TITANIUM_ASSERT(argument.IsBoolean());
				button__->IsEnabled = static_cast<bool>(argument);
				return true;
			}

			void AppBarToggleButton::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
			{
				Titanium::Module::enableEvent(event_name);

				if (event_name == "click") {
					const auto ctx = this->get_context();
					click_event__ = button__->Click += ref new RoutedEventHandler([this, ctx](Platform::Object^ sender, RoutedEventArgs^ e) {
						auto eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("checked", ctx.CreateBoolean(button__->IsChecked->Value));
						this->fireEvent("click", eventArgs);
					});

				}
			}

			void AppBarToggleButton::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
			{
				Titanium::Module::disableEvent(event_name);
				if (event_name == "click") {
					button__->Tapped -= click_event__;
				}
			}

		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
