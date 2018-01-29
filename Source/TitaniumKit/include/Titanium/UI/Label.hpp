/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LABEL_HPP_
#define _TITANIUM_UI_LABEL_HPP_

#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Font.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		class AttributedString;

		/*!
		  @class

		  @discussion This is the Titanium UI Label.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Label
		*/
		class TITANIUMKIT_EXPORT Label : public View, public JSExport<Label>
		{
		public:
			/*!
			  @method

			  @abstract color : String

			  @discussion Color of the label text, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, color);

			/*!
			  @method

			  @abstract ellipsize : Boolean

			  @discussion Turn on/off the addition of ellipses at the end of the label if the text is too large to fit.

			  Default: false
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, ellipsize);

			/*!
			  @method

			  @abstract font : Font

			  @discussion Font to use for the label text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Font, font);

			/*!
			@method

			@abstract textid : String

			@discussion Key identifying a string from the locale file to use for the label text.

			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, textid);

			/*!
			  @method

			  @abstract text : String

			  @discussion Label text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, text);

			/*!
			  @method

			  @abstract textAlign : String/Number

			  @discussion Text alignment.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TEXT_ALIGNMENT, textAlign);

			/*!
			  @method

			  @abstract verticalAlign : String/Number

			  @discussion Vertical text alignment, specified using one of the vertical alignment constants from Titanium.UI.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TEXT_VERTICAL_ALIGNMENT, verticalAlign);

			/*!
			  @method

			  @abstract wordWrap : Boolean

			  @discussion Enable or disable word wrapping in the label.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, wordWrap);

			/*!
			  @method

			  @abstract attributedString : AttributedString

			  @discussion Specify an attributed string for the label.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<AttributedString>, attributedString);

			/*!
			  @property
			  @abstract autoLink
			  @discussion Automatically convert text to clickable links. Multiple autolink values can be combined
			    with a bitwise OR. For example:
			    textArea.autoLink = AUTOLINK_MAP_ADDRESSES|AUTOLINK_PHONE_NUMBERS;
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::unordered_set<AUTOLINK>, autoLink);

			/*!
			  @property
			  @abstract minimumFontSize
			  @discussion Minimum font size when the font is sized based on the contents.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, minimumFontSize);

			/*!
			  @property
			  @abstract maxLines
			  @discussion Maximum lines of text shown in the Label.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, maxLines);

			Label(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Label() = default;
			Label(const Label&) = default;
			Label& operator=(const Label&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Label(Label&&) = default;
			Label& operator=(Label&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(color);
			TITANIUM_FUNCTION_DEF(getColor);
			TITANIUM_FUNCTION_DEF(setColor);

			TITANIUM_PROPERTY_DEF(ellipsize);
			TITANIUM_FUNCTION_DEF(getEllipsize);
			TITANIUM_FUNCTION_DEF(setEllipsize);

			TITANIUM_PROPERTY_DEF(font);
			TITANIUM_FUNCTION_DEF(getFont);
			TITANIUM_FUNCTION_DEF(setFont);

			TITANIUM_PROPERTY_DEF(textid);
			TITANIUM_FUNCTION_DEF(getTextid);
			TITANIUM_FUNCTION_DEF(setTextid);

			TITANIUM_PROPERTY_DEF(text);
			TITANIUM_FUNCTION_DEF(getText);
			TITANIUM_FUNCTION_DEF(setText);

			TITANIUM_PROPERTY_DEF(textAlign);
			TITANIUM_FUNCTION_DEF(getTextAlign);
			TITANIUM_FUNCTION_DEF(setTextAlign);

			TITANIUM_PROPERTY_DEF(verticalAlign);
			TITANIUM_FUNCTION_DEF(getVerticalAlign);
			TITANIUM_FUNCTION_DEF(setVerticalAlign);

			TITANIUM_PROPERTY_DEF(wordWrap);
			TITANIUM_FUNCTION_DEF(getWordWrap);
			TITANIUM_FUNCTION_DEF(setWordWrap);

			TITANIUM_PROPERTY_DEF(attributedString);
			TITANIUM_FUNCTION_DEF(getAttributedString);
			TITANIUM_FUNCTION_DEF(setAttributedString);

			TITANIUM_PROPERTY_DEF(autoLink);
			TITANIUM_FUNCTION_DEF(getAutoLink);
			TITANIUM_FUNCTION_DEF(setAutoLink);

			TITANIUM_PROPERTY_DEF(minimumFontSize);
			TITANIUM_FUNCTION_DEF(getMinimumFontSize);
			TITANIUM_FUNCTION_DEF(setMinimumFontSize);

			TITANIUM_PROPERTY_DEF(maxLines);
			TITANIUM_FUNCTION_DEF(getMaxLines);
			TITANIUM_FUNCTION_DEF(setMaxLines);

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string color__;
			bool ellipsize__;
			Font font__;
			std::string text__;
			std::string textid__;
			TEXT_ALIGNMENT textAlign__;
			TEXT_VERTICAL_ALIGNMENT verticalAlign__;
			bool wordWrap__;
			std::shared_ptr<AttributedString> attributedString__;
			std::unordered_set<AUTOLINK> autoLink__;
			double minimumFontSize__;
			std::uint32_t maxLines__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_LABEL_HPP_
