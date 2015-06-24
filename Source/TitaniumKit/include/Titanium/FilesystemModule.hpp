/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_FILESYSTEM_HPP_
#define _TITANIUM_FILESYSTEM_HPP_

#include "Titanium/Filesystem/File.hpp"
#include "Titanium/Filesystem/FileStream.hpp"

namespace Titanium
{
	using namespace HAL;
	using File_shared_ptr_t = std::shared_ptr<Titanium::Filesystem::File>;
	using FileStream_shared_ptr_t = std::shared_ptr<Titanium::Filesystem::FileStream>;

	/*!
	  @class
	  @discussion This is the Ti.Filesystem Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Ti.Filesystem
	*/
	class TITANIUMKIT_EXPORT FilesystemModule : public Module, public JSExport<FilesystemModule>
	{
	public:
		/*!
		  @method
		  @abstract getFile
		  @discussion Returns a File object representing the file identified by the path arguments.
		*/
		virtual File_shared_ptr_t getFile(const JSContext&, const std::string&) TITANIUM_NOEXCEPT final;
		/*!
		  @method
		  @abstract createTempDirectory
		  @discussion Creates a temporary directory and returns a File object representing the new directory.
		*/
		virtual File_shared_ptr_t createTempDirectory(const JSContext&) TITANIUM_NOEXCEPT final;
		/*!
		  @method
		  @abstract createTempFile
		  @discussion Creates a temporary file and returns a File object representing the new file.
		*/
		virtual File_shared_ptr_t createTempFile(const JSContext&) TITANIUM_NOEXCEPT final;
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
		virtual FileStream_shared_ptr_t openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract get_MODE_READ
		  @discussion Constant for read mode for file operations.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(MODE_READ);
		/*!
		  @method
		  @abstract get_MODE_WRITE
		  @discussion Constant for write mode for file operations.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(MODE_WRITE);
		/*!
		  @method
		  @abstract MODE_APPEND
		  @discussion Constant for append mode for file operations.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(MODE_APPEND);
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

		FilesystemModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~FilesystemModule() = default;
		FilesystemModule(const FilesystemModule&) = default;
		FilesystemModule& operator=(const FilesystemModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		FilesystemModule(FilesystemModule&&) = default;
		FilesystemModule& operator=(FilesystemModule&&) = default;
#endif

		static void JSExportInitialize();
		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

		TITANIUM_FUNCTION_DEF(getFile);
		TITANIUM_FUNCTION_DEF(createTempDirectory);
		TITANIUM_FUNCTION_DEF(createTempFile);
		TITANIUM_FUNCTION_DEF(isExternalStoragePresent);
		TITANIUM_FUNCTION_DEF(openStream);

		TITANIUM_FUNCTION_DEF(getSeparator);
		TITANIUM_FUNCTION_DEF(getApplicationCacheDirectory);
		TITANIUM_FUNCTION_DEF(getApplicationDataDirectory);
		TITANIUM_FUNCTION_DEF(getApplicationDirectory);
		TITANIUM_FUNCTION_DEF(getApplicationSupportDirectory);
		TITANIUM_FUNCTION_DEF(getExternalStorageDirectory);
		TITANIUM_FUNCTION_DEF(getLineEnding);
		TITANIUM_FUNCTION_DEF(getResourcesDirectory);
		TITANIUM_FUNCTION_DEF(getTempDirectory);

		TITANIUM_PROPERTY_READONLY_DEF(separator);
		TITANIUM_PROPERTY_READONLY_DEF(applicationCacheDirectory);
		TITANIUM_PROPERTY_READONLY_DEF(applicationDataDirectory);
		TITANIUM_PROPERTY_READONLY_DEF(applicationDirectory);
		TITANIUM_PROPERTY_READONLY_DEF(applicationSupportDirectory);
		TITANIUM_PROPERTY_READONLY_DEF(externalStorageDirectory);
		TITANIUM_PROPERTY_READONLY_DEF(lineEnding);
		TITANIUM_PROPERTY_READONLY_DEF(resourcesDirectory);
		TITANIUM_PROPERTY_READONLY_DEF(tempDirectory);

	private:
		JSValue mode_read__;
		JSValue mode_write__;
		JSValue mode_append__;
	};

}  // namespace Titanium

#endif  // _TITANIUM_FILESYSTEM_HPP_
