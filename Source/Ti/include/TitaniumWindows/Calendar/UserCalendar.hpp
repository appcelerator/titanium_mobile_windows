/**
 * Titanium.Calendar.Calendar for Windows
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_CALENDAR_CALENDAR_HPP_
#define _TITANIUMWINDOWS_CALENDAR_CALENDAR_HPP_

#include "Titanium/Calendar/UserCalendar.hpp"
#include "TitaniumWindows_Ti_EXPORT.h"

namespace TitaniumWindows
{
	namespace Calendar
	{
		using namespace HAL;

		/*!
		  @class UserCalendar
		  @ingroup Titanium.Calendar.Calendar

		  @discussion This is the Titanium.Calendar.Calendar implementation for Windows.
		*/
		class TITANIUMWINDOWS_TI_EXPORT UserCalendar final : public Titanium::Calendar::UserCalendar, public JSExport<UserCalendar>
		{

		public:

			UserCalendar(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~UserCalendar()                      = default;
			UserCalendar(const UserCalendar&)            = default;
			UserCalendar& operator=(const UserCalendar&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			UserCalendar(UserCalendar&&)                 = default;
			UserCalendar& operator=(UserCalendar&&)      = default;
#endif

			static void JSExportInitialize();

			virtual std::shared_ptr<Titanium::Calendar::Event> getEventById(const std::string& id) const TITANIUM_NOEXCEPT;
			virtual std::vector<std::shared_ptr<Titanium::Calendar::Event>> getEventsBetweenDates(std::chrono::time_point<std::chrono::system_clock> date1, std::chrono::time_point<std::chrono::system_clock> date2) const TITANIUM_NOEXCEPT;
			virtual std::shared_ptr<Titanium::Calendar::Event> createEvent(JSObject& parameters) TITANIUM_NOEXCEPT override;

			void construct(Windows::ApplicationModel::Appointments::AppointmentStore^, Windows::ApplicationModel::Appointments::AppointmentCalendar^);
			void updateObjectProperties();

		private:
			Windows::ApplicationModel::Appointments::AppointmentCalendar^ appointmentCalendar__;
			Windows::ApplicationModel::Appointments::AppointmentStore^    appointmentStore__;
		};
	}  // namespace Calendar
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_CALENDAR_CALENDAR_HPP_
