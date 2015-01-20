/**
* Titanium.UI.Button for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Button.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		Button::Button(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Titanium::UI::Button(js_context, arguments),
		      button__(ref new Windows::UI::Xaml::Controls::Button())
		{
			TITANIUM_LOG_DEBUG("Button::ctor Initialize");
			setComponent(button__);
		}

		void Button::JSExportInitialize()
		{
			JSExport<Button>::SetClassVersion(1);
			JSExport<Button>::SetParent(JSExport<Titanium::UI::Button>::Class());
		}

		void Button::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_title(title);
			button__->Content = ref new Platform::String(std::wstring(title.begin(), title.end()).c_str());
		}

		void Button::set_backgroundColor(const std::string& backgroundColorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_backgroundColor(backgroundColorName);
			const auto backgroundColor = ColorForName(backgroundColorName);
			button__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
		}

		void Button::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_bottom(bottom);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void Button::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_height(height);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
		}

		void Button::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_left(left);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void Button::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_layout(layout);
			setLayout(layout);
		}

		void Button::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_right(right);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void Button::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_top(top);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void Button::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_width(width);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
		}

		void Button::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Button::enableEvent: (event name '", event_name, "'");

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			if (event_name == "click") {
				if (click_event_count_ == 0) {
					click_event_ = getComponent()->Tapped += ref new TappedEventHandler([this, ctx](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
						auto component = safe_cast<FrameworkElement^>(sender);
						auto position = e->GetPosition(component);

						JSObject  eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
						eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

						this->fireEvent("click", eventArgs);
					});
				}

				++click_event_count_;

				return;
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
