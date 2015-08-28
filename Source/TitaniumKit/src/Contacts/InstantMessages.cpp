/**
 * TitaniumKit InstantMessages
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/InstantMessages.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		InstantMessage js_to_InstantMessage(const JSObject& object)
		{	
			std::string service = "";
			if (object.HasProperty("service")) {
				service = static_cast<std::string>(object.GetProperty("service"));
			}

			std::string username = "";
			if (object.HasProperty("username")) {
				username = static_cast<std::string>(object.GetProperty("username"));
			}

			InstantMessage im {
				service,
				username
			};
			
			return im;
		};

		JSObject InstantMessage_to_js(const JSContext& js_context, const InstantMessage& im)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("service", js_context.CreateString(im.service));
			object.SetProperty("username", js_context.CreateString(im.username));
			return object;
		};

		InstantMessages js_to_InstantMessages(const JSObject& object)
		{	
			std::vector<InstantMessage> home;
			if (object.HasProperty("home")) {
				const auto js_home_object = static_cast<JSObject>(object.GetProperty("home"));
				if (js_home_object.IsArray()) {
					const auto js_home = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_home_object));
					for (const auto f : js_home) {
						home.push_back(js_to_InstantMessage(static_cast<JSObject>(f)));
					}
				}
			}

			std::vector<InstantMessage> work;
			if (object.HasProperty("work")) {
				const auto js_home_object = static_cast<JSObject>(object.GetProperty("work"));
				if (js_home_object.IsArray()) {
					const auto js_home = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_home_object));
					for (const auto f : js_home) {
						work.push_back(js_to_InstantMessage(static_cast<JSObject>(f)));
					}
				}
			}

			std::vector<InstantMessage> other;
			if (object.HasProperty("other")) {
				const auto js_home_object = static_cast<JSObject>(object.GetProperty("other"));
				if (js_home_object.IsArray()) {
					const auto js_home = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_home_object));
					for (const auto f : js_home) {
						other.push_back(js_to_InstantMessage(static_cast<JSObject>(f)));
					}
				}
			}

			InstantMessages ims {
				home,
				work,
				other
			};
			
			return ims;
		};

		JSObject InstantMessages_to_js(const JSContext& js_context, const InstantMessages& ims)
		{
			auto object = js_context.CreateObject();
			std::vector<JSValue> js_home;
			for (const auto im : ims.home) {
				js_home.push_back(static_cast<JSValue>(InstantMessage_to_js(js_context, im)));
			}
			object.SetProperty("home", js_context.CreateArray(js_home));

			std::vector<JSValue> js_work;
			for (const auto im : ims.work) {
				js_work.push_back(static_cast<JSValue>(InstantMessage_to_js(js_context, im)));
			}
			object.SetProperty("work", js_context.CreateArray(js_work));

			std::vector<JSValue> js_other;
			for (const auto im : ims.other) {
				js_other.push_back(static_cast<JSValue>(InstantMessage_to_js(js_context, im)));
			}
			object.SetProperty("other", js_context.CreateArray(js_other));
			return object;
		};

		InstantMessages create_empty_InstantMessages(const JSContext& js_context)
		{
			InstantMessages ims {
				std::vector<InstantMessage>(),
				std::vector<InstantMessage>(),
				std::vector<InstantMessage>()
			};
			return ims;
		}
	} // namespace Contacts
} // namespace Titanium
