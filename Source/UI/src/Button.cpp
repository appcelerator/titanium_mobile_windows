/**
* Titanium.UI.Button for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Button.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Input;

		Button::Button(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::UI::Button(js_context)
		{
			TITANIUM_LOG_DEBUG("Button::ctor");
		}

		void Button::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Button::postCallAsConstructor(js_context, arguments);
			Titanium::UI::Button::setLayoutDelegate<WindowsButtonLayoutDelegate>();

			button__ = ref new Controls::Button();
			button__->VerticalAlignment = VerticalAlignment::Stretch;
			button__->HorizontalAlignment = HorizontalAlignment::Stretch;
			button__->FontSize = DefaultFontSize;
			button__->BorderThickness = 0;

			// TIMOB-19143: reset MinWidth to fix size issues
			button__->MinWidth = 0;

			border__ = ref new Controls::Border();
			border__->Child = button__;

			getViewLayoutDelegate<WindowsButtonLayoutDelegate>()->setComponent(border__, button__, border__);
		}

		void Button::JSExportInitialize()
		{
			JSExport<Button>::SetClassVersion(1);
			JSExport<Button>::SetParent(JSExport<Titanium::UI::Button>::Class());
		}

		void Button::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_color(colorName);

			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
			button__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void Button::set_image(const std::string& image) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_image(image);

			// Just call set_backgroundImage behind the scenes...and it should just work.
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->set_backgroundImage(image);
		}

		void Button::set_imageAsBlob(const std::shared_ptr<Titanium::Blob>& image) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_imageAsBlob(image);
			if (image != nullptr) {
				getViewLayoutDelegate<WindowsViewLayoutDelegate>()->set_backgroundImage(image);
			}
		}

		void Button::set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_font(font);
			TitaniumWindows::UI::ViewHelper::SetFont<Windows::UI::Xaml::Controls::Button^>(get_context(), button__, font);
		}

		void Button::set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_textAlign(textAlign);

			if (textAlign == Titanium::UI::TEXT_ALIGNMENT::CENTER) {
				button__->HorizontalContentAlignment = HorizontalAlignment::Center;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::LEFT) {
				button__->HorizontalContentAlignment = HorizontalAlignment::Left;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::RIGHT) {
				button__->HorizontalContentAlignment = HorizontalAlignment::Right;
			}
			// TODO Windows supports JUSTIFY!
		}

		void Button::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_title(title);
			button__->Content = TitaniumWindows::Utility::ConvertUTF8String(title);
		}

		void Button::set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_verticalAlign(verticalAlign);
			if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM) {
				button__ ->VerticalContentAlignment = VerticalAlignment::Bottom;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER) {
				button__->VerticalContentAlignment = VerticalAlignment::Center;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP) {
				button__->VerticalContentAlignment = VerticalAlignment::Top;
			}
			// TODO Windows supports stretch!
		}

		void Button::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			//
			// Disable some touch events because Xaml Button has a inconsistency on Pointer event handling.
			//
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->filterEvents({ "touchstart", "touchend", "touchcancel" });

			Titanium::UI::Button::enableEvent(event_name);
		}
	} // namespace UI
} // namespace TitaniumWindows
