/**
* Titanium.App.Properties for Windows
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

		Properties::Properties(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, arguments)
		{
		}

		bool Properties::getBool(const std::string& property, bool default) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getBool: Unimplemented");
			return false;
		}

		double Properties::getDouble(const std::string& property, double default) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getDouble: Unimplemented");
			return 0;
		}

		double Properties::getInt(const std::string& property, double default) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getInt: Unimplemented");
			return 0;
		}

		JSValue Properties::getList(const std::string& property, JSValue default) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getList: Unimplemented");
			return get_context().CreateUndefined();
		}

		JSValue Properties::getObject(const std::string& property, JSValue default) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getObject: Unimplemented");
			return get_context().CreateUndefined();
		}

		std::string Properties::getString(const std::string& property, const std::string& default) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::getString: Unimplemented");
			return "";
		}

		bool Properties::hasProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::hasProperty: Unimplemented");
			return false;
		}

		JSValue Properties::listProperties() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::listProperties: Unimplemented");
			return get_context().CreateUndefined();
		}

		void Properties::removeProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::removeProperty: Unimplemented");
		}

		JSValue Properties::setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setBool: Unimplemented");
			return get_context().CreateUndefined();
		}

		JSValue Properties::setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setDouble: Unimplemented");
			return get_context().CreateUndefined();
		}

		JSValue Properties::setInt(const std::string& property, int value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setInt: Unimplemented");
			return get_context().CreateUndefined();
		}

		JSValue Properties::setList(const std::string& property, JSValue value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setList: Unimplemented");
			return get_context().CreateUndefined();
		}

		JSValue Properties::setObject(const std::string& property, JSValue value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setObject: Unimplemented");
			return get_context().CreateUndefined();
		}

		JSValue Properties::setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Properties::setString: Unimplemented");
			return get_context().CreateUndefined();
		}


		void Properties::JSExportInitialize() {
			JSExport<Properties>::SetClassVersion(1);
			JSExport<Properties>::SetParent(JSExport<Module>::Class());

			JSExport<Properties>::AddFunctionProperty("getBool", std::mem_fn(&Properties::js_getBool));
			JSExport<Properties>::AddFunctionProperty("getDouble", std::mem_fn(&Properties::js_getDouble));
			JSExport<Properties>::AddFunctionProperty("getInt", std::mem_fn(&Properties::js_getInt));
			JSExport<Properties>::AddFunctionProperty("getList", std::mem_fn(&Properties::js_getList));
			JSExport<Properties>::AddFunctionProperty("getObject", std::mem_fn(&Properties::js_getObject));
			JSExport<Properties>::AddFunctionProperty("getString", std::mem_fn(&Properties::js_getString));
			JSExport<Properties>::AddFunctionProperty("hasProperty", std::mem_fn(&Properties::js_hasProperty));
			JSExport<Properties>::AddFunctionProperty("listProperties", std::mem_fn(&Properties::js_listProperties));
			JSExport<Properties>::AddFunctionProperty("removeProperty", std::mem_fn(&Properties::js_removeProperty));
			JSExport<Properties>::AddFunctionProperty("setBool", std::mem_fn(&Properties::js_setBool));
			JSExport<Properties>::AddFunctionProperty("setDouble", std::mem_fn(&Properties::js_setDouble));
			JSExport<Properties>::AddFunctionProperty("setInt", std::mem_fn(&Properties::js_setInt));
			JSExport<Properties>::AddFunctionProperty("setList", std::mem_fn(&Properties::js_setList));
			JSExport<Properties>::AddFunctionProperty("setObject", std::mem_fn(&Properties::js_setObject));
			JSExport<Properties>::AddFunctionProperty("setString", std::mem_fn(&Properties::js_setString));
		}

		JSValue Properties::js_getBool(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsBoolean());

				const std::string property = static_cast<std::string>(_0);
				const bool default = static_cast<bool>(_1);

				return get_context().CreateBoolean(getBool(property, default));

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				return get_context().CreateBoolean(getBool(property, false));
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_getDouble(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsNumber());

				const std::string property = static_cast<std::string>(_0);
				const double default = static_cast<double>(_1);

				return get_context().CreateNumber(getDouble(property, default));

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsNumber());

				const std::string property = static_cast<std::string>(_0);

				return get_context().CreateNumber(getDouble(property, 0));
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_getInt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsNumber());

				const std::string property = static_cast<std::string>(_0);
				const double default = static_cast<double>(_1);

				return get_context().CreateNumber(getInt(property, default));

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsNumber());

				const std::string property = static_cast<std::string>(_0);

				return get_context().CreateNumber(getInt(property, 0));
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_getList(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsObject());

				const std::string property = static_cast<std::string>(_0);
				const auto default = _1;

				getList(property, default);

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				getList(property, get_context().CreateUndefined());
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_getObject(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsObject());

				const std::string property = static_cast<std::string>(_0);
				const auto default = _1;

				return getObject(property, default);

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				return getObject(property, get_context().CreateUndefined());
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_getString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateString("");

			} else if (arguments.size() < 2) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				return get_context().CreateString(getString(property, ""));

			} else if (arguments.size() < 3) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsString());

				const std::string property = static_cast<std::string>(_0);
				const std::string default = static_cast<std::string>(_1);

				return get_context().CreateString(getString(property, default));
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_hasProperty(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);

			TITANIUM_ASSERT(_0.IsString());

			const std::string property = static_cast<std::string>(_0);

			return get_context().CreateBoolean(hasProperty(property));
		}

		JSValue Properties::js_listProperties(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return listProperties();
		}

		JSValue Properties::js_removeProperty(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);

			TITANIUM_ASSERT(_0.IsString());

			const std::string property = static_cast<std::string>(_0);

			removeProperty(property);
			return get_context().CreateUndefined();
		}

		JSValue Properties::js_setBool(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsBoolean());

				const std::string property = static_cast<std::string>(_0);
				const bool value = static_cast<bool>(_1);

				setBool(property, value);

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				setBool(property, false);
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_setDouble(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsNumber());

				const std::string property = static_cast<std::string>(_0);
				const int value = static_cast<int>(_1);

				setDouble(property, value);

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				setDouble(property, 0);
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_setInt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsNumber());

				const std::string property = static_cast<std::string>(_0);
				const int value = static_cast<int>(_1);

				setInt(property, value);

			} else if (arguments.size() >= 1) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				setInt(property, 0);
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_setList(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsObject());

				const std::string property = static_cast<std::string>(_0);
				const auto value = _1;

				setList(property, value);

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				setList(property, get_context().CreateUndefined());
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_setObject(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsObject());

				const std::string property = static_cast<std::string>(_0);
				const auto value = _1;

				setObject(property, value);

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				setObject(property, get_context().CreateUndefined());
			}

			return get_context().CreateUndefined();
		}

		JSValue Properties::js_setString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsString());

				const std::string property = static_cast<std::string>(_0);
				const std::string value = static_cast<std::string>(_1);

				setString(property, value);

			} else if (arguments.size() >= 2) {

				const auto _0 = arguments.at(0);

				TITANIUM_ASSERT(_0.IsString());

				const std::string property = static_cast<std::string>(_0);

				setString(property, "");
			}

			return get_context().CreateUndefined();
		}
	}
}