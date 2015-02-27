/**
 * Titanium.Map for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MAP_HPP_
#define _TITANIUM_MAP_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Map/Constants.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Titanium Map Module.
	  See http://docs.appcelerator.com/titanium/3.0/#!/api/Modules.Map
	*/
	class TITANIUMKIT_EXPORT MapModule : public Module, public JSExport<MapModule>
	{

	public:
		virtual JSValue HYBRID_TYPE() const TITANIUM_NOEXCEPT;
		virtual JSValue SATELLITE_TYPE() const TITANIUM_NOEXCEPT;
		virtual JSValue NORMAL_TYPE() const TITANIUM_NOEXCEPT;
		virtual JSValue TERRAIN_TYPE() const TITANIUM_NOEXCEPT;

		virtual JSValue ANNOTATION_DRAG_STATE_END() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_DRAG_STATE_START() const TITANIUM_NOEXCEPT;

		virtual JSValue ANNOTATION_AZURE() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_BLUE() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_CYAN() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_GREEN() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_MAGENTA() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_ORANGE() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_PURPLE() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_RED() const TITANIUM_NOEXCEPT;	
		virtual JSValue ANNOTATION_ROSE() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_VIOLET() const TITANIUM_NOEXCEPT;
		virtual JSValue ANNOTATION_YELLOW() const TITANIUM_NOEXCEPT;

		virtual JSValue OVERLAY_LEVEL_ABOVE_LABELS() const TITANIUM_NOEXCEPT;
		virtual JSValue OVERLAY_LEVEL_ABOVE_ROADS() const TITANIUM_NOEXCEPT;

		virtual JSValue SERVICE_DISABLED() const TITANIUM_NOEXCEPT;
		virtual JSValue SERVICE_INVALID() const TITANIUM_NOEXCEPT;
		virtual JSValue SERVICE_MISSING() const TITANIUM_NOEXCEPT;
		virtual JSValue SERVICE_VERSION_UPDATE_REQUIRED() const TITANIUM_NOEXCEPT;
		virtual JSValue SUCCESS() const TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract createMapView
		  @discussion Creates and returns an instance of <Titanium.Map.View>.
		*/
		virtual JSValue createView(JSObject parameters) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract createAnnotation
		  @discussion Creates and returns an instance of <Titanium.Map.Annotation>.
		*/
		virtual JSValue createAnnotation(JSObject parameters) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract createRoute
		  @discussion Creates and returns an instance of <Titanium.Map.Route>.
		*/
		virtual JSValue createRoute(JSObject parameters) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract createCamera
		  @discussion Creates and returns an instance of <Titanium.Map.Camera>.
		*/
		virtual JSValue createCamera(JSObject parameters) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract isGooglePlayServicesAvailable
		  @discussion Returns a code to indicate whether Google Play Services is available on the device.
		*/
		virtual Titanium::Map::GOOGLE_PLAY_SERVICE_STATE isGooglePlayServicesAvailable() TITANIUM_NOEXCEPT;

		MapModule(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~MapModule() = default;
		MapModule(const MapModule&) = default;
		MapModule& operator=(const MapModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		MapModule(MapModule&&)                 = default;
		MapModule& operator=(MapModule&&)      = default;
#endif

		static void JSExportInitialize();

		virtual JSValue js_createView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_createAnnotation(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_createRoute(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_createCamera(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_isGoogleMapServicesAvailable(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

	private:
		JSValue hybrid_type__;
		JSValue satellite_type__;
		JSValue normal_type__;
		JSValue terrain_type__;
		JSValue annotation_drag_state_end__;
		JSValue annotation_drag_state_start__;
		JSValue annotation_azure__;
		JSValue annotation_blue__;
		JSValue annotation_cyan__;
		JSValue annotation_green__;
		JSValue annotation_magenta__;
		JSValue annotation_orange__;
		JSValue annotation_purple__;
		JSValue annotation_red__;
		JSValue annotation_rose__;
		JSValue annotation_violet__;
		JSValue annotation_yellow__;
		JSValue overlay_level_above_labels__;
		JSValue overlay_level_above_roads__;
		JSValue service_disabled__;
		JSValue service_invalid__;
		JSValue service_missing__;
		JSValue service_version_update_required__;
		JSValue success__;
	};
} // namespace Titanium
#endif // _TITANIUM_MAP_HPP_