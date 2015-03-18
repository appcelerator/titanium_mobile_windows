/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Gesture.hpp"
#include <type_traits>

namespace Titanium
{
	Gesture::Gesture(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context)
	{
	}

	Titanium::UI::ORIENTATION Gesture::get_orientation() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Gesture::get_orientation: Unimplemented");
		return Titanium::UI::ORIENTATION::UNKNOWN;
	}

	// TODO: The following functions can automatically be generated from
	// the YAML API docs.

	void Gesture::JSExportInitialize()
	{
		JSExport<Gesture>::SetClassVersion(1);
		JSExport<Gesture>::SetParent(JSExport<Module>::Class());
		JSExport<Gesture>::AddFunctionProperty("getLandscape", std::mem_fn(&Gesture::js_getLandscape));
		JSExport<Gesture>::AddFunctionProperty("getPortrait", std::mem_fn(&Gesture::js_getPortrait));
		JSExport<Gesture>::AddFunctionProperty("getOrientation", std::mem_fn(&Gesture::js_getOrientation));
		JSExport<Gesture>::AddFunctionProperty("isFaceDown", std::mem_fn(&Gesture::js_isFaceDown));
		JSExport<Gesture>::AddFunctionProperty("isFaceUp", std::mem_fn(&Gesture::js_isFaceUp));
		JSExport<Gesture>::AddFunctionProperty("isLandscape", std::mem_fn(&Gesture::js_isLandscape));
		JSExport<Gesture>::AddFunctionProperty("isPortrait", std::mem_fn(&Gesture::js_isPortrait));
		JSExport<Gesture>::AddValueProperty("orientation", std::mem_fn(&Gesture::js_get_orientation));
		JSExport<Gesture>::AddValueProperty("landscape", std::mem_fn(&Gesture::js_get_landscape));
		JSExport<Gesture>::AddValueProperty("portrait", std::mem_fn(&Gesture::js_get_portrait));
	}

	JSObject Gesture::GetGestureObject(const JSContext& js_context) const TITANIUM_NOEXCEPT
	{
		JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Object_property = Titanium.GetProperty("Gesture");
		TITANIUM_ASSERT(Object_property.IsObject());  // precondition
		return static_cast<JSObject>(Object_property);
	}

	JSValue Gesture::js_get_orientation() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(UI::Constants::to_underlying_type(get_orientation()));
	}
	JSValue Gesture::js_getOrientation(
	    const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetGestureObject(js_context).GetPrivate<Gesture>();
		return this_object.get_context().CreateNumber(UI::Constants::to_underlying_type(gesture_ptr->get_orientation()));
	}

	JSValue Gesture::js_isFaceDown(
	    const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetGestureObject(js_context).GetPrivate<Gesture>();
		return this_object.get_context().CreateBoolean(gesture_ptr->get_orientation() == UI::ORIENTATION::FACE_DOWN);
	}

	JSValue Gesture::js_isFaceUp(
	    const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetGestureObject(js_context).GetPrivate<Gesture>();
		return this_object.get_context().CreateBoolean(gesture_ptr->get_orientation() == UI::ORIENTATION::FACE_UP);
	}

	JSValue Gesture::js_isLandscape(
	    const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetGestureObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_landscape();
	}

	JSValue Gesture::js_isPortrait(
	    const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetGestureObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_portrait();
	}

	JSValue Gesture::js_getLandscape(
	    const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetGestureObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_landscape();
	}

	JSValue Gesture::js_get_landscape() const TITANIUM_NOEXCEPT
	{
		const auto o = get_orientation();
		const bool isLandscape = (o == UI::ORIENTATION::LANDSCAPE_LEFT || o == UI::ORIENTATION::LANDSCAPE_RIGHT);
		return get_context().CreateBoolean(isLandscape);
	}

	JSValue Gesture::js_getPortrait(
	    const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetGestureObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_portrait();
	}

	JSValue Gesture::js_get_portrait() const TITANIUM_NOEXCEPT
	{
		const auto o = get_orientation();
		const bool isPortrait = (o == UI::ORIENTATION::PORTRAIT || o == UI::ORIENTATION::UPSIDE_PORTRAIT);
		return get_context().CreateBoolean(isPortrait);
	};

	void Gesture::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Ti::Gesture::enableEvent: Unimplemented (event name '", event_name, "'");
	}

	void Gesture::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Ti::Gesture::disableEvent: Unimplemented (event name '", event_name, "'");
	}

}  // namespace Titanium
