/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEPLATFORMEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEPLATFORMEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
 @class
 @discussion This is an example of how to implement Titanium::Platform
 for a native platform.
 */
class NativePlatformExample final : public Titanium::Platform, public JSExport<NativePlatformExample> {
  
public:
  
  NativePlatformExample(const JSContext& js_context)                                    TITANIUM_NOEXCEPT;
  NativePlatformExample(const NativePlatformExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativePlatformExample()                          = default;
  NativePlatformExample(const NativePlatformExample&)            = default;
  NativePlatformExample& operator=(const NativePlatformExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativePlatformExample(NativePlatformExample&&)                 = default;
  NativePlatformExample& operator=(NativePlatformExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
protected:
  
  virtual std::string osname() const TITANIUM_NOEXCEPT override final;
};

#endif // _TITANIUM_EXAMPLES_NATIVEPLATFORMEXAMPLE_HPP_
