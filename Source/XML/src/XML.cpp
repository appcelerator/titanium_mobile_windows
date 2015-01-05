/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/XML.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>
#include <objbase.h>

namespace TitaniumWindows {

  XML::XML(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::XML(js_context)
    , ti_xml(js_context.CreateObject())
  {
    TITANIUM_LOG_DEBUG("TitaniumWindows::XML::ctor Initialize");
  }

  XML::XML(const XML& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::XML(rhs, arguments) 
    , ti_xml(get_context().CreateObject()) {
    TITANIUM_LOG_DEBUG("TitaniumWindows::XML::ctor CallAsConstructor");

    const auto globalObject = get_context().get_global_object();
    const auto xrequire_property = globalObject.GetProperty("require");
    TITANIUM_ASSERT(xrequire_property.IsObject());
    JSObject xrequire = xrequire_property;

    auto result = xrequire("TitaniumWindows_XML/ti.xml.js");
    if (result.IsObject()) {
      ti_xml = result;
    }
  }

  XML::~XML() {
    TITANIUM_LOG_DEBUG("TitaniumWindows::XML::dtor");
  }

  void XML::JSExportInitialize() {
    JSExport<XML>::SetClassVersion(1);
    JSExport<XML>::SetParent(JSExport<Titanium::XML>::Class());
  }

  JSValue XML::parseString_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    auto func = ti_xml.GetProperty("parserString");
    return static_cast<JSObject>(func)();
  }

  JSValue XML::serializeToString_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    auto func = ti_xml.GetProperty("serializeToString");
    return static_cast<JSObject>(func)();
  }

}  // namespace TitaniumWindows
