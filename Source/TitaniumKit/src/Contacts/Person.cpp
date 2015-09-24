/**
 * TitaniumKit Titanium.Contacts.Person
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Contacts/Person.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Contacts
	{
		using namespace std;

		Person::Person(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context),
			address__(Titanium::Contacts::create_empty_Addresses(js_context)),
			alternateBirthday__(Titanium::Contacts::create_empty_AlternateBirthday(js_context)),
			birthday__(""),
			created__(""),
			date__(Titanium::Contacts::create_empty_Dates(js_context)),
			email__(Titanium::Contacts::create_empty_Emails(js_context)),
			department__(""),
			firstName__(""),
			firstPhonetic__(""),
			fullName__(""),
			id__(js_context.CreateNull()),
			instantMessage__(Titanium::Contacts::create_empty_InstantMessages(js_context)),
			jobTitle__(""),
			kind__(KIND::PERSON),
			lastName__(""),
			lastPhonetic__(""),
			middleName__(""),
			middlePhonetic__(""),
			modified__(""),
			nickname__(""),
			note__(""),
			organization__(""),
			phone__(Titanium::Contacts::create_empty_Phones(js_context)),
			prefix__(""),
			recordId__(js_context.CreateNull()),
			relatedNames__(Titanium::Contacts::create_empty_RelatedNames(js_context)),
			socialProfile__(Titanium::Contacts::create_empty_InstantMessages(js_context)),
			suffix__(""),
			url__(Titanium::Contacts::create_empty_Urls(js_context))
		{
		}

		TITANIUM_PROPERTY_READWRITE(Person, Addresses, address)
		TITANIUM_PROPERTY_READWRITE(Person, AlternateBirthday, alternateBirthday)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, birthday)
		TITANIUM_PROPERTY_READ(Person, std::string, created)
		TITANIUM_PROPERTY_READWRITE(Person, Dates, date)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, department)
		TITANIUM_PROPERTY_READWRITE(Person, Emails, email)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, firstName)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, firstPhonetic)
		TITANIUM_PROPERTY_WRITE(Person, std::string, fullName)
		std::string Person::get_fullName() const TITANIUM_NOEXCEPT
		{
			const auto middle = get_middleName();
			if (middle.empty()) {
				return get_firstName() + " " + get_lastName();
			}
			return get_firstName() + " " + middle + " " + get_lastName();
		}
		TITANIUM_PROPERTY_READ(Person, JSValue, id)
		TITANIUM_PROPERTY_READWRITE(Person, std::shared_ptr<Titanium::Blob>, image)
		TITANIUM_PROPERTY_READWRITE(Person, InstantMessages, instantMessage)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, jobTitle)
		TITANIUM_PROPERTY_READWRITE(Person, ::Titanium::Contacts::KIND, kind)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, lastName)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, lastPhonetic)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, middleName)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, middlePhonetic)
		TITANIUM_PROPERTY_READ(Person, std::string, modified)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, nickname)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, note)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, organization)
		TITANIUM_PROPERTY_READWRITE(Person, Phones, phone)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, prefix)
		TITANIUM_PROPERTY_READWRITE(Person, JSValue, recordId)
		TITANIUM_PROPERTY_READWRITE(Person, RelatedNames, relatedNames)
		TITANIUM_PROPERTY_READWRITE(Person, InstantMessages, socialProfile)
		TITANIUM_PROPERTY_READWRITE(Person, std::string, suffix)
		TITANIUM_PROPERTY_READWRITE(Person, Urls, url)

		void Person::JSExportInitialize() {
			JSExport<Person>::SetClassVersion(1);
			JSExport<Person>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(Person, address);
			TITANIUM_ADD_PROPERTY(Person, alternateBirthday);
			TITANIUM_ADD_PROPERTY(Person, birthday);
			TITANIUM_ADD_PROPERTY_READONLY(Person, created);
			TITANIUM_ADD_PROPERTY(Person, date);
			TITANIUM_ADD_PROPERTY(Person, department);
			TITANIUM_ADD_PROPERTY(Person, email);
			TITANIUM_ADD_PROPERTY(Person, firstName);
			TITANIUM_ADD_PROPERTY(Person, firstPhonetic);
			TITANIUM_ADD_PROPERTY(Person, fullName);
			TITANIUM_ADD_PROPERTY_READONLY(Person, id);
			TITANIUM_ADD_PROPERTY(Person, image);
			TITANIUM_ADD_PROPERTY(Person, instantMessage);
			TITANIUM_ADD_PROPERTY(Person, jobTitle);
			TITANIUM_ADD_PROPERTY(Person, kind);
			TITANIUM_ADD_PROPERTY(Person, lastName);
			TITANIUM_ADD_PROPERTY(Person, lastPhonetic);
			TITANIUM_ADD_PROPERTY(Person, middleName);
			TITANIUM_ADD_PROPERTY(Person, middlePhonetic);
			TITANIUM_ADD_PROPERTY_READONLY(Person, modified);
			TITANIUM_ADD_PROPERTY(Person, nickname);
			TITANIUM_ADD_PROPERTY(Person, note);
			TITANIUM_ADD_PROPERTY(Person, organization);
			TITANIUM_ADD_PROPERTY(Person, phone);
			TITANIUM_ADD_PROPERTY(Person, prefix);
			TITANIUM_ADD_PROPERTY(Person, recordId);
			TITANIUM_ADD_PROPERTY(Person, relatedNames);
			TITANIUM_ADD_PROPERTY(Person, socialProfile);
			TITANIUM_ADD_PROPERTY(Person, suffix);
			TITANIUM_ADD_PROPERTY(Person, url);

			TITANIUM_ADD_FUNCTION(Person, getAddress);
			TITANIUM_ADD_FUNCTION(Person, setAddress);
			TITANIUM_ADD_FUNCTION(Person, getAlternateBirthday);
			TITANIUM_ADD_FUNCTION(Person, setAlternateBirthday);
			TITANIUM_ADD_FUNCTION(Person, getBirthday);
			TITANIUM_ADD_FUNCTION(Person, setBirthday);
			TITANIUM_ADD_FUNCTION(Person, getCreated);
			TITANIUM_ADD_FUNCTION(Person, getDate);
			TITANIUM_ADD_FUNCTION(Person, setDate);
			TITANIUM_ADD_FUNCTION(Person, getDepartment);
			TITANIUM_ADD_FUNCTION(Person, setDepartment);
			TITANIUM_ADD_FUNCTION(Person, getEmail);
			TITANIUM_ADD_FUNCTION(Person, setEmail);
			TITANIUM_ADD_FUNCTION(Person, getFirstName);
			TITANIUM_ADD_FUNCTION(Person, setFirstName);
			TITANIUM_ADD_FUNCTION(Person, getFirstPhonetic);
			TITANIUM_ADD_FUNCTION(Person, setFirstPhonetic);
			TITANIUM_ADD_FUNCTION(Person, getFullName);
			TITANIUM_ADD_FUNCTION(Person, setFullName);
			TITANIUM_ADD_FUNCTION(Person, getId);
			TITANIUM_ADD_FUNCTION(Person, getImage);
			TITANIUM_ADD_FUNCTION(Person, setImage);
			TITANIUM_ADD_FUNCTION(Person, getInstantMessage);
			TITANIUM_ADD_FUNCTION(Person, setInstantMessage);
			TITANIUM_ADD_FUNCTION(Person, getJobTitle);
			TITANIUM_ADD_FUNCTION(Person, setJobTitle);
			TITANIUM_ADD_FUNCTION(Person, getKind);
			TITANIUM_ADD_FUNCTION(Person, setKind);
			TITANIUM_ADD_FUNCTION(Person, getLastName);
			TITANIUM_ADD_FUNCTION(Person, setLastName);
			TITANIUM_ADD_FUNCTION(Person, getLastPhonetic);
			TITANIUM_ADD_FUNCTION(Person, setLastPhonetic);
			TITANIUM_ADD_FUNCTION(Person, getMiddleName);
			TITANIUM_ADD_FUNCTION(Person, setMiddleName);
			TITANIUM_ADD_FUNCTION(Person, getMiddlePhonetic);
			TITANIUM_ADD_FUNCTION(Person, setMiddlePhonetic);
			TITANIUM_ADD_FUNCTION(Person, getModified);
			TITANIUM_ADD_FUNCTION(Person, getNickname);
			TITANIUM_ADD_FUNCTION(Person, setNickname);
			TITANIUM_ADD_FUNCTION(Person, getNote);
			TITANIUM_ADD_FUNCTION(Person, setNote);
			TITANIUM_ADD_FUNCTION(Person, getOrganization);
			TITANIUM_ADD_FUNCTION(Person, setOrganization);
			TITANIUM_ADD_FUNCTION(Person, getPhone);
			TITANIUM_ADD_FUNCTION(Person, setPhone);
			TITANIUM_ADD_FUNCTION(Person, getPrefix);
			TITANIUM_ADD_FUNCTION(Person, setPrefix);
			TITANIUM_ADD_FUNCTION(Person, getRecordId);
			TITANIUM_ADD_FUNCTION(Person, setRecordId);
			TITANIUM_ADD_FUNCTION(Person, getRelatedNames);
			TITANIUM_ADD_FUNCTION(Person, setRelatedNames);
			TITANIUM_ADD_FUNCTION(Person, getSocialProfile);
			TITANIUM_ADD_FUNCTION(Person, setSocialProfile);
			TITANIUM_ADD_FUNCTION(Person, getSuffix);
			TITANIUM_ADD_FUNCTION(Person, setSuffix);
			TITANIUM_ADD_FUNCTION(Person, getUrl);
			TITANIUM_ADD_FUNCTION(Person, setUrl);
		}

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, address, Addresses)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, address, Addresses)

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, alternateBirthday, AlternateBirthday)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, alternateBirthday, AlternateBirthday)

		// TODO Validate Date format is "yyyy-_MM_-ddTHH:mm:ss.SSS+0000"
		TITANIUM_PROPERTY_GETTER_STRING(Person, birthday);
		TITANIUM_PROPERTY_SETTER_STRING(Person, birthday);

		// TODO Return Date format is "yyyy-_MM_-ddTHH:mm:ss.SSS+0000"
		TITANIUM_PROPERTY_GETTER_STRING(Person, created);

		// TODO Validate Date format is "yyyy-_MM_-ddTHH:mm:ss.SSS+0000"
		TITANIUM_PROPERTY_GETTER_STRUCT(Person, date, Dates)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, date, Dates)

		TITANIUM_PROPERTY_GETTER_STRING(Person, department);
		TITANIUM_PROPERTY_SETTER_STRING(Person, department);

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, email, Emails)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, email, Emails)

		TITANIUM_PROPERTY_GETTER_STRING(Person, firstName);
		TITANIUM_PROPERTY_SETTER_STRING(Person, firstName);

		TITANIUM_PROPERTY_GETTER_STRING(Person, firstPhonetic);
		TITANIUM_PROPERTY_SETTER_STRING(Person, firstPhonetic);

		TITANIUM_PROPERTY_GETTER_STRING(Person, fullName);
		TITANIUM_PROPERTY_SETTER_STRING(Person, fullName);

		TITANIUM_PROPERTY_GETTER(Person, id)
		{
			return get_id();
		}

		TITANIUM_PROPERTY_GETTER_OBJECT(Person, image)
		TITANIUM_PROPERTY_SETTER_OBJECT(Person, image, Blob)

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, instantMessage, InstantMessages)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, instantMessage, InstantMessages)

		TITANIUM_PROPERTY_GETTER_STRING(Person, jobTitle);
		TITANIUM_PROPERTY_SETTER_STRING(Person, jobTitle);

		TITANIUM_PROPERTY_GETTER_ENUM(Person, kind);
		TITANIUM_PROPERTY_SETTER_ENUM(Person, kind, KIND);

		TITANIUM_PROPERTY_GETTER_STRING(Person, lastName);
		TITANIUM_PROPERTY_SETTER_STRING(Person, lastName);

		TITANIUM_PROPERTY_GETTER_STRING(Person, lastPhonetic);
		TITANIUM_PROPERTY_SETTER_STRING(Person, lastPhonetic);

		TITANIUM_PROPERTY_GETTER_STRING(Person, middleName);
		TITANIUM_PROPERTY_SETTER_STRING(Person, middleName);

		TITANIUM_PROPERTY_GETTER_STRING(Person, middlePhonetic);
		TITANIUM_PROPERTY_SETTER_STRING(Person, middlePhonetic);

		TITANIUM_PROPERTY_GETTER_STRING(Person, modified);

		TITANIUM_PROPERTY_GETTER_STRING(Person, nickname);
		TITANIUM_PROPERTY_SETTER_STRING(Person, nickname);

		TITANIUM_PROPERTY_GETTER_STRING(Person, note);
		TITANIUM_PROPERTY_SETTER_STRING(Person, note);

		TITANIUM_PROPERTY_GETTER_STRING(Person, organization);
		TITANIUM_PROPERTY_SETTER_STRING(Person, organization);

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, phone, Phones)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, phone, Phones)

		TITANIUM_PROPERTY_GETTER_STRING(Person, prefix);
		TITANIUM_PROPERTY_SETTER_STRING(Person, prefix);

		TITANIUM_PROPERTY_GETTER(Person, recordId)
		{
			return get_recordId();
		}

		TITANIUM_PROPERTY_SETTER(Person, recordId)
		{
			set_recordId(argument);
			return true;
		}

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, relatedNames, RelatedNames)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, relatedNames, RelatedNames)

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, socialProfile, InstantMessages)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, socialProfile, InstantMessages)

		TITANIUM_PROPERTY_GETTER_STRING(Person, suffix);
		TITANIUM_PROPERTY_SETTER_STRING(Person, suffix);

		TITANIUM_PROPERTY_GETTER_STRUCT(Person, url, Urls)
		TITANIUM_PROPERTY_SETTER_STRUCT(Person, url, Urls)

		TITANIUM_FUNCTION_AS_GETTER(Person, getAddress, address)
		TITANIUM_FUNCTION_AS_SETTER(Person, setAddress, address)

		TITANIUM_FUNCTION_AS_GETTER(Person, getAlternateBirthday, alternateBirthday)
		TITANIUM_FUNCTION_AS_SETTER(Person, setAlternateBirthday, alternateBirthday)

		TITANIUM_FUNCTION_AS_GETTER(Person, getBirthday, birthday)
		TITANIUM_FUNCTION_AS_SETTER(Person, setBirthday, birthday)

		TITANIUM_FUNCTION_AS_GETTER(Person, getCreated, created)

		TITANIUM_FUNCTION_AS_GETTER(Person, getDate, date)
		TITANIUM_FUNCTION_AS_SETTER(Person, setDate, date)

		TITANIUM_FUNCTION_AS_GETTER(Person, getDepartment, department)
		TITANIUM_FUNCTION_AS_SETTER(Person, setDepartment, department)

		TITANIUM_FUNCTION_AS_GETTER(Person, getEmail, email)
		TITANIUM_FUNCTION_AS_SETTER(Person, setEmail, email)

		TITANIUM_FUNCTION_AS_GETTER(Person, getFirstName, firstName)
		TITANIUM_FUNCTION_AS_SETTER(Person, setFirstName, firstName)

		TITANIUM_FUNCTION_AS_GETTER(Person, getFirstPhonetic, firstPhonetic)
		TITANIUM_FUNCTION_AS_SETTER(Person, setFirstPhonetic, firstPhonetic)

		TITANIUM_FUNCTION_AS_GETTER(Person, getFullName, fullName)
		TITANIUM_FUNCTION_AS_SETTER(Person, setFullName, fullName)

		TITANIUM_FUNCTION_AS_GETTER(Person, getId, id)

		TITANIUM_FUNCTION_AS_GETTER(Person, getImage, image)
		TITANIUM_FUNCTION_AS_SETTER(Person, setImage, image)

		TITANIUM_FUNCTION_AS_GETTER(Person, getInstantMessage, instantMessage)
		TITANIUM_FUNCTION_AS_SETTER(Person, setInstantMessage, instantMessage)

		TITANIUM_FUNCTION_AS_GETTER(Person, getJobTitle, jobTitle)
		TITANIUM_FUNCTION_AS_SETTER(Person, setJobTitle, jobTitle)

		TITANIUM_FUNCTION_AS_GETTER(Person, getKind, kind)
		TITANIUM_FUNCTION_AS_SETTER(Person, setKind, kind)

		TITANIUM_FUNCTION_AS_GETTER(Person, getLastName, lastName)
		TITANIUM_FUNCTION_AS_SETTER(Person, setLastName, lastName)

		TITANIUM_FUNCTION_AS_GETTER(Person, getLastPhonetic, lastPhonetic)
		TITANIUM_FUNCTION_AS_SETTER(Person, setLastPhonetic, lastPhonetic)

		TITANIUM_FUNCTION_AS_GETTER(Person, getMiddleName, middleName)
		TITANIUM_FUNCTION_AS_SETTER(Person, setMiddleName, middleName)

		TITANIUM_FUNCTION_AS_GETTER(Person, getMiddlePhonetic, middlePhonetic)
		TITANIUM_FUNCTION_AS_SETTER(Person, setMiddlePhonetic, middlePhonetic)

		TITANIUM_FUNCTION_AS_GETTER(Person, getModified, modified)

		TITANIUM_FUNCTION_AS_GETTER(Person, getNickname, nickname)
		TITANIUM_FUNCTION_AS_SETTER(Person, setNickname, nickname)

		TITANIUM_FUNCTION_AS_GETTER(Person, getNote, note)
		TITANIUM_FUNCTION_AS_SETTER(Person, setNote, note)

		TITANIUM_FUNCTION_AS_GETTER(Person, getOrganization, organization)
		TITANIUM_FUNCTION_AS_SETTER(Person, setOrganization, organization)

		TITANIUM_FUNCTION_AS_GETTER(Person, getPhone, phone)
		TITANIUM_FUNCTION_AS_SETTER(Person, setPhone, phone)

		TITANIUM_FUNCTION_AS_GETTER(Person, getPrefix, prefix)
		TITANIUM_FUNCTION_AS_SETTER(Person, setPrefix, prefix)

		TITANIUM_FUNCTION_AS_GETTER(Person, getRecordId, recordId)
		TITANIUM_FUNCTION_AS_SETTER(Person, setRecordId, recordId)

		TITANIUM_FUNCTION_AS_GETTER(Person, getRelatedNames, relatedNames)
		TITANIUM_FUNCTION_AS_SETTER(Person, setRelatedNames, relatedNames)

		TITANIUM_FUNCTION_AS_GETTER(Person, getSocialProfile, socialProfile)
		TITANIUM_FUNCTION_AS_SETTER(Person, setSocialProfile, socialProfile)

		TITANIUM_FUNCTION_AS_GETTER(Person, getSuffix, suffix)
		TITANIUM_FUNCTION_AS_SETTER(Person, setSuffix, suffix)

		TITANIUM_FUNCTION_AS_GETTER(Person, getUrl, url)
		TITANIUM_FUNCTION_AS_SETTER(Person, setUrl, url)

	} // namespace Contacts
} // namespace Titanium