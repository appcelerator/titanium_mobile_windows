/**
 * TitaniumKit Titanium.Contacts
 *
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts.hpp"
#include "Titanium/Contacts/Group.hpp"
#include "Titanium/Contacts/Person.hpp"
#include "Titanium/Contacts/ShowContactsParams.hpp"
#include "Titanium/detail/TiImpl.hpp"

#define CREATE_TITANIUM_CONTACTS(NAME) \
  JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue Contacts_property = Titanium.GetProperty("Contacts"); \
  TITANIUM_ASSERT(Contacts_property.IsObject()); \
  JSObject Contacts = static_cast<JSObject>(Contacts_property); \
  JSValue NAME##_property = Contacts.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  JSObject NAME = static_cast<JSObject>(NAME##_property); \
  auto NAME##_obj = NAME.CallAsConstructor(parameters); \
  Titanium::Module::applyProperties(parameters, NAME##_obj); \
  return NAME##_obj;

namespace Titanium
{

	ContactsModule::ContactsModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.Contacts"),
		contactsAuthorization__(Titanium::Contacts::AUTHORIZATION::UNKNOWN)
	{
	}

	ContactsModule& ContactsModule::GroupClass(const JSClass& Group) TITANIUM_NOEXCEPT
	{
		group__ = Group;
		return *this;
	}

	ContactsModule& ContactsModule::PersonClass(const JSClass& Person) TITANIUM_NOEXCEPT
	{
		person__ = Person;
		return *this;
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, Group)
	{
		return get_context().CreateObject(group__);
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, Person)
	{
		return get_context().CreateObject(person__);
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, CONTACTS_KIND_ORGANIZATION)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::KIND::ORGANIZATION));
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, CONTACTS_KIND_PERSON)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::KIND::PERSON));
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, CONTACTS_SORT_FIRST_NAME)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::SORT::FIRST_NAME));
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, CONTACTS_SORT_LAST_NAME)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::SORT::LAST_NAME));
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, AUTHORIZATION_AUTHORIZED)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::AUTHORIZATION::AUTHORIZED));
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, AUTHORIZATION_DENIED)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::AUTHORIZATION::DENIED));
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, AUTHORIZATION_RESTRICTED)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::AUTHORIZATION::RESTRICTED));
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, AUTHORIZATION_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(Titanium::Contacts::AUTHORIZATION::UNKNOWN));
	}

	TITANIUM_PROPERTY_READ(ContactsModule, Contacts::AUTHORIZATION, contactsAuthorization);

	std::vector<std::shared_ptr<Contacts::Group>> ContactsModule::getAllGroups() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::getAllGroups: Unimplemented");
		return std::vector<std::shared_ptr<Contacts::Group>>();
	}

	std::vector<std::shared_ptr<Contacts::Person>> ContactsModule::getAllPeople(const uint32_t& limit) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::getAllPeople: Unimplemented");
		return std::vector<std::shared_ptr<Contacts::Person>>();
	}

	std::shared_ptr<Contacts::Group> ContactsModule::getGroupByID(const int32_t& id) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::getGroupByID: Unimplemented");
		return nullptr;
	}

	std::shared_ptr<Contacts::Group> ContactsModule::getGroupByIdentifier(const std::string& id) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::getGroupByIdentifier: Unimplemented");
		return nullptr;
	}

	std::vector<std::shared_ptr<Contacts::Person>> ContactsModule::getPeopleWithName(const std::string& name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::getPeopleWithName: Unimplemented");
		return std::vector<std::shared_ptr<Contacts::Person>>();
	}

	std::shared_ptr<Contacts::Person> ContactsModule::getPersonByID(const int32_t& id) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::getPersonByID: Unimplemented");
		return nullptr;
	}

	std::shared_ptr<Contacts::Person> ContactsModule::getPersonByIdentifier(const std::string& id) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::getPersonByIdentifier: Unimplemented");
		return nullptr;
	}

	void ContactsModule::removeGroup(const std::shared_ptr<Contacts::Group>& group) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::removeGroup: Unimplemented");
	}

	void ContactsModule::removePerson(const std::shared_ptr<Contacts::Person>& person) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::removePerson: Unimplemented");
	}

	void ContactsModule::requestAuthorization(JSObject& callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::requestAuthorization: Unimplemented");
	}

	void ContactsModule::revert() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::revert: Unimplemented");
	}

	void ContactsModule::save(const std::vector<std::shared_ptr<Contacts::Person>>& contacts) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::save: Unimplemented");
	}

	void ContactsModule::showContacts(const Contacts::ShowContactsParams& params) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("ContactsModule::showContacts: Unimplemented");
	}

	void ContactsModule::JSExportInitialize()
	{
		JSExport<ContactsModule>::SetClassVersion(1);
		JSExport<ContactsModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, Group);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, Person);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, CONTACTS_KIND_ORGANIZATION);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, CONTACTS_KIND_PERSON);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, CONTACTS_SORT_FIRST_NAME);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, CONTACTS_SORT_LAST_NAME);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, AUTHORIZATION_AUTHORIZED);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, AUTHORIZATION_DENIED);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, AUTHORIZATION_RESTRICTED);
		TITANIUM_ADD_CONSTANT_PROPERTY(ContactsModule, AUTHORIZATION_UNKNOWN);
		TITANIUM_ADD_PROPERTY_READONLY(ContactsModule, contactsAuthorization);

		TITANIUM_ADD_FUNCTION(ContactsModule, createGroup);
		TITANIUM_ADD_FUNCTION(ContactsModule, createPerson);
		TITANIUM_ADD_FUNCTION(ContactsModule, getAllGroups);
		TITANIUM_ADD_FUNCTION(ContactsModule, getAllPeople);
		TITANIUM_ADD_FUNCTION(ContactsModule, getGroupByID);
		TITANIUM_ADD_FUNCTION(ContactsModule, getGroupByIdentifier);
		TITANIUM_ADD_FUNCTION(ContactsModule, getPeopleWithName);
		TITANIUM_ADD_FUNCTION(ContactsModule, getPersonByID);
		TITANIUM_ADD_FUNCTION(ContactsModule, getPersonByIdentifier);
		TITANIUM_ADD_FUNCTION(ContactsModule, removeGroup);
		TITANIUM_ADD_FUNCTION(ContactsModule, removePerson);
		TITANIUM_ADD_FUNCTION(ContactsModule, requestAuthorization);
		TITANIUM_ADD_FUNCTION(ContactsModule, revert);
		TITANIUM_ADD_FUNCTION(ContactsModule, save);
		TITANIUM_ADD_FUNCTION(ContactsModule, showContacts);
		TITANIUM_ADD_FUNCTION(ContactsModule, getContactsAuthorization);
	}

	TITANIUM_FUNCTION(ContactsModule, createGroup)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_CONTACTS(Group);
	}

	TITANIUM_FUNCTION(ContactsModule, createPerson)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_CONTACTS(Person);
		// TODO call save() after!
	}

	TITANIUM_FUNCTION(ContactsModule, getAllGroups)
	{
		std::vector<JSValue> values;
		for (auto value : getAllGroups()) {
			values.push_back(value->get_object());
		}
		return get_context().CreateArray(values);
	}

	TITANIUM_FUNCTION(ContactsModule, getAllPeople)
	{
		ENSURE_OPTIONAL_INT_AT_INDEX(limit, 0, 0);
		std::vector<JSValue> values;
		for (auto value : getAllPeople(limit)) {
			values.push_back(value->get_object());
		}
		return get_context().CreateArray(values);
	}

	TITANIUM_FUNCTION(ContactsModule, getGroupByID)
	{
		ENSURE_INT_AT_INDEX(id, 0);
		auto group = getGroupByID(id);
		if (group != nullptr) {
			return group->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(ContactsModule, getGroupByIdentifier)
	{
		ENSURE_STRING_AT_INDEX(id, 0);
		auto group = getGroupByIdentifier(id);
		if (group != nullptr) {
			return group->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(ContactsModule, getPeopleWithName)
	{
		ENSURE_STRING_AT_INDEX(name, 0);
		auto people = getPeopleWithName(name);
		std::vector<JSValue> values;
		for (auto value : people) {
			values.push_back(value->get_object());
		}
		return get_context().CreateArray(values);
	}

	TITANIUM_FUNCTION(ContactsModule, getPersonByID)
	{
		ENSURE_INT_AT_INDEX(id, 0);
		auto person = getPersonByID(id);
		if (person != nullptr) {
			return person->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(ContactsModule, getPersonByIdentifier)
	{
		ENSURE_STRING_AT_INDEX(id, 0);
		auto person = getPersonByIdentifier(id);
		if (person != nullptr) {
			return person->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_FUNCTION(ContactsModule, removeGroup)
	{
		ENSURE_OBJECT_AT_INDEX(group, 0);
		removeGroup(group.GetPrivate<Contacts::Group>());
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(ContactsModule, removePerson)
	{
		ENSURE_OBJECT_AT_INDEX(person, 0);
		removePerson(person.GetPrivate<Contacts::Person>());
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(ContactsModule, requestAuthorization)
	{
		ENSURE_OBJECT_AT_INDEX(callback, 0);
		requestAuthorization(callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(ContactsModule, revert)
	{
		revert();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(ContactsModule, save)
	{
		std::vector<std::shared_ptr<Contacts::Person>> contacts;
		if (arguments.size() > 0) {
			auto arg = arguments.at(0);
			ENSURE_OBJECT_ARRAY(arg, contacts, Contacts::Person);
		}
		save(contacts);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(ContactsModule, showContacts)
	{
		// optional arg
		if (arguments.size() > 0) {
			ENSURE_OBJECT_AT_INDEX(params, 0);
			showContacts(Titanium::Contacts::js_to_ShowContactsParams(params));
		} else {
			showContacts(Titanium::Contacts::create_empty_ShowContactsParams(get_context()));
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_PROPERTY_GETTER(ContactsModule, contactsAuthorization)
	{
		return get_context().CreateNumber(Titanium::Contacts::Constants::to_underlying_type(get_contactsAuthorization()));
	}

	TITANIUM_FUNCTION_AS_GETTER(ContactsModule, getContactsAuthorization, contactsAuthorization)

} // namespace Titanium
