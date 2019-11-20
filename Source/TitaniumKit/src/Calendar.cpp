/**
 * TitaniumKit Titanium.Calendar
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Calendar.hpp"
#include "Titanium/Calendar/UserCalendar.hpp"
#include "Titanium/Calendar/Alert.hpp"
#include "Titanium/Calendar/Attendee.hpp"
#include "Titanium/Calendar/Event.hpp"
#include "Titanium/Calendar/RecurrenceRule.hpp"
#include "Titanium/Calendar/Reminder.hpp"
#include "Titanium/Calendar/UserCalendar.hpp"

namespace Titanium
{

	CalendarModule::CalendarModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.Calendar")
		, calendarAuthorization__(Titanium::Calendar::AUTHORIZATION::UNKNOWN)
		, alert__(JSExport<Titanium::Calendar::Alert>::Class())
		, attendee__(JSExport<Titanium::Calendar::Attendee>::Class())
		, event__(JSExport<Titanium::Calendar::Event>::Class())
		, recurrenceRule__(JSExport<Titanium::Calendar::RecurrenceRule>::Class())
		, reminder__(JSExport<Titanium::Calendar::Reminder>::Class())
		, calendar__(JSExport<Titanium::Calendar::UserCalendar>::Class())
	{
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, AUTHORIZATION_AUTHORIZED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AUTHORIZATION::AUTHORIZED));
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, AUTHORIZATION_DENIED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AUTHORIZATION::DENIED));
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, AUTHORIZATION_RESTRICTED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AUTHORIZATION::RESTRICTED));
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, AUTHORIZATION_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AUTHORIZATION::UNKNOWN));
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::UNKNOWN));

	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_PENDING)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::PENDING));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_ACCEPTED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::ACCEPTED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_DECLINED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::DECLINED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_TENTATIVE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::TENTATIVE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_INVITED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::INVITED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_NONE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::NONE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_STATUS_IN_PROCESS)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_STATUS::IN_PROCESS));

	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_ROLE_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_ROLE::UNKNOWN));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_ROLE_OPTIONAL)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_ROLE::OPTIONAL_ARTICIPANT));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_ROLE_REQUIRED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_ROLE::REQUIRED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_ROLE_CHAIR)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_ROLE::CHAIR));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_ROLE_NON_PARTICIPANT)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_ROLE::NON_PARTICIPANT));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_TYPE_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_TYPE::UNKNOWN));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_TYPE_PERSON)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_TYPE::PERSON));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_TYPE_ROOM)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_TYPE::ROOM));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_TYPE_RESOURCE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_TYPE::RESOURCE));

	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_TYPE_NONE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_TYPE::NONE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_TYPE_REQUIRED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_TYPE::REQUIRED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, ATTENDEE_TYPE_GROUP)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::ATTENDEE_TYPE::GROUP));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, AVAILABILITY_NOTSUPPORTED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AVAILABILITY::NOTSUPPORTED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, AVAILABILITY_BUSY)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AVAILABILITY::BUSY));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, AVAILABILITY_FREE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AVAILABILITY::FREE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, AVAILABILITY_TENTATIVE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AVAILABILITY::TENTATIVE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, AVAILABILITY_UNAVAILABLE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::AVAILABILITY::UNAVAILABLE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, METHOD_DEFAULT)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::METHOD::DEFAULT));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, METHOD_ALERT)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::METHOD::ALERT));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, METHOD_EMAIL)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::METHOD::EMAIL));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, METHOD_SMS)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::METHOD::SMS));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, RECURRENCEFREQUENCY_DAILY)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::RECURRENCEFREQUENCY::DAILY));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, RECURRENCEFREQUENCY_WEEKLY)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::RECURRENCEFREQUENCY::WEEKLY));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, RECURRENCEFREQUENCY_MONTHLY)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::RECURRENCEFREQUENCY::MONTHLY));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, RECURRENCEFREQUENCY_YEARLY)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::RECURRENCEFREQUENCY::YEARLY));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, SPAN_FUTUREEVENTS)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::SPAN::FUTUREEVENTS));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, SPAN_THISEVENT)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::SPAN::THISEVENT));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, STATUS_NONE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::STATUS::NONE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, STATUS_CANCELED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::STATUS::CANCELED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, STATUS_CANCELLED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::STATUS::CANCELLED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, STATUS_CONFIRMED)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::STATUS::CONFIRMED));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, STATUS_TENTATIVE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::STATUS::TENTATIVE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, VISIBILITY_CONFIDENTIAL)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::VISIBILITY::CONFIDENTIAL));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, VISIBILITY_DEFAULT)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::VISIBILITY::DEFAULT));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, VISIBILITY_PRIVATE)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::VISIBILITY::PRIVATE));
	}
	TITANIUM_PROPERTY_GETTER(CalendarModule, VISIBILITY_PUBLIC)
	{
		return get_context().CreateNumber(Titanium::Calendar::Constants::to_underlying_type(Titanium::Calendar::VISIBILITY::PUBLIC));
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, Alert)
	{
		return get_context().CreateObject(alert__);
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, Attendee)
	{
		return get_context().CreateObject(attendee__);
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, Event)
	{
		return get_context().CreateObject(event__);
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, RecurrenceRule)
	{
		return get_context().CreateObject(recurrenceRule__);
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, Reminder)
	{
		return get_context().CreateObject(reminder__);
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, Calendar)
	{
		return get_context().CreateObject(calendar__);
	}

	TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(CalendarModule, allAlerts);
	TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(CalendarModule, allCalendars);
	TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(CalendarModule, allEditableCalendars);
	TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(CalendarModule, selectableCalendars)

	TITANIUM_PROPERTY_GETTER(CalendarModule, calendarAuthorization)
	{
		return get_context().CreateNumber(static_cast<std::uint32_t>(calendarAuthorization__));
	}

	TITANIUM_PROPERTY_GETTER(CalendarModule, defaultCalendar)
	{
		const auto calendar = getDefaultCalendar();
		if (calendar) {
			return calendar->get_object();
		}
		return get_context().CreateNull();
	}

	std::vector<std::shared_ptr<Calendar::Alert>> CalendarModule::get_allAlerts() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::get_allAlerts: Unimplemented");
		return std::vector<std::shared_ptr<Calendar::Alert>>();
	}

	std::vector<std::shared_ptr<Calendar::UserCalendar>> CalendarModule::get_allCalendars() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::get_allCalendars: Unimplemented");
		return std::vector<std::shared_ptr<Calendar::UserCalendar>>();
	}

	std::vector<std::shared_ptr<Calendar::UserCalendar>> CalendarModule::get_allEditableCalendars() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::get_allEditableCalendars: Unimplemented");
		return std::vector<std::shared_ptr<Calendar::UserCalendar>>();
	}

	std::vector<std::shared_ptr<Calendar::UserCalendar>> CalendarModule::get_selectableCalendars() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::get_selectableCalendars: Unimplemented");
		return std::vector<std::shared_ptr<Calendar::UserCalendar>>();
	}

	std::shared_ptr<Calendar::UserCalendar> CalendarModule::getDefaultCalendar() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::getDefaultCalendar: Unimplemented");
		return nullptr;
	}

	std::shared_ptr<Calendar::UserCalendar> CalendarModule::getCalendarById(const std::string& id) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::getCalendarById: Unimplemented");
		return nullptr;
	}

	bool CalendarModule::hasCalendarPermissions() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::hasCalendarPermissions: Unimplemented");
		return false;
	}

	void CalendarModule::requestCalendarPermissions(JSObject& callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("CalendarModule::requestCalendarPermissions: Unimplemented");
	}

	void CalendarModule::JSExportInitialize()
	{
		JSExport<CalendarModule>::SetClassVersion(1);
		JSExport<CalendarModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_PENDING);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_ACCEPTED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_DECLINED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_TENTATIVE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_INVITED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_STATUS_IN_PROCESS);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_ROLE_UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_ROLE_OPTIONAL);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_ROLE_REQUIRED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_ROLE_CHAIR);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_ROLE_NON_PARTICIPANT);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_TYPE_UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_TYPE_PERSON);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_TYPE_ROOM);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_TYPE_RESOURCE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_TYPE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_TYPE_REQUIRED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, ATTENDEE_TYPE_GROUP);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AVAILABILITY_NOTSUPPORTED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AVAILABILITY_BUSY);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AVAILABILITY_FREE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AVAILABILITY_TENTATIVE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AVAILABILITY_UNAVAILABLE);
		
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AUTHORIZATION_AUTHORIZED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AUTHORIZATION_DENIED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AUTHORIZATION_RESTRICTED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, AUTHORIZATION_UNKNOWN);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, METHOD_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, METHOD_ALERT);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, METHOD_EMAIL);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, METHOD_SMS);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, RECURRENCEFREQUENCY_DAILY);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, RECURRENCEFREQUENCY_WEEKLY);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, RECURRENCEFREQUENCY_MONTHLY);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, RECURRENCEFREQUENCY_YEARLY);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, SPAN_FUTUREEVENTS);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, SPAN_THISEVENT);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, STATUS_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, STATUS_CANCELLED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, STATUS_CANCELED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, STATUS_CONFIRMED);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, STATUS_TENTATIVE);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, VISIBILITY_CONFIDENTIAL);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, VISIBILITY_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, VISIBILITY_PRIVATE);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, VISIBILITY_PUBLIC);

		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, Alert);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, Attendee);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, Event);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, RecurrenceRule);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, Reminder);
		TITANIUM_ADD_CONSTANT_PROPERTY(CalendarModule, Calendar);

		TITANIUM_ADD_PROPERTY_READONLY(CalendarModule, allAlerts);
		TITANIUM_ADD_PROPERTY_READONLY(CalendarModule, allCalendars);
		TITANIUM_ADD_PROPERTY_READONLY(CalendarModule, allEditableCalendars);
		TITANIUM_ADD_PROPERTY_READONLY(CalendarModule, calendarAuthorization);
		TITANIUM_ADD_PROPERTY_READONLY(CalendarModule, defaultCalendar);
		TITANIUM_ADD_PROPERTY_READONLY(CalendarModule, selectableCalendars);

		TITANIUM_ADD_FUNCTION(CalendarModule, getCalendarById);
		TITANIUM_ADD_FUNCTION(CalendarModule, hasCalendarPermissions);
		TITANIUM_ADD_FUNCTION(CalendarModule, requestCalendarPermissions);
	}

	CalendarModule& CalendarModule::AlertClass(const JSClass& alert) TITANIUM_NOEXCEPT
	{
		alert__ = alert;
		return *this;
	}

	CalendarModule& CalendarModule::AttendeeClass(const JSClass& attendee) TITANIUM_NOEXCEPT
	{
		attendee__ = attendee;
		return *this;
	}

	CalendarModule& CalendarModule::EventClass(const JSClass& event) TITANIUM_NOEXCEPT
	{
		event__ = event;
		return *this;
	}

	CalendarModule& CalendarModule::RecurrenceRuleClass(const JSClass& rule) TITANIUM_NOEXCEPT
	{
		recurrenceRule__ = rule;
		return *this;
	}

	CalendarModule& CalendarModule::ReminderClass(const JSClass& reminder) TITANIUM_NOEXCEPT
	{
		reminder__ = reminder;
		return *this;
	}

	CalendarModule& CalendarModule::CalendarClass(const JSClass& calendar) TITANIUM_NOEXCEPT
	{
		calendar__ = calendar;
		return *this;
	}

	TITANIUM_FUNCTION(CalendarModule, getCalendarById)
	{
		ENSURE_STRING_AT_INDEX(id, 0);
		auto calendar = getCalendarById(id);
		if (calendar != nullptr) {
			return calendar->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(CalendarModule, hasCalendarPermissions)
	{
		return get_context().CreateBoolean(hasCalendarPermissions());
	}

	TITANIUM_FUNCTION(CalendarModule, requestCalendarPermissions)
	{
		ENSURE_ARGUMENT_INDEX(0);
		const auto _0 = arguments.at(0);
		if (_0.IsObject()) {
			requestCalendarPermissions(static_cast<JSObject>(_0));
		}
		return get_context().CreateUndefined();
	}

} // namespace Titanium
