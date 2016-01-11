/**
 * Titanium.Contacts.Group for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Contacts.hpp"
#include "TitaniumWindows/Contacts/Group.hpp"
#include "TitaniumWindows/Contacts/Person.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <memory>
#include <concrt.h>
#include <collection.h>

namespace TitaniumWindows
{
	namespace Contacts
	{
		using namespace Windows::Foundation::Collections;
		using namespace Windows::ApplicationModel::Contacts;

		Group::Group(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::Contacts::Group(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("Group::ctor Initialize");
		}

		void Group::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			// TODO Remove since we don't do anything extra?
			Titanium::Contacts::Group::postCallAsConstructor(js_context, arguments);
		}

#if defined(IS_WINDOWS_10)
		void Group::construct(Windows::ApplicationModel::Contacts::ContactList^ list)
		{
			contact_list__ = list;
		}
#endif

		void Group::JSExportInitialize() {
			JSExport<Group>::SetClassVersion(1);
			JSExport<Group>::SetParent(JSExport<Titanium::Contacts::Group>::Class());
		}

		void Group::add(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			auto list = get_writable_list();
			if (list) {
				// TODO Do we need to make this sync? i.e. wait for it to finish before we return? Seems like we shouldn't...
				// TODO What if we haven't saved the contact list yet?! We should make sure we saved it first!
				std::shared_ptr<TitaniumWindows::Contacts::Person> win_person = std::dynamic_pointer_cast<::TitaniumWindows::Contacts::Person>(person);
				list->SaveContactAsync(win_person->GetContact());
			}
#endif
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Person>> Group::members() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			// Windows 10+ API!
			if (contact_list__) {
				std::vector<std::shared_ptr<Titanium::Contacts::Person>> people;
				IVectorView<Contact^>^ view;
				auto reader = contact_list__->GetContactReader(); // is this available?
				concurrency::event event;
				concurrency::create_task(reader->ReadBatchAsync()).then([&view, &event](concurrency::task<Windows::ApplicationModel::Contacts::ContactBatch^> task) {
					try {
						const auto batch = task.get();
						view = batch->Contacts;
					}
					catch (...) {
						// TODO Log something here?
					}
					event.set();
				});
				event.wait();

				if (view) {
					const auto ctx = get_context();
					for (const auto contact : view) {
						people.push_back(TitaniumWindows::Contacts::contactToPerson(ctx, contact));
					}
				}

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
			auto list = get_writable_list();
			if (list) {
				std::shared_ptr<TitaniumWindows::Contacts::Person> win_person = std::dynamic_pointer_cast<::TitaniumWindows::Contacts::Person>(person);
				win_person->removeFromList(list);
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
				// FIXME What if the DisplayName is null? We can't return nullptr here...
				return TitaniumWindows::Utility::ConvertUTF8String(contact_list__->DisplayName);
			}
#endif
			return Titanium::Contacts::Group::get_name();
		}

		void Group::set_name(const std::string& name) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Group::set_name(name);
#if defined(IS_WINDOWS_10)
			// TODO Do we need to get a writable copy of contact list?
			auto list = get_writable_list();
			if (list) {
				list->DisplayName = TitaniumWindows::Utility::ConvertUTF8String(name);
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

		void Group::create()
		{
#if defined(IS_WINDOWS_10)
			// TODO Run this async and return some IAsyncAction or something we can wait for all of them to finish at a higher level?
			// FIXME Running into this issue: https://social.msdn.microsoft.com/Forums/sqlserver/en-US/1f06228a-1da1-440c-b706-59d26e39cbea/uwp-contactstorecreatecontactlistasync-fails?forum=wpdevelop
			// Basically looks like we can only create a _single_ ContactList?!
			// So we can create the "Default" one, but not a second one?
			const auto name = TitaniumWindows::Utility::ConvertUTF8String(get_name());

			concurrency::event event;
			concurrency::create_task(ContactManager::RequestStoreAsync(ContactStoreAccessType::AppContactsReadWrite), concurrency::task_continuation_context::use_arbitrary())
			.then([&name](ContactStore^ store) {
				return store->CreateContactListAsync(name, );
			}, concurrency::task_continuation_context::use_arbitrary())
			.then([this, &event](concurrency::task<ContactList^> task) {
				try {
					construct(task.get());
				}
				catch (Platform::AccessDeniedException^ ade) {
					TITANIUM_LOG_ERROR("Ti.Contacts.Group.create: Access denied:", ade->Message->Data());
				}
				catch (Platform::COMException^ ce) {
					TITANIUM_LOG_ERROR("Ti.Contacts.Group.create: ", ce->Message->Data());
				}
				catch (const std::exception& e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.Group.create: ", e.what());
				}
				catch (...) {
					// TODO Log something here?
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			if (contact_list__) {
				is_writable__ = true;
			}
#else
			TITANIUM_LOG_WARN("Group::create: Unimplemented");
#endif
		}

		void Group::removeList()
		{
#if defined(IS_WINDOWS_10)
			auto list = get_writable_list();
			if (!list) {
				return;
			}
			// Just delete it async, I don't think we _have_ to wait for it to finish here...
			list->DeleteAsync();
			is_writable__ = false;
#else
			TITANIUM_LOG_WARN("Group::removeList: Unimplemented");
#endif
		}

#if defined(IS_WINDOWS_10)
		ContactList^ Group::get_writable_list() {
			// we haven't created it yet...
			if (!contact_list__) {
				return nullptr;
			}
			// we already have a writable copy
			if (is_writable__) {
				return contact_list__;
			}

			// We grabbed the group via a read-only query, so let's look up a writable copy
			ContactList^ writable;
			concurrency::event event;
			concurrency::create_task(ContactManager::RequestStoreAsync(ContactStoreAccessType::AppContactsReadWrite), concurrency::task_continuation_context::use_arbitrary())
				.then([this](ContactStore^ store) {
				return store->GetContactListAsync(contact_list__->Id);
			}, concurrency::task_continuation_context::use_arbitrary())
				.then([&writable, &event](concurrency::task<ContactList^> task) {
				try {
					writable = task.get();
				}
				catch (Platform::AccessDeniedException^ ade) {
					TITANIUM_LOG_ERROR("Ti.Contacts.Group.removeList: Access denied:", ade->Message->Data());
				}
				catch (Platform::COMException^ ce) {
					TITANIUM_LOG_ERROR("Ti.Contacts.Group.removeList: ", ce->Message->Data());
				}
				catch (const std::exception& e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.Group.removeList: ", e.what());
				}
				catch (...) {
					// TODO Log something here?
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			if (writable) {
				contact_list__ = writable;
				is_writable__ = true;
			}

			return contact_list__;
		}
#endif
	}  // namespace Contacts
}  // namespace TitaniumWindows