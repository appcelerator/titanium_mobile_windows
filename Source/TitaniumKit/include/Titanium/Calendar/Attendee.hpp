/**
 * TitaniumKit Titanium.Calendar.Attendee
 *
 * Copyright (c) 2019 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_CALENDAR_ATTENDEE_HPP_
#define _TITANIUM_CALENDAR_ATTENDEE_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Calendar/Constants.hpp"

namespace Titanium
{
	namespace Calendar
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Attendee Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Calendar.Attendee
		*/
		class TITANIUMKIT_EXPORT Attendee : public Module, public JSExport<Attendee>
		{

		public:

			Attendee(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Attendee()               = default;
			Attendee(const Attendee&)            = default;
			Attendee& operator=(const Attendee&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Attendee(Attendee&&)                 = default;
			Attendee& operator=(Attendee&&)      = default;
#endif

			static void JSExportInitialize();

			/*!
			  @property
			  @abstract email
			  @discussion The attendee email.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(email);
			TITANIUM_PROPERTY_IMPL_DEF(std::string, email);

			/*!
			  @property
			  @abstract isOrganizer
			  @discussion Indicates whether this attendee is the event organizer.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(isOrganizer);
			TITANIUM_PROPERTY_IMPL_DEF(bool, isOrganizer);

			/*!
			  @property
			  @abstract name
			  @discussion The attendee name.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(name);
			TITANIUM_PROPERTY_IMPL_DEF(std::string, name);

			/*!
			  @property
			  @abstract role
			  @discussion The role of the attendee.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(role);
			TITANIUM_PROPERTY_IMPL_DEF(Titanium::Calendar::ATTENDEE_ROLE, role);

			/*!
			  @property
			  @abstract status
			  @discussion The status of the attendee.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(status);
			TITANIUM_PROPERTY_IMPL_DEF(Titanium::Calendar::ATTENDEE_STATUS, status);

			/*!
			  @property
			  @abstract type
			  @discussion The type of the attendee.
			*/
			TITANIUM_PROPERTY_READONLY_DEF(type);
			TITANIUM_PROPERTY_IMPL_DEF(Titanium::Calendar::ATTENDEE_TYPE, type);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string email__;
			std::string name__;
			bool isOrganizer__;
			Titanium::Calendar::ATTENDEE_ROLE role__;
			Titanium::Calendar::ATTENDEE_STATUS status__;
			Titanium::Calendar::ATTENDEE_TYPE type__;
#pragma warning(pop)
		};

	} // namespace Calendar
} // namespace Titanium
#endif // _TITANIUM_CALENDAR_ATTENDEE_HPP_