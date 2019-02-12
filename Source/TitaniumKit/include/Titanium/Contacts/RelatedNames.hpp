/**
 * TitaniumKit RelatedNames
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_RELATEDNAMES_HPP_
#define _TITANIUM_CONTACTS_RELATEDNAMES_HPP_

#include "Titanium/detail/TiBase.hpp"

// TODO: inline into Person.hpp
namespace Titanium
{
	namespace Contacts
	{
	
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the Dictionary of options for the Titanium.Contacts.Person.relatedNames property.
		*/
		struct RelatedNames {
			std::vector<std::string> mother;
			std::vector<std::string> father;
			std::vector<std::string> parent;
			std::vector<std::string> brother;
			std::vector<std::string> sister;
			std::vector<std::string> child;
			std::vector<std::string> friend_;
			std::vector<std::string> spouse;
			std::vector<std::string> partner;
			std::vector<std::string> assistant;
			std::vector<std::string> manager;
			std::vector<std::string> other;
		};

		TITANIUMKIT_EXPORT RelatedNames js_to_RelatedNames(const JSObject& ject);
		TITANIUMKIT_EXPORT JSObject RelatedNames_to_js(const JSContext&, const RelatedNames&);
		TITANIUMKIT_EXPORT RelatedNames create_empty_RelatedNames(const JSContext&);

	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_CONTACTS_RELATEDNAMES_HPP_
