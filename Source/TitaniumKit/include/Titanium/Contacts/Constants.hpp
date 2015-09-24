/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_CONSTANTS_HPP_
#define _TITANIUM_CONTACTS_CONSTANTS_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_set>
#include <functional>

#define ENUM_HASH(NAME) \
using Titanium::Contacts::NAME; \
template <> \
struct hash<NAME> \
{ \
	using argument_type = NAME; \
	using result_type = std::size_t; \
	using underlying_type = std::underlying_type<argument_type>::type; \
	std::hash<underlying_type> hash_function = std::hash<underlying_type>(); \
\
	result_type operator()(const argument_type& property_attribute) const \
	{ \
		return hash_function(static_cast<underlying_type>(property_attribute)); \
	} \
};

#define ENUM_CONVERSIONS(NAME) \
static std::string to_string(const NAME&) TITANIUM_NOEXCEPT; \
static NAME to_##NAME(const std::string&) TITANIUM_NOEXCEPT; \
static NAME to_##NAME(std::underlying_type<NAME>::type) TITANIUM_NOEXCEPT; \
static std::underlying_type<NAME>::type to_underlying_type(const NAME&) TITANIUM_NOEXCEPT;

namespace Titanium
{
	namespace Contacts
	{
		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.Contacts.contactsAuthorization property.

		  @constant AUTHORIZED A contactsAuthorization value indicating that the application is authorized to use the address book.

		  @constant DENIED A contactsAuthorization value indicating that the application is not authorized to use the address book.

		  @constant RESTRICTED A contactsAuthorization value indicating that the application is not authorized to use the address book and the user cannot change this application's status.

		  @constant UNKNOWN A contactsAuthorization value indicating that the authorization state is unknown.
		*/
		enum class TITANIUMKIT_EXPORT AUTHORIZATION {
			AUTHORIZED,
			DENIED,
			RESTRICTED,
			UNKNOWN
		};

		/*!
		  @enum

		  @abstract These constants are for use with the Titanium.Contacts.Group.sortedMembers function.

		  @constant FIRST_NAME Specifies that group members will be sorted by first name.

		  @constant LAST_NAME Specifies that group members will be sorted by last name.
		*/
		enum class TITANIUMKIT_EXPORT SORT {
			FIRST_NAME,
			LAST_NAME
		};

		/*!
		  @enum

		  @abstract These constants are for use with the Titanium.Contacts.Person.kind property.

		  @constant ORGANIZATION Specifies that a contact is an organization.

		  @constant PERSON Specifies that a contact is a person.
		*/
		enum class TITANIUMKIT_EXPORT KIND {
			ORGANIZATION,
			PERSON
		};
	} // namespace Contacts
}  // namespace Titanium

namespace std
{
	ENUM_HASH(AUTHORIZATION)
	ENUM_HASH(SORT)
	ENUM_HASH(KIND)
}  // namespace std

namespace Titanium
{
	namespace Contacts
	{
		class TITANIUMKIT_EXPORT Constants final
		{
		public:
			ENUM_CONVERSIONS(AUTHORIZATION)
			ENUM_CONVERSIONS(SORT)
			ENUM_CONVERSIONS(KIND)
		};
	} // namespace Contacts
}  // namespace Titanium

#endif  // _TITANIUM_CONTACTS_CONSTANTS_HPP_
