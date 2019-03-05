/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_FILESYSTEM_FILE_HPP_
#define _TITANIUM_FILESYSTEM_FILE_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Filesystem/Constants.hpp"
#include "Titanium/ErrorResponse.hpp"
#include <chrono>
#include <vector>
#include <functional>

namespace Titanium
{
	class Blob;

	namespace Filesystem
	{
		using namespace HAL;

		class File;
		class FileStream;

		/*!
		  @class
		  @discussion This is the Titanium.Filesystem.File module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Filesystem.File
		*/
		class TITANIUMKIT_EXPORT File : public Module, public JSExport<File>
		{
		public:
			/*!
			  @method
			  @abstract get_executable
			  @discussion true if the file is executable.
			*/
			virtual bool get_executable() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_hidden
			  @discussion Set to true if the file is hidden.
			*/
			virtual bool get_hidden() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_name
			  @discussion Name of the file.
			*/
			virtual std::string get_name() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_nativePath
			  @discussion Native path associated with this file object, as a file URL.
			*/
			virtual std::string get_nativePath() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_parent
			  @discussion A File object representing the parent directory of the file identified by this object.
			*/
			virtual std::shared_ptr<File> get_parent() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_teadonly
			  @discussion true if the file identified by this object is read-only.
			*/
			virtual bool get_readonly() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_remoteBackup
			  @discussion Value indicating whether or not to back up to a cloud service.
			*/
			virtual bool get_remoteBackup() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_size
			  @discussion Size, in bytes, of the file identified by this object.
			*/
			virtual std::uint64_t get_size() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_symbolicLink
			  @discussion true if the file identified by this object is a symbolic link.
			*/
			virtual bool get_symbolicLink() const TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract get_writable
			  @discussion true if the file identified by this object is writable.
			*/
			virtual bool get_writable() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract append
			  @discussion Appends data to the file identified by this file object.
			*/
			virtual bool append(const std::string& data) TITANIUM_NOEXCEPT;
			virtual bool append(const std::shared_ptr<Titanium::Blob>& data) TITANIUM_NOEXCEPT;
			virtual bool append(const std::shared_ptr<File>& data) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract copy
			  @discussion Copies the file identified by this file object to a new path.
			*/
			virtual bool copy(const std::string& dest) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract createDirectory
			  @discussion Creates a directory at the path identified by this file object.
			*/
			virtual bool createDirectory() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract createFile
			  @discussion Creates a file at the path identified by this file object.
			*/
			virtual bool createFile() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract createTimestamp
			  @discussion Returns the creation timestamp for the file identified by this file object.
			*/
			virtual std::chrono::milliseconds createTimestamp() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract deleteDirectory
			  @discussion Deletes the directory identified by this file object.
			*/
			virtual bool deleteDirectory(const bool& recursive) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract deleteFile
			  @discussion Deletes the file identified by this file object.
			*/
			virtual bool deleteFile() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract exists
			  @discussion Returns true if the file or directory identified by this file object exists on the device.
			*/
			virtual bool exists() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract extension
			  @discussion Returns the extension for the file identified by this file object.
			*/
			virtual std::string extension() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getDirectoryListing
			  @discussion Returns a listing of the directory identified by this file object, or null
			  if this object doesn't identify a directory.
			*/
			virtual std::vector<std::string> getDirectoryListing() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract isDirectory
			  @discussion Returns true if this file object represents a directory.
			*/
			virtual bool isDirectory() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract isFile
			  @discussion Returns true if this file object represents an ordinary file.
			*/
			virtual bool isFile() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract modificationTimestamp
			  @discussion Returns the last modification time for this file.
			*/
			virtual std::chrono::milliseconds modificationTimestamp() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract move
			  @discussion Moves the file identified by this file object to another path.
			*/
			virtual bool move(const std::string& newpath) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract open
			  @discussion Opens the file identified by this file object for random access.
			*/
			virtual std::shared_ptr<FileStream> open(const std::unordered_set<MODE>&) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract read
			  @discussion Returns the contents of the file identified by this file object as a Blob.
			*/
			virtual std::shared_ptr<Titanium::Blob> read() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract rename
			  @discussion Renames the file identified by this file object.
			*/
			virtual bool rename(const std::string& newname) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract resolve
			  @discussion Returns the fully-resolved native path associated with this file object.
			*/
			virtual std::string resolve() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract spaceAvailable
			  @discussion Returns the amount of free space available on the device where the file identified by this file object is stored.
			*/
			virtual std::uint64_t spaceAvailable() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract write
			  @discussion Writes the specified data to the file identified by this file object.
			*/
			virtual bool write(const std::string& data, const bool& append) TITANIUM_NOEXCEPT;
			virtual bool write(const std::shared_ptr<Titanium::Blob>& data, const bool& append) TITANIUM_NOEXCEPT;
			virtual bool write(const std::shared_ptr<File>& data, const bool& append) TITANIUM_NOEXCEPT;
			virtual bool write(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append);
			virtual void writeAsync(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append, const std::function<void(const ErrorResponse&, const uint32_t&)>&);

			virtual std::vector<std::uint8_t> readBytes(const std::uint32_t& offset, const std::uint32_t& length) const;
			virtual void readBytesAsync(const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const ErrorResponse&, const std::vector<std::uint8_t>&)>&) const;
			virtual void readAllBytesAsync(const std::function<void(const ErrorResponse&, const std::vector<std::uint8_t>&)>&) const;

			virtual std::vector<std::uint8_t> getContent() const TITANIUM_NOEXCEPT;

			File(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~File() = default;
			File(const File&) = default;
			File& operator=(const File&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			File(File&&) = default;
			File& operator=(File&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(executable);
			TITANIUM_PROPERTY_READONLY_DEF(hidden);
			TITANIUM_PROPERTY_READONLY_DEF(name);
			TITANIUM_PROPERTY_READONLY_DEF(nativePath);
			TITANIUM_PROPERTY_READONLY_DEF(parent);
			TITANIUM_PROPERTY_READONLY_DEF(readonly);
			TITANIUM_PROPERTY_READONLY_DEF(remoteBackup);
			TITANIUM_PROPERTY_READONLY_DEF(size);
			TITANIUM_PROPERTY_READONLY_DEF(symbolicLink);
			TITANIUM_PROPERTY_READONLY_DEF(writable);

			TITANIUM_FUNCTION_DEF(getExecutable);
			TITANIUM_FUNCTION_DEF(getHidden);
			TITANIUM_FUNCTION_DEF(getName);
			TITANIUM_FUNCTION_DEF(getNativePath);
			TITANIUM_FUNCTION_DEF(getParent);
			TITANIUM_FUNCTION_DEF(getReadonly);
			TITANIUM_FUNCTION_DEF(getRemoteBackup);
			TITANIUM_FUNCTION_DEF(getSize);
			TITANIUM_FUNCTION_DEF(getSymbolicLink);
			TITANIUM_FUNCTION_DEF(getWritable);

			TITANIUM_FUNCTION_DEF(append);
			TITANIUM_FUNCTION_DEF(copy);
			TITANIUM_FUNCTION_DEF(createDirectory);
			TITANIUM_FUNCTION_DEF(createFile);
			TITANIUM_FUNCTION_DEF(createTimestamp);
			TITANIUM_FUNCTION_DEF(createdAt);
			TITANIUM_FUNCTION_DEF(deleteDirectory);
			TITANIUM_FUNCTION_DEF(deleteFile);
			TITANIUM_FUNCTION_DEF(exists);
			TITANIUM_FUNCTION_DEF(extension);
			TITANIUM_FUNCTION_DEF(getDirectoryListing);
			TITANIUM_FUNCTION_DEF(isDirectory);
			TITANIUM_FUNCTION_DEF(isFile);
			TITANIUM_FUNCTION_DEF(modificationTimestamp);
			TITANIUM_FUNCTION_DEF(modifiedAt);
			TITANIUM_FUNCTION_DEF(move);
			TITANIUM_FUNCTION_DEF(open);
			TITANIUM_FUNCTION_DEF(read);
			TITANIUM_FUNCTION_DEF(rename);
			TITANIUM_FUNCTION_DEF(resolve);
			TITANIUM_FUNCTION_DEF(spaceAvailable);
			TITANIUM_FUNCTION_DEF(write);
		};
	} // namespace Filesystem
}  // namespace Titanium

#endif  // _TITANIUM_FILESYSTEM_FILE_HPP_
