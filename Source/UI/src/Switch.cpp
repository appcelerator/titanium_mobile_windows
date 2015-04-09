/**
 * Titanium.UI.Switch for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Switch.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

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

			Titanium::UI::Switch::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(switch__);
		}

		void Switch::JSExportInitialize() {
			JSExport<Switch>::SetClassVersion(1);
			JSExport<Switch>::SetParent(JSExport<Titanium::UI::Switch>::Class());
		}

		void Switch::set_value(const bool& value) TITANIUM_NOEXCEPT
		{
			//Titanium::UI::Switch::set_value(value);
			switch__->IsOn = value;
		}

		void Switch::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Switch::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			auto component = getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();

			if (event_name == "click") {
				click_event_ = component->Tapped += ref new TappedEventHandler([this, ctx](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
					auto component = safe_cast<FrameworkElement^>(sender);
					auto position = e->GetPosition(component);

					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
					eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

					this->fireEvent("click", eventArgs);
				});
			} else if (event_name == "change") {
				change_event_ = switch__->Toggled += ref new Windows::UI::Xaml::RoutedEventHandler([this, ctx](Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {						
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("value", ctx.CreateBoolean(get_value()));

					this->fireEvent("change", eventArgs);
				});
			}
		}

	}  // namespace UI
}  // namespace TitaniumWindows