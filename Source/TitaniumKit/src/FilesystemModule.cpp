/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/FilesystemModule.hpp"
#include <sstream>

namespace Titanium {

  FilesystemModule::FilesystemModule(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Module(js_context)
    , mode_read__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::READ)))
    , mode_write__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::WRITE)))
    , mode_append__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::APPEND)))
  {
  }

  FilesystemModule::FilesystemModule(const FilesystemModule& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Module(rhs, arguments)
    , mode_read__(rhs.mode_read__)
    , mode_write__(rhs.mode_write__)
    , mode_append__(rhs.mode_append__)
  {
  }

  JSValue FilesystemModule::MODE_READ() const TITANIUM_NOEXCEPT {
    return mode_read__;
  }
    JSValue FilesystemModule::MODE_WRITE() const TITANIUM_NOEXCEPT {
    return mode_write__;
  }
    JSValue FilesystemModule::MODE_APPEND() const TITANIUM_NOEXCEPT {
    return mode_append__;
  }

    std::string FilesystemModule::separator() const TITANIUM_NOEXCEPT {
    return "/";
  }

  JSValue FilesystemModule::getFile(const std::string& path) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_DEBUG("Filesystem::getFile: ", path);

    JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
    TITANIUM_ASSERT(Titanium_property.IsObject()); // precondition
    JSObject Titanium = Titanium_property;

    JSValue FS_property = Titanium.GetProperty("Filesystem");
    TITANIUM_ASSERT(FS_property.IsObject()); // precondition
    JSObject FS = FS_property;

    JSValue File_property = FS.GetProperty("File");
    TITANIUM_ASSERT(File_property.IsObject()); // precondition
    JSObject File = File_property;

    return File.CallAsConstructor(path);
  }

  JSValue FilesystemModule::createTempDirectory() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::createTempDirectory: Unimplemented");
    return get_context().CreateNull();
  }
  JSValue FilesystemModule::createTempFile() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::createTempFile: Unimplemented");
    return get_context().CreateNull();
  }
  bool FilesystemModule::isExternalStoragePresent() TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::isExternalStoragePresent: Unimplemented");
    return false;
  }
  JSValue FilesystemModule::openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::openStream: Unimplemented");
    return get_context().CreateNull();
  }
  std::string FilesystemModule::applicationCacheDirectory() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::applicationCacheDirectory: Unimplemented");
    return "";
  }
  std::string FilesystemModule::applicationDataDirectory() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::applicationDataDirectory: Unimplemented");
    return "";
  }
  std::string FilesystemModule::applicationDirectory() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::applicationDirectory: Unimplemented");
    return "";
  }
  std::string FilesystemModule::applicationSupportDirectory() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::applicationSupportDirectory: Unimplemented");
    return "";
  }
  std::string FilesystemModule::externalStorageDirectory() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::externalStorageDirectory: Unimplemented");
    return "";
  }
  std::string FilesystemModule::lineEnding() const TITANIUM_NOEXCEPT {
    return "\n";
  }
  std::string FilesystemModule::resourcesDirectory() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::resourcesDirectory: Unimplemented");
    return "";
  }
  std::string FilesystemModule::tempDirectory() const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("File::tempDirectory: Unimplemented");
    return "";
  }

  void FilesystemModule::JSExportInitialize() {
    JSExport<FilesystemModule>::SetClassVersion(1);
    JSExport<FilesystemModule>::SetParent(JSExport<Module>::Class());
    JSExport<FilesystemModule>::AddFunctionProperty("getFile", std::mem_fn(&FilesystemModule::getFile_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("createTempDirectory", std::mem_fn(&FilesystemModule::createTempDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("createTempFile", std::mem_fn(&FilesystemModule::createTempFile_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("isExternalStoragePresent", std::mem_fn(&FilesystemModule::isExternalStoragePresent_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("openStream", std::mem_fn(&FilesystemModule::openStream_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("MODE_READ", std::mem_fn(&FilesystemModule::MODE_READ));
    JSExport<FilesystemModule>::AddValueProperty("MODE_WRITE", std::mem_fn(&FilesystemModule::MODE_WRITE));
    JSExport<FilesystemModule>::AddValueProperty("MODE_APPEND", std::mem_fn(&FilesystemModule::MODE_APPEND));
    JSExport<FilesystemModule>::AddValueProperty("separator", std::mem_fn(&FilesystemModule::separator_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("lineEnding", std::mem_fn(&FilesystemModule::lineEnding_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("applicationCacheDirectory", std::mem_fn(&FilesystemModule::applicationCacheDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("applicationDataDirectory", std::mem_fn(&FilesystemModule::applicationDataDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("applicationDirectory", std::mem_fn(&FilesystemModule::applicationDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("applicationSupportDirectory", std::mem_fn(&FilesystemModule::applicationSupportDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("externalStorageDirectory", std::mem_fn(&FilesystemModule::externalStorageDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("resourcesDirectory", std::mem_fn(&FilesystemModule::resourcesDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddValueProperty("tempDirectory", std::mem_fn(&FilesystemModule::tempDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getSeparator", std::mem_fn(&FilesystemModule::getSeparator_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getLineEnding", std::mem_fn(&FilesystemModule::getLineEnding_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getApplicationCacheDirectory", std::mem_fn(&FilesystemModule::getApplicationCacheDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getApplicationDataDirectory", std::mem_fn(&FilesystemModule::getApplicationDataDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getApplicationDirectory", std::mem_fn(&FilesystemModule::getApplicationDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getApplicationSupportDirectory", std::mem_fn(&FilesystemModule::getApplicationSupportDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getExternalStorageDirectory", std::mem_fn(&FilesystemModule::getExternalStorageDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getResourcesDirectory", std::mem_fn(&FilesystemModule::getResourcesDirectory_ArgumentValidator));
    JSExport<FilesystemModule>::AddFunctionProperty("getTempDirectory", std::mem_fn(&FilesystemModule::getTempDirectory_ArgumentValidator));

  }

  JSValue FilesystemModule::getFile_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
    TITANIUM_ASSERT(Titanium_property.IsObject()); // precondition
    JSObject Titanium = Titanium_property;

    JSValue FS_property = Titanium.GetProperty("Filesystem");
    TITANIUM_ASSERT(FS_property.IsObject()); // precondition
    JSObject FS = FS_property;

    JSValue sep_property = FS.GetProperty("separator");
    TITANIUM_ASSERT(sep_property.IsString()); // precondition
    std::string separator = static_cast<std::string>(sep_property);

    // join paths with separator
    std::ostringstream oss;
    const auto size = arguments.size();
    for (unsigned i = 0; i < size; i++) {
      oss << static_cast<std::string>(arguments.at(i));
      if (i + 1 < size) {
        oss << separator;
      }
    }
    return getFile(oss.str());
  }

  JSValue FilesystemModule::createTempDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT {
    return createTempDirectory();
  }
  JSValue FilesystemModule::createTempFile_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT {
    return createTempFile();
  }
  JSValue FilesystemModule::isExternalStoragePresent_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(isExternalStoragePresent());
  }
  JSValue FilesystemModule::openStream_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT {
    if (arguments.size() < 2) {
      return get_context().CreateUndefined();
    }
    const auto _0 = arguments.at(0);
    const auto _1 = arguments.at(1);

    TITANIUM_ASSERT(_0.IsNumber());
    TITANIUM_ASSERT(_1.IsString());

    const auto modes = Titanium::Filesystem::Constants::to_MODE(static_cast<std::underlying_type<Titanium::Filesystem::MODE>::type>(_0));
    const std::string path = static_cast<std::string>(_1);
    return openStream(modes, path);
  }

  JSValue FilesystemModule::getSeparator_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return separator_ArgumentValidator();
  }
  JSValue FilesystemModule::getApplicationCacheDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return applicationCacheDirectory_ArgumentValidator();
  }
  JSValue FilesystemModule::getApplicationDataDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return applicationDataDirectory_ArgumentValidator();
  }
  JSValue FilesystemModule::getApplicationDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return applicationDirectory_ArgumentValidator();
  }
  JSValue FilesystemModule::getApplicationSupportDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return applicationSupportDirectory_ArgumentValidator();
  }
  JSValue FilesystemModule::getExternalStorageDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return externalStorageDirectory_ArgumentValidator();
  }
  JSValue FilesystemModule::getLineEnding_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return lineEnding_ArgumentValidator();
  }
  JSValue FilesystemModule::getResourcesDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return resourcesDirectory_ArgumentValidator();
  }
  JSValue FilesystemModule::getTempDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return tempDirectory_ArgumentValidator();
  }

  JSValue FilesystemModule::separator_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(separator());
  }
  JSValue FilesystemModule::applicationCacheDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(applicationCacheDirectory());
  }
  JSValue FilesystemModule::applicationDataDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(applicationDataDirectory());
  }
  JSValue FilesystemModule::applicationDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(applicationDirectory());
  }
  JSValue FilesystemModule::applicationSupportDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(applicationSupportDirectory());
  }
  JSValue FilesystemModule::externalStorageDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(externalStorageDirectory());
  }
  JSValue FilesystemModule::lineEnding_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(lineEnding());
  }
  JSValue FilesystemModule::resourcesDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(resourcesDirectory());
  }
  JSValue FilesystemModule::tempDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(tempDirectory());
  }

} // namespace Titanium {
