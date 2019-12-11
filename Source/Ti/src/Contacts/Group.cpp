/**
 * Titanium.Contacts.Group for Windows
 *
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Contacts.hpp"
#include <memory>
#include <windows.h>
#include <memory>
#include "TitaniumWindows/Contacts/Group.hpp"
#include "TitaniumWindows/Contacts/Person.hpp"
#include "TitaniumWindows/Contacts/group_js.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

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

		void Group::JSExportInitialize()
		{
			JSExport<Group>::SetClassVersion(1);
			JSExport<Group>::SetParent(JSExport<Titanium::Contacts::Group>::Class());
		}

		void Group::add(const std::shared_ptr<Titanium::Contacts::Person>& person) TITANIUM_NOEXCEPT
		{
			if (!js_instance__.IsNull() && js_instance__.IsObject()) {
				// Call out to "add" method on instance of group we've created
				auto obj = static_cast<JSObject>(js_instance__);
				auto add_func = obj.GetProperty("add");
				static_cast<JSObject>(add_func)(static_cast<JSValue>(person->get_object()), obj);
			}
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Person>> Group::members() TITANIUM_NOEXCEPT
		{
			if (!js_instance__.IsNull() && js_instance__.IsObject()) {
				// Call out to "members" method on instance of group we've created
				auto obj = static_cast<JSObject>(js_instance__);
				auto members_func = obj.GetProperty("members");
				auto result = static_cast<JSObject>(members_func)(obj);
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
			if (!js_instance__.IsNull() && js_instance__.IsObject()) {
				// Call out to "remove" method on instance of group we've created
				auto obj = static_cast<JSObject>(js_instance__);
				auto remove_func = obj.GetProperty("remove");
				static_cast<JSObject>(remove_func)(static_cast<JSValue>(person->get_object()), obj);
			}
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Person>> Group::sortedMembers(const Titanium::Contacts::SORT& sortBy) TITANIUM_NOEXCEPT
		{
			// See https://msdn.microsoft.com/en-us/library/windows/apps/windows.applicationmodel.contacts.contactnameorder.aspx
			// https://msdn.microsoft.com/en-us/library/windows/apps/windows.applicationmodel.contacts.contactmanager.systemsortorder.aspx
			TITANIUM_MODULE_LOG_WARN("Group::sortedMembers: Unimplemented");
			// TODO Just grab all the members and sort them ourself?
			return members();
		}

		std::string Group::get_identifier() const TITANIUM_NOEXCEPT
		{
			if (!js_instance__.IsNull() && js_instance__.IsObject()) {
				auto obj = static_cast<JSObject>(js_instance__);
				auto value = obj.GetProperty("identifier");
				if (value.IsString()) {
					return static_cast<std::string>(value);
				}
			}
			return Titanium::Contacts::Group::get_identifier();
		}

		std::string Group::get_name() const TITANIUM_NOEXCEPT
		{
			if (!js_instance__.IsNull() && js_instance__.IsObject()) {
				auto obj = static_cast<JSObject>(js_instance__);
				auto name_value = obj.GetProperty("name");
				return static_cast<std::string>(name_value);
			}
			return Titanium::Contacts::Group::get_name();
		}

		void Group::set_name(const std::string& name) TITANIUM_NOEXCEPT
		{
			Titanium::Contacts::Group::set_name(name);
			if (!js_instance__.IsNull() && js_instance__.IsObject()) {
				auto obj = static_cast<JSObject>(js_instance__);
				obj.SetProperty("name", get_context().CreateString(name));
			}
		}

		void Group::set_recordId(const uint32_t& recordId) TITANIUM_NOEXCEPT
		{
			TITANIUM_MODULE_LOG_WARN("Group::recordId property is read-only");
		}

		JSObject Group::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
		{
			static JSObject cached = js_context.CreateObject();
			static std::once_flag of;
			std::call_once(of, [=] {
				auto Titanium_property = js_context.get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
				auto Titanium = static_cast<JSObject>(Titanium_property);

				auto Contacts_property = Titanium.GetProperty("Contacts");
				TITANIUM_ASSERT(Contacts_property.IsObject());  // precondition
				auto Contacts = static_cast<JSObject>(Contacts_property);

				auto Group_property = Contacts.GetProperty("Group");
				TITANIUM_ASSERT(Group_property.IsObject());  // precondition
				cached = static_cast<JSObject>(Group_property);
			});
			return cached;
		}

		std::vector<std::shared_ptr<Titanium::Contacts::Group>> Group::getAllGroups(const JSContext& js_context) TITANIUM_NOEXCEPT
		{
			std::vector<std::shared_ptr<Titanium::Contacts::Group>> all_groups;
			auto GroupType = GetStaticObject(js_context);
			const auto group = GroupType.GetPrivate<Group>();

			// lazy loading
			const auto loaded = group->loadJS();
			if (loaded) {
				auto getAllGroups_func = group->getTiObject().GetProperty("getAllGroups");
				auto js_groups = static_cast<JSObject>(getAllGroups_func)(js_context.get_global_object());
				ENSURE_ARRAY(js_groups, js_groups_array);
				auto js_groups_vector = static_cast<std::vector<JSValue>>(js_groups_array);
				// We need to wrap the group in a Ti.Contacts.Group instance!
				for (auto js_group : js_groups_vector) {
					if (js_group.IsNull() || js_group.IsUndefined()) {
						continue;
					}
					auto instance = GroupType.CallAsConstructor();
					auto win_group = instance.GetPrivate<TitaniumWindows::Contacts::Group>();
					win_group->js_instance__ = js_group;
					all_groups.push_back(win_group);
				}
			}
			else {
				TITANIUM_LOG_ERROR("Failed to execute Ti.Contacts.getAllGroups");
			}
			return all_groups;
		}

		std::shared_ptr<Titanium::Contacts::Group> Group::getGroupByIdentifier(const std::string& id, const JSContext& js_context) TITANIUM_NOEXCEPT
		{
			auto GroupType = GetStaticObject(js_context);
			const auto group = GroupType.GetPrivate<Group>();

			// lazy loading
			const auto loaded = group->loadJS();
			if (loaded) {
				auto getGroupByIdentifier_func = group->getTiObject().GetProperty("getGroupByIdentifier");
				auto js_group = static_cast<JSObject>(getGroupByIdentifier_func)(js_context.CreateString(id), js_context.get_global_object());
				if (js_group.IsNull() || js_group.IsUndefined()) {
					return nullptr;
				}
				// We need to generate a new Ti.Contacts.Group, then set the js_instance__ on it!
				auto instance = GroupType.CallAsConstructor();
				auto win_group = instance.GetPrivate<TitaniumWindows::Contacts::Group>();
				win_group->js_instance__ = js_group;
				return win_group;
			}
			else {
				TITANIUM_LOG_ERROR("Failed to execute Ti.Contacts.getGroupByIdentifier");
			}
			return nullptr;
		}

		void Group::create()
		{
			const auto js_context = get_context();
			auto GroupType = GetStaticObject(js_context);
			const auto group = GroupType.GetPrivate<Group>();

			// lazy loading
			const auto loaded = group->loadJS();
			if (loaded) {
				auto create_func = group->getTiObject().GetProperty("create");
				js_instance__ = static_cast<JSObject>(create_func)(js_context.CreateString(get_name()), js_context.get_global_object());
			}
			else {
				TITANIUM_LOG_ERROR("Failed to execute Ti.Contacts.createGroup");
			}
		}

		void Group::removeList()
		{
			if (!js_instance__.IsNull() && js_instance__.IsObject()) {
				auto obj = static_cast<JSObject>(js_instance__);
				auto destroy_func = obj.GetProperty("destroy");
				static_cast<JSObject>(destroy_func)(obj);
				js_instance__ = get_context().CreateNull();
			}
		}
	}  // namespace Contacts
}  // namespace TitaniumWindows
