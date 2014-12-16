/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Picker.hpp"
#include <type_traits>

namespace Titanium { namespace UI {
  
  Picker::Picker(const JSContext& js_context) TITANIUM_NOEXCEPT
  : View(js_context)
  , type__(PICKER_TYPE::PLAIN) {
  }
  
  Picker::Picker(const Picker& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : View(rhs, arguments)
  , type__(rhs.type__) {
  }
  
  PICKER_TYPE Picker::get_type() const  TITANIUM_NOEXCEPT {
    return type__;
  }
  
  void Picker::set_type(const PICKER_TYPE& type) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Picker::set_type: Unimplemented");
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void Picker::JSExportInitialize() {
    JSExport<Picker>::SetClassVersion(1);
    JSExport<Picker>::SetParent(JSExport<View>::Class());
    JSExport<Picker>::AddValueProperty("type", std::mem_fn(&Picker::getTypeArgumentValidator), std::mem_fn(&Picker::setTypeArgumentValidator));
  }
  
  JSValue Picker::getTypeArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<PICKER_TYPE>::type>(get_type()));
  }
  
  bool Picker::setTypeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    type__ = Constants::to_PICKER_TYPE(static_cast<std::underlying_type<PICKER_TYPE>::type>(argument));
    set_type(type__);
    return true;
  }

}} // namespace Titanium { namespace UI {
