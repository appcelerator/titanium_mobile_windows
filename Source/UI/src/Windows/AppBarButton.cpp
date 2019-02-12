/**
* Windows.AppBarButton
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/AppBarButton.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml {

			using namespace ::Windows::UI::Xaml;
			using namespace ::Windows::UI::Xaml::Input;

			AppBarButton::AppBarButton(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.UI.Windows.AppBarButton")
				, icon__(js_context.CreateNull())
			{
				TITANIUM_LOG_DEBUG("AppBarButton::ctor Initialize");
			}

			void AppBarButton::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
			{
				TITANIUM_LOG_DEBUG("AppBarButton::postCallAsConstructor");
				Titanium::Module::postCallAsConstructor(js_context, arguments);

				button__ = ref new Controls::AppBarButton();
			}

			void AppBarButton::JSExportInitialize()
			{
				JSExport<AppBarButton>::SetClassVersion(1);
				JSExport<AppBarButton>::SetParent(JSExport<Titanium::Module>::Class());
				TITANIUM_ADD_PROPERTY(AppBarButton, icon);
				TITANIUM_ADD_PROPERTY(AppBarButton, touchEnabled);
			}

			TITANIUM_PROPERTY_GETTER(AppBarButton, icon)
			{
				return icon__;
			}

			TITANIUM_PROPERTY_SETTER(AppBarButton, icon)
			{
				icon__ = argument;

				/*
				 * This implementation assumes number value for SymbolIcon.
				 * TODO: Support FontIcon and PathIcon which may be passed as JS object.
				 */
				if (argument.IsNumber()) {
					button__->Icon = ref new Controls::SymbolIcon(static_cast<Controls::Symbol>(static_cast<std::uint32_t>(argument)));
				} else {
					TITANIUM_LOG_WARN("AppBarButton::icon: Unknown icon specified");
				}
				return true;
			}

			TITANIUM_PROPERTY_GETTER(AppBarButton, touchEnabled)
			{
				return get_context().CreateBoolean(button__->IsEnabled);
			}

			TITANIUM_PROPERTY_SETTER(AppBarButton, touchEnabled)
			{
				TITANIUM_ASSERT(argument.IsBoolean());
				button__->IsEnabled = static_cast<bool>(argument);
				return true;
			}

			void AppBarButton::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
			{
				Titanium::Module::enableEvent(event_name);
				if (event_name == "click") {
					click_event__ = button__->Click += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
						this->fireEvent("click");
					});
				}
			}

		  void AppBarButton::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
			{
				Titanium::Module::disableEvent(event_name);
				if (event_name == "click") {
					button__->Click -= click_event__;
				}
			}

		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
