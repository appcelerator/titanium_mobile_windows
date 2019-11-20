/**
 * TitaniumKit Titanium.Calendar.Calendar
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Calendar/UserCalendar.hpp"
#include "Titanium/Calendar/Event.hpp"

namespace Titanium
{
	namespace Calendar
	{

		TITANIUM_PROPERTY_READWRITE(UserCalendar, bool, hidden);
		TITANIUM_PROPERTY_READWRITE(UserCalendar, std::string, id);
		TITANIUM_PROPERTY_READWRITE(UserCalendar, std::string, name);

		UserCalendar::UserCalendar(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Calendar.Calendar")
			, hidden__(false)
		{
		}

		void UserCalendar::JSExportInitialize() 
		{
			JSExport<UserCalendar>::SetClassVersion(1);
			JSExport<UserCalendar>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(UserCalendar, hidden);
			TITANIUM_ADD_PROPERTY_READONLY(UserCalendar, id);
			TITANIUM_ADD_PROPERTY_READONLY(UserCalendar, name);

			TITANIUM_ADD_FUNCTION(UserCalendar, createEvent);
			TITANIUM_ADD_FUNCTION(UserCalendar, getEventById);
			TITANIUM_ADD_FUNCTION(UserCalendar, getEventsBetweenDates);
		}

		TITANIUM_PROPERTY_GETTER_BOOL(UserCalendar, hidden);
		TITANIUM_PROPERTY_GETTER_STRING(UserCalendar, id);
		TITANIUM_PROPERTY_GETTER_STRING(UserCalendar, name);

		std::shared_ptr<Titanium::Calendar::Event> UserCalendar::getEventById(const std::string& id) const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Calendar::getEventById: Unimplemented");
			return nullptr;
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Event>> UserCalendar::getEventsBetweenDates(std::chrono::time_point<std::chrono::system_clock> date1, std::chrono::time_point<std::chrono::system_clock> date2) const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Calendar::getEventsBetweenDates: Unimplemented");
			return std::vector<std::shared_ptr<Titanium::Calendar::Event>>();
		}

		std::shared_ptr<Titanium::Calendar::Event> UserCalendar::createEvent(JSObject& parameters) TITANIUM_NOEXCEPT
		{
			static auto Event_ctor = get_object();
			static std::once_flag of;
			std::call_once(of, [=] {
				JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
				JSObject Titanium = static_cast<JSObject>(Titanium_property);
				JSValue Calendar_property = Titanium.GetProperty("Calendar");
				JSObject Calendar = static_cast<JSObject>(Calendar_property);
				JSValue Event_property = Calendar.GetProperty("Event");
				Event_ctor = static_cast<JSObject>(Event_property);
			});
			auto Event_obj = Event_ctor.CallAsConstructor();
			Titanium::Module::applyProperties(parameters, Event_obj);
			return Event_obj.GetPrivate<Titanium::Calendar::Event>();
		}

		TITANIUM_FUNCTION(UserCalendar, createEvent)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			const auto event_ptr = createEvent(parameters);
			TITANIUM_ASSERT(event_ptr != nullptr);
			return event_ptr->get_object();
		}

		TITANIUM_FUNCTION(UserCalendar, getEventById)
		{
			ENSURE_STRING_AT_INDEX(id, 0);
			auto evt = getEventById(id);
			if (evt != nullptr) {
				return evt->get_object();
			}
			return get_context().CreateNull();
		}

		TITANIUM_FUNCTION(UserCalendar, getEventsBetweenDates)
		{
			ENSURE_ARGUMENT_INDEX(0);
			ENSURE_ARGUMENT_INDEX(1);

			const auto date1_msec = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<double>(arguments.at(0))));
 			const auto date1 = std::chrono::time_point<std::chrono::system_clock>(date1_msec);

			const auto date2_msec = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<double>(arguments.at(1))));
 			const auto date2 = std::chrono::time_point<std::chrono::system_clock>(date2_msec);

			const auto events = getEventsBetweenDates(date1, date2);
			std::vector<JSValue> values;
			for (auto value : events) {
				values.push_back(value->get_object());
			}
			return get_context().CreateArray(values); 
		}
	} // namespace Calendar
} // namespace Titanium
