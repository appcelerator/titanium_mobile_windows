/**
 * TitaniumKit Titanium.Calendar.Event
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Calendar/Event.hpp"
#include "Titanium/Calendar/Alert.hpp"
#include "Titanium/Calendar/Attendee.hpp"
#include "Titanium/Calendar/RecurrenceRule.hpp"
#include "Titanium/Calendar/Reminder.hpp"

#define CREATE_TITANIUM_CALENDAR(NAME) \
  static auto NAME##_ctor = this_object; \
  static std::once_flag of; \
  std::call_once(of, [=] {\
  JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue Calendar_property = Titanium.GetProperty("Calendar"); \
  TITANIUM_ASSERT(Calendar_property.IsObject()); \
  JSObject Calendar = static_cast<JSObject>(Calendar_property); \
  JSValue NAME##_property = Calendar.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  NAME##_ctor = static_cast<JSObject>(NAME##_property); \
  });\
  auto NAME##_obj = NAME##_ctor.CallAsConstructor(); \
  Titanium::Module::applyProperties(parameters, NAME##_obj);

namespace Titanium
{
	namespace Calendar
	{

		void Event::addRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT
		{
			recurrenceRules__.push_back(rule);
		}

		void Event::removeRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT
		{
			recurrenceRules__.erase(std::find(recurrenceRules__.begin(), recurrenceRules__.end(), rule));
		}

		bool Event::refresh(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::refresh: Unimplemented");
			return false;
		}

		bool Event::remove(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::remove: Unimplemented");
			return false;
		}

		bool Event::save(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::save: Unimplemented");
			return false;
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Alert>> Event::get_alerts() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::get_alerts: Unimplemented");
			return std::vector<std::shared_ptr<Titanium::Calendar::Alert>>();
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Attendee>> Event::get_attendees() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::get_attendees: Unimplemented");
			return std::vector<std::shared_ptr<Titanium::Calendar::Attendee>>();
		}

		void Event::createAlert(const std::shared_ptr<Titanium::Calendar::Alert>&) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::createAlert: Unimplemented");
		}

		void Event::createReminder(const std::shared_ptr<Titanium::Calendar::Reminder>&) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::createReminder: Unimplemented");
		}

		std::vector<std::shared_ptr<Titanium::Calendar::RecurrenceRule>> Event::get_recurrenceRules() const TITANIUM_NOEXCEPT
		{
			return recurrenceRules__;
		}

		void Event::set_recurrenceRules(const std::vector<std::shared_ptr<Titanium::Calendar::RecurrenceRule>>& recurrenceRules) TITANIUM_NOEXCEPT
		{
			recurrenceRules__ = recurrenceRules;
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Reminder>> Event::get_reminders() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::get_reminders: Unimplemented");
			return std::vector<std::shared_ptr<Titanium::Calendar::Reminder>>();
		}

		std::string Event::get_calendarID() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Event::get_calendarID: Unimplemented");
			return "";
		}

		TITANIUM_PROPERTY_READWRITE(Event, boost::optional<std::chrono::system_clock::time_point>, begin);
		TITANIUM_PROPERTY_READWRITE(Event, boost::optional<std::chrono::system_clock::time_point>, end);
		TITANIUM_PROPERTY_READWRITE(Event, Titanium::Calendar::AVAILABILITY, availability);
		TITANIUM_PROPERTY_READWRITE(Event, Titanium::Calendar::VISIBILITY, visibility);
		TITANIUM_PROPERTY_READWRITE(Event, std::string, description);
		TITANIUM_PROPERTY_READWRITE(Event, std::string, id);
		TITANIUM_PROPERTY_READWRITE(Event, std::string, location);
		TITANIUM_PROPERTY_READWRITE(Event, std::string, notes);
		TITANIUM_PROPERTY_READWRITE(Event, std::string, title);
		TITANIUM_PROPERTY_READWRITE(Event, bool, allDay);
		TITANIUM_PROPERTY_READWRITE(Event, bool, hasAlarm);
		TITANIUM_PROPERTY_READWRITE(Event, bool, isDetached);

		Event::Event(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Calendar.Event")
			, allDay__(false)
			, isDetached__(false)
			, hasAlarm__(false)
		{
		}

		void Event::JSExportInitialize() 
		{
			JSExport<Event>::SetClassVersion(1);
			JSExport<Event>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Event, alerts);
			TITANIUM_ADD_PROPERTY_READONLY(Event, attendees);
			TITANIUM_ADD_PROPERTY(Event, recurrenceRules);
			TITANIUM_ADD_PROPERTY_READONLY(Event, reminders);
			TITANIUM_ADD_PROPERTY(Event, begin);
			TITANIUM_ADD_PROPERTY(Event, end);
			TITANIUM_ADD_PROPERTY(Event, availability);
			TITANIUM_ADD_PROPERTY(Event, visibility);
			TITANIUM_ADD_PROPERTY(Event, description);
			TITANIUM_ADD_PROPERTY_READONLY(Event, id);
			TITANIUM_ADD_PROPERTY(Event, location);
			TITANIUM_ADD_PROPERTY(Event, notes);
			TITANIUM_ADD_PROPERTY(Event, title);
			TITANIUM_ADD_PROPERTY(Event, allDay);
			TITANIUM_ADD_PROPERTY_READONLY(Event, hasAlarm);
			TITANIUM_ADD_PROPERTY_READONLY(Event, isDetached);
			TITANIUM_ADD_FUNCTION(Event, addRecurrenceRule);
			TITANIUM_ADD_FUNCTION(Event, createAlert);
			TITANIUM_ADD_FUNCTION(Event, createRecurrenceRule);
			TITANIUM_ADD_FUNCTION(Event, createReminder);
			TITANIUM_ADD_FUNCTION(Event, refresh);
			TITANIUM_ADD_FUNCTION(Event, save);
			TITANIUM_ADD_FUNCTION(Event, remove);
			TITANIUM_ADD_FUNCTION(Event, removeRecurrenceRule);
		}
 
 		TITANIUM_FUNCTION(Event, addRecurrenceRule)
		{
			ENSURE_OBJECT_AT_INDEX(rule, 0);
			addRecurrenceRule(rule.GetPrivate<RecurrenceRule>());
			return get_context().CreateUndefined();
		}

 		TITANIUM_FUNCTION(Event, createAlert)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_CALENDAR(Alert);
			createAlert(Alert_obj.GetPrivate<Titanium::Calendar::Alert>());
			return Alert_obj;
		}

 		TITANIUM_FUNCTION(Event, createRecurrenceRule)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_CALENDAR(RecurrenceRule);
			const auto rule_ptr = RecurrenceRule_obj.GetPrivate<RecurrenceRule>();
			rule_ptr->set_calendarID(get_calendarID());
			return RecurrenceRule_obj;
		}

 		TITANIUM_FUNCTION(Event, createReminder)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_CALENDAR(Reminder);
			createReminder(Reminder_obj.GetPrivate<Titanium::Calendar::Reminder>());
			return Reminder_obj;
		}

 		TITANIUM_FUNCTION(Event, refresh)
		{
			ENSURE_ENUM_AT_INDEX(span, 0, Titanium::Calendar::SPAN);
			return get_context().CreateBoolean(refresh(span));
		}

 		TITANIUM_FUNCTION(Event, removeRecurrenceRule)
		{
			ENSURE_OBJECT_AT_INDEX(rule, 0);
			removeRecurrenceRule(rule.GetPrivate<RecurrenceRule>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Event, remove)
		{
			ENSURE_ENUM_AT_INDEX(span, 0, Titanium::Calendar::SPAN);
			return get_context().CreateBoolean(remove(span));
		}

 		TITANIUM_FUNCTION(Event, save)
		{
			ENSURE_ENUM_AT_INDEX(span, 0, Titanium::Calendar::SPAN);
			return get_context().CreateBoolean(save(span));
		}

		TITANIUM_PROPERTY_GETTER_BOOL(Event, allDay);
		TITANIUM_PROPERTY_SETTER_BOOL(Event, allDay);
		TITANIUM_PROPERTY_GETTER_BOOL(Event, hasAlarm);
		TITANIUM_PROPERTY_GETTER_BOOL(Event, isDetached);
		TITANIUM_PROPERTY_GETTER_STRING(Event, description);
		TITANIUM_PROPERTY_SETTER_STRING(Event, description);
		TITANIUM_PROPERTY_GETTER_STRING(Event, id);
		TITANIUM_PROPERTY_GETTER_STRING(Event, location);
		TITANIUM_PROPERTY_SETTER_STRING(Event, location);
		TITANIUM_PROPERTY_GETTER_STRING(Event, notes);
		TITANIUM_PROPERTY_SETTER_STRING(Event, notes);
		TITANIUM_PROPERTY_GETTER_STRING(Event, title);
		TITANIUM_PROPERTY_SETTER_STRING(Event, title);
		TITANIUM_PROPERTY_GETTER_ENUM(Event, availability);
		TITANIUM_PROPERTY_SETTER_ENUM(Event, availability, Titanium::Calendar::AVAILABILITY);
		TITANIUM_PROPERTY_GETTER_ENUM(Event, visibility);
		TITANIUM_PROPERTY_SETTER_ENUM(Event, visibility, Titanium::Calendar::VISIBILITY);
		TITANIUM_PROPERTY_GETTER_DATE(Event, begin);
		TITANIUM_PROPERTY_SETTER_DATE(Event, begin);
		TITANIUM_PROPERTY_GETTER_DATE(Event, end);
		TITANIUM_PROPERTY_SETTER_DATE(Event, end);

		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(Event, alerts);
		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(Event, attendees);
		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(Event, recurrenceRules); 
		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(Event, reminders);
		TITANIUM_PROPERTY_SETTER_OBJECT_ARRAY(Event, recurrenceRules, Titanium::Calendar::RecurrenceRule);

	} // namespace Calendar
} // namespace Titanium
