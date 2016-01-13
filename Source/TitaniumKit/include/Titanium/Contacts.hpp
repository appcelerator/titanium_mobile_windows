/**
 * TitaniumKit Titanium.Contacts
 *
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CONTACTS_HPP_
#define _TITANIUM_CONTACTS_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Contacts/Constants.hpp"

namespace Titanium
{
	using namespace HAL;

	namespace Contacts
	{
		class Group;
		class Person;
		struct ShowContactsParams;
	}

	/*!
	  @class
	  @discussion This is the Titanium Contacts Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Contacts
	*/
	class TITANIUMKIT_EXPORT ContactsModule : public Module, public JSExport<ContactsModule>
	{

	public:
		/*!
		  @property
		  @abstract contactsAuthorization
		  @discussion Returns an authorization constant indicating if the application has access to the address book.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(Contacts::AUTHORIZATION, contactsAuthorization);

		/*!
		  @method
		  @abstract getAllGroups
		  @discussion Gets all groups.
		*/
		virtual std::vector<std::shared_ptr<Contacts::Group>> getAllGroups() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getAllPeople
		  @discussion Gets all people, unless a limit is specified. On Tizen, use [Titanium.Contacts.Tizen.getAllPeople](Titanium.Contacts.Tizen.getAllPeople).
		*/
		virtual std::vector<std::shared_ptr<Contacts::Person>> getAllPeople(const uint32_t& limit) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getGroupByID
		  @discussion Gets the group with the specified identifier.
		*/
		virtual std::shared_ptr<Contacts::Group> getGroupByID(const int32_t& id) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getGroupByIdentifier
		  @discussion Gets the group with the specified identifier.
		*/
		virtual std::shared_ptr<Contacts::Group> getGroupByIdentifier(const std::string& id) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getPeopleWithName
		  @discussion Gets people with a `firstName`, `middleName` or `lastName` field, or a combination of these fields, that match the specified name.
		*/
		virtual std::vector<std::shared_ptr<Contacts::Person>> getPeopleWithName(const std::string& name) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getPersonByID
		  @discussion Gets the person with the specified identifier.
		*/
		virtual std::shared_ptr<Contacts::Person> getPersonByID(const int32_t& id) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getPersonByIdentifier
		  @discussion Gets the person with the specified identifier.
		*/
		virtual std::shared_ptr<Contacts::Person> getPersonByIdentifier(const std::string& id) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract removeGroup
		  @discussion Removes a group from the address book.
		*/
		virtual void removeGroup(const std::shared_ptr<Contacts::Group>& group) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract removePerson
		  @discussion Removes a contact from the address book.
		*/
		virtual void removePerson(const std::shared_ptr<Contacts::Person>& person) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract requestAuthorization
		  @discussion If authorization is unknown, will bring up a dialog requesting permission.
		*/
		virtual void requestAuthorization(JSObject& callback) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract revert
		  @discussion Reverts all changes made by the previous save to the address book.
		*/
		virtual void revert() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract save
		  @discussion Commits all pending changes to the underlying contacts database.
		*/
		virtual void save(const std::vector<std::shared_ptr<Contacts::Person>>& contacts) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract showContacts
		  @discussion Displays a picker that allows a person to be selected.
		*/
		virtual void showContacts(const Contacts::ShowContactsParams& params) TITANIUM_NOEXCEPT;

		ContactsModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
		virtual ~ContactsModule()                        = default;
		ContactsModule(const ContactsModule&)            = default;
		ContactsModule& operator=(const ContactsModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		ContactsModule(ContactsModule&&)                 = default;
		ContactsModule& operator=(ContactsModule&&)      = default;
#endif

		static void JSExportInitialize();

		/*!
		  @property
		  @abstract CONTACTS_KIND_ORGANIZATION
		  @discussion Specifies that a contact is an organization.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(CONTACTS_KIND_ORGANIZATION);

		/*!
		@property
		@abstract CONTACTS_KIND_PERSON
		@discussion Specifies that a contact is a person.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(CONTACTS_KIND_PERSON);

		/*!
		  @property
		  @abstract CONTACTS_SORT_FIRST_NAME
		  @discussion Specifies that group members will be sorted by first name.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(CONTACTS_SORT_FIRST_NAME);

		/*!
		  @property
		  @abstract CONTACTS_SORT_LAST_NAME
		  @discussion Specifies that group members will be sorted by last name.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(CONTACTS_SORT_LAST_NAME);

		/*!
		  @property
		  @abstract AUTHORIZATION_AUTHORIZED
		  @discussion A [contactsAuthorization](Titanium.Contacts.contactsAuthorization) value indicating that the application is authorized to use the address book.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_AUTHORIZED);

		/*!
		  @property
		  @abstract AUTHORIZATION_DENIED
		  @discussion A [contactsAuthorization](Titanium.Contacts.contactsAuthorization) value indicating that the application is not authorized to use the address book.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_DENIED);

		/*!
		  @property
		  @abstract AUTHORIZATION_RESTRICTED
		  @discussion A [contactsAuthorization](Titanium.Contacts.contactsAuthorization) value indicating that the application is not authorized to use the address book *and*the user cannot change this application's status.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_RESTRICTED);

		/*!
		  @property
		  @abstract AUTHORIZATION_UNKNOWN
		  @discussion A [contactsAuthorization](Titanium.Contacts.contactsAuthorization) value indicating that the authorization state is unknown.
		*/
		TITANIUM_PROPERTY_READONLY_DEF(AUTHORIZATION_UNKNOWN);

		TITANIUM_PROPERTY_READONLY_DEF(contactsAuthorization);

		virtual TITANIUM_FUNCTION_DEF(createGroup);
		virtual TITANIUM_FUNCTION_DEF(createPerson);
		TITANIUM_FUNCTION_DEF(getAllGroups);
		TITANIUM_FUNCTION_DEF(getAllPeople);
		TITANIUM_FUNCTION_DEF(getGroupByID);
		TITANIUM_FUNCTION_DEF(getGroupByIdentifier);
		TITANIUM_FUNCTION_DEF(getPeopleWithName);
		TITANIUM_FUNCTION_DEF(getPersonByID);
		TITANIUM_FUNCTION_DEF(getPersonByIdentifier);
		TITANIUM_FUNCTION_DEF(removeGroup);
		TITANIUM_FUNCTION_DEF(removePerson);
		TITANIUM_FUNCTION_DEF(requestAuthorization);
		TITANIUM_FUNCTION_DEF(revert);
		TITANIUM_FUNCTION_DEF(save);
		TITANIUM_FUNCTION_DEF(showContacts);
		TITANIUM_FUNCTION_DEF(getContactsAuthorization);

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		JSValue CONTACTS_KIND_ORGANIZATION__;
		JSValue CONTACTS_KIND_PERSON__;
		JSValue CONTACTS_SORT_FIRST_NAME__;
		JSValue CONTACTS_SORT_LAST_NAME__;
		JSValue AUTHORIZATION_AUTHORIZED__;
		JSValue AUTHORIZATION_DENIED__;
		JSValue AUTHORIZATION_RESTRICTED__;
		JSValue AUTHORIZATION_UNKNOWN__;
		Contacts::AUTHORIZATION contactsAuthorization__;
#pragma warning(pop)
	};

} // namespace Titanium
#endif // _TITANIUM_CONTACTS_HPP_