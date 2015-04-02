/**
 * TitaniumKit Titanium.Geolocation
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GEOLOCATION_HPP_
#define _TITANIUM_GEOLOCATION_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Geolocation/Constants.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Titanium Geolocation Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Geolocation
	*/
	class TITANIUMKIT_EXPORT GeolocationModule : public Module, public JSExport<GeolocationModule>
	{

	public:

		virtual JSValue ACCURACY_BEST() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACCURACY_BEST_FOR_NAVIGATION() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACCURACY_HUNDRED_METERS() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACCURACY_KILOMETER() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACCURACY_NEAREST_TEN_METERS() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACCURACY_THREE_KILOMETERS() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACCURACY_HIGH() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACCURACY_LOW() const TITANIUM_NOEXCEPT final;

		virtual JSValue ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACTIVITYTYPE_FITNESS() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACTIVITYTYPE_OTHER() const TITANIUM_NOEXCEPT final;
		virtual JSValue ACTIVITYTYPE_OTHER_NAVIGATION() const TITANIUM_NOEXCEPT final;

		virtual JSValue AUTHORIZATION_ALWAYS() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTHORIZATION_AUTHORIZED() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTHORIZATION_DENIED() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTHORIZATION_RESTRICTED() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTHORIZATION_UNKNOWN() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTHORIZATION_WHEN_IN_USE() const TITANIUM_NOEXCEPT final;

		virtual JSValue ERROR_DENIED() const TITANIUM_NOEXCEPT final;
		virtual JSValue ERROR_HEADING_FAILURE() const TITANIUM_NOEXCEPT final;
		virtual JSValue ERROR_LOCATION_UNKNOWN() const TITANIUM_NOEXCEPT final;
		virtual JSValue ERROR_NETWORK() const TITANIUM_NOEXCEPT final;
		virtual JSValue ERROR_REGION_MONITORING_DELAYED() const TITANIUM_NOEXCEPT final;
		virtual JSValue ERROR_REGION_MONITORING_DENIED() const TITANIUM_NOEXCEPT final;
		virtual JSValue ERROR_REGION_MONITORING_FAILURE() const TITANIUM_NOEXCEPT final;
		virtual JSValue ERROR_TIMEOUT() const TITANIUM_NOEXCEPT final;

		virtual JSValue PROVIDER_GPS() const TITANIUM_NOEXCEPT final;
		virtual JSValue PROVIDER_NETWORK() const TITANIUM_NOEXCEPT final;
		virtual JSValue PROVIDER_PASSIVE() const TITANIUM_NOEXCEPT final;
		
		/*!
		  @property
		  @abstract accuracy
		  @discussion Specifies the requested accuracy for location updates.
		*/
		virtual Geolocation::ACCURACY get_accuracy() const TITANIUM_NOEXCEPT;
		virtual void set_accuracy(const Geolocation::ACCURACY accuracy) TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract activityType
		  @discussion The type of user activity to be associated with the location updates.
		*/
		virtual Geolocation::ACTIVITYTYPE get_activityType() const TITANIUM_NOEXCEPT;
		virtual void set_activityType(const Geolocation::ACTIVITYTYPE activityType) TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract distanceFilter
		  @discussion The minimum change of position (in meters) before a 'location' event is fired.
		*/
		virtual double get_distanceFilter() const TITANIUM_NOEXCEPT;
		virtual void set_distanceFilter(const double distance) TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract headingFilter
		  @discussion Minimum heading change (in degrees) before a heading event is fired.
		*/
		virtual double get_headingFilter() const TITANIUM_NOEXCEPT;
		virtual void set_headingFilter(const double distance) TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract hasCompass
		  @discussion Indicates whether the current device supports a compass.
		*/
		virtual bool get_hasCompass() const TITANIUM_NOEXCEPT;
		virtual void set_hasCompass(const bool& hasCompass) TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract locationServicesAuthorization
		  @discussion Gets the value of the locationServicesAuthorization property.
		*/
		virtual Geolocation::AUTHORIZATION get_locationServicesAuthorization() const TITANIUM_NOEXCEPT;
		virtual void set_locationServicesAuthorization(Geolocation::AUTHORIZATION locationServicesAuthorization) TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract locationServicesEnabled
		  @discussion Indicates if the user has enabled or disabled location services for the device (not the application).
		*/
		virtual bool get_locationServicesEnabled() const TITANIUM_NOEXCEPT;
		virtual void set_locationServicesEnabled(bool locationServicesEnabled) TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract lastGeolocation
		  @discussion JSON representation of the last geolocation received.
		*/
		virtual const JSObject& get_lastGeolocation() const TITANIUM_NOEXCEPT;
		virtual void set_lastGeolocation(const JSObject& lastGeolocation) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract forwardGeocoder
		  @discussion Resolves an address to a location.
		*/
		virtual void forwardGeocoder(const std::string& address, JSObject callback) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getCurrentHeading
		  @discussion Retrieves the current compass heading.
		*/
		virtual void getCurrentHeading(JSObject callback) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getCurrentPosition
		  @discussion Retrieves the last known location from the device.
		*/
		virtual void getCurrentPosition(JSObject callback) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract reverseGeocoder
		  @discussion Tries to resolve a location to an address.
		*/
		virtual void reverseGeocoder(const double& latitude, const double& longitude, JSObject callback) TITANIUM_NOEXCEPT;

		GeolocationModule(const JSContext&) TITANIUM_NOEXCEPT;
		virtual ~GeolocationModule() = default;
		GeolocationModule(const GeolocationModule&) = default;
		GeolocationModule& operator=(const GeolocationModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		GeolocationModule(GeolocationModule&&)                 = default;
		GeolocationModule& operator=(GeolocationModule&&)      = default;
#endif

		static void JSExportInitialize();

		virtual JSValue js_get_accuracy() const TITANIUM_NOEXCEPT final;
		virtual bool js_set_accuracy(const JSValue& argument) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_activityType() const TITANIUM_NOEXCEPT final;
		virtual bool js_set_activityType(const JSValue& argument) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_distanceFilter() const TITANIUM_NOEXCEPT final;
		virtual bool js_set_distanceFilter(const JSValue& argument) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_headingFilter() const TITANIUM_NOEXCEPT final;
		virtual bool js_set_headingFilter(const JSValue& argument) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_hasCompass() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_locationServicesAuthorization() const TITANIUM_NOEXCEPT final;
		virtual bool js_set_locationServicesAuthorization(const JSValue& argument) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_locationServicesEnabled() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_lastGeolocation() const TITANIUM_NOEXCEPT final;

		virtual JSValue js_forwardGeocoder(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getCurrentHeading(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getCurrentPosition(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_reverseGeocoder(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getAccuracy(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_setAccuracy(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getActivityType(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_setActivityType(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getDistanceFilter(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_setDistanceFilter(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getHeadingFilter(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_setHeadingFilter(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getHasCompass(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_setLocationServicesAuthorization(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getLocationServicesAuthorization(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getLocationServicesEnabled(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getLastGeolocation(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		protected:
			JSValue accuracy_best__;
			JSValue accuracy_best_for_navigation__;
			JSValue accuracy_hundred_meters__;
			JSValue accuracy_kilometer__;
			JSValue accuracy_nearest_ten_meters__;
			JSValue accuracy_three_kilometers__;
			JSValue accuracy_high__;
			JSValue accuracy_low__;
			JSValue activitytype_automotive_navigation__;
			JSValue activitytype_fitness__;
			JSValue activitytype_other__;
			JSValue activitytype_other_navigation__;
			JSValue authorization_always__;
			JSValue authorization_authorized__;
			JSValue authorization_denied__;
			JSValue authorization_restricted__;
			JSValue authorization_unknown__;
			JSValue authorization_when_in_use__;
			JSValue error_denied__;
			JSValue error_heading_failure__;
			JSValue error_location_unknown__;
			JSValue error_network__;
			JSValue error_region_monitoring_delayed__;
			JSValue error_region_monitoring_denied__;
			JSValue error_region_monitoring_failure__;
			JSValue error_timeout__;
			JSValue provider_gps__;
			JSValue provider_network__;
			JSValue provider_passive__;
			Geolocation::ACCURACY accuracy__;
			Geolocation::ACTIVITYTYPE activityType__;
			double distanceFilter__;
			double headingFilter__;
			bool hasCompass__;
			Geolocation::AUTHORIZATION locationServicesAuthorization__;
			bool locationServicesEnabled__;
			JSObject lastGeolocation__;
			JSObject heading__;
	};
} // namespace Titanium
#endif // _TITANIUM_GEOLOCATION_HPP_