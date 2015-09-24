/**
 * TitaniumKit Dates
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Dates.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		Dates js_to_Dates(const JSObject& object)
		{	
			std::vector<std::string> anniversary;
			if (object.HasProperty("anniversary")) {
				const auto js_anniversary_object = static_cast<JSObject>(object.GetProperty("anniversary"));
				if (js_anniversary_object.IsArray()) {
					anniversary = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_anniversary_object));
				}
			}

			std::vector<std::string> other;
			if (object.HasProperty("other")) {
				const auto js_other_object = static_cast<JSObject>(object.GetProperty("other"));
				if (js_other_object.IsArray()) {
					other = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_other_object));
				}
			}

			Dates dates {
				anniversary,
				other
			};
			
			return dates;
		};

		JSObject Dates_to_js(const JSContext& js_context, const Dates& dates)
		{
			auto object = js_context.CreateObject();

			std::vector<JSValue> js_anniversary;
			for (const auto date : dates.anniversary) {
				js_anniversary.push_back(js_context.CreateString(date));
			}
			object.SetProperty("anniversary", js_context.CreateArray(js_anniversary));

			std::vector<JSValue> js_other;
			for (const auto date : dates.other) {
				js_other.push_back(js_context.CreateString(date));
			}
			object.SetProperty("other", js_context.CreateArray(js_other));

			return object;
		};

		Dates create_empty_Dates(const JSContext& js_context)
		{
			Dates dates {
				std::vector<std::string>(),
				std::vector<std::string>()
			};
			return dates;
		}
	} // namespace Contacts
} // namespace Titanium
