/**
 * TitaniumKit Addresses
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Addresses.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		Address js_to_Address(const JSObject& object)
		{	
			std::string countryCode = "";
			if (object.HasProperty("CountryCode")) {
				countryCode = static_cast<std::string>(object.GetProperty("CountryCode"));
			}

			std::string street = "";
			if (object.HasProperty("Street")) {
				street = static_cast<std::string>(object.GetProperty("Street"));
			}

			std::string city = "";
			if (object.HasProperty("City")) {
				city = static_cast<std::string>(object.GetProperty("City"));
			}

			std::string state = "";
			if (object.HasProperty("State")) {
				state = static_cast<std::string>(object.GetProperty("State"));
			}

			std::string country = "";
			if (object.HasProperty("Country")) {
				country = static_cast<std::string>(object.GetProperty("Country"));
			}

			std::string postalCode = "";
			if (object.HasProperty("PostalCode")) {
				postalCode = static_cast<std::string>(object.GetProperty("PostalCode"));
			}

			Address address {
				countryCode,
				street,
				city,
				state,
				country,
				postalCode
			};
			
			return address;
		};

		JSObject Address_to_js(const JSContext& js_context, const Address& address)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("CountryCode", js_context.CreateString(address.countryCode));
			object.SetProperty("Street", js_context.CreateString(address.street));
			object.SetProperty("City", js_context.CreateString(address.city));
			object.SetProperty("State", js_context.CreateString(address.state));
			object.SetProperty("Country", js_context.CreateString(address.country));
			object.SetProperty("PostalCode", js_context.CreateString(address.postalCode));
			return object;
		};

		Addresses js_to_Addresses(const JSObject& object)
		{	
			std::vector<Address> home;
			if (object.HasProperty("home")) {
				const auto js_home_object = static_cast<JSObject>(object.GetProperty("home"));
				if (js_home_object.IsArray()) {
					const auto js_home = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_home_object));
					for (const auto f : js_home) {
						home.push_back(js_to_Address(static_cast<JSObject>(f)));
					}
				}
			}

			std::vector<Address> work;
			if (object.HasProperty("work")) {
				const auto js_home_object = static_cast<JSObject>(object.GetProperty("work"));
				if (js_home_object.IsArray()) {
					const auto js_home = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_home_object));
					for (const auto f : js_home) {
						work.push_back(js_to_Address(static_cast<JSObject>(f)));
					}
				}
			}

			std::vector<Address> other;
			if (object.HasProperty("other")) {
				const auto js_home_object = static_cast<JSObject>(object.GetProperty("other"));
				if (js_home_object.IsArray()) {
					const auto js_home = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_home_object));
					for (const auto f : js_home) {
						other.push_back(js_to_Address(static_cast<JSObject>(f)));
					}
				}
			}

			Addresses addresses {
				home,
				work,
				other
			};
			
			return addresses;
		};

		JSObject Addresses_to_js(const JSContext& js_context, const Addresses& addresses)
		{
			auto object = js_context.CreateObject();
			std::vector<JSValue> js_home;
			for (const auto address : addresses.home) {
				js_home.push_back(static_cast<JSValue>(Address_to_js(js_context, address)));
			}
			object.SetProperty("home", js_context.CreateArray(js_home));

			std::vector<JSValue> js_work;
			for (const auto address : addresses.work) {
				js_work.push_back(static_cast<JSValue>(Address_to_js(js_context, address)));
			}
			object.SetProperty("work", js_context.CreateArray(js_work));

			std::vector<JSValue> js_other;
			for (const auto address : addresses.other) {
				js_other.push_back(static_cast<JSValue>(Address_to_js(js_context, address)));
			}
			object.SetProperty("other", js_context.CreateArray(js_other));
			return object;
		};

		Addresses create_empty_Addresses(const JSContext& js_context)
		{
			Addresses addresses {
				std::vector<Address>(),
				std::vector<Address>(),
				std::vector<Address>()
			};
			return addresses;
		}
	} // namespace Contacts
} // namespace Titanium
