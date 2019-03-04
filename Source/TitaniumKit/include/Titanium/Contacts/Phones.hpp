/**
 * TitaniumKit Phones
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_PHONES_HPP_
#define _TITANIUM_CONTACTS_PHONES_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace Contacts
	{
	
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the Dictionary of options for the Titanium.Contacts.Person.phone property.
		*/
		struct Phones {
			std::vector<std::string> home;
			std::vector<std::string> work;
			std::vector<std::string> other;
			std::vector<std::string> mobile;
			std::vector<std::string> pager;
			std::vector<std::string> workFax;
			std::vector<std::string> homeFax;
			std::vector<std::string> main;
			std::vector<std::string> iPhone;
		};

		TITANIUMKIT_EXPORT Phones js_to_Phones(const JSObject& ject);
		TITANIUMKIT_EXPORT JSObject Phones_to_js(const JSContext&, const Phones&);
		TITANIUMKIT_EXPORT Phones create_empty_Phones(const JSContext&);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_PHONES_HPP_
