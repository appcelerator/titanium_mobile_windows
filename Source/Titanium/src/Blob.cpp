/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Blob.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <boost/algorithm/string/predicate.hpp>

namespace TitaniumWindows
{
	Blob::Blob(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::Blob(js_context)
	{
	}

	Blob::~Blob()
	{
	}

	void Blob::JSExportInitialize()
	{
		JSExport<Blob>::SetClassVersion(1);
		JSExport<Blob>::SetParent(JSExport<Titanium::Blob>::Class());
	}

	void Blob::construct(Windows::Storage::StorageFile^ file)
	{
		width_ = 0;
		height_ = 0;
		data_ = TitaniumWindows::Utility::GetContentFromFile(file);
		path_ = TitaniumWindows::Utility::ConvertString(file->Path);

		mimetype_ = TitaniumWindows::Utility::ConvertString(file->ContentType);
		if (mimetype_ == "application/x-javascript") { // handle special cases to match other platforms
			mimetype_ = "text/javascript";
		}
		if (boost::starts_with(mimetype_, "image/")) {
			// TODO Determine width/height!
			//create_task(file->OpenReadAsync()).then();
			//auto decoder = Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(getImageDecoder(), stream);
		}

		this->type_ = Titanium::BlobModule::TYPE::FILE;
	}

	::Platform::Guid Blob::getImageEncoder()
	{
		if (mimetype_ == "image/png") {
			return Windows::Graphics::Imaging::BitmapEncoder::PngEncoderId;
		} else if (mimetype_ == "image/jpg" || mimetype_ == "image/jpeg" || mimetype_ == "image/pjpeg") {
			return Windows::Graphics::Imaging::BitmapEncoder::JpegEncoderId;
		} else if (mimetype_ == "image/tiff") {
			return Windows::Graphics::Imaging::BitmapEncoder::TiffEncoderId;
		} else if (mimetype_ == "image/gif") {
			return Windows::Graphics::Imaging::BitmapEncoder::GifEncoderId;
		} else { // image/bmp?
			return Windows::Graphics::Imaging::BitmapEncoder::BmpEncoderId;
		}
	}
}  // namespace TitaniumWindows
