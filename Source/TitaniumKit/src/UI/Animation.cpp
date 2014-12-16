/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Animation.hpp"
#include <type_traits>

namespace Titanium { namespace UI {
  
  Animation::Animation(const JSContext& js_context) TITANIUM_NOEXCEPT
  : Module(js_context)
  , curve__(ANIMATION_CURVE::LINEAR) {
  }
  
  Animation::Animation(const Animation& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments)
  , curve__(rhs.curve__) {
  }
  
  ANIMATION_CURVE Animation::get_curve() const TITANIUM_NOEXCEPT {
    return curve__;
  }
  
  void Animation::set_curve(const ANIMATION_CURVE& curve) TITANIUM_NOEXCEPT {
    curve__ = curve;
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void Animation::JSExportInitialize() {
    JSExport<Animation>::SetClassVersion(1);
    JSExport<Animation>::SetParent(JSExport<Module>::Class());
    JSExport<Animation>::AddValueProperty("curve", std::mem_fn(&Animation::getCurveArgumentValidator), std::mem_fn(&Animation::setCurveArgumentValidator));
  }
  
  JSValue Animation::getCurveArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(static_cast<std::underlying_type<ANIMATION_CURVE>::type>(curve__));
  }
  
  bool Animation::setCurveArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Animation::setCurveArgumentValidator: Unimplemented");
    TITANIUM_ASSERT(argument.IsNumber());
    curve__ = Constants::to_ANIMATION_CURVE(static_cast<std::underlying_type<ANIMATION_CURVE>::type>(argument));
    
    TITANIUM_LOG_DEBUG("Animation::setCurveArgumentValidator: set_curve(", Constants::to_string(curve__), ")");
    set_curve(curve__);
    
    return true;
  }
  
}} // namespace Titanium { namespace UI {
