/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TextField.hpp"
#include <type_traits>

namespace Titanium
{
	namespace UI
	{
		TextField::TextField(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : UIBase(js_context),
		      autoCapitalization__(TEXT_AUTOCAPITALIZATION::NONE),
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

		TEXT_AUTOCAPITALIZATION TextField::get_autoCapitalization() const TITANIUM_NOEXCEPT
		{
			return autoCapitalization__;
		}

		void TextField::set_autoCapitalization(const TEXT_AUTOCAPITALIZATION& autoCapitalization) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_autoCapitalization: Unimplemented");
		}

		INPUT_BORDERSTYLE TextField::get_borderStyle() const TITANIUM_NOEXCEPT
		{
			return borderStyle__;
		}

		void TextField::set_borderStyle(const INPUT_BORDERSTYLE& borderStyle) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_borderStyle: Unimplemented");
		}

		INPUT_BUTTONMODE TextField::get_clearButtonMode() const TITANIUM_NOEXCEPT
		{
			return clearButtonMode__;
		}

		void TextField::set_clearButtonMode(const INPUT_BUTTONMODE& clearButtonMode) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_clearButtonMode: Unimplemented");
		}

		std::string TextField::get_color() const TITANIUM_NOEXCEPT
		{
			return color__;
		}

		void TextField::set_color(const std::string& color) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_color: Unimplemented");
		}

		bool TextField::get_editable() const TITANIUM_NOEXCEPT
		{
			return editable__;
		}

		void TextField::set_editable(const bool& editable) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_editable: Unimplemented");
		}

		bool TextField::get_ellipsize() const TITANIUM_NOEXCEPT
		{
			return ellipsize__;
		}

		void TextField::set_ellipsize(const bool& ellipsize) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_ellipsize: Unimplemented");
		}

		bool TextField::get_enableReturnKey() const TITANIUM_NOEXCEPT
		{
			return enableReturnKey__;
		}

		void TextField::set_enableReturnKey(const bool& enableReturnKey) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_enableReturnKey: Unimplemented");
		}

		std::string TextField::get_hintText() const TITANIUM_NOEXCEPT
		{
			return hintText__;
		}

		void TextField::set_hintText(const std::string& hintText) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_hintText: Unimplemented");
		}

		KEYBOARD TextField::get_keyboardType() const TITANIUM_NOEXCEPT
		{
			return keyboardType__;
		}

		void TextField::set_keyboardType(const KEYBOARD& keyboardType) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_keyboardType: Unimplemented");
		}

		INPUT_BUTTONMODE TextField::get_leftButtonMode() const TITANIUM_NOEXCEPT
		{
			return leftButtonMode__;
		}

		void TextField::set_leftButtonMode(const INPUT_BUTTONMODE& leftButtonMode) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_clearButtonMode: Unimplemented");
		}

		int32_t TextField::get_maxLength() const TITANIUM_NOEXCEPT
		{
			return maxLength__;
		}

		void TextField::set_maxLength(const int32_t& maxLength) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_maxLength: Unimplemented");
		}

		bool TextField::get_passwordMask() const TITANIUM_NOEXCEPT
		{
			return passwordMask__;
		}

		void TextField::set_passwordMask(const bool& passwordMask) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_passwordMask: Unimplemented");
		}

		RETURNKEY TextField::get_returnKeyType() const TITANIUM_NOEXCEPT
		{
			return returnKeyType__;
		}

		void TextField::set_returnKeyType(const RETURNKEY& keyboardType) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::get_returnKeyType: Unimplemented");
		}

		INPUT_BUTTONMODE TextField::get_rightButtonMode() const TITANIUM_NOEXCEPT
		{
			return rightButtonMode__;
		}

		void TextField::set_rightButtonMode(const INPUT_BUTTONMODE& rightButtonMode) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_clearButtonMode: Unimplemented");
		}

		bool TextField::get_suppressReturn() const TITANIUM_NOEXCEPT
		{
			return suppressReturn__;
		}

		void TextField::set_suppressReturn(const bool& suppressReturn) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_suppressReturn: Unimplemented");
		}

		TEXT_ALIGNMENT TextField::get_textAlign() const TITANIUM_NOEXCEPT
		{
			return textAlign__;
		}

		void TextField::set_textAlign(const TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_textAlign: Unimplemented");
		}

		std::string TextField::get_value() const TITANIUM_NOEXCEPT
		{
			return value__;
		}

		void TextField::set_value(const std::string& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_value: Unimplemented");
		}

		TEXT_VERTICAL_ALIGNMENT TextField::get_verticalAlign() const TITANIUM_NOEXCEPT
		{
			return verticalAlign__;
		}

		void TextField::set_verticalAlign(const TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextField::set_verticalAlign: Unimplemented");
		}

		void TextField::blur() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("TextField::blur");
		}

		void TextField::focus() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("TextField::focus");
		}

		bool TextField::hasText() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("TextField::hasText");
			return false;
		}

		void TextField::JSExportInitialize()
		{
			JSExport<TextField>::SetClassVersion(1);
			JSExport<TextField>::SetParent(JSExport<UIBase>::Class());
			JSExport<TextField>::AddValueProperty("autocapitalization", std::mem_fn(&TextField::js_get_autoCapitalization), std::mem_fn(&TextField::js_set_autoCapitalization));
			JSExport<TextField>::AddValueProperty("borderStyle", std::mem_fn(&TextField::js_get_borderStyle), std::mem_fn(&TextField::js_set_borderStyle));
			JSExport<TextField>::AddValueProperty("clearButtonMode", std::mem_fn(&TextField::js_get_clearButtonMode), std::mem_fn(&TextField::js_set_clearButtonMode));
			JSExport<TextField>::AddValueProperty("color", std::mem_fn(&TextField::js_get_color), std::mem_fn(&TextField::js_set_color));
			JSExport<TextField>::AddValueProperty("editable", std::mem_fn(&TextField::js_get_editable), std::mem_fn(&TextField::js_set_editable));
			JSExport<TextField>::AddValueProperty("ellipsize", std::mem_fn(&TextField::js_get_ellipsize), std::mem_fn(&TextField::js_set_ellipsize));
			JSExport<TextField>::AddValueProperty("enableReturnKey", std::mem_fn(&TextField::js_get_enableReturnKey), std::mem_fn(&TextField::js_set_enableReturnKey));
			JSExport<TextField>::AddValueProperty("hintText", std::mem_fn(&TextField::js_get_hintText), std::mem_fn(&TextField::js_set_hintText));
			JSExport<TextField>::AddValueProperty("keyboardType", std::mem_fn(&TextField::js_get_keyboardType), std::mem_fn(&TextField::js_set_keyboardType));
			JSExport<TextField>::AddValueProperty("leftButtonMode", std::mem_fn(&TextField::js_get_leftButtonMode), std::mem_fn(&TextField::js_set_leftButtonMode));
			JSExport<TextField>::AddValueProperty("maxLength", std::mem_fn(&TextField::js_get_maxLength), std::mem_fn(&TextField::js_set_maxLength));
			JSExport<TextField>::AddValueProperty("passwordMask", std::mem_fn(&TextField::js_get_passwordMask), std::mem_fn(&TextField::js_set_passwordMask));
			JSExport<TextField>::AddValueProperty("returnKeyType", std::mem_fn(&TextField::js_get_returnKeyType), std::mem_fn(&TextField::js_set_returnKeyType));
			JSExport<TextField>::AddValueProperty("rightButtonMode", std::mem_fn(&TextField::js_get_rightButtonMode), std::mem_fn(&TextField::js_set_rightButtonMode));
			JSExport<TextField>::AddValueProperty("suppressReturn", std::mem_fn(&TextField::js_get_suppressReturn), std::mem_fn(&TextField::js_set_suppressReturn));
			JSExport<TextField>::AddValueProperty("textAlign", std::mem_fn(&TextField::js_get_textAlign), std::mem_fn(&TextField::js_set_textAlign));
			JSExport<TextField>::AddValueProperty("value", std::mem_fn(&TextField::js_get_value), std::mem_fn(&TextField::js_set_value));
			JSExport<TextField>::AddValueProperty("verticalAlign", std::mem_fn(&TextField::js_get_verticalAlign), std::mem_fn(&TextField::js_set_verticalAlign));
			JSExport<TextField>::AddFunctionProperty("blur", std::mem_fn(&TextField::js_blur));
			JSExport<TextField>::AddFunctionProperty("focus", std::mem_fn(&TextField::js_focus));
			JSExport<TextField>::AddFunctionProperty("hasText", std::mem_fn(&TextField::js_hasText));
		}

		JSValue TextField::js_get_autoCapitalization() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(get_autoCapitalization()));
		}

		bool TextField::js_set_autoCapitalization(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			autoCapitalization__ = Constants::to_TEXT_AUTOCAPITALIZATION(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(argument));
			set_autoCapitalization(autoCapitalization__);
			return true;
		}

		JSValue TextField::js_get_borderStyle() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(get_borderStyle()));
		}

		bool TextField::js_set_borderStyle(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			borderStyle__ = Constants::to_INPUT_BORDERSTYLE(static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(argument));
			set_borderStyle(borderStyle__);
			return true;
		}

		JSValue TextField::js_get_clearButtonMode() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_clearButtonMode()));
		}

		bool TextField::js_set_clearButtonMode(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			clearButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(argument));
			set_clearButtonMode(clearButtonMode__);
			return true;
		}

		JSValue TextField::js_get_color() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_color());
		}

		bool TextField::js_set_color(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		JSValue TextField::js_get_editable() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_editable());
		}

		bool TextField::js_set_editable(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			editable__ = static_cast<bool>(argument);
			set_editable(editable__);
			return true;
		}

		JSValue TextField::js_get_ellipsize() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_ellipsize());
		}

		bool TextField::js_set_ellipsize(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			ellipsize__ = static_cast<bool>(argument);
			set_ellipsize(ellipsize__);
			return true;
		}

		JSValue TextField::js_get_enableReturnKey() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_enableReturnKey());
		}

		bool TextField::js_set_enableReturnKey(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			enableReturnKey__ = static_cast<bool>(argument);
			set_enableReturnKey(enableReturnKey__);
			return true;
		}

		JSValue TextField::js_get_hintText() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_hintText());
		}

		bool TextField::js_set_hintText(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_hintText(static_cast<std::string>(argument));
			return true;
		}

		JSValue TextField::js_get_keyboardType() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<KEYBOARD>::type>(get_keyboardType()));
		}

		bool TextField::js_set_keyboardType(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			keyboardType__ = Constants::to_KEYBOARD(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
			set_keyboardType(keyboardType__);
			return true;
		}

		JSValue TextField::js_get_leftButtonMode() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_leftButtonMode()));
		}

		bool TextField::js_set_leftButtonMode(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			leftButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(argument));
			set_leftButtonMode(leftButtonMode__);
			return true;
		}

		JSValue TextField::js_get_maxLength() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_maxLength());
		}

		bool TextField::js_set_maxLength(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_maxLength(static_cast<int32_t>(argument));
			return true;
		}

		JSValue TextField::js_get_passwordMask() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_passwordMask());
		}

		bool TextField::js_set_passwordMask(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_passwordMask(static_cast<bool>(argument));
			return true;
		}

		JSValue TextField::js_get_returnKeyType() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<RETURNKEY>::type>(get_returnKeyType()));
		}

		bool TextField::js_set_returnKeyType(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			returnKeyType__ = Constants::to_RETURNKEY(static_cast<std::underlying_type<RETURNKEY>::type>(argument));
			set_returnKeyType(returnKeyType__);
			return true;
		}

		JSValue TextField::js_get_rightButtonMode() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_rightButtonMode()));
		}

		bool TextField::js_set_rightButtonMode(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			rightButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
			set_rightButtonMode(rightButtonMode__);
			return true;
		}

		JSValue TextField::js_get_suppressReturn() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_suppressReturn());
		}

		bool TextField::js_set_suppressReturn(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_suppressReturn(static_cast<bool>(argument));
			return true;
		}

		JSValue TextField::js_get_textAlign() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		bool TextField::js_set_textAlign(const JSValue& argument) TITANIUM_NOEXCEPT
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

		JSValue TextField::js_get_value() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_value());
		}

		bool TextField::js_set_value(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_value(static_cast<std::string>(argument));
			return true;
		}

		JSValue TextField::js_get_verticalAlign() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		bool TextField::js_set_verticalAlign(const JSValue& argument) TITANIUM_NOEXCEPT
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

		JSValue TextField::js_blur(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			blur();
			return get_context().CreateUndefined();
		}

		JSValue TextField::js_focus(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			focus();
			return get_context().CreateUndefined();
		}

		JSValue TextField::js_hasText(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			return get_context().CreateBoolean(hasText());
		}
	} // namespace UI
}  // namespace Titanium
