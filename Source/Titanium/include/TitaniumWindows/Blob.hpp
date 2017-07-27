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

	/*!
	  @class Blob
	  @ingroup Titanium.Blob

	  @discussion This is the Titanium.Blob implementation for Windows.
    */
	class TITANIUMWINDOWS_EXPORT Blob final : public Titanium::Blob, public JSExport<Blob>
	{
	public:
		TITANIUM_FUNCTION_UNIMPLEMENTED(imageWithAlpha);
		TITANIUM_FUNCTION_UNIMPLEMENTED(imageWithRoundedCorner);
		TITANIUM_FUNCTION_UNIMPLEMENTED(imageWithTransparentBorder);
		::Platform::Guid getImageEncoder();

		virtual void construct(const std::vector<std::uint8_t>& data, const std::string& mimetype) TITANIUM_NOEXCEPT;
		virtual void construct(Windows::Storage::StorageFile^ file) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract transformImage
		  @param width Width to resize
		  @param height Height to resize
		  @param crop options (width, height, x, y)
		  @discussion Creates a new blob by resizing/scaling/cropping the underlying image to the specified dimensions.
		*/
		virtual std::shared_ptr<Titanium::Blob> transformImage(const std::uint32_t& scaledWidth, const std::uint32_t scaledHeight, const Titanium::UI::Dimension& crop) TITANIUM_NOEXCEPT override;

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
