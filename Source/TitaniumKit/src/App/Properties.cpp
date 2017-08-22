/**
* TitaniumKit Titanium.App.Properties
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "Titanium/detail/TiImpl.hpp"
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
			: Module(js_context, "Ti.App.Properties"),
			  stringify_function__(createStringifyFunction(js_context)),
			  app_properties__(js_context.CreateObject())
		{
			TITANIUM_LOG_DEBUG("Properties:: ctor ", this);
		}

		void Properties::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			HAL_LOG_DEBUG("Properties:: postCallAsConstructor ", this);
		}

		void Properties::loadAppProperties() TITANIUM_NOEXCEPT
		{
			// Statically create loadJson javascript function
			static JSFunction loadJson = get_context().CreateFunction(
				"var file = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory+Ti.Filesystem.separator+'_app_props_.json');"
				"if (file.exists()) return JSON.parse(file.read().text);"
				);

			// Statically create readJson javascript function
			static JSFunction readJson = get_context().CreateFunction(
				"if (json != undefined && property in json) return json[property];"
				"return null;",
				{ "json", "property" }
			);

			// Load _app_props_.json
			const auto result = loadJson(get_context().get_global_object());
			if (!result.IsUndefined() && result.IsObject()) {
				app_properties__ = static_cast<JSObject>(result);
			}
		}

		boost::optional<bool> Properties::getBool(const std::string& property, boost::optional<bool> defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				return static_cast<bool>(app_properties__.GetProperty(property));
			}
			if (defaultValue) {
				return *defaultValue;
			}
			return boost::none;
		}

		boost::optional<double> Properties::getDouble(const std::string& property, boost::optional<double> defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				return static_cast<double>(app_properties__.GetProperty(property));
			}
			if (defaultValue) {
				return *defaultValue;
			}
			return boost::none;
		}

		boost::optional<double> Properties::getInt(const std::string& property, boost::optional<double> defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				return static_cast<int32_t>(app_properties__.GetProperty(property));
			}
			if (defaultValue) {
				return *defaultValue;
			}
			return boost::none;
		}

		JSValue Properties::getList(const std::string& property, JSValue defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				const auto value = getObject(property, get_context().CreateObject());
				if (value.IsObject()) {
					const auto object = static_cast<JSObject>(value);
					if (object.IsArray()) {
						return static_cast<JSArray>(object);
					}
				}
			}
			return defaultValue;
		}

		JSValue Properties::getObject(const std::string& property, JSValue defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				const auto string = getString(property, boost::none);
				if (string) {
					return get_context().CreateValueFromJSON(*string);
				}
			}
			return defaultValue;
		}

		boost::optional<std::string> Properties::getString(const std::string& property, const boost::optional<std::string>& defaultValue) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				return static_cast<std::string>(app_properties__.GetProperty(property));
			}
			if (defaultValue) {
				return *defaultValue;
			}
			return boost::none;
		}

		bool Properties::hasProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			return app_properties__.HasProperty(property);
		}

		std::vector<std::string> Properties::listProperties() TITANIUM_NOEXCEPT
		{
			const auto names = static_cast<std::vector<JSString>>(app_properties__.GetPropertyNames());
			std::vector<std::string> result;
			for (size_t i = 0; i < names.size(); i++) {
				result.push_back(static_cast<std::string>(names.at(i)));
			}
			return result;
		}

		void Properties::removeAllProperties() TITANIUM_NOEXCEPT
		{
			const auto names = listProperties();
			for (size_t i = 0; i < names.size(); i++) {
				removeProperty(names.at(i));
			}
		}

		void Properties::removeProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::removeProperty: Unimplemented");
		}

		void Properties::setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				get_context().JSEvaluateScript("Ti.API.warn('Cannot overwrite/delete read-only property: " + property + "');");
				return;
			}
		}

		void Properties::setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				get_context().JSEvaluateScript("Ti.API.warn('Cannot overwrite/delete read-only property: " + property + "');");
				return;
			}
		}

		void Properties::setInt(const std::string& property, int value) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				get_context().JSEvaluateScript("Ti.API.warn('Cannot overwrite/delete read-only property: " + property + "');");
				return;
			}
		}

		void Properties::setList(const std::string& property, JSValue value) TITANIUM_NOEXCEPT
		{
			if (value.IsObject() && static_cast<JSObject>(value).IsArray()) {
				std::vector<JSValue> arguments = { value };
				setString(property, static_cast<std::string>(stringify_function__(arguments, get_context().get_global_object())));
			} else {
				setObject(property, value);
			}
		}

		void Properties::setObject(const std::string& property, JSValue value) TITANIUM_NOEXCEPT
		{
			setString(property, static_cast<std::string>(stringify_function__({ value }, get_context().get_global_object())));
		}

		void Properties::setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				get_context().JSEvaluateScript("Ti.API.warn('Cannot overwrite/delete read-only property: " + property + "');");
				return;
			}
		}

		void Properties::JSExportInitialize() {
			JSExport<Properties>::SetClassVersion(1);
			JSExport<Properties>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_FUNCTION(Properties, _loadAppProperties);

			TITANIUM_ADD_FUNCTION(Properties, getBool);
			TITANIUM_ADD_FUNCTION(Properties, getDouble);
			TITANIUM_ADD_FUNCTION(Properties, getInt);
			TITANIUM_ADD_FUNCTION(Properties, getList);
			TITANIUM_ADD_FUNCTION(Properties, getObject);
			TITANIUM_ADD_FUNCTION(Properties, getString);
			TITANIUM_ADD_FUNCTION(Properties, hasProperty);
			TITANIUM_ADD_FUNCTION(Properties, listProperties);
			TITANIUM_ADD_FUNCTION(Properties, removeAllProperties);
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

		TITANIUM_FUNCTION(Properties, _loadAppProperties)
		{
			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->loadAppProperties();

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, getBool)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			boost::optional<bool> defaultValue;
			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				if (_1.IsBoolean()) {
					defaultValue = static_cast<bool>(_1);
				}
			}

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			const auto result = object_ptr->getBool(property, defaultValue);
			if (result) {
				return js_context.CreateBoolean(*result);
			}
			return js_context.CreateNull();

		}

		TITANIUM_FUNCTION(Properties, getDouble)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			boost::optional<double> defaultValue;
			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				if (_1.IsNumber()) {
					defaultValue = static_cast<double>(_1);
				}
			}

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			const auto result = object_ptr->getDouble(property, defaultValue);
			if (result) {
				return js_context.CreateNumber(*result);
			}
			return js_context.CreateNull();
		}

		TITANIUM_FUNCTION(Properties, getInt)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			boost::optional<double> defaultValue;
			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				if (_1.IsNumber()) {
					defaultValue = static_cast<double>(_1);
				}
			}

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			const auto result = object_ptr->getInt(property, defaultValue);
			if (result) {
				return js_context.CreateNumber(*result);
			}
			return js_context.CreateNull();

		}

		TITANIUM_FUNCTION(Properties, getList)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_VALUE_AT_INDEX(defaultValue, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return object_ptr->getList(property, defaultValue);
		}

		TITANIUM_FUNCTION(Properties, getObject)
		{
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OPTIONAL_VALUE_AT_INDEX(defaultValue, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			return object_ptr->getObject(property, defaultValue);
		}

		TITANIUM_FUNCTION(Properties, getString)
		{
			ENSURE_STRING_AT_INDEX(property, 0);

			boost::optional<std::string> defaultValue;
			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				if (_1.IsString()) {
					defaultValue = static_cast<std::string>(_1);
				}
			}

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			const auto result = object_ptr->getString(property, defaultValue);
			if (result) {
				return js_context.CreateString(*result);
			}
			return js_context.CreateNull();
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

		TITANIUM_FUNCTION(Properties, removeAllProperties)
		{
			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->removeAllProperties();

			return js_context.CreateUndefined();
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
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_BOOL_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setBool(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setDouble)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_DOUBLE_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setDouble(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setInt)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_INT_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setInt(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setList)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_ARRAY_AT_INDEX(array, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setList(property, array);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setObject)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_OBJECT_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setObject(property, value);
			return js_context.CreateUndefined();
		}

		TITANIUM_FUNCTION(Properties, setString)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_STRING_AT_INDEX(property, 0);
			ENSURE_STRING_AT_INDEX(value, 1);

			const auto js_context = this_object.get_context();
			const auto object_ptr = GetStaticObject(js_context).GetPrivate<Properties>();

			object_ptr->setString(property, value);
			return js_context.CreateUndefined();
		}
	}
}
