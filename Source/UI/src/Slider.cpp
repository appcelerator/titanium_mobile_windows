/**
* Titanium.UI.Slider for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Slider.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		Slider::Slider(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::Slider(js_context)
		{
		}

		void Slider::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Slider::postCallAsConstructor(js_context, arguments);	
			border__ = ref new Windows::UI::Xaml::Controls::Border();
			slider__ = ref new Windows::UI::Xaml::Controls::Slider();

			border__->Child = slider__;

			Titanium::UI::Slider::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			layout->setStyleComponent(slider__);
			layout->setComponent(border__, nullptr, border__);
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

		double Slider::get_value() const TITANIUM_NOEXCEPT
		{
			if (slider__) {
				return slider__->Value;
			}
			return 0;
		}

		void Slider::set_value(const double& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Slider::set_value(value);
			slider__->Value = value;
		}

		void Slider::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Slider::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			auto component = getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();

			if (event_name == "change") {
				change_event_ = slider__->ValueChanged += ref new Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventHandler([this, ctx](Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e) {						

					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("value", ctx.CreateNumber(slider__->Value));

					this->fireEvent("change", eventArgs);
				});
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
