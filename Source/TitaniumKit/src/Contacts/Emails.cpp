/**
 * TitaniumKit Emails
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Emails.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		Emails js_to_Emails(const JSObject& object)
		{	
			std::vector<std::string> home;
			if (object.HasProperty("home")) {
				const auto js_home_object = static_cast<JSObject>(object.GetProperty("home"));
				if (js_home_object.IsArray()) {
					home = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_home_object));
				}
			}
			std::vector<std::string> work;
			if (object.HasProperty("work")) {
				const auto js_work_object = static_cast<JSObject>(object.GetProperty("work"));
				if (js_work_object.IsArray()) {
					work = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_work_object));
				}
			}
			std::vector<std::string> other;
			if (object.HasProperty("other")) {
				const auto js_other_object = static_cast<JSObject>(object.GetProperty("other"));
				if (js_other_object.IsArray()) {
					other = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_other_object));
				}
			}

			Emails emails {
				home,
				work,
				other
			};
			
			return emails;
		};

		JSObject Emails_to_js(const JSContext& js_context, const Emails& emails)
		{
			auto object = js_context.CreateObject();

			std::vector<JSValue> js_home;
			for (const auto email : emails.home) {
				js_home.push_back(js_context.CreateString(email));
			}
			object.SetProperty("home", js_context.CreateArray(js_home));

			std::vector<JSValue> js_work;
			for (const auto email : emails.work) {
				js_work.push_back(js_context.CreateString(email));
			}
			object.SetProperty("work", js_context.CreateArray(js_work));

			std::vector<JSValue> js_other;
			for (const auto email : emails.other) {
				js_other.push_back(js_context.CreateString(email));
			}
			object.SetProperty("other", js_context.CreateArray(js_other));
			return object;
		};

		Emails create_empty_Emails(const JSContext& js_context)
		{
			Emails emails {
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>()
			};
			return emails;
		}
	} // namespace Contacts
} // namespace Titanium
