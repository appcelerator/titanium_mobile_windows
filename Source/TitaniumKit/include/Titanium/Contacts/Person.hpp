/**
 * TitaniumKit Titanium.Contacts.Person
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_PERSON_HPP_
#define _TITANIUM_PERSON_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Contacts/Constants.hpp"
#include "Titanium/Contacts/Addresses.hpp"
#include "Titanium/Contacts/AlternateBirthday.hpp"
#include "Titanium/Contacts/Dates.hpp"
#include "Titanium/Contacts/Emails.hpp"
#include "Titanium/Contacts/InstantMessages.hpp"
#include "Titanium/Contacts/Phones.hpp"
#include "Titanium/Contacts/RelatedNames.hpp"
#include "Titanium/Contacts/Urls.hpp"
#include <vector>
#include <unordered_map>

namespace Titanium
{

	class Blob;
	
	namespace Contacts
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Person Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Contacts.Person
		*/
		class TITANIUMKIT_EXPORT Person : public Module, public JSExport<Person>
		{

		public:

			/*!
			  @property
			  @abstract address
			  @discussion Addresses for the person. Multi-value. Read-only on Android.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Addresses, address);

			/*!
			  @property
			  @abstract birthday
			  @discussion Date of birth of the person. Single value.
			*/
			 // TODO Use date type!
			TITANIUM_PROPERTY_IMPL_DEF(std::string, birthday);

			/*!
			  @property
			  @abstract alternateBirthday
			  @discussion Alternate birthday of the person. Single Dictionary.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(AlternateBirthday, alternateBirthday);

			/*!
			  @property
			  @abstract created
			  @discussion Date and time that the person record was created. Single value.
			*/
			  // TODO Use date type, not string!
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, created);

			/*!
			  @property
			  @abstract date
			  @discussion Dates associated with the person. Multi-value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Dates, date);

			/*!
			  @property
			  @abstract department
			  @discussion Department of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, department);

			/*!
			  @property
			  @abstract email
			  @discussion Email addresses for the person. Multi-value. Read-only on Android.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Emails, email);

			/*!
			  @property
			  @abstract firstName
			  @discussion First name of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, firstName);

			/*!
			  @property
			  @abstract firstPhonetic
			  @discussion Phonetic first name of the person.  Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, firstPhonetic);

			/*!
			  @property
			  @abstract fullName
			  @discussion Localized full name of the person. Single value. Read-only on Android.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, fullName);

			/*!
			  @property
			  @abstract id
			  @discussion Record identifier of the person. Single value.
			  This value is a Number on iOS, and is a String on Windows.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(JSValue, id);

			/*!
			  @property
			  @abstract image
			  @discussion Image for the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<::Titanium::Blob>, image);

			/*!
			  @property
			  @abstract instantMessage
			  @discussion Instant messenger names of the person. Multi-value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(InstantMessages, instantMessage);

			/*!
			  @property
			  @abstract jobTitle
			  @discussion Job title of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, jobTitle);

			/*!
			  @property
			  @abstract kind
			  @discussion Determines the type of information the person record contains; either person or organization. Read-only on Android.
			*/
			  // FIXME Use a constant!
			TITANIUM_PROPERTY_IMPL_DEF(KIND, kind);

			/*!
			  @property
			  @abstract lastName
			  @discussion Last name of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, lastName);

			/*!
			  @property
			  @abstract lastPhonetic
			  @discussion Phonetic last name of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, lastPhonetic);

			/*!
			  @property
			  @abstract middleName
			  @discussion Middle name of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, middleName);

			/*!
			  @property
			  @abstract middlePhonetic
			  @discussion Phonetic middle name of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, middlePhonetic);

			/*!
			  @property
			  @abstract modified
			  @discussion Date and time that the person record was last modified. Single value.
			*/
			// FIXME Use a time type!
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, modified);

			/*!
			  @property
			  @abstract nickname
			  @discussion Nickname of the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, nickname);

			/*!
			  @property
			  @abstract note
			  @discussion Notes for the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, note);

			/*!
			  @property
			  @abstract organization
			  @discussion Organization to which the person belongs. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, organization);

			/*!
			  @property
			  @abstract phone
			  @discussion Phone numbers for the person. Multi-value. Read-only on Android.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Phones, phone);

			/*!
			  @property
			  @abstract prefix
			  @discussion Prefix for the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, prefix);

			/*!
			  @property
			  @abstract recordId
			  @discussion Record identifier of the person. Single value.
			  This value is a Number on iOS, and is a String on Windows.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(JSValue, recordId);

			/*!
			  @property
			  @abstract relatedNames
			  @discussion Names of people to which the person is related. Multi-value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(RelatedNames, relatedNames);

			/*!
			  @property
			  @abstract socialProfile
			  @discussion Social profile information of the person. Multi-value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(InstantMessages, socialProfile);

			/*!
			  @property
			  @abstract suffix
			  @discussion Suffix for the person. Single value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, suffix);

			/*!
			  @property
			  @abstract url
			  @discussion URLs of webpages associated with the person. Multi-value.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Urls, url);

			Person(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Person()                = default;
			Person(const Person&)            = default;
			Person& operator=(const Person&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Person(Person&&)                 = default;
			Person& operator=(Person&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(address);
			TITANIUM_PROPERTY_DEF(birthday);
			TITANIUM_PROPERTY_DEF(alternateBirthday);
			TITANIUM_PROPERTY_READONLY_DEF(created);
			TITANIUM_PROPERTY_DEF(date);
			TITANIUM_PROPERTY_DEF(department);
			TITANIUM_PROPERTY_DEF(email);
			TITANIUM_PROPERTY_DEF(firstName);
			TITANIUM_PROPERTY_DEF(firstPhonetic);
			TITANIUM_PROPERTY_DEF(fullName);
			TITANIUM_PROPERTY_READONLY_DEF(id);
			TITANIUM_PROPERTY_DEF(image);
			TITANIUM_PROPERTY_DEF(instantMessage);
			TITANIUM_PROPERTY_DEF(jobTitle);
			TITANIUM_PROPERTY_DEF(kind);
			TITANIUM_PROPERTY_DEF(lastName);
			TITANIUM_PROPERTY_DEF(lastPhonetic);
			TITANIUM_PROPERTY_DEF(middleName);
			TITANIUM_PROPERTY_DEF(middlePhonetic);
			TITANIUM_PROPERTY_READONLY_DEF(modified);
			TITANIUM_PROPERTY_DEF(nickname);
			TITANIUM_PROPERTY_DEF(note);
			TITANIUM_PROPERTY_DEF(organization);
			TITANIUM_PROPERTY_DEF(phone);
			TITANIUM_PROPERTY_DEF(prefix);
			TITANIUM_PROPERTY_DEF(recordId);
			TITANIUM_PROPERTY_DEF(relatedNames);
			TITANIUM_PROPERTY_DEF(socialProfile);
			TITANIUM_PROPERTY_DEF(suffix);
			TITANIUM_PROPERTY_DEF(url);

			TITANIUM_FUNCTION_DEF(getAddress);
			TITANIUM_FUNCTION_DEF(setAddress);
			TITANIUM_FUNCTION_DEF(getBirthday);
			TITANIUM_FUNCTION_DEF(setBirthday);
			TITANIUM_FUNCTION_DEF(getAlternateBirthday);
			TITANIUM_FUNCTION_DEF(setAlternateBirthday);
			TITANIUM_FUNCTION_DEF(getCreated);
			TITANIUM_FUNCTION_DEF(getDate);
			TITANIUM_FUNCTION_DEF(setDate);
			TITANIUM_FUNCTION_DEF(getDepartment);
			TITANIUM_FUNCTION_DEF(setDepartment);
			TITANIUM_FUNCTION_DEF(getEmail);
			TITANIUM_FUNCTION_DEF(setEmail);
			TITANIUM_FUNCTION_DEF(getFirstName);
			TITANIUM_FUNCTION_DEF(setFirstName);
			TITANIUM_FUNCTION_DEF(getFirstPhonetic);
			TITANIUM_FUNCTION_DEF(setFirstPhonetic);
			TITANIUM_FUNCTION_DEF(getFullName);
			TITANIUM_FUNCTION_DEF(setFullName);
			TITANIUM_FUNCTION_DEF(getId);
			TITANIUM_FUNCTION_DEF(getImage);
			TITANIUM_FUNCTION_DEF(setImage);
			TITANIUM_FUNCTION_DEF(getInstantMessage);
			TITANIUM_FUNCTION_DEF(setInstantMessage);
			TITANIUM_FUNCTION_DEF(getJobTitle);
			TITANIUM_FUNCTION_DEF(setJobTitle);
			TITANIUM_FUNCTION_DEF(getKind);
			TITANIUM_FUNCTION_DEF(setKind);
			TITANIUM_FUNCTION_DEF(getLastName);
			TITANIUM_FUNCTION_DEF(setLastName);
			TITANIUM_FUNCTION_DEF(getLastPhonetic);
			TITANIUM_FUNCTION_DEF(setLastPhonetic);
			TITANIUM_FUNCTION_DEF(getMiddleName);
			TITANIUM_FUNCTION_DEF(setMiddleName);
			TITANIUM_FUNCTION_DEF(getMiddlePhonetic);
			TITANIUM_FUNCTION_DEF(setMiddlePhonetic);
			TITANIUM_FUNCTION_DEF(getModified);
			TITANIUM_FUNCTION_DEF(getNickname);
			TITANIUM_FUNCTION_DEF(setNickname);
			TITANIUM_FUNCTION_DEF(getNote);
			TITANIUM_FUNCTION_DEF(setNote);
			TITANIUM_FUNCTION_DEF(getOrganization);
			TITANIUM_FUNCTION_DEF(setOrganization);
			TITANIUM_FUNCTION_DEF(getPhone);
			TITANIUM_FUNCTION_DEF(setPhone);
			TITANIUM_FUNCTION_DEF(getPrefix);
			TITANIUM_FUNCTION_DEF(setPrefix);
			TITANIUM_FUNCTION_DEF(getRecordId);
			TITANIUM_FUNCTION_DEF(setRecordId);
			TITANIUM_FUNCTION_DEF(getRelatedNames);
			TITANIUM_FUNCTION_DEF(setRelatedNames);
			TITANIUM_FUNCTION_DEF(getSocialProfile);
			TITANIUM_FUNCTION_DEF(setSocialProfile);
			TITANIUM_FUNCTION_DEF(getSuffix);
			TITANIUM_FUNCTION_DEF(setSuffix);
			TITANIUM_FUNCTION_DEF(getUrl);
			TITANIUM_FUNCTION_DEF(setUrl);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			Addresses address__;
			std::string birthday__;
			AlternateBirthday alternateBirthday__;
			std::string created__;
			Dates date__;
			std::string department__;
			Emails email__;
			std::string firstName__;
			std::string firstPhonetic__;
			std::string fullName__;
			JSValue id__;
			std::shared_ptr<::Titanium::Blob> image__;
			InstantMessages instantMessage__;
			std::string jobTitle__;
			KIND kind__;
			std::string lastName__;
			std::string lastPhonetic__;
			std::string middleName__;
			std::string middlePhonetic__;
			std::string modified__;
			std::string nickname__;
			std::string note__;
			std::string organization__;
			Phones phone__;
			std::string prefix__;
			JSValue recordId__;
			RelatedNames relatedNames__;
			InstantMessages socialProfile__;
			std::string suffix__;
			Urls url__;
#pragma warning(pop)
		};

	} // namespace Contacts
} // namespace Titanium
#endif // _TITANIUM_PERSON_HPP_