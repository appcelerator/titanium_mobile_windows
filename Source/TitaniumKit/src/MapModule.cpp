/**
 * Titanium.Map for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/MapModule.hpp"

namespace Titanium
{
    MapModule::MapModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
        : Module(js_context, arguments),
		hybrid_type__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::HYBRID))),
		satellite_type__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::SATELLITE))),
		normal_type__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::NORMAL))),
		terrain_type__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::TERRAIN))),
		annotation_drag_state_end__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_DRAG_STATE::END))),
		annotation_drag_state_start__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_DRAG_STATE::START))),
		annotation_azure__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::AZURE))),
		annotation_blue__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::BLUE))),
		annotation_cyan__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::CYAN))),
		annotation_green__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::GREEN))),
		annotation_magenta__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::MAGENTA))),
		annotation_orange__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::ORANGE))),
		annotation_purple__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::PURPLE))),
		annotation_red__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::RED))),
		annotation_rose__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::ROSE))),
		annotation_violet__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::VIOLET))),
		annotation_yellow__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::YELLOW))),
		overlay_level_above_labels__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::OVERLAY_LEVEL::ABOVE_LABELS))),
		overlay_level_above_roads__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::OVERLAY_LEVEL::ABOVE_ROADS))),
		service_disabled__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::DISABLED))),
		service_invalid__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::INVALID))),
		service_missing__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::MISSING))),
		service_version_update_required__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::VERSION_UPDATE_REQUIRED))),
		success__(js_context.CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::SUCCESS)))
    {
	}

	JSValue MapModule::HYBRID_TYPE() const TITANIUM_NOEXCEPT
	{
		return hybrid_type__;
	}

	JSValue MapModule::SATELLITE_TYPE() const TITANIUM_NOEXCEPT
	{
		return satellite_type__;
	}

	JSValue MapModule::NORMAL_TYPE() const TITANIUM_NOEXCEPT
	{
		return normal_type__;
	}

	JSValue MapModule::TERRAIN_TYPE() const TITANIUM_NOEXCEPT
	{
		return terrain_type__;
	}

	JSValue MapModule::ANNOTATION_DRAG_STATE_END() const TITANIUM_NOEXCEPT
	{
		return annotation_drag_state_end__;
	}

	JSValue MapModule::ANNOTATION_DRAG_STATE_START() const TITANIUM_NOEXCEPT
	{
		return annotation_drag_state_start__;
	}

	JSValue MapModule::ANNOTATION_AZURE() const TITANIUM_NOEXCEPT
	{
		return annotation_azure__;
	}
	
	JSValue MapModule::ANNOTATION_BLUE() const TITANIUM_NOEXCEPT
	{
		return annotation_blue__;
	}
	
	JSValue MapModule::ANNOTATION_CYAN() const TITANIUM_NOEXCEPT
	{
		return annotation_cyan__;
	}
		
	JSValue MapModule::ANNOTATION_GREEN() const TITANIUM_NOEXCEPT
	{
		return annotation_green__;
	}

	JSValue MapModule::ANNOTATION_MAGENTA() const TITANIUM_NOEXCEPT
	{
		return annotation_magenta__;
	}

	JSValue MapModule::ANNOTATION_ORANGE() const TITANIUM_NOEXCEPT
	{
		return annotation_orange__;
	}

	JSValue MapModule::ANNOTATION_PURPLE() const TITANIUM_NOEXCEPT
	{
		return annotation_purple__;
	}

	JSValue MapModule::ANNOTATION_RED() const TITANIUM_NOEXCEPT
	{
		return annotation_red__;
	}

	JSValue MapModule::ANNOTATION_ROSE() const TITANIUM_NOEXCEPT
	{
		return annotation_rose__;
	}
		
	JSValue MapModule::ANNOTATION_VIOLET() const TITANIUM_NOEXCEPT
	{
		return annotation_violet__;
	}
		
	JSValue MapModule::ANNOTATION_YELLOW() const TITANIUM_NOEXCEPT
	{
		return annotation_yellow__;
	}
	JSValue MapModule::OVERLAY_LEVEL_ABOVE_LABELS() const TITANIUM_NOEXCEPT
	{
		return overlay_level_above_labels__;
	}

	JSValue MapModule::OVERLAY_LEVEL_ABOVE_ROADS() const TITANIUM_NOEXCEPT
	{
		return overlay_level_above_roads__;
	}

	JSValue MapModule::SERVICE_DISABLED() const TITANIUM_NOEXCEPT
	{
		return service_disabled__;
	}

	JSValue MapModule::SERVICE_INVALID() const TITANIUM_NOEXCEPT
	{
		return service_invalid__;
	}

	JSValue MapModule::SERVICE_MISSING() const TITANIUM_NOEXCEPT
	{
		return service_missing__;
	}

	JSValue MapModule::SERVICE_VERSION_UPDATE_REQUIRED() const TITANIUM_NOEXCEPT
	{
		return service_version_update_required__;
	}

	JSValue MapModule::SUCCESS() const TITANIUM_NOEXCEPT
	{
		return success__;
	}

	JSValue MapModule::createView(JSObject parameters) TITANIUM_NOEXCEPT
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

		auto mapView = MapView.CallAsConstructor(parameters);
		Titanium::Module::applyProperties(parameters, mapView);
		return mapView;
	}

	JSValue MapModule::createAnnotation(JSObject parameters) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Map::createAnnotation: Unimplemented");
		return get_context().CreateUndefined();
	}

	JSValue MapModule::createRoute(JSObject parameters) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Map::createRoute: Unimplemented");
		return get_context().CreateUndefined();
	}

	JSValue MapModule::createCamera(JSObject parameters) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Map::createCamera: Unimplemented");
		return get_context().CreateUndefined();
	}

	Titanium::Map::GOOGLE_PLAY_SERVICE_STATE MapModule::isGooglePlayServicesAvailable() TITANIUM_NOEXCEPT
	{
		return Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::MISSING;
	}

	void MapModule::JSExportInitialize() {
		JSExport<MapModule>::SetClassVersion(1);
		JSExport<MapModule>::SetParent(JSExport<Module>::Class());

		JSExport<MapModule>::AddValueProperty("HYBRID_TYPE", std::mem_fn(&MapModule::HYBRID_TYPE));
		JSExport<MapModule>::AddValueProperty("SATELLITE_TYPE", std::mem_fn(&MapModule::SATELLITE_TYPE));
		JSExport<MapModule>::AddValueProperty("NORMAL_TYPE", std::mem_fn(&MapModule::NORMAL_TYPE));
		JSExport<MapModule>::AddValueProperty("TERRAIN_TYPE", std::mem_fn(&MapModule::TERRAIN_TYPE));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_DRAG_STATE_END", std::mem_fn(&MapModule::ANNOTATION_DRAG_STATE_END));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_DRAG_STATE_START", std::mem_fn(&MapModule::ANNOTATION_DRAG_STATE_START));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_AZURE", std::mem_fn(&MapModule::ANNOTATION_AZURE));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_BLUE", std::mem_fn(&MapModule::ANNOTATION_BLUE));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_CYAN", std::mem_fn(&MapModule::ANNOTATION_CYAN));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_GREEN", std::mem_fn(&MapModule::ANNOTATION_GREEN));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_MAGENTA", std::mem_fn(&MapModule::ANNOTATION_MAGENTA));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_ORANGE", std::mem_fn(&MapModule::ANNOTATION_ORANGE));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_PURPLE", std::mem_fn(&MapModule::ANNOTATION_PURPLE));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_RED", std::mem_fn(&MapModule::ANNOTATION_RED));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_ROSE", std::mem_fn(&MapModule::ANNOTATION_ROSE));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_VIOLET", std::mem_fn(&MapModule::ANNOTATION_VIOLET));
		JSExport<MapModule>::AddValueProperty("ANNOTATION_YELLOW", std::mem_fn(&MapModule::ANNOTATION_YELLOW));
		JSExport<MapModule>::AddValueProperty("OVERLAY_LEVEL_ABOVE_LABELS", std::mem_fn(&MapModule::OVERLAY_LEVEL_ABOVE_LABELS));
		JSExport<MapModule>::AddValueProperty("OVERLAY_LEVEL_ABOVE_ROADS", std::mem_fn(&MapModule::OVERLAY_LEVEL_ABOVE_ROADS));
		JSExport<MapModule>::AddValueProperty("SERVICE_DISABLED", std::mem_fn(&MapModule::SERVICE_DISABLED));
		JSExport<MapModule>::AddValueProperty("SERVICE_INVALID", std::mem_fn(&MapModule::SERVICE_INVALID));
		JSExport<MapModule>::AddValueProperty("SERVICE_MISSING", std::mem_fn(&MapModule::SERVICE_MISSING));
		JSExport<MapModule>::AddValueProperty("SERVICE_VERSION_UPDATE_REQUIRED", std::mem_fn(&MapModule::SERVICE_VERSION_UPDATE_REQUIRED));
		JSExport<MapModule>::AddValueProperty("SUCCESS", std::mem_fn(&MapModule::SUCCESS));

		JSExport<MapModule>::AddFunctionProperty("createView", std::mem_fn(&MapModule::js_createView));
		JSExport<MapModule>::AddFunctionProperty("createAnnotation", std::mem_fn(&MapModule::js_createAnnotation));
		JSExport<MapModule>::AddFunctionProperty("createRoute", std::mem_fn(&MapModule::js_createRoute));
		JSExport<MapModule>::AddFunctionProperty("createCamera", std::mem_fn(&MapModule::js_createCamera));
		JSExport<MapModule>::AddFunctionProperty("isGoogleMapServicesAvailable", std::mem_fn(&MapModule::js_isGoogleMapServicesAvailable));
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

	JSValue MapModule::js_createRoute(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		JSObject parameters = get_context().CreateObject();

		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = static_cast<JSObject>(_0);
		}

		return createRoute(parameters);
	}

	JSValue MapModule::js_createCamera(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		JSObject parameters = get_context().CreateObject();

		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = static_cast<JSObject>(_0);
		}

		return createCamera(parameters);
	}

	JSValue MapModule::js_isGoogleMapServicesAvailable(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(isGooglePlayServicesAvailable()));
	}

} // namespace Titanium