/**
 * Titanium.Contacts for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "Titanium/ErrorResponse.hpp"
#include "Titanium/Contacts/ShowContactsParams.hpp"
#include "TitaniumWindows/Contacts.hpp"
#include "TitaniumWindows/Contacts/Group.hpp"
#include "TitaniumWindows/Contacts/Person.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"
#include <ppltasks.h>
#include <collection.h>
#include <concrt.h>

#define ENSURE_CONTACTSTORE(RESULT) \
  if (contactStore__ == nullptr) { \
    HAL::detail::ThrowRuntimeError("TitaniumWindows::Contact", "Call Ti.Contacts.requestContactsPermissions before accessing contacts."); \
    return RESULT; \
  } \

namespace TitaniumWindows
{

	using namespace Windows::Foundation::Collections;
	using namespace Windows::ApplicationModel::Contacts;

	ContactsModule::ContactsModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Titanium::ContactsModule(js_context, arguments)
	{
		TITANIUM_LOG_DEBUG("Contacts::ctor Initialize");
	}

	void ContactsModule::JSExportInitialize()
	{
		JSExport<ContactsModule>::SetClassVersion(1);
		JSExport<ContactsModule>::SetParent(JSExport<Titanium::ContactsModule>::Class());
	}

	std::vector<std::shared_ptr<Titanium::Contacts::Group>> ContactsModule::getAllGroups() TITANIUM_NOEXCEPT
	{
		return TitaniumWindows::Contacts::Group::getAllGroups(get_context());
	}

	std::vector<std::shared_ptr<Titanium::Contacts::Person>> ContactsModule::getAllPeople(const uint32_t& limit) TITANIUM_NOEXCEPT
	{
		std::vector<std::shared_ptr<Titanium::Contacts::Person>> result;
		ENSURE_CONTACTSTORE(result);
		try {
			IVectorView<Contact^>^ contacts;
			concurrency::event event;
			concurrency::create_task(contactStore__->FindContactsAsync(), concurrency::task_continuation_context::use_arbitrary())
			  .then([&contacts, &event] (concurrency::task<IVectorView<Contact^>^> task) {
				try {
					contacts = task.get();
				} catch (Platform::AccessDeniedException^ ade) {
					TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Access denied: ", ade->Message->Data());
				} catch (Platform::Exception^ e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: ", e->Message->Data());
				} catch (const std::exception& e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: ", e.what());
				} catch (...) {
					TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Unknown error");
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			if (contacts) {
				const auto ctx = get_context();
				for (auto contact : contacts) {
					result.push_back(TitaniumWindows::Contacts::contactToPerson(ctx, contact));
				}
			}

		} catch (Platform::AccessDeniedException^ ade) {
			TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Access denied: ", ade->Message->Data());
		} catch (const std::exception& e) {
			TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: ", e.what());
		} catch (...) {
			TITANIUM_LOG_ERROR("Ti.Contacts.getAllPeople: Unknown error");
		}
		return result;
	}

	std::shared_ptr<Titanium::Contacts::Group> ContactsModule::getGroupByIdentifier(const std::string& id) TITANIUM_NOEXCEPT
	{
		return TitaniumWindows::Contacts::Group::getGroupByIdentifier(id, get_context());
	}

	std::vector<std::shared_ptr<Titanium::Contacts::Person>> ContactsModule::getPeopleWithName(const std::string& name) TITANIUM_NOEXCEPT
	{
		std::vector<std::shared_ptr<Titanium::Contacts::Person>> result;
		ENSURE_CONTACTSTORE(result);

		IVectorView<Contact^>^ contacts;
		const auto query = TitaniumWindows::Utility::ConvertUTF8String(name);
		concurrency::event event;
		concurrency::create_task(contactStore__->FindContactsAsync(query), concurrency::task_continuation_context::use_arbitrary())
		.then([&contacts, &event](concurrency::task<IVectorView<Contact^>^> task) {
			try {
				contacts = task.get();
			}
			catch (Platform::AccessDeniedException^ ade) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPeopleWithName: Access denied:", ade->Message->Data());
			}
			catch (Platform::Exception^ ce) {
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

		if (contacts) {
			const auto ctx = get_context();
			for (const auto contact : contacts) {
				result.push_back(TitaniumWindows::Contacts::contactToPerson(ctx, contact));
			}
		}
		return result;
	}

	std::shared_ptr<Titanium::Contacts::Person> ContactsModule::getPersonByIdentifier(const std::string& id) TITANIUM_NOEXCEPT
	{
		std::shared_ptr<Titanium::Contacts::Person> result = nullptr;
		ENSURE_CONTACTSTORE(result);
		Contact^ contact;
		const auto identifier = Utility::ConvertUTF8String(id);
		concurrency::event event;
		concurrency::create_task(contactStore__->GetContactAsync(identifier), concurrency::task_continuation_context::use_arbitrary())
		.then([&contact, &event](concurrency::task<Contact^> task) {
			try {
				contact = task.get();
			}
			catch (Platform::AccessDeniedException^ ade) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPersonByIdentifier: Access denied:", ade->Message->Data());
			}
			catch (Platform::InvalidArgumentException^ iae) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPersonByIdentifier: Invalid identifier: ", iae->Message->Data());
			}
			catch (Platform::Exception^ ce) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPersonByIdentifier: ", ce->Message->Data());
			}
			catch (const std::exception& e) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getPersonByIdentifier: ", e.what());
			}
			catch (...) {
				// TODO Log something here?
			}
			event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();

		if (contact) {
			const auto ctx = get_context();
			result = TitaniumWindows::Contacts::contactToPerson(ctx, contact);
		}
		return result;
	}

	JSValue ContactsModule::js_createGroup(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		auto result = Titanium::ContactsModule::js_createGroup(arguments, this_object);
		// record group we'll need to save later!
		if (result.IsObject()) {
			auto object = static_cast<JSObject>(result);
			auto group_ptr = object.GetPrivate<TitaniumWindows::Contacts::Group>();
			to_create.push_back(group_ptr);
		}
		return result;
	}

#if defined(IS_WINDOWS_10)
	// TODO Maybe we should store this in a field so we don't have to look it up every time?
	ContactList^ ContactsModule::getDefaultContactList()
	{
		// Grab the app's contact list
		ContactList^ default_list;
		ContactStore^ contact_store;

		ENSURE_CONTACTSTORE(default_list);

		// Search to see if it exists
		concurrency::event event;
		concurrency::create_task(contactStore__->FindContactListsAsync(), concurrency::task_continuation_context::use_arbitrary())
			.then([&default_list, &event](concurrency::task<IVectorView<ContactList^>^> task) {
			try {
				const auto lists = task.get();
				for (const auto list : lists) {
					if (list->DisplayName == "Default") {
						// This is the list we'll add everyone to
						default_list = list;
						break;
					}
				}
			}
			catch (Platform::AccessDeniedException^ ade) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getAllGroups: Access denied: ", ade->Message->Data());
			}
			catch (Platform::Exception^ e) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getAllGroups: ", e->Message->Data());
			}
			catch (const std::exception& e) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getAllGroups: ", e.what());
			}
			catch (...) {
				TITANIUM_LOG_ERROR("Ti.Contacts.getAllGroups: Unknown error");
			}
			event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();

		// if we get the default list or couldn't get the store (access denied?) return what we have now
		if (default_list || !contact_store) {
			return default_list;
		}

		// Must create the default contact list
		concurrency::event create_event;
		concurrency::create_task(contact_store->CreateContactListAsync("Default"), concurrency::task_continuation_context::use_arbitrary())
		.then([&default_list, &create_event](concurrency::task<ContactList^> task) {
			try {
				default_list = task.get();
			}
			catch (Platform::AccessDeniedException^ ade) {
				TITANIUM_LOG_ERROR("Ti.Contacts.Group.create: Access denied:", ade->Message->Data());
			}
			catch (Platform::Exception^ ce) {
				TITANIUM_LOG_ERROR("Ti.Contacts.Group.create: ", ce->Message->Data());
			}
			catch (const std::exception& e) {
				TITANIUM_LOG_ERROR("Ti.Contacts.Group.create: ", e.what());
			}
			catch (...) {
				// TODO Log something here?
			}
			create_event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		create_event.wait();

		return default_list;
	}
#endif

	JSValue ContactsModule::js_createPerson(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		auto result = Titanium::ContactsModule::js_createPerson(arguments, this_object);
#if defined(IS_WINDOWS_10)
		if (result.IsObject()) {
			// save first so we know any pending groups are created...
			// FIXME move save call up to TitaniumKit level!
			std::vector<std::shared_ptr<Titanium::Contacts::Person>> contacts;
			save(contacts);

			// Add the person to the app's single contact list
			auto person_object = static_cast<JSObject>(result);
			auto person = person_object.GetPrivate<TitaniumWindows::Contacts::Person>();
			auto list = getDefaultContactList();
			auto contact = person->GetContact();
			// sync save
			concurrency::event event;
			concurrency::create_task(list->SaveContactAsync(contact), concurrency::task_continuation_context::use_arbitrary())
				.then([&event](concurrency::task<void> task) {
				try {
					task.get();
				}
				catch (Platform::AccessDeniedException^ ade) {
					TITANIUM_LOG_ERROR("Ti.Contacts.createPerson: Access denied:", ade->Message->Data());
				}
				catch (Platform::Exception^ ce) {
					TITANIUM_LOG_ERROR("Ti.Contacts.createPerson: ", ce->Message->Data());
				}
				catch (const std::exception& e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.createPerson: ", e.what());
				}
				catch (...) {
					// TODO Log something here?
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
		}
#endif
		return result;
	}

	void ContactsModule::removeGroup(const std::shared_ptr<Titanium::Contacts::Group>& group) TITANIUM_NOEXCEPT
	{
		std::shared_ptr<TitaniumWindows::Contacts::Group> win_group = std::dynamic_pointer_cast<TitaniumWindows::Contacts::Group>(group);
		to_remove.push_back(win_group);
	}

	void ContactsModule::removePerson(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
	{
		if (contactStore__ == nullptr) {
				HAL::detail::ThrowRuntimeError("TitaniumWindows::Contact", "Call Ti.Contacts.requestContactsPermissions before accessing contacts.");
				return;
		}

		std::shared_ptr<TitaniumWindows::Contacts::Person> win_person = std::dynamic_pointer_cast<TitaniumWindows::Contacts::Person>(person);
		win_person->remove(contactStore__);
	}

	void ContactsModule::revert() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Ti.Contacts.revert is not implemented yet");
	}

	void ContactsModule::save(const std::vector<std::shared_ptr<Titanium::Contacts::Person>>& contacts) TITANIUM_NOEXCEPT
	{
		// Commit any created groups, remove any removed groups!
		for (auto group : to_create) {
			group->create();
		}
		to_create.clear();
		// Remove any pending!
		for (auto group : to_remove) {
			group->removeList();
		}
		to_remove.clear();
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
						auto person = getPersonByIdentifier(TitaniumWindows::Utility::ConvertUTF8String(contact->Id));
						params.callbacks.onselectedPerson(person);
					}
				} catch (Platform::Exception^ ce) {
					TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", ce->Message->Data());
				} catch (const std::exception& e) {
					TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", e.what());
				} catch (...) {
					TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: Unknown error in selecting a contact.");
				}
			});
		} catch (Platform::Exception^ ce) {
			TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", ce->Message->Data());
		} catch (const std::exception& e) {
			TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: ", e.what());
		} catch (...) {
			TITANIUM_LOG_ERROR("Ti.Contacts.showContacts: Unknown error in selecting a contact.");
		}
	}

	void ContactsModule::requestContactsPermissions(JSObject& callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_EXCEPTION_CATCH_START{
			if (Titanium::Contacts::AUTHORIZATION::UNKNOWN == contactsAuthorization__) {
				concurrency::create_task(ContactManager::RequestStoreAsync(ContactStoreAccessType::AllContactsReadOnly))
				.then([callback, this](concurrency::task<ContactStore^> task) {
					Titanium::ErrorResponse e;
					e.code = 0;
					e.error = "";
					try {
						contactStore__ = task.get();
						contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::AUTHORIZED;
					} catch (Platform::AccessDeniedException^ ade) {
						e.code = ade->HResult;
						e.error = TitaniumWindows::Utility::ConvertUTF8String(ade->Message);
						contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::DENIED;
						TITANIUM_LOG_ERROR("Access denied to contacts");
					} catch (const std::exception& ex) {
						e.error = ex.what();
						contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::DENIED;
						TITANIUM_LOG_ERROR("Access denied to contacts");
					} catch (...) {
						contactsAuthorization__ = Titanium::Contacts::AUTHORIZATION::DENIED;
						TITANIUM_LOG_ERROR("Unable to get contact store");
					}

					if (Titanium::Contacts::AUTHORIZATION::DENIED == contactsAuthorization__) {
						e.success = false;
					}

					// fire the callback in main thread
					const std::vector<JSValue> args = {
						ErrorResponse_to_js(callback.get_context(), e)
					};
					static_cast<JSObject>(callback)(args, get_object());

				});
			} else {
				Titanium::ErrorResponse e;
				e.code = 0;
				e.error = "";
				const std::vector<JSValue> args = {
					ErrorResponse_to_js(callback.get_context(), e)
				};
				static_cast<JSObject>(callback)(args, get_object());
			}

		} TITANIUMWINDOWS_EXCEPTION_CATCH_END
	}

}  // namespace TitaniumWindows
