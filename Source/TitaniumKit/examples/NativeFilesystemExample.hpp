/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEFILESYSTEMEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEFILESYSTEMEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
 @class
 @discussion This is an example of how to implement Titanium::File
 for a native File.
 */
class NativeFilesystemExample final : public Titanium::FilesystemModule, public JSExport<NativeFilesystemExample> {
  
public:
  
  virtual JSValue getFile(const std::string&) TITANIUM_NOEXCEPT;
  virtual JSValue createTempDirectory() TITANIUM_NOEXCEPT;
  virtual JSValue createTempFile() TITANIUM_NOEXCEPT;
  virtual bool isExternalStoragePresent() TITANIUM_NOEXCEPT;
  virtual JSValue openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT;

  virtual std::string separator() const TITANIUM_NOEXCEPT;
  virtual std::string applicationCacheDirectory() const TITANIUM_NOEXCEPT;
  virtual std::string applicationDataDirectory() const TITANIUM_NOEXCEPT;
  virtual std::string applicationDirectory() const TITANIUM_NOEXCEPT;
  virtual std::string applicationSupportDirectory() const TITANIUM_NOEXCEPT;
  virtual std::string externalStorageDirectory() const TITANIUM_NOEXCEPT;
  virtual std::string lineEnding() const TITANIUM_NOEXCEPT;
  virtual std::string resourcesDirectory() const TITANIUM_NOEXCEPT;
  virtual std::string tempDirectory() const TITANIUM_NOEXCEPT;

  NativeFilesystemExample(const JSContext& js_context)                                    TITANIUM_NOEXCEPT;
  NativeFilesystemExample(const NativeFilesystemExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
  
  virtual ~NativeFilesystemExample()                          = default;
  NativeFilesystemExample(const NativeFilesystemExample&)            = default;
  NativeFilesystemExample& operator=(const NativeFilesystemExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  NativeFilesystemExample(NativeFilesystemExample&&)                 = default;
  NativeFilesystemExample& operator=(NativeFilesystemExample&&)      = default;
#endif
  
  static void JSExportInitialize();
  
protected:
  
};

#endif // _TITANIUM_EXAMPLES_NATIVEFILESYSTEMEXAMPLE_HPP_
