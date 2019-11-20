/**
 * TitaniumKit Titanium.Calendar.Calendar
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_CALENDAR_HPP_
#define _TITANIUM_CALENDAR_CALENDAR_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace Calendar
	{
		using namespace HAL;

		class Event;

		/*!
		  @class
		  @discussion This is the Titanium Calendar Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Calendar.Calendar
		*/
		class TITANIUMKIT_EXPORT UserCalendar : public Module, public JSExport<UserCalendar>
		{

		public:

			virtual std::shared_ptr<Titanium::Calendar::Event> getEventById(const std::string& id) const TITANIUM_NOEXCEPT;
			virtual std::vector<std::shared_ptr<Titanium::Calendar::Event>> getEventsBetweenDates(std::chrono::time_point<std::chrono::system_clock> date1, std::chrono::time_point<std::chrono::system_clock> date2) const TITANIUM_NOEXCEPT;
			virtual std::shared_ptr<Titanium::Calendar::Event> createEvent(JSObject& parameters) TITANIUM_NOEXCEPT;

			UserCalendar(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~UserCalendar()               = default;
			UserCalendar(const UserCalendar&)            = default;
			UserCalendar& operator=(const UserCalendar&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			UserCalendar(UserCalendar&&)                 = default;
			UserCalendar& operator=(UserCalendar&&)      = default;
#endif

			static void JSExportInitialize();

			/*!
			 @property
			 @abstract hidden
			 @discussion Indicates whether this calendar can be edited or deleted.
			 */
	 		TITANIUM_PROPERTY_IMPL_DEF(bool, hidden);
			TITANIUM_PROPERTY_READONLY_DEF(hidden);

			/*!
			 @property
			 @abstract id
			 @discussion Identifier of this calendar.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::string, id);
			TITANIUM_PROPERTY_READONLY_DEF(id);

			/*!
			 @property
			 @abstract name
			 @discussion Display name of this calendar.
			 */
			TITANIUM_PROPERTY_IMPL_DEF(std::string, name);
			TITANIUM_PROPERTY_READONLY_DEF(name);

			/*!
			  @method
			  @abstract createEvent
			  @discussion Creates an event in this calendar.
			*/
			TITANIUM_FUNCTION_DEF(createEvent);

			/*!
			  @method
			  @abstract getEventById
			  @discussion Gets the event with the specified identifier.
			*/
			TITANIUM_FUNCTION_DEF(getEventById);

			/*!
			  @method
			  @abstract getEventsBetweenDates
			  @discussion Gets events that occur between two dates.
			*/
			TITANIUM_FUNCTION_DEF(getEventsBetweenDates);
		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			bool hidden__;
			std::string id__;
			std::string name__;
#pragma warning(pop)
		};

	} // namespace Calendar
} // namespace Titanium
#endif // _TITANIUM_CALENDAR_CALENDAR_HPP_