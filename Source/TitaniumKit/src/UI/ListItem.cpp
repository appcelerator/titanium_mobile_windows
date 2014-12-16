/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListItem.hpp"
#include <type_traits>

namespace Titanium { namespace UI {
  
  ListItem::ListItem(const JSContext& js_context) TITANIUM_NOEXCEPT
  : Module(js_context)
  , accessoryType__(LIST_ACCESSORY_TYPE::NONE) {
  }
  
  ListItem::ListItem(const ListItem& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments)
  , accessoryType__(rhs.accessoryType__) {
  }
  
  LIST_ACCESSORY_TYPE ListItem::get_accessoryType() const  TITANIUM_NOEXCEPT {
    return accessoryType__;
  }
  
  void ListItem::set_accessoryType(const LIST_ACCESSORY_TYPE& accessoryType) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("ListItem::set_accessoryType: Unimplemented");
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void ListItem::JSExportInitialize() {
    JSExport<ListItem>::SetClassVersion(1);
    JSExport<ListItem>::SetParent(JSExport<Module>::Class());
    JSExport<ListItem>::AddValueProperty("accessoryType", std::mem_fn(&ListItem::getAccessoryTypeArgumentValidator), std::mem_fn(&ListItem::setAccessoryTypeArgumentValidator));
  }
  
  JSValue ListItem::getAccessoryTypeArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(get_accessoryType()));
  }
  
  bool ListItem::setAccessoryTypeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    accessoryType__ = Constants::to_LIST_ACCESSORY_TYPE(static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(argument));
    set_accessoryType(accessoryType__);
    return true;
  }

}} // namespace Titanium { namespace UI {
