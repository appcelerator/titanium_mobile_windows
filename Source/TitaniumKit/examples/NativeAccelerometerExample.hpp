/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEACCELEROMATEREXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEACCELEROMATEREXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
 @class
 @discussion This is an example of how to implement Titanium::Accelerometer
 for a native Accelerometer.
 */
class NativeAccelerometerExample final : public Titanium::Accelerometer, public JSExport<NativeAccelerometerExample> {
  
public:
  
  NativeAccelerometerExample(const JSContext& js_context)                                    TITANIUM_NOEXCEPT;
  NativeAccelerometerExample(const NativeAccelerometerExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeAccelerometerExample()                          = default;
  NativeAccelerometerExample(const NativeAccelerometerExample&)            = default;
  NativeAccelerometerExample& operator=(const NativeAccelerometerExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeAccelerometerExample(NativeAccelerometerExample&&)                 = default;
  NativeAccelerometerExample& operator=(NativeAccelerometerExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
  virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
  virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;

protected:
};

#endif // _TITANIUM_EXAMPLES_NATIVEACCELEROMATEREXAMPLE_HPP_
