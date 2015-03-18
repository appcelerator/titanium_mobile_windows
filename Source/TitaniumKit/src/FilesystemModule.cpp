/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/FilesystemModule.hpp"
#include <sstream>

namespace Titanium
{
	FilesystemModule::FilesystemModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context),
	      mode_read__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::READ))),
	      mode_write__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::WRITE))),
	      mode_append__(js_context.CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::APPEND)))
	{
	}

	JSValue FilesystemModule::MODE_READ() const TITANIUM_NOEXCEPT
	{
		return mode_read__;
	}
	JSValue FilesystemModule::MODE_WRITE() const TITANIUM_NOEXCEPT
	{
		return mode_write__;
	}
	JSValue FilesystemModule::MODE_APPEND() const TITANIUM_NOEXCEPT
	{
		return mode_append__;
	}

	std::string FilesystemModule::separator() const TITANIUM_NOEXCEPT
	{
		return "/";
	}

	File_shared_ptr_t FilesystemModule::getFile(const JSContext& js_context, const std::string& path) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Filesystem::getFile: ", path);

		JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue FS_property = Titanium.GetProperty("Filesystem");
		TITANIUM_ASSERT(FS_property.IsObject());  // precondition
		JSObject FS = static_cast<JSObject>(FS_property);

		JSValue File_property = FS.GetProperty("File");
		TITANIUM_ASSERT(File_property.IsObject());  // precondition
		JSObject File = static_cast<JSObject>(File_property);

		return File.CallAsConstructor(path).GetPrivate<Titanium::Filesystem::File>();
	}

	File_shared_ptr_t FilesystemModule::createTempDirectory(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		const auto script =
		"       var file = Ti.Filesystem.getFile(Ti.Filesystem.tempDirectory, new Date().getTime());"
		"       file.createDirectory();"
		"       file;";
		auto file = js_context.JSEvaluateScript(script);
		if (file.IsObject()) {
			return static_cast<JSObject>(file).GetPrivate<Titanium::Filesystem::File>();
		}
		return nullptr;
	}
	File_shared_ptr_t FilesystemModule::createTempFile(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		const auto script =
		"       var dir  = Ti.Filesystem.createTempDirectory();"
		"       var file = Ti.Filesystem.getFile(dir.nativePath, 'tifile' + Math.random().toString(36).substring(2) + '.tmp');"
		"       file.createFile();"
		"       file;";
		auto file = js_context.JSEvaluateScript(script);
		if (file.IsObject()) {
			return static_cast<JSObject>(file).GetPrivate<Titanium::Filesystem::File>();
		}
		return nullptr;
	}
	bool FilesystemModule::isExternalStoragePresent() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::isExternalStoragePresent: Unimplemented");
		return false;
	}
	FileStream_shared_ptr_t FilesystemModule::openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::openStream: Unimplemented");
		return nullptr;
	}
	std::string FilesystemModule::applicationCacheDirectory() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::applicationCacheDirectory: Unimplemented");
		return "";
	}
	std::string FilesystemModule::applicationDataDirectory() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::applicationDataDirectory: Unimplemented");
		return "";
	}
	std::string FilesystemModule::applicationDirectory() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::applicationDirectory: Unimplemented");
		return "";
	}
	std::string FilesystemModule::applicationSupportDirectory() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::applicationSupportDirectory: Unimplemented");
		return "";
	}
	std::string FilesystemModule::externalStorageDirectory() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::externalStorageDirectory: Unimplemented");
		return "";
	}
	std::string FilesystemModule::lineEnding() const TITANIUM_NOEXCEPT
	{
		return "\n";
	}
	std::string FilesystemModule::resourcesDirectory() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::resourcesDirectory: Unimplemented");
		return "";
	}
	std::string FilesystemModule::tempDirectory() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("File::tempDirectory: Unimplemented");
		return "";
	}

	void FilesystemModule::JSExportInitialize()
	{
		JSExport<FilesystemModule>::SetClassVersion(1);
		JSExport<FilesystemModule>::SetParent(JSExport<Module>::Class());
		JSExport<FilesystemModule>::AddFunctionProperty("getFile", std::mem_fn(&FilesystemModule::js_getFile));
		JSExport<FilesystemModule>::AddFunctionProperty("createTempDirectory", std::mem_fn(&FilesystemModule::js_createTempDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("createTempFile", std::mem_fn(&FilesystemModule::js_createTempFile));
		JSExport<FilesystemModule>::AddFunctionProperty("isExternalStoragePresent", std::mem_fn(&FilesystemModule::js_isExternalStoragePresent));
		JSExport<FilesystemModule>::AddFunctionProperty("openStream", std::mem_fn(&FilesystemModule::js_openStream));
		JSExport<FilesystemModule>::AddValueProperty("MODE_READ", std::mem_fn(&FilesystemModule::MODE_READ));
		JSExport<FilesystemModule>::AddValueProperty("MODE_WRITE", std::mem_fn(&FilesystemModule::MODE_WRITE));
		JSExport<FilesystemModule>::AddValueProperty("MODE_APPEND", std::mem_fn(&FilesystemModule::MODE_APPEND));
		JSExport<FilesystemModule>::AddValueProperty("separator", std::mem_fn(&FilesystemModule::js_separator));
		JSExport<FilesystemModule>::AddValueProperty("lineEnding", std::mem_fn(&FilesystemModule::js_lineEnding));
		JSExport<FilesystemModule>::AddValueProperty("applicationCacheDirectory", std::mem_fn(&FilesystemModule::js_applicationCacheDirectory));
		JSExport<FilesystemModule>::AddValueProperty("applicationDataDirectory", std::mem_fn(&FilesystemModule::js_applicationDataDirectory));
		JSExport<FilesystemModule>::AddValueProperty("applicationDirectory", std::mem_fn(&FilesystemModule::js_applicationDirectory));
		JSExport<FilesystemModule>::AddValueProperty("applicationSupportDirectory", std::mem_fn(&FilesystemModule::js_applicationSupportDirectory));
		JSExport<FilesystemModule>::AddValueProperty("externalStorageDirectory", std::mem_fn(&FilesystemModule::js_externalStorageDirectory));
		JSExport<FilesystemModule>::AddValueProperty("resourcesDirectory", std::mem_fn(&FilesystemModule::js_resourcesDirectory));
		JSExport<FilesystemModule>::AddValueProperty("tempDirectory", std::mem_fn(&FilesystemModule::js_tempDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("getSeparator", std::mem_fn(&FilesystemModule::js_getSeparator));
		JSExport<FilesystemModule>::AddFunctionProperty("getLineEnding", std::mem_fn(&FilesystemModule::js_getLineEnding));
		JSExport<FilesystemModule>::AddFunctionProperty("getApplicationCacheDirectory", std::mem_fn(&FilesystemModule::js_getApplicationCacheDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("getApplicationDataDirectory", std::mem_fn(&FilesystemModule::js_getApplicationDataDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("getApplicationDirectory", std::mem_fn(&FilesystemModule::js_getApplicationDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("getApplicationSupportDirectory", std::mem_fn(&FilesystemModule::js_getApplicationSupportDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("getExternalStorageDirectory", std::mem_fn(&FilesystemModule::js_getExternalStorageDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("getResourcesDirectory", std::mem_fn(&FilesystemModule::js_getResourcesDirectory));
		JSExport<FilesystemModule>::AddFunctionProperty("getTempDirectory", std::mem_fn(&FilesystemModule::js_getTempDirectory));
	}

	JSObject FilesystemModule::GetFilesystemObject(const JSContext& js_context) const TITANIUM_NOEXCEPT
	{
		JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Object_property = Titanium.GetProperty("Filesystem");
		TITANIUM_ASSERT(Object_property.IsObject());  // precondition
		return static_cast<JSObject>(Object_property);
	}

	JSValue FilesystemModule::js_getFile(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();

		JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue FS_property = Titanium.GetProperty("Filesystem");
		TITANIUM_ASSERT(FS_property.IsObject());  // precondition
		JSObject FS = static_cast<JSObject>(FS_property);

		JSValue sep_property = FS.GetProperty("separator");
		TITANIUM_ASSERT(sep_property.IsString());  // precondition
		std::string separator = static_cast<std::string>(sep_property);

		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();

		// join paths with separator
		std::ostringstream oss;
		const auto size = arguments.size();
		for (size_t i = 0; i < size; i++) {
			auto segment = static_cast<std::string>(arguments.at(i));
			oss << segment;
			if (i + 1 < size && segment.find(separator) != (segment.size() - 1)) {
				oss << separator;
			}
		}
		const auto object_ptr = filesystem_ptr->getFile(js_context, oss.str());
		if (object_ptr != nullptr) {
			return object_ptr->get_object();
		}
		return this_object.get_context().CreateUndefined();
	}

	JSValue FilesystemModule::js_createTempDirectory(const std::vector<JSValue>&, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		const auto object_ptr = filesystem_ptr->createTempDirectory(this_object.get_context());
		if (object_ptr != nullptr) {
			return object_ptr->get_object();
		}
		return this_object.get_context().CreateUndefined();
	}
	JSValue FilesystemModule::js_createTempFile(const std::vector<JSValue>&, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		const auto object_ptr = filesystem_ptr->createTempFile(this_object.get_context());
		if (object_ptr != nullptr) {
			return object_ptr->get_object();
		}
		return this_object.get_context().CreateUndefined();
	}
	JSValue FilesystemModule::js_isExternalStoragePresent(const std::vector<JSValue>&, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateBoolean(filesystem_ptr->isExternalStoragePresent());
	}
	JSValue FilesystemModule::js_openStream(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() < 2) {
			return this_object.get_context().CreateUndefined();
		}
		const auto _0 = arguments.at(0);
		const auto _1 = arguments.at(1);

		TITANIUM_ASSERT(_0.IsNumber());
		TITANIUM_ASSERT(_1.IsString());

		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();

		const auto modes = Titanium::Filesystem::Constants::to_MODE(static_cast<std::underlying_type<Titanium::Filesystem::MODE>::type>(_0));
		const std::string path = static_cast<std::string>(_1);
		const auto object_ptr = filesystem_ptr->openStream(modes, path);
		if (object_ptr != nullptr) {
			return object_ptr->get_object();
		}
		return this_object.get_context().CreateUndefined();
	}

	JSValue FilesystemModule::js_getSeparator(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->separator());
	}
	JSValue FilesystemModule::js_getApplicationCacheDirectory(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationCacheDirectory());
	}
	JSValue FilesystemModule::js_getApplicationDataDirectory(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationDataDirectory());
	}
	JSValue FilesystemModule::js_getApplicationDirectory(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationDirectory());
	}
	JSValue FilesystemModule::js_getApplicationSupportDirectory(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationSupportDirectory());
	}
	JSValue FilesystemModule::js_getExternalStorageDirectory(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->externalStorageDirectory());
	}
	JSValue FilesystemModule::js_getLineEnding(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->lineEnding());
	}
	JSValue FilesystemModule::js_getResourcesDirectory(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->resourcesDirectory());
	}
	JSValue FilesystemModule::js_getTempDirectory(const std::vector<JSValue>&, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetFilesystemObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->tempDirectory());
	}

	JSValue FilesystemModule::js_separator() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(separator());
	}
	JSValue FilesystemModule::js_applicationCacheDirectory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(applicationCacheDirectory());
	}
	JSValue FilesystemModule::js_applicationDataDirectory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(applicationDataDirectory());
	}
	JSValue FilesystemModule::js_applicationDirectory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(applicationDirectory());
	}
	JSValue FilesystemModule::js_applicationSupportDirectory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(applicationSupportDirectory());
	}
	JSValue FilesystemModule::js_externalStorageDirectory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(externalStorageDirectory());
	}
	JSValue FilesystemModule::js_lineEnding() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(lineEnding());
	}
	JSValue FilesystemModule::js_resourcesDirectory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(resourcesDirectory());
	}
	JSValue FilesystemModule::js_tempDirectory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(tempDirectory());
	}

}  // namespace Titanium
