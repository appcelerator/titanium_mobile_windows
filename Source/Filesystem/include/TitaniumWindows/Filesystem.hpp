/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_FILESYSTEMMODULE_HPP_
#define _TITANIUMWINDOWS_FILESYSTEMMODULE_HPP_

#include "TitaniumWindows_Filesystem_EXPORT.h"
#include "Titanium/FilesystemModule.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium.FilesystemModule implementation for Windows.
    */
	class TITANIUMWINDOWS_FILESYSTEM_EXPORT FilesystemModule final : public Titanium::FilesystemModule, public JSExport<FilesystemModule>
	{
	public:
		FilesystemModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~FilesystemModule();
		FilesystemModule(const FilesystemModule&) = default;
		FilesystemModule& operator=(const FilesystemModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		FilesystemModule(FilesystemModule&&) = default;
		FilesystemModule& operator=(FilesystemModule&&) = default;
#endif

		static void JSExportInitialize();

		virtual bool isExternalStoragePresent() TITANIUM_NOEXCEPT;
		virtual std::shared_ptr<Titanium::Filesystem::FileStream> openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const std::string& path) TITANIUM_NOEXCEPT;

		virtual std::string separator() const TITANIUM_NOEXCEPT;
		virtual std::string applicationCacheDirectory() const TITANIUM_NOEXCEPT;
		virtual std::string applicationDataDirectory() const TITANIUM_NOEXCEPT;
		virtual std::string applicationDirectory() const TITANIUM_NOEXCEPT;
		virtual std::string applicationSupportDirectory() const TITANIUM_NOEXCEPT;
		virtual std::string externalStorageDirectory() const TITANIUM_NOEXCEPT;
		virtual std::string lineEnding() const TITANIUM_NOEXCEPT;
		virtual std::string resourcesDirectory() const TITANIUM_NOEXCEPT;
		virtual std::string tempDirectory() const TITANIUM_NOEXCEPT;

	protected:
	private:
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_FILESYSTEMMODULE_HPP_
