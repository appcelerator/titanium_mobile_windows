/**
 * TitaniumKit Urls
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_URLS_HPP_
#define _TITANIUM_CONTACTS_URLS_HPP_

#include "Titanium/detail/TiBase.hpp"

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
		struct Urls {
			std::vector<std::string> homepage;
			std::vector<std::string> home;
			std::vector<std::string> work;
			std::vector<std::string> other;
		};

		TITANIUMKIT_EXPORT Urls js_to_Urls(const JSObject& ject);
		TITANIUMKIT_EXPORT JSObject Urls_to_js(const JSContext&, const Urls&);
		TITANIUMKIT_EXPORT Urls create_empty_Urls(const JSContext&);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_EMAILS_HPP_
