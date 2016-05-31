/**
 * TitaniumKit Titanium.BlobStream
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/BlobStream.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/Buffer.hpp"

namespace Titanium
{

	BlobStream::BlobStream(const JSContext& js_context) TITANIUM_NOEXCEPT
		: IOStream(js_context, "Ti.BlobStream")
	{

	}

	void BlobStream::construct(const std::shared_ptr<Blob>& blob)
	{
		TITANIUM_ASSERT(blob != nullptr);
		blob__ = blob;
	}

	std::int32_t BlobStream::read(const std::shared_ptr<Buffer>& write_buffer, const std::uint32_t& offset, const std::uint32_t& length)
	{
		const auto buffer_ctor = get_context().JSEvaluateScript("Ti.Buffer"); \
		const auto buffer_object = static_cast<JSObject>(buffer_ctor).CallAsConstructor();
		auto source_buffer = buffer_object.GetPrivate<Buffer>();
		source_buffer->construct(blob__->getData());

		const auto bytesToRead = getAvailableBytesToRead(source_buffer, write_buffer, totalBytesProcessed__, offset, length);
		if (bytesToRead == 0) {
			return -1;
		}
		write_buffer->copy(source_buffer, offset, totalBytesProcessed__, bytesToRead);

		totalBytesProcessed__ += bytesToRead;
		return bytesToRead;
	}

	void BlobStream::readAllAsync(const std::shared_ptr<Buffer>& buffer, const std::function<void(const ErrorResponse&, const std::shared_ptr<IOStream>& source)>& callback)
	{
		ErrorResponse error;
		buffer->construct(blob__->getData());
		totalBytesProcessed__ = buffer->get_length();
		callback(error, get_object().GetPrivate<IOStream>());
	}

	std::uint32_t BlobStream::write(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length)
	{
		HAL::detail::ThrowRuntimeError("Titanium::BlobStream", "Invalid operation: BlobStream is read-only");
		return 0;
	}

	void BlobStream::close()
	{

	}

	void BlobStream::JSExportInitialize()
	{
		JSExport<BlobStream>::SetClassVersion(1);
		JSExport<BlobStream>::SetParent(JSExport<IOStream>::Class());
	}

} // namespace Titanium
