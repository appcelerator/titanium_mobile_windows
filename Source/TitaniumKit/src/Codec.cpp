/**
 * TitaniumKit Titanium.CodecModule
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Codec.hpp"

namespace Titanium
{
	namespace Codec
	{
		CodecModule::CodecModule(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Codec")
			, CHARSET_ASCII__(js_context.CreateString(Constants::to_string(CharSet::ASCII)))
			, CHARSET_ISO_LATIN_1__(js_context.CreateString(Constants::to_string(CharSet::ISO_LATIN_1)))
			, CHARSET_UTF8__(js_context.CreateString(Constants::to_string(CharSet::UTF8)))
			, CHARSET_UTF16__(js_context.CreateString(Constants::to_string(CharSet::UTF16)))
			, CHARSET_UTF16BE__(js_context.CreateString(Constants::to_string(CharSet::UTF16BE)))
			, CHARSET_UTF16LE__(js_context.CreateString(Constants::to_string(CharSet::UTF16LE)))
			, TYPE_BYTE__(js_context.CreateString(Constants::to_string(Type::Byte)))
			, TYPE_SHORT__(js_context.CreateString(Constants::to_string(Type::Short)))
			, TYPE_INT__(js_context.CreateString(Constants::to_string(Type::Int)))
			, TYPE_FLOAT__(js_context.CreateString(Constants::to_string(Type::Float)))
			, TYPE_LONG__(js_context.CreateString(Constants::to_string(Type::Long)))
			, TYPE_DOUBLE__(js_context.CreateString(Constants::to_string(Type::Double)))
			, BIG_ENDIAN__(js_context.CreateNumber(static_cast<std::uint32_t>(ByteOrder::BigEndian)))
			, LITTLE_ENDIAN__(js_context.CreateNumber(static_cast<std::uint32_t>(ByteOrder::LittleEndian)))
		{

		}

		ByteOrder CodecModule::getNativeByteOrder() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("CodecModule::getNativeByteOrder: Unimplemented");
			return ByteOrder::Unknown;
		}

		std::uint32_t CodecModule::encodeNumber(const EncodeNumberDict& options) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("CodecModule::encodeNumber: Unimplemented");
			return 0;
		}

		double CodecModule::decodeNumber(const DecodeNumberDict& options) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("CodecModule::decodeNumber: Unimplemented");
			return 0;
		}

		std::uint32_t CodecModule::encodeString(const EncodeStringDict& options) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("CodecModule::encodeString: Unimplemented");
			return 0;
		}

		std::string CodecModule::decodeString(const DecodeStringDict& options) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("CodecModule::decodeString: Unimplemented");
			return "";
		}

		std::uint32_t CodecModule::GetBOMOffsetForUnicode(const std::vector<std::uint8_t>& data, const std::uint32_t& offset, const CharSet& charset, const ByteOrder& byteOrder)
		{
			if (charset == CharSet::UTF8 && (data.size() >= 3 && data[offset] == 0xEF && data[offset + 1] == 0xBB && data[offset + 2] == 0xBF)) {
				// UTF-8 with BOM
				return offset + 3;
			} else if ((charset == CharSet::UTF16 || charset == CharSet::UTF16BE || charset == CharSet::UTF16LE) && data.size() >= 2) {
				// UTF-16 with BOM
				if (byteOrder == ByteOrder::BigEndian && (data[offset] == 0xFE && data[offset + 1] == 0xFF)) {
					return offset + 2;
				} else if (byteOrder == ByteOrder::LittleEndian && (data[offset] == 0xFF && data[offset + 1] == 0xFE)) {
					return offset + 2;
				}
			}
			return offset;
		}

		void CodecModule::JSExportInitialize()
		{
			JSExport<CodecModule>::SetClassVersion(1);
			JSExport<CodecModule>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, CHARSET_ASCII);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, CHARSET_ISO_LATIN_1);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, CHARSET_UTF8);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, CHARSET_UTF16);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, CHARSET_UTF16BE);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, CHARSET_UTF16LE);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, TYPE_BYTE);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, TYPE_SHORT);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, TYPE_INT);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, TYPE_FLOAT);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, TYPE_LONG);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, TYPE_DOUBLE);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, BIG_ENDIAN);
			TITANIUM_ADD_PROPERTY_READONLY(CodecModule, LITTLE_ENDIAN);

			TITANIUM_ADD_FUNCTION(CodecModule, getNativeByteOrder);
			TITANIUM_ADD_FUNCTION(CodecModule, encodeNumber);
			TITANIUM_ADD_FUNCTION(CodecModule, decodeNumber);
			TITANIUM_ADD_FUNCTION(CodecModule, encodeString);
			TITANIUM_ADD_FUNCTION(CodecModule, decodeString);
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, BIG_ENDIAN)
		{
			return BIG_ENDIAN__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, LITTLE_ENDIAN)
		{
			return LITTLE_ENDIAN__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, CHARSET_ASCII)
		{
			return CHARSET_ASCII__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, CHARSET_ISO_LATIN_1)
		{
			return CHARSET_ISO_LATIN_1__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, CHARSET_UTF8)
		{
			return CHARSET_UTF8__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, CHARSET_UTF16)
		{
			return CHARSET_UTF16__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, CHARSET_UTF16BE)
		{
			return CHARSET_UTF16BE__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, CHARSET_UTF16LE)
		{
			return CHARSET_UTF16LE__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, TYPE_BYTE)
		{
			return TYPE_BYTE__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, TYPE_SHORT)
		{
			return TYPE_SHORT__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, TYPE_INT)
		{
			return TYPE_INT__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, TYPE_FLOAT)
		{
			return TYPE_FLOAT__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, TYPE_LONG)
		{
			return TYPE_LONG__;
		}

		TITANIUM_PROPERTY_GETTER(CodecModule, TYPE_DOUBLE)
		{
			return TYPE_DOUBLE__;
		}

		TITANIUM_FUNCTION(CodecModule, getNativeByteOrder)
		{
			return get_context().CreateNumber(static_cast<std::uint32_t>(getNativeByteOrder()));
		}

		TITANIUM_FUNCTION(CodecModule, encodeNumber)
		{
			ENSURE_OBJECT_AT_INDEX(options, 0);
			if (!options.HasProperty("source") || !options.HasProperty("dest") || !options.HasProperty("type")) {
				HAL::detail::ThrowRuntimeError("Codec", "Invalid type passed to function");
				return get_context().CreateUndefined();
			}

			return get_context().CreateNumber(encodeNumber(js_to_EncodeNumberDict(options)));
		}

		TITANIUM_FUNCTION(CodecModule, decodeNumber)
		{
			ENSURE_OBJECT_AT_INDEX(options, 0);
			if (!options.HasProperty("source") || !options.HasProperty("type")) {
				HAL::detail::ThrowRuntimeError("Codec", "Invalid type passed to function");
				return get_context().CreateUndefined();
			}
			return get_context().CreateNumber(decodeNumber(js_to_DecodeNumberDict(options)));
		}

		TITANIUM_FUNCTION(CodecModule, encodeString)
		{
			ENSURE_OBJECT_AT_INDEX(options, 0);
			return get_context().CreateNumber(encodeString(js_to_EncodeStringDict(options)));
		}

		TITANIUM_FUNCTION(CodecModule, decodeString)
		{
			ENSURE_OBJECT_AT_INDEX(options, 0);
			return get_context().CreateString(decodeString(js_to_DecodeStringDict(options)));
		}

	} // namespace Codec
} // namespace Titanium
