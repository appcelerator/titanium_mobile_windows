/**
 * Titanium.Contacts.Person for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Contacts/Person.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "Titanium/Blob.hpp"
#include <windows.h>
#include <ppltasks.h>
#include <concrt.h>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

#define CONTACT_VOID_GUARD if (contact__ == nullptr) return;
#define CONTACT_STRING_GUARD if (contact__ == nullptr) return "";
#define CONTACT_VALUE_GUARD(VALUE) if (contact__ == nullptr) return VALUE;

namespace TitaniumWindows
{
	namespace Contacts
	{

		using namespace Windows::ApplicationModel::Contacts;

		Person::Person(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::Contacts::Person(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("Person::ctor Initialize");
		}

		void Person::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			contact__ = ref new Contact();
			Titanium::Contacts::Person::postCallAsConstructor(js_context, arguments);
		}

		void Person::construct(Windows::ApplicationModel::Contacts::Contact^ contact)
		{
			contact__ = contact;
		}

		void Person::JSExportInitialize() {
			JSExport<Person>::SetClassVersion(1);
			JSExport<Person>::SetParent(JSExport<Titanium::Contacts::Person>::Class());
		}

		Titanium::Contacts::Addresses Person::get_address() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Addresses addresses = Titanium::Contacts::create_empty_Addresses(get_context());

			CONTACT_VALUE_GUARD(addresses)

			for (size_t i = 0; i < contact__->Addresses->Size; i++) {
				auto win_address = contact__->Addresses->GetAt(i);

				Titanium::Contacts::Address address;
				address.city = TitaniumWindows::Utility::ConvertUTF8String(win_address->Locality);
				address.country = TitaniumWindows::Utility::ConvertUTF8String(win_address->Country);
				address.postalCode = TitaniumWindows::Utility::ConvertUTF8String(win_address->PostalCode);
				address.street = TitaniumWindows::Utility::ConvertUTF8String(win_address->StreetAddress);
				address.state = TitaniumWindows::Utility::ConvertUTF8String(win_address->Region);

				switch (win_address->Kind) {
				case ContactAddressKind::Home:
					addresses.home.push_back(address);
					break;
				case ContactAddressKind::Work:
					addresses.work.push_back(address);
					break;
				default:
					addresses.other.push_back(address);
					break;
				}
			}
			return addresses;
		}

		void Person::set_address(const Titanium::Contacts::Addresses& addresses) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_address(addresses);
			CONTACT_VOID_GUARD
			contact__->Addresses->Clear();
			for (auto ad : addresses.home) {
				auto address = createAddress(ad, ContactAddressKind::Home);
				contact__->Addresses->Append(address);
			}
			for (auto ad : addresses.work) {
				auto address = createAddress(ad, ContactAddressKind::Work);
				contact__->Addresses->Append(address);
			}
			for (auto ad : addresses.other) {
				auto address = createAddress(ad, ContactAddressKind::Other);
				contact__->Addresses->Append(address);
			}
		}

		ContactAddress^ Person::createAddress(const Titanium::Contacts::Address& ad, ContactAddressKind kind) TITANIUM_NOEXCEPT
		{
			auto address = ref new ContactAddress();
			address->Kind = kind;
			address->StreetAddress = TitaniumWindows::Utility::ConvertUTF8String(ad.street);
			address->Locality = TitaniumWindows::Utility::ConvertUTF8String(ad.city);
			address->Region = TitaniumWindows::Utility::ConvertUTF8String(ad.state);
			address->Country = TitaniumWindows::Utility::ConvertUTF8String(ad.country);
			address->PostalCode = TitaniumWindows::Utility::ConvertUTF8String(ad.postalCode);
			return address;
		}

		void Person::set_alternateBirthday(const Titanium::Contacts::AlternateBirthday& abd) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_alternateBirthday(abd);
			// FIXME We only want to remove birthdays! Can't just clear all ImportantDates, need to remove only birthday kinds!
			//contact__->ImportantDates->Clear();
			//auto date = ref new ContactDate();
			// TODO Convert into "standard" calendar?
			//date->Kind = ContactDateKind::Birthday;
			//date->Day = abd.day;
			//date->Month = abd.month;
			//date->Year = abd.year;
			
			//contact__->ImportantDates->Append(date);

			TITANIUM_MODULE_LOG_WARN("Person::set_alternateBirthday: Unimplemented");
		}

		std::string dateToString(ContactDate^ date) TITANIUM_NOEXCEPT
		{
			return TitaniumWindows::Utility::ConvertUTF8String("" + date->Year + "-" + date->Month + "-" + date->Day + "T00:00:00+000");
		}

		std::string Person::get_birthday() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			for (size_t i = 0; i < contact__->ImportantDates->Size; i++) {
				auto date = contact__->ImportantDates->GetAt(i);
				if (date->Kind == ContactDateKind::Birthday) {
					return dateToString(date);
				}
			}
			return Titanium::Contacts::Person::get_birthday();
		}

		void Person::set_birthday(const std::string& birthday) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_birthday(birthday);
			CONTACT_VOID_GUARD
			// Loop through ImportantDates and Remove birthday entries?
			// keep track of which entries are birthdays...
			std::vector<size_t> to_erase;
			for (size_t i = 0; i < contact__->ImportantDates->Size; i++) {
				auto date = contact__->ImportantDates->GetAt(i);
				if (ContactDateKind::Birthday == date->Kind) {
					to_erase.push_back(i);
				}
			}
			// Then remove them from back to front (to avoid having to deal with indices changing)
			for (size_t i = to_erase.size(); i >= 0; i--) {
				contact__->ImportantDates->RemoveAt(to_erase.at(i));
			}

			auto date = createDate(birthday, ContactDateKind::Birthday);
			contact__->ImportantDates->Append(date);
		}

		Titanium::Contacts::Dates Person::get_date() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Dates dates = Titanium::Contacts::create_empty_Dates(get_context());
			CONTACT_VALUE_GUARD(dates)
			// Only add anniversaries and other, not birthdays
			std::vector<size_t> to_erase;
			for (size_t i = 0; i < contact__->ImportantDates->Size; i++) {
				auto date = contact__->ImportantDates->GetAt(i);
				const auto str = dateToString(date);
				switch (date->Kind) {
				case ContactDateKind::Anniversary:
					dates.anniversary.push_back(str);
					break;
				case ContactDateKind::Other:
					dates.other.push_back(str);
					break;
				default:
					break;
				}
			}
			return dates;
		}

		void Person::set_date(const Titanium::Contacts::Dates& dates) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_date(dates);
			CONTACT_VOID_GUARD
			// Loop through ImportantDates and Remove non-birthday entries?
			// keep track of which entries are not birthdays...
			std::vector<size_t> to_erase;
			for (size_t i = 0; i < contact__->ImportantDates->Size; i++) {
				auto date = contact__->ImportantDates->GetAt(i);
				if (ContactDateKind::Birthday != date->Kind) {
					to_erase.push_back(i);
				}
			}
			// Then remove them from back to front (to avoid having to deal with indices changing)
			for (size_t i = to_erase.size(); i >= 0; i--) {
				contact__->ImportantDates->RemoveAt(to_erase.at(i));
			}

			// Now add the anniversaries/other
			for (auto ad : dates.anniversary) {
				auto date = createDate(ad, ContactDateKind::Anniversary);
				contact__->ImportantDates->Append(date);
			}
			for (auto ad : dates.other) {
				auto date = createDate(ad, ContactDateKind::Other);
				contact__->ImportantDates->Append(date);
			}
		}

		ContactDate^ Person::createDate(const std::string& dateString, ContactDateKind kind) TITANIUM_NOEXCEPT
		{
			auto date = ref new ContactDate();
			date->Kind = kind;
			auto copy = dateString;
			// strip off .%s+0000
			auto found = copy.find(".");
			if (found != std::string::npos)
			{
				copy.erase(found, std::string::npos);
			}

			std::tm tm;
			std::stringstream ss(copy);
			ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
			//auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
			date->Year = 1900 + tm.tm_year;
			date->Month = static_cast<uint32_t>(tm.tm_mon + 1);
			date->Day = static_cast<uint32_t>(tm.tm_mday);
			return date;
		}

		std::string Person::get_department() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			auto job_infos = contact__->JobInfo;
			if (job_infos->Size == 0) {
				return ""; // No job info, so no department
			}

			// get the first JobInfo
			auto info = job_infos->GetAt(0);
			return TitaniumWindows::Utility::ConvertUTF8String(info->Department);
		}

		void Person::set_department(const std::string& department) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_department(department);
			CONTACT_VOID_GUARD
			auto job_infos = contact__->JobInfo;
			ContactJobInfo^ info;
			if (job_infos->Size == 0) {
				// Create a JobInfo!
				info = ref new ContactJobInfo();
				job_infos->Append(info);
			} else {
				// get the first JobInfo
				info = job_infos->GetAt(0);
			}
			info->Department = TitaniumWindows::Utility::ConvertUTF8String(department);
		}

		Titanium::Contacts::Emails Person::get_email() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Emails emails = Titanium::Contacts::create_empty_Emails(get_context());
			CONTACT_VALUE_GUARD(emails)
			for (size_t i = 0; i < contact__->Emails->Size; i++) {
				auto email = contact__->Emails->GetAt(i);
				auto address = TitaniumWindows::Utility::ConvertUTF8String(email->Address);
				switch (email->Kind) {
					case ContactEmailKind::Personal:
						emails.home.push_back(address);
						break;
					case ContactEmailKind::Work:
						emails.work.push_back(address);
						break;
					case ContactEmailKind::Other:
						emails.other.push_back(address);
						break;
				}
			}
			return emails;
		}

		void Person::set_email(const Titanium::Contacts::Emails& emails) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_email(emails);
			CONTACT_VOID_GUARD
			contact__->Emails->Clear();
			for (auto ad : emails.home) {
				auto address = createEmail(ad, ContactEmailKind::Personal);
				contact__->Emails->Append(address);
			}
			for (auto ad : emails.work) {
				auto address = createEmail(ad, ContactEmailKind::Work);
				contact__->Emails->Append(address);
			}
			for (auto ad : emails.other) {
				auto address = createEmail(ad, ContactEmailKind::Other);
				contact__->Emails->Append(address);
			}
		}

		ContactEmail^ Person::createEmail(const std::string& value, ContactEmailKind kind) TITANIUM_NOEXCEPT
		{
			auto email = ref new ContactEmail();
			email->Kind = kind;
			email->Address = TitaniumWindows::Utility::ConvertUTF8String(value);
			return email;
		}

		std::string Person::get_firstName() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->FirstName);
		}

		void Person::set_firstName(const std::string& firstName) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_firstName(firstName);
			CONTACT_VOID_GUARD
			contact__->FirstName = TitaniumWindows::Utility::ConvertUTF8String(firstName);
		}

		std::string Person::get_firstPhonetic() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->YomiGivenName);
		}

		void Person::set_firstPhonetic(const std::string& firstPhonetic) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_firstPhonetic(firstPhonetic);
			CONTACT_VOID_GUARD
			contact__->YomiGivenName = TitaniumWindows::Utility::ConvertUTF8String(firstPhonetic);
		}

		std::string Person::get_fullName() const TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			CONTACT_STRING_GUARD
			// Windows 10+
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->FullName);
#else
			return Titanium::Contacts::Person::get_fullName();
#endif
		}

		void Person::set_fullName(const std::string& fullName) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_fullName(fullName);
			TITANIUM_MODULE_LOG_WARN("Person::set_fullName: Read-only on Windows 8.1 and Windows 10");
		}

		std::string Person::get_identifier() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->Id);
		}

		void Person::set_image(const std::shared_ptr<::Titanium::Blob>& image) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_image(image);
			// TODO cast to TitaniumWindows::Filesystem::File and unwrap the StorageFile
			//auto file = image->get_file();
			//std::dynamic_pointer_cast<TitaniumWindows::Filesystem::File>(file);
			//contact__->Thumbnail = 
			TITANIUM_MODULE_LOG_WARN("Person::set_image: Unimplemented");
		}

		Titanium::Contacts::InstantMessages Person::get_instantMessage() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::InstantMessages ims = Titanium::Contacts::create_empty_InstantMessages(get_context());

			CONTACT_VALUE_GUARD(ims)

			// FIXME How do we differentiate between socialprofile and instantMessages?
			// Should we do some filtering based on the service name?
			// AIM, Facebook, GaduGadu, GoogleTalk, ICQ, Jabber, MSN, QQ, Skype, or Yahoo for IM
			for (size_t i = 0; i < contact__->ConnectedServiceAccounts->Size; i++) {
				auto account = contact__->ConnectedServiceAccounts->GetAt(i);
				Titanium::Contacts::InstantMessage im;
				im.username = TitaniumWindows::Utility::ConvertUTF8String(account->Id);
				im.service = TitaniumWindows::Utility::ConvertUTF8String(account->ServiceName);
				// They only allow you to specify the service name and id, but can't organize by work/home/other
				ims.home.push_back(im);
			}
			return ims;
		}

		void Person::set_instantMessage(const Titanium::Contacts::InstantMessages& instantMessage) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_instantMessage(instantMessage);
			CONTACT_VOID_GUARD
			// They only allow you to specify the service name and id, but can't organize by work/home/other
			contact__->ConnectedServiceAccounts->Clear();
			for (auto ad : instantMessage.home) {
				auto p = createInstantMessage(ad);
				contact__->ConnectedServiceAccounts->Append(p);
			}
			for (auto ad : instantMessage.work) {
				auto p = createInstantMessage(ad);
				contact__->ConnectedServiceAccounts->Append(p);
			}
			for (auto ad : instantMessage.other) {
				auto p = createInstantMessage(ad);
				contact__->ConnectedServiceAccounts->Append(p);
			}
		}

		ContactConnectedServiceAccount^ Person::createInstantMessage(const Titanium::Contacts::InstantMessage& im) TITANIUM_NOEXCEPT
		{
			auto account = ref new ContactConnectedServiceAccount();
			account->ServiceName = TitaniumWindows::Utility::ConvertUTF8String(im.service);
			account->Id = TitaniumWindows::Utility::ConvertUTF8String(im.username);
			return account;
		}

		std::string Person::get_jobTitle() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			auto job_infos = contact__->JobInfo;
			if (job_infos->Size == 0) {
				return ""; // No job info, so no title
			}

			// get the first JobInfo
			auto info = job_infos->GetAt(0);
			return TitaniumWindows::Utility::ConvertUTF8String(info->Title);
		}

		void Person::set_jobTitle(const std::string& jobTitle) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_jobTitle(jobTitle);
			CONTACT_VOID_GUARD
			auto job_infos = contact__->JobInfo;
			ContactJobInfo^ info;
			if (job_infos->Size == 0)
			{
				// Create a JobInfo!
				info = ref new ContactJobInfo();
				job_infos->Append(info);
			} else {
				// get the first JobInfo
				info = job_infos->GetAt(0);
			}
			info->Title = TitaniumWindows::Utility::ConvertUTF8String(jobTitle);
		}

		void Person::set_kind(const Titanium::Contacts::KIND& kind) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_kind(kind);
			TITANIUM_MODULE_LOG_WARN("Person::set_kind: Unimplemented");
		}

		std::string Person::get_lastName() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->LastName);
		}

		void Person::set_lastName(const std::string& lastName) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_lastName(lastName);
			CONTACT_VOID_GUARD
			contact__->LastName = TitaniumWindows::Utility::ConvertUTF8String(lastName);
		}

		std::string Person::get_lastPhonetic() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->YomiFamilyName);
		}

		void Person::set_lastPhonetic(const std::string& lastPhonetic) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_firstPhonetic(lastPhonetic);
			CONTACT_VOID_GUARD
			contact__->YomiFamilyName = TitaniumWindows::Utility::ConvertUTF8String(lastPhonetic);
		}

		std::string Person::get_middleName() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->MiddleName);
		}

		void Person::set_middleName(const std::string& middleName) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_middleName(middleName);
			CONTACT_VOID_GUARD
			contact__->MiddleName = TitaniumWindows::Utility::ConvertUTF8String(middleName);
		}

		void Person::set_middlePhonetic(const std::string& middlePhonetic) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_middlePhonetic(middlePhonetic);
			TITANIUM_MODULE_LOG_WARN("Person::set_middlePhonetic: Unimplemented");
		}

		std::string Person::get_nickname() const TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->Nickname);
#else
			return Titanium::Contacts::Person::get_nickname();
#endif
		}

		void Person::set_nickname(const std::string& nickname) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_nickname(nickname);
#if defined(IS_WINDOWS_10)
			CONTACT_VOID_GUARD
			contact__->Nickname = TitaniumWindows::Utility::ConvertUTF8String(nickname);
#else
			TITANIUM_MODULE_LOG_WARN("Person::set_nickname: Unimplemented");
#endif
		}

		std::string Person::get_note() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->Notes);
		}

		void Person::set_note(const std::string& note) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_note(note);
			CONTACT_VOID_GUARD
			contact__->Notes = TitaniumWindows::Utility::ConvertUTF8String(note);
		}

		std::string Person::get_organization() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			auto job_infos = contact__->JobInfo;
			if (job_infos->Size == 0) {
				return "";
			}
			
			// get the first JobInfo
			auto info = job_infos->GetAt(0);
			
			// FIXME What's the best fit here? CompanyName? Office? We already use Department...
			return TitaniumWindows::Utility::ConvertUTF8String(info->CompanyName);
		}

		void Person::set_organization(const std::string& organization) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_organization(organization);
			CONTACT_VOID_GUARD
			auto job_infos = contact__->JobInfo;
			ContactJobInfo^ info;
			if (job_infos->Size == 0) {
				// Create a JobInfo!
				info = ref new ContactJobInfo();
				job_infos->Append(info);
			} else {
				// get the first JobInfo
				info = job_infos->GetAt(0);
			}
			// FIXME What's the best fit here? CompanyName? Office? We already use Department...
			info->CompanyName = TitaniumWindows::Utility::ConvertUTF8String(organization);
		}

		Titanium::Contacts::Phones Person::get_phone() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Phones phones = Titanium::Contacts::create_empty_Phones(get_context());
			CONTACT_VALUE_GUARD(phones)
			for (size_t i = 0; i < contact__->Phones->Size; i++) {
				auto phone = contact__->Phones->GetAt(i);
				auto number = TitaniumWindows::Utility::ConvertUTF8String(phone->Number);

				// use Description to get back original string used for categorization if we stuffed it in there
				auto description = TitaniumWindows::Utility::ConvertUTF8String(phone->Description);
				if ("home" == description) {
					phones.home.push_back(number);
				} else if ("work" == description) {
					phones.work.push_back(number);
				} else if ("other" == description) {
					phones.other.push_back(number);
				} else if ("mobile" == description) {
					phones.mobile.push_back(number);
				} else if ("pager" == description) {
					phones.pager.push_back(number);
				} else if ("workFax" == description) {
					phones.workFax.push_back(number);
				} else if ("homeFax" == description) {
					phones.homeFax.push_back(number);
				} else if ("main" == description) {
					phones.main.push_back(number);
				} else if ("iPhone" == description) {
					phones.iPhone.push_back(number);
				} else {
					// Ok we didn't populate the Description, or it's changed since...
					switch (phone->Kind) {
#if defined(IS_WINDOWS_10)
					case ContactPhoneKind::Pager:
						phones.pager.push_back(number);
						break;
					case ContactPhoneKind::BusinessFax:
						phones.workFax.push_back(number);
						break;
					case ContactPhoneKind::HomeFax:
						phones.homeFax.push_back(number);
						break;
					case ContactPhoneKind::Company:
						phones.main.push_back(number);
						break;
#endif
					case ContactPhoneKind::Home:
						phones.home.push_back(number);
						break;
					case ContactPhoneKind::Mobile:
						phones.mobile.push_back(number);
						break;
					case ContactPhoneKind::Work:
						phones.work.push_back(number);
						break;
					case ContactPhoneKind::Other:
						phones.other.push_back(number);
						break;
					}
				}
			}
			return phones;
		}

		void Person::set_phone(const Titanium::Contacts::Phones& phones) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_phone(phones);
			CONTACT_VOID_GUARD
			contact__->Phones->Clear();

			for (auto ad : phones.home) {
				auto p = createPhone(ad, "home", ContactPhoneKind::Home);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.work) {
				auto p = createPhone(ad, "work", ContactPhoneKind::Work);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.other) {
				auto p = createPhone(ad, "other", ContactPhoneKind::Other);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.mobile) {
				auto p = createPhone(ad, "mobile", ContactPhoneKind::Mobile);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.pager) {
#if defined(IS_WINDOWS_10)
				auto kind = ContactPhoneKind::Pager;
#else
				auto kind = ContactPhoneKind::Other;
#endif
				auto p = createPhone(ad, "pager", kind);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.workFax) {
#if defined(IS_WINDOWS_10)
				auto kind = ContactPhoneKind::BusinessFax;
#else
				auto kind = ContactPhoneKind::Other;
#endif
				auto p = createPhone(ad, "workFax", kind);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.homeFax) {
#if defined(IS_WINDOWS_10)
				auto kind = ContactPhoneKind::HomeFax;
#else
				auto kind = ContactPhoneKind::Other;
#endif
				auto p = createPhone(ad, "homeFax", kind);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.main) {
#if defined(IS_WINDOWS_10)
				// Windows 10+
				auto kind = ContactPhoneKind::Company;
#else
				auto kind = ContactPhoneKind::Other;
#endif
				auto p = createPhone(ad, "main", kind);
				contact__->Phones->Append(p);
			}
			for (auto ad : phones.iPhone) {
				auto p = createPhone(ad, "iPhone", ContactPhoneKind::Mobile);
				contact__->Phones->Append(p);
			}
		}

		ContactPhone^ Person::createPhone(const std::string& number, const std::string& type, ContactPhoneKind kind) TITANIUM_NOEXCEPT
		{
			auto phone = ref new ContactPhone();
			phone->Kind = kind;
			// Set the Titanium key in the Description field, since for Win 8.1 we lose resolution with kind
			phone->Description = TitaniumWindows::Utility::ConvertUTF8String(type);
			phone->Number = TitaniumWindows::Utility::ConvertUTF8String(number);
			return phone;
		}

		std::string Person::get_prefix() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->HonorificNamePrefix);
		}

		void Person::set_prefix(const std::string& prefix) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_prefix(prefix);
			CONTACT_VOID_GUARD
			contact__->HonorificNamePrefix = TitaniumWindows::Utility::ConvertUTF8String(prefix);
		}

		Titanium::Contacts::RelatedNames Person::get_relatedNames() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::RelatedNames names = Titanium::Contacts::create_empty_RelatedNames(get_context());
			CONTACT_VALUE_GUARD(names)
			for (size_t i = 0; i < contact__->SignificantOthers->Size; i++) {
				auto so = contact__->SignificantOthers->GetAt(i);
				auto name = TitaniumWindows::Utility::ConvertUTF8String(so->Name);

				// use Description to get back original string used for categorization if we stuffed it in there
				auto description = TitaniumWindows::Utility::ConvertUTF8String(so->Description);
				if ("mother" == description) {
					names.mother.push_back(name);
				} else if ("father" == description) {
					names.father.push_back(name);
				} else if ("parent" == description) {
					names.parent.push_back(name);
				} else if ("brother" == description) {
					names.brother.push_back(name);
				} else if ("sister" == description) {
					names.sister.push_back(name);
				} else if ("child" == description) {
					names.child.push_back(name);
				} else if ("friend" == description) {
					names.friend_.push_back(name);
				} else if ("spouse" == description) {
					names.spouse.push_back(name);
				} else if ("partner" == description) {
					names.partner.push_back(name);
				} else if ("assistant" == description) {
					names.assistant.push_back(name);
				} else if ("manager" == description) {
					names.manager.push_back(name);
				} else {

#if defined(IS_WINDOWS_10)
					// Windows 10+ enum values
					// Ok we didn't populate the Description, or it's changed since...
					switch (so->Relationship) {
					case ContactRelationship::Spouse:
						names.spouse.push_back(name);
						break;
					case ContactRelationship::Partner:
						names.partner.push_back(name);
						break;
					case ContactRelationship::Sibling:
						names.brother.push_back(name); // guess male gender?!
						break;
					case ContactRelationship::Parent:
						names.parent.push_back(name);
						break;
					case ContactRelationship::Child:
						names.child.push_back(name);
						break;
					default:
						names.other.push_back(name);
						break;
					}
#else
					names.other.push_back(name);
#endif
				}
			}
			return names;
		}

		void Person::set_relatedNames(const Titanium::Contacts::RelatedNames& relatedNames) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_relatedNames(relatedNames);
			CONTACT_VOID_GUARD
			contact__->SignificantOthers->Clear();
			for (auto ad : relatedNames.mother) {
				auto p = createSignificantOther(ad, "mother");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.father) {
				auto p = createSignificantOther(ad, "father");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.parent) {
				auto p = createSignificantOther(ad, "parent");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.brother) {
				auto p = createSignificantOther(ad, "brother");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.sister) {
				auto p = createSignificantOther(ad, "sister");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.child) {
				auto p = createSignificantOther(ad, "child");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.friend_) {
				auto p = createSignificantOther(ad, "friend");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.spouse) {
				auto p = createSignificantOther(ad, "spouse");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.partner) {
				auto p = createSignificantOther(ad, "partner");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.assistant) {
				auto p = createSignificantOther(ad, "assistant");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.manager) {
				auto p = createSignificantOther(ad, "manager");
				contact__->SignificantOthers->Append(p);
			}
			for (auto ad : relatedNames.other) {
				auto p = createSignificantOther(ad, "other");
				contact__->SignificantOthers->Append(p);
			}
		}

		ContactSignificantOther^ Person::createSignificantOther(const std::string& name, const std::string& type) TITANIUM_NOEXCEPT
		{
			auto other = ref new ContactSignificantOther();
			other->Name = TitaniumWindows::Utility::ConvertUTF8String(name);
			// store Titanium key in Description, since we actually lose info about relationship using Windows 10+ enum
			other->Description = TitaniumWindows::Utility::ConvertUTF8String(type);
#if defined(IS_WINDOWS_10)
			auto relationship = ContactRelationship::Other;
			if (type == "spouse") {
				relationship = ContactRelationship::Spouse;
			} else if (type == "partner") {
				relationship = ContactRelationship::Partner;
			} else if ((type == "sister") || (type == "brother")) {
				relationship = ContactRelationship::Sibling;
			} else if ((type == "parent") || (type == "mother") || (type == "father")) {
				relationship = ContactRelationship::Parent;
			} else if (type == "child") {
				relationship = ContactRelationship::Child;
			}
			other->Relationship = relationship;
			// FIXME We can actually set a Manager in ContactJobInfo listings...
			// contact__->JobInfo->GetAt(0)->Manager = 
#endif
			return other;
		}

		Titanium::Contacts::InstantMessages Person::get_socialProfile() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::InstantMessages ims = Titanium::Contacts::create_empty_InstantMessages(get_context());
			CONTACT_VALUE_GUARD(ims)
			// FIXME How do we differentiate between socialprofile and instantMessages?
			// Should we do some filtering based on the service name?
			// twitter, sinaweibo, gamecenter, facebook, myspace, linkedin, or flickr for socialProfile
			for (size_t i = 0; i < contact__->ConnectedServiceAccounts->Size; i++) {
				auto account = contact__->ConnectedServiceAccounts->GetAt(i);
				Titanium::Contacts::InstantMessage im;
				im.username = TitaniumWindows::Utility::ConvertUTF8String(account->Id);
				im.service = TitaniumWindows::Utility::ConvertUTF8String(account->ServiceName);
				// They only allow you to specify the service name and id, but can't organize by work/home/other
				ims.home.push_back(im);
			}
			return ims;
		}

		void Person::set_socialProfile(const Titanium::Contacts::InstantMessages& instantMessage) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_socialProfile(instantMessage);
			CONTACT_VOID_GUARD
			// They only allow you to specify the service name and id, but can't organize by work/home/other
			// FIXME Need to only wipe out the "social profile" accounts, but not the instant message ones!
			contact__->ConnectedServiceAccounts->Clear();
			for (auto ad : instantMessage.home) {
				auto p = createInstantMessage(ad);
				contact__->ConnectedServiceAccounts->Append(p);
			}
			for (auto ad : instantMessage.work) {
				auto p = createInstantMessage(ad);
				contact__->ConnectedServiceAccounts->Append(p);
			}
			for (auto ad : instantMessage.other) {
				auto p = createInstantMessage(ad);
				contact__->ConnectedServiceAccounts->Append(p);
			}
		}

		std::string Person::get_suffix() const TITANIUM_NOEXCEPT
		{
			CONTACT_STRING_GUARD
			return TitaniumWindows::Utility::ConvertUTF8String(contact__->HonorificNameSuffix);
		}

		void Person::set_suffix(const std::string& suffix) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_suffix(suffix);
			CONTACT_VOID_GUARD
			contact__->HonorificNameSuffix = TitaniumWindows::Utility::ConvertUTF8String(suffix);
		}

		Titanium::Contacts::Urls Person::get_url() const TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Urls urls = Titanium::Contacts::create_empty_Urls(get_context());
			CONTACT_VALUE_GUARD(urls)
			for (size_t i = 0; i < contact__->Websites->Size; i++) {
				auto website = contact__->Websites->GetAt(i);
				auto url = TitaniumWindows::Utility::ConvertUTF8String(website->Uri->AbsoluteUri);
				auto category = TitaniumWindows::Utility::ConvertUTF8String(website->Description);
				if (category == "homepage") {
					urls.homepage.push_back(url);
				}
				else if (category == "home") {
					urls.home.push_back(url);
				}
				else if (category == "work") {
					urls.work.push_back(url);
				}
				else { // "other"
					urls.other.push_back(url);
				}
			}
			return urls;
		}

		void Person::set_url(const Titanium::Contacts::Urls& urls) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Person::set_url(urls);
			CONTACT_VOID_GUARD
			contact__->Websites->Clear();
			for (auto ad : urls.homepage) {
				auto address = createWebsite(ad, "homepage");
				contact__->Websites->Append(address);
			}
			for (auto ad : urls.home) {
				auto address = createWebsite(ad, "home");
				contact__->Websites->Append(address);
			}
			for (auto ad : urls.work) {
				auto address = createWebsite(ad, "work");
				contact__->Websites->Append(address);
			}
			for (auto ad : urls.other) {
				auto address = createWebsite(ad, "other");
				contact__->Websites->Append(address);
			}
		}

		ContactWebsite^ Person::createWebsite(const std::string& value, const std::string& type) TITANIUM_NOEXCEPT
		{
			auto website = ref new ContactWebsite();
#if defined(IS_WINDOWS_10)
			website->RawValue = TitaniumWindows::Utility::ConvertUTF8String(value);
#endif
			website->Uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertUTF8String(value));
			// Store the Titanium url type in the Description field
			website->Description = TitaniumWindows::Utility::ConvertUTF8String(type);
			return website;
		}

#if defined(IS_WINDOWS_10)
		Windows::ApplicationModel::Contacts::Contact^ Person::GetContact() const
		{
			return contact__;
		}
#endif

		void Person::remove()
		{
			// TODO Remove from any contact lists in DB
#if defined(IS_WINDOWS_10)
			CONTACT_VOID_GUARD
			const auto list_id = contact__->ContactListId;
			// Pull up the contact list associated with this contact...
			concurrency::event event;
			concurrency::create_task(ContactManager::RequestStoreAsync(ContactStoreAccessType::AppContactsReadWrite))
			.then([&list_id](ContactStore^ store) {
				return store->GetContactListAsync(list_id);
			}, concurrency::task_continuation_context::use_arbitrary())
			.then([this] (ContactList^ list) {
				return list->DeleteContactAsync(contact__);
			}, concurrency::task_continuation_context::use_arbitrary())
			.then([&event](concurrency::task<void> task) {
				try {
					task.get();
				}
				catch (...) {
					// TODO log
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
#else
			TITANIUM_MODULE_LOG_WARN("Person::remove: Unimplemented");
#endif
		}

	}  // namespace Contacts
}  // namespace TitaniumWindows