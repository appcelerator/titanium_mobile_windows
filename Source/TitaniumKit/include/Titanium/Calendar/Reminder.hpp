/**
 * TitaniumKit Titanium.Calendar.Reminder
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_REMINDER_HPP_
#define _TITANIUM_CALENDAR_REMINDER_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Calendar/Constants.hpp"
#include <chrono>

namespace Titanium
{
	namespace Calendar
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Reminder Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Calendar.Reminder
		*/
		class TITANIUMKIT_EXPORT Reminder : public Module, public JSExport<Reminder>
		{

		public:

			Reminder(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Reminder()               = default;
			Reminder(const Reminder&)            = default;
			Reminder& operator=(const Reminder&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Reminder(Reminder&&)                 = default;
			Reminder& operator=(Reminder&&)      = default;
#endif

			static void JSExportInitialize();

			/*!
			  @property
			  @abstract id
			  @discussion Identifier of this reminder.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(id);
			TITANIUM_PROPERTY_IMPL_DEF(std::string, id);

			/*!
			  @property
			  @abstract method
			  @discussion Method by which this reminder will be delivered.
			*/
			TITANIUM_PROPERTY_DEF(method);
			TITANIUM_PROPERTY_IMPL_DEF(Titanium::Calendar::METHOD, method);

			/*!
			  @property
			  @abstract minutes
			  @discussion Reminder notice period in minutes, that determines how long prior to the event this reminder should trigger.
			*/
			TITANIUM_PROPERTY_DEF(minutes);
			TITANIUM_PROPERTY_IMPL_DEF(std::chrono::minutes, minutes);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string id__;
			Titanium::Calendar::METHOD method__;
			std::chrono::minutes minutes__;
#pragma warning(pop)
		};

	} // namespace Calendar
} // namespace Titanium
#endif // _TITANIUM_CALENDAR_REMINDER_HPP_