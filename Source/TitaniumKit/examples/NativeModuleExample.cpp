/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeModuleExample.hpp"

NativeModuleExample::NativeModuleExample(const JSContext& js_context) TITANIUM_NOEXCEPT
: Titanium::Module(js_context)
, event_name__("foo")
, enabled__(js_context.CreateBoolean(false)) {
}

NativeModuleExample::NativeModuleExample(const NativeModuleExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
: Titanium::Module(rhs, arguments)
, event_name__(rhs.event_name__)
, enabled__(rhs.enabled__) {
}

JSValue NativeModuleExample::get_enabled() const {
  return enabled__;
}

std::string NativeModuleExample::get_event_name() const TITANIUM_NOEXCEPT {
  return event_name__;
}

void NativeModuleExample::set_event_name(const std::string& event_name) TITANIUM_NOEXCEPT {
  event_name__ = event_name;
}

void NativeModuleExample::JSExportInitialize() {
  JSExport<NativeModuleExample>::SetClassVersion(1);
  JSExport<NativeModuleExample>::SetParent(JSExport<Titanium::Module>::Class());
  JSExport<NativeModuleExample>::AddValueProperty("enabled", std::mem_fn(&NativeModuleExample::get_enabled));
}

void NativeModuleExample::enableEvent(const std::string& eventName) TITANIUM_NOEXCEPT {
  if (eventName == event_name__) {
    enabled__ = get_context().CreateBoolean(true);
  }
  TITANIUM_LOG_INFO("NativeModuleExample::enableEvent: event name = '", eventName, "', enabled = ", enabled__);
}

void NativeModuleExample::disableEvent(const std::string& eventName) TITANIUM_NOEXCEPT {
  if (eventName == event_name__) {
    enabled__ = get_context().CreateBoolean(false);
  }
  TITANIUM_LOG_INFO("NativeModuleExample::disableEvent: event name = '", eventName, "', enabled = ", enabled__);
}
