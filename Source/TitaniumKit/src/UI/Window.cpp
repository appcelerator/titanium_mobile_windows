/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Window.hpp"

namespace Titanium { namespace UI {
  
  Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
  : View(js_context)
  , extendEdges__({EXTEND_EDGE::NONE}) {
 }
  
  Window::Window(const Window& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : View(rhs, arguments)
  , extendEdges__(rhs.extendEdges__) {
  }
  
  void Window::open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Window::open: Unimplemented");
  }
  
  std::unordered_set<EXTEND_EDGE> Window::get_extendEdges() const  TITANIUM_NOEXCEPT {
    return extendEdges__;
  }
  
  void Window::set_extendEdges(const std::unordered_set<EXTEND_EDGE>& autoLink) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Window::set_extendEdges: Unimplemented");
  }

  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void Window::JSExportInitialize() {
    JSExport<Window>::SetClassVersion(1);
    JSExport<Window>::SetParent(JSExport<View>::Class());
    JSExport<Window>::AddFunctionProperty("open" , std::mem_fn(&Window::openArgumentValidator));
  }
  
  JSValue Window::openArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    JSObject params = get_context().CreateObject();
    if (arguments.size() >= 1) {
      const auto _0 = arguments.at(0);
      TITANIUM_ASSERT(_0.IsObject());
      params = _0;
    }
    open(params, this_object);
    return get_context().CreateUndefined();
  }
  
  JSValue Window::getExtendEdgesArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(Constants::to_underlying_type(extendEdges__));
  }
  
  bool Window::setExtendEdgesArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsNumber());
    extendEdges__ = Constants::to_EXTEND_EDGE(static_cast<std::underlying_type<EXTEND_EDGE>::type>(argument));
    set_extendEdges(extendEdges__);
    return true;
  }
  
}} // namespace Titanium { namespace UI {
