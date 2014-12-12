/**
 * TitaniumKit
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/View.hpp"

namespace Titanium { namespace UI {
  
  View::View(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Module(js_context)
    , children__(js_context.CreateArray())
    , backgroundColor__(js_context.CreateString()) {
  }
  
  View::View(const View& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments)
  , children__(rhs.children__)
  , backgroundColor__(rhs.backgroundColor__) {
  }
  
  void View::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_DEBUG("View::add");
    
    // precondition
    auto native_view_ptr = view.GetPrivate<View>();
    TITANIUM_ASSERT(native_view_ptr.get());
    
    const auto view_count = children__.GetPropertyNames().GetCount();
    children__.SetProperty(static_cast<unsigned>(view_count), view);
  }
  
  JSArray View::get_children() const TITANIUM_NOEXCEPT {
    return children__;
  }
  
  JSValue View::get_backgroundColor() const TITANIUM_NOEXCEPT {
    return View::backgroundColor__;
  }
  
  void View::set_backgroundColor(const JSValue& backgroundColor) TITANIUM_NOEXCEPT {
    backgroundColor__ = backgroundColor;
  }

    NativeChildrenList_t View::get_native_children() const TITANIUM_NOEXCEPT{
    NativeChildrenList_t native_children_list;

    const auto child_count = children__.GetPropertyNames().GetCount();
    for (unsigned i = 0; i < child_count; ++i) {
      JSValue child_property = children__.GetProperty(i);

      // preconditions
      TITANIUM_ASSERT(child_property.IsObject());

      JSObject child = child_property;

      // precondition
      auto native_child_ptr = child.GetPrivate<View>();
      TITANIUM_ASSERT(native_child_ptr);

      native_children_list.push_back(native_child_ptr);
    }

    return native_children_list;
  }
  
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void View::JSExportInitialize() {
    JSExport<View>::SetClassVersion(1);
    JSExport<View>::SetParent(JSExport<Module>::Class());
    JSExport<View>::AddFunctionProperty("add", std::mem_fn(&View::addArgumentValidator));
    JSExport<View>::AddValueProperty("children", std::mem_fn(&View::get_children));
    JSExport<View>::AddValueProperty("backgroundColor", std::mem_fn(&View::get_backgroundColor), std::mem_fn(&View::setBackgroundColorArgumentValidator));
  }
  
  JSValue View::addArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsObject());
    JSObject view = _0;
    add(view, this_object);
    return get_context().CreateUndefined();
  }
  
  bool View::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("View::setBackgroundColorArgumentValidator: Unimplemented");
    
    // Base classes must implement this method. This is the minimum
    // functionality that you should perform:
    //
    // TITANIUM_ASSERT(argument.IsString());
    // bool result = false;
    // std::string backgroundColor = static_cast<std::string>(argument);
    // Set the native view's background color to backgroundColor.
    // set_backgroundColor(argument);
    // result = true;
    // return result;

    return false;
  }

}} // namespace Titanium { namespace UI {
