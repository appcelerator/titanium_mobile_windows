/**
 * Titanium.Contacts.Group for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Contacts/Group.hpp"
#include "TitaniumWindows/Contacts/Person.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <memory>
#include <concrt.h>

namespace TitaniumWindows
{
	namespace Contacts
	{
		Group::Group(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::Contacts::Group(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("Group::ctor Initialize");
		}

		void Group::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::Contacts::Group::postCallAsConstructor(js_context, arguments);
		}

#if defined(IS_WINDOWS_10)
		void Group::construct(Windows::ApplicationModel::Contacts::ContactList^ list)
		{
			contact_list__ = list;
			// TODO Set properties like name, identifier, etc!
		}
#endif

		void Group::JSExportInitialize() {
			JSExport<Group>::SetClassVersion(1);
			JSExport<Group>::SetParent(JSExport<Titanium::Contacts::Group>::Class());
		}

		void Group::add(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			if (contact_list__) {
				// TODO Do we need to make this sync? i.e. wait for it to finish before we return? Seems like we shouldn't...
				std::shared_ptr<TitaniumWindows::Contacts::Person> win_person = std::dynamic_pointer_cast<::TitaniumWindows::Contacts::Person>(person);
				contact_list__->SaveContactAsync(win_person->GetContact());
			}
#endif
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Person>> Group::members() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			// Windows 10+ API!
			if (contact_list__) {
				std::vector<std::shared_ptr<Titanium::Contacts::Person>> people;
				auto reader = contact_list__->GetContactReader(); // is this available?
				concurrency::event event;
				concurrency::create_task(reader->ReadBatchAsync()).then([&people, &event](concurrency::task<Windows::ApplicationModel::Contacts::ContactBatch^> task) {
					try {
						const auto batch = task.get();
						const auto view = batch->Contacts;
						//for (const auto contact : view) {
							// TODO Turn the contact into a Person like we do in Contacts.cpp!
							//people.push_back();
						//}
					}
					catch (...) {
						// TODO Log something here?
					}
					event.set();
				});
				event.wait();
				return people;
			}
#else
			TITANIUM_LOG_WARN("Group::members: Unimplemented");
#endif
			return std::vector<std::shared_ptr<Titanium::Contacts::Person>>();
		}

		void Group::remove(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			// Windows 10+ API!
			if (contact_list__) {
				std::shared_ptr<TitaniumWindows::Contacts::Person> win_person = std::dynamic_pointer_cast<::TitaniumWindows::Contacts::Person>(person);
				win_person->removeFromList(contact_list__);
			}
#else
			TITANIUM_LOG_WARN("Group::remove: Unimplemented");
#endif
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Person>> Group::sortedMembers(const Titanium::Contacts::SORT& sortBy) TITANIUM_NOEXCEPT
		{
			// See https://msdn.microsoft.com/en-us/library/windows/apps/windows.applicationmodel.contacts.contactnameorder.aspx
			// https://msdn.microsoft.com/en-us/library/windows/apps/windows.applicationmodel.contacts.contactmanager.systemsortorder.aspx
			TITANIUM_LOG_WARN("Group::sortedMembers: Unimplemented");
			return std::vector<std::shared_ptr<Titanium::Contacts::Person>>();
		}

		JSValue Group::get_identifier() const TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			if (contact_list__) {
				return get_context().CreateString(TitaniumWindows::Utility::ConvertUTF8String(contact_list__->Id));
			}
#endif
			return get_context().CreateNull();
		}

		std::string Group::get_name() const TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			if (contact_list__) {
				return TitaniumWindows::Utility::ConvertUTF8String(contact_list__->DisplayName);
			}
#endif
			return Titanium::Contacts::Group::get_name();
		}

		void Group::set_name(const std::string& name) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Group::set_name(name);
#if defined(IS_WINDOWS_10)
			if (contact_list__) {
				contact_list__->DisplayName = TitaniumWindows::Utility::ConvertUTF8String(name);
			}
#else
			TITANIUM_LOG_WARN("Group::set_name: Unimplemented");
#endif
		}

		void Group::set_recordId(const uint32_t& recordId) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Group::set_recordId(recordId);
			TITANIUM_LOG_WARN("Group::recordId property is read-only");
		}

		void Group::removeList()
		{
#if defined(IS_WINDOWS_10)
			// Do we need to make this sync? I don't think we do...
			if (contact_list__) {
				contact_list__->DeleteAsync();
			}
#else
			TITANIUM_LOG_WARN("Group::removeList: Unimplemented");
#endif
		}
	}  // namespace Contacts
}  // namespace TitaniumWindows