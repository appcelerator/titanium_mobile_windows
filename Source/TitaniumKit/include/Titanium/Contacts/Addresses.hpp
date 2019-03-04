/**
 * TitaniumKit Addresses
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_ADDRESSES_HPP_
#define _TITANIUM_CONTACTS_ADDRESSES_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace Contacts
	{
	
		using namespace HAL;

		struct Address {
			// TODO Do more validation/use another type to hold standard two character country codes?
			std::string countryCode;
			std::string street;
			std::string city;
			std::string state;
			std::string country;
			std::string postalCode;
			// County?
		};

		/*!
		  @struct
		  @discussion This is the ShowContactsParams.
		  Dictionary of options for the Titanium.Contacts.showContacts method.
		  See http://docs.appcelerator.com/platform/latest/#!/api/showContactsParams
		*/
		struct Addresses {
			std::vector<Address> home;
			std::vector<Address> work;
			std::vector<Address> other;
		};

		TITANIUMKIT_EXPORT Addresses js_to_Addresses(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject Addresses_to_js(const JSContext& js_context, const Addresses& dict);
		TITANIUMKIT_EXPORT Addresses create_empty_Addresses(const JSContext& js_context);

		TITANIUMKIT_EXPORT Address js_to_Address(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject Address_to_js(const JSContext& js_context, const Address& dict);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_ADDRESSES_HPP_
