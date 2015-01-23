/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Blob.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>
#include <objbase.h>
#include "File.hpp"

namespace TitaniumWindows
{
	Blob::Blob(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::Blob(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Blob::ctor Initialize");
	}

	Blob::Blob(const Blob& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Titanium::Blob(rhs, arguments)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Blob::ctor CallAsConstructor");
	}

	Blob::~Blob()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Blob::dtor");
	}

	void Blob::JSExportInitialize()
	{
		JSExport<Blob>::SetClassVersion(1);
		JSExport<Blob>::SetParent(JSExport<Titanium::Blob>::Class());
	}

	void Blob::construct(Windows::Storage::StorageFile^ file)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Blob::construct");
		data_ = TitaniumWindows::Utility::GetContentFromFile(file);
		path_ = TitaniumWindows::Utility::ConvertString(file->Path);

		std::string path = path_;
		mimetype_ = TitaniumWindows::Utility::MimeTypeForExtension(path);

		this->type_ = BlobModule::TYPE::FILE;
	}

	std::vector<unsigned char> Blob::getData()
	{
		return data_;
	}

	::Platform::Guid Blob::getImageEncoder()
	{
		if (mimetype_ == "image/png") {
			return Windows::Graphics::Imaging::BitmapEncoder::PngEncoderId;
		} else if (mimetype_ == "image/jpg") {
			return Windows::Graphics::Imaging::BitmapEncoder::PngEncoderId;
		} else {
			return Windows::Graphics::Imaging::BitmapEncoder::BmpEncoderId;
		}
	}

	unsigned Blob::get_length() const TITANIUM_NOEXCEPT
	{
		return data_.size();
	}

	JSValue Blob::get_file() const TITANIUM_NOEXCEPT
	{
		if (path_.size() > 0) {
			auto File = get_context().CreateObject(JSExport<TitaniumWindows::Filesystem::File>::Class());
			return File.CallAsConstructor(path_);
		} else {
			return get_context().CreateNull();
		}
	}

	unsigned Blob::get_height() const TITANIUM_NOEXCEPT
	{
		return height_;
	}

	std::string Blob::get_mimeType() const TITANIUM_NOEXCEPT
	{
		return mimetype_;
	}

	std::string Blob::get_nativePath() const TITANIUM_NOEXCEPT
	{
		return path_;
	}

	unsigned Blob::get_size() const TITANIUM_NOEXCEPT
	{
		if (type_ == BlobModule::TYPE::IMAGE) {
			return width_ * height_;
		} else {
			return get_length();
		}
	}

	std::string Blob::get_text() const TITANIUM_NOEXCEPT
	{
		if (type_ == BlobModule::TYPE::IMAGE) {
			return "";
		} else {
			return std::string(data_.begin(), data_.end());
		}
	}

	unsigned Blob::get_width() const TITANIUM_NOEXCEPT
	{
		return width_;
	}

	void Blob::append(std::shared_ptr<Titanium::Blob>& other) TITANIUM_NOEXCEPT
	{
		auto blob = std::dynamic_pointer_cast<Blob>(other).get();
		const auto b = blob->getData();
		data_.reserve(data_.size() + b.size());
		data_.insert(data_.end(), b.begin(), b.end());
	}
}  // namespace TitaniumWindows
