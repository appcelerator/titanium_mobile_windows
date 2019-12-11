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

#ifdef SERVICE_DISABLED
#pragma push_macro("SERVICE_DISABLED")
#undef SERVICE_DISABLED
#define _restore_SERVICE_DISABLED_
#endif

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
		TITANIUM_PROPERTY_READONLY_DEF(Annotation);
		TITANIUM_PROPERTY_READONLY_DEF(Camera);
		TITANIUM_PROPERTY_READONLY_DEF(Route);
		TITANIUM_PROPERTY_READONLY_DEF(View);

		TITANIUM_PROPERTY_READONLY_DEF(HYBRID_TYPE);
		TITANIUM_PROPERTY_READONLY_DEF(SATELLITE_TYPE);
		TITANIUM_PROPERTY_READONLY_DEF(NORMAL_TYPE);
		TITANIUM_PROPERTY_READONLY_DEF(TERRAIN_TYPE);

		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_DRAG_STATE_END);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_DRAG_STATE_START);

		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_AZURE);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_BLUE);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_CYAN);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_GREEN);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_MAGENTA);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_ORANGE);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_PURPLE);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_RED);	
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_ROSE);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_VIOLET);
		TITANIUM_PROPERTY_READONLY_DEF(ANNOTATION_YELLOW);

		TITANIUM_PROPERTY_READONLY_DEF(OVERLAY_LEVEL_ABOVE_LABELS);
		TITANIUM_PROPERTY_READONLY_DEF(OVERLAY_LEVEL_ABOVE_ROADS);

		TITANIUM_PROPERTY_READONLY_DEF(SERVICE_DISABLED);
		TITANIUM_PROPERTY_READONLY_DEF(SERVICE_INVALID);
		TITANIUM_PROPERTY_READONLY_DEF(SERVICE_MISSING);
		TITANIUM_PROPERTY_READONLY_DEF(SERVICE_VERSION_UPDATE_REQUIRED);
		TITANIUM_PROPERTY_READONLY_DEF(SUCCESS);

		/*!
		  @method
		  @abstract createAnnotation
		  @discussion Creates and returns an instance of <Titanium.Map.Annotation>.
		*/
		JSObject createAnnotation(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract createCamera
		  @discussion Creates and returns an instance of <Titanium.Map.Camera>.
		*/
		JSObject createCamera(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract createRoute
		  @discussion Creates and returns an instance of <Titanium.Map.Route>.
		*/
		JSObject createRoute(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract createMapView
		  @discussion Creates and returns an instance of <Titanium.Map.View>.
		*/
		JSObject createView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract isGooglePlayServicesAvailable
		  @discussion Returns a code to indicate whether Google Play Services is available on the device.
		*/
		Titanium::Map::GOOGLE_PLAY_SERVICE_STATE isGooglePlayServicesAvailable() TITANIUM_NOEXCEPT;

		MapModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~MapModule() = default;
		MapModule(const MapModule&) = default;
		MapModule& operator=(const MapModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		MapModule(MapModule&&)                 = default;
		MapModule& operator=(MapModule&&)      = default;
#endif

		static void JSExportInitialize();

		TITANIUM_FUNCTION_DEF(createAnnotation);
		TITANIUM_FUNCTION_DEF(createCamera);
		TITANIUM_FUNCTION_DEF(createRoute);
		TITANIUM_FUNCTION_DEF(createView);
		TITANIUM_FUNCTION_DEF(isGooglePlayServicesAvailable);

		MapModule& ViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		MapModule& AnnotationClass(const JSClass&) TITANIUM_NOEXCEPT;
		MapModule& CameraClass(const JSClass&) TITANIUM_NOEXCEPT;
		MapModule& RouteClass(const JSClass&) TITANIUM_NOEXCEPT;

	protected:
		JSClass annotation__;
		JSClass camera__;
		JSClass route__;
		JSClass view__;
	};
} // namespace Titanium

#ifdef _restore_SERVICE_DISABLED_
#pragma pop_macro("SERVICE_DISABLED")
#undef _restore_SERVICE_DISABLED_
#endif

#endif // _TITANIUM_MAP_HPP_
