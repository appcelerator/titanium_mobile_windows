/**
 * TitaniumKit Titanium.Contacts.Group
 *
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GROUP_HPP_
#define _TITANIUM_GROUP_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Contacts/Constants.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace HAL;

		class Person;

		/*!
		  @class
		  @discussion This is the Titanium Group Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Contacts.Group
		*/
		class TITANIUMKIT_EXPORT Group : public Module, public JSExport<Group>
		{

		public:

			/*!
			  @property
			  @abstract identifier
			  @discussion Identifier of the group.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, identifier);

			/*!
			  @property
			  @abstract name
			  @discussion Name of this group.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, name);

			/*!
			  @property
			  @abstract recordId
			  @discussion Record identifier of the group. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(uint32_t, recordId);

			/*!
			  @method
			  @abstract add
			  @discussion Adds a person to this group.
			*/
			virtual void add(const std::shared_ptr<Person>& person) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract members
			  @discussion Gets people that are members of this group.
			*/
			virtual std::vector<std::shared_ptr<Person>> members() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract remove
			  @discussion Removes a person from this group.
			*/
			virtual void remove(const std::shared_ptr<Person>& person) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract sortedMembers
			  @discussion Gets people that are members of this group, sorted in the specified order.
			*/
			virtual std::vector<std::shared_ptr<Person>> sortedMembers(const SORT& sortBy) TITANIUM_NOEXCEPT;

			Group(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Group()               = default;
			Group(const Group&)            = default;
			Group& operator=(const Group&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Group(Group&&)                 = default;
			Group& operator=(Group&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(identifier);
			TITANIUM_PROPERTY_DEF(name);
			TITANIUM_PROPERTY_DEF(recordId);

			TITANIUM_FUNCTION_DEF(add);
			TITANIUM_FUNCTION_DEF(members);
			TITANIUM_FUNCTION_DEF(remove);
			TITANIUM_FUNCTION_DEF(sortedMembers);
			TITANIUM_FUNCTION_DEF(getIdentifier);
			TITANIUM_FUNCTION_DEF(getName);
			TITANIUM_FUNCTION_DEF(setName);
			TITANIUM_FUNCTION_DEF(getRecordId);
			TITANIUM_FUNCTION_DEF(setRecordId);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string identifier__{};
			std::string name__{};
			uint32_t recordId__{0};
#pragma warning(pop)
		};

	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_GROUP_HPP_