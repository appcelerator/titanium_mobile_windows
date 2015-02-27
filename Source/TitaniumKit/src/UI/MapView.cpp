/**
 * TitaniumKit Titanium.UI.MapView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/MapView.hpp"

namespace Titanium
{
	namespace UI
	{
		MapView::MapView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: View(js_context, arguments),
			animate__(false),
			compassEnabled__(false),
			enableZoomControls__(false),
			mapType__(Titanium::Map::MAP_TYPE::NORMAL),
			region__({0}),
			zoom__(16),
			maxZoomLevel__(0),
			minZoomLevel__(0),
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

		void MapView::JSExportInitialize() {
			JSExport<MapView>::SetClassVersion(1);
			JSExport<MapView>::SetParent(JSExport<Module>::Class());

			JSExport<MapView>::AddFunctionProperty("showAnnotations", std::mem_fn(&js_showAnnotations));
			JSExport<MapView>::AddFunctionProperty("snapshot", std::mem_fn(&js_snapshot));
			JSExport<MapView>::AddFunctionProperty("addAnnotation", std::mem_fn(&js_addAnnotation));
			JSExport<MapView>::AddFunctionProperty("addAnnotations", std::mem_fn(&js_addAnnotations));
			JSExport<MapView>::AddFunctionProperty("addRoute", std::mem_fn(&js_addRoute));
			JSExport<MapView>::AddFunctionProperty("animateCamera", std::mem_fn(&js_animateCamera));
			JSExport<MapView>::AddFunctionProperty("deselectAnnotation", std::mem_fn(&js_deselectAnnotation));
			JSExport<MapView>::AddFunctionProperty("removeAllAnnotations", std::mem_fn(&js_removeAllAnnotations));
			JSExport<MapView>::AddFunctionProperty("removeAnnotation", std::mem_fn(&js_removeAnnotation));
			JSExport<MapView>::AddFunctionProperty("removeAnnotations", std::mem_fn(&js_removeAnnotations));
			JSExport<MapView>::AddFunctionProperty("removeRoute", std::mem_fn(&js_removeRoute));
			JSExport<MapView>::AddFunctionProperty("selectAnnotation", std::mem_fn(&js_selectAnnotation));

			JSExport<MapView>::AddValueProperty("animate", std::mem_fn(&js_get_animate), std::mem_fn(&js_set_animate));
			JSExport<MapView>::AddFunctionProperty("setAnimate", std::mem_fn(&js_setAnimate));

			JSExport<MapView>::AddValueProperty("compassEnabled", std::mem_fn(&js_get_compassEnabled), std::mem_fn(&js_set_compassEnabled));
			JSExport<MapView>::AddFunctionProperty("setCompassEnabled", std::mem_fn(&js_setCompassEnabled));

			JSExport<MapView>::AddValueProperty("enableZoomControls", std::mem_fn(&js_get_enableZoomControls), std::mem_fn(&js_set_enableZoomControls));
			JSExport<MapView>::AddFunctionProperty("setEnableZoomControls", std::mem_fn(&js_setEnableZoomControls));

			JSExport<MapView>::AddValueProperty("mapType", std::mem_fn(&js_get_mapType), std::mem_fn(&js_set_mapType));
			JSExport<MapView>::AddFunctionProperty("setMapType", std::mem_fn(&js_setMapType));

			JSExport<MapView>::AddValueProperty("region", std::mem_fn(&js_get_region), std::mem_fn(&js_set_region));
			JSExport<MapView>::AddFunctionProperty("setRegion", std::mem_fn(&js_setRegion));

			JSExport<MapView>::AddValueProperty("maxZoomLevel", std::mem_fn(&js_get_maxZoomLevel), std::mem_fn(&js_set_maxZoomLevel));
			JSExport<MapView>::AddFunctionProperty("setMaxZoomLevel", std::mem_fn(&js_setMaxZoomLevel));

			JSExport<MapView>::AddValueProperty("minZoomLevel", std::mem_fn(&js_get_minZoomLevel), std::mem_fn(&js_set_minZoomLevel));
			JSExport<MapView>::AddFunctionProperty("setMinZoomLevel", std::mem_fn(&js_setMinZoomLevel));

			JSExport<MapView>::AddValueProperty("pitchEnabled", std::mem_fn(&js_get_pitchEnabled), std::mem_fn(&js_set_pitchEnabled));
			JSExport<MapView>::AddFunctionProperty("setPitchEnabled", std::mem_fn(&js_setPitchEnabled));

			JSExport<MapView>::AddValueProperty("rotateEnabled", std::mem_fn(&js_get_rotateEnabled), std::mem_fn(&js_set_rotateEnabled));
			JSExport<MapView>::AddFunctionProperty("setRotateEnabled", std::mem_fn(&js_setRotateEnabled));

			JSExport<MapView>::AddValueProperty("showsBuildings", std::mem_fn(&js_get_showsBuildings), std::mem_fn(&js_set_showsBuildings));
			JSExport<MapView>::AddFunctionProperty("setShowsBuildings", std::mem_fn(&js_setShowsBuildings));

			JSExport<MapView>::AddValueProperty("showsPointsOfInterest", std::mem_fn(&js_get_showsPointsOfInterest), std::mem_fn(&js_set_showsPointsOfInterest));
			JSExport<MapView>::AddFunctionProperty("setShowsPointsOfInterest", std::mem_fn(&js_setShowsPointsOfInterest));

			JSExport<MapView>::AddValueProperty("traffic", std::mem_fn(&js_get_traffic), std::mem_fn(&js_set_traffic));
			JSExport<MapView>::AddFunctionProperty("setTraffic", std::mem_fn(&js_setTraffic));

			JSExport<MapView>::AddValueProperty("userLocation", std::mem_fn(&js_get_userLocation), std::mem_fn(&js_set_userLocation));
			JSExport<MapView>::AddFunctionProperty("setUserLocation", std::mem_fn(&js_setUserLocation));

			JSExport<MapView>::AddValueProperty("userLocationButton", std::mem_fn(&js_get_userLocationButton), std::mem_fn(&js_set_userLocationButton));
			JSExport<MapView>::AddFunctionProperty("setUserLocationButton", std::mem_fn(&js_setUserLocationButton));

			JSExport<MapView>::AddValueProperty("zOrderOnTop", std::mem_fn(&js_get_zOrderOnTop), std::mem_fn(&js_set_zOrderOnTop));
			JSExport<MapView>::AddFunctionProperty("setZOrderOnTop", std::mem_fn(&js_setZOrderOnTop));

			JSExport<MapView>::AddFunctionProperty("zoom", std::mem_fn(&js_setZoomLevel));
		}

		void MapView::showAnnotations() TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::showAnnotations: Unimplemented");
		}

		void MapView::showAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::showAnnotations: Unimplemented");
		}

		void MapView::snapshot() TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::snapshot: Unimplemented");
		}
		
		void MapView::addAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::addAnnotation: Unimplemented");
		}
		
		void MapView::addAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::addAnnotations: Unimplemented");
		}
		
		void MapView::addRoute(JSObject& route) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::addRoute: Unimplemented");
		}
		
		void MapView::animateCamera(JSObject& animationParams, JSObject& callback) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::animateCamera: Unimplemented");
		}
		
		void MapView::deselectAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::deselectAnnotation: Unimplemented");
		}
		
		void MapView::removeAllAnnotations() TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::removeAllAnnotations: Unimplemented");
		}
		
		void MapView::removeAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::removeAnnotation: Unimplemented");
		}
		
		void MapView::removeAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::removeAnnotations: Unimplemented");
		}
		
		void MapView::removeRoute(JSObject& route) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::removeRoute: Unimplemented");
		}
		
		void MapView::selectAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT {
			TITANIUM_LOG_WARN("Map::View::selectAnnotation: Unimplemented");
		}

		// TODO : Implement Titanium.Map.Annotation and Titanium.Map.Camera
		/*void MapView::annotations() const TITANIUM_NOEXCEPT {
		}

		void MapView::setAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT {
		}

		void MapView::camera() const TITANIUM_NOEXCEPT {
		}

		void MapView::setCamera(JSObject& camera) TITANIUM_NOEXCEPT {
		}*/
			
		bool MapView::animate() const TITANIUM_NOEXCEPT {
			return animate__;
		}

		void MapView::setAnimate(bool animate) TITANIUM_NOEXCEPT {
			animate__ = animate;
		}

		bool MapView::compassEnabled() const TITANIUM_NOEXCEPT {
			return compassEnabled__;
		}

		void MapView::setCompassEnabled(bool compass) TITANIUM_NOEXCEPT {
			compassEnabled__ = compass;
		}

		bool MapView::enableZoomControls() const TITANIUM_NOEXCEPT {
			return enableZoomControls__;
		}
		
		void MapView::setEnableZoomControls(bool zoomControls) TITANIUM_NOEXCEPT {
			enableZoomControls__ = zoomControls;
		}

		Titanium::Map::MAP_TYPE MapView::mapType() const TITANIUM_NOEXCEPT {
			return mapType__;
		}

		void MapView::setMapType(Titanium::Map::MAP_TYPE mapType) TITANIUM_NOEXCEPT {
			mapType__ = mapType;
		}

		MapView::MapRegionType MapView::getMapRegionType(JSObject& mapRegionType) {
			MapRegionType region;

			region.bearing = static_cast<double>(mapRegionType.GetProperty("bearing"));
			region.latitude = static_cast<double>(mapRegionType.GetProperty("latitude"));
			region.latitudeDelta = static_cast<double>(mapRegionType.GetProperty("latitudeDelta"));
			region.longitude = static_cast<double>(mapRegionType.GetProperty("longitude"));
			region.longitudeDelta = static_cast<double>(mapRegionType.GetProperty("longitudeDelta"));
			region.tilt = static_cast<double>(mapRegionType.GetProperty("tilt"));
			region.zoom = static_cast<double>(mapRegionType.GetProperty("zoom"));

			return region;
		}

		JSValue MapView::region() const TITANIUM_NOEXCEPT {
			JSObject region = get_context().CreateObject();

			region.SetProperty("bearing", get_context().CreateNumber(region__.bearing));
			region.SetProperty("latitude", get_context().CreateNumber(region__.latitude));
			region.SetProperty("latitudeDelta", get_context().CreateNumber(region__.latitudeDelta));
			region.SetProperty("longitude", get_context().CreateNumber(region__.longitude));
			region.SetProperty("longitudeDelta", get_context().CreateNumber(region__.longitudeDelta));
			region.SetProperty("tilt", get_context().CreateNumber(region__.tilt));
			region.SetProperty("zoom", get_context().CreateNumber(region__.zoom));

			return static_cast<JSValue>(region);
		}

		void MapView::setRegion(JSObject& region) TITANIUM_NOEXCEPT {
			region__ = getMapRegionType(region);
		}

		uint32_t MapView::zoom() const TITANIUM_NOEXCEPT {
			return zoom__;
		}

		void MapView::setZoom(int zoom) TITANIUM_NOEXCEPT {
			zoom__ = zoom;
		}

		uint32_t MapView::minZoomLevel() const TITANIUM_NOEXCEPT {
			return minZoomLevel__;
		}

		void MapView::setMinZoomLevel(int zoom) TITANIUM_NOEXCEPT {
			minZoomLevel__ = zoom;
		}

		uint32_t MapView::maxZoomLevel() const TITANIUM_NOEXCEPT {
			return maxZoomLevel__;
		}

		void MapView::setMaxZoomLevel(int zoom) TITANIUM_NOEXCEPT {
			maxZoomLevel__ = zoom;
		}

		bool MapView::pitchEnabled() const TITANIUM_NOEXCEPT {
			return pitchEnabled__;
		}

		void MapView::setPitchEnabled(bool pitch) TITANIUM_NOEXCEPT {
			pitchEnabled__ = pitch;
		}

		bool MapView::rotateEnabled() const TITANIUM_NOEXCEPT {
			return rotateEnabled__;
		}

		void MapView::setRotateEnabled(bool rotate) TITANIUM_NOEXCEPT {
			rotateEnabled__ = rotate;
		}

		bool MapView::showsBuildings() const TITANIUM_NOEXCEPT {
			return showsBuildings__;
		}

		void MapView::setShowsBuildings(bool buildings) TITANIUM_NOEXCEPT {
			showsBuildings__ = buildings;
		}

		bool MapView::showsPointsOfInterest() const TITANIUM_NOEXCEPT {
			return showsPointsOfInterest__;
		}

		void MapView::setShowsPointsOfInterest(bool poi) TITANIUM_NOEXCEPT {
			showsPointsOfInterest__ = poi;
		}

		bool MapView::traffic() const TITANIUM_NOEXCEPT {
			return traffic__;
		}

		void MapView::setTraffic(bool traffic) TITANIUM_NOEXCEPT {
			traffic__ = traffic;
		}

		bool MapView::userLocation() const TITANIUM_NOEXCEPT {
			return userLocation__;
		}

		void MapView::setUserLocation(bool userLocation) TITANIUM_NOEXCEPT {
			userLocation__ = userLocation;
		}

		bool MapView::userLocationButton() const TITANIUM_NOEXCEPT {
			return userLocationButton__;
		}

		void MapView::setUserLocationButton(bool userLocationButton) TITANIUM_NOEXCEPT {
			userLocationButton__ = userLocationButton;
		}

		bool MapView::zOrderOnTop() const TITANIUM_NOEXCEPT {
			return zOrderOnTop__;
		}

		void MapView::setZOrderOnTop(bool zOrderOnTop) TITANIUM_NOEXCEPT {
			zOrderOnTop__ = zOrderOnTop;
		}

		JSValue MapView::js_showAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				showAnnotations(static_cast<JSObject>(arguments[0]));
			} else {
				showAnnotations();
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_snapshot(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			snapshot();
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_addAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				addAnnotation(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_addAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				addAnnotations(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_addRoute(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				addRoute(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_animateCamera(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 1) {
				auto _0 = arguments[0];
				auto _1 = arguments[1];
				TITANIUM_ASSERT(_0.IsObject());
				TITANIUM_ASSERT(_1.IsObject());
				animateCamera(static_cast<JSObject>(_0), static_cast<JSObject>(_1));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_deselectAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				deselectAnnotation(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_removeAllAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			removeAllAnnotations();
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_removeAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				removeAnnotation(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_removeAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				removeAnnotations(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_removeRoute(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				removeRoute(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_selectAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
			if (arguments.size() > 0) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsObject());
				selectAnnotation(static_cast<JSObject>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_animate() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(animate());
		}

		bool MapView::js_set_animate(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setAnimate(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setAnimate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_animate(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_enableZoomControls() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(enableZoomControls());
		}

		bool MapView::js_set_enableZoomControls(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setEnableZoomControls(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setEnableZoomControls(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_enableZoomControls(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_compassEnabled() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(compassEnabled());
		}

		bool MapView::js_set_compassEnabled(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setCompassEnabled(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setCompassEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_compassEnabled(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_mapType() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(Titanium::Map::Constants::to_underlying_type(mapType()));
		}

		bool MapView::js_set_mapType(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setMapType(Titanium::Map::Constants::to_MAP_TYPE(static_cast<std::underlying_type<Titanium::Map::MAP_TYPE>::type>(argument)));
			return true;
		}

		JSValue MapView::js_setMapType(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_mapType(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_region() const TITANIUM_NOEXCEPT
		{
			return region();
		}

		bool MapView::js_set_region(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			setRegion(static_cast<JSObject>(argument));
			return true;
		}

		JSValue MapView::js_setRegion(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_region(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_setZoomLevel(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				auto _0 = arguments[0];
				TITANIUM_ASSERT(_0.IsNumber());
				setZoom(static_cast<uint32_t>(_0));
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_maxZoomLevel() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_maxZoomLevel(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setMaxZoomLevel(static_cast<uint32_t>(argument));
			return true;
		}

		JSValue MapView::js_setMaxZoomLevel(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_maxZoomLevel(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_minZoomLevel() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(minZoomLevel__);
		}

		bool MapView::js_set_minZoomLevel(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setMinZoomLevel(static_cast<uint32_t>(argument));
			return true;
		}

		JSValue MapView::js_setMinZoomLevel(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_minZoomLevel(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_pitchEnabled() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_pitchEnabled(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setPitchEnabled(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setPitchEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_pitchEnabled(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_rotateEnabled() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_rotateEnabled(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setRotateEnabled(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setRotateEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_rotateEnabled(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_showsBuildings() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_showsBuildings(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setShowsBuildings(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setShowsBuildings(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_showsBuildings(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_showsPointsOfInterest() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_showsPointsOfInterest(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setShowsPointsOfInterest(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setShowsPointsOfInterest(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_showsPointsOfInterest(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_traffic() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_traffic(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setTraffic(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setTraffic(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_traffic(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_userLocation() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_userLocation(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setUserLocation(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setUserLocation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_userLocation(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_userLocationButton() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_userLocationButton(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setUserLocationButton(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setUserLocationButton(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_userLocationButton(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

		JSValue MapView::js_get_zOrderOnTop() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(maxZoomLevel__);
		}

		bool MapView::js_set_zOrderOnTop(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			setZOrderOnTop(static_cast<bool>(argument));
			return true;
		}

		JSValue MapView::js_setZOrderOnTop(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_zOrderOnTop(arguments[0]);
			}
			return get_context().CreateUndefined();
		}

	} // namespace UI
}  // namespace Titanium