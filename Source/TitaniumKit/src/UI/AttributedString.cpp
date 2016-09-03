/**
 * TitaniumKit Titanium.UI.AttributedString
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/AttributedString.hpp"

namespace Titanium
{
	namespace UI
	{

		Attribute js_to_Attribute(const JSObject& object)
		{
			Attribute dict{ object.get_context().CreateNull(), 0, 0 };
			if (object.HasProperty("range")) {
				const auto js_range = object.GetProperty("range");
				if (js_range.IsObject() && static_cast<JSObject>(js_range).IsArray()) {
					const auto range = static_cast<JSArray>(static_cast<JSObject>(js_range));
					TITANIUM_ASSERT(range.GetLength() >= 2);
					dict.from   = static_cast<std::uint32_t>(range.GetProperty(0));
					dict.length = static_cast<std::uint32_t>(range.GetProperty(1));
				}
			}
			if (object.HasProperty("type")) {
				dict.type = Constants::to_ATTRIBUTE_TYPE(static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(object.GetProperty("type")));
			}
			if (object.HasProperty("value")) {
				dict.value = object.GetProperty("value");
			}
			return dict;
		};

		JSObject Attribute_to_js(const JSContext& js_context, const Attribute& dict)
		{
			auto object = js_context.CreateObject();
			const std::vector<JSValue> range = { js_context.CreateNumber(dict.from), js_context.CreateNumber(dict.length) };
			object.SetProperty("range", js_context.CreateArray(range));
			object.SetProperty("type", js_context.CreateNumber(Constants::to_underlying_type(dict.type)));
			object.SetProperty("value", dict.value);
			return object;
		};

		AttributedString::AttributedString(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.AttributedString")
		{
		}

		TITANIUM_PROPERTY_READWRITE(AttributedString, std::string, text)
		TITANIUM_PROPERTY_READWRITE(AttributedString, std::vector<Attribute>, attributes)

		void AttributedString::addAttribute(const Attribute& attribute) TITANIUM_NOEXCEPT
		{
			attributes__.push_back(attribute);
		}

		void AttributedString::JSExportInitialize() 
		{
			JSExport<AttributedString>::SetClassVersion(1);
			JSExport<AttributedString>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(AttributedString, text);
			TITANIUM_ADD_PROPERTY(AttributedString, attributes);

			TITANIUM_ADD_FUNCTION(AttributedString, addAttribute);
			TITANIUM_ADD_FUNCTION(AttributedString, getText);
			TITANIUM_ADD_FUNCTION(AttributedString, setText);
			TITANIUM_ADD_FUNCTION(AttributedString, getAttributes);
			TITANIUM_ADD_FUNCTION(AttributedString, setAttributes);
		}

		TITANIUM_PROPERTY_GETTER_STRING(AttributedString, text)
		TITANIUM_PROPERTY_SETTER_STRING(AttributedString, text)
		TITANIUM_PROPERTY_GETTER_STRUCT_ARRAY(AttributedString, attributes, Attribute)
		TITANIUM_PROPERTY_SETTER_STRUCT_ARRAY(AttributedString, attributes, Attribute)

		TITANIUM_FUNCTION(AttributedString, addAttribute)
		{
			ENSURE_OBJECT_AT_INDEX(attribute, 0);
			addAttribute(js_to_Attribute(attribute));
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(AttributedString, getText, text)
		TITANIUM_FUNCTION_AS_SETTER(AttributedString, setText, text)
		TITANIUM_FUNCTION_AS_GETTER(AttributedString, getAttributes, attributes)
		TITANIUM_FUNCTION_AS_SETTER(AttributedString, setAttributes, attributes)

	} // namespace UI
} // namespace Titanium