/**
 * TitaniumKit Titanium.UI.MapView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_MAPVIEW_HPP_
#define _TITANIUM_UI_MAPVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/Map/Constants.hpp"

namespace Titanium 
{
	namespace UI 
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium MapView Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.MapView
		 */
		class TITANIUMKIT_EXPORT MapView : public View, public JSExport<MapView> 
		{

		public:

			struct MapRegionType {
				double bearing;
				double latitude;
				double latitudeDelta;
				double longitude;
				double longitudeDelta;
				double tilt;
				double zoom;
			};

			virtual Titanium::Map::MAP_TYPE mapType() const TITANIUM_NOEXCEPT;
			virtual void setMapType(Titanium::Map::MAP_TYPE mapType) TITANIUM_NOEXCEPT;

			virtual JSValue region() const TITANIUM_NOEXCEPT;
			virtual void setRegion(JSObject& region) TITANIUM_NOEXCEPT;

			virtual uint32_t zoom() const TITANIUM_NOEXCEPT;
			virtual void setZoom(int zoom) TITANIUM_NOEXCEPT;

			virtual uint32_t maxZoomLevel() const TITANIUM_NOEXCEPT;
			virtual void setMaxZoomLevel(int zoom) TITANIUM_NOEXCEPT;

			virtual uint32_t minZoomLevel() const TITANIUM_NOEXCEPT;
			virtual void setMinZoomLevel(int zoom) TITANIUM_NOEXCEPT;

			virtual void showAnnotations() TITANIUM_NOEXCEPT;
			virtual void showAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT;
			virtual void snapshot() TITANIUM_NOEXCEPT;
			virtual void addAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT;
			virtual void addAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT;
			virtual void addRoute(JSObject& route) TITANIUM_NOEXCEPT;
			virtual void animateCamera(JSObject& animationParams, JSObject& callback) TITANIUM_NOEXCEPT;
			virtual void deselectAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT;
			virtual void removeAllAnnotations() TITANIUM_NOEXCEPT;
			virtual void removeAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT;
			virtual void removeAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT;
			virtual void removeRoute(JSObject& route) TITANIUM_NOEXCEPT;
			virtual void selectAnnotation(JSObject& annotation) TITANIUM_NOEXCEPT;
			
			virtual bool animate() const TITANIUM_NOEXCEPT;
			virtual void setAnimate(bool animate) TITANIUM_NOEXCEPT;
			
			//virtual void annotations() const TITANIUM_NOEXCEPT;
			//virtual void setAnnotations(JSObject& annotations) TITANIUM_NOEXCEPT;

			//virtual void camera() const TITANIUM_NOEXCEPT;
			//virtual void setCamera(JSObject& camera) TITANIUM_NOEXCEPT;

			virtual bool compassEnabled() const TITANIUM_NOEXCEPT;
			virtual void setCompassEnabled(bool compass) TITANIUM_NOEXCEPT;

			virtual bool enableZoomControls() const TITANIUM_NOEXCEPT;
			virtual void setEnableZoomControls(bool zoomControls) TITANIUM_NOEXCEPT;
			 
			virtual bool pitchEnabled() const TITANIUM_NOEXCEPT;
			virtual void setPitchEnabled(bool pitch) TITANIUM_NOEXCEPT;

			virtual bool rotateEnabled() const TITANIUM_NOEXCEPT;
			virtual void setRotateEnabled(bool rotate) TITANIUM_NOEXCEPT;

			virtual bool showsBuildings() const TITANIUM_NOEXCEPT;
			virtual void setShowsBuildings(bool buildings) TITANIUM_NOEXCEPT;

			virtual bool showsPointsOfInterest() const TITANIUM_NOEXCEPT;
			virtual void setShowsPointsOfInterest(bool poi) TITANIUM_NOEXCEPT;

			virtual bool traffic() const TITANIUM_NOEXCEPT;
			virtual void setTraffic(bool traffic) TITANIUM_NOEXCEPT;

			virtual bool userLocation() const TITANIUM_NOEXCEPT;
			virtual void setUserLocation(bool userLocation) TITANIUM_NOEXCEPT;

			virtual bool userLocationButton() const TITANIUM_NOEXCEPT;
			virtual void setUserLocationButton(bool userLocationButton) TITANIUM_NOEXCEPT;

			virtual bool zOrderOnTop() const TITANIUM_NOEXCEPT;
			virtual void setZOrderOnTop(bool zOrderOnTop) TITANIUM_NOEXCEPT;

			virtual MapRegionType getMapRegionType(JSObject& mapRegionType) TITANIUM_NOEXCEPT;

			MapView(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
			virtual ~MapView() = default;
			MapView(const MapView&) = default;
			MapView& operator=(const MapView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			MapView(MapView&&)                 = default;
			MapView& operator=(MapView&&)      = default;
#endif

			static void JSExportInitialize();

			JSValue js_showAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_snapshot(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_addAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_addAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_addRoute(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_animateCamera(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_deselectAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_removeAllAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_removeAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_removeAnnotations(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_removeRoute(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;
			JSValue js_selectAnnotation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_animate() const TITANIUM_NOEXCEPT;
			bool js_set_animate(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setAnimate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_compassEnabled() const TITANIUM_NOEXCEPT;
			bool js_set_compassEnabled(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setCompassEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_enableZoomControls() const TITANIUM_NOEXCEPT;
			bool js_set_enableZoomControls(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setEnableZoomControls(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_mapType() const TITANIUM_NOEXCEPT;
			bool js_set_mapType(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setMapType(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_region() const TITANIUM_NOEXCEPT;
			bool js_set_region(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setRegion(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_setZoomLevel(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_maxZoomLevel() const TITANIUM_NOEXCEPT;
			bool js_set_maxZoomLevel(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setMaxZoomLevel(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_minZoomLevel() const TITANIUM_NOEXCEPT;
			bool js_set_minZoomLevel(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setMinZoomLevel(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_pitchEnabled() const TITANIUM_NOEXCEPT;
			bool js_set_pitchEnabled(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setPitchEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_rotateEnabled() const TITANIUM_NOEXCEPT;
			bool js_set_rotateEnabled(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setRotateEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_showsBuildings() const TITANIUM_NOEXCEPT;
			bool js_set_showsBuildings(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setShowsBuildings(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_showsPointsOfInterest() const TITANIUM_NOEXCEPT;
			bool js_set_showsPointsOfInterest(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setShowsPointsOfInterest(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_traffic() const TITANIUM_NOEXCEPT;
			bool js_set_traffic(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setTraffic(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_userLocation() const TITANIUM_NOEXCEPT;
			bool js_set_userLocation(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setUserLocation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_userLocationButton() const TITANIUM_NOEXCEPT;
			bool js_set_userLocationButton(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setUserLocationButton(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			JSValue js_get_zOrderOnTop() const TITANIUM_NOEXCEPT;
			bool js_set_zOrderOnTop(const JSValue& argument) TITANIUM_NOEXCEPT;
			JSValue js_setZOrderOnTop(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

			bool animate__;
			// Titanium::Map::Annotation annotations__[];
			// Titanium::Map::Camera camera__;
			bool compassEnabled__;
			bool enableZoomControls__;
			Titanium::Map::MAP_TYPE mapType__;
			MapRegionType region__;
			uint32_t zoom__;
			uint32_t maxZoomLevel__;
			uint32_t minZoomLevel__;
			bool pitchEnabled__;
			bool rotateEnabled__;
			bool showsBuildings__;
			bool showsPointsOfInterest__;
			bool traffic__;
			bool userLocation__;
			bool userLocationButton__;
			bool zOrderOnTop__;
		};
	} // namespace UI
}  // namespace Titanium
#endif // _TITANIUM_UI_MAPVIEW_HPP_