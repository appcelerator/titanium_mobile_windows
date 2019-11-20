/**
 * Titanium.Calendar.Event for Windows
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_CALENDAR_EVENT_HPP_
#define _TITANIUMWINDOWS_CALENDAR_EVENT_HPP_

#include "TitaniumWindows_Ti_EXPORT.h"
#include "Titanium/Calendar/Event.hpp"
#include <vector>

namespace TitaniumWindows
{
	namespace Calendar
	{
		using namespace HAL;

		/*!
		  @class Event
		  @ingroup Titanium.Calendar.Event

		  @discussion This is the Titanium.Calendar.Event implementation for Windows.
		*/
		class TITANIUMWINDOWS_TI_EXPORT Event final : public Titanium::Calendar::Event, public JSExport<Event>
		{

		public:

			Event(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Event()               = default;
			Event(const Event&)            = default;
			Event& operator=(const Event&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Event(Event&&)                 = default;
			Event& operator=(Event&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual void addRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT override;
			virtual void removeRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT override;
			virtual bool refresh(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT override;
			virtual bool save(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT override;
			virtual bool remove(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT override;
			virtual std::string get_calendarID() const TITANIUM_NOEXCEPT override;
			virtual void createReminder(const std::shared_ptr<Titanium::Calendar::Reminder>&) TITANIUM_NOEXCEPT override;
			virtual void createAlert(const std::shared_ptr<Titanium::Calendar::Alert>&) TITANIUM_NOEXCEPT override;

			std::vector<std::shared_ptr<Titanium::Calendar::Alert>> Event::get_alerts() const TITANIUM_NOEXCEPT override;
			std::vector<std::shared_ptr<Titanium::Calendar::Attendee>> Event::get_attendees() const TITANIUM_NOEXCEPT override;
			std::vector<std::shared_ptr<Titanium::Calendar::Reminder>> Event::get_reminders() const TITANIUM_NOEXCEPT override;

			virtual void set_title(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_location(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_description(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_allDay(const bool&) TITANIUM_NOEXCEPT override;
			virtual void set_begin(const boost::optional<std::chrono::system_clock::time_point>&) TITANIUM_NOEXCEPT override;
			virtual void set_end(const boost::optional<std::chrono::system_clock::time_point>&) TITANIUM_NOEXCEPT override;
			virtual void set_visibility(const Titanium::Calendar::VISIBILITY&) TITANIUM_NOEXCEPT override;
			virtual void set_availability(const Titanium::Calendar::AVAILABILITY&) TITANIUM_NOEXCEPT override;
			virtual void set_recurrenceRules(const std::vector<std::shared_ptr<Titanium::Calendar::RecurrenceRule>>&) TITANIUM_NOEXCEPT override;

			void construct(Windows::ApplicationModel::Appointments::AppointmentStore^, Windows::ApplicationModel::Appointments::AppointmentCalendar^, Windows::ApplicationModel::Appointments::Appointment^ = nullptr);
			void updateObjectProperties();

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			Windows::ApplicationModel::Appointments::Appointment^ appointment__;
			Windows::ApplicationModel::Appointments::AppointmentStore^ appointmentStore__;
			Windows::ApplicationModel::Appointments::AppointmentCalendar^ appointmentCalendar__;
#pragma warning(pop)
		};
	}  // namespace Calendar
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_CALENDAR_EVENT_HPP_
