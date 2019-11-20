/**
 * TitaniumKit Titanium.Calendar.RecurrenceRule
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Calendar/RecurrenceRule.hpp"

namespace Titanium
{
	namespace Calendar
	{

		DaysOfTheWeekDictionary js_to_DaysOfTheWeekDictionary(const JSObject& object)
		{	
			DaysOfTheWeekDictionary dict;

			if (object.HasProperty("daysOfWeek")) {
				dict.daysOfWeek = static_cast<std::int8_t>(static_cast<std::uint32_t>(object.GetProperty("daysOfWeek")));
			}

			if (object.HasProperty("week")) {
				dict.week = static_cast<std::int8_t>(static_cast<std::uint32_t>(object.GetProperty("week")));
			}
			
			return dict;
		};

		JSObject DaysOfTheWeekDictionary_to_js(const JSContext& js_context, const DaysOfTheWeekDictionary& dict)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("daysOfWeek", js_context.CreateNumber(dict.daysOfWeek));
			object.SetProperty("week", js_context.CreateNumber(dict.week));
			return object;
		};

		RecurrenceEndDictionary js_to_RecurrenceEndDictionary(const JSObject& object)
		{	
			RecurrenceEndDictionary dict;

			if (object.HasProperty("endDate")) {
				const auto msec = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<double>(object.GetProperty("endDate"))));
				const auto msec_tt = std::chrono::time_point<std::chrono::system_clock>(msec);
				dict.endDate = msec_tt;
			}

			if (object.HasProperty("occurrenceCount")) {
				dict.occurrenceCount = static_cast<std::uint32_t>(object.GetProperty("occurrenceCount"));
			}

			return dict;
		};

		JSObject RecurrenceEndDictionary_to_js(const JSContext& js_context, const RecurrenceEndDictionary& dict)
		{
			auto object = js_context.CreateObject();
			if (dict.endDate) {
				const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>((*dict.endDate).time_since_epoch()).count();
				const std::vector<JSValue> args = { js_context.CreateNumber(static_cast<double>(msec)) };
				object.SetProperty("endDate", js_context.CreateDate(args));
			}	
			object.SetProperty("occurrenceCount", js_context.CreateNumber(dict.occurrenceCount));
			return object;
		};

		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, std::string, calendarID);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, std::vector<std::int8_t>, daysOfTheMonth);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, std::vector<Titanium::Calendar::DaysOfTheWeekDictionary>, daysOfTheWeek);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, std::vector<std::int16_t>, daysOfTheYear);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, std::vector<std::int8_t>, monthsOfTheYear);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, std::vector<std::int8_t>, weeksOfTheYear);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, boost::optional<Titanium::Calendar::RecurrenceEndDictionary>, end);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, Titanium::Calendar::RECURRENCEFREQUENCY, frequency);
		TITANIUM_PROPERTY_READWRITE(RecurrenceRule, std::uint32_t, interval);

		RecurrenceRule::RecurrenceRule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Calendar.RecurrenceRule")
			, interval__(1)
		{
		}

		void RecurrenceRule::JSExportInitialize() 
		{
			JSExport<RecurrenceRule>::SetClassVersion(1);
			JSExport<RecurrenceRule>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_PROPERTY_READONLY(RecurrenceRule, calendarID);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, daysOfTheMonth);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, daysOfTheWeek);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, daysOfTheYear);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, monthsOfTheYear);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, weeksOfTheYear);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, end);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, frequency);
			TITANIUM_ADD_PROPERTY(RecurrenceRule, interval);
		}

		TITANIUM_PROPERTY_GETTER_STRING(RecurrenceRule, calendarID);
		TITANIUM_PROPERTY_GETTER_UINT(RecurrenceRule, interval);
		TITANIUM_PROPERTY_SETTER_UINT(RecurrenceRule, interval);
		TITANIUM_PROPERTY_GETTER_ENUM(RecurrenceRule, frequency);
		TITANIUM_PROPERTY_SETTER_ENUM(RecurrenceRule, frequency, Titanium::Calendar::RECURRENCEFREQUENCY);
		TITANIUM_PROPERTY_GETTER_STRUCT_ARRAY(RecurrenceRule, daysOfTheWeek, DaysOfTheWeekDictionary);
		TITANIUM_PROPERTY_SETTER_STRUCT_ARRAY(RecurrenceRule, daysOfTheWeek, DaysOfTheWeekDictionary);
		TITANIUM_PROPERTY_GETTER_TYPE_ARRAY(RecurrenceRule, daysOfTheMonth,  std::int32_t, Number);
		TITANIUM_PROPERTY_GETTER_TYPE_ARRAY(RecurrenceRule, daysOfTheYear,   std::int32_t, Number);
		TITANIUM_PROPERTY_GETTER_TYPE_ARRAY(RecurrenceRule, monthsOfTheYear, std::int32_t, Number);
		TITANIUM_PROPERTY_GETTER_TYPE_ARRAY(RecurrenceRule, weeksOfTheYear,  std::int32_t, Number);
		TITANIUM_PROPERTY_SETTER_NUMBER_ARRAY(RecurrenceRule, daysOfTheMonth,  std::int8_t);
		TITANIUM_PROPERTY_SETTER_NUMBER_ARRAY(RecurrenceRule, daysOfTheYear,   std::int16_t);
		TITANIUM_PROPERTY_SETTER_NUMBER_ARRAY(RecurrenceRule, monthsOfTheYear, std::int8_t);
		TITANIUM_PROPERTY_SETTER_NUMBER_ARRAY(RecurrenceRule, weeksOfTheYear,  std::int8_t);

		TITANIUM_PROPERTY_GETTER(RecurrenceRule, end)
		{
			const auto ctx = get_context();
			const auto end = get_end();
			if (end) {
				return RecurrenceEndDictionary_to_js(ctx, *end);
			}
			return ctx.CreateNull();
		}

		TITANIUM_PROPERTY_SETTER(RecurrenceRule, end)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_end(js_to_RecurrenceEndDictionary(static_cast<JSObject>(argument)));
			return true;
		}

	} // namespace Calendar
} // namespace Titanium
