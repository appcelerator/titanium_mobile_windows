/**
 * Titanium.Calendar.Calendar for Windows
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Calendar/UserCalendar.hpp"
#include "TitaniumWindows/Calendar/Event.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <ppltasks.h>
#include <concrt.h>
#include <collection.h>

#define CREATE_TITANIUM_CALENDAR_EVENT(VARNAME, CTX) \
  static auto Event_ctor = CTX.CreateObject(); \
  static std::once_flag of; \
  std::call_once(of, [=] {\
  JSValue Titanium_property = CTX.get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue Parent_property = Titanium.GetProperty("Calendar"); \
  TITANIUM_ASSERT(Parent_property.IsObject()); \
  JSObject Calendar = static_cast<JSObject>(Parent_property); \
  JSValue Event_property = Calendar.GetProperty("Event"); \
  TITANIUM_ASSERT(Event_property.IsObject()); \
  Event_ctor = static_cast<JSObject>(Event_property); \
  });\
  JSObject VARNAME = Event_ctor.CallAsConstructor(); \

namespace TitaniumWindows
{
	namespace Calendar
	{
		using namespace Windows::ApplicationModel::Appointments;

		UserCalendar::UserCalendar(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::Calendar::UserCalendar(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("UserCalendar::ctor Initialize");
		}

		void UserCalendar::JSExportInitialize()
		{
			JSExport<UserCalendar>::SetClassVersion(1);
			JSExport<UserCalendar>::SetParent(JSExport<Titanium::Calendar::UserCalendar>::Class());
		}

		void UserCalendar::construct(AppointmentStore^ store, AppointmentCalendar^ calendar)
		{
			appointmentStore__    = store;
			appointmentCalendar__ = calendar;
			updateObjectProperties();
		}

		void UserCalendar::updateObjectProperties()
		{
			TITANIUM_ASSERT(appointmentCalendar__ != nullptr);
			id__ = TitaniumWindows::Utility::ConvertUTF8String(appointmentCalendar__->LocalId);
			name__ = TitaniumWindows::Utility::ConvertUTF8String(appointmentCalendar__->DisplayName);
			hidden__ = appointmentCalendar__->IsHidden;
		}

		std::shared_ptr<Titanium::Calendar::Event> UserCalendar::getEventById(const std::string& id) const TITANIUM_NOEXCEPT
		{
			Appointment^ appointment = nullptr;
			concurrency::event evt;
			concurrency::create_task(appointmentCalendar__->GetAppointmentAsync(TitaniumWindows::Utility::ConvertUTF8String(id)))
				.then([&appointment, &evt](concurrency::task<Appointment^> task) {
				try {
					appointment = task.get();
				} catch (...) {
					// Do nothing
				}
				evt.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			evt.wait();

			if (appointment == nullptr) {
				return nullptr;
			}

			const auto ctx = get_context();
			CREATE_TITANIUM_CALENDAR_EVENT(the_event, ctx);

			const auto event_ptr = the_event.GetPrivate<TitaniumWindows::Calendar::Event>();
			TITANIUM_ASSERT(event_ptr != nullptr);
			event_ptr->construct(appointmentStore__, appointmentCalendar__, appointment);

			return event_ptr;
		}

		std::vector<std::shared_ptr<Titanium::Calendar::Event>> UserCalendar::getEventsBetweenDates(std::chrono::time_point<std::chrono::system_clock> date1, std::chrono::time_point<std::chrono::system_clock> date2) const TITANIUM_NOEXCEPT
		{
			std::vector<std::shared_ptr<Titanium::Calendar::Event>> events;

			const auto startDate = TitaniumWindows::Utility::GetDateTime(date1);
			const auto endDate   = TitaniumWindows::Utility::GetDateTime(date2);

			Windows::Foundation::TimeSpan rangeLength;
			rangeLength.Duration = endDate.UniversalTime - startDate.UniversalTime;

			auto options = ref new FindAppointmentsOptions();
			options->IncludeHidden = true;
			options->CalendarIds->Append(appointmentCalendar__->LocalId);

			Windows::Foundation::Collections::IVectorView<Appointment^>^ appointments = nullptr;
			concurrency::event evt;
			concurrency::create_task(appointmentStore__->FindAppointmentsAsync(startDate, rangeLength, options))
				.then([&appointments, &evt](concurrency::task<Windows::Foundation::Collections::IVectorView<Appointment^>^> task) {
				try {
					appointments = task.get();
				} catch (...) {
					// Do nothing
				}
				evt.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			evt.wait();

			if (appointments == nullptr) {
				return events;
			}

			const auto ctx = get_context();
			for (const auto appointment : appointments) {
				CREATE_TITANIUM_CALENDAR_EVENT(the_event, ctx);

				const auto event_ptr = the_event.GetPrivate<TitaniumWindows::Calendar::Event>();
				TITANIUM_ASSERT(event_ptr != nullptr);
				event_ptr->construct(appointmentStore__, appointmentCalendar__, appointment);

				events.push_back(event_ptr);
			}

			return events;
		}

		std::shared_ptr<Titanium::Calendar::Event> UserCalendar::createEvent(JSObject& parameters) TITANIUM_NOEXCEPT
		{
			auto event_ptr = std::dynamic_pointer_cast<TitaniumWindows::Calendar::Event>(Titanium::Calendar::UserCalendar::createEvent(parameters));
			TITANIUM_ASSERT(event_ptr != nullptr);

			event_ptr->construct(appointmentStore__, appointmentCalendar__);

			return event_ptr;
		}
	}  // namespace Calendar
}  // namespace TitaniumWindows
