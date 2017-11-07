/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TextField.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/AttributedString.hpp"
#include "Titanium/Locale.hpp"
#include <type_traits>

namespace Titanium
{
	namespace UI
	{
		TextField::TextField(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context, "Ti.UI.TextField"),
		      autocapitalization__(TEXT_AUTOCAPITALIZATION::NONE),
		      borderStyle__(INPUT_BORDERSTYLE::NONE),
		      clearButtonMode__(INPUT_BUTTONMODE::NEVER),
			  color__(js_context.CreateString()),
			  editable__(js_context.CreateBoolean(true)),
			  ellipsize__(js_context.CreateBoolean(false)),
			  hintText__(js_context.CreateString()),
		      leftButtonMode__(INPUT_BUTTONMODE::NEVER),
			  maxLength__(js_context.CreateNumber(-1)),
			  passwordMask__(js_context.CreateBoolean(false)),
		      returnKeyType__(RETURNKEY::DEFAULT),
		      rightButtonMode__(INPUT_BUTTONMODE::NEVER),
			  suppressReturn__(js_context.CreateBoolean(false)),
		      textAlign__(TEXT_ALIGNMENT::LEFT),
			  value__(js_context.CreateString()),
		      verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER)
		{
		}

		TITANIUM_PROPERTY_READWRITE(TextField, TEXT_AUTOCAPITALIZATION, autocapitalization)
		TITANIUM_PROPERTY_READWRITE(TextField, INPUT_BORDERSTYLE, borderStyle)
		TITANIUM_PROPERTY_READWRITE(TextField, INPUT_BUTTONMODE, clearButtonMode)
		TITANIUM_PROPERTY_READWRITE(TextField, std::string, color)
		TITANIUM_PROPERTY_READWRITE(TextField, bool, editable)
		TITANIUM_PROPERTY_READWRITE(TextField, bool, ellipsize)
		TITANIUM_PROPERTY_READWRITE(TextField, bool, enableReturnKey)
		TITANIUM_PROPERTY_READWRITE(TextField, Font, font)
		TITANIUM_PROPERTY_READWRITE(TextField, std::string, hintText)
		TITANIUM_PROPERTY_READWRITE(TextField, KEYBOARD, keyboardType)
		TITANIUM_PROPERTY_READWRITE(TextField, INPUT_BUTTONMODE, leftButtonMode)
		TITANIUM_PROPERTY_READWRITE(TextField, int32_t, maxLength)
		TITANIUM_PROPERTY_READWRITE(TextField, bool, passwordMask)
		TITANIUM_PROPERTY_READWRITE(TextField, RETURNKEY, returnKeyType)
		TITANIUM_PROPERTY_READWRITE(TextField, INPUT_BUTTONMODE, rightButtonMode)
		TITANIUM_PROPERTY_READWRITE(TextField, bool, suppressReturn)
		TITANIUM_PROPERTY_READWRITE(TextField, TEXT_ALIGNMENT, textAlign)
		TITANIUM_PROPERTY_READWRITE(TextField, std::string, value)
		TITANIUM_PROPERTY_READWRITE(TextField, TEXT_VERTICAL_ALIGNMENT, verticalAlign)
		TITANIUM_PROPERTY_READWRITE(TextField, std::shared_ptr<AttributedString>, attributedHintString)
		TITANIUM_PROPERTY_READWRITE(TextField, std::shared_ptr<AttributedString>, attributedString)

		TITANIUM_PROPERTY_READ(TextField, std::string, hinttextid)
		void TextField::set_hinttextid(const std::string& hinttextid) TITANIUM_NOEXCEPT
		{
			hinttextid__ = hinttextid;
			const auto value = Titanium::Locale::GetString(get_context(), hinttextid);
			if (value) {
				set_hintText(*value);
			}
		}

		bool TextField::hasText() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("TextField::hasText");
			return false;
		}

		void TextField::JSExportInitialize()
		{
			JSExport<TextField>::SetClassVersion(1);
			JSExport<TextField>::SetParent(JSExport<View>::Class());
			// properties
			TITANIUM_ADD_PROPERTY(TextField, attributedHintString);
			TITANIUM_ADD_PROPERTY(TextField, attributedString);
			TITANIUM_ADD_PROPERTY(TextField, autocapitalization);
			TITANIUM_ADD_PROPERTY(TextField, borderStyle);
			TITANIUM_ADD_PROPERTY(TextField, clearButtonMode);
			TITANIUM_ADD_PROPERTY(TextField, color);
			TITANIUM_ADD_PROPERTY(TextField, editable);
			TITANIUM_ADD_PROPERTY(TextField, ellipsize);
			TITANIUM_ADD_PROPERTY(TextField, enableReturnKey);
			TITANIUM_ADD_PROPERTY(TextField, font);
			TITANIUM_ADD_PROPERTY(TextField, hinttextid);
			TITANIUM_ADD_PROPERTY(TextField, hintText);
			TITANIUM_ADD_PROPERTY(TextField, keyboardType);
			TITANIUM_ADD_PROPERTY(TextField, leftButtonMode);
			TITANIUM_ADD_PROPERTY(TextField, maxLength);
			TITANIUM_ADD_PROPERTY(TextField, passwordMask);
			TITANIUM_ADD_PROPERTY(TextField, returnKeyType);
			TITANIUM_ADD_PROPERTY(TextField, rightButtonMode);
			TITANIUM_ADD_PROPERTY(TextField, suppressReturn);
			TITANIUM_ADD_PROPERTY(TextField, textAlign);
			TITANIUM_ADD_PROPERTY(TextField, value);
			TITANIUM_ADD_PROPERTY(TextField, verticalAlign);
			// methods
			TITANIUM_ADD_FUNCTION(TextField, blur);
			TITANIUM_ADD_FUNCTION(TextField, focus);
			TITANIUM_ADD_FUNCTION(TextField, hasText);
			// property accessor methods
			TITANIUM_ADD_FUNCTION(TextField, getAttributedHintString);
			TITANIUM_ADD_FUNCTION(TextField, setAttributedHintString);
			TITANIUM_ADD_FUNCTION(TextField, getAttributedString);
			TITANIUM_ADD_FUNCTION(TextField, setAttributedString);
			TITANIUM_ADD_FUNCTION(TextField, getAutocapitalization);
			TITANIUM_ADD_FUNCTION(TextField, setAutocapitalization);
			TITANIUM_ADD_FUNCTION(TextField, getBorderStyle);
			TITANIUM_ADD_FUNCTION(TextField, setBorderStyle);
			TITANIUM_ADD_FUNCTION(TextField, getClearButtonMode);
			TITANIUM_ADD_FUNCTION(TextField, setClearButtonMode);
			TITANIUM_ADD_FUNCTION(TextField, getColor);
			TITANIUM_ADD_FUNCTION(TextField, setColor);
			TITANIUM_ADD_FUNCTION(TextField, getEditable);
			TITANIUM_ADD_FUNCTION(TextField, setEditable);
			TITANIUM_ADD_FUNCTION(TextField, getEllipsize);
			TITANIUM_ADD_FUNCTION(TextField, setEllipsize);
			TITANIUM_ADD_FUNCTION(TextField, getEnableReturnKey);
			TITANIUM_ADD_FUNCTION(TextField, setEnableReturnKey);
			TITANIUM_ADD_FUNCTION(TextField, getFont);
			TITANIUM_ADD_FUNCTION(TextField, setFont);
			TITANIUM_ADD_FUNCTION(TextField, getHinttextid);
			TITANIUM_ADD_FUNCTION(TextField, setHinttextid);
			TITANIUM_ADD_FUNCTION(TextField, getHintText);
			TITANIUM_ADD_FUNCTION(TextField, setHintText);
			TITANIUM_ADD_FUNCTION(TextField, getKeyboardType);
			TITANIUM_ADD_FUNCTION(TextField, setKeyboardType);
			TITANIUM_ADD_FUNCTION(TextField, getLeftButtonMode);
			TITANIUM_ADD_FUNCTION(TextField, setLeftButtonMode);
			TITANIUM_ADD_FUNCTION(TextField, getMaxLength);
			TITANIUM_ADD_FUNCTION(TextField, setMaxLength);
			TITANIUM_ADD_FUNCTION(TextField, getPasswordMask);
			TITANIUM_ADD_FUNCTION(TextField, setPasswordMask);
			TITANIUM_ADD_FUNCTION(TextField, getReturnKeyType);
			TITANIUM_ADD_FUNCTION(TextField, setReturnKeyType);
			TITANIUM_ADD_FUNCTION(TextField, getRightButtonMode);
			TITANIUM_ADD_FUNCTION(TextField, setRightButtonMode);
			TITANIUM_ADD_FUNCTION(TextField, getSuppressReturn);
			TITANIUM_ADD_FUNCTION(TextField, setSuppressReturn);
			TITANIUM_ADD_FUNCTION(TextField, getTextAlign);
			TITANIUM_ADD_FUNCTION(TextField, setTextAlign);
			TITANIUM_ADD_FUNCTION(TextField, getValue);
			TITANIUM_ADD_FUNCTION(TextField, setValue);
			TITANIUM_ADD_FUNCTION(TextField, getVerticalAlign);
			TITANIUM_ADD_FUNCTION(TextField, setVerticalAlign);
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getAttributedHintString, attributedHintString)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setAttributedHintString, attributedHintString)
		TITANIUM_FUNCTION_AS_GETTER(TextField, getAttributedString, attributedString)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setAttributedString, attributedString)

		TITANIUM_PROPERTY_GETTER_OBJECT(TextField, attributedHintString)
		TITANIUM_PROPERTY_SETTER_OBJECT(TextField, attributedHintString, AttributedString)
		TITANIUM_PROPERTY_GETTER_OBJECT(TextField, attributedString)
		TITANIUM_PROPERTY_SETTER_OBJECT(TextField, attributedString, AttributedString)

		TITANIUM_PROPERTY_GETTER(TextField, autocapitalization)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(get_autocapitalization()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, autocapitalization)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			autocapitalization__ = Constants::to_TEXT_AUTOCAPITALIZATION(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(argument));
			set_autocapitalization(autocapitalization__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getAutocapitalization, autocapitalization)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setAutocapitalization, autocapitalization)

		TITANIUM_PROPERTY_GETTER(TextField, borderStyle)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(get_borderStyle()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, borderStyle)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			borderStyle__ = Constants::to_INPUT_BORDERSTYLE(static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(argument));
			set_borderStyle(borderStyle__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getBorderStyle, borderStyle)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setBorderStyle, borderStyle)

		TITANIUM_PROPERTY_GETTER(TextField, clearButtonMode)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_clearButtonMode()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, clearButtonMode)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			clearButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(argument));
			set_clearButtonMode(clearButtonMode__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getClearButtonMode, clearButtonMode)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setClearButtonMode, clearButtonMode)

		TITANIUM_PROPERTY_GETTER_STRING(TextField, color)
		TITANIUM_PROPERTY_SETTER_STRING(TextField, color)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setColor, color)

		TITANIUM_PROPERTY_GETTER_BOOL(TextField, editable)
		TITANIUM_PROPERTY_SETTER_BOOL(TextField, editable)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getEditable, editable)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setEditable, editable)

		TITANIUM_PROPERTY_GETTER(TextField, ellipsize)
		{
			return get_context().CreateBoolean(get_ellipsize());
		}

		TITANIUM_PROPERTY_SETTER(TextField, ellipsize)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			ellipsize__ = static_cast<bool>(argument);
			set_ellipsize(ellipsize__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getEllipsize, ellipsize)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setEllipsize, ellipsize)

		TITANIUM_PROPERTY_GETTER_BOOL(TextField, enableReturnKey)
		TITANIUM_PROPERTY_SETTER_BOOL(TextField, enableReturnKey)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getEnableReturnKey, enableReturnKey)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setEnableReturnKey, enableReturnKey)

		TITANIUM_PROPERTY_GETTER_STRUCT(TextField, font, Font)
		TITANIUM_PROPERTY_SETTER_STRUCT(TextField, font, Font)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setFont, font)

		TITANIUM_PROPERTY_GETTER_STRING(TextField, hinttextid)
		TITANIUM_PROPERTY_SETTER_STRING(TextField, hinttextid)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getHinttextid, hinttextid)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setHinttextid, hinttextid)

		TITANIUM_PROPERTY_GETTER_STRING(TextField, hintText)
		TITANIUM_PROPERTY_SETTER_STRING(TextField, hintText)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getHintText, hintText)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setHintText, hintText)

		TITANIUM_PROPERTY_GETTER(TextField, keyboardType)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<KEYBOARD>::type>(get_keyboardType()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, keyboardType)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			keyboardType__ = Constants::to_KEYBOARD(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
			set_keyboardType(keyboardType__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getKeyboardType, keyboardType)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setKeyboardType, keyboardType)

		TITANIUM_PROPERTY_GETTER(TextField, leftButtonMode)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_leftButtonMode()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, leftButtonMode)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			leftButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(argument));
			set_leftButtonMode(leftButtonMode__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getLeftButtonMode, leftButtonMode)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setLeftButtonMode, leftButtonMode)

		TITANIUM_PROPERTY_GETTER_INT(TextField, maxLength)
		TITANIUM_PROPERTY_SETTER_INT(TextField, maxLength)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getMaxLength, maxLength)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setMaxLength, maxLength)

		TITANIUM_PROPERTY_GETTER_BOOL(TextField, passwordMask)
		TITANIUM_PROPERTY_SETTER_BOOL(TextField, passwordMask)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getPasswordMask, passwordMask)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setPasswordMask, passwordMask)

		TITANIUM_PROPERTY_GETTER(TextField, returnKeyType)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<RETURNKEY>::type>(get_returnKeyType()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, returnKeyType)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			returnKeyType__ = Constants::to_RETURNKEY(static_cast<std::underlying_type<RETURNKEY>::type>(argument));
			set_returnKeyType(returnKeyType__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getReturnKeyType, returnKeyType)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setReturnKeyType, returnKeyType)

		TITANIUM_PROPERTY_GETTER(TextField, rightButtonMode)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_rightButtonMode()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, rightButtonMode)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			rightButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
			set_rightButtonMode(rightButtonMode__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getRightButtonMode, rightButtonMode)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setRightButtonMode, rightButtonMode)

		TITANIUM_PROPERTY_GETTER_BOOL(TextField, suppressReturn)
		TITANIUM_PROPERTY_SETTER_BOOL(TextField, suppressReturn)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getSuppressReturn, suppressReturn)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setSuppressReturn, suppressReturn)

		TITANIUM_PROPERTY_GETTER(TextField, textAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, textAlign)
		{
			bool result = false;
			if (argument.IsNumber()) {
				textAlign__ = Constants::to_TEXT_ALIGNMENT(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(argument));
				set_textAlign(textAlign__);
				result = true;
			} else if (argument.IsString()) {
				textAlign__ = Constants::to_TEXT_ALIGNMENT(static_cast<std::string>(argument));
				set_textAlign(textAlign__);
				result = true;
			}

			return result;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getTextAlign, textAlign)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setTextAlign, textAlign)

		TITANIUM_PROPERTY_GETTER_STRING(TextField, value)
		TITANIUM_PROPERTY_SETTER_STRING(TextField, value)

		TITANIUM_FUNCTION_AS_GETTER(TextField, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setValue, value)

		TITANIUM_PROPERTY_GETTER(TextField, verticalAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		TITANIUM_PROPERTY_SETTER(TextField, verticalAlign)
		{
			bool result = false;
			if (argument.IsNumber()) {
				verticalAlign__ = Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(argument));
				set_verticalAlign(verticalAlign__);
				result = true;
			} else if (argument.IsString()) {
				verticalAlign__ = Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::string>(argument));
				set_verticalAlign(verticalAlign__);
				result = true;
			}

			return result;
		}

		TITANIUM_FUNCTION_AS_GETTER(TextField, getVerticalAlign, verticalAlign)
		TITANIUM_FUNCTION_AS_SETTER(TextField, setVerticalAlign, verticalAlign)

		TITANIUM_FUNCTION(TextField, blur)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			blur();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TextField, focus)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			focus();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TextField, hasText)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			return get_context().CreateBoolean(hasText());
		}
	} // namespace UI
}  // namespace Titanium
