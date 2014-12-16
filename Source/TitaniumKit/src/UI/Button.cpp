/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Button.hpp"

namespace Titanium { namespace UI {
  
  Button::Button(const JSContext& js_context) TITANIUM_NOEXCEPT
    : View(js_context)
    , title__(js_context.CreateString()) {
  }
  
  Button::Button(const Button& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : View(rhs, arguments)
    , title__(rhs.title__) {
  }
  
  JSValue Button::get_title() const TITANIUM_NOEXCEPT {
    return title__;
  }
  
  void Button::set_title(const JSValue& title) TITANIUM_NOEXCEPT {
    title__ = title;
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void Button::JSExportInitialize() {
    JSExport<Button>::SetClassVersion(1);
    JSExport<Button>::SetParent(JSExport<View>::Class());
    JSExport<Button>::AddValueProperty("title", std::mem_fn(&Button::get_title), std::mem_fn(&Button::setTitleArgumentValidator));
  }
  
  bool Button::setTitleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Button::setTitleArgumentValidator: Unimplemented");

    // Base classes must implement this method. This is the minimum
    // functionality that you should perform:
    //
    // TITANIUM_ASSERT(argument.IsString());
    // set_title(argument);
    // return true;

    return false;
  }
  
}} // namespace Titanium { namespace UI {
