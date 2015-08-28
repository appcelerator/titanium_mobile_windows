/**
 * Titanium.Contacts for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/ErrorResponse.hpp"
#include "Titanium/Contacts/ShowContactsParams.hpp"
#include "TitaniumWindows/Contacts.hpp"
#include "TitaniumWindows/Contacts/Group.hpp"
#include "TitaniumWindows/Contacts/Person.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <ppltasks.h>
#include <collection.h>

namespace TitaniumWindows
{

	using namespace Windows::Foundation::Collections;
	using namespace Windows::ApplicationModel::Contacts;

	ContactsModule::ContactsModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Titanium::ContactsModule(js_context, arguments)
	{
		TITANIUM_LOG_DEBUG("Contacts::ctor Initialize");
	}

	void ContactsModule::JSExportInitialize() {
		JSExport<ContactsModule>::SetClassVersion(1);
		JSExport<ContactsModule>::SetParent(JSExport<Titanium::ContactsModule>::Class());
	}

#if (WINVER >= 0x0A00)
	// Windows 10+ API!
	std::shared_ptr<Titanium::Contacts::Group> listToGroup(const JSContext& context, Windows::ApplicationModel::Contacts::ContactList^ contact_list) TITANIUM_NOEXCEPT
	{
		// convert the contact_list to a Group object!
		auto Group = context.CreateObject(JSExport<TitaniumWindows::Contacts::Group>::Class());
		auto group = Group.CallAsConstructor();
		auto group_ptr = group.GetPrivate<TitaniumWindows::Contacts::Group>();
		group_ptr->construct(contact_list);

		return group.GetPrivate<Titanium::Contacts::Group>();
	}
#endif

	std::shared_ptr<Titanium::Contacts::Person> contactToPerson(const JSContext& context, Windows::ApplicationModel::Contacts::Contact^ contact) TITANIUM_NOEXCEPT
	{
		auto Person = context.CreateObject(JSExport<TitaniumWindows::Contacts::Person>::Class());
		auto person = Person.CallAsConstructor();
		auto person_ptr = person.GetPrivate<TitaniumWindows::Contacts::Person>();
		person_ptr->construct(contact);

		return person.GetPrivate<Titanium::Contacts::Person>();
	}

	std::vector<std::shared_ptr<Titanium::Contacts::Group>> ContactsModule::getAllGroups() TITANIUM_NOEXCEPT
	{
#if (WINVER >= 0x0A00)
		// Windows 10+ API!
		std::vector<std::shared_ptr<Titanium::Contacts::Group>> result;
		// FIXME Should we grab the contact store during requestAuthorization?
		concurrency::event event;
		create_task(ContactManager::RequestStoreAsync()).then([](ContactStore^ store) {
			return store->FindContactListsAsync(id);
		}, concurrency::task_continuation_context::use_arbitrary())
		.then([&result, &event] (task<IVectorView<ContactList^>^> task) {
			try {
				const auto lists = task.get();
				for (const auto list : lists) {
					result.push_back(listToGroup(list));
				}
			}
			catch (...) {
				// TODO Log something here?
			}
			event.set();
		});
		event.wait();

		return result;
#else
		TITANIUM_LOG_WARN("Ti.Contacts.getAllGroups: Not supported in Windows 8.1");
		return std::vector<std::shared_ptr<Titanium::Contacts::Group>>();
#endif
	}

	std::vector<std::shared_ptr<Titanium::Contacts::Person>> ContactsModule::getAllPeople(const uint32_t& limit) TITANIUM_NOEXCEPT
	{
		std::vector<std::shared_ptr<Titanium::Contacts::Person>> result;
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) && (WINVER >= 0x0A00)
		// FIXME Should we grab the contact store during requestAuthorization?
		try {
			const auto ctx = get_context();
			concurrency::event event;
			concurrency::create_task(ContactManager::RequestStoreAsync(), concurrency::task_continuation_context::use_arbitrary())
			.then([](ContactStore^ store) {
				return store->FindContactsAsync();
			}, concurrency::task_continuation_context::use_arbitrary())
			.then([&result, &event, &ctx] (concurrency::task<IVectorView<Contact^>^> task) {
				try {
					const auto contacts = task.get();
					for (auto contact : contacts) {
						result.push_back(contactToPerson(ctx, contact));
					}
				}
				catch (Platform::AccessDeniedException^ ade) {
					TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Access denied: ", ade->Message->Data());
				}
				catch (Platform::COMException^ e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: ", e->Message->Data());
				}
				catch (const std::exception& e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: ", e.what());
				}
				catch (...) {
					TITANIUM_LOG_ERROR("i.Contacts.getAllPeople: Unknown error");
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
		}
		catch (Platform::AccessDeniedException^ ade) {
			TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Access denied: ", ade->Message->Data());
		}
		catch (const std::exception& e) {
			TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: ", e.what());
		}
		catch (...) {
			TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Unknown error");
		}
#else
		TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Contact access not allowed on Windows 8.1 Store/Desktop apps");
#endif
		return result;
	}

	std::shared_ptr<Titanium::Contacts::Group> ContactsModule::getGroupByIdentifier(const JSValue& id) TITANIUM_NOEXCEPT
	{
#if (WINVER >= 0x0A00)
		// Windows 10+ API!
		TITANIUM_ASSERT(id.IsString());
		const auto identifier = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(id));
		const autp ctx = get_context();
		std::shared_ptr<Titanium::Contacts::Group> result = nullptr;
		// FIXME Should we grab the contact store during requestAuthorization?

		concurrency::event event;
		concurrency::create_task(ContactManager::RequestStoreAsync(), concurrency::task_continuation_context::use_arbitrary())
		.then([&identifier](ContactStore^ store) {
			return store->GetContactListAsync(identifier);
		}, concurrency::task_continuation_context::use_arbitrary())
		.then([&result, &event, &ctx] (concurrency::task<ContactList^> task) {
			try {
				result = listToGroup(ctx, task.get());
			}
			catch (...) {
				// TODO Log something here?
			}
			event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();

		return result;
#else
		TITANIUM_LOG_WARN("Ti.Contacts.getGroupByIdentifier: Not supported in Windows 8.1");
		return nullptr;
#endif
	}

	std::vector<std::shared_ptr<Titanium::Contacts::Person>> ContactsModule::getPeopleWithName(const std::string& name) TITANIUM_NOEXCEPT
	{
		std::vector<std::shared_ptr<Titanium::Contacts::Person>> result;
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) && (WINVER >= 0x0A00)
		// FIXME Should we grab the contact store during requestAuthorization?
		const auto ctx = get_context();
		const auto query = TitaniumWindows::Utility::ConvertUTF8String(name);
		concurrency::event event;
		concurrency::create_task(ContactManager::RequestStoreAsync(), concurrency::task_continuation_context::use_arbitrary())
		.then([&query](ContactStore^ store) {
			return store->FindContactsAsync(query);
		}, concurrency::task_continuation_context::use_arbitrary())
		.then([&result, &event, &ctx](concurrency::task<IVectorView<Contact^>^> task) {
			try {
				const auto contacts = task.get();
				for (const auto contact : contacts) {
					result.push_back(contactToPerson(ctx, contact));
				}
			}
			catch (Platform::AccessDeniedException^ ade) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPeopleWithName: Access denied:", ade->Message->Data());
			}
			catch (Platform::COMException^ ce) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPeopleWithName: ", ce->Message->Data());
			}
			catch (const std::exception& e) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPeopleWithName: ", e.what());
			}
			catch (...) {
				// TODO Log something here?
			}
			event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();
#else
		TITANIUM_LOG_ERROR("Ti.Contacts.getPeopleWithName: Contact access not allowed on Windows 8.1 Store/Desktop apps");
#endif
		return result;
	}

	std::shared_ptr<Titanium::Contacts::Person> ContactsModule::getPersonByIdentifier(const JSValue& id) TITANIUM_NOEXCEPT
	{
		std::shared_ptr<Titanium::Contacts::Person> result = nullptr;
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) && (WINVER >= 0x0A00)
		// FIXME Should we grab the contact store during requestAuthorization?
		TITANIUM_ASSERT(id.IsString());
		const auto identifier = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(id));
		const auto ctx = get_context();
		concurrency::event event;
		concurrency::create_task(ContactManager::RequestStoreAsync(), concurrency::task_continuation_context::use_arbitrary())
		.then([&identifier](ContactStore^ store) {
			return store->GetContactAsync(identifier);
		}, concurrency::task_continuation_context::use_arbitrary())
		.then([&result, &event, &ctx](concurrency::task<Contact^> task) {
			try {
				result = contactToPerson(ctx, task.get());
			}
			catch (...) {
				// TODO Log something here?
			}
			event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();
#else
		TITANIUM_LOG_ERROR("Ti.Contacts.getPersonByIdentifier: Contact access not allowed on Windows 8.1 Store/Desktop apps");
#endif
		return result;
	}

	void ContactsModule::removeGroup(const std::shared_ptr<Titanium::Contacts::Group>& group) TITANIUM_NOEXCEPT
	{
		std::shared_ptr<TitaniumWindows::Contacts::Group> win_group = std::dynamic_pointer_cast<TitaniumWindows::Contacts::Group>(group);
		win_group->removeList();
	}

	void ContactsModule::removePerson(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
	{
		std::shared_ptr<TitaniumWindows::Contacts::Person> win_person = std::dynamic_pointer_cast<TitaniumWindows::Contacts::Person>(person);
		win_person->remove();
	}

	void ContactsModule::revert() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Ti.Contacts.revert is not implemented yet");
	}

	void ContactsModule::save(const std::vector<std::shared_ptr<Titanium::Contacts::Person>>& contacts) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Ti.Contacts.save is not implemented yet");
	}

	void ContactsModule::showContacts(const Titanium::Contacts::ShowContactsParams& params) TITANIUM_NOEXCEPT
	{
		auto contact_picker = ref new ContactPicker();
		// TODO Use params.fields to narrow fields! Do we narrow based on fields array, or which callback user supplied (selectedPerson vs selectedProperty)?
		//contact_picker->SelectionMode = ContactSelectionMode::Fields;
		contact_picker->DesiredFieldsWithContactFieldType->Append(ContactFieldType::PhoneNumber); // If we don't set desired fields, we get runtime exception!
		try {
			concurrency::create_task(contact_picker->PickContactAsync())
			.then([params, this](Contact^ contact) {
				try {
					if (contact == nullptr) {
						params.callbacks.oncancel();
					} else {
						// Look up the contact by id so we get all their fields and not just the phone number as we specified above
						// This is a workaround for needing to specify one field for Phone.
						auto person = getPersonByIdentifier(params.callbacks.selectedPerson.get_context().CreateString(TitaniumWindows::Utility::ConvertUTF8String(contact->Id)));
						params.callbacks.onselectedPerson(person);
					}
				}
				catch (Platform::COMException^ ce) {
					TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", ce->Message->Data());
				}
				catch (const std::exception& e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", e.what());
				}
				catch (...) {
					TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: Unknown error in selecting a contact.");
				}
			});
		}
		catch (Platform::COMException^ ce) {
			TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", ce->Message->Data());
		}
		catch (const std::exception& e) {
			TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", e.what());
		}
		catch (...) {
			TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: Unknown error in selecting a contact.");
		}
	}

	void ContactsModule::requestAuthorization(JSObject& callback) TITANIUM_NOEXCEPT
	{
		Titanium::ErrorResponse e;
		e.code = 0;
		e.error = "";
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) && (WINVER >= 0x0A00)
		if (Titanium::Contacts::AUTHORIZATION::UNKNOWN == contactsAuthorization__) {
			concurrency::event event;
			concurrency::create_task(ContactManager::RequestStoreAsync(), concurrency::task_continuation_context::use_arbitrary())
			.then([&callback, &event, &e, this](concurrency::task<ContactStore^> task) {
				try {
					task.get(); // TODO Set a field to hold the store for re-use in the other methods?
					contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::AUTHORIZED;
				}
				catch (Platform::AccessDeniedException^ ade) {
					e.code = ade->HResult;
					e.error = TitaniumWindows::Utility::ConvertUTF8String(ade->Message);
					contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::DENIED;
					TITANIUM_LOG_ERROR("Access denied to contacts");
				}
				catch (const std::exception& ex) {
					e.error = ex.what();
					contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::DENIED;
					TITANIUM_LOG_ERROR("Access denied to contacts");
				}
				catch (...) {
					contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::DENIED;
					TITANIUM_LOG_ERROR("Unable to get contact store");
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
		}
#else
		contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::RESTRICTED;
		e.error = "Access denied to contacts: Contact query/lookup not allowed on Windows 8.1 Store/Desktop apps. You can still call showContacts() to pick a contact.";
#endif

		if (Titanium::Contacts::AUTHORIZATION::DENIED == contactsAuthorization__) {
			e.success = false;
		}

		// fire the callback in main thread
		const std::vector<JSValue> args = {
			ErrorResponse_to_js(callback.get_context(), e)
		};
		callback(args, get_object());
	}

}  // namespace TitaniumWindows