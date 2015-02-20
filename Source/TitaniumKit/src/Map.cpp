/**
 * Titanium.Map for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Map.hpp"

namespace Titanium
{
    MapModule::MapModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
        : Module(js_context, arguments)
    {
	}

	JSValue MapModule::MAPTYPE_HYBRID() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(static_cast<int>(MapType::HYBRID));
	}

	JSValue MapModule::MAPTYPE_SATELITE() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(static_cast<int>(MapType::SATELITE));
	}

	JSValue MapModule::MAPTYPE_STANDARD() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(static_cast<int>(MapType::STANDARD));
	}

	JSValue MapModule::createView(JSValue parameters) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Map::createView");

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Map_property = Titanium.GetProperty("Map");
		TITANIUM_ASSERT(Map_property.IsObject());  // precondition
		JSObject Map = static_cast<JSObject>(Map_property);

		JSValue View_property = Map.GetProperty("View");
		TITANIUM_ASSERT(View_property.IsObject());  // precondition
		JSObject MapView = static_cast<JSObject>(View_property);

		return MapView.CallAsConstructor(parameters);
	}

	JSValue MapModule::createAnnotation(JSValue parameters) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Map::createAnnotation: Unimplemented");
		return get_context().CreateUndefined();
	}

	void MapModule::JSExportInitialize() {
		JSExport<MapModule>::SetClassVersion(1);
		JSExport<MapModule>::SetParent(JSExport<Module>::Class());

		JSExport<MapModule>::AddValueProperty("HYBRID_TYPE", std::mem_fn(&MapModule::MAPTYPE_HYBRID));
		JSExport<MapModule>::AddValueProperty("SATELLITE_TYPE", std::mem_fn(&MapModule::MAPTYPE_SATELITE));
		JSExport<MapModule>::AddValueProperty("STANDARD_TYPE", std::mem_fn(&MapModule::MAPTYPE_STANDARD));

		JSExport<MapModule>::AddFunctionProperty("createView", std::mem_fn(&MapModule::js_createView));
		JSExport<MapModule>::AddFunctionProperty("createAnnotation", std::mem_fn(&MapModule::js_createAnnotation));
	}

	JSValue MapModule::js_createView(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();

		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = static_cast<JSObject>(_0);
		}

		return createView(parameters);
	}

	JSValue MapModule::js_createAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		JSObject parameters = get_context().CreateObject();

		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = static_cast<JSObject>(_0);
		}

		return createAnnotation(parameters);
	}

} // namespace Titanium