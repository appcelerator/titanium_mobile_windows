/**
* Titanium.UI.Label for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Label.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"

#include "TitaniumWindows/Utility.hpp"

#define DEFAULT_FONT_SIZE 20

namespace TitaniumWindows
{
	namespace UI
	{
		// FIXME What file formats does windows support for fonts? We need to limit here! Most of what I read says only TTF, but I see some mentions of OpenType
		static const std::string ti_label_js = R"TI_LABEL_JS(
	this.exports = {};
	this.exports.getFontFilePath = function(fontFamily) {
		var iconsFolder = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory, 'fonts');
		var files = iconsFolder.getDirectoryListing();
		for (var i = 0; i < files.length; i++) {
			var name = files[i];
			if (name.toLowerCase() == fontFamily.toLowerCase() || name.toLowerCase().indexOf(fontFamily.toLowerCase() + '.') == 0) {
				return name;
			}
		}
		return null;
	};
	)TI_LABEL_JS";

		Label::Label(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::Label(js_context)
		{
		}

		void Label::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Label::postCallAsConstructor(js_context, arguments);
			
			label__ = ref new Windows::UI::Xaml::Controls::TextBlock();
			Titanium::UI::Label::setLayoutDelegate<WindowsViewLayoutDelegate>();

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);

			label__->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
			label__->TextTrimming = Windows::UI::Xaml::TextTrimming::Clip;
			label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
			label__->FontSize = DEFAULT_FONT_SIZE;

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(label__);

		}

		void Label::JSExportInitialize()
		{
			JSExport<Label>::SetClassVersion(1);
			JSExport<Label>::SetParent(JSExport<Titanium::UI::Label>::Class());
		}

		void Label::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_color(colorName);
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
			label__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void Label::set_text(const std::string& text) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_text(text);
			label__->Text = TitaniumWindows::Utility::ConvertUTF8String(text);
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

		void Label::set_font(const Titanium::UI::Font font) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Label::set_font(font);
			// TODO This lookup map should be global, not per-instance of a Label!
			// Did we already look up this font?
			auto family = font.fontFamily;
			if (family.length() > 0) {
				auto path = family;
				if (custom_fonts__.find(family) == custom_fonts__.end()) {
					// Look up to see if this is a custom font!
					auto export_object = get_context().CreateObject();
					get_context().JSEvaluateScript(ti_label_js, export_object);
					TITANIUM_ASSERT(export_object.HasProperty("exports"));
					auto exports = export_object.GetProperty("exports");
					TITANIUM_ASSERT(exports.IsObject());
					auto exports_object = static_cast<JSObject>(exports);
					auto eval_result = exports_object.GetProperty("getFontFilePath");
					TITANIUM_ASSERT(eval_result.IsObject());
					auto func = static_cast<JSObject>(eval_result);
					TITANIUM_ASSERT(func.IsFunction());
					auto result = func(family, get_context().get_global_object());
					if (result.IsNull()) { // we have no custom font by this name, assume it's a built-in font
						path = family;
					} else {
						TITANIUM_ASSERT(result.IsString()); // custom font file
						const auto file_name = static_cast<std::string>(result);
						path = "/fonts/" + file_name + "#" + family;
					}
				}
				
				custom_fonts__.emplace(family, path);
				label__->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily(Utility::ConvertUTF8String(path));
			}
			if (font.fontSize.length() > 0) {
				label__->FontSize = std::stod(font.fontSize);
			}

			if (font.fontStyle == Titanium::UI::FONT_STYLE::ITALIC) {
				label__->FontStyle = Windows::UI::Text::FontStyle::Italic;
			} else if (font.fontStyle == Titanium::UI::FONT_STYLE::NORMAL) {
				label__->FontStyle = Windows::UI::Text::FontStyle::Normal;
			}
			// TODO Windows supports Oblique: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontstyle.aspx

			if (font.fontWeight == Titanium::UI::FONT_WEIGHT::BOLD) {
				label__->FontWeight = Windows::UI::Text::FontWeights::Bold;
			} else if (font.fontWeight == Titanium::UI::FONT_WEIGHT::NORMAL) {
				label__->FontWeight = Windows::UI::Text::FontWeights::Normal;
			} else if (font.fontWeight == Titanium::UI::FONT_WEIGHT::SEMIBOLD) {
				label__->FontWeight = Windows::UI::Text::FontWeights::SemiBold;
			}
			// TODO Windows supports a large number of other weights: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontweights
		}

		void Label::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			auto component = getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();

			if (event_name == "click") {
				click_event_ = component->Tapped += ref new TappedEventHandler([this, ctx](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
					auto component = safe_cast<FrameworkElement^>(sender);
					auto position = e->GetPosition(component);

					JSObject  eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
					eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

					this->fireEvent("click", eventArgs);
				});
			}
		}

	} // namespace UI
} // namespace TitaniumWindows
