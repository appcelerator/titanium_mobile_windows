/**
 * TitaniumKit Titanium.Calendar.Alert
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Calendar/Alert.hpp"

namespace Titanium
{
	namespace Calendar
	{

		TITANIUM_PROPERTY_READWRITE(Alert, boost::optional<std::chrono::system_clock::time_point>, absoluteDate);
		TITANIUM_PROPERTY_READWRITE(Alert, boost::optional<std::chrono::system_clock::time_point>, alarmTime);
		TITANIUM_PROPERTY_READWRITE(Alert, std::chrono::minutes, minutes);
		TITANIUM_PROPERTY_READWRITE(Alert, std::string, id);

		Alert::Alert(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Calendar.Alert")
		{
		}

		void Alert::JSExportInitialize() 
		{
			JSExport<Alert>::SetClassVersion(1);
			JSExport<Alert>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(Alert, absoluteDate);
			TITANIUM_ADD_PROPERTY(Alert, minutes);
			TITANIUM_ADD_PROPERTY_READONLY(Alert, alarmTime);
			TITANIUM_ADD_PROPERTY_READONLY(Alert, id);
		}

		TITANIUM_PROPERTY_GETTER_DATE(Alert, absoluteDate);
		TITANIUM_PROPERTY_SETTER_DATE(Alert, absoluteDate);
		TITANIUM_PROPERTY_GETTER_DATE(Alert, alarmTime);
		TITANIUM_PROPERTY_GETTER_STRING(Alert, id);
		TITANIUM_PROPERTY_GETTER_TIME(Alert, minutes);
		TITANIUM_PROPERTY_SETTER_TIME_MINUTES(Alert, minutes);

	} // namespace Calendar
} // namespace Titanium
