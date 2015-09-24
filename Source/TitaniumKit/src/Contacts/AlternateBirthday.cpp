/**
 * TitaniumKit AlternateBirthday
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/AlternateBirthday.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		AlternateBirthday js_to_AlternateBirthday(const JSObject& object)
		{	
			std::string calendarIdentifier = "";
			if (object.HasProperty("calendarIdentifier")) {
				// TODO Verify it's one of "chinese", "hebrew", or "islamic-civil"
				calendarIdentifier = static_cast<std::string>(object.GetProperty("calendarIdentifier"));
			}

			// TODO Do we need to assert that all these values are in the object?
			uint32_t era = 0;
			if (object.HasProperty("era")) {
				era = static_cast<uint32_t>(object.GetProperty("era"));
			}

			int32_t year = 0;
			if (object.HasProperty("year")) {
				year = static_cast<int32_t>(object.GetProperty("year"));
			}

			uint32_t month = 0;
			if (object.HasProperty("month")) {
				month = static_cast<uint32_t>(object.GetProperty("month"));
			}

			uint32_t day = 0;
			if (object.HasProperty("day")) {
				day = static_cast<uint32_t>(object.GetProperty("day"));
			}

			bool isLeapMonth = false;
			if (object.HasProperty("isLeapMonth")) {
				isLeapMonth = static_cast<bool>(object.GetProperty("isLeapMonth"));
			}

			AlternateBirthday abd {
				calendarIdentifier,
				era,
				year,
				month,
				day,
				isLeapMonth
			};
			
			return abd;
		};

		JSObject AlternateBirthday_to_js(const JSContext& js_context, const AlternateBirthday& abd)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("calendarIdentifier", js_context.CreateString(abd.calendarIdentifier));
			object.SetProperty("era", js_context.CreateNumber(abd.era));
			object.SetProperty("year", js_context.CreateNumber(abd.year));
			object.SetProperty("month", js_context.CreateNumber(abd.month));
			object.SetProperty("day", js_context.CreateNumber(abd.day));
			object.SetProperty("isLeapMonth", js_context.CreateBoolean(abd.isLeapMonth));
			return object;
		};

		AlternateBirthday create_empty_AlternateBirthday(const JSContext& js_context)
		{
			AlternateBirthday abd {
				"chinese",
				0,
				0,
				0,
				0,
				false
			};
			return abd;
		}
	} // namespace Contacts
} // namespace Titanium
