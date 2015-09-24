/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Constants.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include <unordered_map>
#include <mutex>

// TODO Move the constants into the proxies they're used solely? i.e. AUTHORIZATION into ContactsModule, KIND into Contacts.Person, SORT into Contacts.Group?

namespace Titanium
{
	namespace Contacts
	{
		std::string Constants::to_string(const AUTHORIZATION& authorization) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "AUTHORIZATION::UNKNOWN";
			static std::unordered_map<AUTHORIZATION, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[AUTHORIZATION::AUTHORIZED]  = "AUTHORIZATION_AUTHORIZED";
				map[AUTHORIZATION::DENIED] 		= "AUTHORIZATION_DENIED";
				map[AUTHORIZATION::RESTRICTED]  = "AUTHORIZATION_RESTRICTED";
				map[AUTHORIZATION::UNKNOWN]     = "AUTHORIZATION_UNKNOWN";
			});

			std::string string = unknown_string;
			const auto position = map.find(authorization);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		AUTHORIZATION Constants::to_AUTHORIZATION(const std::string& authorizationName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, AUTHORIZATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["AUTHORIZATION_AUTHORIZED"]     = AUTHORIZATION::AUTHORIZED;
				map["AUTHORIZATION_DENIED"] 		= AUTHORIZATION::DENIED;
				map["AUTHORIZATION_RESTRICTED"]    	= AUTHORIZATION::RESTRICTED;
				map["AUTHORIZATION_UNKNOWN"]      	= AUTHORIZATION::UNKNOWN;
			});

			AUTHORIZATION authorization = AUTHORIZATION::UNKNOWN;
			const auto position = map.find(authorizationName);
			if (position != map.end()) {
				authorization = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_AUTHORIZATION: Titanium::Contacts::AUTHORIZATION with name '", authorizationName, "' does not exist");
			}

			return authorization;
		}

		AUTHORIZATION Constants::to_AUTHORIZATION(std::underlying_type<AUTHORIZATION>::type authorization_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<AUTHORIZATION>::type, AUTHORIZATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::AUTHORIZED)]  = AUTHORIZATION::AUTHORIZED;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::DENIED)] 		= AUTHORIZATION::DENIED;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::RESTRICTED)]  = AUTHORIZATION::RESTRICTED;
				map[static_cast<std::underlying_type<AUTHORIZATION>::type>(AUTHORIZATION::UNKNOWN)]     = AUTHORIZATION::UNKNOWN;
			});

			AUTHORIZATION authorization = AUTHORIZATION::UNKNOWN;
			const auto position = map.find(authorization_underlying_type);
			if (position != map.end()) {
				authorization = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_AUTHORIZATION: Titanium::Contacts::AUTHORIZATION with value '", authorization_underlying_type, "' does not exist");
			}

			return authorization;
		}

		std::underlying_type<AUTHORIZATION>::type Constants::to_underlying_type(const AUTHORIZATION& authorization) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<AUTHORIZATION>::type>(authorization);
		}

		std::string Constants::to_string(const KIND& kind) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "KIND::UNKNOWN";
			static std::unordered_map<KIND, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[KIND::PERSON]		= "CONTACTS_KIND_PERSON";
				map[KIND::ORGANIZATION] = "CONTACTS_KIND_ORGANIZATION";
			});

			std::string string = unknown_string;
			const auto position = map.find(kind);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		KIND Constants::to_KIND(const std::string& name) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, KIND> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["CONTACTS_KIND_PERSON"]			= KIND::PERSON;
				map["CONTACTS_KIND_ORGANIZATION"]	= KIND::ORGANIZATION;
			});

			KIND kind = KIND::PERSON;
			const auto position = map.find(name);
			if (position != map.end()) {
				kind = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_KIND: Titanium::Contacts::KIND with name '", name, "' does not exist");
			}

			return kind;
		}

		KIND Constants::to_KIND(std::underlying_type<KIND>::type underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<KIND>::type, KIND> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<KIND>::type>(KIND::PERSON)]		= KIND::PERSON;
				map[static_cast<std::underlying_type<KIND>::type>(KIND::ORGANIZATION)]	= KIND::ORGANIZATION;
			});

			KIND kind = KIND::PERSON;
			const auto position = map.find(underlying_type);
			if (position != map.end()) {
				kind = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_KIND: Titanium::Contacts::KIND with value '", underlying_type, "' does not exist");
			}

			return kind;
		}

		std::underlying_type<KIND>::type Constants::to_underlying_type(const KIND& kind) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<KIND>::type>(kind);
		}

		std::string Constants::to_string(const SORT& kind) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "SORT::UNKNOWN";
			static std::unordered_map<SORT, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[SORT::FIRST_NAME]	= "CONTACTS_SORT_FIRST_NAME";
				map[SORT::LAST_NAME]	= "CONTACTS_SORT_LAST_NAME";
			});

			std::string string = unknown_string;
			const auto position = map.find(kind);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		SORT Constants::to_SORT(const std::string& name) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, SORT> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["CONTACTS_SORT_FIRST_NAME"] = SORT::FIRST_NAME;
				map["CONTACTS_SORT_LAST_NAMEN"] = SORT::LAST_NAME;
			});

			SORT kind = SORT::FIRST_NAME;
			const auto position = map.find(name);
			if (position != map.end()) {
				kind = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_SORT: Titanium::Contacts::SORT with name '", name, "' does not exist");
			}

			return kind;
		}

		SORT Constants::to_SORT(std::underlying_type<SORT>::type underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<SORT>::type, SORT> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<SORT>::type>(SORT::FIRST_NAME)]	= SORT::FIRST_NAME;
				map[static_cast<std::underlying_type<SORT>::type>(SORT::LAST_NAME)]		= SORT::LAST_NAME;
			});

			SORT sort = SORT::FIRST_NAME;
			const auto position = map.find(underlying_type);
			if (position != map.end()) {
				sort = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_SORT: Titanium::Contacts::SORT with value '", underlying_type, "' does not exist");
			}

			return sort;
		}

		std::underlying_type<SORT>::type Constants::to_underlying_type(const SORT& sort) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<SORT>::type>(sort);
		}
	} // namespace Contacts
}  // namespace Titanium
