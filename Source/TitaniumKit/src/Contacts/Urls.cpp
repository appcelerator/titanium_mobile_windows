/**
 * TitaniumKit Urls
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Urls.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		Urls js_to_Urls(const JSObject& object)
		{	
			std::vector<std::string> homepage;
			if (object.HasProperty("homepage")) {
				const auto js_homepage_object = static_cast<JSObject>(object.GetProperty("homepage"));
				if (js_homepage_object.IsArray()) {
					homepage = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_homepage_object));
				}
			}

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

			Urls urls {
				homepage,
				home,
				work,
				other
			};
			
			return urls;
		};

		JSObject Urls_to_js(const JSContext& js_context, const Urls& urls)
		{
			auto object = js_context.CreateObject();

			std::vector<JSValue> js_homepage;
			for (const auto url : urls.homepage) {
				js_homepage.push_back(js_context.CreateString(url));
			}
			object.SetProperty("homepage", js_context.CreateArray(js_homepage));

			std::vector<JSValue> js_home;
			for (const auto url : urls.home) {
				js_home.push_back(js_context.CreateString(url));
			}
			object.SetProperty("home", js_context.CreateArray(js_home));

			std::vector<JSValue> js_work;
			for (const auto url : urls.work) {
				js_work.push_back(js_context.CreateString(url));
			}
			object.SetProperty("work", js_context.CreateArray(js_work));

			std::vector<JSValue> js_other;
			for (const auto url : urls.other) {
				js_other.push_back(js_context.CreateString(url));
			}
			object.SetProperty("other", js_context.CreateArray(js_other));
			return object;
		};

		Urls create_empty_Urls(const JSContext& js_context)
		{
			Urls urls {
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>()
			};
			return urls;
		}
	} // namespace Contacts
} // namespace Titanium
