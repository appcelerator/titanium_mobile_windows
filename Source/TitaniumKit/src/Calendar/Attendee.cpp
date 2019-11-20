/**
 * TitaniumKit Titanium.Calendar.Attendee
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Calendar/Attendee.hpp"

namespace Titanium
{
	namespace Calendar
	{

		TITANIUM_PROPERTY_READWRITE(Attendee, std::string, email);
		TITANIUM_PROPERTY_READWRITE(Attendee, std::string, name);
		TITANIUM_PROPERTY_READWRITE(Attendee, bool, isOrganizer);
		TITANIUM_PROPERTY_READWRITE(Attendee, Titanium::Calendar::ATTENDEE_ROLE, role);
		TITANIUM_PROPERTY_READWRITE(Attendee, Titanium::Calendar::ATTENDEE_STATUS, status);
		TITANIUM_PROPERTY_READWRITE(Attendee, Titanium::Calendar::ATTENDEE_TYPE, type);

		Attendee::Attendee(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Calendar.Attendee")
		{
		}

		void Attendee::JSExportInitialize() 
		{
			JSExport<Attendee>::SetClassVersion(1);
			JSExport<Attendee>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Attendee, email);
			TITANIUM_ADD_PROPERTY_READONLY(Attendee, name);
			TITANIUM_ADD_PROPERTY_READONLY(Attendee, isOrganizer);
			TITANIUM_ADD_PROPERTY_READONLY(Attendee, role);
			TITANIUM_ADD_PROPERTY_READONLY(Attendee, status);
			TITANIUM_ADD_PROPERTY_READONLY(Attendee, type);
		}

		TITANIUM_PROPERTY_GETTER_STRING(Attendee, email);
		TITANIUM_PROPERTY_GETTER_STRING(Attendee, name);
		TITANIUM_PROPERTY_GETTER_BOOL(Attendee, isOrganizer);
		TITANIUM_PROPERTY_GETTER_ENUM(Attendee, role);
		TITANIUM_PROPERTY_GETTER_ENUM(Attendee, status);
		TITANIUM_PROPERTY_GETTER_ENUM(Attendee, type);

	} // namespace Calendar
} // namespace Titanium
