/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEMODULEEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEMODULEEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
 @class
 
 @discussion This is an example of how to implement a native module
 derived from Titanium::UI::Module for a native platform.
 */
class NativeModuleExample final : public Titanium::Module, public JSExport<NativeModuleExample> {
  
public:
  
  JSValue get_enabled() const;
  
  std::string get_event_name() const                        TITANIUM_NOEXCEPT;
  void        set_event_name(const std::string& event_name) TITANIUM_NOEXCEPT;
  
  NativeModuleExample(const JSContext& js_context)                                       TITANIUM_NOEXCEPT;
  NativeModuleExample(const NativeModuleExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeModuleExample()                             = default;
  NativeModuleExample(const NativeModuleExample&)            = default;
  NativeModuleExample& operator=(const NativeModuleExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeModuleExample(NativeModuleExample&&)                 = default;
  NativeModuleExample& operator=(NativeModuleExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
protected:
  
  virtual void  enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
  virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;
  
private:
  
  std::string event_name__;
  JSValue     enabled__;
};

#endif // _TITANIUM_EXAMPLES_NATIVEMODULEEXAMPLE_HPP_
