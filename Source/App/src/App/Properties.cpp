/**
* Titanium.App.Properties for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/App/Properties.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace App
	{

		JSFunction Properties::createStringifyFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT
		{
			return get_context().CreateFunction("return JSON.stringify(value);", { "value" });
		}

		Properties::Properties(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::App::Properties(js_context),
			stringify_function__(createStringifyFunction(js_context)),
			local_settings_(ApplicationData::Current->LocalSettings)
		{
			TITANIUM_LOG_DEBUG("Properties::ctor Initialize");
		}

		void Properties::JSExportInitialize() {
			JSExport<Properties>::SetClassVersion(1);
			JSExport<Properties>::SetParent(JSExport<Titanium::App::Properties>::Class());
		}

		bool Properties::getBool(const std::string& property, bool default) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				return safe_cast<IPropertyValue^>(values->Lookup(key))->GetBoolean();
			}
			return default;
		}

		double Properties::getDouble(const std::string& property, double default) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				return safe_cast<IPropertyValue^>(values->Lookup(key))->GetDouble();
			}
			return default;
		}

		double Properties::getInt(const std::string& property, double default) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				return safe_cast<IPropertyValue^>(values->Lookup(key))->GetInt32();
			}
			return default;
		}

		JSValue Properties::getList(const std::string& property, JSValue default) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				return get_context().CreateValueFromJSON(getString(property, ""));
			}
			return default;
		}

		JSValue Properties::getObject(const std::string& property, JSValue default) TITANIUM_NOEXCEPT
		{
			if (hasProperty(property)) {
				return get_context().CreateValueFromJSON(getString(property, ""));
			}
			return default;
		}

		std::string Properties::getString(const std::string& property, const std::string& default = "") TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				auto value = safe_cast<IPropertyValue^>(values->Lookup(key))->GetString();
				return Utility::ConvertString(value);
			}
			return default;
		}

		bool Properties::hasProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			return values->HasKey(Utility::ConvertString(property));
		}

		JSValue Properties::listProperties() TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			std::vector<JSValue> properties;
			for (auto i = values->First(); i->HasCurrent; i->MoveNext()) {
				properties.push_back(get_context().CreateString(Utility::ConvertString(i->Current->Key)));
			}
			return get_context().CreateArray(properties);
		}

		void Properties::removeProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Remove(Utility::ConvertString(property));
		}

		JSValue Properties::setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(value)));

			//fireEvent

			return get_context().CreateUndefined();
		}

		JSValue Properties::setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateDouble(value)));

			//fireEvent

			return get_context().CreateUndefined();
		}

		JSValue Properties::setInt(const std::string& property, int value) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateInt32(value)));

			//fireEvent

			return get_context().CreateUndefined();
		}

		JSValue Properties::setList(const std::string& property, JSValue value) TITANIUM_NOEXCEPT
		{
			setString(property, static_cast<std::string>(stringify_function__({ value }, get_context().get_global_object())));

			//fireEvent

			return get_context().CreateUndefined();
		}

		JSValue Properties::setObject(const std::string& property, JSValue value) TITANIUM_NOEXCEPT
		{
			setString(property, static_cast<std::string>(stringify_function__({ value }, get_context().get_global_object())));

			//fireEvent

			return get_context().CreateUndefined();
		}

		JSValue Properties::setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateString(Utility::ConvertString(value))));

			//fireEvent

			return get_context().CreateUndefined();
		}

	}
}  // namespace TitaniumWindows