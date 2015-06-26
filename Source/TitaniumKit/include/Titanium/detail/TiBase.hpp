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
#include "Titanium/detail/TiImpl.hpp"
#include "HAL/HAL.hpp"

// For defining the bridge function for a function property exposed on JS Object (hpp)
#define TITANIUM_FUNCTION_DEF(NAME) \
JSValue js_##NAME(const std::vector<JSValue>& arguments, JSObject& this_object)

// For defining the getter bridge function for a read-only property exposed on JS Object (hpp)
#define TITANIUM_PROPERTY_READONLY_DEF(NAME) \
JSValue js_get_##NAME() const

// For defining the getter and setter bridge functions for a property exposed on JS Object (hpp)
#define TITANIUM_PROPERTY_DEF(NAME) \
TITANIUM_PROPERTY_READONLY_DEF(NAME); \
bool js_set_##NAME(const JSValue& argument)

// For defining the native c++ getter method for a property (hpp)
#define TITANIUM_PROPERTY_IMPL_READONLY_DEF(TYPE, NAME) \
virtual TYPE get_##NAME() const TITANIUM_NOEXCEPT

// For defining the native c++ type getter/setter methods for a property. (hpp)
#define TITANIUM_PROPERTY_IMPL_DEF(TYPE, NAME) \
TITANIUM_PROPERTY_IMPL_READONLY_DEF(TYPE, NAME); \
virtual void set_##NAME(const TYPE& NAME) TITANIUM_NOEXCEPT

#endif  // _TITANIUM_DETAIL_TIBASE_HPP_
