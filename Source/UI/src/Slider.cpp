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
		Slider::Slider(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::UI::Slider(js_context),
		      slider__(ref new Windows::UI::Xaml::Controls::Slider())
		{
			TITANIUM_LOG_DEBUG("Slider::ctor Initialize");
		}

		Slider::Slider(const Slider& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Titanium::UI::Slider(rhs, arguments),
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

		void Slider::set_backgroundColor(const std::string& backgroundColorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_backgroundColor(backgroundColorName);
			const auto backgroundColor = ColorForName(backgroundColorName);
			slider__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
		}

		void Slider::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_bottom(bottom);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void Slider::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_height(height);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
		}

		void Slider::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_left(left);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void Slider::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_layout(layout);
			setLayout(layout);
		}

		void Slider::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_right(right);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void Slider::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_top(top);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void Slider::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_width(width);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
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
