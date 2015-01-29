/**
* Titanium.UI.Label for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Label.hpp"

#define DEFAULT_FONT_SIZE 20

namespace TitaniumWindows
{
	namespace UI
	{
		Label::Label(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			  : Titanium::UI::Label(js_context, arguments),
			   Titanium::UI::View(js_context, arguments),
			    ViewBase(js_context, arguments),
		        label__(ref new Windows::UI::Xaml::Controls::TextBlock())
		{
			TITANIUM_LOG_DEBUG("Label::ctor");

			label__->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
			label__->TextTrimming = Windows::UI::Xaml::TextTrimming::Clip;
			label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
			label__->FontSize = DEFAULT_FONT_SIZE;
			setComponent(label__);
		}

		void Label::JSExportInitialize()
		{
			JSExport<Label>::SetClassVersion(1);
			JSExport<Label>::SetParent(JSExport<Titanium::UI::Label>::Class());
		}

		void Label::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_color(colorName);
			const auto color_obj = ColorForName(colorName);
			label__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void Label::set_text(const std::string& text) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_text(text);
			label__->Text = ref new Platform::String(std::wstring(text.begin(), text.end()).c_str());
		}

		void Label::set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_textAlign(textAlign);
			if (textAlign == Titanium::UI::TEXT_ALIGNMENT::CENTER) {
				label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Center;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::LEFT) {
				label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Left;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::RIGHT) {
				label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Right;
			}
			// TODO Windows supports JUSTIFY!
		}

		void Label::set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_verticalAlign(verticalAlign);
			if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM) {
				label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER) {
				label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP) {
				label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
			}
			// TODO Windows supports stretch!
		}

		void Label::set_wordWrap(const bool& wordWrap) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_wordWrap(wordWrap);
			label__->TextWrapping = wordWrap ? Windows::UI::Xaml::TextWrapping::Wrap : Windows::UI::Xaml::TextWrapping::NoWrap;
		}

		void Label::set_fontFamily(const std::string& family) TITANIUM_NOEXCEPT
		{
			label__->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily(ref new Platform::String(std::wstring(family.begin(), family.end()).c_str()));
		}

		void Label::set_fontSize(const JSValue& size) TITANIUM_NOEXCEPT
		{
			label__->FontSize = static_cast<double>(size);
		}

		void Label::set_fontStyle(const std::string& style) TITANIUM_NOEXCEPT
		{
			if (style == "italic") {
				label__->FontStyle = Windows::UI::Text::FontStyle::Italic;
			} else if (style == "normal") {
				label__->FontStyle = Windows::UI::Text::FontStyle::Normal;
			}
			// TODO Windows supports Oblique: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontstyle.aspx
		}

		void Label::set_fontWeight(const std::string& weight) TITANIUM_NOEXCEPT
		{
			if (weight == "bold") {
				label__->FontWeight = Windows::UI::Text::FontWeights::Bold;
			} else if (weight == "normal") {
				label__->FontWeight = Windows::UI::Text::FontWeights::Normal;
			} else if (weight == "semibold") {
				label__->FontWeight = Windows::UI::Text::FontWeights::SemiBold;
			}
			// TODO Windows supports a large number of other weights: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontweights
		}

		void Label::set_textStyle(const Titanium::UI::TEXT_STYLE& textStyle) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_textStyle(textStyle);
		}

		void Label::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Label::enableEvent: (event name '", event_name, "'");

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
