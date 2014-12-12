/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEGESTUREEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEGESTUREEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace JavaScriptCoreCPP;

/*!
 @class
 @discussion This is an example of how to implement Titanium::Gesture
 for a native Gesture.
 */
class NativeGestureExample final : public Titanium::Gesture, public JSExport<NativeGestureExample> {
  
public:
  
  NativeGestureExample(const JSContext& js_context)                                    TITANIUM_NOEXCEPT;
  NativeGestureExample(const NativeGestureExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeGestureExample()                          = default;
  NativeGestureExample(const NativeGestureExample&)            = default;
  NativeGestureExample& operator=(const NativeGestureExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeGestureExample(NativeGestureExample&&)                 = default;
  NativeGestureExample& operator=(NativeGestureExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
  virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
  virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;

  virtual Titanium::UI::ORIENTATION get_orientation() const TITANIUM_NOEXCEPT override;

protected:
  
};

#endif // _TITANIUM_EXAMPLES_NATIVEGESTUREEXAMPLE_HPP_
