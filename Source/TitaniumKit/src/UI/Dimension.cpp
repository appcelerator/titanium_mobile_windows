/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Dimension.hpp"

namespace Titanium { namespace UI {
  
  Dimension::Dimension(const JSContext& js_context) TITANIUM_NOEXCEPT
  : JSExportObject(js_context)
  , height__(js_context.CreateNumber(0))
  , width__(js_context.CreateNumber(0))
  , x__(js_context.CreateNumber(0))
  , y__(js_context.CreateNumber(0)) {
  }
  
  Dimension::Dimension(const Dimension& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : JSExportObject(rhs, arguments)
  , height__(rhs.height__)
  , width__(rhs.width__)
  , x__(rhs.x__)
  , y__(rhs.y__) {
  }
  
  JSNumber Dimension::get_height() const TITANIUM_NOEXCEPT {
    return height__;
  }
  
  void Dimension::set_height(const JSNumber& height) TITANIUM_NOEXCEPT {
    height__ = height;
  }
  
  JSNumber Dimension::get_width() const TITANIUM_NOEXCEPT {
    return width__;
  }
  
  void Dimension::set_width(const JSNumber& width) TITANIUM_NOEXCEPT {
    width__ = width;
  }
  
  JSNumber Dimension::get_x() const TITANIUM_NOEXCEPT {
    return x__;
  }
  
  void Dimension::set_x(const JSNumber& x) TITANIUM_NOEXCEPT {
    // TODO: Add additional preconsitions to validate x.
    x__ = x;
  }
  
  JSNumber Dimension::get_y() const TITANIUM_NOEXCEPT {
    return y__;
  }
  
  void Dimension::set_y(const JSNumber& y) TITANIUM_NOEXCEPT {
    // TODO: Add additional preconsitions to validate y.
    y__ = y;
  }
  
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void Dimension::JSExportInitialize() {
    JSExport<Dimension>::SetClassVersion(1);
    JSExport<Dimension>::SetParent(JSExport<JSExportObject>::Class());
    JSExport<Dimension>::AddValueProperty("height", std::mem_fn(&Dimension::get_height), std::mem_fn(&Dimension::setHeightArgumentValidator));
    JSExport<Dimension>::AddValueProperty("width" , std::mem_fn(&Dimension::get_width) , std::mem_fn(&Dimension::setWidthArgumentValidator));
    JSExport<Dimension>::AddValueProperty("x"     , std::mem_fn(&Dimension::get_x)     , std::mem_fn(&Dimension::setXArgumentValidator));
    JSExport<Dimension>::AddValueProperty("y"     , std::mem_fn(&Dimension::get_y)     , std::mem_fn(&Dimension::setYArgumentValidator));
  }
  
  bool Dimension::setHeightArgumentValidator(const JSValue& argument) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(argument.IsNumber());
    JSNumber height = argument;
    bool result = false;
    if (static_cast<uint32_t>(height) > 0) {
      set_height(height);
      result = true;
    }
    return result;
  }
  
  bool Dimension::setWidthArgumentValidator(const JSValue& argument) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(argument.IsNumber());
    JSNumber width = argument;
    bool result = false;
    if (static_cast<uint32_t>(width) > 0) {
      set_width(width);
      result = true;
    }
    return result;
  }
  
  bool Dimension::setXArgumentValidator(const JSValue& argument) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(argument.IsNumber());
    JSNumber x = argument;
    bool result = false;
    // TODO: Are there additional preconditions on x?
    set_x(x);
    result = true;
    return result;
  }
  
  bool Dimension::setYArgumentValidator(const JSValue& argument) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(argument.IsNumber());
    JSNumber y = argument;
    bool result = false;
    // TODO: Are there additional preconditions on y?
    set_y(y);
    result = true;
    return result;
  }
  
}} // namespace Titanium { namespace UI {
