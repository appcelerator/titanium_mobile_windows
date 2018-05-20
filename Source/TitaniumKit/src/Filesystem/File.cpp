/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Filesystem/File.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Filesystem/FileStream.hpp"
#include "Titanium/FilesystemModule.hpp"
#include "Titanium/Blob.hpp"
#include <type_traits>

namespace Titanium
{
	namespace Filesystem
	{
		File::File(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context, "Ti.Filesystem.File")
		{
		}

		void File::JSExportInitialize()
		{
			JSExport<File>::SetClassVersion(1);
			JSExport<File>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_PROPERTY_READONLY(File, executable);
			TITANIUM_ADD_PROPERTY_READONLY(File, hidden);
			TITANIUM_ADD_PROPERTY_READONLY(File, name);
			TITANIUM_ADD_PROPERTY_READONLY(File, nativePath);
			TITANIUM_ADD_PROPERTY_READONLY(File, parent);
			TITANIUM_ADD_PROPERTY_READONLY(File, readonly);
			TITANIUM_ADD_PROPERTY_READONLY(File, remoteBackup);
			TITANIUM_ADD_PROPERTY_READONLY(File, size);
			TITANIUM_ADD_PROPERTY_READONLY(File, symbolicLink);
			TITANIUM_ADD_PROPERTY_READONLY(File, writable);

			TITANIUM_ADD_FUNCTION(File, getExecutable);
			TITANIUM_ADD_FUNCTION(File, getHidden);
			TITANIUM_ADD_FUNCTION(File, getName);
			TITANIUM_ADD_FUNCTION(File, getNativePath);
			TITANIUM_ADD_FUNCTION(File, getParent);
			TITANIUM_ADD_FUNCTION(File, getReadonly);
			TITANIUM_ADD_FUNCTION(File, getRemoteBackup);
			TITANIUM_ADD_FUNCTION(File, getSize);
			TITANIUM_ADD_FUNCTION(File, getSymbolicLink);
			TITANIUM_ADD_FUNCTION(File, getWritable);

			TITANIUM_ADD_FUNCTION(File, append);
			TITANIUM_ADD_FUNCTION(File, copy);
			TITANIUM_ADD_FUNCTION(File, createDirectory);
			TITANIUM_ADD_FUNCTION(File, createFile);
			TITANIUM_ADD_FUNCTION(File, createTimestamp);
			TITANIUM_ADD_FUNCTION(File, createdAt);
			TITANIUM_ADD_FUNCTION(File, deleteDirectory);
			TITANIUM_ADD_FUNCTION(File, deleteFile);
			TITANIUM_ADD_FUNCTION(File, exists);
			TITANIUM_ADD_FUNCTION(File, extension);
			TITANIUM_ADD_FUNCTION(File, getDirectoryListing);
			TITANIUM_ADD_FUNCTION(File, isDirectory);
			TITANIUM_ADD_FUNCTION(File, isFile);
			TITANIUM_ADD_FUNCTION(File, modificationTimestamp);
			TITANIUM_ADD_FUNCTION(File, modifiedAt);
			TITANIUM_ADD_FUNCTION(File, move);
			TITANIUM_ADD_FUNCTION(File, open);
			TITANIUM_ADD_FUNCTION(File, read);
			TITANIUM_ADD_FUNCTION(File, rename);
			TITANIUM_ADD_FUNCTION(File, resolve);
			TITANIUM_ADD_FUNCTION(File, spaceAvailable);
			TITANIUM_ADD_FUNCTION(File, write);
		}

		bool File::get_executable() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_executable: Unimplemented");
			return false;
		}

		bool File::get_hidden() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_hidden: Unimplemented");
			return false;
		}

		std::string File::get_name() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_name: Unimplemented");
			return "";
		}

		std::string File::get_nativePath() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_nativePath: Unimplemented");
			return "";
		}

		std::shared_ptr<File> File::get_parent() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_parent: Unimplemented");
			return nullptr;
		}

		bool File::get_readonly() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_readonly: Unimplemented");
			return false;
		}

		bool File::get_remoteBackup() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_remoteBackup: Unimplemented");
			return false;
		}

		bool File::get_symbolicLink() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_symbolicLink: Unimplemented");
			return false;
		}

		bool File::get_writable() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_writable: Unimplemented");
			return false;
		}

		std::uint64_t File::get_size() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_size: Unimplemented");
			return 0;
		}

		bool File::append(const std::string& data) TITANIUM_NOEXCEPT
		{
			return write(data, true);
		}

		bool File::append(const std::shared_ptr<Titanium::Blob>& data) TITANIUM_NOEXCEPT
		{
			return write(data, true);
		}

		bool File::append(const std::shared_ptr<File>& data) TITANIUM_NOEXCEPT
		{
			return write(data, true);
		}

		bool File::copy(const std::string& dest) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::copy: Unimplemented");
			return false;
		}

		bool File::createDirectory() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::createDirectory: Unimplemented");
			return false;
		}

		bool File::createFile() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::createFile: Unimplemented");
			return false;
		}

		std::chrono::milliseconds File::createTimestamp() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::createTimestamp: Unimplemented");
			return std::chrono::milliseconds(0);
		}

		bool File::deleteDirectory(const bool& recursive) TITANIUM_NOEXCEPT
		{
			if (!isDirectory()) {
				return false;
			}
			if (!recursive) {
				return deleteFile();
			}

			const auto js_filesystem = get_context().JSEvaluateScript("Ti.Filesystem");
			TITANIUM_ASSERT(js_filesystem.IsObject());
			const auto filesystem_obj = static_cast<JSObject>(js_filesystem).CallAsConstructor();
			const auto Filesystem = filesystem_obj.GetPrivate<Titanium::FilesystemModule>();

			std::vector<std::string> contents = getDirectoryListing();
			for (size_t i = 0; i < contents.size(); i++) {
				auto value = contents.at(i);
				auto file = Filesystem->getFile(get_context(), resolve() + Filesystem->separator() + value);

				if (file->isDirectory()) {
					if (!file->deleteDirectory(recursive)) {
						return false;
					}
				} else {
					if (!file->deleteFile()) {
						return false;
					}
				}
			}

			return deleteFile();
		}

		bool File::deleteFile() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::deleteFile: Unimplemented");
			return false;
		}

		bool File::exists() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::exists: Unimplemented");
			return false;
		}

		std::string File::extension() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::extension: Unimplemented");
			return "";
		}

		std::vector<std::string> File::getDirectoryListing() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::getDirectoryListing: Unimplemented");
			std::vector<std::string> list;
			return list;
		}

		bool File::isDirectory() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::isDirectory: Unimplemented");
			return false;
		}

		bool File::isFile() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::isFile: Unimplemented");
			return false;
		}

		std::chrono::milliseconds File::modificationTimestamp() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::modificationTimestamp: Unimplemented");
			return std::chrono::milliseconds(0);
		}

		bool File::move(const std::string& newpath) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::move: Unimplemented");
			return false;
		}

		std::shared_ptr<FileStream> File::open(const std::unordered_set<MODE>& modes) TITANIUM_NOEXCEPT
		{
			const auto fileStream_ctor = get_context().JSEvaluateScript("Ti.Filesystem.FileStream");
			TITANIUM_ASSERT(fileStream_ctor.IsObject());
			const auto fileStream = static_cast<JSObject>(fileStream_ctor).CallAsConstructor();
			const auto fileStream_ptr = fileStream.GetPrivate<FileStream>();
			fileStream_ptr->set_modes(modes);
			fileStream_ptr->construct(get_object().GetPrivate<File>());
			return fileStream_ptr;
		}

		std::shared_ptr<Titanium::Blob> File::read() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::read: Unimplemented");
			return nullptr;
		}

		bool File::rename(const std::string& newname) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::rename: Unimplemented");
			return false;
		}

		std::string File::resolve() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::resolve: Unimplemented");
			return "";
		}

		std::uint64_t File::spaceAvailable() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::spaceAvailable: Unimplemented");
			return false;
		}

		bool File::write(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append)
		{
			TITANIUM_LOG_WARN("File::write(vector<uint8_t>): Unimplemented");
			return false;
		}

		void File::writeAsync(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const std::uint32_t& length, const bool& append, const std::function<void(const ErrorResponse&, const uint32_t&)>&)
		{
			TITANIUM_LOG_WARN("File::writeAsync(vector<uint8_t>): Unimplemented");
		}

		bool File::write(const std::string& data, const bool& append) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::write(string): Unimplemented");
			return false;
		}

		bool File::write(const std::shared_ptr<Titanium::Blob>& data, const bool& append) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::write(Blob): Unimplemented");
			return false;
		}

		bool File::write(const std::shared_ptr<File>& data, const bool& append) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::write(File): Unimplemented");
			return false;
		}

		std::vector<std::uint8_t> File::getContent() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::getContent(): Unimplemented");
			return std::vector<std::uint8_t>();
		}

		std::vector<std::uint8_t> File::readBytes(const std::uint32_t& offset, const std::uint32_t& length) const
		{
			TITANIUM_LOG_WARN("File::readBytes(): Unimplemented");
			return std::vector<std::uint8_t>();
		}

		void File::readBytesAsync(const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const ErrorResponse&, const std::vector<std::uint8_t>&)>&) const
		{
			TITANIUM_LOG_WARN("File::readBytesAsync(): Unimplemented");
		}

		void File::readAllBytesAsync(const std::function<void(const ErrorResponse&, const std::vector<std::uint8_t>&)>& callback) const
		{
			ErrorResponse error;
			error.code = -1;
			error.success = false;
			error.error = "File::readAllBytesAsync(): Unimplemented";
			callback(error, std::vector<std::uint8_t>());
		}

		TITANIUM_PROPERTY_GETTER(File, executable)
		{
			return get_context().CreateBoolean(get_executable());
		}

		TITANIUM_PROPERTY_GETTER(File, hidden)
		{
			return get_context().CreateBoolean(get_hidden());
		}

		TITANIUM_PROPERTY_GETTER(File, name)
		{
			return get_context().CreateString(get_name());
		}

		TITANIUM_PROPERTY_GETTER(File, nativePath)
		{
			return get_context().CreateString(get_nativePath());
		}

		TITANIUM_PROPERTY_GETTER(File, parent)
		{
			auto parent = get_parent();
			if (parent != nullptr) {
				return parent->get_object();
			}
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_GETTER(File, readonly)
		{
			return get_context().CreateBoolean(get_readonly());
		}

		TITANIUM_PROPERTY_GETTER(File, remoteBackup)
		{
			return get_context().CreateBoolean(get_remoteBackup());
		}

		TITANIUM_PROPERTY_GETTER(File, symbolicLink)
		{
			return get_context().CreateBoolean(get_symbolicLink());
		}

		TITANIUM_PROPERTY_GETTER(File, writable)
		{
			return get_context().CreateBoolean(get_writable());
		}

		TITANIUM_PROPERTY_GETTER(File, size)
		{
			return get_context().CreateNumber(static_cast<double>(get_size()));
		}

		TITANIUM_FUNCTION_AS_GETTER(File, getSize, size);
		TITANIUM_FUNCTION_AS_GETTER(File, getExecutable, executable);
		TITANIUM_FUNCTION_AS_GETTER(File, getHidden, hidden);
		TITANIUM_FUNCTION_AS_GETTER(File, getName, name);
		TITANIUM_FUNCTION_AS_GETTER(File, getNativePath, nativePath);
		TITANIUM_FUNCTION_AS_GETTER(File, getParent, parent);
		TITANIUM_FUNCTION_AS_GETTER(File, getReadonly, readonly);
		TITANIUM_FUNCTION_AS_GETTER(File, getRemoteBackup, remoteBackup);
		TITANIUM_FUNCTION_AS_GETTER(File, getSymbolicLink, symbolicLink);
		TITANIUM_FUNCTION_AS_GETTER(File, getWritable, writable);

		TITANIUM_FUNCTION(File, append)
		{
			const auto js_context = this_object.get_context();

			if (arguments.size() == 0) {
				return js_context.CreateUndefined();
			}
			auto _0 = arguments.at(0);

			if (_0.IsString()) {
				return js_context.CreateBoolean(append(static_cast<std::string>(arguments.at(0))));
			} else if (_0.IsObject()) {
				const auto js_object = static_cast<JSObject>(_0);
				const auto blob = js_object.GetPrivate<Titanium::Blob>();
				const auto file = js_object.GetPrivate<File>();
				if (blob != nullptr) {
					return js_context.CreateBoolean(append(blob));
				} else if (file != nullptr) {
					return js_context.CreateBoolean(append(file));
				}
			}
			return js_context.CreateNull();
		}

		TITANIUM_FUNCTION(File, copy)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto destinationPath = static_cast<std::string>(_0);
			return get_context().CreateBoolean(copy(destinationPath));
		}

		TITANIUM_FUNCTION(File, createDirectory)
		{
			return get_context().CreateBoolean(createDirectory());
		}

		TITANIUM_FUNCTION(File, createFile)
		{
			return get_context().CreateBoolean(createFile());
		}

		TITANIUM_FUNCTION(File, createTimestamp)
		{
			const auto ctx = get_context();
			ctx.JSEvaluateScript("Ti.API.warn('createTimestamp() has been deprecated in 7.2.0 in favor of createdAt() to avoid platform-differences for return type. createdAt() will return a Date object on all platforms.');");

			return ctx.CreateNumber(static_cast<double>(createTimestamp().count()));
		}

		TITANIUM_FUNCTION(File, createdAt)
		{
			const auto ctx = get_context();

			const std::vector<JSValue> dateArg = { ctx.CreateNumber(static_cast<double>(createTimestamp().count())) };
			return ctx.CreateDate(dateArg);
		}

		TITANIUM_FUNCTION(File, deleteDirectory)
		{
			bool recursive = false;
			if (arguments.size() > 0) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				recursive = static_cast<bool>(_0);
			}

			return get_context().CreateBoolean(deleteDirectory(recursive));
		}

		TITANIUM_FUNCTION(File, deleteFile)
		{
			return get_context().CreateBoolean(deleteFile());
		}

		TITANIUM_FUNCTION(File, exists)
		{
			return get_context().CreateBoolean(exists());
		}

		TITANIUM_FUNCTION(File, extension)
		{
			return get_context().CreateString(extension());
		}

		TITANIUM_FUNCTION(File, getDirectoryListing)
		{
			auto listing = getDirectoryListing();
			auto context = get_context();
			std::vector<JSValue> result;
			for (size_t i = 0; i < listing.size(); i++) {
				result.push_back(context.CreateString(listing.at(i)));
			}
			return context.CreateArray(result);
		}

		TITANIUM_FUNCTION(File, isDirectory)
		{
			return get_context().CreateBoolean(isDirectory());
		}

		TITANIUM_FUNCTION(File, isFile)
		{
			return get_context().CreateBoolean(isFile());
		}

		TITANIUM_FUNCTION(File, modificationTimestamp)
		{
			const auto ctx = get_context();
			ctx.JSEvaluateScript("Ti.API.warn('modificationTimestamp() has been deprecated in 7.2.0 in favor of modifiedAt() to avoid platform-differences for return type. modifiedAt() will return a Date object on all platforms.');");

			return ctx.CreateNumber(static_cast<double>(modificationTimestamp().count()));
		}

		TITANIUM_FUNCTION(File, modifiedAt)
		{
			const auto ctx = get_context();

			const std::vector<JSValue> dateArg = { ctx.CreateNumber(static_cast<double>(modificationTimestamp().count())) };
			return ctx.CreateDate(dateArg);
		}

		TITANIUM_FUNCTION(File, move)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto newpath = static_cast<std::string>(_0);
			return get_context().CreateBoolean(move(newpath));
		}

		TITANIUM_FUNCTION(File, open)
		{
			auto js_context = this_object.get_context();
			if (arguments.size() == 0) {
				return js_context.CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());

			const auto result = open(Constants::to_MODE(static_cast<std::underlying_type<MODE>::type>(_0)));
			if (result != nullptr) {
				return result->get_object();
			} else {
				return js_context.CreateNull();
			}
		}

		TITANIUM_FUNCTION(File, read)
		{
			const auto result = read();
			if (result != nullptr) {
				return result->get_object();
			} else {
				return this_object.get_context().CreateNull();
			}
		}

		TITANIUM_FUNCTION(File, rename)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto newname = static_cast<std::string>(_0);
			return get_context().CreateBoolean(rename(newname));
		}

		TITANIUM_FUNCTION(File, resolve)
		{
			return get_context().CreateString(resolve());
		}

		TITANIUM_FUNCTION(File, spaceAvailable)
		{
			return get_context().CreateNumber(static_cast<double>(spaceAvailable()));
		}

		TITANIUM_FUNCTION(File, write)
		{
			const auto js_context = this_object.get_context();

			if (arguments.size() < 1) {
				return js_context.CreateUndefined();
			}

			const auto _0 = arguments.at(0);

			const auto _1 = arguments.size() < 2 ? js_context.CreateBoolean(false) : arguments.at(1);
			TITANIUM_ASSERT(_1.IsBoolean());
			const auto append = static_cast<bool>(_1);

			if (_0.IsString()) {
				return js_context.CreateBoolean(write(static_cast<std::string>(arguments.at(0)), append));
			} else if (_0.IsObject()) {
				const auto js_object = static_cast<JSObject>(_0);
				const auto blob = js_object.GetPrivate<Titanium::Blob>();
				const auto file = js_object.GetPrivate<File>();
				if (blob != nullptr) {
					return js_context.CreateBoolean(write(blob, append));
				} else if (file != nullptr) {
					return js_context.CreateBoolean(write(file, append));
				}
			}
			return js_context.CreateNull();
		}
	} // namespace Filesystem
}  // namespace Titanium
