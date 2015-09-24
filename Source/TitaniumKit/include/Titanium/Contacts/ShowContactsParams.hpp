/**
 * TitaniumKit ShowContactsParams
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_SHOWCONTACTSPARAMS_HPP_
#define _TITANIUM_CONTACTS_SHOWCONTACTSPARAMS_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace Contacts
	{

		class Person;
		
		using namespace HAL;

		struct ShowContactsParamsCallbacks 
		{
			// need to keep these references to prevent from GC
			JSValue cancel;
			JSValue selectedPerson;
			JSValue selectedProperty;
			std::function<void()> oncancel;
			std::function<void(const std::shared_ptr<Person>&)> onselectedPerson;
			std::function<void(const std::shared_ptr<Person>&)> onselectedProperty;
		};

		/*!
		  @struct
		  @discussion This is the ShowContactsParams.
		  Dictionary of options for the Titanium.Contacts.showContacts method.
		  See http://docs.appcelerator.com/platform/latest/#!/api/showContactsParams
		*/
		struct ShowContactsParams
		{
			bool animated;
			std::vector<std::string> fields;
			ShowContactsParamsCallbacks callbacks;
		};

		TITANIUMKIT_EXPORT ShowContactsParams js_to_ShowContactsParams(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject ShowContactsParams_to_js(const JSContext& js_context, const ShowContactsParams& dict);
		TITANIUMKIT_EXPORT ShowContactsParams create_empty_ShowContactsParams(const JSContext& js_context);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_SHOWCONTACTSPARAMS_HPP_
