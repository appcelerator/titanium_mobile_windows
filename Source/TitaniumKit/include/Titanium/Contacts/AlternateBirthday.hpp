/**
 * TitaniumKit AlternateBirthday
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_ALTERNATEBIRTHDAY_HPP_
#define _TITANIUM_CONTACTS_ALTERNATEBIRTHDAY_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace Contacts
	{
	
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the AlternateBirthday.
		  Dictionary of options for the Titanium.Contacts.Person.alternateBirthday property.
		  See http://docs.appcelerator.com/platform/latest/#!/api/Titanium.Contacts.Person-property-alternateBirthday
		*/
		struct AlternateBirthday {
			std::string calendarIdentifier; // chinese, hebrew and islamic-civil
			uint32_t era;
			int32_t year;
			uint32_t month;
			uint32_t day;
			bool isLeapMonth;
		};

		TITANIUMKIT_EXPORT AlternateBirthday js_to_AlternateBirthday(const JSObject& ject);
		TITANIUMKIT_EXPORT JSObject AlternateBirthday_to_js(const JSContext&, const AlternateBirthday&);
		TITANIUMKIT_EXPORT AlternateBirthday create_empty_AlternateBirthday(const JSContext&);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_ALTERNATEBIRTHDAY_HPP_
