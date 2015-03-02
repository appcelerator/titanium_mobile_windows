/**
 * TitaniumKit Titanium.Map.View
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Map/View.hpp"

namespace Titanium
{
	namespace Map
	{
		View::View(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::View(js_context, arguments),
			animate__(false),
			compassEnabled__(false),
			enableZoomControls__(false),
			mapType__(Titanium::Map::MAP_TYPE::NORMAL),
			region__({0}),
			pitchEnabled__(false),
			rotateEnabled__(false),
			showsBuildings__(false),
			showsPointsOfInterest__(false),
			traffic__(false),
			userLocation__(false),
			userLocationButton__(false),
			zOrderOnTop__(false)
		{
		}
		
		void View::addAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::addAnnotation: Unimplemented");
		}
		
		void View::addAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::addAnnotations: Unimplemented");
		}
		
		void View::addRoute(JSObject& route) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::addRoute: Unimplemented");
		}
		
		void View::animateCamera(JSObject& animationParams, JSObject& callback) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::animateCamera: Unimplemented");
		}
		
		void View::deselectAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::deselectAnnotation: Unimplemented");
		}
		
		void View::removeAllAnnotations() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::removeAllAnnotations: Unimplemented");
		}
		
		void View::removeAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::removeAnnotation: Unimplemented");
		}
		
		void View::removeAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::removeAnnotations: Unimplemented");
		}
		
		void View::removeRoute(JSObject& route) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::removeRoute: Unimplemented");
		}
		
		void View::selectAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::selectAnnotation: Unimplemented");
		}

		void View::setLocation(JSObject& location) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::setLocation: Unimplemented");
		}

		void View::showAnnotations() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::showAnnotations: Unimplemented");
		}

		void View::showAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::showAnnotations: Unimplemented");
		}

		void View::snapshot() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::snapshot: Unimplemented");
		}

		void View::zoom(const uint32_t& zoom) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::zoom: Unimplemented");
		}

		// properties
		bool View::get_animate() const TITANIUM_NOEXCEPT
		{
			return animate__;
		}

		void View::set_animate(const bool& animate) TITANIUM_NOEXCEPT
		{
			animate__ = animate;
		}

		// TODO : Implement Titanium.Map.Annotation and Titanium.Map.Camera
		/*JSObject View::get_annotations() const TITANIUM_NOEXCEPT
		{
		}

		void View::set_annotations(const JSObject& annotations) TITANIUM_NOEXCEPT
		{
		}

		JSObject View::get_camera() const TITANIUM_NOEXCEPT
		{
		}

		void View::set_camera(const JSObject& camera) TITANIUM_NOEXCEPT
		{
		}*/

		bool View::get_compassEnabled() const TITANIUM_NOEXCEPT
		{
			return compassEnabled__;
		}

		void View::set_compassEnabled(const bool& compass) TITANIUM_NOEXCEPT
		{
			compassEnabled__ = compass;
		}

		bool View::get_enableZoomControls() const TITANIUM_NOEXCEPT
		{
			return enableZoomControls__;
		}
		
		void View::set_enableZoomControls(const bool& zoomControls) TITANIUM_NOEXCEPT
		{
			enableZoomControls__ = zoomControls;
		}

		Titanium::Map::MAP_TYPE View::get_mapType() const TITANIUM_NOEXCEPT
		{
			return mapType__;
		}

		void View::set_mapType(const Titanium::Map::MAP_TYPE& mapType) TITANIUM_NOEXCEPT
		{
			mapType__ = mapType;
		}

		uint32_t View::get_maxZoomLevel() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::get_maxZoomLevel: Unimplemented");
			return 0;
		}

		uint32_t View::get_minZoomLevel() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Map::View::get_minZoomLevel: Unimplemented");
			return 0;
		}

		bool View::get_pitchEnabled() const TITANIUM_NOEXCEPT
		{
			return pitchEnabled__;
		}

		void View::set_pitchEnabled(const bool& pitch) TITANIUM_NOEXCEPT
		{
			pitchEnabled__ = pitch;
		}

		View::MapRegionType View::get_region() const TITANIUM_NOEXCEPT
		{
			return region__;
		}

		void View::set_region(const View::MapRegionType& region) TITANIUM_NOEXCEPT
		{
			region__ = region;
		}

		bool View::get_rotateEnabled() const TITANIUM_NOEXCEPT
		{
			return rotateEnabled__;
		}

		void View::set_rotateEnabled(const bool& rotate) TITANIUM_NOEXCEPT
		{
			rotateEnabled__ = rotate;
		}

		bool View::get_showsBuildings() const TITANIUM_NOEXCEPT
		{
			return showsBuildings__;
		}

		void View::set_showsBuildings(const bool& buildings) TITANIUM_NOEXCEPT
		{
			showsBuildings__ = buildings;
		}

		bool View::get_showsPointsOfInterest() const TITANIUM_NOEXCEPT
		{
			return showsPointsOfInterest__;
		}

		void View::set_showsPointsOfInterest(const bool& poi) TITANIUM_NOEXCEPT
		{
			showsPointsOfInterest__ = poi;
		}

		bool View::get_traffic() const TITANIUM_NOEXCEPT
		{
			return traffic__;
		}

		void View::set_traffic(const bool& traffic) TITANIUM_NOEXCEPT
		{
			traffic__ = traffic;
		}

		bool View::get_userLocation() const TITANIUM_NOEXCEPT
		{
			return userLocation__;
		}

		void View::set_userLocation(const bool& userLocation) TITANIUM_NOEXCEPT
		{
			userLocation__ = userLocation;
		}

		bool View::get_userLocationButton() const TITANIUM_NOEXCEPT
		{
			return userLocationButton__;
		}

		void View::set_userLocationButton(const bool& userLocationButton) TITANIUM_NOEXCEPT
		{
			userLocationButton__ = userLocationButton;
		}

		bool View::get_zOrderOnTop() const TITANIUM_NOEXCEPT
		{
			return zOrderOnTop__;
		}

		void View::set_zOrderOnTop(const bool& zOrderOnTop) TITANIUM_NOEXCEPT
		{
			zOrderOnTop__ = zOrderOnTop;
		}

		void View::JSExportInitialize() {
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Module>::Class());
			
			// methods
			JSExport<View>::AddFunctionProperty("addAnnotation", std::mem_fn(&View::js_addAnnotation));
			JSExport<View>::AddFunctionProperty("addAnnotations", std::mem_fn(&View::js_addAnnotations));
			JSExport<View>::AddFunctionProperty("addRoute", std::mem_fn(&View::js_addRoute));
			JSExport<View>::AddFunctionProperty("animateCamera", std::mem_fn(&View::js_animateCamera));
			JSExport<View>::AddFunctionProperty("deselectAnnotation", std::mem_fn(&View::js_deselectAnnotation));
			JSExport<View>::AddFunctionProperty("removeAllAnnotations", std::mem_fn(&View::js_removeAllAnnotations));
			JSExport<View>::AddFunctionProperty("removeAnnotation", std::mem_fn(&View::js_removeAnnotation));
			JSExport<View>::AddFunctionProperty("removeAnnotations", std::mem_fn(&View::js_removeAnnotations));
			JSExport<View>::AddFunctionProperty("removeRoute", std::mem_fn(&View::js_removeRoute));
			JSExport<View>::AddFunctionProperty("selectAnnotation", std::mem_fn(&View::js_selectAnnotation));
			JSExport<View>::AddFunctionProperty("setLocation", std::mem_fn(&View::js_setLocation));
			JSExport<View>::AddFunctionProperty("showAnnotations", std::mem_fn(&View::js_showAnnotations));
			JSExport<View>::AddFunctionProperty("snapshot", std::mem_fn(&View::js_snapshot));
			JSExport<View>::AddFunctionProperty("zoom", std::mem_fn(&View::js_zoom));

			// properties
			JSExport<View>::AddValueProperty("animate", std::mem_fn(&View::js_get_animate), std::mem_fn(&View::js_set_animate));
			JSExport<View>::AddValueProperty("compassEnabled", std::mem_fn(&View::js_get_compassEnabled), std::mem_fn(&View::js_set_compassEnabled));
			JSExport<View>::AddValueProperty("enableZoomControls", std::mem_fn(&View::js_get_enableZoomControls), std::mem_fn(&View::js_set_enableZoomControls));
			JSExport<View>::AddValueProperty("mapType", std::mem_fn(&View::js_get_mapType), std::mem_fn(&View::js_set_mapType));
			JSExport<View>::AddValueProperty("maxZoomLevel", std::mem_fn(&View::js_get_maxZoomLevel));
			JSExport<View>::AddValueProperty("minZoomLevel", std::mem_fn(&View::js_get_minZoomLevel));
			JSExport<View>::AddValueProperty("pitchEnabled", std::mem_fn(&View::js_get_pitchEnabled), std::mem_fn(&View::js_set_pitchEnabled));
			JSExport<View>::AddValueProperty("region", std::mem_fn(&View::js_get_region), std::mem_fn(&View::js_set_region));
			JSExport<View>::AddValueProperty("rotateEnabled", std::mem_fn(&View::js_get_rotateEnabled), std::mem_fn(&View::js_set_rotateEnabled));
			JSExport<View>::AddValueProperty("showsBuildings", std::mem_fn(&View::js_get_showsBuildings), std::mem_fn(&View::js_set_showsBuildings));
			JSExport<View>::AddValueProperty("showsPointsOfInterest", std::mem_fn(&View::js_get_showsPointsOfInterest), std::mem_fn(&View::js_set_showsPointsOfInterest));
			JSExport<View>::AddValueProperty("traffic", std::mem_fn(&View::js_get_traffic), std::mem_fn(&View::js_set_traffic));
			JSExport<View>::AddValueProperty("userLocation", std::mem_fn(&View::js_get_userLocation), std::mem_fn(&View::js_set_userLocation));
			JSExport<View>::AddValueProperty("userLocationButton", std::mem_fn(&View::js_get_userLocationButton), std::mem_fn(&View::js_set_userLocationButton));
			JSExport<View>::AddValueProperty("zOrderOnTop", std::mem_fn(&View::js_get_zOrderOnTop), std::mem_fn(&View::js_set_zOrderOnTop));

			// prperty setter functions
			JSExport<View>::AddFunctionProperty("setAnimate", std::mem_fn(&View::js_setAnimate));
			JSExport<View>::AddFunctionProperty("setCompassEnabled", std::mem_fn(&View::js_setCompassEnabled));
			JSExport<View>::AddFunctionProperty("setEnableZoomControls", std::mem_fn(&View::js_setEnableZoomControls));
			JSExport<View>::AddFunctionProperty("setMapType", std::mem_fn(&View::js_setMapType));
			JSExport<View>::AddFunctionProperty("setPitchEnabled", std::mem_fn(&View::js_setPitchEnabled));
			JSExport<View>::AddFunctionProperty("setRegion", std::mem_fn(&View::js_setRegion));
			JSExport<View>::AddFunctionProperty("setRotateEnabled", std::mem_fn(&View::js_setRotateEnabled));
			JSExport<View>::AddFunctionProperty("setShowsBuildings", std::mem_fn(&View::js_setShowsBuildings));
			JSExport<View>::AddFunctionProperty("setShowsPointsOfInterest", std::mem_fn(&View::js_setShowsPointsOfInterest));
			JSExport<View>::AddFunctionProperty("setTraffic", std::mem_fn(&View::js_setTraffic));
			JSExport<View>::AddFunctionProperty("setUserLocation", std::mem_fn(&View::js_setUserLocation));
			JSExport<View>::AddFunctionProperty("setUserLocationButton", std::mem_fn(&View::js_setUserLocationButton));
			JSExport<View>::AddFunctionProperty("setZOrderOnTop", std::mem_fn(&View::js_setZOrderOnTop));
		}

		JSValue View::js_addAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);

			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			addAnnotation(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_addAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() > 0);

			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			addAnnotations(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_addRoute(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);

			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			addRoute(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_animateCamera(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() > 1) {
				auto _0 = arguments[0];
				auto _1 = arguments[1];
				TITANIUM_ASSERT(_0.IsObject());
				TITANIUM_ASSERT(_1.IsObject());
				animateCamera(static_cast<JSObject>(_0), static_cast<JSObject>(_1));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_deselectAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);

			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			deselectAnnotation(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_removeAllAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			removeAllAnnotations();
			return get_context().CreateUndefined();
		}

		JSValue View::js_removeAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);

			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			removeAnnotation(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_removeAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() > 0);

			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			removeAnnotations(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_removeRoute(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);
			
			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			removeRoute(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_selectAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);
			
			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			selectAnnotation(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_setLocation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);
			
			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsObject());
			setLocation(static_cast<JSObject>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_showAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() > 0) {
				showAnnotations(static_cast<JSObject>(arguments.at(0)));
			} else {
				showAnnotations();
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_snapshot(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			snapshot();
			return get_context().CreateUndefined();
		}

		JSValue View::js_zoom(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);
			
			auto _0 = arguments[0];
			TITANIUM_ASSERT(_0.IsNumber());
			zoom(static_cast<uint32_t>(_0));
			
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_animate() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_animate());
		}

		bool View::js_set_animate(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_animate(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setAnimate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_animate(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_enableZoomControls() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_enableZoomControls());
		}

		bool View::js_set_enableZoomControls(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_enableZoomControls(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setEnableZoomControls(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_enableZoomControls(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_compassEnabled() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_compassEnabled());
		}

		bool View::js_set_compassEnabled(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_compassEnabled(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setCompassEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_compassEnabled(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_mapType() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(get_mapType()));
		}

		bool View::js_set_mapType(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_mapType(Titanium::Map::Constants::to_MAP_TYPE(static_cast<std::underlying_type<Titanium::Map::MAP_TYPE>::type>(argument)));
			return true;
		}

		JSValue View::js_setMapType(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_mapType(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_maxZoomLevel() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_maxZoomLevel());
		}

		JSValue View::js_get_minZoomLevel() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_minZoomLevel());
		}

		JSValue View::js_get_pitchEnabled() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_pitchEnabled());
		}

		bool View::js_set_pitchEnabled(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_pitchEnabled(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setPitchEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_pitchEnabled(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_region() const TITANIUM_NOEXCEPT
		{
			const auto region = get_region();
			// convert struct to JSObject
			JSObject object = get_context().CreateObject();
			object.SetProperty("bearing", get_context().CreateNumber(region.bearing));
			object.SetProperty("latitude", get_context().CreateNumber(region.latitude));
			object.SetProperty("latitudeDelta", get_context().CreateNumber(region.latitudeDelta));
			object.SetProperty("longitude", get_context().CreateNumber(region.longitude));
			object.SetProperty("longitudeDelta", get_context().CreateNumber(region.longitudeDelta));
			object.SetProperty("tilt", get_context().CreateNumber(region.tilt));
			object.SetProperty("zoom", get_context().CreateNumber(region.zoom));
			return static_cast<JSValue>(object);
		}

		bool View::js_set_region(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			const auto mapRegionType = static_cast<JSObject>(argument);

			MapRegionType region;
			region.bearing = static_cast<double>(mapRegionType.GetProperty("bearing"));
			region.latitude = static_cast<double>(mapRegionType.GetProperty("latitude"));
			region.latitudeDelta = static_cast<double>(mapRegionType.GetProperty("latitudeDelta"));
			region.longitude = static_cast<double>(mapRegionType.GetProperty("longitude"));
			region.longitudeDelta = static_cast<double>(mapRegionType.GetProperty("longitudeDelta"));
			region.tilt = static_cast<double>(mapRegionType.GetProperty("tilt"));
			region.zoom = static_cast<uint32_t>(mapRegionType.GetProperty("zoom"));

			set_region(region);
			return true;
		}

		JSValue View::js_setRegion(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_region(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_rotateEnabled() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_rotateEnabled());
		}

		bool View::js_set_rotateEnabled(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_rotateEnabled(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setRotateEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_rotateEnabled(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_showsBuildings() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_showsBuildings());
		}

		bool View::js_set_showsBuildings(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_showsBuildings(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setShowsBuildings(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_showsBuildings(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_showsPointsOfInterest() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_showsPointsOfInterest());
		}

		bool View::js_set_showsPointsOfInterest(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_showsPointsOfInterest(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setShowsPointsOfInterest(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_showsPointsOfInterest(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_traffic() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_traffic());
		}

		bool View::js_set_traffic(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_traffic(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setTraffic(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_traffic(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_userLocation() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_userLocation());
		}

		bool View::js_set_userLocation(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_userLocation(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setUserLocation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_userLocation(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_userLocationButton() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_userLocationButton());
		}

		bool View::js_set_userLocationButton(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_userLocationButton(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setUserLocationButton(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_userLocationButton(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_zOrderOnTop() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_zOrderOnTop());
		}

		bool View::js_set_zOrderOnTop(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_zOrderOnTop(static_cast<bool>(argument));
			return true;
		}

		JSValue View::js_setZOrderOnTop(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_zOrderOnTop(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

	} // namespace Map
}  // namespace Titanium