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
	    : JSExportObject(js_context)
	{
	}

	void Module::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			if (_0.IsObject()) {
				JSObject properties = static_cast<JSObject>(_0);
				TITANIUM_LOG_DEBUG("Module:: ctor has ", properties.GetPropertyNames().GetCount(), " properties for ", this);
			}
		}
	}

	Module::~Module() TITANIUM_NOEXCEPT
	{
	}

	void Module::addEventListener(const std::string& name, JSObject& callback, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (!callback.IsFunction()) {
			TITANIUM_LOG_WARN("Module::addEventListener: Listener is not a function for event '", name, "'");
			return;
		}

		std::vector<JSObject> event_listener_list;
		if (event_listener_map__.find(name) != event_listener_map__.end()) {
			event_listener_list = event_listener_map__.at(name);
		}

		JSObject callback_payload = get_context().CreateObject();
		callback_payload.SetProperty("callback", callback);
		callback_payload.SetProperty("this_object", this_object);

		// Precondition
		const auto event_listener_index = eventListenerIndex(event_listener_list, name, callback_payload);
		if (event_listener_index > 0) {
			TITANIUM_LOG_WARN("Module::addEventListener: event listener already added at index ", event_listener_index, " for event '", name, "'");
		} else {
			const auto callback_list_index = event_listener_list.size();
			if (callback_list_index == 0) {
				// This is the first event listener for this event name, so signal
				// module subclasses that callbacks have been registered for this event.
				enableEvent(name);
			}
			TITANIUM_LOG_DEBUG("Module::addEventListener: add listener at index ", callback_list_index, " for event '", name, "' for ", this);
			event_listener_list.emplace_back(callback_payload);
		}
		event_listener_map__.emplace(name, event_listener_list);
	}

	void Module::removeEventListener(const std::string& name, JSObject& callback, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (!callback.IsFunction()) {
			TITANIUM_LOG_WARN("Module::removeEventListener: callback is not a function for event '", name, "'");
			return;
		}

		if (event_listener_map__.find(name) == event_listener_map__.end()) {
			TITANIUM_LOG_WARN("Module::removeEventListener: No event listener's for event '", name, "'");
			return;
		}

		std::vector<JSObject> event_listener_list = event_listener_map__.at(name);

		JSObject callback_payload = get_context().CreateObject();
		callback_payload.SetProperty("callback", callback);
		callback_payload.SetProperty("this_object", this_object);

		const auto event_listener_count = event_listener_list.size();
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
			event_listener_list.erase(event_listener_list.begin() +  event_listener_index);
			//if (!deleted) {
				// This is a TitaniumKit logic error.
				//TITANIUM_LOG_ERROR("Module::removeEventListener: event listener at index ", event_listener_index, " for event '", name, "' was not removed");
				//TITANIUM_ASSERT(deleted);
			//}
		} else {
			TITANIUM_LOG_WARN("Module::removeEventListener: listener does not exist for event '", name, "'");
		}
	}

	void Module::applyProperties(const JSObject& props, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (props.GetPropertyNames().GetCount() > 0) {
			const auto propertyNames = props.GetPropertyNames();
			for (const auto& property_name : static_cast<std::vector<JSString>>(propertyNames)) {
				this_object.SetProperty(property_name, props.GetProperty(property_name));
			}
		}
	}

	void Module::fireEvent(const std::string& name) TITANIUM_NOEXCEPT
	{
		fireEvent(name, get_context().CreateObject());
	}

	void Module::fireEvent(const std::string& name, const JSObject& event) TITANIUM_NOEXCEPT
	{
		if (!enableEvents__) {
			TITANIUM_LOG_WARN("Module::fireEvent: Stopped firing '", name, "'");
			return;
		}
		if (event_listener_map__.find(name) == event_listener_map__.end()) {
			TITANIUM_LOG_WARN("Module::fireEvent: No event named '", name, "' has been added");
			return;
		}

		std::vector<JSObject> event_listener_list = event_listener_map__.at(name);
		const auto event_listener_count = event_listener_list.size();

		if (event_listener_count == 0) {
			TITANIUM_LOG_WARN("Module::fireEvent: No listeners for event '", name, "'");
			return;
		}

		auto event_copy = event;
		if (!event_copy.HasProperty("source")) {
			event_copy.SetProperty("source", get_object());
		}
		event_copy.SetProperty("type", event.get_context().CreateString(name));

		for (size_t i = 0; i < event_listener_count; ++i) {
			JSObject callback_payload = event_listener_list.at(i);

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
			callback({ static_cast<JSValue>(event_copy) }, this_object);
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

	unsigned Module::eventListenerIndex(const std::vector<JSObject>& event_listener_list, const std::string& name, JSObject& callback) TITANIUM_NOEXCEPT
	{
		unsigned index = 0;
		bool found = false;
		const auto event_listener_count = event_listener_list.size();
		for (unsigned i = 0; i < event_listener_count; ++i) {
			JSObject callback_payload = event_listener_list.at(i);

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

	void Module::JSExportInitialize()
	{
		JSExport<Module>::SetClassVersion(1);
		JSExport<Module>::SetParent(JSExport<JSExportObject>::Class());
		TITANIUM_ADD_FUNCTION(Module, addEventListener);
		TITANIUM_ADD_FUNCTION(Module, removeEventListener);
		TITANIUM_ADD_FUNCTION(Module, applyProperties);
		TITANIUM_ADD_FUNCTION(Module, fireEvent);
	}

	TITANIUM_FUNCTION(Module, addEventListener)
	{
		ENSURE_STRING_AT_INDEX(name, 0);
		ENSURE_OBJECT_AT_INDEX(callback, 1);

		TITANIUM_ASSERT(callback.IsFunction());
		addEventListener(name, callback, this_object);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Module, removeEventListener)
	{
		ENSURE_STRING_AT_INDEX(name, 0);
		ENSURE_OBJECT_AT_INDEX(callback, 1);

		TITANIUM_ASSERT(callback.IsFunction());
		removeEventListener(name, callback, this_object);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Module, applyProperties)
	{
		ENSURE_OBJECT_AT_INDEX(props, 0);

		applyProperties(props, this_object);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Module, fireEvent)
	{
		ENSURE_STRING_AT_INDEX(name, 0);
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(param, 1);

		fireEvent(name, param);
		return get_context().CreateUndefined();
	}

}  // namespace Titanium {
