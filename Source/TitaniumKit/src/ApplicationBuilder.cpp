/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/ApplicationBuilder.hpp"
#include "Titanium/API.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/Platform.hpp"
#include "Titanium/Accelerometer.hpp"
#include "Titanium/Gesture.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/FilesystemModule.hpp"
#include "Titanium/Filesystem/File.hpp"

namespace Titanium {
  
  ApplicationBuilder::ApplicationBuilder(const JSClassPtr_t& global_object_class_ptr) TITANIUM_NOEXCEPT
  : global_object_class_ptr__(global_object_class_ptr)
  , js_context__(js_context_group__.CreateContext(*global_object_class_ptr)) {
  }
  
  Application ApplicationBuilder::build() {
    
    if (!api_class_ptr__) {
      api_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::API>::Class());
    }
    
    if (!view_class_ptr__) {
      view_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::UI::View>::Class());
    }

    if (!window_class_ptr__) {
      window_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::UI::Window>::Class());
    }
    
    if (!button_class_ptr__) {
      button_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::UI::Button>::Class());
    }
      
    if (!platform_class_ptr__) {
      platform_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::Platform>::Class());
    }
    
    if (!accelerometer_class_ptr__) {
      accelerometer_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::Accelerometer>::Class());
    }
    
    if (!gesture_class_ptr__) {
      gesture_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::Gesture>::Class());
    }
    
    if (!blob_class_ptr__) {
      blob_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::Blob>::Class());
    }
    
    if (!file_class_ptr__) {
      file_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::Filesystem::File>::Class());
    }

    if (!filesystem_class_ptr__) {
      filesystem_class_ptr__ = std::make_shared<JSClass>(JSExport<Titanium::FilesystemModule>::Class());
    }

    JSObject global_object = js_context__.get_global_object();
    JSObject titanium      = js_context__.CreateObject();
    global_object.SetProperty("Titanium", titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
    global_object.SetProperty("Ti"      , titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

    JSObject api = js_context__.CreateObject(*api_class_ptr__);
    titanium.SetProperty("API", api, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

    JSObject ui = js_context__.CreateObject(JSExport<Titanium::UIModule>::Class());
    titanium.SetProperty("UI" , ui , {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
    ui.SetProperty("View"  , js_context__.CreateObject(*view_class_ptr__));
    ui.SetProperty("Window", js_context__.CreateObject(*window_class_ptr__));
    ui.SetProperty("Button", js_context__.CreateObject(*button_class_ptr__));
      
    JSObject platform = js_context__.CreateObject(*platform_class_ptr__);
    titanium.SetProperty("Platform", platform, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
    
    JSObject accelerometer = js_context__.CreateObject(*accelerometer_class_ptr__);
    titanium.SetProperty("Accelerometer", accelerometer, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
    
    JSObject gesture = js_context__.CreateObject(*gesture_class_ptr__);
    titanium.SetProperty("Gesture", gesture, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
    
    JSObject blob = js_context__.CreateObject(*blob_class_ptr__);
    titanium.SetProperty("Blob", blob, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
    
    JSObject fs = js_context__.CreateObject(*filesystem_class_ptr__);
    titanium.SetProperty("Filesystem" , fs , {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
    fs.SetProperty("File"  , js_context__.CreateObject(*file_class_ptr__));
    
    return Application(*this);
  }
  
  JSClassPtr_t ApplicationBuilder::APIClass() const TITANIUM_NOEXCEPT {
    return api_class_ptr__;
  }
  
  ApplicationBuilder& ApplicationBuilder::APIClass(const JSClassPtr_t& api_class_ptr) TITANIUM_NOEXCEPT {
    api_class_ptr__ = api_class_ptr;
    return *this;
  }
  
  JSClassPtr_t ApplicationBuilder::ViewClass() const TITANIUM_NOEXCEPT {
    return view_class_ptr__;
  }
  
  ApplicationBuilder& ApplicationBuilder::ViewClass(const JSClassPtr_t& view_class_ptr) TITANIUM_NOEXCEPT {
    view_class_ptr__ = view_class_ptr;
    return *this;
  }
  
  JSClassPtr_t ApplicationBuilder::WindowClass() const TITANIUM_NOEXCEPT {
    return window_class_ptr__;
  }
  
  ApplicationBuilder& ApplicationBuilder::WindowClass(const JSClassPtr_t& window_class_ptr) TITANIUM_NOEXCEPT {
    window_class_ptr__ = window_class_ptr;
    return *this;
  }

  JSClassPtr_t ApplicationBuilder::ButtonClass() const TITANIUM_NOEXCEPT {
    return button_class_ptr__;
  }
  
  ApplicationBuilder& ApplicationBuilder::ButtonClass(const JSClassPtr_t& button_class_ptr) TITANIUM_NOEXCEPT {
    button_class_ptr__ = button_class_ptr;
    return *this;
  }
    
  JSClassPtr_t ApplicationBuilder::PlatformClass() const TITANIUM_NOEXCEPT {
    return platform_class_ptr__;
  }
  ApplicationBuilder& ApplicationBuilder::PlatformClass(const JSClassPtr_t& platform_class_ptr) TITANIUM_NOEXCEPT {
    platform_class_ptr__ = platform_class_ptr;
    return *this;
  }
  
  JSClassPtr_t ApplicationBuilder::AccelerometerClass() const TITANIUM_NOEXCEPT {
    return accelerometer_class_ptr__;
  }
  ApplicationBuilder& ApplicationBuilder::AccelerometerClass(const JSClassPtr_t& accelerometer_class_ptr) TITANIUM_NOEXCEPT {
    accelerometer_class_ptr__ = accelerometer_class_ptr;
    return *this;
  }
  
  JSClassPtr_t ApplicationBuilder::GestureClass() const TITANIUM_NOEXCEPT {
    return gesture_class_ptr__;
  }
  ApplicationBuilder& ApplicationBuilder::GestureClass(const JSClassPtr_t& gesture_class_ptr) TITANIUM_NOEXCEPT {
    gesture_class_ptr__ = gesture_class_ptr;
    return *this;
  }
  
  JSClassPtr_t ApplicationBuilder::BlobClass() const TITANIUM_NOEXCEPT {
    return blob_class_ptr__;
  }
  ApplicationBuilder& ApplicationBuilder::BlobClass(const JSClassPtr_t& blob_class_ptr) TITANIUM_NOEXCEPT {
    blob_class_ptr__ = blob_class_ptr;
    return *this;
  }
  
  JSClassPtr_t ApplicationBuilder::FileClass() const TITANIUM_NOEXCEPT {
    return file_class_ptr__;
  }
  ApplicationBuilder& ApplicationBuilder::FileClass(const JSClassPtr_t& file_class_ptr) TITANIUM_NOEXCEPT {
    file_class_ptr__ = file_class_ptr;
    return *this;
  }

  JSClassPtr_t ApplicationBuilder::FilesystemClass() const TITANIUM_NOEXCEPT {
    return filesystem_class_ptr__;
  }
    ApplicationBuilder& ApplicationBuilder::FilesystemClass(const JSClassPtr_t& filesystem_class_ptr) TITANIUM_NOEXCEPT {
    filesystem_class_ptr__ = filesystem_class_ptr;
    return *this;
  }

} // namespace Titanium {
