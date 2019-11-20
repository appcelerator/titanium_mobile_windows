/**
 * TitaniumKit
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Calendar/Constants.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include <unordered_map>
#include <mutex>

namespace Titanium
{
	namespace Calendar
	{
		std::string Constants::to_string(const AUTHORIZATION& authorization) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "AUTHORIZATION_UNKNOWN";
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
				TITANIUM_LOG_WARN("Constants::to_AUTHORIZATION: Titanium::Calendar::AUTHORIZATION with name '", authorizationName, "' does not exist");
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
				TITANIUM_LOG_WARN("Constants::to_AUTHORIZATION: Titanium::Calendar::AUTHORIZATION with value '", authorization_underlying_type, "' does not exist");
			}

			return authorization;
		}

		std::underlying_type<AUTHORIZATION>::type Constants::to_underlying_type(const AUTHORIZATION& authorization) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<AUTHORIZATION>::type>(authorization);
		}

		std::string Constants::to_string(const ATTENDEE_STATUS& status) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ATTENDEE_STATUS_UNKNOWN";
			static std::unordered_map<ATTENDEE_STATUS, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ATTENDEE_STATUS::NONE]       = "ATTENDEE_STATUS_NONE";
				map[ATTENDEE_STATUS::UNKNOWN]    = "ATTENDEE_STATUS_UNKNOWN";
				map[ATTENDEE_STATUS::PENDING]    = "ATTENDEE_STATUS_PENDING";
				map[ATTENDEE_STATUS::ACCEPTED]   = "ATTENDEE_STATUS_ACCEPTED";
				map[ATTENDEE_STATUS::DECLINED]   = "ATTENDEE_STATUS_DECLINED";
				map[ATTENDEE_STATUS::INVITED]    = "ATTENDEE_STATUS_INVITED";
				map[ATTENDEE_STATUS::IN_PROCESS] = "ATTENDEE_STATUS_IN_PROCESS";
				map[ATTENDEE_STATUS::TENTATIVE]  = "ATTENDEE_STATUS_TENTATIVE";
			});

			std::string string = unknown_string;
			const auto position = map.find(status);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ATTENDEE_STATUS Constants::to_ATTENDEE_STATUS(const std::string& statusName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ATTENDEE_STATUS> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ATTENDEE_STATUS_NONE"]     = ATTENDEE_STATUS::NONE;
				map["ATTENDEE_STATUS_UNKNOWN"] 	= ATTENDEE_STATUS::UNKNOWN;
				map["ATTENDEE_STATUS_PENDING"]  = ATTENDEE_STATUS::PENDING;
				map["ATTENDEE_STATUS_ACCEPTED"] = ATTENDEE_STATUS::ACCEPTED;
				map["ATTENDEE_STATUS_DECLINED"] = ATTENDEE_STATUS::DECLINED;
				map["ATTENDEE_STATUS_INVITED"]  = ATTENDEE_STATUS::INVITED;
				map["ATTENDEE_STATUS_IN_PROCESS"] = ATTENDEE_STATUS::IN_PROCESS;
				map["ATTENDEE_STATUS_TENTATIVE"]  = ATTENDEE_STATUS::TENTATIVE;
			});

			ATTENDEE_STATUS status = ATTENDEE_STATUS::UNKNOWN;
			const auto position = map.find(statusName);
			if (position != map.end()) {
				status = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTENDEE_STATUS: Titanium::Calendar::ATTENDEE_STATUS with name '", statusName, "' does not exist");
			}

			return status;
		}

		ATTENDEE_STATUS Constants::to_ATTENDEE_STATUS(std::underlying_type<ATTENDEE_STATUS>::type status_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ATTENDEE_STATUS>::type, ATTENDEE_STATUS> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::NONE)]       = ATTENDEE_STATUS::NONE;
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::UNKNOWN)]    = ATTENDEE_STATUS::UNKNOWN;
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::PENDING)]    = ATTENDEE_STATUS::PENDING;
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::ACCEPTED)]   = ATTENDEE_STATUS::ACCEPTED;
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::DECLINED)]   = ATTENDEE_STATUS::DECLINED;
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::INVITED)]    = ATTENDEE_STATUS::INVITED;
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::IN_PROCESS)] = ATTENDEE_STATUS::IN_PROCESS;
				map[static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(ATTENDEE_STATUS::TENTATIVE)]  = ATTENDEE_STATUS::TENTATIVE;
			});

			ATTENDEE_STATUS status = ATTENDEE_STATUS::UNKNOWN;
			const auto position = map.find(status_underlying_type);
			if (position != map.end()) {
				status = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTENDEE_STATUS: Titanium::Calendar::ATTENDEE_STATUS with value '", status_underlying_type, "' does not exist");
			}

			return status;
		}

		std::underlying_type<ATTENDEE_STATUS>::type Constants::to_underlying_type(const ATTENDEE_STATUS& status) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ATTENDEE_STATUS>::type>(status);
		}

		std::string Constants::to_string(const ATTENDEE_ROLE& role) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ATTENDEE_ROLE_UNKNOWN";
			static std::unordered_map<ATTENDEE_ROLE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ATTENDEE_ROLE::UNKNOWN]    = "ATTENDEE_ROLE_UNKNOWN";
				map[ATTENDEE_ROLE::CHAIR]      = "ATTENDEE_ROLE_CHAIR";
				map[ATTENDEE_ROLE::NON_PARTICIPANT] = "ATTENDEE_ROLE_NON_PARTICIPANT";
				map[ATTENDEE_ROLE::OPTIONAL_ARTICIPANT]   = "ATTENDEE_ROLE_OPTIONAL";
				map[ATTENDEE_ROLE::REQUIRED]   = "ATTENDEE_ROLE_REQUIRED";
			});

			std::string string = unknown_string;
			const auto position = map.find(role);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ATTENDEE_ROLE Constants::to_ATTENDEE_ROLE(const std::string& roleName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ATTENDEE_ROLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ATTENDEE_ROLE_UNKNOWN"]     = ATTENDEE_ROLE::UNKNOWN;
				map["ATTENDEE_ROLE_CHAIR"] 	= ATTENDEE_ROLE::CHAIR;
				map["ATTENDEE_ROLE_NON_PARTICIPANT"]  = ATTENDEE_ROLE::NON_PARTICIPANT;
				map["ATTENDEE_ROLE_OPTIONAL"] = ATTENDEE_ROLE::OPTIONAL_ARTICIPANT;
				map["ATTENDEE_ROLE_REQUIRED"] = ATTENDEE_ROLE::REQUIRED;
			});

			ATTENDEE_ROLE role = ATTENDEE_ROLE::UNKNOWN;
			const auto position = map.find(roleName);
			if (position != map.end()) {
				role = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTENDEE_ROLE: Titanium::Calendar::ATTENDEE_ROLE with name '", roleName, "' does not exist");
			}

			return role;
		}

		ATTENDEE_ROLE Constants::to_ATTENDEE_ROLE(std::underlying_type<ATTENDEE_ROLE>::type role_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ATTENDEE_ROLE>::type, ATTENDEE_ROLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ATTENDEE_ROLE>::type>(ATTENDEE_ROLE::UNKNOWN)]       = ATTENDEE_ROLE::UNKNOWN;
				map[static_cast<std::underlying_type<ATTENDEE_ROLE>::type>(ATTENDEE_ROLE::CHAIR)]    = ATTENDEE_ROLE::CHAIR;
				map[static_cast<std::underlying_type<ATTENDEE_ROLE>::type>(ATTENDEE_ROLE::NON_PARTICIPANT)]    = ATTENDEE_ROLE::NON_PARTICIPANT;
				map[static_cast<std::underlying_type<ATTENDEE_ROLE>::type>(ATTENDEE_ROLE::OPTIONAL_ARTICIPANT)]   = ATTENDEE_ROLE::OPTIONAL_ARTICIPANT;
				map[static_cast<std::underlying_type<ATTENDEE_ROLE>::type>(ATTENDEE_ROLE::REQUIRED)]   = ATTENDEE_ROLE::REQUIRED;
			});

			ATTENDEE_ROLE role = ATTENDEE_ROLE::UNKNOWN;
			const auto position = map.find(role_underlying_type);
			if (position != map.end()) {
				role = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTENDEE_ROLE: Titanium::Calendar::ATTENDEE_ROLE with value '", role_underlying_type, "' does not exist");
			}

			return role;
		}

		std::underlying_type<ATTENDEE_ROLE>::type Constants::to_underlying_type(const ATTENDEE_ROLE& role) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ATTENDEE_ROLE>::type>(role);
		}
		
		std::string Constants::to_string(const ATTENDEE_TYPE& type) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ATTENDEE_TYPE_UNKNOWN";
			static std::unordered_map<ATTENDEE_TYPE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ATTENDEE_TYPE::UNKNOWN]  = "ATTENDEE_TYPE_UNKNOWN";
				map[ATTENDEE_TYPE::NONE]     = "ATTENDEE_TYPE_NONE";
				map[ATTENDEE_TYPE::GROUP]    = "ATTENDEE_TYPE_GROUP";
				map[ATTENDEE_TYPE::PERSON]   = "ATTENDEE_TYPE_PERSON";
				map[ATTENDEE_TYPE::REQUIRED] = "ATTENDEE_TYPE_REQUIRED";
				map[ATTENDEE_TYPE::RESOURCE] = "ATTENDEE_TYPE_RESOURCE";
				map[ATTENDEE_TYPE::ROOM]     = "ATTENDEE_TYPE_ROOM";
			});

			std::string string = unknown_string;
			const auto position = map.find(type);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ATTENDEE_TYPE Constants::to_ATTENDEE_TYPE(const std::string& typeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ATTENDEE_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ATTENDEE_TYPE_UNKNOWN"]     = ATTENDEE_TYPE::UNKNOWN;
				map["ATTENDEE_TYPE_NONE"] 	= ATTENDEE_TYPE::NONE;
				map["ATTENDEE_TYPE_GROUP"]  = ATTENDEE_TYPE::GROUP;
				map["ATTENDEE_TYPE_PERSON"] = ATTENDEE_TYPE::PERSON;
				map["ATTENDEE_TYPE_REQUIRED"] = ATTENDEE_TYPE::REQUIRED;
				map["ATTENDEE_TYPE_RESOURCE"] = ATTENDEE_TYPE::RESOURCE;
				map["ATTENDEE_TYPE_ROOM"] = ATTENDEE_TYPE::ROOM;
			});

			ATTENDEE_TYPE type = ATTENDEE_TYPE::UNKNOWN;
			const auto position = map.find(typeName);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTENDEE_TYPE: Titanium::Calendar::ATTENDEE_TYPE with name '", typeName, "' does not exist");
			}

			return type;
		}

		ATTENDEE_TYPE Constants::to_ATTENDEE_TYPE(std::underlying_type<ATTENDEE_TYPE>::type type_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ATTENDEE_TYPE>::type, ATTENDEE_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(ATTENDEE_TYPE::UNKNOWN)]   = ATTENDEE_TYPE::UNKNOWN;
				map[static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(ATTENDEE_TYPE::NONE)]      = ATTENDEE_TYPE::NONE;
				map[static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(ATTENDEE_TYPE::GROUP)]     = ATTENDEE_TYPE::GROUP;
				map[static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(ATTENDEE_TYPE::PERSON)]    = ATTENDEE_TYPE::PERSON;
				map[static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(ATTENDEE_TYPE::REQUIRED)]  = ATTENDEE_TYPE::REQUIRED;
				map[static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(ATTENDEE_TYPE::RESOURCE)]  = ATTENDEE_TYPE::RESOURCE;
				map[static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(ATTENDEE_TYPE::ROOM)]      = ATTENDEE_TYPE::ROOM;
			});

			ATTENDEE_TYPE type = ATTENDEE_TYPE::UNKNOWN;
			const auto position = map.find(type_underlying_type);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTENDEE_TYPE: Titanium::Calendar::ATTENDEE_TYPE with value '", type_underlying_type, "' does not exist");
			}

			return type;
		}

		std::underlying_type<ATTENDEE_TYPE>::type Constants::to_underlying_type(const ATTENDEE_TYPE& type) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ATTENDEE_TYPE>::type>(type);
		}

		std::string Constants::to_string(const AVAILABILITY& type) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "AVAILABILITY_NOTSUPPORTED";
			static std::unordered_map<AVAILABILITY, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[AVAILABILITY::NOTSUPPORTED] = "AVAILABILITY_NOTSUPPORTED";
				map[AVAILABILITY::BUSY]         = "AVAILABILITY_BUSY";
				map[AVAILABILITY::FREE]         = "AVAILABILITY_FREE";
				map[AVAILABILITY::TENTATIVE]    = "AVAILABILITY_TENTATIVE";
				map[AVAILABILITY::UNAVAILABLE]  = "AVAILABILITY_UNAVAILABL";
			});

			std::string string = unknown_string;
			const auto position = map.find(type);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		AVAILABILITY Constants::to_AVAILABILITY(const std::string& typeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, AVAILABILITY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["AVAILABILITY_NOTSUPPORTED"] = AVAILABILITY::NOTSUPPORTED;
				map["AVAILABILITY_BUSY"]       = AVAILABILITY::BUSY;
				map["AVAILABILITY_FREE"]       = AVAILABILITY::FREE;
				map["AVAILABILITY_TENTATIVE"]  = AVAILABILITY::TENTATIVE;
				map["AVAILABILITY_UNAVAILABL"] = AVAILABILITY::UNAVAILABLE;
			});

			AVAILABILITY type = AVAILABILITY::NOTSUPPORTED;
			const auto position = map.find(typeName);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_AVAILABILITY: Titanium::Calendar::AVAILABILITY with name '", typeName, "' does not exist");
			}

			return type;
		}

		AVAILABILITY Constants::to_AVAILABILITY(std::underlying_type<AVAILABILITY>::type type_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<AVAILABILITY>::type, AVAILABILITY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<AVAILABILITY>::type>(AVAILABILITY::NOTSUPPORTED)]   = AVAILABILITY::NOTSUPPORTED;
				map[static_cast<std::underlying_type<AVAILABILITY>::type>(AVAILABILITY::BUSY)]      = AVAILABILITY::BUSY;
				map[static_cast<std::underlying_type<AVAILABILITY>::type>(AVAILABILITY::FREE)]     = AVAILABILITY::FREE;
				map[static_cast<std::underlying_type<AVAILABILITY>::type>(AVAILABILITY::TENTATIVE)]    = AVAILABILITY::TENTATIVE;
				map[static_cast<std::underlying_type<AVAILABILITY>::type>(AVAILABILITY::UNAVAILABLE)]  = AVAILABILITY::UNAVAILABLE;
			});

			AVAILABILITY type = AVAILABILITY::NOTSUPPORTED;
			const auto position = map.find(type_underlying_type);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_AVAILABILITY: Titanium::Calendar::AVAILABILITY with value '", type_underlying_type, "' does not exist");
			}

			return type;
		}

		std::underlying_type<AVAILABILITY>::type Constants::to_underlying_type(const AVAILABILITY& type) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<AVAILABILITY>::type>(type);
		}

		std::string Constants::to_string(const RECURRENCEFREQUENCY& type) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "RECURRENCEFREQUENCY_DAILY";
			static std::unordered_map<RECURRENCEFREQUENCY, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[RECURRENCEFREQUENCY::DAILY]   = "RECURRENCEFREQUENCY_DAILY";
				map[RECURRENCEFREQUENCY::WEEKLY]  = "RECURRENCEFREQUENCY_WEEKLY";
				map[RECURRENCEFREQUENCY::MONTHLY] = "RECURRENCEFREQUENCY_MONTHLY";
				map[RECURRENCEFREQUENCY::YEARLY]  = "RECURRENCEFREQUENCY_YEARLY";
			});

			std::string string = unknown_string;
			const auto position = map.find(type);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		RECURRENCEFREQUENCY Constants::to_RECURRENCEFREQUENCY(const std::string& typeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, RECURRENCEFREQUENCY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["RECURRENCEFREQUENCY_DAILY"]   = RECURRENCEFREQUENCY::DAILY;
				map["RECURRENCEFREQUENCY_WEEKLY"]  = RECURRENCEFREQUENCY::WEEKLY;
				map["RECURRENCEFREQUENCY_MONTHLY"] = RECURRENCEFREQUENCY::MONTHLY;
				map["RECURRENCEFREQUENCY_YEARLY"]  = RECURRENCEFREQUENCY::YEARLY;
			});

			RECURRENCEFREQUENCY type = RECURRENCEFREQUENCY::DAILY;
			const auto position = map.find(typeName);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_RECURRENCEFREQUENCY: Titanium::Calendar::RECURRENCEFREQUENCY with name '", typeName, "' does not exist");
			}

			return type;
		}

		RECURRENCEFREQUENCY Constants::to_RECURRENCEFREQUENCY(std::underlying_type<RECURRENCEFREQUENCY>::type type_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<RECURRENCEFREQUENCY>::type, RECURRENCEFREQUENCY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<RECURRENCEFREQUENCY>::type>(RECURRENCEFREQUENCY::DAILY)]   = RECURRENCEFREQUENCY::DAILY;
				map[static_cast<std::underlying_type<RECURRENCEFREQUENCY>::type>(RECURRENCEFREQUENCY::WEEKLY)]  = RECURRENCEFREQUENCY::WEEKLY;
				map[static_cast<std::underlying_type<RECURRENCEFREQUENCY>::type>(RECURRENCEFREQUENCY::MONTHLY)] = RECURRENCEFREQUENCY::MONTHLY;
				map[static_cast<std::underlying_type<RECURRENCEFREQUENCY>::type>(RECURRENCEFREQUENCY::YEARLY)]  = RECURRENCEFREQUENCY::YEARLY;
			});

			RECURRENCEFREQUENCY type = RECURRENCEFREQUENCY::DAILY;
			const auto position = map.find(type_underlying_type);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_RECURRENCEFREQUENCY: Titanium::Calendar::RECURRENCEFREQUENCY with value '", type_underlying_type, "' does not exist");
			}

			return type;
		}

		std::underlying_type<RECURRENCEFREQUENCY>::type Constants::to_underlying_type(const RECURRENCEFREQUENCY& type) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<RECURRENCEFREQUENCY>::type>(type);
		}

		std::string Constants::to_string(const STATUS& status) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "STATUS_NONE";
			static std::unordered_map<STATUS, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[STATUS::NONE]      = "STATUS_NONE";
				map[STATUS::CANCELLED] = "STATUS_CANCELLED";
				map[STATUS::CANCELED]  = "STATUS_CANCELED";
				map[STATUS::CONFIRMED] = "STATUS_CONFIRMED";
				map[STATUS::TENTATIVE] = "STATUS_TENTATIVE";
			});

			std::string string = unknown_string;
			const auto position = map.find(status);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		STATUS Constants::to_STATUS(const std::string& statusName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, STATUS> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["STATUS_NONE"]      = STATUS::NONE;
				map["STATUS_CANCELLED"]	= STATUS::CANCELLED;
				map["STATUS_CANCELED"] 	= STATUS::CANCELED;
				map["STATUS_CONFIRMED"]	= STATUS::CONFIRMED;
				map["STATUS_TENTATIVE"]	= STATUS::TENTATIVE;
			});

			STATUS status = STATUS::NONE;
			const auto position = map.find(statusName);
			if (position != map.end()) {
				status = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_STATUS: Titanium::Calendar::STATUS with name '", statusName, "' does not exist");
			}

			return status;
		}

		STATUS Constants::to_STATUS(std::underlying_type<STATUS>::type status_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<STATUS>::type, STATUS> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<STATUS>::type>(STATUS::NONE)]  	= STATUS::NONE;
				map[static_cast<std::underlying_type<STATUS>::type>(STATUS::CANCELLED)]	= STATUS::CANCELLED;
				map[static_cast<std::underlying_type<STATUS>::type>(STATUS::CANCELED)]  = STATUS::CANCELED;
				map[static_cast<std::underlying_type<STATUS>::type>(STATUS::CONFIRMED)] = STATUS::CONFIRMED;
				map[static_cast<std::underlying_type<STATUS>::type>(STATUS::TENTATIVE)] = STATUS::TENTATIVE;
			});

			STATUS status = STATUS::NONE;
			const auto position = map.find(status_underlying_type);
			if (position != map.end()) {
				status = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_STATUS: Titanium::Calendar::STATUS with value '", status_underlying_type, "' does not exist");
			}

			return status;
		}

		std::underlying_type<STATUS>::type Constants::to_underlying_type(const STATUS& status) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<STATUS>::type>(status);
		}

		std::string Constants::to_string(const SPAN& span) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "SPAN_UNKNOWN";
			static std::unordered_map<SPAN, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[SPAN::FUTUREEVENTS] = "SPAN_FUTUREEVENTS";
				map[SPAN::THISEVENT]     = "SPAN_THISEVENT";
			});

			std::string string = unknown_string;
			const auto position = map.find(span);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		SPAN Constants::to_SPAN(const std::string& spanName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, SPAN> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["SPAN_FUTUREEVENTS"] = SPAN::FUTUREEVENTS;
				map["SPAN_THISEVENT"]    = SPAN::THISEVENT;
			});

			SPAN span = SPAN::THISEVENT;
			const auto position = map.find(spanName);
			if (position != map.end()) {
				span = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_SPAN: Titanium::Calendar::SPAN with name '", spanName, "' does not exist");
			}

			return span;
		}

		SPAN Constants::to_SPAN(std::underlying_type<SPAN>::type span_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<SPAN>::type, SPAN> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<SPAN>::type>(SPAN::FUTUREEVENTS)]  = SPAN::FUTUREEVENTS;
				map[static_cast<std::underlying_type<SPAN>::type>(SPAN::THISEVENT)]     = SPAN::THISEVENT;
			});

			SPAN span = SPAN::THISEVENT;
			const auto position = map.find(span_underlying_type);
			if (position != map.end()) {
				span = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_SPAN: Titanium::Calendar::SPAN with value '", span_underlying_type, "' does not exist");
			}

			return span;
		}

		std::underlying_type<SPAN>::type Constants::to_underlying_type(const SPAN& span) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<SPAN>::type>(span);
		}

		std::string Constants::to_string(const VISIBILITY& type) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "VISIBILITY_DEFAULT";
			static std::unordered_map<VISIBILITY, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[VISIBILITY::DEFAULT]  = "VISIBILITY_DEFAULT";
				map[VISIBILITY::PUBLIC]   = "VISIBILITY_PUBLIC";
				map[VISIBILITY::PRIVATE]  = "VISIBILITY_PRIVATE";
				map[VISIBILITY::CONFIDENTIAL] = "VISIBILITY_CONFIDENTIAL";
			});

			std::string string = unknown_string;
			const auto position = map.find(type);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		VISIBILITY Constants::to_VISIBILITY(const std::string& typeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, VISIBILITY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["VISIBILITY_DEFAULT"] = VISIBILITY::DEFAULT;
				map["VISIBILITY_PUBLIC"]  = VISIBILITY::PUBLIC;
				map["VISIBILITY_PRIVATE"] = VISIBILITY::PRIVATE;
				map["VISIBILITY_CONFIDENTIAL"]  = VISIBILITY::CONFIDENTIAL;
			});

			VISIBILITY type = VISIBILITY::DEFAULT;
			const auto position = map.find(typeName);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_VISIBILITY: Titanium::Calendar::VISIBILITY with name '", typeName, "' does not exist");
			}

			return type;
		}

		VISIBILITY Constants::to_VISIBILITY(std::underlying_type<VISIBILITY>::type type_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<VISIBILITY>::type, VISIBILITY> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<VISIBILITY>::type>(VISIBILITY::DEFAULT)] = VISIBILITY::DEFAULT;
				map[static_cast<std::underlying_type<VISIBILITY>::type>(VISIBILITY::PUBLIC)]  = VISIBILITY::PUBLIC;
				map[static_cast<std::underlying_type<VISIBILITY>::type>(VISIBILITY::PRIVATE)] = VISIBILITY::PRIVATE;
				map[static_cast<std::underlying_type<VISIBILITY>::type>(VISIBILITY::CONFIDENTIAL)] = VISIBILITY::CONFIDENTIAL;
			});

			VISIBILITY type = VISIBILITY::DEFAULT;
			const auto position = map.find(type_underlying_type);
			if (position != map.end()) {
				type = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_VISIBILITY: Titanium::Calendar::VISIBILITY with value '", type_underlying_type, "' does not exist");
			}

			return type;
		}

		std::underlying_type<VISIBILITY>::type Constants::to_underlying_type(const VISIBILITY& type) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<VISIBILITY>::type>(type);
		}


		std::string Constants::to_string(const METHOD& method) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "METHOD_DEFAULT";
			static std::unordered_map<METHOD, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[METHOD::ALERT]   = "METHOD_ALERT";
				map[METHOD::EMAIL]   = "METHOD_EMAIL";
				map[METHOD::SMS]     = "METHOD_SMS";
				map[METHOD::DEFAULT] = "METHOD_DEFAULT";
			});

			std::string string = unknown_string;
			const auto position = map.find(method);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		METHOD Constants::to_METHOD(const std::string& methodName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, METHOD> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["METHOD_ALERT"]   = METHOD::ALERT;
				map["METHOD_EMAIL"]   = METHOD::EMAIL;
				map["METHOD_SMS"]     = METHOD::SMS;
				map["METHOD_DEFAULT"] = METHOD::DEFAULT;
			});

			METHOD method = METHOD::DEFAULT;
			const auto position = map.find(methodName);
			if (position != map.end()) {
				method = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_METHOD: Titanium::Calendar::METHOD with name '", methodName, "' does not exist");
			}

			return method;
		}

		METHOD Constants::to_METHOD(std::underlying_type<METHOD>::type method_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<METHOD>::type, METHOD> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<METHOD>::type>(METHOD::ALERT)]   = METHOD::ALERT;
				map[static_cast<std::underlying_type<METHOD>::type>(METHOD::EMAIL)]   = METHOD::EMAIL;
				map[static_cast<std::underlying_type<METHOD>::type>(METHOD::SMS)]     = METHOD::SMS;
				map[static_cast<std::underlying_type<METHOD>::type>(METHOD::DEFAULT)] = METHOD::DEFAULT;
			});

			METHOD method = METHOD::DEFAULT;
			const auto position = map.find(method_underlying_type);
			if (position != map.end()) {
				method = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_METHOD: Titanium::Calendar::METHOD with value '", method_underlying_type, "' does not exist");
			}

			return method;
		}

		std::underlying_type<METHOD>::type Constants::to_underlying_type(const METHOD& method) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<METHOD>::type>(method);
		}

	} // namespace Calendar
}  // namespace Titanium
