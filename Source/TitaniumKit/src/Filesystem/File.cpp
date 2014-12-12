/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Filesystem/File.hpp"
#include <type_traits>

namespace Titanium { namespace Filesystem {
  
  File::File(const JSContext& js_context) TITANIUM_NOEXCEPT
  : Module(js_context) {
  }
  
  File::File(const File& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments) {
  }
  
  void File::JSExportInitialize() {
    JSExport<File>::SetClassVersion(1);
    JSExport<File>::SetParent(JSExport<Module>::Class());
    JSExport<File>::AddValueProperty("executable", std::mem_fn(&File::get_executable_ArgumentValidator));
    JSExport<File>::AddValueProperty("hidden", std::mem_fn(&File::get_hidden_ArgumentValidator));
    JSExport<File>::AddValueProperty("name", std::mem_fn(&File::get_name_ArgumentValidator));
    JSExport<File>::AddValueProperty("nativePath", std::mem_fn(&File::get_nativePath_ArgumentValidator));
    JSExport<File>::AddValueProperty("parent", std::mem_fn(&File::get_parent_ArgumentValidator));
    JSExport<File>::AddValueProperty("readonly", std::mem_fn(&File::get_readonly_ArgumentValidator));
    JSExport<File>::AddValueProperty("remoteBackup", std::mem_fn(&File::get_remoteBackup_ArgumentValidator));
    JSExport<File>::AddValueProperty("size", std::mem_fn(&File::get_size_ArgumentValidator));
    JSExport<File>::AddValueProperty("symbolicLink", std::mem_fn(&File::get_symbolicLink_ArgumentValidator));
    JSExport<File>::AddValueProperty("writable", std::mem_fn(&File::get_writable_ArgumentValidator));
    
    JSExport<File>::AddFunctionProperty("getExecutable", std::mem_fn(&File::getExecutable_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getHidden", std::mem_fn(&File::getHidden_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getName", std::mem_fn(&File::getName_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getNativePath", std::mem_fn(&File::getNativePath_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getParent", std::mem_fn(&File::getParent_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getReadonly", std::mem_fn(&File::getReadonly_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getRemoteBackup", std::mem_fn(&File::getRemoteBackup_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getSize", std::mem_fn(&File::getSize_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getSymbolicLink", std::mem_fn(&File::getSymbolicLink_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getWritable", std::mem_fn(&File::getWritable_ArgumentValidator));

    JSExport<File>::AddFunctionProperty("append", std::mem_fn(&File::append_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("copy", std::mem_fn(&File::copy_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("createDirectory", std::mem_fn(&File::createDirectory_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("createFile", std::mem_fn(&File::createFile_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("createTimestamp", std::mem_fn(&File::createTimestamp_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("deleteDirectory", std::mem_fn(&File::deleteDirectory_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("deleteFile", std::mem_fn(&File::deleteFile_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("exists", std::mem_fn(&File::exists_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("extension", std::mem_fn(&File::extension_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("getDirectoryListing", std::mem_fn(&File::getDirectoryListing_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("isDirectory", std::mem_fn(&File::isDirectory_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("isFile", std::mem_fn(&File::isFile_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("modificationTimestamp", std::mem_fn(&File::modificationTimestamp_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("move", std::mem_fn(&File::move_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("open", std::mem_fn(&File::open_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("read", std::mem_fn(&File::read_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("rename", std::mem_fn(&File::rename_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("resolve", std::mem_fn(&File::resolve_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("spaceAvailable", std::mem_fn(&File::spaceAvailable_ArgumentValidator));
    JSExport<File>::AddFunctionProperty("write", std::mem_fn(&File::write_ArgumentValidator));
  }
  
  bool File::get_executable() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_executable: Unimplemented");
    return false;
  }
  bool File::get_hidden() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_hidden: Unimplemented");
    return false;
  }
  std::string File::get_name() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_name: Unimplemented");
    return "";
  }
  std::string File::get_nativePath() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_nativePath: Unimplemented");
    return "";
  }
  JSValue File::get_parent() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_parent: Unimplemented");
    return get_context().CreateNull();
  }
  bool File::get_readonly() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_readonly: Unimplemented");
    return false;
  }
  bool File::get_remoteBackup() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_remoteBackup: Unimplemented");
    return false;
  }
  bool File::get_symbolicLink() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_symbolicLink: Unimplemented");
    return false;
  }
  bool File::get_writable() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_writable: Unimplemented");
    return false;
  }
  unsigned File::get_size() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::get_size: Unimplemented");
    return 0;
  }
  
  bool File::append(const JSValue& data) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::append: Unimplemented");
    return false;
  }
  bool File::copy(const std::string& dest) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::copy: Unimplemented");
    return false;
  }
  bool File::createDirectory() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::createDirectory: Unimplemented");
    return false;
  }
  bool File::createFile() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::createFile: Unimplemented");
    return false;
  }
  unsigned File::createTimestamp() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::createTimestamp: Unimplemented");
    return 0;
  }
  bool File::deleteDirectory(bool recursive) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::deleteDirectory: Unimplemented");
    return false;
  }
  bool File::deleteFile() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::deleteFile: Unimplemented");
    return false;
  }
  bool File::exists() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::exists: Unimplemented");
    return false;
  }
  std::string File::extension() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::extension: Unimplemented");
    return "";
  }
  std::vector<JSValue> File::getDirectoryListing() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::getDirectoryListing: Unimplemented");
    std::vector<JSValue> list;
    return list;
  }
  bool File::isDirectory() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::isDirectory: Unimplemented");
    return false;
  }
  bool File::isFile() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::isFile: Unimplemented");
    return false;
  }
  unsigned File::modificationTimestamp() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::modificationTimestamp: Unimplemented");
    return 0;
  }
  bool File::move(const std::string& newpath) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::move: Unimplemented");
    return false;
  }
  JSValue File::open(const std::unordered_set<MODE>&) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::open: Unimplemented");
    return get_context().CreateNull();
  }
  JSValue File::read() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::read: Unimplemented");
    return get_context().CreateNull();
  }
  bool File::rename(const std::string& newname) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::rename: Unimplemented");
    return false;
  }
  std::string File::resolve() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::resolve: Unimplemented");
    return "";
  }
  unsigned File::spaceAvailable() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::spaceAvailable: Unimplemented");
    return false;
  }
  bool File::write(const JSValue& data, bool append) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::write: Unimplemented");
    return false;
  }
  
  JSValue File::get_executable_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_executable());
  }
  JSValue File::get_hidden_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_hidden());
  }
  JSValue File::get_name_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(get_name());
  }
  JSValue File::get_nativePath_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(get_nativePath());
  }
  JSValue File::get_parent_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_parent();
  }
  JSValue File::get_readonly_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_readonly());
  }
  JSValue File::get_remoteBackup_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_remoteBackup());
  }
  JSValue File::get_symbolicLink_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_symbolicLink());
  }
  JSValue File::get_writable_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(get_writable());
  }
  JSValue File::get_size_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(get_size());
  }
  JSValue File::getSize_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_size_ArgumentValidator();
  }
  
  JSValue File::getExecutable_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_executable_ArgumentValidator();
  }
  JSValue File::getHidden_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_hidden_ArgumentValidator();
  }
  JSValue File::getName_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_name_ArgumentValidator();
  }
  JSValue File::getNativePath_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_nativePath_ArgumentValidator();
  }
  JSValue File::getParent_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_parent_ArgumentValidator();
  }
  JSValue File::getReadonly_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_readonly_ArgumentValidator();
  }
  JSValue File::getRemoteBackup_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_remoteBackup_ArgumentValidator();
  }
  JSValue File::getSymbolicLink_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_symbolicLink_ArgumentValidator();
  }
  JSValue File::getWritable_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_writable_ArgumentValidator();
  }

  JSValue File::append_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() == 0) {
      return get_context().CreateUndefined();
    }
    return get_context().CreateBoolean(append(arguments.at(0)));
  }
  JSValue File::copy_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() == 0) {
      return get_context().CreateUndefined();
    }
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    const auto destinationPath = static_cast<std::string>(_0);
    return get_context().CreateBoolean(copy(destinationPath));
  }
  JSValue File::createDirectory_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(createDirectory());
  }
  JSValue File::createFile_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(createFile());
  }
  JSValue File::createTimestamp_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(createTimestamp());
  }
  JSValue File::deleteDirectory_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() == 0) {
      return get_context().CreateUndefined();
    }
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsBoolean());
    const auto recursive = static_cast<bool>(_0);
    return get_context().CreateBoolean(deleteDirectory(recursive));
  }
  JSValue File::deleteFile_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(deleteFile());
  }
  JSValue File::exists_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(exists());
  }
  JSValue File::extension_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateString(extension());
  }
  JSValue File::getDirectoryListing_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateArray(getDirectoryListing());
  }
  JSValue File::isDirectory_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(isDirectory());
  }
  JSValue File::isFile_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(isFile());
  }
  JSValue File::modificationTimestamp_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(modificationTimestamp());
  }
  JSValue File::move_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() == 0) {
      return get_context().CreateUndefined();
    }
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    const auto newpath = static_cast<std::string>(_0);
    return get_context().CreateBoolean(move(newpath));
  }
  JSValue File::open_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() == 0) {
      return get_context().CreateUndefined();
    }
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsNumber());
    
    return open(Constants::to_MODE(static_cast<std::underlying_type<MODE>::type>(_0)));
  }
  JSValue File::read_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return read();
  }
  JSValue File::rename_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() == 0) {
      return get_context().CreateUndefined();
    }
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    const auto newname = static_cast<std::string>(_0);
    return get_context().CreateBoolean(rename(newname));
  }
  JSValue File::resolve_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateString(resolve());
  }
  JSValue File::spaceAvailable_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(spaceAvailable());
  }
  JSValue File::write_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() < 2) {
      return get_context().CreateUndefined();
    }
    
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsObject());
    JSObject data = _0;
    
    const auto _1 = arguments.at(1);
    TITANIUM_ASSERT(_1.IsBoolean());
    const auto append = static_cast<bool>(_1);
    
    return get_context().CreateBoolean(write(data, append));
  }

}} // namespace Titanium { namespace Filesystem {
