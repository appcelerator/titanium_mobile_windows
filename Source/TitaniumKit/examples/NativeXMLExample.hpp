/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEXMLEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEXMLEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
 @class
 @discussion This is an example of how to implement Titanium::XML
 for a native XML.
 */
class NativeXMLExample final : public Titanium::XML, public JSExport<NativeXMLExample> {
  
public:
  
  NativeXMLExample(const JSContext& js_context)                                    TITANIUM_NOEXCEPT;
  NativeXMLExample(const NativeXMLExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeXMLExample()                          = default;
  NativeXMLExample(const NativeXMLExample&)            = default;
  NativeXMLExample& operator=(const NativeXMLExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeXMLExample(NativeXMLExample&&)                 = default;
  NativeXMLExample& operator=(NativeXMLExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
protected:
  
};

#endif // _TITANIUM_EXAMPLES_NATIVEXMLEXAMPLE_HPP_
