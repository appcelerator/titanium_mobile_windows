/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Accelerometer.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium {

	Accelerometer::Accelerometer(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context) {
	}

	Accelerometer::Accelerometer(const Accelerometer& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Module(rhs, arguments) {
	}
	void Accelerometer::JSExportInitialize() {
    JSExport<Accelerometer>::SetClassVersion(1);
    JSExport<Accelerometer>::SetParent(JSExport<Module>::Class());
	}
  
  void Accelerometer::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Ti::Accelerometer::enableEvent: Unimplemented (event name '", event_name, "'");
  }
  
  void Accelerometer::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Ti::Accelerometer::disableEvent: Unimplemented (event name '", event_name, "'");
  }


} // namespace Titanium
