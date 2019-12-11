/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/UI/Dimension.hpp"
#include <type_traits>

namespace Titanium
{
	Blob::Blob(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti.Blob")
	{
	}

	void Blob::construct(const std::vector<std::uint8_t>& data) TITANIUM_NOEXCEPT
	{
		height_ = 0;
		width_ = 0;
		path_ = "";
		data_ = data;
		mimetype_ = "application/octet-stream";

		this->type_ = Titanium::BlobModule::TYPE::DATA;
	}

	std::vector<std::uint8_t> Blob::getData() TITANIUM_NOEXCEPT
	{
		return data_;
	}

	void Blob::JSExportInitialize()
	{
		JSExport<Blob>::SetClassVersion(1);
		JSExport<Blob>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_PROPERTY_READONLY(Blob, file);
		TITANIUM_ADD_PROPERTY_READONLY(Blob, height);
		TITANIUM_ADD_PROPERTY_READONLY(Blob, length);
		TITANIUM_ADD_PROPERTY_READONLY(Blob, mimeType);
		TITANIUM_ADD_PROPERTY_READONLY(Blob, nativePath);
		TITANIUM_ADD_PROPERTY_READONLY(Blob, size);
		TITANIUM_ADD_PROPERTY_READONLY(Blob, text);
		TITANIUM_ADD_PROPERTY_READONLY(Blob, width);

		TITANIUM_ADD_FUNCTION(Blob, getFile);
		TITANIUM_ADD_FUNCTION(Blob, getHeight);
		TITANIUM_ADD_FUNCTION(Blob, getLength);
		TITANIUM_ADD_FUNCTION(Blob, getMimeType);
		TITANIUM_ADD_FUNCTION(Blob, getNativePath);
		TITANIUM_ADD_FUNCTION(Blob, getSize);
		TITANIUM_ADD_FUNCTION(Blob, getText);
		TITANIUM_ADD_FUNCTION(Blob, getWidth);
		TITANIUM_ADD_FUNCTION(Blob, append);
		TITANIUM_ADD_FUNCTION(Blob, toString);
		TITANIUM_ADD_FUNCTION(Blob, imageAsCropped);
		TITANIUM_ADD_FUNCTION(Blob, imageAsResized);
		TITANIUM_ADD_FUNCTION(Blob, imageAsThumbnail);
		TITANIUM_ADD_FUNCTION(Blob, imageWithAlpha);
		TITANIUM_ADD_FUNCTION(Blob, imageWithRoundedCorner);
		TITANIUM_ADD_FUNCTION(Blob, imageWithTransparentBorder);
	}

	uint32_t Blob::get_length() const TITANIUM_NOEXCEPT
	{
		return static_cast<uint32_t>(data_.size());
	}

	File_shared_ptr_t Blob::get_file() const TITANIUM_NOEXCEPT
	{
		if (path_.size() > 0) {
			JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Filesystem_property = Titanium.GetProperty("Filesystem");
			TITANIUM_ASSERT(Filesystem_property.IsObject());  // precondition
			JSObject Filesystem = static_cast<JSObject>(Filesystem_property);

			JSValue File_property = Filesystem.GetProperty("File");
			TITANIUM_ASSERT(File_property.IsObject());  // precondition
			JSObject File = static_cast<JSObject>(File_property);

			return File.CallAsConstructor(get_context().CreateString(get_nativePath())).GetPrivate<Filesystem::File>();
		}
		return nullptr;
	}

	uint32_t Blob::get_height() const TITANIUM_NOEXCEPT
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

	void Blob::set_nativePath(const std::string& nativePath) TITANIUM_NOEXCEPT
	{
		path_ = nativePath;
	}

	uint32_t Blob::get_size() const TITANIUM_NOEXCEPT
	{
		if (type_ == Titanium::BlobModule::TYPE::IMAGE) {
			return get_width() * get_height();
		} else {
			return get_length();
		}
	}

	std::string Blob::get_text() const TITANIUM_NOEXCEPT
	{
		if (type_ == Titanium::BlobModule::TYPE::IMAGE) {
			return "";
		} else {
			return std::string(data_.begin(), data_.end());
		}
	}

	uint32_t Blob::get_width() const TITANIUM_NOEXCEPT
	{
		return width_;
	}

	void Blob::append(const std::shared_ptr<Blob>& other) TITANIUM_NOEXCEPT
	{
		auto blob = std::dynamic_pointer_cast<Blob>(other).get();
		const auto b = blob->getData();
		data_.reserve(data_.size() + b.size());
		data_.insert(data_.end(), b.begin(), b.end());
	}

	void Blob::release() TITANIUM_NOEXCEPT
	{
		data_ = std::vector<std::uint8_t>();
		path_ = "";
		mimetype_ = "";
	}

	std::shared_ptr<Titanium::Blob> Blob::transformImage(const std::uint32_t& scaledWidth, const std::uint32_t scaledHeight, const Titanium::UI::Dimension& crop) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::transformImage: Unimplemented");
		return nullptr;
	}

	std::shared_ptr<Titanium::Blob> Blob::imageAsCropped(const Titanium::UI::Dimension& options) TITANIUM_NOEXCEPT
	{
		return transformImage(width_, height_, options);
	}

	std::shared_ptr<Titanium::Blob> Blob::imageAsResized(const std::uint32_t& width, const std::uint32_t& height) TITANIUM_NOEXCEPT
	{
		Titanium::UI::Dimension crop;
		crop.width = width;
		crop.height = height;
		crop.x = 0;
		crop.y = 0;

		return transformImage(width, height, crop);
	}

	std::shared_ptr<Titanium::Blob> Blob::imageAsThumbnail(const std::uint32_t& size, const std::uint32_t& borderSize, const double& cornerRadius) TITANIUM_NOEXCEPT
	{
		Titanium::UI::Dimension crop;
		crop.width = size;
		crop.height = size;
		crop.x = 0;
		crop.y = 0;

		return transformImage(size, size, crop);
	}

	std::shared_ptr<Blob> Blob::imageWithAlpha() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::imageWithAlpha: Unimplemented");
		return nullptr;
	}

	std::shared_ptr<Blob> Blob::imageWithRoundedCorner(const std::uint32_t&, const std::uint32_t&) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::imageWithRoundedCorner: Unimplemented");
		return nullptr;
	}

	std::shared_ptr<Blob> Blob::imageWithTransparentBorder(const std::uint32_t&) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::imageWithTransparentBorder: Unimplemented");
		return nullptr;
	}

	TITANIUM_PROPERTY_GETTER(Blob, length)
	{
		return get_context().CreateNumber(get_length());
	}

	TITANIUM_PROPERTY_GETTER(Blob, file)
	{
		auto file = get_file();
		if (file) {
			return get_file()->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_PROPERTY_GETTER(Blob, height)
	{
		return get_context().CreateNumber(get_height());
	}

	TITANIUM_PROPERTY_GETTER(Blob, mimeType)
	{
		return get_context().CreateString(get_mimeType());
	}

	TITANIUM_PROPERTY_GETTER(Blob, nativePath)
	{
		const auto path = get_nativePath();
		if (path.size() > 0) {
			return get_context().CreateString(path);
		} else {
			return get_context().CreateNull();
		}
	}

	TITANIUM_PROPERTY_GETTER(Blob, size)
	{
		return get_context().CreateNumber(get_size());
	}

	TITANIUM_PROPERTY_GETTER(Blob, text)
	{
		const auto text = get_text();
		if (text.size() > 0) {
			return get_context().CreateString(text);
		} else {
			return get_context().CreateNull();
		}
	}

	TITANIUM_PROPERTY_GETTER(Blob, width)
	{
		return get_context().CreateNumber(get_width());
	}

	TITANIUM_FUNCTION(Blob, append)
	{
		if (arguments.size() < 1) {
			return get_context().CreateUndefined();
		}
		const auto _0 = arguments.at(0);
		if (!_0.IsObject()) {
			return get_context().CreateUndefined();
		}
		const JSObject blob = static_cast<JSObject>(_0);
		auto blob_ptr = blob.GetPrivate<Blob>();
		TITANIUM_ASSERT(blob_ptr);
		append(blob_ptr);

		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Blob, imageAsCropped)
	{
		ENSURE_OBJECT_AT_INDEX(options, 0);
		const auto blob = imageAsCropped(Titanium::UI::js_to_Dimension(options));
		if (blob) {
			return blob->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(Blob, imageAsResized)
	{
		ENSURE_ARGUMENT_INDEX(1);
		ENSURE_UINT_AT_INDEX(width,  0);
		ENSURE_UINT_AT_INDEX(height, 1);
		const auto blob = imageAsResized(width, height);
		if (blob) {
			return blob->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(Blob, imageAsThumbnail)
	{
		ENSURE_UINT_AT_INDEX(size, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(borderSize, 1, 0);
		ENSURE_OPTIONAL_DOUBLE_AT_INDEX(cornerRadius, 2, 0);
		const auto blob = imageAsThumbnail(size, borderSize, cornerRadius);
		if (blob) {
			return blob->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(Blob, imageWithAlpha)
	{
		const auto blob = imageWithAlpha();
		if (blob) {
			return blob->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(Blob, imageWithRoundedCorner)
	{
		ENSURE_UINT_AT_INDEX(cornerSize, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(borderSize, 1, 0);
		const auto blob = imageWithRoundedCorner(cornerSize, borderSize);
		if (blob) {
			return blob->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(Blob, imageWithTransparentBorder)
	{
		ENSURE_UINT_AT_INDEX(size, 0);
		const auto blob = imageWithTransparentBorder(size);
		if (blob) {
			return blob->get_object();
		}
		return get_context().CreateNull();
	}

	// getter functions
	TITANIUM_FUNCTION_AS_GETTER(Blob, getFile, file);
	TITANIUM_FUNCTION_AS_GETTER(Blob, getHeight, height);
	TITANIUM_FUNCTION_AS_GETTER(Blob, getLength, length);
	TITANIUM_FUNCTION_AS_GETTER(Blob, getMimeType, mimeType);
	TITANIUM_FUNCTION_AS_GETTER(Blob, getNativePath, nativePath);
	TITANIUM_FUNCTION_AS_GETTER(Blob, getSize, size);
	TITANIUM_FUNCTION_AS_GETTER(Blob, getText, text);
	TITANIUM_FUNCTION_AS_GETTER(Blob, getWidth, width);
	TITANIUM_FUNCTION_AS_GETTER(Blob, toString, text);

}  // namespace Titanium
