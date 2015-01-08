/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_FILESYSTEM_HPP_
#define _TITANIUM_FILESYSTEM_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Filesystem/Constants.hpp"
#include "Titanium/Filesystem/File.hpp"

namespace Titanium {

using namespace HAL;

/*!
   @class
   @discussion This is the Ti.Filesystem Module.
   See http://docs.appcelerator.com/titanium/latest/#!/api/Ti.Filesystem
  */
class TITANIUMKIT_EXPORT FilesystemModule : public Module, public JSExport<FilesystemModule> {
 public:
  /*!
     @method
     @abstract getFile
     @discussion Returns a File object representing the file identified by the path arguments.
    */
  virtual JSValue getFile(const std::string&) TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract createTempDirectory
     @discussion Creates a temporary directory and returns a File object representing the new directory.
    */
  virtual JSValue createTempDirectory() TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract createTempFile
     @discussion Creates a temporary file and returns a File object representing the new file.
    */
  virtual JSValue createTempFile() TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract isExternalStoragePresent
     @discussion Returns true if the device supports external storage and the external storage device is mounted.
    */
  virtual bool isExternalStoragePresent() TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract openStream
     @discussion Opens file using the Ti.IOStream interface.
    */
  virtual JSValue openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract get_MODE_READ
     @discussion Constant for read mode for file operations.
    */
  virtual JSValue MODE_READ() const TITANIUM_NOEXCEPT final;
  /*!
     @method
     @abstract get_MODE_WRITE
     @discussion Constant for write mode for file operations.
    */
  virtual JSValue MODE_WRITE() const TITANIUM_NOEXCEPT final;
  /*!
     @method
     @abstract MODE_APPEND
     @discussion Constant for append mode for file operations.
    */
  virtual JSValue MODE_APPEND() const TITANIUM_NOEXCEPT final;
  /*!
     @method
     @abstract separator
     @discussion Platform-specific path separator constant.
    */
  virtual std::string separator() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract applicationCacheDirectory
     @discussion Path to the application's internal cache directory.
    */
  virtual std::string applicationCacheDirectory() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract applicationDataDirectory
     @discussion Path to the application's data directory.
    */
  virtual std::string applicationDataDirectory() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract applicationDirectory
     @discussion Path to the application directory.
    */
  virtual std::string applicationDirectory() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract applicationSupportDirectory
     @discussion Path to the application support directory.
    */
  virtual std::string applicationSupportDirectory() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract externalStorageDirectory
     @discussion Path to a directory on removable storage, such as SD card.
    */
  virtual std::string externalStorageDirectory() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract lineEnding
     @discussion Platform-specific line ending constant.
    */
  virtual std::string lineEnding() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract resourcesDirectory
     @discussion Path to the application's resource directory.
    */
  virtual std::string resourcesDirectory() const TITANIUM_NOEXCEPT;
  /*!
     @method
     @abstract tempDirectory
     @discussion Path for the application's temporary directory.
    */
  virtual std::string tempDirectory() const TITANIUM_NOEXCEPT;

  FilesystemModule(const JSContext& js_context) TITANIUM_NOEXCEPT;
  FilesystemModule(const FilesystemModule&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

  virtual ~FilesystemModule() = default;
  FilesystemModule(const FilesystemModule&) = default;
  FilesystemModule& operator=(const FilesystemModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  FilesystemModule(FilesystemModule&&) = default;
  FilesystemModule& operator=(FilesystemModule&&) = default;
#endif

  static void JSExportInitialize();

  virtual JSValue getFile_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
  virtual JSValue createTempDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
  virtual JSValue createTempFile_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
  virtual JSValue isExternalStoragePresent_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
  virtual JSValue openStream_ArgumentValidator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

  virtual JSValue getSeparator_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getApplicationCacheDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getApplicationDataDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getApplicationDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getApplicationSupportDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getExternalStorageDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getLineEnding_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getResourcesDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
  virtual JSValue getTempDirectory_ArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;

  virtual JSValue separator_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue applicationCacheDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue applicationDataDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue applicationDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue applicationSupportDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue externalStorageDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue lineEnding_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue resourcesDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  virtual JSValue tempDirectory_ArgumentValidator() const TITANIUM_NOEXCEPT final;

 private:
  JSValue mode_read__;
  JSValue mode_write__;
  JSValue mode_append__;
};

}  // namespace Titanium {

#endif  // _TITANIUM_FILESYSTEM_HPP_
