/**
 * TitaniumKit ShowContactsParams
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/ShowContactsParams.hpp"
#include "Titanium/Contacts/Person.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		ShowContactsParams js_to_ShowContactsParams(const JSObject& object)
		{
			auto animated = true;
			if (object.HasProperty("animated")) {
				animated = static_cast<bool>(object.GetProperty("animated"));
			}
			
			std::vector<std::string> fields;
			if (object.HasProperty("fields")) {
				const auto js_fields_object = static_cast<JSObject>(object.GetProperty("fields"));
				if (js_fields_object.IsArray()) {
					const auto js_fields = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_fields_object));
					for (const auto f : js_fields) {
						fields.push_back(static_cast<std::string>(f));
					}
				}
			}

			const auto cancel_property = object.GetProperty("cancel");
			const auto oncancel = [cancel_property]() {
				if (cancel_property.IsObject()) {
					auto func = static_cast<JSObject>(cancel_property);
					if (func.IsFunction()) {
						const std::vector<JSValue> args = {};
						func(args, func);
					}
				}
			};

			const auto selectedPerson_property = object.GetProperty("selectedPerson");
			const auto onselectedPerson = [selectedPerson_property](const std::shared_ptr<Person>& e) {
				if (selectedPerson_property.IsObject()) {
					auto func = static_cast<JSObject>(selectedPerson_property);
					if (func.IsFunction()) {
						auto obj = func.get_context().CreateObject();
						obj.SetProperty("person", e->get_object());
						const std::vector<JSValue> args = {
							static_cast<JSValue>(obj)
						};
						func(args, func);
					}
				}
			};

			const auto selectedProperty_property = object.GetProperty("selectedProperty");
			const auto onselectedProperty = [selectedProperty_property](const std::shared_ptr<Person>& e) {
				if (selectedProperty_property.IsObject()) {
					auto func = static_cast<JSObject>(selectedProperty_property);
					if (func.IsFunction()) {
						auto obj = func.get_context().CreateObject();
						obj.SetProperty("person", e->get_object());
						const std::vector<JSValue> args = {
							static_cast<JSValue>(obj)
						};
						func(args, func);
					}
				}
			};

			ShowContactsParamsCallbacks callbacks {
				cancel_property,
				selectedPerson_property,
				selectedProperty_property,
				oncancel,
				onselectedPerson,
				onselectedProperty
			};

			ShowContactsParams config {
				animated,
				fields,
				callbacks
			};
			
			return config;
		};

		JSObject ShowContactsParams_to_js(const JSContext& js_context, const ShowContactsParams& dict)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("animated", js_context.CreateBoolean(dict.animated));
			object.SetProperty("cancel", dict.callbacks.cancel);
			
			std::vector<JSValue> js_fields;
			for (const auto f : dict.fields) {
				js_fields.push_back(js_context.CreateString(f));
			}
			object.SetProperty("fields", js_context.CreateArray(js_fields));

			object.SetProperty("selectedPerson", dict.callbacks.selectedPerson);
			object.SetProperty("selectedProperty", dict.callbacks.selectedProperty);
			return object;
		};

		ShowContactsParams create_empty_ShowContactsParams(const JSContext& js_context) {
			const auto js_null = js_context.CreateNull();
			ShowContactsParamsCallbacks callbacks {
				js_null,
				js_null,
				js_null,
				nullptr,
				nullptr,
				nullptr
			};
			ShowContactsParams config {
				false,
				std::vector<std::string>(),
				callbacks
			};
			return config;
		}
	} // namespace Contacts
} // namespace Titanium
