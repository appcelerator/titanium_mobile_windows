/**
* TitaniumKit Titanium.App.Properties
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "Titanium/App/Properties.hpp"

namespace Titanium
{
	namespace App
	{
		JSFunction Properties::createStringifyFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT
		{
			return get_context().CreateFunction("return JSON.stringify(value);", { "value" });
		}

		Properties::Properties(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context),
			  stringify_function__(createStringifyFunction(js_context))
		{
			TITANIUM_LOG_DEBUG("Properties:: ctor ", this);
		}

		void Properties::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			HAL_LOG_DEBUG("Properties:: postCallAsConstructor ", this);
		}

		bool Properties::getBool(const std::string& property, bool defaultValue) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getBool: Unimplemented");
			return false;
		}

		double Properties::getDouble(const std::string& property, double defaultValue) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getDouble: Unimplemented");
			return 0;
		}

		double Properties::getInt(const std::string& property, double defaultValue) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getInt: Unimplemented");
			return 0;
		}

		std::vector<JSValue> Properties::getList(const std::string& property, std::vector<JSValue> defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				auto object = getObject(property, get_context().CreateObject());
				if (object.IsArray()) {
					return static_cast<JSArray>(object);
				}
			}
			return defaultValue;
		}

		JSObject Properties::getObject(const std::string& property, JSObject defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				auto value = get_context().CreateValueFromJSON(getString(property, ""));
				if (value.IsObject()) {
					return static_cast<JSObject>(value);
				}
			}
			return defaultValue;
		}

		std::string Properties::getString(const std::string& property, const std::string& defaultValue) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getString: Unimplemented");
			return "";
		}

		bool Properties::hasProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::hasProperty: Unimplemented");
			return false;
		}

		std::vector<std::string> Properties::listProperties() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::listProperties: Unimplemented");
			return std::vector <std::string>();
		}

		void Properties::removeProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::removeProperty: Unimplemented");
		}

		void Properties::setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setBool: Unimplemented");
		}

		void Properties::setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setDouble: Unimplemented");
		}

		void Properties::setInt(const std::string& property, int value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setInt: Unimplemented");
		}

		void Properties::setList(const std::string& property, std::vector<JSValue> value) TITANIUM_NOEXCEPT
		{
			std::vector<JSValue> arguments;
			arguments.push_back(get_context().CreateArray(value));
			setString(property, static_cast<std::string>(stringify_function__(arguments, get_context().get_global_object())));

			//fireEvent
		}

		void Properties::setObject(const std::string& property, JSObject value) TITANIUM_NOEXCEPT
		{
			setString(property, static_cast<std::string>(stringify_function__({ value }, get_context().get_global_object())));

			//fireEvent
		}

		void Properties::setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setString: Unimplemented");
		}

		void Properties::JSExportInitialize() {
			JSExport<Properties>::SetClassVersion(1);
			JSExport<Properties>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_FUNCTION(Properties, getBool);
			TITANIUM_ADD_FUNCTION(Properties, getDouble);
			TITANIUM_ADD_FUNCTION(Properties, getInt);
			TITANIUM_ADD_FUNCTION(Properties, getList);
			TITANIUM_ADD_FUNCTION(Properties, getObject);
			TITANIUM_ADD_FUNCTION(Properties, getString);
			TITANIUM_ADD_FUNCTION(Properties, hasProperty);
			TITANIUM_ADD_FUNCTION(Properties, listProperties);
			TITANIUM_ADD_FUNCTION(Properties, removeProperty);
			TITANIUM_ADD_FUNCTION(Properties, setBool);
			TITANIUM_ADD_FUNCTION(Properties, setDouble);
			TITANIUM_ADD_FUNCTION(Properties, setInt);
			TITANIUM_ADD_FUNCTION(Properties, setList);
			TITANIUM_ADD_FUNCTION(Properties, setObject);
			TITANIUM_ADD_FUNCTION(Properties, setString);
		}

		JSObject Properties::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
		{
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue App_property = Titanium.GetProperty("App");
			TITANIUM_ASSERT(App_property.IsObject());  // precondition
			JSObject App = static_cast<JSObject>(App_property);

			JSValue Object_property = App.GetProperty("Properties");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			return static_cast<JSObject>(Object_property);
		}

		TITANIUM_FUNCTION(Properties, getBool)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_BOOL_AT_INDEX(defaultValue, 1, false);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return js_context.CreateBoolean(object_ptr->getBool(property, defaultValue));
		}

		TITANIUM_FUNCTION(Properties, getDouble)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_DOUBLE_AT_INDEX(defaultValue, 1, 0);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return js_context.CreateNumber(object_ptr->getDouble(property, defaultValue));
		}

		TITANIUM_FUNCTION(Properties, getInt)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_DOUBLE_AT_INDEX(defaultValue, 1, 0);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return js_context.CreateNumber(object_ptr->getInt(property, defaultValue));
		}

		TITANIUM_FUNCTION(Properties, getList)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_ARRAY_AT_INDEX(defaultValue, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			const auto list = object_ptr->getList(property, static_cast<std::vector<JSValue>>(defaultValue));
			return js_context.CreateArray(list);
		}

		TITANIUM_FUNCTION(Properties, getObject)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(defaultValue, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return object_ptr->getObject(property, defaultValue);
		}

		TITANIUM_FUNCTION(Properties, getString)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_STRING_AT_INDEX(defaultValue, 1, "");

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return js_context.CreateString(object_ptr->getString(property, defaultValue));
		}

		TITANIUM_FUNCTION(Properties, hasProperty)
		{
			ENSURE_STRING_AT_INDEX(property, 0);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return js_context.CreateBoolean(object_ptr->hasProperty(property));
		}

		TITANIUM_FUNCTION(Properties, listProperties)
		{
			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			const auto props = object_ptr->listProperties();
			std::vector<JSValue> converted;
			for (size_t i = 0; i < props.size(); i++) {
				converted.push_back(js_context.CreateString(props.at(i)));
			}
			return js_context.CreateArray(converted);
		}

		TITANIUM_FUNCTION(Properties, removeProperty)
		{
			ENSURE_STRING_AT_INDEX(property, 0);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();
			
			object_ptr->removeProperty(property);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setBool)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_BOOL_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();
			
			object_ptr->setBool(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setDouble)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_DOUBLE_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setDouble(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setInt)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_INT_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setInt(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setList)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_ARRAY_AT_INDEX(array, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setList(property, array);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setObject)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OBJECT_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setObject(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setString)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_STRING_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setString(property, value);
			return js_context.CreateUndefined();
		}
	}
}