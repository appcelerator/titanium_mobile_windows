/**
 * TitaniumKit
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_CONSTANTS_HPP_
#define _TITANIUM_CALENDAR_CONSTANTS_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_set>
#include <functional>

#define ENUM_CONVERSIONS_CALENDAR(NAME) \
static std::string to_string(const NAME&) TITANIUM_NOEXCEPT; \
static NAME to_##NAME(const std::string&) TITANIUM_NOEXCEPT; \
static NAME to_##NAME(std::underlying_type<NAME>::type) TITANIUM_NOEXCEPT; \
static std::underlying_type<NAME>::type to_underlying_type(const NAME&) TITANIUM_NOEXCEPT;

namespace Titanium
{
	namespace Calendar
	{
		/*!
		  @enum

		  @abstract Attendee role

		  @constant UNKNOWN Attendee role is unknown.
		  @constant CHAIR Attendee role is chair.
		  @constant NON_PARTICIPANT Attendee is not a participant.
		  @constant OPTIONAL Attendee is optional.
		  @constant REQUIRED Attendee is required.
		*/
		enum class TITANIUMKIT_EXPORT ATTENDEE_ROLE {
			UNKNOWN,
			CHAIR,
			NON_PARTICIPANT,
			OPTIONAL_ARTICIPANT,
			REQUIRED
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.Calendar.calendarAuthorization property.

		  @constant AUTHORIZED A calendarAuthorization value indicating that the application is authorized to use events in the Calendar. 
		  @constant DENIED A calendarAuthorization value indicating that the application is not authorized to use events in the Calendar.
		  @constant RESTRICTED A calendarAuthorization value indicating that the application is not authorized to use events in the Calendar.
		  @constant UNKNOWN A calendarAuthorization value indicating that the authorization state is unknown.
		*/
		enum class TITANIUMKIT_EXPORT AUTHORIZATION {
			AUTHORIZED,
			DENIED,
			RESTRICTED,
			UNKNOWN
		};

		/*!
		  @enum

		  @abstract Calendar attendee status

		  @constant NONE Attendee status is none
		  @constant UNKNOWN Attendee status is unknown
		  @constant PENDING Attendee status is pending
		  @constant ACCEPTED Attendee status is accepted
		  @constant DECLINED Attendee status is declined
		  @constant INVITED Attendee status is invited
		  @constant IN_PROCESS Attendee status is in process
		  @constant TENTATIVE Attendee status is tentative
		*/
		enum class TITANIUMKIT_EXPORT ATTENDEE_STATUS {
			NONE,
			UNKNOWN,
			PENDING,
			ACCEPTED,
			DECLINED,
			INVITED,
			IN_PROCESS,
			TENTATIVE
		};

		/*!
		  @enum

		  @abstract Calendar attendee type

		  @constant NONE There is no attendee type.
		  @constant UNKNOWN Attendee type is unknown
		  @constant GROUP Attendee type is group
		  @constant PERSON Attendee type is person
		  @constant REQUIRED Attendee type is required
		  @constant RESOURCE Attendee type is resource
		  @constant ROOM Attendee type is room
		*/
		enum class TITANIUMKIT_EXPORT ATTENDEE_TYPE {
			NONE,
			UNKNOWN,
			GROUP,
			PERSON,
			REQUIRED,
			RESOURCE,
			ROOM
		};

		/*!
		  @enum

		  @abstract Calendar event availability

		  @constant BUSY Event has a busy availability setting.
		  @constant FREE Event has a free availability setting.
		  @constant NOTSUPPORTED Availability settings are not supported by the event's calendar.
		  @constant TENTATIVE Event has a tentative availability setting.
		  @constant UNAVAILABLE Event has a unavailable availability setting.
		*/
		enum class TITANIUMKIT_EXPORT AVAILABILITY {
			BUSY,
			FREE,
			NOTSUPPORTED,
			TENTATIVE,
			UNAVAILABLE
		};	

		/*!
		  @enum

		  @abstract Method by which reminder will be delivered.

		  @constant DEFAULT Reminder default delivery method.
		  @constant ALERT Reminder alert delivery method.
		  @constant EMAIL Reminder email delivery method.
		  @constant SMS Reminder SMS delivery method.
		*/
		enum class TITANIUMKIT_EXPORT METHOD {
			DEFAULT,
			ALERT,
			EMAIL,
			SMS
		};

		/*!
		  @enum

		  @abstract Frequency of the recurrence rule.

		  @constant DAILY Indicates a daily recurrence rule for a events reccurance frequency.
		  @constant WEEKLY Indicates a weekly recurrence rule for a events reccurance frequency.
		  @constant MONTHLY Indicates a monthly recurrence rule for a events reccurance frequency.
		  @constant YEARLY Indicates a yearly recurrence rule for a events reccurance frequency.
		*/
		enum class TITANIUMKIT_EXPORT RECURRENCEFREQUENCY {
			DAILY,
			WEEKLY,
			MONTHLY,
			YEARLY
		};	

		/*!
		  @enum

		  @abstract Status of the event.

		  @constant NONE Event has no status.
		  @constant CANCELLED Event canceled status.
		  @constant CANCELED Event canceled status.
		  @constant CONFIRMED Event confirmed status.
		  @constant TENTATIVE Event tentative status.
		*/
		enum class TITANIUMKIT_EXPORT STATUS {
			NONE,
			CANCELLED,
			CANCELED,
			CONFIRMED,
			TENTATIVE
		};

		/*!
		  @enum

		  @abstract Status of the event.

		  @constant FUTUREEVENTS A save/remove event value, indicating modifications to this event instance should also affect future instances of this event.
		  @constant THISEVENT A save/remove event value, indicating modifications to this event instance should affect only this instance.
		*/
		enum class TITANIUMKIT_EXPORT SPAN {
			FUTUREEVENTS,
			THISEVENT
		};

		/*!
		  @enum

		  @abstract Visibility of the event.

		  @constant DEFAULT Default visibility.
		  @constant PUBLIC Public visibility.
		  @constant PRIVATE Private visibility.
		  @constant CONFIDENTIAL Confidential visibility.
		*/
		enum class TITANIUMKIT_EXPORT VISIBILITY {
			DEFAULT,
			PUBLIC,
			PRIVATE,
			CONFIDENTIAL
		};	
	} // namespace Calendar
}  // namespace Titanium

namespace std
{

	template <>
	struct hash<Titanium::Calendar::AUTHORIZATION>
	{
		using argument_type = Titanium::Calendar::AUTHORIZATION;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::ATTENDEE_ROLE>
	{
		using argument_type = Titanium::Calendar::ATTENDEE_ROLE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::ATTENDEE_STATUS>
	{
		using argument_type = Titanium::Calendar::ATTENDEE_STATUS;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::ATTENDEE_TYPE>
	{
		using argument_type = Titanium::Calendar::ATTENDEE_TYPE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::AVAILABILITY>
	{
		using argument_type = Titanium::Calendar::AVAILABILITY;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::METHOD>
	{
		using argument_type = Titanium::Calendar::METHOD;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::RECURRENCEFREQUENCY>
	{
		using argument_type = Titanium::Calendar::RECURRENCEFREQUENCY;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::STATUS>
	{
		using argument_type = Titanium::Calendar::STATUS;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::SPAN>
	{
		using argument_type = Titanium::Calendar::SPAN;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Calendar::VISIBILITY>
	{
		using argument_type = Titanium::Calendar::VISIBILITY;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};
}  // namespace std

namespace Titanium
{
	namespace Calendar
	{
		class TITANIUMKIT_EXPORT Constants final
		{
		public:
			ENUM_CONVERSIONS_CALENDAR(AUTHORIZATION)
			ENUM_CONVERSIONS_CALENDAR(ATTENDEE_ROLE)
			ENUM_CONVERSIONS_CALENDAR(ATTENDEE_STATUS)
			ENUM_CONVERSIONS_CALENDAR(ATTENDEE_TYPE)
			ENUM_CONVERSIONS_CALENDAR(AVAILABILITY)
			ENUM_CONVERSIONS_CALENDAR(METHOD)
			ENUM_CONVERSIONS_CALENDAR(RECURRENCEFREQUENCY)
			ENUM_CONVERSIONS_CALENDAR(SPAN)
			ENUM_CONVERSIONS_CALENDAR(STATUS)
			ENUM_CONVERSIONS_CALENDAR(VISIBILITY)
		};
	} // namespace Calendar
}  // namespace Titanium

#endif  // _TITANIUM_CALENDAR_CONSTANTS_HPP_
