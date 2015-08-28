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

namespace TitaniumWindows
{
	namespace Contacts
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.Contacts.Person implementation for Windows.
		*/
		class TITANIUMWINDOWS_TI_EXPORT Person final : public Titanium::Contacts::Person, public JSExport<Person>
		{

		public:
			
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

			void construct(Windows::ApplicationModel::Contacts::Contact^ contact);
			Windows::ApplicationModel::Contacts::Contact^ GetContact();

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
			virtual JSValue get_id() const TITANIUM_NOEXCEPT override final;
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

			void remove();
#if (WINVER >= 0x0A00)
// Windows 10+ API
			void removeFromList(Windows::ApplicationModel::Contacts::ContactList^ list);
#endif
		private:
			Windows::ApplicationModel::Contacts::ContactAddress^ Person::createAddress(const Titanium::Contacts::Address&, Windows::ApplicationModel::Contacts::ContactAddressKind) TITANIUM_NOEXCEPT;
			Windows::ApplicationModel::Contacts::ContactDate^ Person::createDate(const std::string&, Windows::ApplicationModel::Contacts::ContactDateKind) TITANIUM_NOEXCEPT;
			Windows::ApplicationModel::Contacts::ContactEmail^ Person::createEmail(const std::string&, Windows::ApplicationModel::Contacts::ContactEmailKind) TITANIUM_NOEXCEPT;
			Windows::ApplicationModel::Contacts::ContactWebsite^ Person::createWebsite(const std::string&, const std::string&) TITANIUM_NOEXCEPT;
			Windows::ApplicationModel::Contacts::ContactPhone^ Person::createPhone(const std::string&, const std::string&, Windows::ApplicationModel::Contacts::ContactPhoneKind) TITANIUM_NOEXCEPT;
			Windows::ApplicationModel::Contacts::ContactConnectedServiceAccount^ Person::createInstantMessage(const Titanium::Contacts::InstantMessage&) TITANIUM_NOEXCEPT;
			Windows::ApplicationModel::Contacts::ContactSignificantOther^ Person::createSignificantOther(const std::string&, const std::string&) TITANIUM_NOEXCEPT;

			Windows::ApplicationModel::Contacts::Contact^ contact__;
		};
	}  // namespace Contacts
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_PERSON_HPP_