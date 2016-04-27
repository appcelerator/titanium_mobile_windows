/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Codec.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Buffer.hpp"
#include <windows.h>
#include <ppltasks.h>
#include <concrt.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

namespace TitaniumWindows
{
	using namespace Titanium::Codec;
	using namespace Windows::Security::Cryptography;
	using namespace concurrency;

	Codec::Codec(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::Codec::CodecModule(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Codec::ctor");
	}

	Codec::~Codec()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Codec::dtor");
	}

	ByteOrder Codec::getNativeByteOrder() TITANIUM_NOEXCEPT
	{
		return ByteOrder::LittleEndian;
	}

	std::uint32_t Codec::encodeNumber(const EncodeNumberDict& options) TITANIUM_NOEXCEPT
	{
		using namespace Windows::Storage::Streams;

		if (options.dest == nullptr) {
			TITANIUM_MODULE_LOG_WARN("Codec::encodeNumber: No dest speciied");
			return 0;
		}

		auto dest_data = options.dest->get_data();

		if (dest_data.size() <= options.position) {
			TITANIUM_MODULE_LOG_WARN("Codec::encodeNumber: Invalid position ", options.position, " for data size ", dest_data.size());
			return 0;
		}

		InMemoryRandomAccessStream^ stream = ref new InMemoryRandomAccessStream();
		DataWriter^ writer = ref new DataWriter(stream);
		DataReader^ reader = ref new DataReader(stream->GetInputStreamAt(0));
		writer->ByteOrder = GetWindowsByteOrder(options.byteOrder);
		reader->ByteOrder = GetWindowsByteOrder(options.byteOrder);

		switch (options.type) {
		case Type::Byte:
			writer->WriteByte(static_cast<unsigned char>(options.source)); break;
		case Type::Float:
			writer->WriteSingle(static_cast<float>(options.source)); break;
		case Type::Double:
			writer->WriteDouble(options.source); break;
		case Type::Short:
		case Type::Int:
		case Type::Long:
			writer->WriteInt64(static_cast<std::int64_t>(options.source)); break;
		}

		event event;
		std::uint32_t bytesLoaded = 0;
		create_task(writer->StoreAsync(), task_continuation_context::use_arbitrary()).then([writer](std::uint32_t) {
			return writer->FlushAsync();
		}, task_continuation_context::use_arbitrary()).then([reader, stream](bool) {
			return reader->LoadAsync(static_cast<std::uint32_t>(stream->Size));
		}, task_continuation_context::use_arbitrary()).then([reader,&bytesLoaded,  &event](task<std::uint32_t> task) {
			bytesLoaded = task.get();
			event.set();
		}, task_continuation_context::use_arbitrary());
		event.wait();

		auto source_data = TitaniumWindows::Utility::GetContentFromBuffer(reader->ReadBuffer(bytesLoaded));

		// down casting discards high bits (big endian) / low bits (little endian)
		if (options.type == Type::Short) {
			if (options.byteOrder == Titanium::Codec::ByteOrder::BigEndian) {
				source_data.erase(source_data.begin(), source_data.begin() + SHORT_DOWNCAST_BITS);
			} else {
				source_data.erase(source_data.end() - SHORT_DOWNCAST_BITS, source_data.end());
			}
		} if (options.type == Type::Int) {
			if (options.byteOrder == Titanium::Codec::ByteOrder::BigEndian) {
				source_data.erase(source_data.begin(), source_data.begin() + INT_DOWNCAST_BITS);
			} else {
				source_data.erase(source_data.end() - INT_DOWNCAST_BITS, source_data.end());
			}
		}

		std::copy(source_data.begin(), source_data.end(), dest_data.begin() + options.position);
		options.dest->set_data(dest_data);

		return options.position + source_data.size();
	}

	double Codec::decodeNumber(const DecodeNumberDict& options) TITANIUM_NOEXCEPT
	{
		using namespace Windows::Storage::Streams;

		auto length = 8;
		switch (options.type) {
		case Type::Byte:
			length = 1;
			break;
		case Type::Short:
			length = 2;
			break;
		case Type::Int:
		case Type::Float:
			length = 4;
			break;
		case Type::Double:
		case Type::Long:
			length = 8; // Do we always use 8 byte for long? Note that iOS-32bit uses 4 bytes for long.
			break;
		}

		auto source_data = options.source->get_data(options.position, length);
		Platform::ArrayReference<std::uint8_t> data_ref(&source_data[0], source_data.size());
		const auto buffer = CryptographicBuffer::CreateFromByteArray(data_ref);
		const auto reader = DataReader::FromBuffer(buffer);
		reader->ByteOrder = GetWindowsByteOrder(options.byteOrder);

		switch (options.type) {
		case Type::Byte:
			return static_cast<double>(reader->ReadByte());
		case Type::Double:
			return static_cast<double>(reader->ReadDouble());
		case Type::Float:
			return static_cast<double>(reader->ReadSingle());
		case Type::Short:
			return static_cast<double>(reader->ReadInt16());
		case Type::Int:
			return static_cast<double>(reader->ReadInt32());
		case Type::Long:
			return static_cast<double>(reader->ReadInt64());
		}

		return 0;
	}

	std::uint32_t Codec::encodeString(const EncodeStringDict& options) TITANIUM_NOEXCEPT
	{
		if (options.dest == nullptr) {
			TITANIUM_MODULE_LOG_WARN("Codec::encodeString: No dest speciied");
			return 0;
		}

		const auto byteOrder = options.dest->get_byteOrder();
		const auto charset = GetWindowsEncoding(options.charset, byteOrder);
		const auto source = options.source.substr(options.sourcePosition, options.sourceLength == 0 ? options.source.length() : options.sourceLength);
		const auto sourceStr = TitaniumWindows::Utility::ConvertUTF8String(source);
		const auto buffer = CryptographicBuffer::ConvertStringToBinary(sourceStr, charset);

		auto source_data = TitaniumWindows::Utility::GetContentFromBuffer(buffer);

		// Ti.Codec.CHARSET_UTF16 assumes BOM according to Titanium API document
		// Ti.Codec.CHARSET_UTF8 doesn't require BOM on the other hand.
		if (options.charset == CharSet::UTF16) {
			if (byteOrder == ByteOrder::BigEndian) {
				source_data.insert(source_data.begin(),     0xFE);
				source_data.insert(source_data.begin() + 1, 0xFF);
			} else {
				source_data.insert(source_data.begin(),     0xFF);
				source_data.insert(source_data.begin() + 1, 0xFE);
			}
		}

		auto dest_data = options.dest->get_data();
		if (source_data.size() > dest_data.size()) {
			if (options.expand_buffer_if_needed) {
				dest_data.resize(source_data.size(), 0);
			} else {
				source_data.resize(dest_data.size(), 0);
			}
		}

		std::copy(source_data.begin(), source_data.end(), dest_data.begin() + options.destPosition);
		options.dest->set_data(dest_data);

		return source_data.size();
	}

	std::string Codec::decodeString(const DecodeStringDict& options) TITANIUM_NOEXCEPT
	{
		if (options.source == nullptr) {
			TITANIUM_MODULE_LOG_WARN("Codec::decodeString: No source speciied");
			return "";
		}

		auto source_data = options.source->get_data();

		// Auto-detect byte order according to BOM if charset is UTF-16.
		auto byteOrder = options.source->get_byteOrder();
		if (options.charset == CharSet::UTF16 && source_data.size() >= 2) {
			if (source_data.at(0) == 0xFE && source_data.at(1) == 0xFF) {
				byteOrder = ByteOrder::BigEndian;
			} else if (source_data.at(0) == 0xFF && source_data.at(1) == 0xFE) {
				byteOrder = ByteOrder::LittleEndian;
			}
		}

		const auto charset = GetWindowsEncoding(options.charset, byteOrder);
		const auto offset = GetBOMOffsetForUnicode(source_data, options.position, options.charset, byteOrder);

		Platform::ArrayReference<std::uint8_t> data_ref(&source_data[offset], source_data.size() - offset);
		const auto buffer = CryptographicBuffer::CreateFromByteArray(data_ref);
		const auto decoded = CryptographicBuffer::ConvertBinaryToString(charset, buffer);

		return TitaniumWindows::Utility::ConvertUTF8String(decoded);
	}

	BinaryStringEncoding Codec::GetWindowsEncoding(const Titanium::Codec::CharSet& charset, const ByteOrder& byteOrder)
	{
		switch (charset) {
		case CharSet::UTF8:
			return BinaryStringEncoding::Utf8; break;
		case CharSet::UTF16:
			return byteOrder == ByteOrder::BigEndian ? BinaryStringEncoding::Utf16BE : BinaryStringEncoding::Utf16LE;
			break;
		case CharSet::UTF16BE:
			return BinaryStringEncoding::Utf16BE; break;
		case CharSet::UTF16LE:
			return BinaryStringEncoding::Utf16LE; break;
		default:
			return BinaryStringEncoding::Utf8;
		}
	}

	Windows::Storage::Streams::ByteOrder Codec::GetWindowsByteOrder(const ByteOrder& byteOrder)
	{
		return byteOrder == ByteOrder::BigEndian ? Windows::Storage::Streams::ByteOrder::BigEndian : Windows::Storage::Streams::ByteOrder::LittleEndian;
	}

	void Codec::JSExportInitialize()
	{
		JSExport<Codec>::SetClassVersion(1);
		JSExport<Codec>::SetParent(JSExport<Titanium::Codec::CodecModule>::Class());
	}

}  // namespace TitaniumWindows
