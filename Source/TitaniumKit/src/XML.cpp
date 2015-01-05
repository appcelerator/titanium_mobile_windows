/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/XML.hpp"

namespace Titanium {
  
  XML::XML(const JSContext& js_context) TITANIUM_NOEXCEPT
  : Module(js_context)
  {
  }
  
  XML::XML(const XML& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments) 
  {
  }
  
  void XML::JSExportInitialize() {
    JSExport<XML>::SetClassVersion(1);
    JSExport<XML>::SetParent(JSExport<Module>::Class());
    JSExport<XML>::AddFunctionProperty("parseString", std::mem_fn(&XML::parseString_ArgumentValidator));
    JSExport<XML>::AddFunctionProperty("serializeToString", std::mem_fn(&XML::serializeToString_ArgumentValidator));
  }

  JSValue XML::parseString_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("XML::parseString_ArgumentValidator: Unimplemented");
    return get_context().CreateUndefined();
  }

  JSValue XML::serializeToString_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("XML::serializeToString_ArgumentValidator: Unimplemented");
    return get_context().CreateUndefined();
  }

} // namespace Titanium {
