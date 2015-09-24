/**
 * TitaniumKit Titanium.Contacts.Group
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Group.hpp"
#include "Titanium/Contacts/Person.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Contacts
	{

		Group::Group(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context),
			name__(""),
			recordId__(0)
		{
		}

		JSValue Group::get_identifier() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_READWRITE(Group, std::string, name)
		TITANIUM_PROPERTY_READWRITE(Group, uint32_t, recordId)

		void Group::add(const std::shared_ptr<Person>& person) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Group::add: Unimplemented");
		}

		std::vector<std::shared_ptr<Person>> Group::members() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Group::members: Unimplemented");
			return std::vector<std::shared_ptr<Person>>();
		}

		void Group::remove(const std::shared_ptr<Person>& person) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Group::remove: Unimplemented");
		}

		std::vector<std::shared_ptr<Person>> Group::sortedMembers(const SORT& sortBy) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Group::sortedMembers: Unimplemented");
			return std::vector<std::shared_ptr<Person>>();
		}

		void Group::JSExportInitialize() {
			JSExport<Group>::SetClassVersion(1);
			JSExport<Group>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Group, identifier);
			TITANIUM_ADD_PROPERTY(Group, name);
			TITANIUM_ADD_PROPERTY(Group, recordId);

			TITANIUM_ADD_FUNCTION(Group, add);
			TITANIUM_ADD_FUNCTION(Group, members);
			TITANIUM_ADD_FUNCTION(Group, remove);
			TITANIUM_ADD_FUNCTION(Group, sortedMembers);
			TITANIUM_ADD_FUNCTION(Group, getName);
			TITANIUM_ADD_FUNCTION(Group, setName);
			TITANIUM_ADD_FUNCTION(Group, getRecordId);
			TITANIUM_ADD_FUNCTION(Group, setRecordId);
		}

		TITANIUM_PROPERTY_GETTER(Group, identifier)
		{
			return get_identifier();
		}

		TITANIUM_PROPERTY_GETTER_STRING(Group, name);
		TITANIUM_PROPERTY_SETTER_STRING(Group, name);

		TITANIUM_PROPERTY_GETTER_INT(Group, recordId);
		TITANIUM_PROPERTY_SETTER_INT(Group, recordId);

		TITANIUM_FUNCTION(Group, add)
		{
			ENSURE_OBJECT_AT_INDEX(person, 0);
			add(person.GetPrivate<Person>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Group, members)
		{
			std::vector<JSValue> values;
			for (auto value : members()) {
				values.push_back(value->get_object());
			}
			return get_context().CreateArray(values);
		}

		TITANIUM_FUNCTION(Group, remove)
		{
			ENSURE_OBJECT_AT_INDEX(person, 0);
			remove(person.GetPrivate<Person>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Group, sortedMembers)
		{
			ENSURE_ENUM_AT_INDEX(sortBy, 0, SORT);
			std::vector<JSValue> values;
			for (auto value : sortedMembers(sortBy)) {
				values.push_back(value->get_object());
			}
			return get_context().CreateArray(values);
		}

		TITANIUM_FUNCTION_AS_GETTER(Group, getIdentifier, identifier)

		TITANIUM_FUNCTION_AS_GETTER(Group, getName, name)
		TITANIUM_FUNCTION_AS_SETTER(Group, setName, name)

		TITANIUM_FUNCTION_AS_GETTER(Group, getRecordId, recordId)
		TITANIUM_FUNCTION_AS_SETTER(Group, setRecordId, recordId)

	} // namespace Contacts
} // namespace Titanium