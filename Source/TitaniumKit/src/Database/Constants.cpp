/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Database/Constants.hpp"
#include <unordered_map>
#include <mutex>

namespace Titanium
{
	namespace Database
	{
		std::string Constants::to_string(const FIELD_TYPE& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "FIELD_TYPE::Unknown";
			static std::unordered_map<FIELD_TYPE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[FIELD_TYPE::DOUBLE] = "FIELD_TYPE_DOUBLE";
				map[FIELD_TYPE::FLOAT] = "FIELD_TYPE_FLOAT";
				map[FIELD_TYPE::INT] = "FIELD_TYPE_INT";
				map[FIELD_TYPE::STRING] = "FIELD_TYPE_STRING";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		FIELD_TYPE Constants::to_FIELD_TYPE(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, FIELD_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["FIELD_TYPE_DOUBLE"] = FIELD_TYPE::DOUBLE;
				map["FIELD_TYPE_FLOAT"] = FIELD_TYPE::FLOAT;
				map["FIELD_TYPE_INT"] = FIELD_TYPE::INT;
				map["FIELD_TYPE_STRING"] = FIELD_TYPE::STRING;
			});

			FIELD_TYPE fieldType = FIELD_TYPE::DOUBLE;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_FIELD_TYPE: Titanium::Database::FIELD_TYPE with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		FIELD_TYPE Constants::to_FIELD_TYPE(std::underlying_type<FIELD_TYPE>::type field_type_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<FIELD_TYPE>::type, FIELD_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<FIELD_TYPE>::type>(FIELD_TYPE::DOUBLE)] = FIELD_TYPE::DOUBLE;
				map[static_cast<std::underlying_type<FIELD_TYPE>::type>(FIELD_TYPE::FLOAT)] = FIELD_TYPE::FLOAT;
				map[static_cast<std::underlying_type<FIELD_TYPE>::type>(FIELD_TYPE::INT)] = FIELD_TYPE::INT;
				map[static_cast<std::underlying_type<FIELD_TYPE>::type>(FIELD_TYPE::STRING)] = FIELD_TYPE::STRING;
			});

			FIELD_TYPE fieldType = FIELD_TYPE::DOUBLE;
			const auto position = map.find(field_type_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_FIELD_TYPE: Titanium::Database::FIELD_TYPE with value '", field_type_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		std::underlying_type<FIELD_TYPE>::type Constants::to_underlying_type(const FIELD_TYPE& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<FIELD_TYPE>::type>(fieldType);
		}
	} // namespace Database
} // namespace Titanium