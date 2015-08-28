/**
 * TitaniumKit Phones
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Phones.hpp"

#define ARRAY_OF_STRINGS(PROP) \
std::vector<std::string> PROP; \
if (object.HasProperty(#PROP)) { \
	const auto js_##PROP_object = static_cast<JSObject>(object.GetProperty(#PROP)); \
	if (js_##PROP_object.IsArray()) { \
		PROP = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_##PROP_object)); \
	} \
}

#define SET_STRING_PROPERTY(OBJECT, PROP) \
std::vector<JSValue> js_##PROP; \
for (const auto prop : OBJECT.PROP) { \
	js_##PROP.push_back(js_context.CreateString(prop)); \
} \
object.SetProperty(#PROP, js_context.CreateArray(js_##PROP)); \

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		Phones js_to_Phones(const JSObject& object)
		{	
			ARRAY_OF_STRINGS(home)
			ARRAY_OF_STRINGS(work)
			ARRAY_OF_STRINGS(other)
			ARRAY_OF_STRINGS(mobile)
			ARRAY_OF_STRINGS(pager)
			ARRAY_OF_STRINGS(workFax)
			ARRAY_OF_STRINGS(homeFax)
			ARRAY_OF_STRINGS(main)
			ARRAY_OF_STRINGS(iPhone)

			Phones phones {
				home,
				work,
				other,
				mobile,
				pager,
				workFax,
				homeFax,
				main,
				iPhone
			};
			
			return phones;
		};

		JSObject Phones_to_js(const JSContext& js_context, const Phones& phones)
		{
			auto object = js_context.CreateObject();
			SET_STRING_PROPERTY(phones, home)
			SET_STRING_PROPERTY(phones, work)
			SET_STRING_PROPERTY(phones, other)
			SET_STRING_PROPERTY(phones, mobile)
			SET_STRING_PROPERTY(phones, pager)
			SET_STRING_PROPERTY(phones, workFax)
			SET_STRING_PROPERTY(phones, homeFax)
			SET_STRING_PROPERTY(phones, main)
			SET_STRING_PROPERTY(phones, iPhone)
			return object;
		};

		Phones create_empty_Phones(const JSContext& js_context)
		{
			Phones phones {
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>()
			};
			return phones;
		}
	} // namespace Contacts
} // namespace Titanium
