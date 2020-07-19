/**
* View Helper for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "LayoutEngine/LayoutEngine.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace ViewHelper
		{

			using namespace Windows::UI::Xaml;
			using namespace Windows::UI::Xaml::Controls;
			using namespace Windows::UI::Xaml::Documents;

			template void SetFont<TextBlock^>(const JSContext& js_context, TextBlock^, const Titanium::UI::Font&);
			template void SetFont<TextBox^>(const JSContext& js_context, TextBox^, const Titanium::UI::Font&);
			template void SetFont<Button^>(const JSContext& js_context, Button^, const Titanium::UI::Font&);
			template void SetFont<Span^>(const JSContext& js_context, Span^, const Titanium::UI::Font&);
			template void SetFont<PasswordBox^>(const JSContext& js_context, PasswordBox^, const Titanium::UI::Font&);
			template void SetFont<DatePicker^>(const JSContext& js_context, DatePicker^, const Titanium::UI::Font&);
			template void SetFont<TimePicker^>(const JSContext& js_context, TimePicker^, const Titanium::UI::Font&);
			template void SetFont<ComboBox^>(const JSContext& js_context, ComboBox^, const Titanium::UI::Font&);

			template <typename T>
			void SetFont(const JSContext& js_context, T component, const Titanium::UI::Font& font)
			{
				if (font.fontFamily.length() > 0) {
					const auto fontFamily = TitaniumWindows::UI::View::LookupFont(js_context, font.fontFamily);
					if (fontFamily != nullptr) {
						component->FontFamily = fontFamily;
					}
				}
				if (font.fontSize.length() > 0) {
					// unit specifier should be ignored
					component->FontSize = atof(font.fontSize.c_str());
				}

				if (font.fontStyle == Titanium::UI::FONT_STYLE::ITALIC) {
					component->FontStyle = Windows::UI::Text::FontStyle::Italic;
				} else if (font.fontStyle == Titanium::UI::FONT_STYLE::NORMAL) {
					component->FontStyle = Windows::UI::Text::FontStyle::Normal;
				}
				// TODO Windows supports Oblique: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontstyle.aspx

				if (font.fontWeight == Titanium::UI::FONT_WEIGHT::BOLD) {
					component->FontWeight = Windows::UI::Text::FontWeights::Bold;
				} else if (font.fontWeight == Titanium::UI::FONT_WEIGHT::NORMAL) {
					component->FontWeight = Windows::UI::Text::FontWeights::Normal;
				} else if (font.fontWeight == Titanium::UI::FONT_WEIGHT::SEMIBOLD) {
					component->FontWeight = Windows::UI::Text::FontWeights::SemiBold;
				}
				// TODO Windows supports a large number of other weights: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontweights
			}

			ResourceDictionary^ LookupXamlResource(Platform::String^ source)
			{
				if (source->IsEmpty()) {
					return nullptr;
				}
				const auto rd = ref new ResourceDictionary();
				try {
					rd->Source = ref new Windows::Foundation::Uri(source);
				} catch (Platform::FailureException^ e) {
					return nullptr;
				}
				return rd;
			}
		} // namespace ViewHelper
	}  // namespace UI
}  // namespace TitaniumWindows
