/**
 * Titanium.Contacts.Group for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_GROUP_HPP_
#define _TITANIUMWINDOWS_GROUP_HPP_

#include "TitaniumWindows_Ti_EXPORT.h"
#include "Titanium/Contacts/Group.hpp"

namespace TitaniumWindows
{
	namespace Contacts
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.Contacts.Group implementation for Windows.
		*/
		class TITANIUMWINDOWS_TI_EXPORT Group final : public Titanium::Contacts::Group, public JSExport<Group>
		{

		public:
			
			Group(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~Group()               = default;
			Group(const Group&)            = default;
			Group& operator=(const Group&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Group(Group&&)                 = default;
			Group& operator=(Group&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

#if (WINVER >= 0x0A00)
// Windows 10+ API!
			void construct(Windows::ApplicationModel::Contacts::ContactList^ list);
#endif

			void removeList();

			virtual void add(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT;
			virtual std::vector<std::shared_ptr<Titanium::Contacts::Person>> members() TITANIUM_NOEXCEPT;
			virtual void remove(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT;
			virtual std::vector<std::shared_ptr<Titanium::Contacts::Person>> sortedMembers(const Titanium::Contacts::SORT& sortBy) TITANIUM_NOEXCEPT override final;

			virtual JSValue get_identifier() const TITANIUM_NOEXCEPT override final;
			virtual std::string get_name() const TITANIUM_NOEXCEPT override final;
			virtual void set_name(const std::string&) TITANIUM_NOEXCEPT override final;
			virtual void set_recordId(const uint32_t&) TITANIUM_NOEXCEPT override final;

		private:
#if (WINVER >= 0x0A00)
// Windows 10+ API!
			Windows::ApplicationModel::Contacts::ContactList^ contact_list__;
#endif
		};
	}  // namespace Contacts
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_GROUP_HPP_