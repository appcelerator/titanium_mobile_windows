/**
 * TitaniumKit Titanium.Calendar.Reminder
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Calendar/Reminder.hpp"

namespace Titanium
{
	namespace Calendar
	{

		TITANIUM_PROPERTY_READWRITE(Reminder, std::string, id);
		TITANIUM_PROPERTY_READWRITE(Reminder, Titanium::Calendar::METHOD, method);
		TITANIUM_PROPERTY_READWRITE(Reminder, std::chrono::minutes, minutes);

		Reminder::Reminder(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Calendar.Reminder")
		{
		}

		void Reminder::JSExportInitialize() 
		{
			JSExport<Reminder>::SetClassVersion(1);
			JSExport<Reminder>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_PROPERTY_READONLY(Reminder, id);
			TITANIUM_ADD_PROPERTY(Reminder, method);
			TITANIUM_ADD_PROPERTY(Reminder, minutes);
		}

		TITANIUM_PROPERTY_GETTER_STRING(Reminder, id);
		TITANIUM_PROPERTY_GETTER_ENUM(Reminder, method);
		TITANIUM_PROPERTY_SETTER_ENUM(Reminder, method, Titanium::Calendar::METHOD);
		TITANIUM_PROPERTY_GETTER_TIME(Reminder, minutes);
		TITANIUM_PROPERTY_SETTER_TIME_MINUTES(Reminder, minutes);

	} // namespace Calendar
} // namespace Titanium
