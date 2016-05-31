/**
 * TitaniumKit Titanium.Filesystem.FileStream
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Filesystem/FileStream.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/Buffer.hpp"

namespace Titanium
{
	namespace Filesystem
	{

		FileStream::FileStream(const JSContext& js_context) TITANIUM_NOEXCEPT
			: IOStream(js_context, "Ti.Filesystem.FileStream")
		{
		}


		void FileStream::construct(const std::shared_ptr<File>& file)
		{
			file__ = file;
		}

		std::int32_t FileStream::read(const std::shared_ptr<Buffer>& write_buffer, const std::uint32_t& write_offset, const std::uint32_t& length)
		{
			const auto data = file__->readBytes(totalBytesProcessed__, length);
			if (data.size() == 0) {
				return -1;
			}

			const auto buffer_ctor = get_context().JSEvaluateScript("Ti.Buffer"); \
			const auto buffer_object = static_cast<JSObject>(buffer_ctor).CallAsConstructor();
			auto source_buffer = buffer_object.GetPrivate<Buffer>();
			source_buffer->construct(data);

			const auto bytesToRead = getAvailableBytesToRead(source_buffer, write_buffer, 0, write_offset, length);
			if (bytesToRead == 0) {
				return -1;
			}
			write_buffer->copy(source_buffer, write_offset, 0, bytesToRead);

			totalBytesProcessed__ += bytesToRead;
			return bytesToRead;
		}

		void FileStream::readAsync(const std::shared_ptr<Buffer>& write_buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const ErrorResponse&, const std::int32_t&)>& callback)
		{
			file__->readBytesAsync(totalBytesProcessed__, length, [this, callback](const Titanium::ErrorResponse& error, const std::vector<std::uint8_t>& data){
				const auto bytesToRead = data.size();
				totalBytesProcessed__ += bytesToRead;
				if (bytesToRead == 0) {
					callback(error, -1);
				} else {
					callback(error, static_cast<std::uint32_t>(bytesToRead));
				}
			});
		}

		void FileStream::readAllAsync(const std::shared_ptr<Buffer>& buffer, const std::function<void(const ErrorResponse&, const std::shared_ptr<IOStream>& source)>& callback)
		{
			file__->readAllBytesAsync([this, buffer, callback](const Titanium::ErrorResponse& error, const std::vector<std::uint8_t>& data) {
				buffer->construct(data);
				totalBytesProcessed__ = static_cast<std::uint32_t>(data.size());
				callback(error, get_object().GetPrivate<IOStream>());
			});
		}

		std::uint32_t FileStream::write(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length)
		{
			if (!isWritable()) {
				HAL::detail::ThrowRuntimeError("Titanium::FileStream::write", "Unable to write to a Stream which is read-only.");
			}

			file__->write(buffer->get_data(), offset, length, true);

			totalBytesProcessed__ += length;
			return length;
		}

		void FileStream::writeAsync(const std::shared_ptr<Buffer>& buffer, const std::uint32_t& offset, const std::uint32_t& length, const std::function<void(const ErrorResponse&, const std::int32_t&)>& callback)
		{
			if (!isWritable()) {
				HAL::detail::ThrowRuntimeError("Titanium::FileStream::write", "Unable to write to a Stream which is read-only.");
			}

			file__->writeAsync(buffer->get_data(), offset, length, true, [this, callback](const ErrorResponse& error, const uint32_t& bytes) {
				totalBytesProcessed__ += bytes;
				if (error.success) {
					callback(error, bytes);
				} else {
					callback(error, -1);
				}
			});

		}

		void FileStream::close()
		{

		}

		void FileStream::JSExportInitialize()
		{
			JSExport<FileStream>::SetClassVersion(1);
			JSExport<FileStream>::SetParent(JSExport<IOStream>::Class());
		}
	} // namespace Filesystem
} // namespace Titanium
