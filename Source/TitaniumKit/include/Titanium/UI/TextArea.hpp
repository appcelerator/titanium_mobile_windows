/**
 * TitaniumKit Titanium.UI.TextArea
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_TEXTAREA_HPP_
#define _TITANIUM_TEXTAREA_HPP_

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
		  @struct
		  @discussion Dictionary object of parameters for the Titanium.UI.TextArea.
		  selected event and Titanium.UI.TextArea.selection property that describes position and length of the selected text.
		  See http://docs.appcelerator.com/platform/latest/#!/api/textAreaSelectedParams
		*/
		struct TextAreaSelectedParams
		{
			std::uint32_t length  { 0 };
			std::uint32_t location{ 0 };
		};

		TITANIUMKIT_EXPORT TextAreaSelectedParams js_to_TextAreaSelectedParams(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject TextAreaSelectedParams_to_js(const JSContext& js_context, const TextAreaSelectedParams& params);

		/*!
		  @struct
		  @discussion Dictionary object of parameters for the Titanium.UI.TextArea.padding that describes the padding
		  See https://docs.appcelerator.com/platform/latest/#!/api/TextAreaPadding
		*/
		struct TextAreaPadding
		{
			double bottom{ 0 };
			double left{ 0 };
			double right{ 0 };
			double top{ 0 };
		};

		TITANIUMKIT_EXPORT TextAreaPadding js_to_TextAreaPadding(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject TextAreaPadding_to_js(const JSContext& js_context, const TextAreaPadding& params);

		/*!
		  @class
		  @discussion This is the Titanium TextArea Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.TextArea
		*/
		class TITANIUMKIT_EXPORT TextArea : public View, public JSExport<TextArea>
		{

		public:

			/*!
			  @property
			  @abstract appearance
			  @discussion Determines the appearance of the keyboard displayed when this text area is focused.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(KEYBOARD_APPEARANCE, appearance);

			/*!
			  @property
			  @abstract attributedString
			  @discussion TextArea attributed string.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<AttributedString>, attributedString);

			/*!
			  @property
			  @abstract autocapitalization
			  @discussion Determines how text is capitalized during typing.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TEXT_AUTOCAPITALIZATION, autocapitalization);

			/*!
			  @property
			  @abstract autocorrect
			  @discussion Determines whether to automatically correct text entered into this text area.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, autocorrect);

			/*!
			  @property
			  @abstract autoLink
			  @discussion Automatically convert text to clickable links. Multiple autolink values can be combined with a bitwise
			  OR. For example:
			  textArea.autoLink = AUTOLINK_MAP_ADDRESSES|AUTOLINK_PHONE_NUMBERS;
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::unordered_set<AUTOLINK>, autoLink);

			/*!
			  @property
			  @abstract clearOnEdit
			  @discussion Determines whether the value of this text area should be cleared when it is focused.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, clearOnEdit);

			/*!
			  @property
			  @abstract color
			  @discussion Color of the text in this text area, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, color);

			/*!
			  @property
			  @abstract editable
			  @discussion Determines whether this field can be edited.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, editable);

			/*!
			  @property
			  @abstract ellipsize
			  @discussion Determines whether an ellipsis (`...`) should be used to indicate truncated text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, ellipsize);

			/*!
			  @property
			  @abstract enableReturnKey
			  @discussion Determines whether the return key is enabled automatically when there is text in this text area.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, enableReturnKey);

			/*!
			  @property
			  @abstract font
			  @discussion Font to use for text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Font, font);

			/*!
			  @property
			  @abstract hintText
			  @discussion Hint text to display when the field is empty.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, hintText);

			/*!
			  @property
			  @abstract handleLinks
			  @discussion Specifies if the text area should allow user interaction with the given URL in the given range of text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, handleLinks);

			/*!
			  @property
			  @abstract keyboardToolbar
			  @discussion Array of toolbar button objects or a [toolbar](Titanium.UI.iOS.Toolbar) to be used when the keyboard is displayed.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(JSValue, keyboardToolbar);

			/*!
			  @property
			  @abstract keyboardToolbarColor
			  @discussion Color of the keyboard toolbar if keyboardToolbar is an array, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, keyboardToolbarColor);

			/*!
			  @property
			  @abstract keyboardToolbarHeight
			  @discussion Height of the keyboard toolbar if keyboardToolbar is an array.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, keyboardToolbarHeight);

			/*!
			  @property
			  @abstract  keyboardType : Number
			  @discussion Keyboard type to display when this text field is
			  focused. When asking for a specific kind of user input, such as a
			  phone number or email address, you should always specify the
			  appropriate keyboard type.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(KEYBOARD, keyboardType);

			/*!
			  @property
			  @abstract maxLength
			  @discussion Maximum length of text field input.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(int32_t, maxLength);

			/*!
			  @property
			  @abstract returnKeyType
			  @discussion Specifies the text to display on the keyboard `Return` key when this text area is focused.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(RETURNKEY, returnKeyType);

			/*!
			  @property
			  @abstract scrollsToTop
			  @discussion Controls whether the scroll-to-top gesture is effective.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, scrollsToTop);

			/*!
			  @property
			  @abstract suppressReturn
			  @discussion Determines if the return key should be suppressed during text entry.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, suppressReturn);

			/*!
			  @property
			  @abstract scrollable
			  @discussion Determines whether this text area can be scrolled.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, scrollable);

			/*!
			  @property
			  @abstract selection
			  @discussion Returns the currently selected text of the text area.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(TextAreaSelectedParams, selection);

			/*!
			  @property
			  @abstract textAlign
			  @discussion Text alignment within this text area.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TEXT_ALIGNMENT, textAlign);

			/*!
			  @property
			  @abstract value
			  @discussion Value of this text area, which may be set programmatically and modified by the user.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, value);

			/*!
			  @property
			  @abstract verticalAlign
			  @discussion Vertical alignment within this text area.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TEXT_VERTICAL_ALIGNMENT, verticalAlign);

			/*!
			  @property
			  @abstract padding
			  @discussion Sets the left and right padding of this TextArea.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TextAreaPadding, padding);

			/*!
			  @method
			  @abstract blur
			  @discussion Forces this text area to lose focus.
			*/
			virtual void blur() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract focus
			  @discussion Forces this text area to gain focus.
			*/
			virtual void focus() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract hasText
			  @discussion Returns `true` if this text area contains text.
			*/
			virtual bool hasText() TITANIUM_NOEXCEPT;

			TextArea(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~TextArea()                  = default;
			TextArea(const TextArea&)            = default;
			TextArea& operator=(const TextArea&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TextArea(TextArea&&)                 = default;
			TextArea& operator=(TextArea&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(appearance);
			TITANIUM_PROPERTY_DEF(attributedString);
			TITANIUM_PROPERTY_DEF(autocapitalization);
			TITANIUM_PROPERTY_DEF(autocorrect);
			TITANIUM_PROPERTY_DEF(autoLink);
			TITANIUM_PROPERTY_DEF(clearOnEdit);
			TITANIUM_PROPERTY_DEF(color);
			TITANIUM_PROPERTY_DEF(editable);
			TITANIUM_PROPERTY_DEF(ellipsize);
			TITANIUM_PROPERTY_DEF(enableReturnKey);
			TITANIUM_PROPERTY_DEF(font);
			TITANIUM_PROPERTY_DEF(hintText);
			TITANIUM_PROPERTY_DEF(handleLinks);
			TITANIUM_PROPERTY_DEF(keyboardToolbar);
			TITANIUM_PROPERTY_DEF(keyboardToolbarColor);
			TITANIUM_PROPERTY_DEF(keyboardToolbarHeight);
			TITANIUM_PROPERTY_DEF(keyboardType);
			TITANIUM_PROPERTY_DEF(maxLength);
			TITANIUM_PROPERTY_DEF(returnKeyType);
			TITANIUM_PROPERTY_DEF(scrollsToTop);
			TITANIUM_PROPERTY_DEF(suppressReturn);
			TITANIUM_PROPERTY_DEF(scrollable);
			TITANIUM_PROPERTY_READONLY_DEF(selection);
			TITANIUM_PROPERTY_DEF(textAlign);
			TITANIUM_PROPERTY_DEF(value);
			TITANIUM_PROPERTY_DEF(verticalAlign);
			TITANIUM_PROPERTY_DEF(padding);

			TITANIUM_FUNCTION_DEF(blur);
			TITANIUM_FUNCTION_DEF(focus);
			TITANIUM_FUNCTION_DEF(hasText);
			
			TITANIUM_FUNCTION_DEF(getAppearance);
			TITANIUM_FUNCTION_DEF(setAppearance);
			TITANIUM_FUNCTION_DEF(getAttributedString);
			TITANIUM_FUNCTION_DEF(setAttributedString);
			TITANIUM_FUNCTION_DEF(getAutocapitalization);
			TITANIUM_FUNCTION_DEF(setAutocapitalization);
			TITANIUM_FUNCTION_DEF(getAutocorrect);
			TITANIUM_FUNCTION_DEF(setAutocorrect);
			TITANIUM_FUNCTION_DEF(getAutoLink);
			TITANIUM_FUNCTION_DEF(setAutoLink);
			TITANIUM_FUNCTION_DEF(getClearOnEdit);
			TITANIUM_FUNCTION_DEF(setClearOnEdit);
			TITANIUM_FUNCTION_DEF(getColor);
			TITANIUM_FUNCTION_DEF(setColor);
			TITANIUM_FUNCTION_DEF(getEditable);
			TITANIUM_FUNCTION_DEF(setEditable);
			TITANIUM_FUNCTION_DEF(getEllipsize);
			TITANIUM_FUNCTION_DEF(setEllipsize);
			TITANIUM_FUNCTION_DEF(getEnableReturnKey);
			TITANIUM_FUNCTION_DEF(setEnableReturnKey);
			TITANIUM_FUNCTION_DEF(getFont);
			TITANIUM_FUNCTION_DEF(setFont);
			TITANIUM_FUNCTION_DEF(getHintText);
			TITANIUM_FUNCTION_DEF(setHintText);
			TITANIUM_FUNCTION_DEF(getHandleLinks);
			TITANIUM_FUNCTION_DEF(setHandleLinks);
			TITANIUM_FUNCTION_DEF(getKeyboardToolbar);
			TITANIUM_FUNCTION_DEF(setKeyboardToolbar);
			TITANIUM_FUNCTION_DEF(getKeyboardToolbarColor);
			TITANIUM_FUNCTION_DEF(setKeyboardToolbarColor);
			TITANIUM_FUNCTION_DEF(getKeyboardToolbarHeight);
			TITANIUM_FUNCTION_DEF(setKeyboardToolbarHeight);
			TITANIUM_FUNCTION_DEF(getKeyboardType);
			TITANIUM_FUNCTION_DEF(setKeyboardType);
			TITANIUM_FUNCTION_DEF(getMaxLength);
			TITANIUM_FUNCTION_DEF(setMaxLength);
			TITANIUM_FUNCTION_DEF(getReturnKeyType);
			TITANIUM_FUNCTION_DEF(setReturnKeyType);
			TITANIUM_FUNCTION_DEF(getScrollsToTop);
			TITANIUM_FUNCTION_DEF(setScrollsToTop);
			TITANIUM_FUNCTION_DEF(getSuppressReturn);
			TITANIUM_FUNCTION_DEF(setSuppressReturn);
			TITANIUM_FUNCTION_DEF(getScrollable);
			TITANIUM_FUNCTION_DEF(setScrollable);
			TITANIUM_FUNCTION_DEF(getSelection);
			TITANIUM_FUNCTION_DEF(getTextAlign);
			TITANIUM_FUNCTION_DEF(setTextAlign);
			TITANIUM_FUNCTION_DEF(getValue);
			TITANIUM_FUNCTION_DEF(setValue);
			TITANIUM_FUNCTION_DEF(getVerticalAlign);
			TITANIUM_FUNCTION_DEF(setVerticalAlign);
			TITANIUM_FUNCTION_DEF(getPadding);
			TITANIUM_FUNCTION_DEF(setPadding);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			KEYBOARD_APPEARANCE appearance__;
			std::shared_ptr<AttributedString> attributedString__;
			TEXT_AUTOCAPITALIZATION autocapitalization__;
			bool autocorrect__;
			std::unordered_set<AUTOLINK> autoLink__;
			bool clearOnEdit__;
			std::string color__;
			bool editable__;
			bool ellipsize__;
			bool enableReturnKey__;
			Font font__;
			std::string hintText__;
			bool handleLinks__;
			JSValue keyboardToolbar__;
			std::string keyboardToolbarColor__;
			double keyboardToolbarHeight__;
			KEYBOARD keyboardType__;
			int32_t maxLength__;
			RETURNKEY returnKeyType__;
			bool scrollsToTop__;
			bool suppressReturn__;
			bool scrollable__;
			TEXT_ALIGNMENT textAlign__;
			std::string value__;
			TEXT_VERTICAL_ALIGNMENT verticalAlign__;
			TextAreaPadding padding__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_TEXTAREA_HPP_