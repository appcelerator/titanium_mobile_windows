/**
 * TitaniumKit Titanium.Buffer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Buffer.hpp"
#include "Titanium/Codec.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/Codec/Constants.hpp"
#include <algorithm>

#define GET_TITANIUM_MODULE(NAME,VARNAME) \
  const auto Titanium_property = get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  const auto Titanium = static_cast<JSObject>(Titanium_property); \
  const auto NAME##_poperty = Titanium.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_poperty.IsObject()); \
  auto VARNAME = static_cast<JSObject>(NAME##_poperty);

namespace Titanium
{

	Buffer::Buffer(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.Buffer")
		, type__(Titanium::Codec::Type::Int)
		, value__(js_context.CreateNull())
		, byteOrder__(Titanium::Codec::ByteOrder::Unknown)
	{
		TITANIUM_LOG_DEBUG("Titanium::Buffer ctor ", this);
	}

	TITANIUM_PROPERTY_READWRITE(Buffer, Titanium::Codec::Type, type)
	TITANIUM_PROPERTY_READWRITE(Buffer, Titanium::Codec::ByteOrder, byteOrder)
	TITANIUM_PROPERTY_READWRITE(Buffer, JSValue, value)
	TITANIUM_PROPERTY_READWRITE(Buffer, std::vector<std::uint8_t>, data)
	TITANIUM_PROPERTY_READWRITE(Buffer, Titanium::Codec::CharSet, charset)

	void Buffer::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
	{
		Titanium::Module::postCallAsConstructor(js_context, arguments);

		if (byteOrder__ == Titanium::Codec::ByteOrder::Unknown) {
			GET_TITANIUM_MODULE(Codec, CodecObj);
			const auto codec_ptr = CodecObj.GetPrivate<Titanium::Codec::CodecModule>();
			TITANIUM_ASSERT(codec_ptr);
			byteOrder__ = codec_ptr->getNativeByteOrder();
		}
	}

	void Buffer::afterPropertiesSet() TITANIUM_NOEXCEPT
	{
		GET_TITANIUM_MODULE(Codec, CodecObj);
		const auto codec_ptr = CodecObj.GetPrivate<Titanium::Codec::CodecModule>();

		if (value__.IsString()) {
			const auto source = static_cast<std::string>(value__);
			Titanium::Codec::EncodeStringDict param;
			param.source = source;
			param.charset = charset__;
			param.dest = get_object().GetPrivate<Buffer>();
			param.expand_buffer_if_needed = true;
			codec_ptr->encodeString(param);
		} else if (value__.IsNumber()) {
			if (data__.size() == 0) {
				switch (type__) {
				case Codec::Type::Byte:   set_length(1); break;
				case Codec::Type::Short:  set_length(2); break;
				case Codec::Type::Int:    set_length(4); break;
				case Codec::Type::Long:   set_length(8); break;
				case Codec::Type::Float:  set_length(4); break;
				case Codec::Type::Double: set_length(8); break;
				case Codec::Type::Unknown: HAL::detail::ThrowRuntimeError("Buffer::postConstructProperties", "Titanium::Buffer: Invalid data type");
				}
			}
			Titanium::Codec::EncodeNumberDict param;
			param.byteOrder = byteOrder__;
			param.type = type__;
			param.source = static_cast<double>(value__);
			param.dest = get_object().GetPrivate<Buffer>();
			codec_ptr->encodeNumber(param);
		}
	}

	void Buffer::construct(const std::vector<std::uint8_t>& data) TITANIUM_NOEXCEPT
	{
		data__ = data;
	}


	std::uint32_t Buffer::get_length() const TITANIUM_NOEXCEPT
	{
		return static_cast<std::uint32_t>(data__.size());
	}

	void Buffer::set_length(const std::uint32_t& length) TITANIUM_NOEXCEPT
	{
		data__.resize(length, 0);
	}

	std::vector<std::uint8_t> Buffer::get_data(const std::uint32_t& offset, const std::uint32_t& size) TITANIUM_NOEXCEPT
	{
		return std::vector<std::uint8_t>(data__.begin() + offset, data__.begin() + std::min(offset + size, static_cast<std::uint32_t>(data__.size())));
	}

	std::uint32_t Buffer::append(const std::shared_ptr<Buffer>& sourceBuffer, const std::uint32_t& sourceOffset, const std::uint32_t& sourceLength) TITANIUM_NOEXCEPT
	{
		const auto source = sourceBuffer->get_data();
		data__.reserve(data__.size() + sourceLength);
		data__.insert(data__.end(), source.begin() + sourceOffset, source.begin() + sourceOffset + sourceLength);
		return sourceLength;
	}

	std::uint32_t Buffer::insert(const std::shared_ptr<Buffer>& sourceBuffer, const std::uint32_t& offset, const std::uint32_t& sourceOffset, const std::uint32_t& sourceLength) TITANIUM_NOEXCEPT
	{
		const auto source = sourceBuffer->get_data();
		data__.reserve(data__.size() + sourceLength);
		data__.insert(data__.begin() + offset, source.begin() + sourceOffset, source.begin() + sourceOffset + sourceLength);
		return sourceLength;
	}

	std::uint32_t Buffer::copy(const std::shared_ptr<Buffer>& sourceBuffer, const std::uint32_t& offset, const std::uint32_t& sourceOffset, const std::uint32_t& sourceLength) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(offset < data__.size());
		const auto source = sourceBuffer->get_data();
		const auto actualLength = offset + sourceLength > data__.size() ? data__.size() - offset : sourceLength;
		std::copy(source.begin() + sourceOffset, source.begin() + sourceOffset + actualLength, data__.begin() + offset);
		return static_cast<std::uint32_t>(actualLength);
	}

	std::shared_ptr<Buffer> Buffer::clone(const std::uint32_t& offset, const std::uint32_t& length) TITANIUM_NOEXCEPT
	{
		const auto js_buffer = get_context().JSEvaluateScript("Ti.createBuffer();");
		TITANIUM_ASSERT(js_buffer.IsObject());
		const auto buffer = static_cast<JSObject>(js_buffer).GetPrivate<Buffer>();
		TITANIUM_ASSERT(buffer);
		buffer->append(get_object().GetPrivate<Buffer>(), offset, length);
		return buffer;
	}

	void Buffer::fill(const std::uint8_t& fillByte, const std::uint32_t& offset, const std::uint32_t& length) TITANIUM_NOEXCEPT
	{
		std::fill(data__.begin() + offset, data__.begin() + offset + length, fillByte);
	}

	void Buffer::clear() TITANIUM_NOEXCEPT
	{
		// Clears this buffer's contents but does not change the size of the buffer.
		fill(0, 0, static_cast<std::uint32_t>(data__.size()));
	}

	void Buffer::release() TITANIUM_NOEXCEPT
	{
		data__.clear();
	}

	std::string Buffer::toString() TITANIUM_NOEXCEPT
	{
		if (data__.size() == 0) {
			return "";
		}

		//
		// Just call Ti.Codec.encodeString(buffer);
		//
		GET_TITANIUM_MODULE(Codec, CodecObj);
		const auto codec_ptr = CodecObj.GetPrivate<Titanium::Codec::CodecModule>();
		TITANIUM_ASSERT(codec_ptr);

		Titanium::Codec::DecodeStringDict param;
		param.length = static_cast<std::uint32_t>(data__.size());
		param.position = 0;
		param.source = get_object().GetPrivate<Buffer>();

		return codec_ptr->decodeString(param);
	}

	std::shared_ptr<Blob> Buffer::toBlob() TITANIUM_NOEXCEPT
	{
		GET_TITANIUM_MODULE(Blob, BlobObj);
		const auto blob = BlobObj.CallAsConstructor();
		const auto blob_ptr = blob.GetPrivate<Titanium::Blob>();
		TITANIUM_ASSERT(blob_ptr);
		blob_ptr->construct(data__);
		return blob_ptr;
	}

	bool Buffer::isDataIndexProperty(const std::string& property_name) const
	{
		if (std::all_of(property_name.begin(), property_name.end(), ::isdigit)) {
			return data__.size() > static_cast<std::size_t>(std::stoi(property_name));
		}
		return false;
	}

	//
	// Buffer provides accessor for the data which acts like an array.
	//
	bool Buffer::js_hasProperty(const JSString& name) const
	{
		const auto property_name = static_cast<std::string>(name);
		if (isDataIndexProperty(property_name)) {
			return true;
		}
		return false;
	}

	JSValue Buffer::js_getProperty(const JSString& name) const
	{
		const auto property_name = static_cast<std::string>(name);
		if (isDataIndexProperty(property_name)) {
			return get_context().CreateNumber(data__.at(std::stoi(property_name)));
		}
		return get_context().CreateUndefined();
	}

	bool Buffer::js_setProperty(const JSString& name, const JSValue& value)
	{
		const auto property_name = static_cast<std::string>(name);
		if (value.IsNumber() && isDataIndexProperty(property_name)) {
			data__.at(std::stoi(property_name)) = static_cast<std::uint8_t>(static_cast<std::uint32_t>(value));
			return true;
		}
		return false;
	}

	void Buffer::JSExportInitialize()
	{
		JSExport<Buffer>::SetClassVersion(1);
		JSExport<Buffer>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_PROPERTY(Buffer, length);
		TITANIUM_ADD_PROPERTY(Buffer, value);
		TITANIUM_ADD_PROPERTY(Buffer, type);
		TITANIUM_ADD_PROPERTY(Buffer, byteOrder);

		TITANIUM_ADD_FUNCTION(Buffer, append);
		TITANIUM_ADD_FUNCTION(Buffer, insert);
		TITANIUM_ADD_FUNCTION(Buffer, copy);
		TITANIUM_ADD_FUNCTION(Buffer, clone);
		TITANIUM_ADD_FUNCTION(Buffer, fill);
		TITANIUM_ADD_FUNCTION(Buffer, clear);
		TITANIUM_ADD_FUNCTION(Buffer, release);
		TITANIUM_ADD_FUNCTION(Buffer, toString);
		TITANIUM_ADD_FUNCTION(Buffer, toBlob);
		TITANIUM_ADD_FUNCTION(Buffer, getLength);
		TITANIUM_ADD_FUNCTION(Buffer, setLength);
		TITANIUM_ADD_FUNCTION(Buffer, getValue);
		TITANIUM_ADD_FUNCTION(Buffer, setValue);
		TITANIUM_ADD_FUNCTION(Buffer, getType);
		TITANIUM_ADD_FUNCTION(Buffer, setType);
		TITANIUM_ADD_FUNCTION(Buffer, getByteOrder);
		TITANIUM_ADD_FUNCTION(Buffer, setByteOrder);
		JSExport<Buffer>::AddHasPropertyCallback(std::mem_fn(&Buffer::js_hasProperty));
		JSExport<Buffer>::AddGetPropertyCallback(std::mem_fn(&Buffer::js_getProperty));
		JSExport<Buffer>::AddSetPropertyCallback(std::mem_fn(&Buffer::js_setProperty));
	}

	TITANIUM_PROPERTY_GETTER_UINT(Buffer, length);
	TITANIUM_PROPERTY_SETTER_UINT(Buffer, length)

	TITANIUM_PROPERTY_GETTER(Buffer, value)
	{
		return get_value();
	}

	TITANIUM_PROPERTY_SETTER(Buffer, value)
	{
		set_value(argument);
		return true;
	}

	TITANIUM_PROPERTY_GETTER(Buffer, type)
	{
		if (value__.IsString()) {
			return get_context().CreateString(Titanium::Codec::Constants::to_string(get_charset()));
		} else {
			return get_context().CreateString(Titanium::Codec::Constants::to_string(get_type()));
		}
	}

	TITANIUM_PROPERTY_SETTER(Buffer, type)
	{
		// type property may be Type or CharSet, so we need to check both.
		const auto type = Titanium::Codec::Constants::to_Type(static_cast<std::string>(argument));
		if (type != Titanium::Codec::Type::Unknown) {
			set_type(Titanium::Codec::Constants::to_Type(static_cast<std::string>(argument)));
		} else {
			set_charset(Titanium::Codec::Constants::to_CharSet(static_cast<std::string>(argument)));
		}
		return true;
	}

	TITANIUM_PROPERTY_GETTER(Buffer, byteOrder)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(get_byteOrder()));
	}

	TITANIUM_PROPERTY_SETTER(Buffer, byteOrder)
	{
		TITANIUM_ASSERT(argument.IsNumber());
		set_byteOrder(Titanium::Codec::Constants::to_ByteOrder(static_cast<std::uint32_t>(argument)));
		return true;
	}

	TITANIUM_FUNCTION(Buffer, append)
	{
		if (arguments.size() == 0) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::append", "Buffer::append: Too few argument");
		}

		ENSURE_OBJECT_AT_INDEX(sourceBuffer, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(sourceOffset, 1, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(sourceLength, 2, 0);

		const auto buffer = sourceBuffer.GetPrivate<Buffer>();
		if (buffer) {
			if (sourceLength == 0) {
				sourceLength = static_cast<std::uint32_t>(buffer->get_length());
			}
		} else {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::append", "Buffer::append: Unable to get Buffer");
		}

		if (buffer->get_length() < sourceOffset + sourceLength) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::append", "Buffer::append: Invalid argument");
		}

		return get_context().CreateNumber(append(buffer, sourceOffset, sourceLength));
	}

	TITANIUM_FUNCTION(Buffer, insert)
	{
		if (arguments.size() < 2) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::insert", "Buffer::insert: Too few argument");
		}

		ENSURE_OBJECT_AT_INDEX(sourceBuffer, 0);
		ENSURE_UINT_AT_INDEX(offset, 1);
		ENSURE_OPTIONAL_UINT_AT_INDEX(sourceOffset, 2, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(sourceLength, 3, 0);

		const auto buffer = sourceBuffer.GetPrivate<Buffer>();
		if (buffer) {
			if (sourceLength == 0) {
				sourceLength = static_cast<std::uint32_t>(buffer->get_data().size());
			}
		} else {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::insert", "Buffer::insert: Unable to get Buffer");
		}

		if (get_length() <= offset || buffer->get_length() < sourceOffset + sourceLength) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::insert", "Buffer::insert: Invalid argument");
		}

		return get_context().CreateNumber(insert(buffer, offset, sourceOffset, sourceLength));
	}

	TITANIUM_FUNCTION(Buffer, copy)
	{
		if (arguments.size() < 2) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::copy", "Buffer::copy: Too few argument");
		}

		ENSURE_OBJECT_AT_INDEX(sourceBuffer, 0);
		ENSURE_UINT_AT_INDEX(offset, 1);
		ENSURE_OPTIONAL_UINT_AT_INDEX(sourceOffset, 2, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(sourceLength, 3, 0);

		const auto buffer = sourceBuffer.GetPrivate<Buffer>();
		if (buffer) {
			if (sourceLength == 0) {
				sourceLength = static_cast<std::uint32_t>(buffer->get_data().size());
			}
		} else {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::copy", "Buffer::copy: Unable to get Buffer");
		}

		if (get_length() <= offset || buffer->get_length() < sourceOffset + sourceLength) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::insert", "Buffer::insert: Invalid argument");
		}

		return get_context().CreateNumber(copy(buffer, offset, sourceOffset, sourceLength));
	}

	TITANIUM_FUNCTION(Buffer, clone)
	{
		ENSURE_OPTIONAL_UINT_AT_INDEX(offset, 0, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(length, 1, get_length());

		if (get_length() < offset + length) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::clone", "Buffer::clone: Invalid argument");
		}

		const auto buffer = clone(offset, length);

		if (buffer) {
			return buffer->get_object();
		} else {
			return get_context().CreateNull();
		}
	}

	TITANIUM_FUNCTION(Buffer, fill)
	{
		if (arguments.size() < 1) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::fill", "Buffer::fill: Too few argument");
		}

		ENSURE_UINT_AT_INDEX(fillByte, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(offset, 1, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(length, 2, get_length());

		if (get_length() < offset + length) {
			HAL::detail::ThrowRuntimeError("Titanium::Buffer::fill", "Buffer::fill: Invalid argument");
		}

		fill(fillByte, offset, length);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Buffer, clear)
	{
		clear();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Buffer, release)
	{
		release();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Buffer, toString)
	{
		return get_context().CreateString(toString());
	}

	TITANIUM_FUNCTION(Buffer, toBlob)
	{
		const auto blob = toBlob();
		if (blob) {
			return blob->get_object();
		} else {
			return get_context().CreateNull();
		}
	}

	TITANIUM_FUNCTION_AS_GETTER(Buffer, getLength, length)
	TITANIUM_FUNCTION_AS_SETTER(Buffer, setLength, length)
	TITANIUM_FUNCTION_AS_GETTER(Buffer, getValue, value)
	TITANIUM_FUNCTION_AS_SETTER(Buffer, setValue, value)
	TITANIUM_FUNCTION_AS_GETTER(Buffer, getType, type)
	TITANIUM_FUNCTION_AS_SETTER(Buffer, setType, type)
	TITANIUM_FUNCTION_AS_GETTER(Buffer, getByteOrder, byteOrder)
	TITANIUM_FUNCTION_AS_SETTER(Buffer, setByteOrder, byteOrder)

} // namespace Titanium
