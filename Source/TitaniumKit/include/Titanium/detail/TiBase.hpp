/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TIBASE_HPP_
#define _TITANIUM_DETAIL_TIBASE_HPP_

#define TITANIUM_LOGGING_ENABLE
// #define TITANIUM_THREAD_SAFE

#define TITANIUM_ASSERT(expr) assert(expr)
#define TITANIUM_ASSERT_AND_THROW(expr, message) \
  if (!expr) { \
    HAL::detail::ThrowRuntimeError("Invalid argument supplied", message); \
  }

#define TITANIUM_NOEXCEPT_ENABLE
#define TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE

// See http://msdn.microsoft.com/en-us/library/b0084kay.aspx for the
// list of Visual C++ "Predefined Macros". Visual Studio 2013 Update 3
// RTM ships with MSVC 18.0.30723.0

#if defined(_MSC_VER) && _MSC_VER <= 1800
// According to Microsoft's "Visual C++ Team Blog":
//
// VS 2013 supported rvalue references, except for automatically
// generated move ctors/assigns. Similarly, VS 2013 supported
// defaulted and deleted functions, except for defaulted move
// ctors/assigns.
//
// The CTP supports noexcept's unconditional form. (Additionally,
// while noexcept's terminate() semantics have been implemented, they
// require library support, and the CTP was intentionally shipped
// without updated libraries.)
//
// Reference:
// http://blogs.msdn.com/b/vcblog/archive/2013/12/02/c-11-14-core-language-features-in-vs-2013-and-the-nov-2013-ctp.aspx

#undef TITANIUM_NOEXCEPT_ENABLE
#undef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE

#endif  // #defined(_MSC_VER) && _MSC_VER <= 1800

#ifdef TITANIUM_NOEXCEPT_ENABLE
#define TITANIUM_NOEXCEPT noexcept
#else
#define TITANIUM_NOEXCEPT
#endif

#ifdef TITANIUM_THREAD_SAFE
#include <mutex>
#endif

#include "TitaniumKit_EXPORT.h"

#include "Titanium/detail/TiLogger.hpp"
#include "HAL/HAL.hpp"

#define TITANIUM_FUNCTION(MODULE, NAME) \
JSValue MODULE::js_##NAME(const std::vector<JSValue>& arguments, JSObject& this_object)

#define TITANIUM_PROPERTY_GETTER(MODULE, NAME) \
JSValue MODULE::js_get_##NAME() const

#define TITANIUM_PROPERTY_SETTER(MODULE, NAME) \
bool MODULE::js_set_##NAME(const JSValue& argument)

#define TITANIUM_FUNCTION_DEF(NAME) \
JSValue js_##NAME(const std::vector<JSValue>& arguments, JSObject& this_object)

#define TITANIUM_PROPERTY_READONLY_DEF(NAME) \
JSValue js_get_##NAME() const

#define TITANIUM_PROPERTY_DEF(NAME) \
TITANIUM_PROPERTY_READONLY_DEF(NAME); \
bool js_set_##NAME(const JSValue& argument)

#define TITANIUM_ADD_FUNCTION(MODULE, NAME) \
JSExport<MODULE>::AddFunctionProperty(#NAME, std::mem_fn(&MODULE::js_##NAME))

#define TITANIUM_ADD_PROPERTY_READONLY(MODULE, NAME) \
JSExport<MODULE>::AddValueProperty(#NAME, std::mem_fn(&MODULE::js_get_##NAME))

#define TITANIUM_ADD_PROPERTY(MODULE, NAME) \
JSExport<MODULE>::AddValueProperty(#NAME, std::mem_fn(&MODULE::js_get_##NAME), std::mem_fn(&MODULE::js_set_##NAME))

#define ENSURE_ARGUMENT_BOUNDS(INDEX) TITANIUM_ASSERT_AND_THROW((arguments.size() >= INDEX + 1), ("Index out of bounds: "#INDEX))

#define ENSURE_OPTIONAL_OBJECT_AT_INDEX(OUT,INDEX) \
  auto OUT = this_object.get_context().CreateObject(); \
  if (arguments.size() >= INDEX + 1) { \
    const auto _##INDEX = arguments.at(INDEX); \
    TITANIUM_ASSERT_AND_THROW(_##INDEX.IsObject(), "Expected Object"); \
    OUT = static_cast<JSObject>(_##INDEX);\
  }

#define ENSURE_OPTIONAL_BOOL_AT_INDEX(OUT,INDEX,VALUE) \
  auto OUT = VALUE; \
  if (arguments.size() >= INDEX + 1) { \
    const auto _##INDEX = arguments.at(INDEX); \
    TITANIUM_ASSERT_AND_THROW(_##INDEX.IsBoolean(), "Expected boolean"); \
    OUT = static_cast<bool>(_##INDEX);\
  }

#define ENSURE_OPTIONAL_STRING_AT_INDEX(OUT,INDEX,VALUE) \
  std::string OUT = VALUE; \
  if (arguments.size() >= INDEX + 1) { \
    const auto _##INDEX = arguments.at(INDEX); \
    OUT = static_cast<std::string>(_##INDEX);\
  }

#define ENSURE_OPTIONAL_NUMBER_AT_INDEX(OUT,INDEX,VALUE,TYPE) \
  TYPE OUT = VALUE; \
  if (arguments.size() >= INDEX + 1) { \
    const auto _##INDEX = arguments.at(INDEX); \
    TITANIUM_ASSERT_AND_THROW(_##INDEX.IsNumber(), "Expected Number"); \
    OUT = static_cast<TYPE>(_##INDEX);\
  }

#define ENSURE_OPTIONAL_ARRAY_AT_INDEX(OUT,INDEX) \
  auto OUT = this_object.get_context().CreateArray(); \
  if (arguments.size() >= INDEX + 1) { \
    const auto _##INDEX = arguments.at(INDEX); \
    TITANIUM_ASSERT_AND_THROW(_##INDEX.IsObject(), "Expected Object"); \
    const auto _obj_##INDEX = static_cast<JSObject>(_##INDEX); \
    TITANIUM_ASSERT_AND_THROW(_obj_##INDEX.IsArray(), "Expected Array"); \
    OUT = static_cast<JSArray>(_obj_##INDEX); \
  }

#define ENSURE_OPTIONAL_INT_AT_INDEX(OUT,INDEX,VALUE) \
  ENSURE_OPTIONAL_NUMBER_AT_INDEX(OUT,INDEX,VALUE,int32_t)

#define ENSURE_OPTIONAL_UINT_AT_INDEX(OUT,INDEX,VALUE) \
  ENSURE_OPTIONAL_NUMBER_AT_INDEX(OUT,INDEX,VALUE,uint32_t)

#define ENSURE_OPTIONAL_DOUBLE_AT_INDEX(OUT,INDEX,VALUE) \
  ENSURE_OPTIONAL_NUMBER_AT_INDEX(OUT,INDEX,VALUE,double)

#define ENSURE_NUMBER_AT_INDEX(OUT,INDEX,TYPE) \
  ENSURE_ARGUMENT_BOUNDS(INDEX); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT_AND_THROW(_##INDEX.IsNumber(), "Expected Number"); \
  auto OUT = static_cast<TYPE>(_##INDEX);

#define ENSURE_BOOL_AT_INDEX(OUT,INDEX) \
  ENSURE_ARGUMENT_BOUNDS(INDEX); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT_AND_THROW(_##INDEX.IsBoolean(), "Expected boolean"); \
  auto OUT = static_cast<bool>(_##INDEX);

#define ENSURE_STRING_AT_INDEX(OUT,INDEX) \
  ENSURE_ARGUMENT_BOUNDS(INDEX); \
  const auto _##INDEX = arguments.at(INDEX); \
  auto OUT = static_cast<std::string>(_##INDEX);

#define ENSURE_VALUE_AT_INDEX(OUT,INDEX) \
  ENSURE_ARGUMENT_BOUNDS(INDEX); \
  OUT = arguments.at(INDEX);

#define ENSURE_OBJECT_AT_INDEX(OUT,INDEX) \
  ENSURE_ARGUMENT_BOUNDS(INDEX); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT_AND_THROW(_##INDEX.IsObject(), "Expected Object"); \
  auto OUT = static_cast<JSObject>(_##INDEX);

#define ENSURE_ARRAY_AT_INDEX(OUT,INDEX) \
  ENSURE_ARGUMENT_BOUNDS(INDEX); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT_AND_THROW(_##INDEX.IsObject(), "Expected Object"); \
  const auto _obj_##INDEX = static_cast<JSObject>(_##INDEX); \
  TITANIUM_ASSERT_AND_THROW(_obj_##INDEX.IsArray(), "Expected Array"); \
  auto OUT = static_cast<JSArray>(_obj_##INDEX);

#define ENSURE_INT_AT_INDEX(OUT,INDEX) \
  ENSURE_NUMBER_AT_INDEX(OUT,INDEX,int32_t)

#define ENSURE_UINT_AT_INDEX(OUT,INDEX) \
  ENSURE_NUMBER_AT_INDEX(OUT,INDEX,uint32_t)

#define ENSURE_DOUBLE_AT_INDEX(OUT,INDEX) \
  ENSURE_NUMBER_AT_INDEX(OUT,INDEX,double)

// Shorthand for getter function
#define TITANIUM_FUNCTION_AS_GETTER(MODULE, NAME, PROPERTY) \
TITANIUM_FUNCTION(MODULE, NAME) \
{ \
  return js_get_##PROPERTY(); \
}

// Shorthand for setter function
#define TITANIUM_FUNCTION_AS_SETTER(MODULE, NAME, PROPERTY) \
TITANIUM_FUNCTION(MODULE, NAME) \
{ \
  ENSURE_VALUE_AT_INDEX(argument, 0); \
  return js_set_##PROPERTY(argument); \
}


#endif  // _TITANIUM_DETAIL_TIBASE_HPP_
