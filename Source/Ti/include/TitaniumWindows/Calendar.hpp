/**
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_CALENDAR_HPP_
#define _TITANIUMWINDOWS_CALENDAR_HPP_

#include "Titanium/Calendar.hpp"
#include "TitaniumWindows_Ti_EXPORT.h"
#include <boost/optional.hpp>

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class Calendar
	  @ingroup Titanium.Calendar

	  @discussion This is Titanium.Calendar module implementation for Windows.
	*/
	class TITANIUMWINDOWS_TI_EXPORT CalendarModule final : public Titanium::CalendarModule, public JSExport<CalendarModule>
	{
	public:

		virtual std::shared_ptr<Titanium::Calendar::UserCalendar> getCalendarById(const std::string& id) TITANIUM_NOEXCEPT override;
		virtual bool hasCalendarPermissions() TITANIUM_NOEXCEPT override;
		virtual void requestCalendarPermissions(JSObject& callback) TITANIUM_NOEXCEPT override;
		virtual std::shared_ptr<Titanium::Calendar::UserCalendar> getDefaultCalendar() const TITANIUM_NOEXCEPT override;

		CalendarModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~CalendarModule()       = default;
		CalendarModule(const CalendarModule&) = default;
		CalendarModule& operator=(const CalendarModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Calendar(CalendarModule&&) = default;
		Calendar& operator=(CalendarModule&&) = default;
#endif

		static void JSExportInitialize();

		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::Alert>>, allAlerts) TITANIUM_NOEXCEPT override;
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>>, allCalendars) TITANIUM_NOEXCEPT override;
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>>, allEditableCalendars) TITANIUM_NOEXCEPT override;
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>>, selectableCalendars) TITANIUM_NOEXCEPT override;

	protected:

#pragma warning(push)
#pragma warning(disable : 4251)
		Windows::ApplicationModel::Appointments::AppointmentStore^ appointmentStore__;
		boost::optional<bool> hasCalendarPermissions__; // permission cache
#pragma warning(pop)
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_CALENDAR_HPP_
