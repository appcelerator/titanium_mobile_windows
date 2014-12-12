/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeFileExample.hpp"
#include <iostream>

NativeFileExample::NativeFileExample(const JSContext& js_context) TITANIUM_NOEXCEPT
: Titanium::Filesystem::File(js_context) {
}

NativeFileExample::NativeFileExample(const NativeFileExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
: Titanium::Filesystem::File(rhs, arguments) {
}

void NativeFileExample::JSExportInitialize() {
  JSExport<NativeFileExample>::SetClassVersion(1);
  JSExport<NativeFileExample>::SetParent(JSExport<Titanium::Filesystem::File>::Class());
}

bool NativeFileExample::get_executable() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_executable");
  return false;
}
bool NativeFileExample::get_hidden() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_hidden");
  return false;
}
std::string NativeFileExample::get_name() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_name");
  return "";
}
std::string NativeFileExample::get_nativePath() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_nativePath");
  return "";
}
JSValue NativeFileExample::get_parent() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_parent");
  return get_context().CreateNull();
}
bool NativeFileExample::get_readonly() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_readonly");
  return false;
}
bool NativeFileExample::get_remoteBackup() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_remoteBackup");
  return false;
}
bool NativeFileExample::get_symbolicLink() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_symbolicLink");
  return false;
}
bool NativeFileExample::get_writable() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_writable");
  return false;
}
unsigned NativeFileExample::get_size() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::get_size");
  return 0;
}

bool NativeFileExample::append(const JSValue& data) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::append");
  return false;
}
bool NativeFileExample::copy(const std::string& dest) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::copy");
  return false;
}
bool NativeFileExample::createDirectory() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::createDirectory");
  return false;
}
bool NativeFileExample::createFile() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::createFile");
  return false;
}
unsigned NativeFileExample::createTimestamp() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::createTimestamp");
  return 0;
}
bool NativeFileExample::deleteDirectory(bool recursive) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::deleteDirectory");
  return false;
}
bool NativeFileExample::deleteFile() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::deleteFile");
  return false;
}
bool NativeFileExample::exists() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::exists");
  return false;
}
std::string NativeFileExample::extension() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::extension");
  return "";
}
std::vector<JSValue> NativeFileExample::getDirectoryListing() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::getDirectoryListing");
  std::vector<JSValue> list;
  return list;
}
bool NativeFileExample::isDirectory() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::isDirectory");
  return false;
}
bool NativeFileExample::isFile() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::isFile");
  return false;
}
unsigned NativeFileExample::modificationTimestamp() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::modificationTimestamp");
  return 0;
}
bool NativeFileExample::move(const std::string& newpath) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::move");
  return false;
}
JSValue NativeFileExample::open(const std::unordered_set<Titanium::Filesystem::MODE>&) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::open");
  return get_context().CreateNull();
}
JSValue NativeFileExample::read() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::read");
  return get_context().CreateNull();
}
bool NativeFileExample::rename(const std::string& newname) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::rename");
  return false;
}
std::string NativeFileExample::resolve() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::resolve");
  return "";
}
unsigned NativeFileExample::spaceAvailable() TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::spaceAvailable");
  return false;
}
bool NativeFileExample::write(const JSValue& data, bool append) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeFileExample::write");
  return false;
}
