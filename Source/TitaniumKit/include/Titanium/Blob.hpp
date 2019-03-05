/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_BLOB_HPP_
#define _TITANIUM_BLOB_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	namespace Filesystem
	{
		class File;
	}

	using File_shared_ptr_t = std::shared_ptr<Filesystem::File>;

	namespace BlobModule
	{
		enum class TYPE {
			IMAGE = 0,
			FILE = 1,
			DATA = 2
		};
	}

	namespace UI
	{
		struct Dimension;
	}

	/*!
	  @class
	  @discussion This is the Titanium.Blob module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Blob
	*/
	class TITANIUMKIT_EXPORT Blob : public Module, public JSExport<Blob>
	{
	public:
		/*!
		  @method
		  @abstract get_length
		  @discussion Length of this blob in bytes.
		*/
		virtual uint32_t get_length() const TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract get_file
		  @discussion File object represented by this blob, or null if this blob is not
		  associated with a file.
		*/
		virtual File_shared_ptr_t get_file() const TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract get_height
		  @discussion If this blob represents an image, this is the height of the image in pixels.
		*/
		virtual uint32_t get_height() const TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract get_mimeType
		  @discussion Mime type of the data in this blob.
		*/
		virtual std::string get_mimeType() const TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract get_nativePath
		  @discussion If this blob represents a File, this is the file URL that represents it.
		*/
		virtual std::string get_nativePath() const TITANIUM_NOEXCEPT;
		virtual void set_nativePath(const std::string& nativePath) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract get_size
		  @discussion Size of the blob in pixels (for image blobs) or bytes (for all other blobs).
		*/
		virtual uint32_t get_size() const TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract get_text
		  @discussion UTF-8 string representation of the data in this blob.
		*/
		virtual std::string get_text() const TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract get_width
		  @discussion If this blob represents an image, this is the width of the image in pixels.
		*/
		virtual uint32_t get_width() const TITANIUM_NOEXCEPT;
		/*!
		  @method
		  @abstract append
		  @discussion Appends the data from another blob to this blob.
		*/
		virtual void append(const std::shared_ptr<Blob>&) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract imageAsCropped
		  @discussion Creates a new blob by cropping the underlying image to the specified dimensions.
		*/
		virtual std::shared_ptr<Blob> imageAsCropped(const Titanium::UI::Dimension&) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract imageAsResized
		  @discussion Creates a new blob by resizing and scaling the underlying image to the specified dimensions.
		*/
		virtual std::shared_ptr<Blob> imageAsResized(const std::uint32_t&, const std::uint32_t&) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract imageAsThumbnail
		  @discussion Returns a thumbnail version of the underlying image, optionally with a border and rounded corners.
		*/
		virtual std::shared_ptr<Blob> imageAsThumbnail(const std::uint32_t&, const std::uint32_t&, const double&) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract imageWithAlpha
		  @discussion Returns a copy of the underlying image with an added alpha channel.
		*/
		virtual std::shared_ptr<Blob> imageWithAlpha() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract imageWithRoundedCorner
		  @discussion Returns a copy of the underlying image with rounded corners added.
		*/
		virtual std::shared_ptr<Blob> imageWithRoundedCorner(const std::uint32_t&, const std::uint32_t&) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract imageWithTransparentBorder
		  @discussion Returns a copy of the underlying image with an added transparent border.
		*/
		virtual std::shared_ptr<Blob> imageWithTransparentBorder(const std::uint32_t&) TITANIUM_NOEXCEPT;

		/*!
		@method
		@abstract transformImage
		@param width Width to resize
		@param height Height to resize
		@param crop options (width, height, x, y)
		@discussion Creates a new blob by resizing/scaling/cropping the underlying image to the specified dimensions.
		*/
		virtual std::shared_ptr<Titanium::Blob> transformImage(const std::uint32_t& scaledWidth, const std::uint32_t scaledHeight, const Titanium::UI::Dimension& crop) TITANIUM_NOEXCEPT;

		virtual void construct(const std::vector<std::uint8_t>& data) TITANIUM_NOEXCEPT;
		virtual std::vector<std::uint8_t> getData() TITANIUM_NOEXCEPT;

		virtual void release() TITANIUM_NOEXCEPT;

		Blob(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~Blob() = default;
		Blob(const Blob&) = default;
		Blob& operator=(const Blob&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Blob(Blob&&) = default;
		Blob& operator=(Blob&&) = default;
#endif

		static void JSExportInitialize();

		TITANIUM_PROPERTY_READONLY_DEF(length);
		TITANIUM_PROPERTY_READONLY_DEF(file);
		TITANIUM_PROPERTY_READONLY_DEF(height);
		TITANIUM_PROPERTY_READONLY_DEF(mimeType);
		TITANIUM_PROPERTY_READONLY_DEF(nativePath);
		TITANIUM_PROPERTY_READONLY_DEF(size);
		TITANIUM_PROPERTY_READONLY_DEF(text);
		TITANIUM_PROPERTY_READONLY_DEF(width);

		TITANIUM_FUNCTION_DEF(append);
		TITANIUM_FUNCTION_DEF(getFile);
		TITANIUM_FUNCTION_DEF(getHeight);
		TITANIUM_FUNCTION_DEF(getLength);
		TITANIUM_FUNCTION_DEF(getMimeType);
		TITANIUM_FUNCTION_DEF(getNativePath);
		TITANIUM_FUNCTION_DEF(getSize);
		TITANIUM_FUNCTION_DEF(getText);
		TITANIUM_FUNCTION_DEF(getWidth);
		TITANIUM_FUNCTION_DEF(toString);
		TITANIUM_FUNCTION_DEF(imageAsCropped);
		TITANIUM_FUNCTION_DEF(imageAsResized);
		TITANIUM_FUNCTION_DEF(imageAsThumbnail);
		TITANIUM_FUNCTION_DEF(imageWithAlpha);
		TITANIUM_FUNCTION_DEF(imageWithRoundedCorner);
		TITANIUM_FUNCTION_DEF(imageWithTransparentBorder);

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		std::string path_;
		std::string mimetype_;
		uint32_t width_;
		uint32_t height_;
		BlobModule::TYPE type_;
		std::vector<std::uint8_t> data_;
#pragma warning(pop)
	};
}  // namespace Titanium

#endif  // _TITANIUM_BLOB_HPP_
