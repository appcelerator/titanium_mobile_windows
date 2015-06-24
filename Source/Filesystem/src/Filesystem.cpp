/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Filesystem.hpp"
#include <iostream>
#include <objbase.h>
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	FilesystemModule::FilesystemModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::FilesystemModule(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::FilesystemModule::ctor");
	}

	FilesystemModule::~FilesystemModule()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::FilesystemModule::dtor");
	}

	void FilesystemModule::JSExportInitialize()
	{
		JSExport<FilesystemModule>::SetClassVersion(1);
		JSExport<FilesystemModule>::SetParent(JSExport<Titanium::FilesystemModule>::Class());
	}

	std::string FilesystemModule::separator() const TITANIUM_NOEXCEPT
	{
		return "\\";
	}

	bool FilesystemModule::isExternalStoragePresent() TITANIUM_NOEXCEPT
	{
		return !this->externalStorageDirectory().empty();
	}

	std::shared_ptr<Titanium::Filesystem::FileStream> FilesystemModule::openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Filesystem.openStream is not implemented yet");
		return nullptr;
	}

	std::string FilesystemModule::applicationCacheDirectory() const TITANIUM_NOEXCEPT
	{
#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
		const auto value = Windows::Storage::ApplicationData::Current->LocalCacheFolder->Path;
		return TitaniumWindows::Utility::ConvertString(value) + separator(); // FIXME Only append separator if not already there!
#else
		TITANIUM_LOG_WARN("Filesystem.applicationCacheDirectory is not supported on Windows Store.");
		return "";
#endif
	}

	std::string FilesystemModule::applicationDataDirectory() const TITANIUM_NOEXCEPT
	{
		const auto value = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
		return TitaniumWindows::Utility::ConvertString(value) + separator(); // FIXME Only append separator if not already there!
	}

	std::string FilesystemModule::applicationDirectory() const TITANIUM_NOEXCEPT
	{
		const auto value = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
		return TitaniumWindows::Utility::ConvertString(value) + separator(); // FIXME Only append separator if not already there!
	}

	std::string FilesystemModule::applicationSupportDirectory() const TITANIUM_NOEXCEPT
	{
		// Need to check exception here because this requires "Documents" capability
		try {
			const auto value = Windows::Storage::KnownFolders::DocumentsLibrary->Path;
			return TitaniumWindows::Utility::ConvertString(value) + separator(); // FIXME Only append separator if not already there!
		} catch (Platform::AccessDeniedException^ e) {
			return "";
		}
	}

	std::string FilesystemModule::externalStorageDirectory() const TITANIUM_NOEXCEPT
	{
		// Need to check exception here because this requires "Removable Storage" capability
		try {
			const auto value = Windows::Storage::KnownFolders::RemovableDevices->Path;
			return TitaniumWindows::Utility::ConvertString(value) + separator(); // FIXME Only append separator if not already there!
		} catch (Platform::AccessDeniedException^ e) {
			return "";
		}
	}

	std::string FilesystemModule::lineEnding() const TITANIUM_NOEXCEPT
	{
		return "\r\n";
	}

	std::string FilesystemModule::resourcesDirectory() const TITANIUM_NOEXCEPT
	{
		const auto value = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
		return TitaniumWindows::Utility::ConvertString(value) + separator(); // FIXME Only append separator if not already there!
	}

	std::string FilesystemModule::tempDirectory() const TITANIUM_NOEXCEPT
	{
		const auto value = Windows::Storage::ApplicationData::Current->TemporaryFolder->Path;
		return TitaniumWindows::Utility::ConvertString(value) + separator(); // FIXME Only append separator if not already there!
	}
}  // namespace TitaniumWindows
