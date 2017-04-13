/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.TextBlock
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_TEXTBLOCK_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_TEXTBLOCK_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.FrameworkElement.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Controls
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT TextBlock : public ::Titanium::Windows::UI::Xaml::FrameworkElement, public JSExport<TextBlock>
		{

		public:
			TITANIUM_PROPERTY_DEF(TextWrapping);
			TITANIUM_PROPERTY_DEF(TextTrimming);
			TITANIUM_PROPERTY_DEF(TextAlignment);
			TITANIUM_PROPERTY_DEF(Text);
			TITANIUM_PROPERTY_DEF(Padding);
			TITANIUM_PROPERTY_DEF(LineStackingStrategy);
			TITANIUM_PROPERTY_DEF(Foreground);
			TITANIUM_PROPERTY_DEF(FontWeight);
			TITANIUM_PROPERTY_DEF(FontStyle);
			TITANIUM_PROPERTY_DEF(FontStretch);
			TITANIUM_PROPERTY_DEF(FontSize);
			TITANIUM_PROPERTY_DEF(FontFamily);
			TITANIUM_PROPERTY_DEF(LineHeight);
			TITANIUM_PROPERTY_DEF(IsTextSelectionEnabled);
			TITANIUM_PROPERTY_DEF(CharacterSpacing);
			TITANIUM_PROPERTY_READONLY_DEF(SelectedText);
			TITANIUM_PROPERTY_READONLY_DEF(SelectionEnd);
			TITANIUM_PROPERTY_READONLY_DEF(SelectionStart);
			TITANIUM_PROPERTY_READONLY_DEF(ContentEnd);
			TITANIUM_PROPERTY_READONLY_DEF(ContentStart);
			TITANIUM_PROPERTY_READONLY_DEF(BaselineOffset);
			TITANIUM_PROPERTY_READONLY_DEF(Inlines);
			TITANIUM_PROPERTY_DEF(OpticalMarginAlignment);
			TITANIUM_PROPERTY_DEF(TextReadingOrder);
			TITANIUM_PROPERTY_DEF(TextLineBounds);
			TITANIUM_PROPERTY_DEF(SelectionHighlightColor);
			TITANIUM_PROPERTY_DEF(MaxLines);
			TITANIUM_PROPERTY_DEF(IsColorFontEnabled);
			TITANIUM_PROPERTY_READONLY_DEF(SelectionHighlightColorProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsColorFontEnabledProperty);
			TITANIUM_PROPERTY_READONLY_DEF(MaxLinesProperty);
			TITANIUM_PROPERTY_READONLY_DEF(OpticalMarginAlignmentProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TextLineBoundsProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TextReadingOrderProperty);
			TITANIUM_PROPERTY_READONLY_DEF(CharacterSpacingProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontFamilyProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontSizeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontStretchProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontStyleProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontWeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ForegroundProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsTextSelectionEnabledProperty);
			TITANIUM_PROPERTY_READONLY_DEF(LineHeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(LineStackingStrategyProperty);
			TITANIUM_PROPERTY_READONLY_DEF(PaddingProperty);
			TITANIUM_PROPERTY_READONLY_DEF(SelectedTextProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TextAlignmentProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TextProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TextTrimmingProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TextWrappingProperty);

			TITANIUM_FUNCTION_DEF(SelectAll);
			TITANIUM_FUNCTION_DEF(Select);
			TITANIUM_FUNCTION_DEF(Focus);

			TextBlock(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~TextBlock() = default;
			TextBlock(const TextBlock&) = default;
			TextBlock& operator=(const TextBlock&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TextBlock(TextBlock&&)                 = default;
			TextBlock& operator=(TextBlock&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::TextBlock^ unwrapWindows_UI_Xaml_Controls_TextBlock() const;
			void wrap(::Windows::UI::Xaml::Controls::TextBlock^ object);

		private:
			::Windows::UI::Xaml::Controls::TextBlock^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_TEXTBLOCK_HPP_
