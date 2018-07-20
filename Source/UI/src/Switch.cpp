/**
 * Titanium.UI.Switch for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Switch.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		Switch::Switch(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::Switch(js_context)
		{
		}

		void Switch::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Switch::postCallAsConstructor(js_context, arguments);	
			
			switch__ = ref new Windows::UI::Xaml::Controls::ToggleSwitch();
			switch__->OnContent = "On";
			switch__->OffContent = "Off";
			switch__->Toggled += ref new Windows::UI::Xaml::RoutedEventHandler([this](Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
				Titanium::UI::Switch::set_value(!get_value());
			});

			border__ = ref new Windows::UI::Xaml::Controls::Border();
			border__->Child = switch__;

			Titanium::UI::Switch::setLayoutDelegate<WindowsViewLayoutDelegate>();
			const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			layout->setStyleComponent(switch__);
			layout->setComponent(border__, nullptr, border__);
		}

		void Switch::JSExportInitialize() {
			JSExport<Switch>::SetClassVersion(1);
			JSExport<Switch>::SetParent(JSExport<Titanium::UI::Switch>::Class());
		}

		void Switch::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Switch::set_color(colorName);
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
			switch__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void Switch::set_enabled(const bool& enabled) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Switch::set_enabled(enabled);
			switch__->IsEnabled = enabled;
		}

		void Switch::set_titleOff(const std::string& titleOff) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Switch::set_titleOff(titleOff);
			switch__->OffContent = TitaniumWindows::Utility::ConvertUTF8String(titleOff);
		}

		void Switch::set_titleOn(const std::string& titleOn) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Switch::set_titleOn(titleOn);
			switch__->OnContent = TitaniumWindows::Utility::ConvertUTF8String(titleOn);
		}

		bool Switch::get_value() const TITANIUM_NOEXCEPT
		{
			return switch__ && switch__->IsOn;
		}

		void Switch::set_value(const bool& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Switch::set_value(value);
			switch__->IsOn = value;
		}

		void Switch::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Switch::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			auto component = getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();

			if (event_name == "change") {
				change_event_ = switch__->Toggled += ref new Windows::UI::Xaml::RoutedEventHandler([this, ctx](Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {						
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("value", ctx.CreateBoolean(get_value()));

					this->fireEvent("change", eventArgs);
				});
			}
		}

	}  // namespace UI
}  // namespace TitaniumWindows