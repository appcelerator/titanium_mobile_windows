/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Blob.hpp"
#include "Titanium/UI/Dimension.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/GlobalObject.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"
#include <ppltasks.h>
#include <concrt.h>
#include <collection.h>
#include <boost/algorithm/string/predicate.hpp>

using Windows::Security::Cryptography::CryptographicBuffer;
using Windows::Security::Cryptography::BinaryStringEncoding;
using Windows::Storage::Streams::IRandomAccessStreamWithContentType;
using Windows::Foundation::IAsyncOperation;
using Windows::Graphics::Imaging::BitmapDecoder;
using concurrency::task_continuation_context;

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

	void Blob::construct(const std::vector<std::uint8_t>& data, const std::string& mimetype) TITANIUM_NOEXCEPT
	{
		Titanium::Blob::construct(data);
		mimetype_ = mimetype;
	}

	void Blob::construct(Windows::Storage::StorageFile^ file) TITANIUM_NOEXCEPT
	{
		width_ = 0;
		height_ = 0;

		path_ = TitaniumWindows::Utility::ConvertString(file->Path);
		const auto is_js = boost::ends_with(path_, ".js");
		if (is_js || boost::ends_with(path_, ".json")){
			// TODO: We should refactor to get the IBuffer back directly, rather than converting the contents multiple times.

			auto js_global = get_context().get_global_object();
			auto global = js_global.GetPrivate<TitaniumWindows::GlobalObject>();
			TITANIUM_ASSERT(global != nullptr);
			std::string contents = global->readRequiredModule(get_object(), path_);
			auto buffer = CryptographicBuffer::ConvertStringToBinary(TitaniumWindows::Utility::ConvertUTF8String(contents), BinaryStringEncoding::Utf8);
			data_ = TitaniumWindows::Utility::GetContentFromBuffer(buffer);
		} else {
			data_ = TitaniumWindows::Utility::GetContentFromFile(file);
		}

		mimetype_ = TitaniumWindows::Utility::ConvertString(file->ContentType);
		if (is_js || mimetype_ == "application/x-javascript" || mimetype_ == "application/javascript") { // handle special cases to match other platforms
			mimetype_ = "text/javascript";
		}
		if (boost::starts_with(mimetype_, "image/")) {
			concurrency::event event;
			concurrency::task<IRandomAccessStreamWithContentType^>(file->OpenReadAsync())
				.then([](IRandomAccessStreamWithContentType^ stream) {
					return Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(stream);
				}, task_continuation_context::use_arbitrary())
				.then([=, &event](concurrency::task<BitmapDecoder^> task) {
					try {
						auto decoder = task.get();
						width_ = static_cast<uint32_t>(decoder->PixelWidth);
						height_ = static_cast<uint32_t>(decoder->PixelHeight);
					} catch (...) {
						TITANIUM_LOG_ERROR("Blob: Could not decode image file");
					}
					event.set();
				}, task_continuation_context::use_arbitrary()
			);
			event.wait();
			type_ = Titanium::BlobModule::TYPE::IMAGE;
		} else {
			type_ = Titanium::BlobModule::TYPE::FILE;
		}
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

	std::shared_ptr<Titanium::Blob> Blob::transformImage(const std::uint32_t& scaledWidth, const std::uint32_t scaledHeight, const Titanium::UI::Dimension& crop) TITANIUM_NOEXCEPT
	{
		if (!boost::starts_with(mimetype_, "image/")) {
			return nullptr;
		}

		using namespace Windows::Graphics::Imaging;
		using namespace Windows::Storage::Streams;

		const auto instream  = ref new InMemoryRandomAccessStream();
		const auto outstream = ref new InMemoryRandomAccessStream();
		const auto writer = ref new DataWriter(instream);
		const auto reader = ref new DataReader(outstream->GetInputStreamAt(0));

		writer->WriteBytes(Platform::ArrayReference<std::uint8_t>(&data_[0], data_.size()));

		concurrency::event evt;
		concurrency::create_task(writer->StoreAsync()).then([writer](std::uint32_t) {
			return writer->FlushAsync();
		}, task_continuation_context::use_arbitrary()).then([instream](bool) {
			instream->Seek(0);
			return BitmapDecoder::CreateAsync(instream);
		}, task_continuation_context::use_arbitrary()).then([outstream](BitmapDecoder^ decoder){
			return BitmapEncoder::CreateForTranscodingAsync(outstream, decoder);
		}, task_continuation_context::use_arbitrary()).then([scaledWidth, scaledHeight, crop](BitmapEncoder^ encoder){

			// scaling
			encoder->BitmapTransform->ScaledWidth  = scaledWidth;
			encoder->BitmapTransform->ScaledHeight = scaledHeight;

			// cropping
			BitmapBounds bounds;
			bounds.Width  = crop.width;
			bounds.Height = crop.height;
			bounds.X = crop.x;
			bounds.Y = crop.y;
			encoder->BitmapTransform->Bounds = bounds;

			return encoder->FlushAsync();
		}, task_continuation_context::use_arbitrary()).then([reader, outstream](){
			return reader->LoadAsync(static_cast<std::uint32_t>(outstream->Size));
		}, task_continuation_context::use_arbitrary()).then([&evt, reader](concurrency::task<std::uint32_t> task){
			try {
				task.get();
			} catch (...) {
				// do nothing
			}
			evt.set();
		}, task_continuation_context::use_arbitrary());
		evt.wait();

		std::vector<std::uint8_t> data(reader->UnconsumedBufferLength);
		if (data.empty()) {
			return nullptr;
		} else {
			reader->ReadBytes(::Platform::ArrayReference<std::uint8_t>(&data[0], data.size()));
		}

		auto Blob = get_context().CreateObject(JSExport<TitaniumWindows::Blob>::Class());
		auto blob = Blob.CallAsConstructor();
		auto blob_ptr = blob.GetPrivate<TitaniumWindows::Blob>();
		blob_ptr->construct(data, mimetype_);
		blob_ptr->width_  = crop.width;
		blob_ptr->height_ = crop.height;

		return blob_ptr;
	}

	std::string Blob::get_text() const TITANIUM_NOEXCEPT
	{
		if (type_ == Titanium::BlobModule::TYPE::IMAGE) {
			return "";
		} else {
			std::vector<std::uint8_t> data = data_;

			Platform::ArrayReference<std::uint8_t> data_ref(&data[0], data.size());
			const auto buffer = CryptographicBuffer::CreateFromByteArray(data_ref);
			const auto decoded = CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, buffer);

			return TitaniumWindows::Utility::ConvertUTF8String(decoded);
		}
	}

}  // namespace TitaniumWindows
