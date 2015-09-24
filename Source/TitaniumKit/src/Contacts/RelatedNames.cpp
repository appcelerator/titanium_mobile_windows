/**
 * TitaniumKit RelatedNames
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/RelatedNames.hpp"

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

		RelatedNames js_to_RelatedNames(const JSObject& object)
		{	
			ARRAY_OF_STRINGS(mother)
			ARRAY_OF_STRINGS(father)
			ARRAY_OF_STRINGS(parent)
			ARRAY_OF_STRINGS(brother)
			ARRAY_OF_STRINGS(sister)
			ARRAY_OF_STRINGS(child)
			std::vector<std::string> friend_;
			if (object.HasProperty("friend")) {
				const auto js_friend_object = static_cast<JSObject>(object.GetProperty("friend"));
				if (js_friend_object.IsArray()) {
					friend_ = static_cast<std::vector<std::string>>(static_cast<JSArray>(js_friend_object));
				}
			}
			ARRAY_OF_STRINGS(spouse)
			ARRAY_OF_STRINGS(partner)
			ARRAY_OF_STRINGS(assistant)
			ARRAY_OF_STRINGS(manager)
			ARRAY_OF_STRINGS(other)

			RelatedNames relatedNames {
				mother,
				father,
				parent,
				brother,
				sister,
				child,
				friend_,
				spouse,
				partner,
				assistant,
				manager,
				other
			};
			
			return relatedNames;
		};

		JSObject RelatedNames_to_js(const JSContext& js_context, const RelatedNames& relatedNames)
		{
			auto object = js_context.CreateObject();
			SET_STRING_PROPERTY(relatedNames, mother)
			SET_STRING_PROPERTY(relatedNames, father)
			SET_STRING_PROPERTY(relatedNames, parent)
			SET_STRING_PROPERTY(relatedNames, brother)
			SET_STRING_PROPERTY(relatedNames, sister)
			SET_STRING_PROPERTY(relatedNames, child)
			std::vector<JSValue> js_friend;
			for (const auto prop : relatedNames.friend_) {
				js_friend.push_back(js_context.CreateString(prop));
			}
			object.SetProperty("friend", js_context.CreateArray(js_friend));
			SET_STRING_PROPERTY(relatedNames, spouse)
			SET_STRING_PROPERTY(relatedNames, partner)
			SET_STRING_PROPERTY(relatedNames, assistant)
			SET_STRING_PROPERTY(relatedNames, manager)
			SET_STRING_PROPERTY(relatedNames, other)
			return object;
		};

		RelatedNames create_empty_RelatedNames(const JSContext& js_context)
		{
			RelatedNames names {
				std::vector<std::string>(),
				std::vector<std::string>(),
				std::vector<std::string>(),
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
			return names;
		}
	} // namespace Contacts
} // namespace Titanium
