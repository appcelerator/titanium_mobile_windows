/**
 * Titanium.Contacts for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_CONTACTS_HPP_
#define _TITANIUMWINDOWS_CONTACTS_HPP_

#include "TitaniumWindows_Ti_EXPORT.h"
#include "Titanium/Contacts.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium.Contacts implementation for Windows.
	*/
	class TITANIUMWINDOWS_TI_EXPORT ContactsModule final : public Titanium::ContactsModule, public JSExport<ContactsModule>
	{

	public:
		
		ContactsModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
		virtual ~ContactsModule()                        = default;
		ContactsModule(const ContactsModule&)            = default;
		ContactsModule& operator=(const ContactsModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		ContactsModule(ContactsModule&&)                 = default;
		ContactsModule& operator=(ContactsModule&&)      = default;
#endif

		static void JSExportInitialize();

		virtual std::vector<std::shared_ptr<Titanium::Contacts::Group>> getAllGroups() TITANIUM_NOEXCEPT override final;
		virtual std::vector<std::shared_ptr<Titanium::Contacts::Person>> getAllPeople(const uint32_t& limit) TITANIUM_NOEXCEPT override final;
		virtual std::shared_ptr<Titanium::Contacts::Group> getGroupByIdentifier(const JSValue& id) TITANIUM_NOEXCEPT override final;
		virtual std::vector<std::shared_ptr<Titanium::Contacts::Person>> getPeopleWithName(const std::string& name) TITANIUM_NOEXCEPT override final;
		virtual std::shared_ptr<Titanium::Contacts::Person> getPersonByIdentifier(const JSValue& id) TITANIUM_NOEXCEPT override final;
		virtual void removeGroup(const std::shared_ptr<Titanium::Contacts::Group>& group) TITANIUM_NOEXCEPT override final;
		virtual void removePerson(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT override final;
		virtual void revert() TITANIUM_NOEXCEPT override final;
		virtual void save(const std::vector<std::shared_ptr<Titanium::Contacts::Person>>& contacts) TITANIUM_NOEXCEPT override final;
		virtual void showContacts(const Titanium::Contacts::ShowContactsParams& params) TITANIUM_NOEXCEPT override final;
		virtual void requestAuthorization(JSObject& callback) TITANIUM_NOEXCEPT override final;
	};
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_CONTACTS_HPP_