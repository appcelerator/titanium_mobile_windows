/**
 * JavaScriptCoreCPP
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "JavaScriptCoreCPP/JSValue.hpp"

#include "JavaScriptCoreCPP/JSContext.hpp"
#include "JavaScriptCoreCPP/JSString.hpp"

#include "JavaScriptCoreCPP/JSUndefined.hpp"
#include "JavaScriptCoreCPP/JSNull.hpp"
#include "JavaScriptCoreCPP/JSBoolean.hpp"
#include "JavaScriptCoreCPP/JSNumber.hpp"

#include "JavaScriptCoreCPP/JSObject.hpp"
#include "JavaScriptCoreCPP/JSArray.hpp"
#include "JavaScriptCoreCPP/JSDate.hpp"
#include "JavaScriptCoreCPP/JSError.hpp"
#include "JavaScriptCoreCPP/JSFunction.hpp"
#include "JavaScriptCoreCPP/JSRegExp.hpp"

#include "JavaScriptCoreCPP/JSClass.hpp"

#include "JavaScriptCoreCPP/detail/JSUtil.hpp"

#include <sstream>
#include <cassert>

namespace JavaScriptCoreCPP {
  
  
  JSString JSValue::ToJSONString(unsigned indent) {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JSValueRef exception { nullptr };
    JSStringRef js_string_ref = JSValueCreateJSONString(js_context__, js_value_ref__, indent, &exception);
    if (exception) {
      // If this assert fails then we need to JSStringRelease
      // js_string_ref.
      assert(!js_string_ref);
      detail::ThrowRuntimeError("JSValue", JSValue(js_context__, exception));
    }
    
    if (js_string_ref) {
      JSString js_string(js_string_ref);
      JSStringRelease(js_string_ref);
      return js_string;
    }
    
    return JSString();
  }
  
  JSValue::operator JSString() const {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JSValueRef exception { nullptr };
    JSStringRef js_string_ref = JSValueToStringCopy(js_context__, js_value_ref__, &exception);
    if (exception) {
      detail::ThrowRuntimeError("JSValue", JSValue(js_context__, exception));
    }
    
    assert(js_string_ref);
    JSString js_string(js_string_ref);
    JSStringRelease(js_string_ref);
    
    return js_string;
  }
  
  JSValue::operator std::string() const {
    return operator JSString();
  }
  
  JSValue::operator bool() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueToBoolean(js_context__, js_value_ref__);
  }
  
  JSValue::operator JSBoolean() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return js_context__.CreateBoolean(operator bool());
  }
  
  JSValue::operator double() const {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JSValueRef exception { nullptr };
    const double result = JSValueToNumber(js_context__, js_value_ref__, &exception);
    
    if (exception) {
      detail::ThrowRuntimeError("JSValue", JSValue(js_context__, exception));
    }
    
    return result;
  }
  
  JSValue::operator int32_t() const {
    return detail::to_int32_t(operator double());
  }
  
  JSValue::operator JSNumber() const {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return js_context__.CreateNumber(operator double());
  }
  
  JSValue::operator JSObject() const {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JSValueRef exception { nullptr };
    JSObjectRef js_object_ref = JSValueToObject(js_context__, js_value_ref__, &exception);
    
    if (exception) {
      // If this assert fails then we need to JSValueUnprotect
      // js_object_ref.
      assert(!js_object_ref);
      detail::ThrowRuntimeError("JSValue", JSValue(js_context__, exception));
    }
    
    assert(js_object_ref);
    return JSObject(js_context__, js_object_ref);
  }
  
  JSValue::Type JSValue::GetType() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    auto type = Type::Undefined;
    const JSType js_type = JSValueGetType(js_context__, js_value_ref__);
    switch (js_type) {
      case kJSTypeUndefined:
        type = Type::Undefined;
        break;
        
      case kJSTypeNull:
        type = Type::Null;
        break;
        
      case kJSTypeBoolean:
        type = Type::Boolean;
        break;
        
      case kJSTypeNumber:
        type = Type::Number;
        break;
        
      case kJSTypeString:
        type = Type::String;
        break;
        
      case kJSTypeObject:
        type = Type::Object;
        break;
    }

    return type;
  }
  
  bool JSValue::IsUndefined() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueIsUndefined(js_context__, js_value_ref__);
  }
  
  bool JSValue::IsNull() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueIsNull(js_context__, js_value_ref__);
  }
  
  bool JSValue::IsBoolean() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueIsBoolean(js_context__, js_value_ref__);
  }
  
  bool JSValue::IsNumber() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueIsNumber(js_context__, js_value_ref__);
  }
  
  bool JSValue::IsString() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueIsString(js_context__, js_value_ref__);
  }
  
  bool JSValue::IsObject() const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueIsObject(js_context__, js_value_ref__);
  }
  
  bool JSValue::IsObjectOfClass(const JSClass& js_class) const JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    return JSValueIsObjectOfClass(js_context__, js_value_ref__, js_class);
  }
  
  bool JSValue::IsInstanceOfConstructor(const JSObject& constructor) const {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JSValueRef exception { nullptr };
    const bool result = JSValueIsInstanceOfConstructor(js_context__, js_value_ref__, constructor, &exception);
    if (exception) {
      detail::ThrowRuntimeError("JSValue", JSValue(js_context__, exception));
    }
    
    return result;
  }
  
  bool JSValue::IsEqualWithTypeCoercion(const JSValue& rhs) const {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JSValueRef exception { nullptr };
    const bool result = JSValueIsEqual(js_context__, js_value_ref__, rhs.js_value_ref__, &exception);
    if (exception) {
      detail::ThrowRuntimeError("JSValue", JSValue(js_context__, exception));
    }
    
    return result;
  }
  
  bool IsEqualWithTypeCoercion(const JSValue& lhs, const JSValue& rhs) {
    return lhs.IsEqualWithTypeCoercion(rhs);
  }
  
  JSValue::~JSValue() JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: dtor");
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: release ", js_value_ref__);
    JSValueUnprotect(js_context__, js_value_ref__);
  }
  
  JSValue::JSValue(const JSValue& rhs) JAVASCRIPTCORECPP_NOEXCEPT
  : js_context__(rhs.js_context__)
  , js_value_ref__(rhs.js_value_ref__) {
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: copy ctor");
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: retain ", js_value_ref__);
    JSValueProtect(js_context__, js_value_ref__);
  }
  
  JSValue::JSValue(JSValue&& rhs) JAVASCRIPTCORECPP_NOEXCEPT
  : js_context__(std::move(rhs.js_context__))
  , js_value_ref__(rhs.js_value_ref__) {
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: move ctor");
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: retain ", js_value_ref__);
    JSValueProtect(js_context__, js_value_ref__);
  }
  
  JSValue& JSValue::operator=(const JSValue& rhs) {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: copy assignment");
    // JSValues can only be copied between contexts within the same
    // context group.
    if (js_context__.get_context_group() != rhs.js_context__.get_context_group()) {
      detail::ThrowRuntimeError("JSValue", "JSValues must belong to JSContexts within the same JSContextGroup to be shared and exchanged.");
    }
    
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: release ", js_value_ref__);
    JSValueUnprotect(js_context__, js_value_ref__);
    js_value_ref__ = rhs.js_value_ref__;
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: retain ", js_value_ref__);
    JSValueProtect(js_context__, js_value_ref__);
    return *this;
  }
  
  JSValue& JSValue::operator=(JSValue&& rhs) {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: move assignment");
    // JSValues can only be copied between contexts within the same
    // context group.
    if (js_context__.get_context_group() != rhs.js_context__.get_context_group()) {
      detail::ThrowRuntimeError("JSValue", "JSValues must belong to JSContexts within the same JSContextGroup to be shared and exchanged.");
    }

    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: release ", js_value_ref__);
    JSValueUnprotect(js_context__, js_value_ref__);
    js_value_ref__ = rhs.js_value_ref__;
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: retain ", js_value_ref__);
    JSValueProtect(js_context__, js_value_ref__);
    return *this;
  }
  
  void JSValue::swap(JSValue& other) JAVASCRIPTCORECPP_NOEXCEPT {
    JAVASCRIPTCORECPP_JSVALUE_LOCK_GUARD;
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: swap");
    using std::swap;
    
    // By swapping the members of two classes, the two classes are
    // effectively swapped.
    swap(js_context__  , other.js_context__);
    swap(js_value_ref__, other.js_value_ref__);
  }
  
  JSValue::JSValue(const JSContext& js_context, const JSString& js_string, bool parse_as_json)
  : js_context__(js_context) {
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: ctor");
    if (parse_as_json) {
      js_value_ref__ = JSValueMakeFromJSONString(js_context, js_string);
      if (!js_value_ref__) {
        const std::string message = "Input is not a valid JSON string: " + to_string(js_string);
        detail::ThrowRuntimeError("JSValue", message);
      }
    } else {
      js_value_ref__ = JSValueMakeString(js_context__, js_string);
    }
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: retain ", js_value_ref__);
  }
  
  // For interoperability with the JavaScriptCore C API.
  JSValue::JSValue(const JSContext& js_context, JSValueRef js_value_ref) JAVASCRIPTCORECPP_NOEXCEPT
  : js_context__(js_context)
  , js_value_ref__(js_value_ref)  {
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: ctor");
    assert(js_value_ref__);
    JAVASCRIPTCORECPP_LOG_DEBUG("JSValue:: retain ", js_value_ref__);
    JSValueProtect(js_context__, js_value_ref__);
  }
  
  std::string to_string(const JSValue::Type& js_value_type) JAVASCRIPTCORECPP_NOEXCEPT {
	  std::string string = "Unknown";
    switch (js_value_type) {
      case JSValue::Type::Undefined:
        string = "Undefined";
        break;
      case JSValue::Type::Null:
        string = "Null";
        break;
      case JSValue::Type::Boolean:
        string = "Boolean";
        break;
      case JSValue::Type::Number:
        string = "Number";
        break;
      case JSValue::Type::String:
        string = "String";
        break;
      case JSValue::Type::Object:
        string = "Object";
        break;
    }
    return string;
  }
  
  bool operator==(const JSValue& lhs, const JSValue& rhs) JAVASCRIPTCORECPP_NOEXCEPT {
    return JSValueIsStrictEqual(lhs.get_context(), lhs, rhs);
  }
  
  
} // namespace JavaScriptCoreCPP {
