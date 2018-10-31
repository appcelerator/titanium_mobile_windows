/**
 * Titanium.Contacts.Person for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_PERSON_HPP_
#define _TITANIUMWINDOWS_PERSON_HPP_

#include "TitaniumWindows_Ti_EXPORT.h"
#include "Titanium/Contacts/Person.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <sdkddkver.h>

namespace TitaniumWindows
{
	namespace Contacts
	{
		using namespace HAL;
		using namespace Windows::ApplicationModel::Contacts;

		/*!
		  @class Person
		  @ingroup Titanium.Contacts.Person

		  @discussion This is the Titanium.Contacts.Person implementation for Windows.
		*/
		class TITANIUMWINDOWS_TI_EXPORT Person final : public Titanium::Contacts::Person, public JSExport<Person>
		{

		public:
			
			TITANIUM_PROPERTY_UNIMPLEMENTED(alternateBirthday);
			TITANIUM_PROPERTY_UNIMPLEMENTED(created);
			TITANIUM_PROPERTY_UNIMPLEMENTED(id);
			TITANIUM_PROPERTY_UNIMPLEMENTED(image);
			TITANIUM_PROPERTY_UNIMPLEMENTED(kind);
			TITANIUM_PROPERTY_UNIMPLEMENTED(middlePhonetic);
			TITANIUM_PROPERTY_UNIMPLEMENTED(modified);
			TITANIUM_PROPERTY_UNIMPLEMENTED(recordId);

			Person(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Person()                = default;
			Person(const Person&)            = default;
			Person& operator=(const Person&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Person(Person&&)                 = default;
			Person& operator=(Person&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			void construct(Contact^ contact);

			virtual Titanium::Contacts::Addresses get_address() const TITANIUM_NOEXCEPT override final;
			virtual void set_address(const Titanium::Contacts::Addresses&) TITANIUM_NOEXCEPT override final;
			virtual void set_alternateBirthday(const Titanium::Contacts::AlternateBirthday&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_birthday() const TITANIUM_NOEXCEPT override final;
			virtual void set_birthday(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual Titanium::Contacts::Dates get_date() const TITANIUM_NOEXCEPT override final;
			virtual void set_date(const Titanium::Contacts::Dates&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_department() const TITANIUM_NOEXCEPT override final;
			virtual void set_department(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual Titanium::Contacts::Emails get_email() const TITANIUM_NOEXCEPT override final;
			virtual void set_email(const Titanium::Contacts::Emails&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_firstName() const TITANIUM_NOEXCEPT override final;
			virtual void set_firstName(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_firstPhonetic() const TITANIUM_NOEXCEPT override final;
			virtual void set_firstPhonetic(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_fullName() const TITANIUM_NOEXCEPT override final;
			virtual void set_fullName(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_identifier() const TITANIUM_NOEXCEPT override final;
			virtual void set_image(const std::shared_ptr<::Titanium::Blob>&) TITANIUM_NOEXCEPT override final;
			virtual Titanium::Contacts::InstantMessages get_instantMessage() const TITANIUM_NOEXCEPT override final;
			virtual void set_instantMessage(const Titanium::Contacts::InstantMessages&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_jobTitle() const TITANIUM_NOEXCEPT override final;
			virtual void set_jobTitle(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual void set_kind(const Titanium::Contacts::KIND&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_lastName() const TITANIUM_NOEXCEPT override final;
			virtual void set_lastName(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_lastPhonetic() const TITANIUM_NOEXCEPT override final;
			virtual void set_lastPhonetic(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_middleName() const TITANIUM_NOEXCEPT override final;
			virtual void set_middleName(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual void set_middlePhonetic(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_nickname() const TITANIUM_NOEXCEPT override final;
			virtual void set_nickname(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_note() const TITANIUM_NOEXCEPT override final;
			virtual void set_note(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_organization() const TITANIUM_NOEXCEPT override final;
			virtual void set_organization(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual Titanium::Contacts::Phones get_phone() const TITANIUM_NOEXCEPT override final;
			virtual void set_phone(const Titanium::Contacts::Phones&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_prefix() const TITANIUM_NOEXCEPT override final;
			virtual void set_prefix(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual Titanium::Contacts::RelatedNames get_relatedNames() const TITANIUM_NOEXCEPT override final;
			virtual void set_relatedNames(const Titanium::Contacts::RelatedNames&) TITANIUM_NOEXCEPT override final;
			virtual Titanium::Contacts::InstantMessages get_socialProfile() const TITANIUM_NOEXCEPT override final;
			virtual void set_socialProfile(const Titanium::Contacts::InstantMessages&) TITANIUM_NOEXCEPT override final;
			virtual std::string get_suffix() const TITANIUM_NOEXCEPT override final;
			virtual void set_suffix(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual Titanium::Contacts::Urls get_url() const TITANIUM_NOEXCEPT override final;
			virtual void set_url(const Titanium::Contacts::Urls&) TITANIUM_NOEXCEPT override final;

			void remove(Windows::ApplicationModel::Contacts::ContactStore^);
#if defined(IS_WINDOWS_10)
			Contact^ GetContact() const;
#endif
		private:
			ContactAddress^ Person::createAddress(const Titanium::Contacts::Address&, ContactAddressKind) TITANIUM_NOEXCEPT;
			ContactDate^ Person::createDate(const std::string&, ContactDateKind) TITANIUM_NOEXCEPT;
			ContactEmail^ Person::createEmail(const std::string&, ContactEmailKind) TITANIUM_NOEXCEPT;
			ContactWebsite^ Person::createWebsite(const std::string&, const std::string&) TITANIUM_NOEXCEPT;
			ContactPhone^ Person::createPhone(const std::string&, const std::string&, ContactPhoneKind) TITANIUM_NOEXCEPT;
			ContactConnectedServiceAccount^ Person::createInstantMessage(const Titanium::Contacts::InstantMessage&) TITANIUM_NOEXCEPT;
			ContactSignificantOther^ Person::createSignificantOther(const std::string&, const std::string&) TITANIUM_NOEXCEPT;

			Contact^ contact__{ nullptr };
		};

		static std::shared_ptr<Titanium::Contacts::Person> contactToPerson(const JSContext& context, Contact^ contact) TITANIUM_NOEXCEPT
		{
			auto Person = context.CreateObject(JSExport<TitaniumWindows::Contacts::Person>::Class());
			auto person = Person.CallAsConstructor();
			auto person_ptr = person.GetPrivate<TitaniumWindows::Contacts::Person>();
			person_ptr->construct(contact);

			return person.GetPrivate<Titanium::Contacts::Person>();
		}
	}  // namespace Contacts
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_PERSON_HPP_
