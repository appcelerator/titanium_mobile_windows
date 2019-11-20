/**
 * TitaniumKit Titanium.Calendar.Event
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_EVENT_HPP_
#define _TITANIUM_CALENDAR_EVENT_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Calendar/Constants.hpp"
#include <chrono>
#include <boost/optional.hpp>

namespace Titanium
{
	namespace Calendar
	{
		using namespace HAL;

		class Alert;
		class Attendee;
		class RecurrenceRule;
		class Reminder;

		/*!
		  @class
		  @discussion This is the Titanium Event Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Calendar.Event
		*/
		class TITANIUMKIT_EXPORT Event : public Module, public JSExport<Event>
		{

		public:

			virtual void addRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT;
			virtual void removeRecurrenceRule(std::shared_ptr<Titanium::Calendar::RecurrenceRule> rule) TITANIUM_NOEXCEPT;
			virtual bool refresh(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT;
			virtual bool save(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT;
			virtual bool remove(const Titanium::Calendar::SPAN span) TITANIUM_NOEXCEPT;
			virtual void createAlert(const std::shared_ptr<Titanium::Calendar::Alert>&) TITANIUM_NOEXCEPT;
			virtual void createReminder(const std::shared_ptr<Titanium::Calendar::Reminder>&) TITANIUM_NOEXCEPT;

			virtual std::string get_calendarID() const TITANIUM_NOEXCEPT;

			Event(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Event()               = default;
			Event(const Event&)            = default;
			Event& operator=(const Event&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Event(Event&&)                 = default;
			Event& operator=(Event&&)      = default;
#endif

			static void JSExportInitialize();

			/*!
			 @property
			 @abstract id
			 @discussion Identifier of this event
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::string, id);
			TITANIUM_PROPERTY_READONLY_DEF(id);

			/*!
			 @property
			 @abstract description
			 @discussion Description of this event
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::string, description);
			TITANIUM_PROPERTY_DEF(description);

			/*!
			 @property
			 @abstract notes
			 @discussion Notes for this event
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::string, notes);
			TITANIUM_PROPERTY_DEF(notes);

			/*!
			 @property
			 @abstract location
			 @discussion Location for this event
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::string, location);
			TITANIUM_PROPERTY_DEF(location);

			/*!
			 @property
			 @abstract title
			 @discussion Title for this event
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);
			TITANIUM_PROPERTY_DEF(title);

			/*!
			 @property
			 @abstract allDay
			 @discussion Indicates whether this event is all day.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(bool, allDay);
			TITANIUM_PROPERTY_DEF(allDay);
				
			/*!
			 @property
			 @abstract hasAlarm
			 @discussion Indicates whether an alarm is scheduled for this event.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(bool, hasAlarm);
			TITANIUM_PROPERTY_READONLY_DEF(hasAlarm);

			/*!
			 @property
			 @abstract isDetached
			 @discussion Boolean value that indicates whether an event is a detached instance of a repeating event.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(bool, isDetached);
			TITANIUM_PROPERTY_READONLY_DEF(isDetached);

			/*!
			 @property
			 @abstract alerts
			 @discussion Alarms associated with the calendar item.
			 */
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::Alert>>, alerts);
			TITANIUM_PROPERTY_READONLY_DEF(alerts);

			/*!
			 @property
			 @abstract attendees
			 @discussion The list of event attendees. This list will be empty if the event has no attendees.
			 */
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::Attendee>>, attendees);
			TITANIUM_PROPERTY_READONLY_DEF(attendees);

			/*!
			 @property
			 @abstract recurrenceRules
			 @discussion The recurrence rules for the calendar item.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::shared_ptr<Titanium::Calendar::RecurrenceRule>>, recurrenceRules);
			TITANIUM_PROPERTY_DEF(recurrenceRules);

			/*!
			 @property
			 @abstract reminders
			 @discussion The recurrence rules for the calendar item.
			 */
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Titanium::Calendar::Reminder>>, reminders);
			TITANIUM_PROPERTY_READONLY_DEF(reminders);

			/*!
			 @property
			 @abstract begin
			 @discussion Start date/time of this event.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::chrono::system_clock::time_point>, begin);
			TITANIUM_PROPERTY_DEF(begin);

			/*!
			 @property
			 @abstract end
			 @discussion End date/time of this event.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::chrono::system_clock::time_point>, end);
			TITANIUM_PROPERTY_DEF(end);

			/*!
			 @property
			 @abstract availability
			 @discussion Availability of this event.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(Titanium::Calendar::AVAILABILITY, availability);
			TITANIUM_PROPERTY_DEF(availability);

			/*!
			 @property
			 @abstract visibility
			 @discussion Visibility of this event.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(Titanium::Calendar::VISIBILITY, visibility);
			TITANIUM_PROPERTY_DEF(visibility);

			/*!
			  @method
			  @abstract addRecurrenceRule
			  @discussion Adds a recurrence rule to the recurrence rule array.
			*/
			TITANIUM_FUNCTION_DEF(addRecurrenceRule);

			/*!
			  @method
			  @abstract createAlert
			  @discussion Creates an alert for this event.
			*/
			TITANIUM_FUNCTION_DEF(createAlert);

			/*!
			  @method
			  @abstract createRecurrenceRule
			  @discussion Creates an recurrence pattern for a recurring event. 
			*/
			TITANIUM_FUNCTION_DEF(createRecurrenceRule);

			/*!
			  @method
			  @abstract createReminder
			  @discussion Creates a reminder for this event.
			*/
			TITANIUM_FUNCTION_DEF(createReminder);

			/*!
			  @method
			  @abstract refresh
			  @discussion Updates the event's data with the current information in the Calendar database.
			*/
			TITANIUM_FUNCTION_DEF(refresh);

			/*!
			  @method
			  @abstract removeRecurrenceRule
			  @discussion Removes a recurrence rule to the recurrence rule array.
			*/
			TITANIUM_FUNCTION_DEF(removeRecurrenceRule);

			/*!
			  @method
			  @abstract save
			  @discussion Saves changes to an event permanently.
			*/
			TITANIUM_FUNCTION_DEF(save);

			/*!
			  @method
			  @abstract save
			  @discussion Saves changes to an event permanently.
			*/
			TITANIUM_FUNCTION_DEF(remove);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			boost::optional<std::chrono::system_clock::time_point> begin__;
			boost::optional<std::chrono::system_clock::time_point> end__;
			std::vector<std::shared_ptr<Titanium::Calendar::RecurrenceRule>> recurrenceRules__;
			Titanium::Calendar::AVAILABILITY availability__;
			Titanium::Calendar::VISIBILITY visibility__;
			std::string description__;
			std::string id__;
			std::string location__;
			std::string notes__;
			std::string title__;
			bool allDay__;
			bool hasAlarm__;
			bool isDetached__;
#pragma warning(pop)
		};

	} // namespace Calendar
} // namespace Titanium
#endif // _TITANIUM_CALENDAR_EVENT_HPP_