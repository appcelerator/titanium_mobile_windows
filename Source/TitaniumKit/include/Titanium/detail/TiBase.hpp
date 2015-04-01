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

#define TITANIUM_MODULE_FUNCTION(MODULE, NAME) \
JSValue MODULE::js_##NAME(const std::vector<JSValue>& arguments, JSObject& this_object)

#define TITANIUM_MODULE_PROPERTY_GETTER(MODULE, NAME) \
JSValue MODULE::js_get_##NAME() const

#define TITANIUM_MODULE_PROPERTY_SETTER(MODULE, NAME) \
bool MODULE::js_set_##NAME(const JSValue& argument)

#define TITANIUM_MODULE_FUNCTION_DEF(NAME) \
JSValue js_##NAME(const std::vector<JSValue>& arguments, JSObject& this_object);

#define TITANIUM_MODULE_PROPERTY_READONLY_DEF(NAME) \
JSValue js_get_##NAME() const;

#define TITANIUM_MODULE_PROPERTY_DEF(NAME) \
JSValue js_get_##NAME() const; \
bool js_set_##NAME(const JSValue& argument);

#define TITANIUM_MODULE_ADD_FUNCTION(MODULE, NAME) \
JSExport<MODULE>::AddFunctionProperty(#NAME, std::mem_fn(&MODULE::js_##NAME))

#define TITANIUM_MODULE_ADD_PROPERTY_READONLY(MODULE, NAME) \
JSExport<MODULE>::AddValueProperty(#NAME, std::mem_fn(&MODULE::js_get_##NAME))

#define TITANIUM_MODULE_ADD_PROPERTY(MODULE, NAME) \
JSExport<MODULE>::AddValueProperty(#NAME, std::mem_fn(&MODULE::js_get_##NAME), std::mem_fn(&MODULE::js_set_##NAME))

#define ENSURE_OPTIONAL_OBJECT_AT_INDEX(OUT,INDEX) \
  auto OUT = this_object.get_context().CreateObject(); \
  if (arguments.size() >= INDEX + 1) { \
    const auto _##INDEX = arguments.at(INDEX); \
    TITANIUM_ASSERT(_##INDEX.IsObject()); \
    OUT = static_cast<JSObject>(_##INDEX);\
  }

#define ENSURE_NUMBER_AT_INDEX(OUT,INDEX,TYPE) \
  TITANIUM_ASSERT(arguments.size() >= INDEX + 1); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT(_##INDEX.IsNumber()); \
  auto OUT = static_cast<TYPE>(_##INDEX);

#define ENSURE_STRING_AT_INDEX(OUT,INDEX) \
  TITANIUM_ASSERT(arguments.size() >= INDEX + 1); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT(_##INDEX.IsString()); \
  auto OUT = static_cast<std::string>(_##INDEX);

#define ENSURE_OBJECT_AT_INDEX(OUT,INDEX) \
  TITANIUM_ASSERT(arguments.size() >= INDEX + 1); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT(_##INDEX.IsObject()); \
  auto OUT = static_cast<JSObject>(_##INDEX);

#define ENSURE_ARRAY_AT_INDEX(OUT,INDEX) \
  TITANIUM_ASSERT(arguments.size() >= INDEX + 1); \
  const auto _##INDEX = arguments.at(INDEX); \
  TITANIUM_ASSERT(_##INDEX.IsObject()); \
  const auto _obj_##INDEX = static_cast<JSObject>(_##INDEX); \
  TITANIUM_ASSERT(_obj_##INDEX.IsArray());\
  auto OUT = static_cast<JSArray>(_obj_##INDEX);

#define ENSURE_INT_AT_INDEX(OUT,INDEX) \
  ENSURE_NUMBER_AT_INDEX(OUT,INDEX,int32_t)

#define ENSURE_UINT_AT_INDEX(OUT,INDEX) \
  ENSURE_NUMBER_AT_INDEX(OUT,INDEX,uint32_t)

#define ENSURE_DOUBLE_AT_INDEX(OUT,INDEX) \
  ENSURE_NUMBER_AT_INDEX(OUT,INDEX,double)

#endif  // _TITANIUM_DETAIL_TIBASE_HPP_
