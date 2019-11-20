/**
 * TitaniumKit Titanium.Calendar
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_HPP_
#define _TITANIUM_CALENDAR_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Calendar/Constants.hpp"

namespace Titanium
{
	using namespace HAL;

	namespace Calendar
	{
		class UserCalendar;
		class Alert;
	}

	/*!
	  @class
	  @discussion This is the Titanium Calendar Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Calendar
	*/
	class TITANIUMKIT_EXPORT CalendarModule : public Module, public JSExport<CalendarModule>
	{

	public:

		virtual std::shared_ptr<Titanium::Calendar::UserCalendar> getCalendarById(const std::string& id) TITANIUM_NOEXCEPT;
		virtual bool hasCalendarPermissions() TITANIUM_NOEXCEPT;
		virtual void requestCalendarPermissions(JSObject& callback) TITANIUM_NOEXCEPT;
		virtual std::shared_ptr<Titanium::Calendar::UserCalendar> getDefaultCalendar() const TITANIUM_NOEXCEPT;

		CalendarModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
		virtual ~CalendarModule()                        = default;
		CalendarModule(const CalendarModule&)            = default;
		CalendarModule& operator=(const CalendarModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		CalendarModule(CalendarModule&&)                 = default;
		CalendarModule& operator=(CalendarModule&&)      = default;
#endif

		static void JSExportInitialize();

		/*!
		  @property
		  @abstract AUTHORIZATION_AUTHORIZED
		  @discussion A calendarAuthorization value indicating that the application is authorized to use events in the Calendar.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_AUTHORIZED);

		/*!
		  @property
		  @abstract AUTHORIZATION_DENIED
		  @discussion A calendarAuthorization value indicating that the application is not authorized to use events in the Calendar.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_DENIED);

		/*!
		  @property
		  @abstract AUTHORIZATION_RESTRICTED
		  @discussion A calendarAuthorization value indicating that the application is not authorized to use events in the Calendar.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_RESTRICTED);

		/*!
		  @property
		  @abstract AUTHORIZATION_UNKNOWN
		  @discussion calendarAuthorization value indicating that the authorization state is unknown.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_UNKNOWN);

		/*!
		  @property
		  @abstract ATTENDEE_STATUS_UNKNOWN
		  @discussion Attendee status is unknown
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_UNKNOWN);

		/*!
		  @property
		  @abstract ATTENDEE_STATUS_PENDING
		  @discussion Attendee status is pending
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_PENDING);

		/*!
		  @property
		  @abstract ATTENDEE_STATUS_ACCEPTED
		  @discussion Attendee status is accepted
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_ACCEPTED);

		/*!
		  @property
		  @abstract ATTENDEE_STATUS_DECLINED
		  @discussion Attendee status is declined
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_DECLINED);

		/*!
		  @property
		  @abstract ATTENDEE_STATUS_TENTATIVE
		  @discussion Attendee status is tentative
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_TENTATIVE);

		/*!
		  @property
		  @abstract ATTENDEE_STATUS_INVITED
		  @discussion Attendee status is invited
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_INVITED);


		/*!
		  @property
		  @abstract ATTENDEE_STATUS_NONE
		  @discussion Attendee status is none
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_NONE);

		/*!
		  @property
		  @abstract ATTENDEE_STATUS_IN_PROCESS
		  @discussion Attendee status is in process
		*/
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_STATUS_IN_PROCESS);

		/*!
		 @property
		 @abstract ATTENDEE_ROLE_UNKNOWN
		 @discussion Attendee role is unknown
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_ROLE_UNKNOWN);
		
		/*!
		 @property
		 @abstract ATTENDEE_ROLE_OPTIONAL
		 @discussion Attendee role is optional
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_ROLE_OPTIONAL);

		/*!
		 @property
		 @abstract ATTENDEE_ROLE_REQUIRED
		 @discussion Attendee role is required
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_ROLE_REQUIRED);

		/*!
		 @property
		 @abstract ATTENDEE_ROLE_CHAIR
		 @discussion Attendee role is chair
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_ROLE_CHAIR);

		/*!
		 @property
		 @abstract ATTENDEE_ROLE_NON_PARTICIPANT
		 @discussion Attendee role is not paticipant
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_ROLE_NON_PARTICIPANT);

		/*!
		 @property
		 @abstract ATTENDEE_TYPE_UNKNOWN
		 @discussion Attendee type is unknown
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_TYPE_UNKNOWN);

		/*!
		 @property
		 @abstract ATTENDEE_TYPE_PERSON
		 @discussion Attendee type is person
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_TYPE_PERSON);

		/*!
		 @property
		 @abstract ATTENDEE_TYPE_ROOM
		 @discussion Attendee type is room
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_TYPE_ROOM);

		/*!
		 @property
		 @abstract ATTENDEE_TYPE_RESOURCE
		 @discussion Attendee type is resource
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_TYPE_RESOURCE);

		/*!
		 @property
		 @abstract ATTENDEE_TYPE_NONE
		 @discussion Attendee type is none
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_TYPE_NONE);

		/*!
		 @property
		 @abstract ATTENDEE_TYPE_REQUIRED
		 @discussion Attendee type is required
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_TYPE_REQUIRED);

		/*!
		 @property
		 @abstract ATTENDEE_TYPE_GROUP
		 @discussion Attendee type is group
		 */
		TITANIUM_PROPERTY_READONLY_DEF(ATTENDEE_TYPE_GROUP);

		/*!
		 @property
		 @abstract AVAILABILITY_NOTSUPPORTED
		 @discussion Attendee availability is not supported
		 */
		TITANIUM_PROPERTY_READONLY_DEF(AVAILABILITY_NOTSUPPORTED);

		/*!
		 @property
		 @abstract AVAILABILITY_BUSY
		 @discussion Attendee availability is busy
		 */
		TITANIUM_PROPERTY_READONLY_DEF(AVAILABILITY_BUSY);

		/*!
		 @property
		 @abstract AVAILABILITY_FREE
		 @discussion Attendee availability is free
		 */
		TITANIUM_PROPERTY_READONLY_DEF(AVAILABILITY_FREE);

		/*!
		 @property
		 @abstract AVAILABILITY_TENTATIVE
		 @discussion Attendee availability is tentative
		 */
		TITANIUM_PROPERTY_READONLY_DEF(AVAILABILITY_TENTATIVE);

		/*!
		 @property
		 @abstract AVAILABILITY_UNAVAILABLE
		 @discussion Attendee availability is unavailable
		 */
		TITANIUM_PROPERTY_READONLY_DEF(AVAILABILITY_UNAVAILABLE);

		/*!
		 @property
		 @abstract METHOD_DEFAULT
		 @discussion Reminder default delivery method.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(METHOD_DEFAULT);

		/*!
		 @property
		 @abstract METHOD_ALERT
		 @discussion Reminder alert delivery method.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(METHOD_ALERT);

		/*!
		 @property
		 @abstract METHOD_EMAIL
		 @discussion Reminder email delivery method.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(METHOD_EMAIL);

		/*!
		 @property
		 @abstract METHOD_SMS
		 @discussion Reminder SMS delivery method.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(METHOD_SMS);

		/*!
		 @property
		 @abstract RECURRENCEFREQUENCY_DAILY
		 @discussion Indicates a daily recurrence rule for a events reccurance frequency.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(RECURRENCEFREQUENCY_DAILY);

		/*!
		 @property
		 @abstract RECURRENCEFREQUENCY_WEEKLY
		 @discussion Indicates a weekly recurrence rule for a events reccurance frequency.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(RECURRENCEFREQUENCY_WEEKLY);

		/*!
		 @property
		 @abstract RECURRENCEFREQUENCY_MONTHLY
		 @discussion Indicates a monthly recurrence rule for a events reccurance frequency.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(RECURRENCEFREQUENCY_MONTHLY);

		/*!
		 @property
		 @abstract RECURRENCEFREQUENCY_YEARLY
		 @discussion Indicates a yearly recurrence rule for a events reccurance frequency.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(RECURRENCEFREQUENCY_YEARLY);

		/*!
		 @property
		 @abstract SPAN_FUTUREEVENTS
		 @discussion A save/remove event value, indicating modifications to this event instance should also affect future instances of this event.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(SPAN_FUTUREEVENTS);

		/*!
		 @property
		 @abstract SPAN_THISEVENT
		 @discussion A save/remove event value, indicating modifications to this event instance should affect only this instance.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(SPAN_THISEVENT);

		/*!
		 @property
		 @abstract STATUS_NONE
		 @discussion Event has no status.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(STATUS_NONE);

		/*!
		 @property
		 @abstract STATUS_CANCELED
		 @discussion Event canceled status.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(STATUS_CANCELED);

		/*!
		 @property
		 @abstract STATUS_CANCELLED
		 @discussion Event cancelled status.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(STATUS_CANCELLED);

		/*!
		 @property
		 @abstract STATUS_CONFIRMED
		 @discussion Event confirmed status.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(STATUS_CONFIRMED);

		/*!
		 @property
		 @abstract STATUS_TENTATIVE
		 @discussion Event tentative status.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(STATUS_TENTATIVE);

		/*!
		 @property
		 @abstract VISIBILITY_CONFIDENTIAL
		 @discussion Confidential visibility.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(VISIBILITY_CONFIDENTIAL);

		/*!
		 @property
		 @abstract VISIBILITY_DEFAULT
		 @discussion Default visibility.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(VISIBILITY_DEFAULT);

		/*!
		 @property
		 @abstract VISIBILITY_PRIVATE
		 @discussion Private visibility.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(VISIBILITY_PRIVATE);

		/*!
		 @property
		 @abstract VISIBILITY_PUBLIC
		 @discussion Public visibility.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(VISIBILITY_PUBLIC);

		/*!
		 @property
		 @abstract allAlerts
		 @discussion All alerts in selected calendars.
		 */
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::Alert>>, allAlerts);
		TITANIUM_PROPERTY_READONLY_DEF(allAlerts);

		/*!
		 @property
		 @abstract allCalendars
		 @discussion All calendars known to the native calendar app.
		 */
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>>, allCalendars);
		TITANIUM_PROPERTY_READONLY_DEF(allCalendars);

		/*!
		 @property
		 @abstract allEditableCalendars
		 @discussion All calendars known to the native calendar app that can add, edit, and delete items in the calendar.
		 */
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>>, allEditableCalendars);
		TITANIUM_PROPERTY_READONLY_DEF(allEditableCalendars);

		/*!
		 @property
		 @abstract calendarAuthorization
		 @discussion Returns an authorization constant indicating if the application has access to the events in the EventKit.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(calendarAuthorization);

		/*!
		 @property
		 @abstract defaultCalendar
		 @discussion Calendar that events are added to by default, as specified by user settings.
		 */
		TITANIUM_PROPERTY_READONLY_DEF(defaultCalendar);

		/*!
		 @property
		 @abstract selectableCalendars
		 @discussion All calendars selected within the native calendar app, which may be a subset of allCalendars.
		 */
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::UserCalendar>>, selectableCalendars);
		TITANIUM_PROPERTY_READONLY_DEF(selectableCalendars);

		/*!
		  @method
		  @abstract getCalendarById
		  @discussion Gets the calendar with the specified identifier.
		*/
		TITANIUM_FUNCTION_DEF(getCalendarById);

		/*!
		  @method
		  @abstract hasCalendarPermissions
		  @discussion Returns true if the app has calendar access.
		*/
		TITANIUM_FUNCTION_DEF(hasCalendarPermissions);

		/*!
		  @method
		  @abstract requestCalendarPermissions
		  @discussion Requests for calendar access.
		*/
		TITANIUM_FUNCTION_DEF(requestCalendarPermissions);

		TITANIUM_PROPERTY_READONLY_DEF(Alert);
		TITANIUM_PROPERTY_READONLY_DEF(Attendee);
		TITANIUM_PROPERTY_READONLY_DEF(Event);
		TITANIUM_PROPERTY_READONLY_DEF(RecurrenceRule);
		TITANIUM_PROPERTY_READONLY_DEF(Reminder);
		TITANIUM_PROPERTY_READONLY_DEF(Calendar);

		CalendarModule& AlertClass(const JSClass&) TITANIUM_NOEXCEPT;
		CalendarModule& AttendeeClass(const JSClass&) TITANIUM_NOEXCEPT;
		CalendarModule& EventClass(const JSClass&) TITANIUM_NOEXCEPT;
		CalendarModule& RecurrenceRuleClass(const JSClass&) TITANIUM_NOEXCEPT;
		CalendarModule& ReminderClass(const JSClass&) TITANIUM_NOEXCEPT;
		CalendarModule& CalendarClass(const JSClass&) TITANIUM_NOEXCEPT;

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		JSClass alert__;
		JSClass attendee__;
		JSClass event__;
		JSClass recurrenceRule__;
		JSClass reminder__;
		JSClass calendar__;

		Titanium::Calendar::AUTHORIZATION calendarAuthorization__;
#pragma warning(pop)
	};

} // namespace Titanium
#endif // _TITANIUM_CALENDAR_HPP_