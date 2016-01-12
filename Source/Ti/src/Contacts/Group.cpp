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
#include "TitaniumWindows/Contacts/group_js.hpp"
#include <memory>

namespace TitaniumWindows
{
	namespace Contacts
	{

		Group::Group(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::Contacts::Group(js_context, arguments),
			  ti_contacts_group__(js_context.CreateObject()),
			  js_instance__(js_context.CreateNull())
		{
			TITANIUM_LOG_DEBUG("Group::ctor Initialize");
		}

		bool Group::loadJS()
		{
			if (ti_contacts_group__.HasProperty("getAllGroups")) {
				return true;
			}

			JSContext context = get_context();
			auto export_object = context.CreateObject();
			export_object.SetProperty("global", context.get_global_object());

			context.JSEvaluateScript(group_js, export_object);

			if (export_object.HasProperty("exports")) {
				ti_contacts_group__ = static_cast<JSObject>(export_object.GetProperty("exports"));
			}
			else {
				return false;
			}
			return true;
		}

		void Group::JSExportInitialize() {
			JSExport<Group>::SetClassVersion(1);
			JSExport<Group>::SetParent(JSExport<Titanium::Contacts::Group>::Class());
		}

		void Group::add(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
		{
			if (!static_cast<JSValue>(js_instance__).IsNull()) {
				// Call out to "add" method on instance of group we've created
				auto add_func = js_instance__.GetProperty("add");
				static_cast<JSObject>(add_func)(static_cast<JSValue>(person->get_object()), js_instance__);
			}
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Person>> Group::members() TITANIUM_NOEXCEPT
		{
			if (!static_cast<JSValue>(js_instance__).IsNull()) {
				// Call out to "members" method on instance of group we've created
				auto members_func = js_instance__.GetProperty("members");
				auto result = static_cast<JSObject>(members_func)(js_instance__);
				if (result.IsObject()) {
					auto result_object = static_cast<JSObject>(result);
					if (result_object.IsArray()) {
						auto result_array = static_cast<JSArray>(result_object);
						return result_array.GetPrivateItems<Titanium::Contacts::Person>();
					}
				}
			}
			return std::vector<std::shared_ptr<Titanium::Contacts::Person>>();
		}

		void Group::remove(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
		{
			if (!static_cast<JSValue>(js_instance__).IsNull()) {
				// Call out to "remove" method on instance of group we've created
				auto remove_func = js_instance__.GetProperty("remove");
				static_cast<JSObject>(remove_func)(static_cast<JSValue>(person->get_object()), js_instance__);
			}
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Person>> Group::sortedMembers(const Titanium::Contacts::SORT& sortBy) TITANIUM_NOEXCEPT
		{
			// See https://msdn.microsoft.com/en-us/library/windows/apps/windows.applicationmodel.contacts.contactnameorder.aspx
			// https://msdn.microsoft.com/en-us/library/windows/apps/windows.applicationmodel.contacts.contactmanager.systemsortorder.aspx
			TITANIUM_LOG_WARN("Group::sortedMembers: Unimplemented");
			// TODO Just grab all the members and sort them ourself?
			return members();
		}

		JSValue Group::get_identifier() const TITANIUM_NOEXCEPT
		{
			if (!static_cast<JSValue>(js_instance__).IsNull()) {
				return js_instance__.GetProperty("identifier");
			}
			return Titanium::Contacts::Group::get_identifier();
		}

		std::string Group::get_name() const TITANIUM_NOEXCEPT
		{
			if (!static_cast<JSValue>(js_instance__).IsNull()) {
				auto name_value = js_instance__.GetProperty("name");
				return static_cast<std::string>(name_value);
			}
			return Titanium::Contacts::Group::get_name();
		}

		void Group::set_name(const std::string& name) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Group::set_name(name);
			if (!static_cast<JSValue>(js_instance__).IsNull()) {
				js_instance__.SetProperty("name", get_context().CreateString(name));
			}
		}

		void Group::set_recordId(const uint32_t& recordId) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Group::recordId property is read-only");
		}

		JSObject Group::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
		{
			auto Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			auto Titanium = static_cast<JSObject>(Titanium_property);

			auto Contacts_property = Titanium.GetProperty("Contacts");
			TITANIUM_ASSERT(Contacts_property.IsObject());  // precondition
			auto Contacts = static_cast<JSObject>(Contacts_property);

			auto Group_property = Titanium.GetProperty("Group");
			TITANIUM_ASSERT(Group_property.IsObject());  // precondition
			return static_cast<JSObject>(Group_property);
		}

		std::shared_ptr<Titanium::Contacts::Group> Group::getAllGroups(const JSContext& js_context) TITANIUM_NOEXCEPT
		{
			std::vector<std::shared_ptr<Titanium::Contacts::Group>> all_groups;
			const auto GroupType = GetStaticObject(js_context);
			const auto group = GroupType.GetPrivate<Group>();

			// lazy loading
			const auto loaded = group->loadJS();
			if (loaded) {
				auto getAllGroups_func = ti_contacts_group__.GetProperty("getAllGroups");
				auto groups = static_cast<JSObject>(getAllGroups_func)(js_context.get_global_object());
				// We need to wrap the group in a Ti.Contacts.Group instance!
				for (auto group_obj in groups) {
					auto instance = GroupType.CallAsConstructor();
					auto win_group = instance.GetPrivate<TitaniumWindows::Contacts::Group>();
					win_group.js_instance__ = group_obj;
					all_groups.push_back(win_group);
				}
			}
			else {
				TITANIUM_LOG_ERROR("Failed to execute Ti.Contacts.getAllGroups");
			}
			return all_groups;
		}

		std::shared_ptr<Titanium::Contacts::Group> Group::getGroupByIdentifier(const JSValue& id, const JSContext& js_context) TITANIUM_NOEXCEPT
		{
			const auto GroupType = GetStaticObject(js_context);
			const auto group = GroupType.GetPrivate<Group>();

			// lazy loading
			const auto loaded = group->loadJS();
			if (loaded) {
				auto getGroupByIdentifier_func = ti_contacts_group__.GetProperty("getGroupByIdentifier");
				auto result_group = static_cast<JSObject>(getGroupByIdentifier_func)(id, js_context.get_global_object());
				// TODO We need to generate a new Ti.Contacts.Group, then set the js_instance__ on it!
				auto instance = GroupType.CallAsConstructor();
				auto win_group = instance.GetPrivate<TitaniumWindows::Contacts::Group>();
				win_group.js_instance__ = result_group;
				return win_group;
			}
			else {
				TITANIUM_LOG_ERROR("Failed to execute Ti.Contacts.getGroupByIdentifier");
			}
			return nullptr;
		}

		void Group::create()
		{
			const auto group = GetStaticObject(get_context()).GetPrivate<Group>();

			// lazy loading
			const auto loaded = group->loadJS();
			if (loaded) {
				auto create_func = ti_contacts_group__.GetProperty("create");
				static_cast<JSObject>(create_func)(get_context().CreateString(get_name()), js_instance__);
			}
			else {
				TITANIUM_LOG_ERROR("Failed to execute Ti.Contacts.createGroup");
			}
		}

		void Group::removeList()
		{
			if (!static_cast<JSValue>(js_instance__).IsNull()) {
				auto destroy_func = js_instance__.GetProperty("destroy");
				static_cast<JSObject>(destroy_func)(js_instance__);
			}
		}
	}  // namespace Contacts
}  // namespace TitaniumWindows
