/**
 * TitaniumKit Titanium.Codec constants
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Codec/Constants.hpp"
#include "Titanium/Buffer.hpp"

namespace Titanium
{
	namespace Codec
	{
		std::string Constants::to_string(const ByteOrder& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "unknown";
			static std::unordered_map<ByteOrder, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ByteOrder::BigEndian] = "bigendian";
				map[ByteOrder::LittleEndian] = "littleendian";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		std::string Constants::to_string(const CharSet& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "unknown";
			static std::unordered_map<CharSet, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[CharSet::ASCII]   = "ascii";
				map[CharSet::ISO_LATIN_1] = "iso-latin-1";
				map[CharSet::UTF16]   = "utf16";
				map[CharSet::UTF16BE] = "utf16be";
				map[CharSet::UTF16LE] = "utf16le";
				map[CharSet::UTF8]    = "utf8";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		std::string Constants::to_string(const Type& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "unknown";
			static std::unordered_map<Type, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[Type::Byte]   = "byte";
				map[Type::Double] = "double";
				map[Type::Float]  = "float";
				map[Type::Int]    = "int";
				map[Type::Long]   = "long";
				map[Type::Short]  = "short";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ByteOrder Constants::to_ByteOrder(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ByteOrder> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["bigendian"]    = ByteOrder::BigEndian;
				map["littleendian"] = ByteOrder::LittleEndian;
			});

			ByteOrder fieldType = ByteOrder::Unknown;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ByteOrder: Titanium::Codec::ByteOrder with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		CharSet Constants::to_CharSet(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, CharSet> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ascii"]    = CharSet::ASCII;
				map["iso-latin-1"] = CharSet::ISO_LATIN_1;
				map["utf8"]     = CharSet::UTF8;
				map["utf16"]    = CharSet::UTF16;
				map["utf16be"]  = CharSet::UTF16BE;
				map["utf16le"]  = CharSet::UTF16LE;
			});

			CharSet fieldType = CharSet::UTF8;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_CharSet: Titanium::Codec::CharSet with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		Type Constants::to_Type(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, Type> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["byte"]   = Type::Byte;
				map["double"] = Type::Double;
				map["float"]  = Type::Float;
				map["int"]    = Type::Int;
				map["long"]   = Type::Long;
				map["short"]  = Type::Short;
			});

			Type fieldType = Type::Unknown;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			}

			return fieldType;
		}

		ByteOrder Constants::to_ByteOrder(std::underlying_type<ByteOrder>::type ByteOrder_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ByteOrder>::type, ByteOrder> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ByteOrder>::type>(ByteOrder::BigEndian)]    = ByteOrder::BigEndian;
				map[static_cast<std::underlying_type<ByteOrder>::type>(ByteOrder::LittleEndian)] = ByteOrder::LittleEndian;
			});

			ByteOrder fieldType = ByteOrder::Unknown;
			const auto position = map.find(ByteOrder_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ByteOrder: Titanium::Codec::ByteOrder with value '", ByteOrder_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		CharSet Constants::to_CharSet(std::underlying_type<CharSet>::type CharSet_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<CharSet>::type, CharSet> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<CharSet>::type>(CharSet::ISO_LATIN_1)] = CharSet::ISO_LATIN_1;
				map[static_cast<std::underlying_type<CharSet>::type>(CharSet::UTF8)]  = CharSet::UTF8;
				map[static_cast<std::underlying_type<CharSet>::type>(CharSet::UTF16)] = CharSet::UTF16;
				map[static_cast<std::underlying_type<CharSet>::type>(CharSet::ASCII)] = CharSet::ASCII;
				map[static_cast<std::underlying_type<CharSet>::type>(CharSet::UTF16BE)] = CharSet::UTF16BE;
				map[static_cast<std::underlying_type<CharSet>::type>(CharSet::UTF16LE)] = CharSet::UTF16LE;
			});

			CharSet fieldType = CharSet::UTF8;
			const auto position = map.find(CharSet_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_CharSet: Titanium::Codec::CharSet with value '", CharSet_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		Type Constants::to_Type(std::underlying_type<Type>::type Type_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<Type>::type, Type> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<Type>::type>(Type::Byte)]   = Type::Byte;
				map[static_cast<std::underlying_type<Type>::type>(Type::Short)]  = Type::Short;
				map[static_cast<std::underlying_type<Type>::type>(Type::Int)]    = Type::Int;
				map[static_cast<std::underlying_type<Type>::type>(Type::Float)]  = Type::Float;
				map[static_cast<std::underlying_type<Type>::type>(Type::Long)]   = Type::Long;
				map[static_cast<std::underlying_type<Type>::type>(Type::Double)] = Type::Double;
			});

			Type fieldType = Type::Int;
			const auto position = map.find(Type_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ByteOrder: Titanium::Codec::ByteOrder with value '", Type_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		std::underlying_type<ByteOrder>::type Constants::to_underlying_type(const ByteOrder& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ByteOrder>::type>(fieldType);
		}

		std::underlying_type<CharSet>::type Constants::to_underlying_type(const CharSet& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<CharSet>::type>(fieldType);
		}

		std::underlying_type<Type>::type Constants::to_underlying_type(const Type& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<Type>::type>(fieldType);
		}

		DecodeNumberDict  js_to_DecodeNumberDict(const JSObject& object) 
		{
			DecodeNumberDict dict;
			if (object.HasProperty("byteOrder")) {
				dict.byteOrder = Constants::to_ByteOrder(static_cast<std::uint32_t>(object.GetProperty("byteOrder")));
			}
			if (object.HasProperty("position")) {
				dict.position = static_cast<std::uint32_t>(object.GetProperty("position"));
			}
			if (object.HasProperty("source")) {
				const auto source = object.GetProperty("source");
				if (source.IsObject()) {
					dict.source = static_cast<JSObject>(source).GetPrivate<Titanium::Buffer>();
				}
			}
			if (object.HasProperty("type")) {
				dict.type = Constants::to_Type(static_cast<std::string>(object.GetProperty("type")));
			}
			return dict;
		}

		JSObject DecodeNumberDict_to_js(const JSContext& js_context, DecodeNumberDict value) 
		{
			auto object = js_context.CreateObject();
			object.SetProperty("byteOrder", js_context.CreateNumber(static_cast<std::uint32_t>(value.byteOrder)));
			object.SetProperty("position", js_context.CreateNumber(value.position));
			if (value.source) {
				object.SetProperty("source", value.source->get_object());
			} else {
				object.SetProperty("source", js_context.CreateNull());
			}
			object.SetProperty("type", js_context.CreateString(Constants::to_string(value.type)));
			return object;
		}

		DecodeStringDict  js_to_DecodeStringDict(const JSObject& object)
		{
			DecodeStringDict dict;
			if (object.HasProperty("charset")) {
				dict.charset = Constants::to_CharSet(static_cast<std::string>(object.GetProperty("charset")));
			}
			if (object.HasProperty("length")) {
				dict.length = static_cast<std::uint32_t>(object.GetProperty("length"));
			}
			if (object.HasProperty("position")) {
				dict.position = static_cast<std::uint32_t>(object.GetProperty("position"));
			}
			if (object.HasProperty("source")) {
				const auto source = object.GetProperty("source");
				if (source.IsObject()) {
					dict.source = static_cast<JSObject>(source).GetPrivate<Titanium::Buffer>();
				}
			}
			return dict;
		}

		JSObject DecodeStringDict_to_js(const JSContext& js_context, DecodeStringDict value)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("charset",  js_context.CreateString(Constants::to_string(value.charset)));
			object.SetProperty("length",   js_context.CreateNumber(value.length));
			object.SetProperty("position", js_context.CreateNumber(value.position));
			if (value.source) {
				object.SetProperty("source", value.source->get_object());
			} else {
				object.SetProperty("source", js_context.CreateNull());
			}
			return object;
		}

		EncodeNumberDict  js_to_EncodeNumberDict(const JSObject& object)
		{
			EncodeNumberDict dict;
			if (object.HasProperty("byteOrder")) {
				dict.byteOrder = Constants::to_ByteOrder(static_cast<std::uint32_t>(object.GetProperty("byteOrder")));
			}
			if (object.HasProperty("position")) {
				dict.position = static_cast<std::uint32_t>(object.GetProperty("position"));
			}
			if (object.HasProperty("source")) {
				dict.source = static_cast<double>(object.GetProperty("source"));
			}
			if (object.HasProperty("dest")) {
				const auto dest = object.GetProperty("dest");
				if (dest.IsObject()) {
					dict.dest = static_cast<JSObject>(dest).GetPrivate<Titanium::Buffer>();
				}
			}
			if (object.HasProperty("type")) {
				dict.type = Constants::to_Type(static_cast<std::string>(object.GetProperty("type")));
			}
			return dict;
		}

		JSObject EncodeNumberDict_to_js(const JSContext& js_context, EncodeNumberDict value)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("byteOrder", js_context.CreateNumber(static_cast<std::uint32_t>(value.byteOrder)));
			object.SetProperty("position", js_context.CreateNumber(value.position));
			object.SetProperty("source", js_context.CreateNumber(value.source));
			if (value.dest) {
				object.SetProperty("dest", value.dest->get_object());
			} else {
				object.SetProperty("dest", js_context.CreateNull());
			}
			object.SetProperty("type", js_context.CreateString(Constants::to_string(value.type)));
			return object;
		}

		EncodeStringDict  js_to_EncodeStringDict(const JSObject& object)
		{
			EncodeStringDict dict;
			if (object.HasProperty("charset")) {
				dict.charset = Constants::to_CharSet(static_cast<std::string>(object.GetProperty("charset")));
			}
			if (object.HasProperty("source")) {
				dict.source = static_cast<std::string>(object.GetProperty("source"));
				dict.sourceLength = static_cast<std::uint32_t>(dict.source.length());
			}
			if (object.HasProperty("sourceLength")) {
				dict.sourceLength = static_cast<std::uint32_t>(object.GetProperty("sourceLength"));
			}
			if (object.HasProperty("sourcePosition")) {
				dict.sourcePosition = static_cast<std::uint32_t>(object.GetProperty("sourcePosition"));
			}
			if (object.HasProperty("dest")) {
				const auto dest = object.GetProperty("dest");
				if (dest.IsObject()) {
					dict.dest = static_cast<JSObject>(dest).GetPrivate<Titanium::Buffer>();
				}
			}
			if (object.HasProperty("destPosition")) {
				dict.destPosition = static_cast<std::uint32_t>(object.GetProperty("destPosition"));
			}
			return dict;
		}

		JSObject EncodeStringDict_to_js(const JSContext& js_context, EncodeStringDict  value)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("charset",  js_context.CreateString(Constants::to_string(value.charset)));
			object.SetProperty("source",   js_context.CreateString(value.source));
			object.SetProperty("sourceLength",   js_context.CreateNumber(value.sourceLength));
			object.SetProperty("sourcePosition", js_context.CreateNumber(value.sourcePosition));
			object.SetProperty("destPosition", js_context.CreateNumber(value.destPosition));
			if (value.dest) {
				object.SetProperty("dest", value.dest->get_object());
			} else {
				object.SetProperty("dest", js_context.CreateNull());
			}
			return object;
		}
		
	} // namespace Codec
} // namespace Titanium