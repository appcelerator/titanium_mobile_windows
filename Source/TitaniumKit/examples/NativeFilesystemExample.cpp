/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeFilesystemExample.hpp"
#include <iostream>

NativeFilesystemExample::NativeFilesystemExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::FilesystemModule(js_context)
{
}

void NativeFilesystemExample::JSExportInitialize()
{
	JSExport<NativeFilesystemExample>::SetClassVersion(1);
	JSExport<NativeFilesystemExample>::SetParent(JSExport<Titanium::FilesystemModule>::Class());
}

JSValue NativeFilesystemExample::getFile(const std::string&) TITANIUM_NOEXCEPT
{
	return get_context().CreateNull();
}
JSValue NativeFilesystemExample::createTempDirectory() TITANIUM_NOEXCEPT
{
	return get_context().CreateNull();
}
JSValue NativeFilesystemExample::createTempFile() TITANIUM_NOEXCEPT
{
	return get_context().CreateNull();
}
bool NativeFilesystemExample::isExternalStoragePresent() TITANIUM_NOEXCEPT
{
	return false;
}
std::shared_ptr<Titanium::Filesystem::FileStream> NativeFilesystemExample::openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT
{
	return nullptr;
}
std::string NativeFilesystemExample::separator() const TITANIUM_NOEXCEPT
{
	return "/";
}
std::string NativeFilesystemExample::applicationCacheDirectory() const TITANIUM_NOEXCEPT
{
	return "";
}
std::string NativeFilesystemExample::applicationDataDirectory() const TITANIUM_NOEXCEPT
{
	return "";
}
std::string NativeFilesystemExample::applicationDirectory() const TITANIUM_NOEXCEPT
{
	return "";
}
std::string NativeFilesystemExample::applicationSupportDirectory() const TITANIUM_NOEXCEPT
{
	return "";
}
std::string NativeFilesystemExample::externalStorageDirectory() const TITANIUM_NOEXCEPT
{
	return "";
}
std::string NativeFilesystemExample::lineEnding() const TITANIUM_NOEXCEPT
{
	return "\n";
}
std::string NativeFilesystemExample::resourcesDirectory() const TITANIUM_NOEXCEPT
{
	return "";
}
std::string NativeFilesystemExample::tempDirectory() const TITANIUM_NOEXCEPT
{
	return "";
}
