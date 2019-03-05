/**
* Titanium.App.Properties for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/App/Properties.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace App
	{

		Properties::Properties(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::App::Properties(js_context),
			local_settings_(ApplicationData::Current->LocalSettings)
		{
			TITANIUM_LOG_DEBUG("Properties::ctor Initialize");
		}

		void Properties::JSExportInitialize() {
			JSExport<Properties>::SetClassVersion(1);
			JSExport<Properties>::SetParent(JSExport<Titanium::App::Properties>::Class());
		}

		boost::optional<bool> Properties::getBool(const std::string& property, boost::optional<bool> default) TITANIUM_NOEXCEPT
		{
			if (Titanium::App::Properties::hasProperty(property)) {
				return Titanium::App::Properties::getBool(property, default);
			}

			auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				return safe_cast<IPropertyValue^>(values->Lookup(key))->GetBoolean();
			}
			return default;
		}

		boost::optional<double> Properties::getDouble(const std::string& property, boost::optional<double> default) TITANIUM_NOEXCEPT
		{
			if (Titanium::App::Properties::hasProperty(property)) {
				return Titanium::App::Properties::getDouble(property, default);
			}

			auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				return safe_cast<IPropertyValue^>(values->Lookup(key))->GetDouble();
			}
			return default;
		}

		boost::optional<double> Properties::getInt(const std::string& property, boost::optional<double> default) TITANIUM_NOEXCEPT
		{
			if (Titanium::App::Properties::hasProperty(property)) {
				return Titanium::App::Properties::getInt(property, default);
			}

			auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				return safe_cast<IPropertyValue^>(values->Lookup(key))->GetInt32();
			}
			return default;
		}

		boost::optional<std::string> Properties::getString(const std::string& property, const boost::optional<std::string>& default) TITANIUM_NOEXCEPT
		{
			if (Titanium::App::Properties::hasProperty(property)) {
				return Titanium::App::Properties::getString(property, default);
			}

			const auto values = local_settings_->Values;
			const auto key = Utility::ConvertString(property);
			if (values->HasKey(key)) {
				const auto stored_value = safe_cast<IPropertyValue^>(values->Lookup(key));
				if (stored_value->Type == PropertyType::Int32) {
					// Note: If string is too large (> 2048), we split them into array of strings.
					// In that case we stores "array size" here, and value type is Int32

					std::string value;
					const auto array_size = stored_value->GetInt32();
					for (int i = 0; i < array_size; i++) {
						// restore original string as string values are stored in different place.
						auto array_key = "T.A.P.SA." + key + "." + i;
						if (values->HasKey(array_key)) {
							value += Utility::ConvertString(safe_cast<IPropertyValue^>(values->Lookup(array_key))->GetString());
						} else {
							HAL::detail::ThrowRuntimeError("Properties::getString", "Ti.App.Properties: Unable to restore large strings");
						}
					}
					return value;
				}

				return Utility::ConvertString(stored_value->GetString());
			}
			return default;
		}

		bool Properties::hasProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			if (Titanium::App::Properties::hasProperty(property)) {
				return true;
			}
			TITANIUM_LOG_INFO("Checking for property in local settings");
			auto values = local_settings_->Values;
			return values->HasKey(Utility::ConvertString(property));
		}

		std::vector<std::string> Properties::listProperties() TITANIUM_NOEXCEPT
		{
			auto properties = Titanium::App::Properties::listProperties();
			auto values = local_settings_->Values;
			for (auto i = values->First(); i->HasCurrent; i->MoveNext()) {
				properties.push_back(Utility::ConvertString(i->Current->Key));
			}
			return properties;
		}

		void Properties::removeProperty(const std::string& property) TITANIUM_NOEXCEPT
		{
			if (Titanium::App::Properties::hasProperty(property)) {
				return; // can't remove system prop
			}

			const auto values = local_settings_->Values;
			const auto key    = Utility::ConvertString(property);

			// we may have stored array of string in different place
			if (values->HasKey(key)) {
				const auto stored_value = safe_cast<IPropertyValue^>(values->Lookup(key));
				if (stored_value->Type == PropertyType::Int32) {
					// Note: If string is too large (> 2048), we split them into array of strings.
					// In that case we stores "array size" here, and value type is Int32
					const auto array_size = stored_value->GetInt32();
					for (int i = 0; i < array_size; i++) {
						const auto array_key = "T.A.P.SA." + key + "." + i;
						if (values->HasKey(array_key)) {
							values->Remove(array_key);
						}
					}
				}
			}

			if (values->HasKey(key)) {
				values->Remove(key);
			}
		}

		void Properties::setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(value)));

			fireChangeEvent();
		}

		void Properties::setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateDouble(value)));

			fireChangeEvent();
		}

		void Properties::setInt(const std::string& property, int value) TITANIUM_NOEXCEPT
		{
			auto values = local_settings_->Values;
			values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateInt32(value)));

			fireChangeEvent();
		}

		void Properties::setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT
		{
			const auto values = local_settings_->Values;

			// Note: If string is too large (> 2048), we split them into array of strings.
			// In that case we stores "array size" here, and value type is Int32
			const int limit = 2048;
			if (value.size() > limit) {
				std::uint32_t array_size = 0;
				for (std::string::const_iterator it(value.begin()); it != value.end();) {
					const auto sc = std::min(limit, std::distance(it, value.end()));
					const auto newvalue = std::string(it, it + sc);

					// store original string in different place.
					const auto array_key = "T.A.P.SA." + Utility::ConvertString(property) + "." + array_size;
					values->Insert(array_key, dynamic_cast<PropertyValue^>(PropertyValue::CreateString(Utility::ConvertString(newvalue))));

					array_size++;
					it = it + sc;
				};
				values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateInt32(array_size)));
			} else {
				values->Insert(Utility::ConvertString(property), dynamic_cast<PropertyValue^>(PropertyValue::CreateString(Utility::ConvertString(value))));
			}

			fireChangeEvent();
		}

		void Properties::fireChangeEvent() TITANIUM_NOEXCEPT
		{
			JSObject changeEvent = get_context().CreateObject();
			changeEvent.SetProperty("source", this->get_object());
			changeEvent.SetProperty("type", get_context().CreateString("change"));
			this->fireEvent("change", changeEvent);
		}

	} // namespace App
}  // namespace TitaniumWindows
