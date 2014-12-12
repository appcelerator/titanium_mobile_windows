/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEFILEEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEFILEEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace JavaScriptCoreCPP;

/*!
 @class
 @discussion This is an example of how to implement Titanium::File
 for a native File.
 */
class NativeFileExample final : public Titanium::Filesystem::File, public JSExport<NativeFileExample> {
  
public:
  
  NativeFileExample(const JSContext& js_context)                                    TITANIUM_NOEXCEPT;
  NativeFileExample(const NativeFileExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeFileExample()                          = default;
  NativeFileExample(const NativeFileExample&)            = default;
  NativeFileExample& operator=(const NativeFileExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeFileExample(NativeFileExample&&)                 = default;
  NativeFileExample& operator=(NativeFileExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
  virtual bool get_executable() const TITANIUM_NOEXCEPT;
  virtual bool get_hidden() const TITANIUM_NOEXCEPT;
  virtual std::string get_name() const TITANIUM_NOEXCEPT;
  virtual std::string get_nativePath() const TITANIUM_NOEXCEPT;
  virtual JSValue get_parent() const TITANIUM_NOEXCEPT;
  virtual bool get_readonly() const TITANIUM_NOEXCEPT;
  virtual bool get_remoteBackup() const TITANIUM_NOEXCEPT;
  virtual unsigned get_size() const TITANIUM_NOEXCEPT;
  virtual bool get_symbolicLink() const TITANIUM_NOEXCEPT;
  virtual bool get_writable() const TITANIUM_NOEXCEPT;
  
  virtual bool append(const JSValue& data) TITANIUM_NOEXCEPT;
  virtual bool copy(const std::string& dest) TITANIUM_NOEXCEPT;
  virtual bool createDirectory() TITANIUM_NOEXCEPT;
  virtual bool createFile() TITANIUM_NOEXCEPT;
  virtual unsigned createTimestamp() TITANIUM_NOEXCEPT;
  virtual bool deleteDirectory(bool recursive) TITANIUM_NOEXCEPT;
  virtual bool deleteFile() TITANIUM_NOEXCEPT;
  virtual bool exists() TITANIUM_NOEXCEPT;
  virtual std::string extension() TITANIUM_NOEXCEPT;
  virtual std::vector<JSValue> getDirectoryListing() TITANIUM_NOEXCEPT;
  virtual bool isDirectory() TITANIUM_NOEXCEPT;
  virtual bool isFile() TITANIUM_NOEXCEPT;
  virtual unsigned modificationTimestamp() TITANIUM_NOEXCEPT;
  virtual bool move(const std::string& newpath) TITANIUM_NOEXCEPT;
  virtual JSValue open(const std::unordered_set<Titanium::Filesystem::MODE>&) TITANIUM_NOEXCEPT;
  virtual JSValue read() TITANIUM_NOEXCEPT;
  virtual bool rename(const std::string& newname) TITANIUM_NOEXCEPT;
  virtual std::string resolve() TITANIUM_NOEXCEPT;
  virtual unsigned spaceAvailable() TITANIUM_NOEXCEPT;
  virtual bool write(const JSValue& data, bool append) TITANIUM_NOEXCEPT;
  
protected:
  
};

#endif // _TITANIUM_EXAMPLES_NATIVEFILEEXAMPLE_HPP_
