/**
 * TitaniumKit Titanium.Calendar.RecurrenceRule
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_RECURRENCERULE_HPP_
#define _TITANIUM_CALENDAR_RECURRENCERULE_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Calendar/Constants.hpp"
#include <chrono>
#include <boost/optional.hpp>

namespace Titanium
{
	namespace Calendar
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion Dictionary containing daysOfWeek and week.
		  See https://docs.appcelerator.com/platform/latest/#!/api/daysOfTheWeekDictionary
		*/
		struct DaysOfTheWeekDictionary  {
			std::int8_t daysOfWeek{ 0 };
			std::int8_t week{ 0 };
		};

		TITANIUMKIT_EXPORT DaysOfTheWeekDictionary js_to_DaysOfTheWeekDictionary(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject DaysOfTheWeekDictionary_to_js(const JSContext& js_context, const DaysOfTheWeekDictionary& dict);

		/*!
		  @struct
		  @discussion Dictionary containing either endDate or occurrenceCount property.
		  See https://docs.appcelerator.com/platform/latest/#!/api/recurrenceEndDictionary
		*/
		struct RecurrenceEndDictionary {
			boost::optional<std::chrono::system_clock::time_point> endDate;
			std::uint32_t occurrenceCount{ 0 };
		};

		TITANIUMKIT_EXPORT RecurrenceEndDictionary js_to_RecurrenceEndDictionary(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject RecurrenceEndDictionary_to_js(const JSContext& js_context, const RecurrenceEndDictionary& dict);

		/*!
		  @class
		  @discussion This is the Titanium RecurrenceRule Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Calendar.RecurrenceRule
		*/
		class TITANIUMKIT_EXPORT RecurrenceRule : public Module, public JSExport<RecurrenceRule>
		{

		public:

			RecurrenceRule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~RecurrenceRule()               = default;
			RecurrenceRule(const RecurrenceRule&)            = default;
			RecurrenceRule& operator=(const RecurrenceRule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			RecurrenceRule(RecurrenceRule&&)                 = default;
			RecurrenceRule& operator=(RecurrenceRule&&)      = default;
#endif

			static void JSExportInitialize();

			/*!
			  @property
			  @abstract calendarID
			  @discussion Identifier for the recurrence rule's calendar.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(calendarID);
			TITANIUM_PROPERTY_IMPL_DEF(std::string, calendarID);

			/*!
			  @property
			  @abstract daysOfTheMonth
			  @discussion The days of the month that the event occurs, as an array of number objects. 
			*/
			TITANIUM_PROPERTY_DEF(daysOfTheMonth);
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::int8_t>, daysOfTheMonth);

			/*!
			  @property
			  @abstract daysOfTheWeek
			  @discussion The days of the week that the event occurs, as an array of objects daysOfWeek and Week.
			*/
			TITANIUM_PROPERTY_DEF(daysOfTheWeek);
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<Titanium::Calendar::DaysOfTheWeekDictionary>, daysOfTheWeek);

			/*!
			  @property
			  @abstract daysOfTheYear
			  @discussion The weeks of the year that the event occurs, as an array of number objects. 
			*/
			TITANIUM_PROPERTY_DEF(daysOfTheYear);
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::int16_t>, daysOfTheYear);

			/*!
			  @property
			  @abstract monthsOfTheYear
			  @discussion The months of the year that the event occurs, as an array of Number objects.
			*/
			TITANIUM_PROPERTY_DEF(monthsOfTheYear);
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::int8_t>, monthsOfTheYear);

			/*!
			  @property
			  @abstract weeksOfTheYear
			  @discussion The weeks of the year that the event occurs, as an array of number objects. 
			*/
			TITANIUM_PROPERTY_DEF(weeksOfTheYear);
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::int8_t>, weeksOfTheYear);

			/*!
			  @property
			  @abstract end
			  @discussion End of a recurrence rule.
			*/
			TITANIUM_PROPERTY_DEF(end);
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<Titanium::Calendar::RecurrenceEndDictionary>, end);

			/*!
			  @property
			  @abstract freqency
			  @discussion Frequency of the recurrence rule.
			*/
			TITANIUM_PROPERTY_DEF(frequency);
			TITANIUM_PROPERTY_IMPL_DEF(Titanium::Calendar::RECURRENCEFREQUENCY, frequency);

			/*!
			  @property
			  @abstract interval
			  @discussion The interval between instances of this recurrence. 
			*/
			TITANIUM_PROPERTY_DEF(interval);
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, interval);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string calendarID__;
			std::vector<std::int8_t> daysOfTheMonth__;
			std::vector<Titanium::Calendar::DaysOfTheWeekDictionary> daysOfTheWeek__;
			std::vector<std::int16_t> daysOfTheYear__;
			std::vector<std::int8_t> monthsOfTheYear__;
			std::vector<std::int8_t> weeksOfTheYear__;

			boost::optional<Titanium::Calendar::RecurrenceEndDictionary> end__;
			Titanium::Calendar::RECURRENCEFREQUENCY frequency__;
			std::uint32_t interval__;
#pragma warning(pop)
		};

	} // namespace Calendar
} // namespace Titanium
#endif // _TITANIUM_CALENDAR_RECURRENCERULE_HPP_
