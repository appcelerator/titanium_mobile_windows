/**
 * TitaniumKit
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEGLOBALOBJECTEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEGLOBALOBJECTEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace JavaScriptCoreCPP;

/*!
 @class
 
 @discussion This is an example of how to implement Titanium::GlobalObject
 for a native platform.
 */
class NativeGlobalObjectExample final : public Titanium::GlobalObject, public JSExport<NativeGlobalObjectExample> {
  
public:

  std::string get_example_resource() const                              TITANIUM_NOEXCEPT;
  void        set_example_resource(const std::string& example_resource) TITANIUM_NOEXCEPT;
  
  
  NativeGlobalObjectExample(const JSContext& js_context)                                             TITANIUM_NOEXCEPT;
  NativeGlobalObjectExample(const NativeGlobalObjectExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeGlobalObjectExample()                                   = default;
  NativeGlobalObjectExample(const NativeGlobalObjectExample&)            = default;
  NativeGlobalObjectExample& operator=(const NativeGlobalObjectExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeGlobalObjectExample(NativeGlobalObjectExample&&)                 = default;
  NativeGlobalObjectExample& operator=(NativeGlobalObjectExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
protected:
  
  virtual std::string LoadResource(const std::string& moduleId) const TITANIUM_NOEXCEPT override final;
  virtual std::shared_ptr<Timer> CreateTimer(Callback_t callback, const std::chrono::milliseconds& interval) const TITANIUM_NOEXCEPT override final;
  
private:
  
  std::string example_resource__;
};

#endif // _TITANIUM_EXAMPLES_NATIVEGLOBALOBJECTEXAMPLE_HPP_
