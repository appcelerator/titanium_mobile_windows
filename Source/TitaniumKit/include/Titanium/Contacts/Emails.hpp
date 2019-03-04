/**
 * TitaniumKit Emails
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_EMAILS_HPP_
#define _TITANIUM_CONTACTS_EMAILS_HPP_

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
		struct Emails {
			std::vector<std::string> home;
			std::vector<std::string> work;
			std::vector<std::string> other;
		};

		TITANIUMKIT_EXPORT Emails js_to_Emails(const JSObject& ject);
		TITANIUMKIT_EXPORT JSObject Emails_to_js(const JSContext&, const Emails&);
		TITANIUMKIT_EXPORT Emails create_empty_Emails(const JSContext&);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_EMAILS_HPP_
