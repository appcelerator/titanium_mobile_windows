/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Filesystem.hpp"
#include "Titanium/Filesystem/FileStream.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <windows.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include "TitaniumWindows/LogForwarder.hpp"
#include <iostream>
#include <objbase.h>
#include <boost/algorithm/string/predicate.hpp>

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

	std::string FilesystemModule::applicationCacheDirectory() const TITANIUM_NOEXCEPT
	{
		static std::string value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = TitaniumWindows::Utility::ConvertString(Windows::Storage::ApplicationData::Current->LocalCacheFolder->Path);
			if (!boost::ends_with(value, "\\")) {
				value = value + "\\";
			}
		});
		return value;
	}

	std::string FilesystemModule::applicationDataDirectory() const TITANIUM_NOEXCEPT
	{
		static std::string value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = TitaniumWindows::Utility::ConvertString(Windows::Storage::ApplicationData::Current->LocalFolder->Path);
			if (!boost::ends_with(value, "\\")) {
				value = value + "\\";
			}
		});
		return value;
	}

	std::string FilesystemModule::applicationDirectory() const TITANIUM_NOEXCEPT
	{
		static std::string value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = TitaniumWindows::Utility::ConvertString(Windows::ApplicationModel::Package::Current->InstalledLocation->Path);
			if (!boost::ends_with(value, "\\")) {
				value = value + "\\";
			}
		});

		return value;
	}

	std::string FilesystemModule::applicationSupportDirectory() const TITANIUM_NOEXCEPT
	{
		// Need to check exception here because this requires "Documents" capability
		try {
			static std::string value;
			static std::once_flag of;
			std::call_once(of, [=] {
				value = TitaniumWindows::Utility::ConvertString(Windows::Storage::KnownFolders::DocumentsLibrary->Path);
				if (!boost::ends_with(value, "\\")) {
					value = value + "\\";
				}
			});

			return value;
		} catch (Platform::AccessDeniedException^ e) {
			return "";
		}
	}

	std::string FilesystemModule::externalStorageDirectory() const TITANIUM_NOEXCEPT
	{
		// Need to check exception here because this requires "Removable Storage" capability
		try {
			static std::string value;
			static std::once_flag of;
			std::call_once(of, [=] {
				const auto path = Windows::Storage::KnownFolders::RemovableDevices->Path;
				if (!path->IsEmpty()) {
					value = TitaniumWindows::Utility::ConvertString(path);
				}
				if (!boost::ends_with(value, "\\")) {
					value = value + "\\";
				}
			});
			return value;
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
		static std::string value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = TitaniumWindows::Utility::ConvertString(Windows::ApplicationModel::Package::Current->InstalledLocation->Path);
			if (!boost::ends_with(value, "\\")) {
				value = value + "\\";
			}
		});
		return value;
	}

	std::string FilesystemModule::tempDirectory() const TITANIUM_NOEXCEPT
	{
		static std::string value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = TitaniumWindows::Utility::ConvertString(Windows::Storage::ApplicationData::Current->TemporaryFolder->Path);
			if (!boost::ends_with(value, "\\")) {
				value = value + "\\";
			}
		});
		return value;
	}
}  // namespace TitaniumWindows
