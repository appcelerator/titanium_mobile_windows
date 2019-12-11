/**
 * Titanium.Map for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/MapModule.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
    MapModule::MapModule(const JSContext& js_context) TITANIUM_NOEXCEPT
        : Module(js_context, "Ti.Map")
    {
		TITANIUM_LOG_DEBUG("MapModule:: ctor ", this);
	}

	TITANIUM_PROPERTY_GETTER(MapModule, HYBRID_TYPE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::HYBRID));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, SATELLITE_TYPE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::SATELLITE));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, NORMAL_TYPE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::NORMAL));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, TERRAIN_TYPE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::MAP_TYPE::TERRAIN));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_DRAG_STATE_END)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_DRAG_STATE::END));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_DRAG_STATE_START)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_DRAG_STATE::START));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_AZURE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::AZURE));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_BLUE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::BLUE));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_CYAN)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::CYAN));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_GREEN)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::GREEN));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_MAGENTA)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::MAGENTA));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_ORANGE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::ORANGE));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_PURPLE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::PURPLE));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_RED)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::RED));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_ROSE)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::ROSE));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_VIOLET)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::VIOLET));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, ANNOTATION_YELLOW)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::ANNOTATION_COLOR::YELLOW));
	}
	TITANIUM_PROPERTY_GETTER(MapModule, OVERLAY_LEVEL_ABOVE_LABELS)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::OVERLAY_LEVEL::ABOVE_LABELS));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, OVERLAY_LEVEL_ABOVE_ROADS)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::OVERLAY_LEVEL::ABOVE_ROADS));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, SERVICE_DISABLED)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::DISABLED));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, SERVICE_INVALID)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::INVALID));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, SERVICE_MISSING)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::MISSING));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, SERVICE_VERSION_UPDATE_REQUIRED)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::VERSION_UPDATE_REQUIRED));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, SUCCESS)
	{
		return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::SUCCESS));
	}

	TITANIUM_PROPERTY_GETTER(MapModule, Camera)
	{
		return get_context().CreateObject(camera__);
	}

	TITANIUM_PROPERTY_GETTER(MapModule, Annotation)
	{
		return get_context().CreateObject(annotation__);
	}

	TITANIUM_PROPERTY_GETTER(MapModule, Route)
	{
		return get_context().CreateObject(route__);
	}

	TITANIUM_PROPERTY_GETTER(MapModule, View)
	{
		return get_context().CreateObject(view__);
	}

	MapModule& MapModule::AnnotationClass(const JSClass& annotation) TITANIUM_NOEXCEPT
	{
		annotation__ = annotation;
		return *this;
	}

	MapModule& MapModule::CameraClass(const JSClass& camera) TITANIUM_NOEXCEPT
	{
		camera__ = camera;
		return *this;
	}

	MapModule& MapModule::RouteClass(const JSClass& route) TITANIUM_NOEXCEPT
	{
		route__ = route;
		return *this;
	}

	MapModule& MapModule::ViewClass(const JSClass& view) TITANIUM_NOEXCEPT
	{
		view__ = view;
		return *this;
	}

	JSObject MapModule::createView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Map::createView");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
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

	JSObject MapModule::createAnnotation(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Map::createAnnotation");

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Map_property = Titanium.GetProperty("Map");
		TITANIUM_ASSERT(Map_property.IsObject());  // precondition
		JSObject Map = static_cast<JSObject>(Map_property);

		JSValue Proxy_property = Map.GetProperty("Annotation");
		TITANIUM_ASSERT(Proxy_property.IsObject());  // precondition
		JSObject Proxy = static_cast<JSObject>(Proxy_property);

		auto proxy = Proxy.CallAsConstructor(parameters);
		Titanium::Module::applyProperties(parameters, proxy);
		return proxy;
	}

	JSObject MapModule::createRoute(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Map::createRoute");

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Map_property = Titanium.GetProperty("Map");
		TITANIUM_ASSERT(Map_property.IsObject());  // precondition
		JSObject Map = static_cast<JSObject>(Map_property);

		JSValue Proxy_property = Map.GetProperty("Route");
		TITANIUM_ASSERT(Proxy_property.IsObject());  // precondition
		JSObject Proxy = static_cast<JSObject>(Proxy_property);

		auto proxy = Proxy.CallAsConstructor(parameters);
		Titanium::Module::applyProperties(parameters, proxy);
		return proxy;
	}

	JSObject MapModule::createCamera(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Map::createCamera");

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Map_property = Titanium.GetProperty("Map");
		TITANIUM_ASSERT(Map_property.IsObject());  // precondition
		JSObject Map = static_cast<JSObject>(Map_property);

		JSValue Proxy_property = Map.GetProperty("Camera");
		TITANIUM_ASSERT(Proxy_property.IsObject());  // precondition
		JSObject Proxy = static_cast<JSObject>(Proxy_property);

		auto proxy = Proxy.CallAsConstructor(parameters);
		Titanium::Module::applyProperties(parameters, proxy);
		return proxy;
	}

	Titanium::Map::GOOGLE_PLAY_SERVICE_STATE MapModule::isGooglePlayServicesAvailable() TITANIUM_NOEXCEPT
	{
		return Titanium::Map::GOOGLE_PLAY_SERVICE_STATE::MISSING;
	}

	void MapModule::JSExportInitialize() {
		JSExport<MapModule>::SetClassVersion(1);
		JSExport<MapModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, HYBRID_TYPE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, SATELLITE_TYPE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, NORMAL_TYPE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, TERRAIN_TYPE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_DRAG_STATE_END);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_DRAG_STATE_START);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_AZURE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_BLUE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_CYAN);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_GREEN);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_MAGENTA);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_ORANGE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_PURPLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_RED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_ROSE);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_VIOLET);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, ANNOTATION_YELLOW);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, OVERLAY_LEVEL_ABOVE_LABELS);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, OVERLAY_LEVEL_ABOVE_ROADS);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, SERVICE_DISABLED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, SERVICE_INVALID);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, SERVICE_MISSING);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, SERVICE_VERSION_UPDATE_REQUIRED);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, SUCCESS);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, Annotation);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, Camera);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, Route);
		TITANIUM_ADD_CONSTANT_PROPERTY(MapModule, View);

		TITANIUM_ADD_FUNCTION(MapModule, createView);
		TITANIUM_ADD_FUNCTION(MapModule, createAnnotation);
		TITANIUM_ADD_FUNCTION(MapModule, createRoute);
		TITANIUM_ADD_FUNCTION(MapModule, createCamera);
		TITANIUM_ADD_FUNCTION(MapModule, isGooglePlayServicesAvailable);
	}

	TITANIUM_FUNCTION(MapModule, createView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		return createView(parameters, this_object);
	}

	TITANIUM_FUNCTION(MapModule, createAnnotation)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		return createAnnotation(parameters, this_object);
	}

	TITANIUM_FUNCTION(MapModule, createRoute)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		return createRoute(parameters, this_object);
	}

	TITANIUM_FUNCTION(MapModule, createCamera)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		return createCamera(parameters, this_object);
	}

	TITANIUM_FUNCTION(MapModule, isGooglePlayServicesAvailable)
	{
		return this_object.get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(isGooglePlayServicesAvailable()));
	}

} // namespace Titanium
