/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiLogger.hpp"
#include "Titanium/Geolocation/Constants.hpp"
#include <unordered_map>
#include <mutex>

namespace Titanium
{
	namespace Geolocation
	{
		std::string Constants::to_string(const ACCURACY& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ACCURACY::Unknown";
			static std::unordered_map<ACCURACY, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ACCURACY::BEST] = "ACCURACY_BEST";
				map[ACCURACY::HIGH] = "ACCURACY_HIGH";
				map[ACCURACY::BEST_FOR_NAVIGATION] = "ACCURACY_BEST_FOR_NAVIGATION";
				map[ACCURACY::HUNDRED_METERS] = "ACCURACY_HUNDRED_METERS";
				map[ACCURACY::KILOMETER] = "ACCURACY_KILOMETER";
				map[ACCURACY::LOW] = "ACCURACY_LOW";
				map[ACCURACY::NEAREST_TEN_METERS] = "ACCURACY_NEAREST_TEN_METERS";
				map[ACCURACY::THREE_KILOMETERS] = "ACCURACY_THREE_KILOMETERS";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		std::string Constants::to_string(const ACTIVITYTYPE& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ACTIVITYTYPE::Unknown";
			static std::unordered_map<ACTIVITYTYPE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ACTIVITYTYPE::AUTOMOTIVE_NAVIGATION] = "ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION";
				map[ACTIVITYTYPE::FITNESS] = "ACTIVITYTYPE_FITNESS";
				map[ACTIVITYTYPE::OTHER] = "ACTIVITYTYPE_OTHER";
				map[ACTIVITYTYPE::OTHER_NAVIGATION] = "ACTIVITYTYPE_OTHER_NAVIGATION";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		std::string Constants::to_string(const AUTHORIZATION& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "AUTHORIZATION::Unknown";
			static std::unordered_map<AUTHORIZATION, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[AUTHORIZATION::ALWAYS] = "AUTHORIZATION_ALWAYS";
				map[AUTHORIZATION::AUTHORIZED] = "AUTHORIZATION_AUTHORIZED";
				map[AUTHORIZATION::DENIED] = "AUTHORIZATION_DENIED";
				map[AUTHORIZATION::RESTRICTED] = "AUTHORIZATION_RESTRICTED";
				map[AUTHORIZATION::UNKNOWN] = "AUTHORIZATION_UNKNOWN";
				map[AUTHORIZATION::WHEN_IN_USE] = "AUTHORIZATION_WHEN_IN_USE";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		std::string Constants::to_string(const ERROR& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ERROR::Unknown";
			static std::unordered_map<ERROR, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ERROR::DENIED] = "ERROR_DENIED";
				map[ERROR::HEADING_FAILIURE] = "ERROR_HEADING_FAILIURE";
				map[ERROR::LOCATION_UNKNOWN] = "ERROR_LOCATION_UNKNOWN";
				map[ERROR::NETWORK] = "ERROR_NETWORK";
				map[ERROR::REGION_MONITORING_DELAYED] = "ERROR_REGION_MONITORING_DELAYED";
				map[ERROR::REGION_MONITORING_DENIED] = "ERROR_REGION_MONITORING_DENIED";
				map[ERROR::REGION_MONITORING_FAILIURE] = "ERROR_REGION_MONITORING_FAILIURE";
				map[ERROR::TIMEOUT] = "ERROR_TIMEOUT";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		std::string Constants::to_string(const PROVIDER& fieldType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "PROVIDER::Unknown";
			static std::unordered_map<PROVIDER, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[PROVIDER::GPS] = "PROVIDER_GPS";
				map[PROVIDER::NETWORK] = "PROVIDER_NETWORK";
				map[PROVIDER::PASSIVE] = "PROVIDER_PASSIVE";
			});

			std::string string = unknown_string;
			const auto position = map.find(fieldType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ACCURACY Constants::to_ACCURACY(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ACCURACY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ACCURACY_BEST"] = ACCURACY::BEST;
				map["ACCURACY_HIGH"] = ACCURACY::HIGH;
				map["ACCURACY_BEST_FOR_NAVIGATION"] = ACCURACY::BEST_FOR_NAVIGATION;
				map["ACCURACY_HUNDRED_METERS"] = ACCURACY::HUNDRED_METERS;
				map["ACCURACY_KILOMETER"] = ACCURACY::KILOMETER;
				map["ACCURACY_LOW"] = ACCURACY::LOW;
				map["ACCURACY_NEAREST_TEN_METERS"] = ACCURACY::NEAREST_TEN_METERS;
				map["ACCURACY_THREE_KILOMETER"] = ACCURACY::THREE_KILOMETERS;
			});

			ACCURACY fieldType = ACCURACY::BEST;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ACCURACY: Titanium::Geolocation::ACCURACY with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		ACTIVITYTYPE Constants::to_ACTIVITYTYPE(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ACTIVITYTYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION"] = ACTIVITYTYPE::AUTOMOTIVE_NAVIGATION;
				map["ACTIVITYTYPE_FITNESS"] = ACTIVITYTYPE::FITNESS;
				map["ACTIVITYTYPE_OTHER"] = ACTIVITYTYPE::OTHER;
				map["ACTIVITYTYPE_OTHER_NAVIGATION"] = ACTIVITYTYPE::OTHER_NAVIGATION;
			});

			ACTIVITYTYPE fieldType = ACTIVITYTYPE::OTHER;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ACTIVITYTYPE: Titanium::Geolocation::ACTIVITYTYPE with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		AUTHORIZATION Constants::to_AUTHORIZATION(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, AUTHORIZATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["AUTHORIZATION_ALWAYS"] = AUTHORIZATION::ALWAYS;
				map["AUTHORIZATION_AUTHORIZED"] = AUTHORIZATION::AUTHORIZED;
				map["AUTHORIZATION_DENIED"] = AUTHORIZATION::DENIED;
				map["AUTHORIZATION_RESTRICTED"] = AUTHORIZATION::RESTRICTED;
				map["AUTHORIZATION_UNKNOWN"] = AUTHORIZATION::UNKNOWN;
				map["AUTHORIZATION_WHEN_IN_USE"] = AUTHORIZATION::WHEN_IN_USE;
			});

			AUTHORIZATION fieldType = AUTHORIZATION::UNKNOWN;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_AUTHORIZATION: Titanium::Geolocation::AUTHORIZATION with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		ERROR Constants::to_ERROR(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ERROR> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ERROR_DENIED"] = ERROR::DENIED;
				map["ERROR_HEADING_FAILIURE"] = ERROR::HEADING_FAILIURE;
				map["ERROR_LOCATION_UNKNOWN"] = ERROR::LOCATION_UNKNOWN;
				map["ERROR_NETWORK"] = ERROR::NETWORK;
				map["ERROR_REGION_MONITORING_DELAYED"] = ERROR::REGION_MONITORING_DELAYED;
				map["ERROR_REGION_MONITORING_DENIED"] = ERROR::REGION_MONITORING_DENIED;
				map["ERROR_REGION_MONITORING_FAILIURE"] = ERROR::REGION_MONITORING_FAILIURE;
				map["ERROR_TIMEOUT"] = ERROR::TIMEOUT;
			});

			ERROR fieldType = ERROR::LOCATION_UNKNOWN;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ERROR: Titanium::Geolocation::ERROR with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		PROVIDER Constants::to_PROVIDER(const std::string& fieldTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, PROVIDER> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["PROVIDER_GPS"] = PROVIDER::GPS;
				map["PROVIDER_NETWORK"] = PROVIDER::NETWORK;
				map["PROVIDER_PASSIVE"] = PROVIDER::PASSIVE;
			});

			PROVIDER fieldType = PROVIDER::GPS;
			const auto position = map.find(fieldTypeName);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_PROVIDER: Titanium::Geolocation::PROVIDER with name '", fieldTypeName, "' does not exist");
			}

			return fieldType;
		}

		ACCURACY Constants::to_ACCURACY(std::underlying_type<ACCURACY>::type ACCURACY_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ACCURACY>::type, ACCURACY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ACCURACY>::type>(ACCURACY::BEST)] = ACCURACY::BEST;
				map[static_cast<std::underlying_type<ACCURACY>::type>(ACCURACY::HIGH)] = ACCURACY::HIGH;
				map[static_cast<std::underlying_type<ACCURACY>::type>(ACCURACY::BEST_FOR_NAVIGATION)] = ACCURACY::BEST_FOR_NAVIGATION;
				map[static_cast<std::underlying_type<ACCURACY>::type>(ACCURACY::HUNDRED_METERS)] = ACCURACY::HUNDRED_METERS;
				map[static_cast<std::underlying_type<ACCURACY>::type>(ACCURACY::KILOMETER)] = ACCURACY::KILOMETER;
				map[static_cast<std::underlying_type<ACCURACY>::type>(ACCURACY::LOW)] = ACCURACY::LOW;
				map[static_cast<std::underlying_type<ACCURACY>::type>(ACCURACY::NEAREST_TEN_METERS)] = ACCURACY::NEAREST_TEN_METERS;
			});

			ACCURACY fieldType = ACCURACY::BEST;
			const auto position = map.find(ACCURACY_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ACCURACY: Titanium::Geolocation::ACCURACY with value '", ACCURACY_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		ACTIVITYTYPE Constants::to_ACTIVITYTYPE(std::underlying_type<ACTIVITYTYPE>::type ACTIVITYTYPE_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ACTIVITYTYPE>::type, ACTIVITYTYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ACTIVITYTYPE>::type>(ACTIVITYTYPE::AUTOMOTIVE_NAVIGATION)] = ACTIVITYTYPE::AUTOMOTIVE_NAVIGATION;
				map[static_cast<std::underlying_type<ACTIVITYTYPE>::type>(ACTIVITYTYPE::FITNESS)] = ACTIVITYTYPE::FITNESS;
				map[static_cast<std::underlying_type<ACTIVITYTYPE>::type>(ACTIVITYTYPE::OTHER)] = ACTIVITYTYPE::OTHER;
				map[static_cast<std::underlying_type<ACTIVITYTYPE>::type>(ACTIVITYTYPE::OTHER_NAVIGATION)] = ACTIVITYTYPE::OTHER_NAVIGATION;
			});

			ACTIVITYTYPE fieldType = ACTIVITYTYPE::OTHER;
			const auto position = map.find(ACTIVITYTYPE_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ACTIVITYTYPE: Titanium::Geolocation::ACTIVITYTYPE with value '", ACTIVITYTYPE_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		AUTHORIZATION Constants::to_AUTHORIZATION(std::underlying_type<AUTHORIZATION>::type AUTHORIZATION_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<AUTHORIZATION>::type, AUTHORIZATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::ALWAYS)] = AUTHORIZATION::ALWAYS;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::AUTHORIZED)] = AUTHORIZATION::AUTHORIZED;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::DENIED)] = AUTHORIZATION::DENIED;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::RESTRICTED)] = AUTHORIZATION::RESTRICTED;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::UNKNOWN)] = AUTHORIZATION::UNKNOWN;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::WHEN_IN_USE)] = AUTHORIZATION::WHEN_IN_USE;
			});

			AUTHORIZATION fieldType = AUTHORIZATION::UNKNOWN;
			const auto position = map.find(AUTHORIZATION_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_AUTHORIZATION: Titanium::Geolocation::AUTHORIZATION with value '", AUTHORIZATION_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		ERROR Constants::to_ERROR(std::underlying_type<ERROR>::type ERROR_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ERROR>::type, ERROR> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::DENIED)] = ERROR::DENIED;
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::HEADING_FAILIURE)] = ERROR::HEADING_FAILIURE;
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::LOCATION_UNKNOWN)] = ERROR::LOCATION_UNKNOWN;
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::NETWORK)] = ERROR::NETWORK;
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::REGION_MONITORING_DELAYED)] = ERROR::REGION_MONITORING_DELAYED;
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::REGION_MONITORING_DENIED)] = ERROR::REGION_MONITORING_DENIED;
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::REGION_MONITORING_FAILIURE)] = ERROR::REGION_MONITORING_FAILIURE;
				map[static_cast<std::underlying_type<ERROR>::type>(ERROR::TIMEOUT)] = ERROR::TIMEOUT;
			});

			ERROR fieldType = ERROR::LOCATION_UNKNOWN;
			const auto position = map.find(ERROR_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ERROR: Titanium::Geolocation::ERROR with value '", ERROR_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		PROVIDER Constants::to_PROVIDER(std::underlying_type<PROVIDER>::type PROVIDER_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<PROVIDER>::type, PROVIDER> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<PROVIDER>::type>(PROVIDER::GPS)] = PROVIDER::GPS;
				map[static_cast<std::underlying_type<PROVIDER>::type>(PROVIDER::NETWORK)] = PROVIDER::NETWORK;
				map[static_cast<std::underlying_type<PROVIDER>::type>(PROVIDER::PASSIVE)] = PROVIDER::PASSIVE;
			});

			PROVIDER fieldType = PROVIDER::GPS;
			const auto position = map.find(PROVIDER_underlying_type);
			if (position != map.end()) {
				fieldType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_PROVIDER: Titanium::Geolocation::PROVIDER with value '", PROVIDER_underlying_type, "' does not exist");
			}

			return fieldType;
		}

		std::underlying_type<ACCURACY>::type Constants::to_underlying_type(const ACCURACY& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ACCURACY>::type>(fieldType);
		}

		std::underlying_type<ACTIVITYTYPE>::type Constants::to_underlying_type(const ACTIVITYTYPE& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ACTIVITYTYPE>::type>(fieldType);
		}

		std::underlying_type<AUTHORIZATION>::type Constants::to_underlying_type(const AUTHORIZATION& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<AUTHORIZATION>::type>(fieldType);
		}

		std::underlying_type<ERROR>::type Constants::to_underlying_type(const ERROR& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ERROR>::type>(fieldType);
		}

		std::underlying_type<PROVIDER>::type Constants::to_underlying_type(const PROVIDER& fieldType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<PROVIDER>::type>(fieldType);
		}
	} // namespace Geolocation
} // namespace Titanium