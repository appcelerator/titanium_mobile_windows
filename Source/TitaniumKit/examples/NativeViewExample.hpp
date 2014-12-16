/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEVIEW_HPP_
#define _TITANIUM_EXAMPLES_NATIVEVIEW_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
 @class
 
 @discussion This is an example of how to implement Titanium::UI::View
 for a native platform.
 */
class NativeViewExample : public Titanium::UI::View, public JSExport<NativeViewExample> {
  
public:
  
  NativeViewExample(const JSContext& js_context)                                     TITANIUM_NOEXCEPT;
  NativeViewExample(const NativeViewExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeViewExample()                           = default;
  NativeViewExample(const NativeViewExample&)            = default;
  NativeViewExample& operator=(const NativeViewExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeViewExample(NativeViewExample&&)                 = default;
  NativeViewExample& operator=(NativeViewExample&&)      = default;
#endif
  
  static void JSExportInitialize();

  virtual bool setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;
};

#endif // _TITANIUM_EXAMPLES_NATIVEVIEW_HPP_
