/**
 * TitaniumKit Titanium.BufferStream
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/BufferStream.hpp"
#include "Titanium/Buffer.hpp"
#include "Titanium/ErrorResponse.hpp"

namespace Titanium
{

	BufferStream::BufferStream(const JSContext& js_context) TITANIUM_NOEXCEPT
		: IOStream(js_context, "Ti.BufferStream")
	{

	}

	void BufferStream::construct(const std::shared_ptr<Buffer>& buffer)
	{
		TITANIUM_ASSERT(buffer != nullptr);
		buffer__ = buffer;
	}

	std::int32_t BufferStream::read(const std::shared_ptr<Buffer>& write_buffer, const std::uint32_t& offset, const std::uint32_t& length)
	{
		const auto bytesToRead = getAvailableBytesToRead(buffer__, write_buffer, totalBytesProcessed__, offset, length);
		if (bytesToRead == 0) {
			return -1;
		}

		write_buffer->copy(buffer__, offset, totalBytesProcessed__, bytesToRead);

		totalBytesProcessed__ += bytesToRead;
		return bytesToRead;
	}

	void BufferStream::readAllAsync(const std::shared_ptr<Buffer>& buffer, const std::function<void(const ErrorResponse&, const std::shared_ptr<IOStream>& source)>& callback)
	{
		ErrorResponse error;
		buffer->construct(buffer__->get_data());
		totalBytesProcessed__ = buffer->get_length();
		callback(error, get_object().GetPrivate<IOStream>());
	}

	std::uint32_t BufferStream::write(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length)
	{
		if (!isWritable()) {
			HAL::detail::ThrowRuntimeError("Titanium::BufferStream::write", "Unable to write to a Stream which is read-only.");
		}
		if (modes__.find(Filesystem::MODE::APPEND) != modes__.end()) {
			buffer__->append(buffer, offset, length);
		} else {
			if (buffer__->get_length() <= totalBytesProcessed__) {
				return 0;
			}
			buffer__->copy(buffer, totalBytesProcessed__, offset, length);
		}
		totalBytesProcessed__ += length;
		return length;
	}

	void BufferStream::close()
	{

	}

	void BufferStream::JSExportInitialize()
	{
		JSExport<BufferStream>::SetClassVersion(1);
		JSExport<BufferStream>::SetParent(JSExport<IOStream>::Class());
	}

} // namespace Titanium
