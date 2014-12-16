/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TextField.hpp"
#include <type_traits>

namespace Titanium { namespace UI {
  
  TextField::TextField(const JSContext& js_context) TITANIUM_NOEXCEPT
  : View(js_context)
  , borderStyle__(INPUT_BORDERSTYLE::NONE)
  , clearButtonMode__(INPUT_BUTTONMODE::NEVER)
  , leftButtonMode__(INPUT_BUTTONMODE::NEVER)
  , rightButtonMode__(INPUT_BUTTONMODE::NEVER)
  , returnKeyType__(RETURNKEY::DEFAULT)
  , textAlign__(TEXT_ALIGNMENT::LEFT)
  , autoCapitalization__(TEXT_AUTOCAPITALIZATION::NONE)
  , verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER) {
  }
  
  TextField::TextField(const TextField& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : View(rhs, arguments)
  , borderStyle__(rhs.borderStyle__)
  , clearButtonMode__(rhs.clearButtonMode__)
  , leftButtonMode__(rhs.leftButtonMode__)
  , rightButtonMode__(rhs.rightButtonMode__)
  , returnKeyType__(rhs.returnKeyType__)
  , textAlign__(rhs.textAlign__)
  , autoCapitalization__(rhs.autoCapitalization__)
  , verticalAlign__(rhs.verticalAlign__) {
  }
  
  INPUT_BORDERSTYLE TextField::get_borderStyle() const  TITANIUM_NOEXCEPT {
    return borderStyle__;
  }
  
  void TextField::set_borderStyle(const INPUT_BORDERSTYLE& borderStyle) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_borderStyle: Unimplemented");
  }
  
  INPUT_BUTTONMODE TextField::get_clearButtonMode() const  TITANIUM_NOEXCEPT {
    return clearButtonMode__;
  }
  
  void TextField::set_clearButtonMode(const INPUT_BUTTONMODE& clearButtonMode) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_clearButtonMode: Unimplemented");
  }
  
  INPUT_BUTTONMODE TextField::get_leftButtonMode() const  TITANIUM_NOEXCEPT {
    return leftButtonMode__;
  }
  
  void TextField::set_leftButtonMode(const INPUT_BUTTONMODE& leftButtonMode) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_clearButtonMode: Unimplemented");
  }
  
  INPUT_BUTTONMODE TextField::get_rightButtonMode() const  TITANIUM_NOEXCEPT {
    return rightButtonMode__;
  }
  
  void TextField::set_rightButtonMode(const INPUT_BUTTONMODE& rightButtonMode) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_clearButtonMode: Unimplemented");
  }
  
  KEYBOARD TextField::get_keyboardType() const  TITANIUM_NOEXCEPT {
    return keyboardType__;
  }
  
  void TextField::set_keyboardType(const KEYBOARD& keyboardType) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_keyboardType: Unimplemented");
  }
  
  RETURNKEY TextField::get_returnKeyType() const  TITANIUM_NOEXCEPT {
    return returnKeyType__;
  }
  
  void TextField::set_returnKeyType(const RETURNKEY& keyboardType) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::get_returnKeyType: Unimplemented");
  }
  
  TEXT_ALIGNMENT TextField::get_textAlign() const  TITANIUM_NOEXCEPT {
    return textAlign__;
  }
  
  void TextField::set_textAlign(const TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_textAlign: Unimplemented");
  }

  TEXT_AUTOCAPITALIZATION TextField::get_autoCapitalization() const  TITANIUM_NOEXCEPT {
    return autoCapitalization__;
  }
  
  void TextField::set_autoCapitalization(const TEXT_AUTOCAPITALIZATION& autoCapitalization) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_autoCapitalization: Unimplemented");
  }

  TEXT_VERTICAL_ALIGNMENT TextField::get_verticalAlign() const  TITANIUM_NOEXCEPT {
    return verticalAlign__;
  }
  
  void TextField::set_verticalAlign(const TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("TextField::set_verticalAlign: Unimplemented");
  }

  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void TextField::JSExportInitialize() {
    JSExport<TextField>::SetClassVersion(1);
    JSExport<TextField>::SetParent(JSExport<View>::Class());
    JSExport<TextField>::AddValueProperty("curve", std::mem_fn(&TextField::getBorderStyleArgumentValidator), std::mem_fn(&TextField::setBorderStyleArgumentValidator));
    JSExport<TextField>::AddValueProperty("clearButtonMode", std::mem_fn(&TextField::getClearButtonModeArgumentValidator), std::mem_fn(&TextField::setClearButtonModeArgumentValidator));
    JSExport<TextField>::AddValueProperty("leftButtonMode", std::mem_fn(&TextField::getLeftButtonModeArgumentValidator), std::mem_fn(&TextField::setLeftButtonModeArgumentValidator));
    JSExport<TextField>::AddValueProperty("rightButtonMode", std::mem_fn(&TextField::getRightButtonModeArgumentValidator), std::mem_fn(&TextField::setRightButtonModeArgumentValidator));
    JSExport<TextField>::AddValueProperty("keyboardType", std::mem_fn(&TextField::getKeyboardTypeArgumentValidator), std::mem_fn(&TextField::setKeyboardTypeArgumentValidator));
    JSExport<TextField>::AddValueProperty("returnKeyType", std::mem_fn(&TextField::getReturnKeyTypeArgumentValidator), std::mem_fn(&TextField::setReturnKeyTypeArgumentValidator));
    JSExport<TextField>::AddValueProperty("textAlign", std::mem_fn(&TextField::getTextAlignArgumentValidator), std::mem_fn(&TextField::setTextAlignArgumentValidator));
    JSExport<TextField>::AddValueProperty("autocapitalization", std::mem_fn(&TextField::getAutoCapitalizationArgumentValidator), std::mem_fn(&TextField::setAutoCapitalizationArgumentValidator));
    JSExport<TextField>::AddValueProperty("verticalAlign", std::mem_fn(&TextField::getVerticalAlignArgumentValidator), std::mem_fn(&TextField::setVerticalAlignArgumentValidator));
  }
  
  JSValue TextField::getBorderStyleArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(get_borderStyle()));
  }
  
  bool TextField::setBorderStyleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    borderStyle__ = Constants::to_INPUT_BORDERSTYLE(static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(argument));
    set_borderStyle(borderStyle__);
    return true;
  }
  
  JSValue TextField::getClearButtonModeArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_clearButtonMode()));
  }
  
  bool TextField::setClearButtonModeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    clearButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(argument));
    set_clearButtonMode(clearButtonMode__);
    return true;
  }
  
  JSValue TextField::getLeftButtonModeArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_leftButtonMode()));
  }
  
  bool TextField::setLeftButtonModeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    leftButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(argument));
    set_leftButtonMode(leftButtonMode__);
    return true;
  }
  
  JSValue TextField::getRightButtonModeArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(get_rightButtonMode()));
  }
  
  bool TextField::setRightButtonModeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    rightButtonMode__ = Constants::to_INPUT_BUTTONMODE(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
    set_rightButtonMode(rightButtonMode__);
    return true;
  }
  
  JSValue TextField::getKeyboardTypeArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<KEYBOARD>::type>(get_keyboardType()));
  }
  
  bool TextField::setKeyboardTypeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    keyboardType__ = Constants::to_KEYBOARD(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
    set_keyboardType(keyboardType__);
    return true;
  }
  
  JSValue TextField::getReturnKeyTypeArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<RETURNKEY>::type>(get_returnKeyType()));
  }
  
  bool TextField::setReturnKeyTypeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    returnKeyType__ = Constants::to_RETURNKEY(static_cast<std::underlying_type<RETURNKEY>::type>(argument));
    set_returnKeyType(returnKeyType__);
    return true;
  }
  
  JSValue TextField::getTextAlignArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
  }
  
  bool TextField::setTextAlignArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
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

  JSValue TextField::getAutoCapitalizationArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(get_autoCapitalization()));
  }
  
  bool TextField::setAutoCapitalizationArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    autoCapitalization__ = Constants::to_TEXT_AUTOCAPITALIZATION(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(argument));
    set_autoCapitalization(autoCapitalization__);
    return true;
  }

  JSValue TextField::getVerticalAlignArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
  }
  
  bool TextField::setVerticalAlignArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
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

}} // namespace Titanium { namespace UI {
