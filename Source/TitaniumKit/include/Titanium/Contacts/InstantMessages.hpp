/**
 * TitaniumKit InstantMessages
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_INSTANTMESSAGES_HPP_
#define _TITANIUM_CONTACTS_INSTANTMESSAGES_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace Contacts
	{
	
		using namespace HAL;

		struct InstantMessage {
			// TODO Do more validation for service values:
			// AIM, Facebook, GaduGadu, GoogleTalk, ICQ, Jabber, MSN, QQ, Skype, or Yahoo. These values are key sensitive.
			// twitter, sinaweibo, gamecenter, facebook, myspace, linkedin, or flickr for socialProfile services
			std::string service;
			std::string username;
		};

		/*!
		  @struct
		  @discussion This is the Dictionary of options for the Titanium.Contacts.Person.instantMessage property.
		*/
		struct InstantMessages {
			std::vector<InstantMessage> home;
			std::vector<InstantMessage> work;
			std::vector<InstantMessage> other;
		};

		TITANIUMKIT_EXPORT InstantMessages js_to_InstantMessages(const JSObject&);
		TITANIUMKIT_EXPORT JSObject InstantMessages_to_js(const JSContext&, const InstantMessages&);
		TITANIUMKIT_EXPORT InstantMessages create_empty_InstantMessages(const JSContext&);

		TITANIUMKIT_EXPORT InstantMessage js_to_InstantMessage(const JSObject&);
		TITANIUMKIT_EXPORT JSObject InstantMessage_to_js(const JSContext&, const InstantMessage&);
		
	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_INSTANTMESSAGES_HPP_
