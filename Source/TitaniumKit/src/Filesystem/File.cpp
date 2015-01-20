/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Filesystem/File.hpp"
#include <type_traits>

namespace Titanium
{
	namespace Filesystem
	{
		File::File(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Module(js_context, arguments)
		{
		}

		void File::JSExportInitialize()
		{
			JSExport<File>::SetClassVersion(1);
			JSExport<File>::SetParent(JSExport<Module>::Class());
			JSExport<File>::AddValueProperty("executable", std::mem_fn(&File::js_get_executable));
			JSExport<File>::AddValueProperty("hidden", std::mem_fn(&File::js_get_hidden));
			JSExport<File>::AddValueProperty("name", std::mem_fn(&File::js_get_name));
			JSExport<File>::AddValueProperty("nativePath", std::mem_fn(&File::js_get_nativePath));
			JSExport<File>::AddValueProperty("parent", std::mem_fn(&File::js_get_parent));
			JSExport<File>::AddValueProperty("readonly", std::mem_fn(&File::js_get_readonly));
			JSExport<File>::AddValueProperty("remoteBackup", std::mem_fn(&File::js_get_remoteBackup));
			JSExport<File>::AddValueProperty("size", std::mem_fn(&File::js_get_size));
			JSExport<File>::AddValueProperty("symbolicLink", std::mem_fn(&File::js_get_symbolicLink));
			JSExport<File>::AddValueProperty("writable", std::mem_fn(&File::js_get_writable));

			JSExport<File>::AddFunctionProperty("getExecutable", std::mem_fn(&File::js_getExecutable));
			JSExport<File>::AddFunctionProperty("getHidden", std::mem_fn(&File::js_getHidden));
			JSExport<File>::AddFunctionProperty("getName", std::mem_fn(&File::js_getName));
			JSExport<File>::AddFunctionProperty("getNativePath", std::mem_fn(&File::js_getNativePath));
			JSExport<File>::AddFunctionProperty("getParent", std::mem_fn(&File::js_getParent));
			JSExport<File>::AddFunctionProperty("getReadonly", std::mem_fn(&File::js_getReadonly));
			JSExport<File>::AddFunctionProperty("getRemoteBackup", std::mem_fn(&File::js_getRemoteBackup));
			JSExport<File>::AddFunctionProperty("getSize", std::mem_fn(&File::js_getSize));
			JSExport<File>::AddFunctionProperty("getSymbolicLink", std::mem_fn(&File::js_getSymbolicLink));
			JSExport<File>::AddFunctionProperty("getWritable", std::mem_fn(&File::js_getWritable));

			JSExport<File>::AddFunctionProperty("append", std::mem_fn(&File::js_append));
			JSExport<File>::AddFunctionProperty("copy", std::mem_fn(&File::js_copy));
			JSExport<File>::AddFunctionProperty("createDirectory", std::mem_fn(&File::js_createDirectory));
			JSExport<File>::AddFunctionProperty("createFile", std::mem_fn(&File::js_createFile));
			JSExport<File>::AddFunctionProperty("createTimestamp", std::mem_fn(&File::js_createTimestamp));
			JSExport<File>::AddFunctionProperty("deleteDirectory", std::mem_fn(&File::js_deleteDirectory));
			JSExport<File>::AddFunctionProperty("deleteFile", std::mem_fn(&File::js_deleteFile));
			JSExport<File>::AddFunctionProperty("exists", std::mem_fn(&File::js_exists));
			JSExport<File>::AddFunctionProperty("extension", std::mem_fn(&File::js_extension));
			JSExport<File>::AddFunctionProperty("getDirectoryListing", std::mem_fn(&File::js_getDirectoryListing));
			JSExport<File>::AddFunctionProperty("isDirectory", std::mem_fn(&File::js_isDirectory));
			JSExport<File>::AddFunctionProperty("isFile", std::mem_fn(&File::js_isFile));
			JSExport<File>::AddFunctionProperty("modificationTimestamp", std::mem_fn(&File::js_modificationTimestamp));
			JSExport<File>::AddFunctionProperty("move", std::mem_fn(&File::js_move));
			JSExport<File>::AddFunctionProperty("open", std::mem_fn(&File::js_open));
			JSExport<File>::AddFunctionProperty("read", std::mem_fn(&File::js_read));
			JSExport<File>::AddFunctionProperty("rename", std::mem_fn(&File::js_rename));
			JSExport<File>::AddFunctionProperty("resolve", std::mem_fn(&File::js_resolve));
			JSExport<File>::AddFunctionProperty("spaceAvailable", std::mem_fn(&File::js_spaceAvailable));
			JSExport<File>::AddFunctionProperty("write", std::mem_fn(&File::js_write));
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
		JSValue File::get_parent() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_parent: Unimplemented");
			return get_context().CreateNull();
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
		unsigned File::get_size() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::get_size: Unimplemented");
			return 0;
		}

		bool File::append(const JSValue& data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::append: Unimplemented");
			return false;
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
		unsigned File::createTimestamp() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::createTimestamp: Unimplemented");
			return 0;
		}
		bool File::deleteDirectory(bool recursive) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::deleteDirectory: Unimplemented");
			return false;
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
		std::vector<JSValue> File::getDirectoryListing() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::getDirectoryListing: Unimplemented");
			std::vector<JSValue> list;
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
		unsigned File::modificationTimestamp() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::modificationTimestamp: Unimplemented");
			return 0;
		}
		bool File::move(const std::string& newpath) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::move: Unimplemented");
			return false;
		}
		JSValue File::open(const std::unordered_set<MODE>&) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::open: Unimplemented");
			return get_context().CreateNull();
		}
		JSValue File::read() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::read: Unimplemented");
			return get_context().CreateNull();
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
		unsigned File::spaceAvailable() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::spaceAvailable: Unimplemented");
			return false;
		}
		bool File::write(const JSValue& data, bool append) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::write: Unimplemented");
			return false;
		}

		JSValue File::js_get_executable() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_executable());
		}
		JSValue File::js_get_hidden() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_hidden());
		}
		JSValue File::js_get_name() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_name());
		}
		JSValue File::js_get_nativePath() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_nativePath());
		}
		JSValue File::js_get_parent() const TITANIUM_NOEXCEPT
		{
			return get_parent();
		}
		JSValue File::js_get_readonly() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_readonly());
		}
		JSValue File::js_get_remoteBackup() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_remoteBackup());
		}
		JSValue File::js_get_symbolicLink() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_symbolicLink());
		}
		JSValue File::js_get_writable() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_writable());
		}
		JSValue File::js_get_size() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_size());
		}
		JSValue File::js_getSize(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_size();
		}

		JSValue File::js_getExecutable(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_executable();
		}
		JSValue File::js_getHidden(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_hidden();
		}
		JSValue File::js_getName(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_name();
		}
		JSValue File::js_getNativePath(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_nativePath();
		}
		JSValue File::js_getParent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_parent();
		}
		JSValue File::js_getReadonly(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_readonly();
		}
		JSValue File::js_getRemoteBackup(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_remoteBackup();
		}
		JSValue File::js_getSymbolicLink(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_symbolicLink();
		}
		JSValue File::js_getWritable(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_writable();
		}

		JSValue File::js_append(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			return get_context().CreateBoolean(append(arguments.at(0)));
		}
		JSValue File::js_copy(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto destinationPath = static_cast<std::string>(_0);
			return get_context().CreateBoolean(copy(destinationPath));
		}
		JSValue File::js_createDirectory(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(createDirectory());
		}
		JSValue File::js_createFile(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(createFile());
		}
		JSValue File::js_createTimestamp(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(createTimestamp());
		}
		JSValue File::js_deleteDirectory(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			bool recursive = false;
			if (arguments.size() > 0) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				recursive = static_cast<bool>(_0);
			}

			return get_context().CreateBoolean(deleteDirectory(recursive));
		}
		JSValue File::js_deleteFile(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(deleteFile());
		}
		JSValue File::js_exists(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(exists());
		}
		JSValue File::js_extension(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(extension());
		}
		JSValue File::js_getDirectoryListing(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateArray(getDirectoryListing());
		}
		JSValue File::js_isDirectory(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(isDirectory());
		}
		JSValue File::js_isFile(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(isFile());
		}
		JSValue File::js_modificationTimestamp(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(modificationTimestamp());
		}
		JSValue File::js_move(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto newpath = static_cast<std::string>(_0);
			return get_context().CreateBoolean(move(newpath));
		}
		JSValue File::js_open(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());

			return open(Constants::to_MODE(static_cast<std::underlying_type<MODE>::type>(_0)));
		}
		JSValue File::js_read(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return read();
		}
		JSValue File::js_rename(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto newname = static_cast<std::string>(_0);
			return get_context().CreateBoolean(rename(newname));
		}
		JSValue File::js_resolve(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(resolve());
		}
		JSValue File::js_spaceAvailable(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(spaceAvailable());
		}
		JSValue File::js_write(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			}

			const auto _0 = arguments.at(0);

			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_1.IsBoolean());
			const auto append = static_cast<bool>(_1);

			return get_context().CreateBoolean(write(_0, append));
		}
	} // namespace Filesystem
}  // namespace Titanium
