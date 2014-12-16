/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListView.hpp"
#include <type_traits>

namespace Titanium { namespace UI {
  
  ListView::ListView(const JSContext& js_context) TITANIUM_NOEXCEPT
  : View(js_context)
  , defaultItemTemplate__(LIST_ITEM_TEMPLATE::DEFAULT) {
  }
  
  ListView::ListView(const ListView& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : View(rhs, arguments)
  , defaultItemTemplate__(rhs.defaultItemTemplate__) {
  }
  
  LIST_ITEM_TEMPLATE ListView::get_defaultItemTemplate() const  TITANIUM_NOEXCEPT {
    return defaultItemTemplate__;
  }
  
  void ListView::set_defaultItemTemplate(const LIST_ITEM_TEMPLATE& defaultItemTemplate) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("ListView::set_defaultItemTemplate: Unimplemented");
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void ListView::JSExportInitialize() {
    JSExport<ListView>::SetClassVersion(1);
    JSExport<ListView>::SetParent(JSExport<View>::Class());
    JSExport<ListView>::AddValueProperty("defaultItemTemplate", std::mem_fn(&ListView::getDefaultItemTemplateArgumentValidator), std::mem_fn(&ListView::setDefaultItemTemplateArgumentValidator));
  }
  
  JSValue ListView::getDefaultItemTemplateArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<LIST_ITEM_TEMPLATE>::type>(get_defaultItemTemplate()));
  }
  
  bool ListView::setDefaultItemTemplateArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    defaultItemTemplate__ = Constants::to_LIST_ITEM_TEMPLATE(static_cast<std::underlying_type<LIST_ITEM_TEMPLATE>::type>(argument));
    set_defaultItemTemplate(defaultItemTemplate__);
    return true;
  }

}} // namespace Titanium { namespace UI {
