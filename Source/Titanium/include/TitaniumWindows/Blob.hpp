/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_BLOB_HPP_
#define _TITANIUMWINDOWS_BLOB_HPP_

#include "TitaniumWindows_EXPORT.h"
#include "Titanium/Blob.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	using File_shared_ptr_t = std::shared_ptr<Titanium::Filesystem::File>;

	/*!
	  @class

	  @discussion This is the Titanium.Blob implementation for Windows.
    */
	class TITANIUMWINDOWS_EXPORT Blob final : public Titanium::Blob, public JSExport<Blob>
	{
	public:
		::Platform::Guid getImageEncoder();

		void construct(Windows::Storage::StorageFile^ file);

		Blob(const JSContext&) TITANIUM_NOEXCEPT;
		virtual ~Blob();
		Blob(const Blob&) = default;
		Blob& operator=(const Blob&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Blob(Blob&&) = default;
		Blob& operator=(Blob&&) = default;
#endif

		static void JSExportInitialize();
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_BLOB_HPP_
