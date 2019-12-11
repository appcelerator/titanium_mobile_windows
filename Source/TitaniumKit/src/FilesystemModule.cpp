/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/FilesystemModule.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/Filesystem/FileStream.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <sstream>

namespace Titanium
{
	JSFunction FilesystemModule::createOpenStreamFunction(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		const std::string script = R"JS(
			var path = Array.prototype.slice.call(arguments, 1).join(Ti.Filesystem.separator);
			var file = Ti.Filesystem.getFile(path);
			if (file.exists()) {
				if (mode == Ti.Filesystem.MODE_WRITE) {
					file.deleteFile();
					file.createFile();
				}
				return file.open(mode);
			} else {
				if (mode == Ti.Filesystem.MODE_WRITE || mode == Ti.Filesystem.MODE_APPEND) {
					file.createFile();
					return file.open(mode);
				}
				throw new Error('Unable to open stream for MODE_READ');
			}
		)JS";
		return js_context.CreateFunction(script, { JSString("mode") });
	}

	FilesystemModule::FilesystemModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti.Filesystem")
	    , openStreamFunc__(createOpenStreamFunction(js_context))
	{
	}

	TITANIUM_PROPERTY_GETTER(FilesystemModule, MODE_READ)
	{
		return get_context().CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::READ));
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, MODE_WRITE)
	{
		return get_context().CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::WRITE));
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, MODE_APPEND)
	{
		return get_context().CreateNumber(Titanium::Filesystem::Constants::to_underlying_type(Titanium::Filesystem::MODE::APPEND));
	}

	std::string FilesystemModule::separator() const TITANIUM_NOEXCEPT
	{
		return "/";
	}

	File_shared_ptr_t FilesystemModule::getFile(const JSContext& js_context, const std::string& path) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Filesystem::getFile: ", path);

		JSObject FS = GetStaticObject(js_context);

		JSValue File_property = FS.GetProperty("File");
		TITANIUM_ASSERT(File_property.IsObject());  // precondition
		JSObject File = static_cast<JSObject>(File_property);

		return File.CallAsConstructor(get_context().CreateString(path)).GetPrivate<Titanium::Filesystem::File>();
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
		TITANIUM_ADD_FUNCTION(FilesystemModule, getFile);
		TITANIUM_ADD_FUNCTION(FilesystemModule, createTempDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, createTempFile);
		TITANIUM_ADD_FUNCTION(FilesystemModule, isExternalStoragePresent);
		TITANIUM_ADD_FUNCTION(FilesystemModule, openStream);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, File);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, FileStream);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, MODE_READ);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, MODE_WRITE);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, MODE_APPEND);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, separator);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, lineEnding);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, applicationCacheDirectory);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, applicationDataDirectory);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, applicationDirectory);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, applicationSupportDirectory);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, externalStorageDirectory);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, resourcesDirectory);
		TITANIUM_ADD_CONSTANT_PROPERTY(FilesystemModule, tempDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getSeparator);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getLineEnding);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getApplicationCacheDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getApplicationDataDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getApplicationDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getApplicationSupportDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getExternalStorageDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getResourcesDirectory);
		TITANIUM_ADD_FUNCTION(FilesystemModule, getTempDirectory);
	}

	JSObject FilesystemModule::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		static JSObject cached = js_context.CreateObject();
		static std::once_flag of;
		std::call_once(of, [=] {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Object_property = Titanium.GetProperty("Filesystem");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			cached = static_cast<JSObject>(Object_property);
		});
		return cached;
	}

	TITANIUM_FUNCTION(FilesystemModule, getFile)
	{
		const auto js_context = this_object.get_context();

		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		std::string separator = filesystem_ptr->separator();

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

	TITANIUM_FUNCTION(FilesystemModule, createTempDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		const auto object_ptr = filesystem_ptr->createTempDirectory(this_object.get_context());
		if (object_ptr != nullptr) {
			return object_ptr->get_object();
		}
		return this_object.get_context().CreateUndefined();
	}
	TITANIUM_FUNCTION(FilesystemModule, createTempFile)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		const auto object_ptr = filesystem_ptr->createTempFile(this_object.get_context());
		if (object_ptr != nullptr) {
			return object_ptr->get_object();
		}
		return this_object.get_context().CreateUndefined();
	}
	TITANIUM_FUNCTION(FilesystemModule, isExternalStoragePresent)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateBoolean(filesystem_ptr->isExternalStoragePresent());
	}
	TITANIUM_FUNCTION(FilesystemModule, openStream)
	{
		return openStreamFunc__(arguments, get_object());
	}

	TITANIUM_FUNCTION(FilesystemModule, getSeparator)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->separator());
	}
	TITANIUM_FUNCTION(FilesystemModule, getApplicationCacheDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationCacheDirectory());
	}
	TITANIUM_FUNCTION(FilesystemModule, getApplicationDataDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationDataDirectory());
	}
	TITANIUM_FUNCTION(FilesystemModule, getApplicationDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationDirectory());
	}
	TITANIUM_FUNCTION(FilesystemModule, getApplicationSupportDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->applicationSupportDirectory());
	}
	TITANIUM_FUNCTION(FilesystemModule, getExternalStorageDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->externalStorageDirectory());
	}
	TITANIUM_FUNCTION(FilesystemModule, getLineEnding)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->lineEnding());
	}
	TITANIUM_FUNCTION(FilesystemModule, getResourcesDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->resourcesDirectory());
	}
	TITANIUM_FUNCTION(FilesystemModule, getTempDirectory)
	{
		const auto js_context = this_object.get_context();
		const auto filesystem_ptr = GetStaticObject(js_context).GetPrivate<FilesystemModule>();
		return this_object.get_context().CreateString(filesystem_ptr->tempDirectory());
	}

	TITANIUM_PROPERTY_GETTER(FilesystemModule, separator)
	{
		return get_context().CreateString(separator());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, applicationCacheDirectory)
	{
		return get_context().CreateString(applicationCacheDirectory());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, applicationDataDirectory)
	{
		return get_context().CreateString(applicationDataDirectory());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, applicationDirectory)
	{
		return get_context().CreateString(applicationDirectory());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, applicationSupportDirectory)
	{
		return get_context().CreateString(applicationSupportDirectory());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, externalStorageDirectory)
	{
		return get_context().CreateString(externalStorageDirectory());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, lineEnding)
	{
		return get_context().CreateString(lineEnding());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, resourcesDirectory)
	{
		return get_context().CreateString(resourcesDirectory());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, tempDirectory)
	{
		return get_context().CreateString(tempDirectory());
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, File)
	{
		return get_context().CreateObject(file__);
	}
	TITANIUM_PROPERTY_GETTER(FilesystemModule, FileStream)
	{
		return get_context().CreateObject(filestream__);
	}

	FilesystemModule& FilesystemModule::FileClass(const JSClass& file) TITANIUM_NOEXCEPT
	{
		file__ = file;
		return *this;
	}

	FilesystemModule& FilesystemModule::FileStreamClass(const JSClass& filestream) TITANIUM_NOEXCEPT
	{
		filestream__ = filestream;
		return *this;
	}
}  // namespace Titanium
