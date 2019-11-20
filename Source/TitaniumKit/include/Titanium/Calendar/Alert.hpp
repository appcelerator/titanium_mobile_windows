/**
 * TitaniumKit Titanium.Calendar.Alert
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_ALERT_HPP_
#define _TITANIUM_CALENDAR_ALERT_HPP_

#include "Titanium/Module.hpp"
#include <chrono>
#include <boost/optional.hpp>

namespace Titanium
{
	namespace Calendar
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Alert Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Calendar.Alert
		*/
		class TITANIUMKIT_EXPORT Alert : public Module, public JSExport<Alert>
		{

		public:

			Alert(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Alert()               = default;
			Alert(const Alert&)            = default;
			Alert& operator=(const Alert&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Alert(Alert&&)                 = default;
			Alert& operator=(Alert&&)      = default;
#endif

			static void JSExportInitialize();

			/*!
			  @property
			  @abstract absoluteDate
			  @discussion The absolute date for the alarm.
			*/
			TITANIUM_PROPERTY_DEF(absoluteDate);
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::chrono::system_clock::time_point>, absoluteDate);

			/*!
			  @property
			  @abstract alarmTime
			  @discussion Date/time at which this alert alarm is set to trigger.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(alarmTime);
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::chrono::system_clock::time_point>, alarmTime);

			/*!
			  @property
			  @abstract absoluteDate
			  @discussion The absolute date for the alarm.
			*/
			TITANIUM_PROPERTY_DEF(minutes);
			TITANIUM_PROPERTY_IMPL_DEF(std::chrono::minutes, minutes);

			/*!
			  @property
			  @abstract id
			  @discussion Identifier of the event for which this alert is set.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(id);
			TITANIUM_PROPERTY_IMPL_DEF(std::string, id);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			boost::optional<std::chrono::system_clock::time_point> absoluteDate__;	
			boost::optional<std::chrono::system_clock::time_point> alarmTime__;	
			std::chrono::minutes minutes__;
			std::string id__;
#pragma warning(pop)
		};

	} // namespace Calendar
} // namespace Titanium
#endif // _TITANIUM_CALENDAR_ALERT_HPP_