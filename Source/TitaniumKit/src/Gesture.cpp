/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Gesture.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <type_traits>

namespace Titanium
{
	Gesture::Gesture(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti.Gesture")
	{
	}

	Titanium::UI::ORIENTATION Gesture::get_orientation() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Gesture::get_orientation: Unimplemented");
		return Titanium::UI::ORIENTATION::UNKNOWN;
	}

	void Gesture::JSExportInitialize()
	{
		JSExport<Gesture>::SetClassVersion(1);
		JSExport<Gesture>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_FUNCTION(Gesture, getLandscape);
		TITANIUM_ADD_FUNCTION(Gesture, getPortrait);
		TITANIUM_ADD_FUNCTION(Gesture, getOrientation);
		TITANIUM_ADD_FUNCTION(Gesture, isFaceDown);
		TITANIUM_ADD_FUNCTION(Gesture, isFaceUp);
		TITANIUM_ADD_FUNCTION(Gesture, isLandscape);
		TITANIUM_ADD_FUNCTION(Gesture, isPortrait);
		TITANIUM_ADD_PROPERTY_READONLY(Gesture, orientation);
		TITANIUM_ADD_PROPERTY_READONLY(Gesture, landscape);
		TITANIUM_ADD_PROPERTY_READONLY(Gesture, portrait);
	}

	JSObject Gesture::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		static JSObject cached = js_context.CreateObject();
		static std::once_flag of;
		std::call_once(of, [=] {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Object_property = Titanium.GetProperty("Gesture");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			cached = static_cast<JSObject>(Object_property);
		});
		return cached;
	}

	TITANIUM_PROPERTY_GETTER(Gesture, orientation)
	{
		return get_context().CreateNumber(UI::Constants::to_underlying_type(get_orientation()));
	}

	TITANIUM_FUNCTION(Gesture, getOrientation)
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetStaticObject(js_context).GetPrivate<Gesture>();
		return this_object.get_context().CreateNumber(UI::Constants::to_underlying_type(gesture_ptr->get_orientation()));
	}

	TITANIUM_FUNCTION(Gesture, isFaceDown)
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetStaticObject(js_context).GetPrivate<Gesture>();
		return this_object.get_context().CreateBoolean(gesture_ptr->get_orientation() == UI::ORIENTATION::FACE_DOWN);
	}

	TITANIUM_FUNCTION(Gesture, isFaceUp)
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetStaticObject(js_context).GetPrivate<Gesture>();
		return this_object.get_context().CreateBoolean(gesture_ptr->get_orientation() == UI::ORIENTATION::FACE_UP);
	}

	TITANIUM_FUNCTION(Gesture, isLandscape)
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetStaticObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_landscape();
	}

	TITANIUM_FUNCTION(Gesture, isPortrait)
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetStaticObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_portrait();
	}

	TITANIUM_FUNCTION(Gesture, getLandscape)
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetStaticObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_landscape();
	}

	TITANIUM_PROPERTY_GETTER(Gesture, landscape)
	{
		const auto o = get_orientation();
		const bool isLandscape = (o == UI::ORIENTATION::LANDSCAPE_LEFT || o == UI::ORIENTATION::LANDSCAPE_RIGHT);
		return get_context().CreateBoolean(isLandscape);
	}

	TITANIUM_FUNCTION(Gesture, getPortrait)
	{
		const auto js_context = this_object.get_context();
		const auto gesture_ptr = GetStaticObject(js_context).GetPrivate<Gesture>();
		return gesture_ptr->js_get_portrait();
	}

	TITANIUM_PROPERTY_GETTER(Gesture, portrait)
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
