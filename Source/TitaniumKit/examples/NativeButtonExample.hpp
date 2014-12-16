/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEBUTTONEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEBUTTONEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"
#include <string>

using namespace HAL;

/*!
 @class
 
 @discussion This is an example of how to implement Titanium::UI::Button
 for a native platform.
 */
class NativeButtonExample final : public Titanium::UI::Button, public JSExport<NativeButtonExample> {
  
public:
  
  NativeButtonExample(const JSContext& js_context)                                       TITANIUM_NOEXCEPT;
  NativeButtonExample(const NativeButtonExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeButtonExample()                             = default;
  NativeButtonExample(const NativeButtonExample&)            = default;
  NativeButtonExample& operator=(const NativeButtonExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeButtonExample(NativeButtonExample&&)                 = default;
  NativeButtonExample& operator=(NativeButtonExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
  virtual bool setTitleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
};

#endif // _TITANIUM_EXAMPLES_NATIVEBUTTONEXAMPLE_HPP_
