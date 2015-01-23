/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Module.hpp"
#include <cstdint>

namespace Titanium
{
	Module::Module(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : JSExportObject(js_context),
	      event_listener_map__(js_context.CreateObject())
	{
		TITANIUM_LOG_DEBUG("Module:: ctor 1 ", this);
	}

	Module::Module(const Module& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : JSExportObject(rhs.get_context(), arguments),
	      event_listener_map__(get_context().CreateObject())
	{
		TITANIUM_LOG_DEBUG("Module:: ctor 2 ", this);
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			if (_0.IsObject()) {
				JSObject properties = static_cast<JSObject>(_0);
				TITANIUM_LOG_DEBUG("Module:: ctor 2 has ", properties.GetPropertyNames().GetCount(), " properties for ", this);
			}
		}
	}

	Module::~Module() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Module:: dtor ", this);
	}

	void Module::addEventListener(const std::string& name, JSObject& callback, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Module::addEventListener: '", name, "' for ", this);
		if (!callback.IsFunction()) {
			TITANIUM_LOG_WARN("Module::addEventListener: Listener is not a function for event '", name, "'");
			return;
		}

		JSObject event_listener_list = get_context().CreateArray();
		if (!event_listener_map__.HasProperty(name)) {
			event_listener_map__.SetProperty(name, event_listener_list);
		} else {
			JSValue event_listener_list_property = event_listener_map__.GetProperty(name);
			// precondition
			TITANIUM_ASSERT(event_listener_list_property.IsObject());
			event_listener_list = static_cast<JSObject>(event_listener_list_property);
		}

		JSObject callback_payload = get_context().CreateObject();
		callback_payload.SetProperty("callback", callback);
		callback_payload.SetProperty("this_object", this_object);

		// Precondition
		const auto event_listener_index = eventListenerIndex(event_listener_list, name, callback_payload);
		if (event_listener_index > 0) {
			TITANIUM_LOG_WARN("Module::addEventListener: event listener already added at index ", event_listener_index, " for event '", name, "'");
		} else {
			const auto callback_list_index = event_listener_list.GetPropertyNames().GetCount();
			if (callback_list_index == 0) {
				// This is the first event listener for this event name, so signal
				// module subclasses that callbacks have been registered for this event.
				enableEvent(name);
			}
			TITANIUM_LOG_DEBUG("Module::addEventListener: add listener at index ", callback_list_index, " for event '", name, "' for ", this);
			event_listener_list.SetProperty(static_cast<unsigned>(callback_list_index), callback_payload);
		}
	}

	void Module::removeEventListener(const std::string& name, JSObject& callback, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Module::removeEventListener: '", name, "' for ", this);
		if (!callback.IsFunction()) {
			TITANIUM_LOG_WARN("Module::removeEventListener: callback is not a function for event '", name, "'");
			return;
		}

		if (!event_listener_map__.HasProperty(name)) {
			TITANIUM_LOG_WARN("Module::removeEventListener: No event listener's for event '", name, "'");
			return;
		}

		JSValue event_listener_list_property = event_listener_map__.GetProperty(name);

		// precondition
		TITANIUM_ASSERT(event_listener_list_property.IsObject());
		JSObject event_listener_list = static_cast<JSObject>(event_listener_list_property);

		JSObject callback_payload = get_context().CreateObject();
		callback_payload.SetProperty("callback", callback);
		callback_payload.SetProperty("this_object", this_object);

		const auto event_listener_count = event_listener_list.GetPropertyNames().GetCount();
		if (event_listener_count > 0) {
			const auto event_listener_index = eventListenerIndex(event_listener_list, name, callback_payload);

			if (event_listener_count == 1) {
				// This is the last event listener for this event name, and it is about
				// to be removed, so signal module subclasses that there are no more
				// callbacks registered for this event.
				disableEvent(name);
			}

			TITANIUM_LOG_DEBUG("Module::removeEventListener: remove listener at index ", event_listener_index, " for event '", name, "' for ", this);

			// postcondition
			const bool deleted = event_listener_list.DeleteProperty(std::to_string(event_listener_index));
			if (!deleted) {
				// This is a TitaniumKit logic error.
				TITANIUM_LOG_ERROR("Module::removeEventListener: event listener at index ", event_listener_index, " for event '", name, "' was not removed");
				TITANIUM_ASSERT(deleted);
			}
		} else {
			TITANIUM_LOG_WARN("Module::removeEventListener: listener does not exist for event '", name, "'");
		}
	}

	void Module::applyProperties(const JSObject& props, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Module::applyProperties: Unimplemented");
		for (const auto& property_name : static_cast<std::vector<JSString>>(props.GetPropertyNames())) {
			this_object.SetProperty(property_name, props.GetProperty(property_name));
		}
	}

	void Module::fireEvent(const std::string& name, const JSObject& event) const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Module::fireEvent: '", name, "' for ", this);

		if (!event_listener_map__.HasProperty(name)) {
			TITANIUM_LOG_WARN("Module::fireEvent: No event named '", name, "' has been added");
			return;
		}

		JSValue event_listener_list_property = event_listener_map__.GetProperty(name);
		// Precondition
		TITANIUM_ASSERT(event_listener_list_property.IsObject());
		JSObject event_listener_list = static_cast<JSObject>(event_listener_list_property);
		const auto event_listener_count = event_listener_list.GetPropertyNames().GetCount();

		if (event_listener_count == 0) {
			TITANIUM_LOG_WARN("Module::fireEvent: No listeners for event '", name, "'");
			return;
		}

		for (unsigned i = 0; i < event_listener_count; ++i) {
			JSValue callback_payload_property = event_listener_list.GetProperty(i);

			// Precondition
			TITANIUM_ASSERT(callback_payload_property.IsObject());
			JSObject callback_payload = static_cast<JSObject>(callback_payload_property);

			JSValue callback_property = callback_payload.GetProperty("callback");

			// Precondition
			TITANIUM_ASSERT(callback_property.IsObject());
			JSObject callback = static_cast<JSObject>(callback_property);

			// Precondition
			TITANIUM_ASSERT(callback.IsFunction());

			JSValue this_object_property = callback_payload.GetProperty("this_object");

			// Precondition
			TITANIUM_ASSERT(this_object_property.IsObject());
			JSObject this_object = static_cast<JSObject>(this_object_property);

			TITANIUM_LOG_DEBUG("Module::fireEvent: name = '", name, "' for listener at index ", i, " for ", this);
			callback({static_cast<JSValue>(event)}, this_object);
		}
	}

	void Module::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Module::enableEvent: Unimplemented (event name '", event_name, "' for ", this);
	}

	void Module::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Module::disableEvent: Unimplemented (event name '", event_name, "' for ", this);
	}

	unsigned Module::eventListenerIndex(const JSObject& event_listener_list, const std::string& name, JSObject& callback) TITANIUM_NOEXCEPT
	{
		unsigned index = 0;
		bool found = false;
		const auto event_listener_count = event_listener_list.GetPropertyNames().GetCount();
		for (unsigned i = 0; i < event_listener_count; ++i) {
			JSValue callback_payload_property = event_listener_list.GetProperty(i);

			// Precondition
			TITANIUM_ASSERT(callback_payload_property.IsObject());
			JSObject callback_payload = static_cast<JSObject>(callback_payload_property);

			JSValue callback_property = callback_payload.GetProperty("callback");
			if (callback == callback_property) {
				// precondition
				if (found) {
					// This is a TitaniumKit logic error.
					TITANIUM_LOG_ERROR("Module::eventListenerIndex: multiple identical listeners found for event = '", name, "'");
				}

				index = i;
				found = true;
			}
		}

		TITANIUM_LOG_ERROR("Module::eventListenerIndex: index = ", index, " for event '", name, "'");
		return index;
	}

	// TODO: The following functions can automatically be generated from
	// the YAML API docs.

	void Module::JSExportInitialize()
	{
		JSExport<Module>::SetClassVersion(1);
		JSExport<Module>::SetParent(JSExport<JSExportObject>::Class());
		JSExport<Module>::AddFunctionProperty("addEventListener", std::mem_fn(&Module::js_addEventListener));
		JSExport<Module>::AddFunctionProperty("removeEventListener", std::mem_fn(&Module::js_removeEventListener));
		JSExport<Module>::AddFunctionProperty("applyProperties", std::mem_fn(&Module::js_applyProperties));
		JSExport<Module>::AddFunctionProperty("fireEvent", std::mem_fn(&Module::js_fireEvent));
	}

	JSValue Module::js_addEventListener(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		TITANIUM_ASSERT(arguments.size() >= 2);
		const auto _0 = arguments.at(0);
		const auto _1 = arguments.at(1);
		TITANIUM_ASSERT(_0.IsString());
		TITANIUM_ASSERT(_1.IsObject());
		std::string name = static_cast<std::string>(_0);
		JSObject callback = static_cast<JSObject>(_1);
		TITANIUM_ASSERT(callback.IsFunction());
		addEventListener(name, callback, this_object);
		return get_context().CreateUndefined();
	}

	JSValue Module::js_removeEventListener(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		TITANIUM_ASSERT(arguments.size() >= 2);
		const auto _0 = arguments.at(0);
		const auto _1 = arguments.at(1);
		TITANIUM_ASSERT(_0.IsString());
		TITANIUM_ASSERT(_1.IsObject());
		std::string name = static_cast<std::string>(_0);
		JSObject callback = static_cast<JSObject>(_1);
		TITANIUM_ASSERT(callback.IsFunction());
		removeEventListener(name, callback, this_object);
		return get_context().CreateUndefined();
	}

	JSValue Module::js_applyProperties(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		TITANIUM_ASSERT(arguments.size() >= 1);
		const auto _0 = arguments.at(0);
		TITANIUM_ASSERT(_0.IsObject());
		JSObject props = static_cast<JSObject>(_0);
		applyProperties(props, this_object);
		return get_context().CreateUndefined();
	}

	JSValue Module::js_fireEvent(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		TITANIUM_ASSERT(arguments.size() >= 2);
		const auto _0 = arguments.at(0);
		const auto _1 = arguments.at(1);
		TITANIUM_ASSERT(_0.IsString());
		TITANIUM_ASSERT(_1.IsObject());
		std::string name = static_cast<std::string>(_0);
		JSObject event = static_cast<JSObject>(_1);
		//fireEvent(name, event, this_object);
		fireEvent(name, event);
		return get_context().CreateUndefined();
	}

}  // namespace Titanium {
