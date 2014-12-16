/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Gesture.hpp"
#include <type_traits>

namespace Titanium {
  
  Gesture::Gesture(const JSContext& js_context) TITANIUM_NOEXCEPT
  : Module(js_context) {
  }
  
  Gesture::Gesture(const Gesture& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments) {
  }
  
  Titanium::UI::ORIENTATION Gesture::get_orientation() const  TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Gesture::get_orientation: Unimplemented");
    return Titanium::UI::ORIENTATION::UNKNOWN;
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void Gesture::JSExportInitialize() {
    JSExport<Gesture>::SetClassVersion(1);
    JSExport<Gesture>::SetParent(JSExport<Module>::Class());
    JSExport<Gesture>::AddFunctionProperty("getLandscape", std::mem_fn(&Gesture::getLandscape_ArgumentValidator));
    JSExport<Gesture>::AddFunctionProperty("getPortrait", std::mem_fn(&Gesture::getPortrait_ArgumentValidator));
    JSExport<Gesture>::AddFunctionProperty("getOrientation", std::mem_fn(&Gesture::getOrientation_ArgumentValidator));
    JSExport<Gesture>::AddValueProperty("orientation", std::mem_fn(&Gesture::get_orientation_ArgumentValidator));
    JSExport<Gesture>::AddValueProperty("landscape", std::mem_fn(&Gesture::get_landscape_ArgumentValidator));
    JSExport<Gesture>::AddValueProperty("portrait", std::mem_fn(&Gesture::get_portrait_ArgumentValidator));
  }
  
  JSValue Gesture::get_orientation_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(UI::Constants::to_underlying_type(get_orientation()));
  }
  JSValue Gesture::getOrientation_ArgumentValidator(
      const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_orientation_ArgumentValidator();
  }
  
  JSValue Gesture::isFaceDown_ArgumentValidator(
      const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_orientation() == UI::ORIENTATION::FACE_DOWN);
  }
  
  JSValue Gesture::isFaceUp_ArgumentValidator(
      const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_orientation() == UI::ORIENTATION::FACE_UP);
  }
  
  JSValue Gesture::getLandscape_ArgumentValidator(
      const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_landscape_ArgumentValidator();
  }
  
  JSValue Gesture::get_landscape_ArgumentValidator() const TITANIUM_NOEXCEPT {
    const auto o = get_orientation();
    const bool isLandscape = (o == UI::ORIENTATION::LANDSCAPE_LEFT || o == UI::ORIENTATION::LANDSCAPE_RIGHT);
    return get_context().CreateBoolean(isLandscape);
  }
  
  JSValue Gesture::getPortrait_ArgumentValidator(
      const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_portrait_ArgumentValidator();
  }

  JSValue Gesture::get_portrait_ArgumentValidator() const TITANIUM_NOEXCEPT {
    const auto o = get_orientation();
    const bool isPortrait = (o == UI::ORIENTATION::PORTRAIT || o == UI::ORIENTATION::UPSIDE_PORTRAIT);
    return get_context().CreateBoolean(isPortrait);
  };
  
  void Gesture::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Ti::Gesture::enableEvent: Unimplemented (event name '", event_name, "'");
  }
  
  void Gesture::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Ti::Gesture::disableEvent: Unimplemented (event name '", event_name, "'");
  }

} // namespace Titanium {
