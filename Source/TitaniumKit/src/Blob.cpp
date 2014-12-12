/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Blob.hpp"
#include <type_traits>

namespace Titanium {
  
  Blob::Blob(const JSContext& js_context) TITANIUM_NOEXCEPT
  : Module(js_context) {
  }
  
  Blob::Blob(const Blob& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments) {
  }
  
  void Blob::JSExportInitialize() {
    JSExport<Blob>::SetClassVersion(1);
    JSExport<Blob>::SetParent(JSExport<Module>::Class());
    JSExport<Blob>::AddValueProperty("length", std::mem_fn(&Blob::get_length_ArgumentValidator));
    JSExport<Blob>::AddValueProperty("file", std::mem_fn(&Blob::get_file_ArgumentValidator));
    JSExport<Blob>::AddValueProperty("height", std::mem_fn(&Blob::get_height_ArgumentValidator));
    JSExport<Blob>::AddValueProperty("mimeType", std::mem_fn(&Blob::get_mimeType_ArgumentValidator));
    JSExport<Blob>::AddValueProperty("nativePath", std::mem_fn(&Blob::get_nativePath_ArgumentValidator));
    JSExport<Blob>::AddValueProperty("size", std::mem_fn(&Blob::get_size_ArgumentValidator));
    JSExport<Blob>::AddValueProperty("text", std::mem_fn(&Blob::get_text_ArgumentValidator));
    JSExport<Blob>::AddValueProperty("width", std::mem_fn(&Blob::get_width_ArgumentValidator));
    
    JSExport<Blob>::AddFunctionProperty("getLength", std::mem_fn(&Blob::getLength_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("getFile", std::mem_fn(&Blob::getFile_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("getHeight", std::mem_fn(&Blob::getHeight_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("getMimeType", std::mem_fn(&Blob::getMimeType_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("getNativePath", std::mem_fn(&Blob::getNativePath_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("getSize", std::mem_fn(&Blob::getSize_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("getText", std::mem_fn(&Blob::getText_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("getWidth", std::mem_fn(&Blob::getWidth_ArgumentValidator));
    
    JSExport<Blob>::AddFunctionProperty("append", std::mem_fn(&Blob::append_ArgumentValidator));
    JSExport<Blob>::AddFunctionProperty("toString", std::mem_fn(&Blob::toString_ArgumentValidator));
  }
  
  unsigned Blob::get_length() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::get_length: Unimplemented");
    return 0;
  }
  
  JSObject Blob::get_file() const TITANIUM_NOEXCEPT {
    JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
    TITANIUM_ASSERT(Titanium_property.IsObject()); // precondition
    JSObject Titanium = Titanium_property;
    
    JSValue Filesystem_property = Titanium.GetProperty("Filesystem");
    TITANIUM_ASSERT(Filesystem_property.IsObject()); // precondition
    JSObject Filesystem = Filesystem_property;
    
    JSValue File_property = Filesystem.GetProperty("File");
    TITANIUM_ASSERT(File_property.IsObject()); // precondition
    JSObject File = File_property;
    
    return File.CallAsConstructor(get_nativePath());
  }
  
  unsigned Blob::get_height() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::get_height: Unimplemented");
    return 0;
  }
  
  std::string Blob::get_mimeType() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::get_mimeType: Unimplemented");
    return "";
  }
  
  std::string Blob::get_nativePath() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::get_nativePath: Unimplemented");
    return "";
  }
  
  unsigned Blob::get_size() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::get_size: Unimplemented");
    return 0;
  }
  
  std::string Blob::get_text() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::get_text: Unimplemented");
    return "";
  }
  
  unsigned Blob::get_width() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::get_width: Unimplemented");
    return 0;
  }
  
  void Blob::append(std::shared_ptr<Blob>&) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("Blob::append: Unimplemented");
  }
  
  JSValue Blob::get_length_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(get_length());
  }
  
  JSValue Blob::get_file_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_file();
  }
  
  JSValue Blob::get_height_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(get_height());
  }
  
  JSValue Blob::get_mimeType_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(get_mimeType());
  }
  
  JSValue Blob::get_nativePath_ArgumentValidator() const TITANIUM_NOEXCEPT {
    const auto path = get_nativePath();
    if (path.size() > 0) {
      return get_context().CreateString(path);
    } else {
      return get_context().CreateNull();
    }
  }
  
  JSValue Blob::get_size_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(get_size());
  }
  
  JSValue Blob::get_text_ArgumentValidator() const TITANIUM_NOEXCEPT {
    const auto text = get_text();
    if (text.size() > 0) {
      return get_context().CreateString(text);
    } else {
      return get_context().CreateNull();
    }
  }
  
  JSValue Blob::get_width_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(get_width());
  }

  JSValue Blob::append_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() < 1) {
      return get_context().CreateUndefined();
    }
    const auto _0 = arguments.at(0);
    if (!_0.IsObject()) {
      return get_context().CreateUndefined();
    }
    const JSObject blob = _0;
    auto blob_ptr = blob.GetPrivate<Blob>();
    TITANIUM_ASSERT(blob_ptr);
    append(blob_ptr);

    return get_context().CreateUndefined();
  }
  
  JSValue Blob::getFile_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_file_ArgumentValidator();
  }
  
  JSValue Blob::getHeight_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_height_ArgumentValidator();
  }
  
  JSValue Blob::getLength_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_length_ArgumentValidator();
  }
  
  JSValue Blob::getMimeType_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_mimeType_ArgumentValidator();
  }
  
  JSValue Blob::getNativePath_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_nativePath_ArgumentValidator();
  }
  
  JSValue Blob::getSize_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_size_ArgumentValidator();
  }
  
  JSValue Blob::getText_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_text_ArgumentValidator();
  }
  
  JSValue Blob::getWidth_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_width_ArgumentValidator();
  }
  
  JSValue Blob::toString_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_text_ArgumentValidator();
  }
  
} // namespace Titanium {
