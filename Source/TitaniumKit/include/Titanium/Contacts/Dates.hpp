/**
 * TitaniumKit Dates
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_DATES_HPP_
#define _TITANIUM_CONTACTS_DATES_HPP_

#include "Titanium/detail/TiBase.hpp"

// TODO: inline into Person.hpp
namespace Titanium
{
	namespace Contacts
	{
	
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the ShowContactsParams.
		  Dictionary of options for the Titanium.Contacts.showContacts method.
		  See http://docs.appcelerator.com/platform/latest/#!/api/showContactsParams
		*/
		struct Dates {
			std::vector<std::string> anniversary;
			std::vector<std::string> other;
		};

		TITANIUMKIT_EXPORT Dates js_to_Dates(const JSObject& ject);
		TITANIUMKIT_EXPORT JSObject Dates_to_js(const JSContext&, const Dates&);
		TITANIUMKIT_EXPORT Dates create_empty_Dates(const JSContext&);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_DATES_HPP_
