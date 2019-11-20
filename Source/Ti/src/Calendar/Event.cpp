/**
 * Titanium.Calendar.Event for Windows
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Calendar/Event.hpp"
#include "TitaniumWindows/Calendar.hpp"
#include "Titanium/Calendar/RecurrenceRule.hpp"
#include "Titanium/Calendar/Alert.hpp"
#include "Titanium/Calendar/Attendee.hpp"
#include "Titanium/Calendar/Reminder.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <ppltasks.h>
#include <concrt.h>
#include <collection.h>

#define CREATE_TITANIUM_CALENDAR(VARNAME, CLASSNAME) \
  static auto CLASSNAME##_ctor = get_context().CreateObject(); \
  static std::once_flag of; \
  std::call_once(of, [=] {\
  JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue Calendar_property = Titanium.GetProperty("Calendar"); \
  TITANIUM_ASSERT(Calendar_property.IsObject()); \
  JSObject Calendar = static_cast<JSObject>(Calendar_property); \
  JSValue CLASSNAME##_property = Calendar.GetProperty(#CLASSNAME); \
  TITANIUM_ASSERT(CLASSNAME##_property.IsObject()); \
  CLASSNAME##_ctor = static_cast<JSObject>(CLASSNAME##_property); \
  });\
  auto VARNAME = CLASSNAME##_ctor.CallAsConstructor();

namespace TitaniumWindows
{
	namespace Calendar
	{
		using namespace Windows::ApplicationModel::Appointments;

		Event::Event(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::Calendar::Event(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("Event::ctor Initialize");
		}

		void Event::JSExportInitialize()
		{
			JSExport<Event>::SetClassVersion(1);
			JSExport<Event>::SetParent(JSExport<Titanium::Calendar::Event>::Class());
		}

		void Event::construct(AppointmentStore^ store, Windows::ApplicationModel::Appointments::AppointmentCalendar^ calendar, Appointment^ appointment)
		{
			appointmentStore__ = store;
			appointmentCalendar__ = calendar;

			// appointment can be a nullptr.
			if (appointment != nullptr) {
				appointment__ = appointment;
				updateObjectProperties();
			}
		}

		void Event::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::Calendar::Event::postCallAsConstructor(js_context, arguments);
			appointment__ = ref new Appointment();
		}

		void Event::createAlert(const std::shared_ptr<Titanium::Calendar::Alert>& alert) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::createAlert(alert);

			Windows::Foundation::TimeSpan span;
			span.Duration = (alert->get_minutes().count() * 60) * 1000 * 10000LL; // 100-nanoseconds

			appointment__->Reminder = span;
		}

		void Event::createReminder(const std::shared_ptr<Titanium::Calendar::Reminder>& reminder) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::createReminder(reminder);

			Windows::Foundation::TimeSpan span;
			span.Duration = (reminder->get_minutes().count() * 60) * 1000 * 10000LL; // 100-nanoseconds

			appointment__->Reminder = span;
		}

		void Event::set_recurrenceRules(const std::vector<std::shared_ptr<Titanium::Calendar::RecurrenceRule>>& rules) TITANIUM_NOEXCEPT
		{
			recurrenceRules__.clear();
			appointment__->Recurrence = ref new AppointmentRecurrence();
			for (const auto rule : rules) {
				addRecurrenceRule(rule);
			}
		}

		void Event::set_title(const std::string& title) TITANIUM_NOEXCEPT 
		{
			Titanium::Calendar::Event::set_title(title);
			appointment__->Subject = TitaniumWindows::Utility::ConvertUTF8String(title);
		}

		void Event::set_location(const std::string& location) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::set_location(location);
			appointment__->Location = TitaniumWindows::Utility::ConvertUTF8String(location);
		}

		void Event::set_description(const std::string& description) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::set_description(description);
			appointment__->Details = TitaniumWindows::Utility::ConvertUTF8String(description);
			appointment__->DetailsKind = AppointmentDetailsKind::PlainText;
		}

		void Event::set_allDay(const bool& allDay) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::set_allDay(allDay);
			appointment__->AllDay = allDay;
		}

		void Event::set_begin(const boost::optional<std::chrono::system_clock::time_point>& begin) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::set_begin(begin);
			if (begin) {
				appointment__->StartTime = TitaniumWindows::Utility::GetDateTime(*begin);
				set_end(end__); // Update appointment duration
			}
		}

		void Event::set_end(const boost::optional<std::chrono::system_clock::time_point>& end) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::set_end(end);
			if (end) {
				Windows::Foundation::TimeSpan duration;
				duration.Duration = TitaniumWindows::Utility::GetDateTime(*end).UniversalTime - appointment__->StartTime.UniversalTime;
				appointment__->Duration = duration;
			}
		}

		void Event::set_visibility(const Titanium::Calendar::VISIBILITY& visibility) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::set_visibility(visibility);
			switch (visibility) {
			case Titanium::Calendar::VISIBILITY::PRIVATE:
				appointment__->Sensitivity = AppointmentSensitivity::Private;
				break;
			case Titanium::Calendar::VISIBILITY::PUBLIC:
				appointment__->Sensitivity = AppointmentSensitivity::Public;
				break;
			}
		}

		void Event::set_availability(const Titanium::Calendar::AVAILABILITY& availabitity) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::set_availability(availabitity);
			switch (availabitity) {
			case Titanium::Calendar::AVAILABILITY::BUSY:
				appointment__->BusyStatus = AppointmentBusyStatus::Busy;
				break;
			case Titanium::Calendar::AVAILABILITY::FREE:
				appointment__->BusyStatus = AppointmentBusyStatus::Free;
				break;
			case Titanium::Calendar::AVAILABILITY::TENTATIVE:
				appointment__->BusyStatus = AppointmentBusyStatus::Tentative;
				break;
			case Titanium::Calendar::AVAILABILITY::UNAVAILABLE:
				appointment__->BusyStatus = AppointmentBusyStatus::OutOfOffice;
				break;
			}
		}

		void Event::updateObjectProperties()
		{
			TITANIUM_ASSERT(appointment__ != nullptr);

			id__ = TitaniumWindows::Utility::ConvertUTF8String(appointment__->LocalId);
			title__ = TitaniumWindows::Utility::ConvertUTF8String(appointment__->Subject);
			location__ = TitaniumWindows::Utility::ConvertUTF8String(appointment__->Location);
			description__ = TitaniumWindows::Utility::ConvertUTF8String(appointment__->Details);
			allDay__ = appointment__->AllDay;
			begin__ = TitaniumWindows::Utility::GetDateTime(appointment__->StartTime);

			Windows::Foundation::DateTime endTime;
			endTime.UniversalTime = appointment__->StartTime.UniversalTime + appointment__->Duration.Duration;
			end__ = TitaniumWindows::Utility::GetDateTime(endTime);

			hasAlarm__ = (appointment__->Reminder != nullptr);

			switch (appointment__->Sensitivity)
			{
			case AppointmentSensitivity::Private:
				visibility__ = Titanium::Calendar::VISIBILITY::PRIVATE;
				break;
			case AppointmentSensitivity::Public:
				visibility__ = Titanium::Calendar::VISIBILITY::PUBLIC;
				break;
			default:
				visibility__ = Titanium::Calendar::VISIBILITY::DEFAULT;
			}

			switch (appointment__->BusyStatus)
			{
			case AppointmentBusyStatus::Busy:
				availability__ = Titanium::Calendar::AVAILABILITY::BUSY;
				break;
			case AppointmentBusyStatus::Free:
				availability__ = Titanium::Calendar::AVAILABILITY::FREE;
				break;
			case AppointmentBusyStatus::Tentative:
				availability__ = Titanium::Calendar::AVAILABILITY::TENTATIVE;
				break;
			case AppointmentBusyStatus::OutOfOffice:
				availability__ = Titanium::Calendar::AVAILABILITY::UNAVAILABLE;
				break;
			case AppointmentBusyStatus::WorkingElsewhere:
				availability__ = Titanium::Calendar::AVAILABILITY::BUSY;
				break;
			default:
				availability__ = Titanium::Calendar::AVAILABILITY::NOTSUPPORTED;
			}
		}

		std::string Event::get_calendarID() const TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(appointmentCalendar__ != nullptr);
			return TitaniumWindows::Utility::ConvertUTF8String(appointmentCalendar__->LocalId);
		}

		void Event::addRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::addRecurrenceRule(rule);

			TITANIUM_ASSERT(appointment__ != nullptr);
			auto recurrence = appointment__->Recurrence == nullptr ? ref new AppointmentRecurrence() : appointment__->Recurrence;

			switch (rule->get_frequency()) {
			case Titanium::Calendar::RECURRENCEFREQUENCY::DAILY:
				recurrence->Unit = AppointmentRecurrenceUnit::Daily;
				break;
			case Titanium::Calendar::RECURRENCEFREQUENCY::MONTHLY:
				recurrence->Unit = AppointmentRecurrenceUnit::Monthly;
				break;
			case Titanium::Calendar::RECURRENCEFREQUENCY::WEEKLY:
				recurrence->Unit = AppointmentRecurrenceUnit::Weekly;
				break;
			case Titanium::Calendar::RECURRENCEFREQUENCY::YEARLY:
				recurrence->Unit = AppointmentRecurrenceUnit::Yearly;
				break;
			}
			
			recurrence->Interval = rule->get_interval();

			for (const auto day : rule->get_daysOfTheWeek()) {
				auto dayOfWeek = AppointmentDaysOfWeek::None;
				switch (day.daysOfWeek)
				{
				case 1:
					dayOfWeek = AppointmentDaysOfWeek::Sunday;
					break;
				case 2:
					dayOfWeek = AppointmentDaysOfWeek::Monday;
					break;
				case 3:
					dayOfWeek = AppointmentDaysOfWeek::Tuesday;
					break;
				case 4:
					dayOfWeek = AppointmentDaysOfWeek::Wednesday;
					break;
				case 5:
					dayOfWeek = AppointmentDaysOfWeek::Thursday;
					break;
				case 6:
					dayOfWeek = AppointmentDaysOfWeek::Friday;
					break;
				case 7:
					dayOfWeek = AppointmentDaysOfWeek::Saturday;
					break;
				default:
					dayOfWeek = AppointmentDaysOfWeek::None;
				}
				recurrence->DaysOfWeek = recurrence->DaysOfWeek | dayOfWeek;
			}

			for (const auto day : rule->get_daysOfTheMonth()) {
				recurrence->Day = day;
			}

			const auto end = rule->get_end();
			if (end) {
				recurrence->Occurrences = end->occurrenceCount;
			}
		}

		void Event::removeRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT
		{
			Titanium::Calendar::Event::removeRecurrenceRule(rule);

			TITANIUM_ASSERT(appointment__ != nullptr);
			auto recurrence = appointment__->Recurrence;

			// Nothing to remove
			if (recurrence == nullptr) {
				return;
			}

			for (const auto day : rule->get_daysOfTheWeek()) {
				auto dayOfWeek = AppointmentDaysOfWeek::None;
				switch (day.daysOfWeek)
				{
				case 1:
					dayOfWeek = AppointmentDaysOfWeek::Sunday;
					break;
				case 2:
					dayOfWeek = AppointmentDaysOfWeek::Monday;
					break;
				case 3:
					dayOfWeek = AppointmentDaysOfWeek::Tuesday;
					break;
				case 4:
					dayOfWeek = AppointmentDaysOfWeek::Wednesday;
					break;
				case 5:
					dayOfWeek = AppointmentDaysOfWeek::Thursday;
					break;
				case 6:
					dayOfWeek = AppointmentDaysOfWeek::Friday;
					break;
				case 7:
					dayOfWeek = AppointmentDaysOfWeek::Saturday;
					break;
				default:
					dayOfWeek = AppointmentDaysOfWeek::None;
				}
				recurrence->DaysOfWeek = recurrence->DaysOfWeek & ~dayOfWeek;
			}
		}

		bool Event::refresh(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT
		{
			updateObjectProperties();
			return true;
		}

		bool Event::remove(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT
		{
			bool result = false;
			concurrency::create_task(appointmentCalendar__->DeleteAppointmentAsync(appointment__->LocalId)).then([this, &result](concurrency::task<void> task) {
				try {
					task.get();
					result = true;
				} catch (Platform::Exception^ e) {
					TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertUTF8String(e->Message));
				} catch (...) {
					TITANIUM_LOG_WARN("Exception during Event::save");
				}
			});
			return result;
		}

		bool Event::save(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT
		{
			bool result = false;
			concurrency::create_task(appointmentCalendar__->SaveAppointmentAsync(appointment__)).then([this, &result](concurrency::task<void> task) {
				try {
					task.get();
					updateObjectProperties();
					result = true;
				} catch (Platform::Exception^ e) {
					TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertUTF8String(e->Message));
				} catch (...) {
					TITANIUM_LOG_WARN("Exception during Event::save");
				}
			});
			return result;
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Alert>> Event::get_alerts() const TITANIUM_NOEXCEPT
		{
			std::vector<std::shared_ptr<Titanium::Calendar::Alert>> alerts;

			if (appointment__ == nullptr) {
				return alerts;
			}

			const auto reminder = appointment__->Reminder;
			if (reminder != nullptr) {
				const auto span = reminder->Value;
				CREATE_TITANIUM_CALENDAR(reminderObj, Alert);
				const auto reminder_ptr = reminderObj.GetPrivate<Titanium::Calendar::Alert>();

				Windows::Foundation::DateTime reminderTime;
				reminderTime.UniversalTime = appointment__->StartTime.UniversalTime - reminder->Value.Duration;
				reminder_ptr->set_alarmTime(TitaniumWindows::Utility::GetDateTime(reminderTime));

				reminder_ptr->set_absoluteDate(TitaniumWindows::Utility::GetDateTime(appointment__->StartTime));

				alerts.push_back(reminder_ptr);
			}
			return alerts;
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Attendee>> Event::get_attendees() const TITANIUM_NOEXCEPT
		{
			std::vector<std::shared_ptr<Titanium::Calendar::Attendee>> attendees;

			if (appointment__ == nullptr) {
				return attendees;
			}

			auto invitees = appointment__->Invitees;
			std::for_each(Windows::Foundation::Collections::begin(invitees), Windows::Foundation::Collections::end(invitees), [this](AppointmentInvitee^ invitee) {
				CREATE_TITANIUM_CALENDAR(attendeeObj, Attendee);
				const auto attendee_ptr = attendeeObj.GetPrivate<Titanium::Calendar::Attendee>();

				attendee_ptr->set_name(TitaniumWindows::Utility::ConvertUTF8String(invitee->DisplayName));

				switch (invitee->Role)
				{
				case AppointmentParticipantRole::RequiredAttendee:
					attendee_ptr->set_type(Titanium::Calendar::ATTENDEE_TYPE::REQUIRED);
					attendee_ptr->set_role(Titanium::Calendar::ATTENDEE_ROLE::REQUIRED);
					break;
				case AppointmentParticipantRole::OptionalAttendee:
					attendee_ptr->set_type(Titanium::Calendar::ATTENDEE_TYPE::NONE);
					attendee_ptr->set_role(Titanium::Calendar::ATTENDEE_ROLE::OPTIONAL_ARTICIPANT);
					break;
				case AppointmentParticipantRole::Resource:
					attendee_ptr->set_type(Titanium::Calendar::ATTENDEE_TYPE::RESOURCE);
					attendee_ptr->set_role(Titanium::Calendar::ATTENDEE_ROLE::UNKNOWN);
					break;
				default:
					attendee_ptr->set_type(Titanium::Calendar::ATTENDEE_TYPE::UNKNOWN);
					attendee_ptr->set_role(Titanium::Calendar::ATTENDEE_ROLE::UNKNOWN);
				}
			});

			return attendees;
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Reminder>> Event::get_reminders() const TITANIUM_NOEXCEPT
		{
			std::vector<std::shared_ptr<Titanium::Calendar::Reminder>> reminders;

			if (appointment__ == nullptr) {
				return reminders;
			}

			const auto reminder = appointment__->Reminder;
			if (reminder != nullptr) {
				const auto span = reminder->Value;
				CREATE_TITANIUM_CALENDAR(reminderObj, Reminder);
				const auto reminder_ptr = reminderObj.GetPrivate<Titanium::Calendar::Reminder>();
				TITANIUM_ASSERT(reminder_ptr != nullptr);
				reminder_ptr->set_minutes(TitaniumWindows::Utility::GetMinutes(reminder->Value));

				reminders.push_back(reminder_ptr);
			}
			return reminders;
		}

	}  // namespace Calendar
}  // namespace TitaniumWindows
