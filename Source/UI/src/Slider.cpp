/**
* Titanium.UI.Slider for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Slider.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		Slider::Slider(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			  : Titanium::UI::Slider(js_context, arguments),
			  TitaniumWindows::UI::ViewBase(js_context, arguments),
		      slider__(ref new Windows::UI::Xaml::Controls::Slider())
		{
			setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setComponent(slider__);
			TITANIUM_LOG_DEBUG("Slider::ctor CallAsConstructor");
		}

		void Slider::JSExportInitialize()
		{
			JSExport<Slider>::SetClassVersion(1);
			JSExport<Slider>::SetParent(JSExport<Titanium::UI::Slider>::Class());
		}

		void Slider::set_max(const double& max) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Slider::set_max(max);
			slider__->Maximum = max;
		}

		void Slider::set_min(const double& min) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Slider::set_min(min);
			slider__->Minimum = min;
		}

		void Slider::set_value(const double& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Slider::set_value(value);
			slider__->Value = value;
		}

		void Slider::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Slider::enableEvent: (event name '", event_name, "'");

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			if (event_name == "click") {
				if (click_event_count_ == 0) {
					click_event_ = getComponent()->Tapped += ref new TappedEventHandler([this, ctx](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
						auto component = safe_cast<FrameworkElement^>(sender);
						auto position = e->GetPosition(component);

						JSObject eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
						eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

						this->fireEvent("click", eventArgs);
					});
				}

				++click_event_count_;
				return;
			}
			else if (event_name == "change") {
				if (change_event_count_ == 0) {
					change_event_ = slider__->ValueChanged += ref new Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventHandler([this, ctx](Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e) {						

						JSObject eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("value", ctx.CreateNumber(slider__->Value));

						this->fireEvent("change", eventArgs);
					});
				}

				++change_event_count_;
				return;
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
