/**
 * TitaniumKit Titanium.Geolocation
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GeolocationModule.hpp"

namespace Titanium
{
	GeolocationModule::GeolocationModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context),
		accuracy_best__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::BEST))),
		accuracy_best_for_navigation__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::BEST_FOR_NAVIGATION))),
		accuracy_high__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::HIGH))),
		accuracy_hundred_meters__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::HUNDRED_METERS))),
		accuracy_kilometer__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::KILOMETER))),
		accuracy_low__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::LOW))),
		accuracy_nearest_ten_meters__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::NEAREST_TEN_METERS))),
		accuracy_three_kilometers__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::THREE_KILOMETERS))),
		accuracy__(Geolocation::ACCURACY::BEST),
		activitytype_automotive_navigation__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::AUTOMOTIVE_NAVIGATION))),
		activitytype_fitness__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::FITNESS))),
		activitytype_other__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::OTHER))),
		activitytype_other_navigation__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::OTHER_NAVIGATION))),
		activityType__(Geolocation::ACTIVITYTYPE::OTHER),
		authorization_always__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::ALWAYS))),
		authorization_authorized__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::AUTHORIZED))),
		authorization_denied__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::DENIED))),
		authorization_restricted__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::RESTRICTED))),
		authorization_unknown__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::UNKNOWN))),
		authorization_when_in_use__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::WHEN_IN_USE))),
		locationServicesAuthorization__(Geolocation::AUTHORIZATION::UNKNOWN),
		error_denied__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::DENIED))),
		error_heading_failure__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::HEADING_FAILIURE))),
		error_location_unknown__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::LOCATION_UNKNOWN))),
		error_network__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::NETWORK))),
		error_region_monitoring_delayed__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::REGION_MONITORING_DELAYED))),
		error_region_monitoring_denied__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::REGION_MONITORING_DENIED))),
		error_region_monitoring_failure__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::REGION_MONITORING_FAILIURE))),
		error_timeout__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::TIMEOUT))),
		provider_gps__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::PROVIDER::GPS))),
		provider_network__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::PROVIDER::NETOWORK))),
		provider_passive__(js_context.CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::PROVIDER::PASSIVE))),
		distanceFilter__(0),
		headingFilter__(0),
		hasCompass__(false),
		locationServicesEnabled__(false),
		lastGeolocation__(get_context().CreateObject()),
		heading__(get_context().CreateObject())
	{
	}

	JSValue GeolocationModule::ACCURACY_BEST() const TITANIUM_NOEXCEPT
	{
		return accuracy_best__;
	}

	JSValue GeolocationModule::ACCURACY_BEST_FOR_NAVIGATION() const TITANIUM_NOEXCEPT
	{
		return accuracy_best_for_navigation__;
	}

	JSValue GeolocationModule::ACCURACY_HUNDRED_METERS() const TITANIUM_NOEXCEPT
	{
		return accuracy_hundred_meters__;
	}

	JSValue GeolocationModule::ACCURACY_KILOMETER() const TITANIUM_NOEXCEPT
	{
		return accuracy_kilometer__;
	}

	JSValue GeolocationModule::ACCURACY_NEAREST_TEN_METERS() const TITANIUM_NOEXCEPT
	{
		return accuracy_nearest_ten_meters__;
	}

	JSValue GeolocationModule::ACCURACY_THREE_KILOMETERS() const TITANIUM_NOEXCEPT
	{
		return accuracy_three_kilometers__;
	}

	JSValue GeolocationModule::ACCURACY_HIGH() const TITANIUM_NOEXCEPT
	{
		return accuracy_high__;
	}

	JSValue GeolocationModule::ACCURACY_LOW() const TITANIUM_NOEXCEPT
	{
		return accuracy_low__;
	}

	Geolocation::ACCURACY GeolocationModule::get_accuracy() const TITANIUM_NOEXCEPT
	{
		return accuracy__;
	}

	void GeolocationModule::set_accuracy(const Geolocation::ACCURACY accuracy) TITANIUM_NOEXCEPT
	{
		accuracy__ = accuracy;
	}

	JSValue GeolocationModule::ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION() const TITANIUM_NOEXCEPT
	{
			return activitytype_automotive_navigation__;
	}

	JSValue GeolocationModule::ACTIVITYTYPE_FITNESS() const TITANIUM_NOEXCEPT
	{
			return activitytype_fitness__;
	}

	JSValue GeolocationModule::ACTIVITYTYPE_OTHER() const TITANIUM_NOEXCEPT
	{
			return activitytype_other__;
	}

	JSValue GeolocationModule::ACTIVITYTYPE_OTHER_NAVIGATION() const TITANIUM_NOEXCEPT
	{
			return activitytype_other_navigation__;
	}

	Geolocation::ACTIVITYTYPE GeolocationModule::get_activityType() const TITANIUM_NOEXCEPT
	{
		return activityType__;
	}

	void GeolocationModule::set_activityType(const Geolocation::ACTIVITYTYPE activityType) TITANIUM_NOEXCEPT
	{
		activityType__ = activityType;
	}

	JSValue GeolocationModule::AUTHORIZATION_ALWAYS() const TITANIUM_NOEXCEPT
	{
			return authorization_always__;
	}

	JSValue GeolocationModule::AUTHORIZATION_AUTHORIZED() const TITANIUM_NOEXCEPT
	{
			return authorization_authorized__;
	}

	JSValue GeolocationModule::AUTHORIZATION_DENIED() const TITANIUM_NOEXCEPT
	{
			return authorization_denied__;
	}

	JSValue GeolocationModule::AUTHORIZATION_RESTRICTED() const TITANIUM_NOEXCEPT
	{
			return authorization_restricted__;
	}

	JSValue GeolocationModule::AUTHORIZATION_UNKNOWN() const TITANIUM_NOEXCEPT
	{
			return authorization_unknown__;
	}

	JSValue GeolocationModule::AUTHORIZATION_WHEN_IN_USE() const TITANIUM_NOEXCEPT
	{
			return authorization_when_in_use__;
	}

	JSValue GeolocationModule::ERROR_DENIED() const TITANIUM_NOEXCEPT
	{
			return error_denied__;
	}

	JSValue GeolocationModule::ERROR_HEADING_FAILURE() const TITANIUM_NOEXCEPT
	{
			return error_heading_failure__;
	}

	JSValue GeolocationModule::ERROR_LOCATION_UNKNOWN() const TITANIUM_NOEXCEPT
	{
			return error_location_unknown__;
	}

	JSValue GeolocationModule::ERROR_NETWORK() const TITANIUM_NOEXCEPT
	{
			return error_network__;
	}

	JSValue GeolocationModule::ERROR_REGION_MONITORING_DELAYED() const TITANIUM_NOEXCEPT
	{
			return error_region_monitoring_delayed__;
	}

	JSValue GeolocationModule::ERROR_REGION_MONITORING_DENIED() const TITANIUM_NOEXCEPT
	{
			return error_region_monitoring_denied__;
	}

	JSValue GeolocationModule::ERROR_REGION_MONITORING_FAILURE() const TITANIUM_NOEXCEPT
	{
			return error_region_monitoring_failure__;
	}

	JSValue GeolocationModule::ERROR_TIMEOUT() const TITANIUM_NOEXCEPT
	{
			return error_timeout__;
	}

	JSValue GeolocationModule::PROVIDER_GPS() const TITANIUM_NOEXCEPT
	{
			return provider_gps__;
	}

	JSValue GeolocationModule::PROVIDER_NETWORK() const TITANIUM_NOEXCEPT
	{
			return provider_network__;
	}

	JSValue GeolocationModule::PROVIDER_PASSIVE() const TITANIUM_NOEXCEPT
	{
			return provider_passive__;
	}

	double GeolocationModule::get_distanceFilter() const TITANIUM_NOEXCEPT
	{
		return distanceFilter__;
	}

	void GeolocationModule::set_distanceFilter(const double distance) TITANIUM_NOEXCEPT
	{
		distanceFilter__ = distance;
	}

	double GeolocationModule::get_headingFilter() const TITANIUM_NOEXCEPT
	{
		return headingFilter__;
	}

	void GeolocationModule::set_headingFilter(const double heading) TITANIUM_NOEXCEPT
	{
		headingFilter__ = heading;
	}

	bool GeolocationModule::get_hasCompass() const TITANIUM_NOEXCEPT
	{
		return hasCompass__;
	}

	void GeolocationModule::set_hasCompass(const bool& hasCompass) TITANIUM_NOEXCEPT
	{
		hasCompass__ = hasCompass;
	}

	Geolocation::AUTHORIZATION GeolocationModule::get_locationServicesAuthorization() const TITANIUM_NOEXCEPT
	{
		return locationServicesAuthorization__;
	}

	void GeolocationModule::set_locationServicesAuthorization(Geolocation::AUTHORIZATION locationServicesAuthorization) TITANIUM_NOEXCEPT
	{
		locationServicesAuthorization__ = locationServicesAuthorization;
	}

	bool GeolocationModule::get_locationServicesEnabled() const TITANIUM_NOEXCEPT
	{
		return locationServicesEnabled__;
	}

	void GeolocationModule::set_locationServicesEnabled(bool locationServicesEnabled) TITANIUM_NOEXCEPT
	{
		locationServicesEnabled__ = locationServicesEnabled;
	}

	const JSObject& GeolocationModule::get_lastGeolocation() const TITANIUM_NOEXCEPT
	{
		return lastGeolocation__;
	}

	void GeolocationModule::set_lastGeolocation(const JSObject& lastGeolocation) TITANIUM_NOEXCEPT
	{
		lastGeolocation__ = lastGeolocation;
	}

	void GeolocationModule::forwardGeocoder(const std::string& address, JSObject callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("GeolocationModule::forwardGeocoder: Unimplemented");
	}

	void GeolocationModule::getCurrentHeading(JSObject callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("GeolocationModule::getCurrentHeading: Unimplemented");
	}

	void GeolocationModule::getCurrentPosition(JSObject callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("GeolocationModule::getCurrentPosition: Unimplemented");
	}

	void GeolocationModule::reverseGeocoder(const double& latitude, const double& longitude, JSObject callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("GeolocationModule::reverseGeocoder: Unimplemented");
	}

	void GeolocationModule::JSExportInitialize() {
		JSExport<GeolocationModule>::SetClassVersion(1);
		JSExport<GeolocationModule>::SetParent(JSExport<Module>::Class());

		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_BEST", std::mem_fn(&GeolocationModule::ACCURACY_BEST));
		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_BEST_FOR_NAVIGATION", std::mem_fn(&GeolocationModule::ACCURACY_BEST_FOR_NAVIGATION));
		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_HUNDRED_METERS", std::mem_fn(&GeolocationModule::ACCURACY_HUNDRED_METERS));
		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_KILOMETER", std::mem_fn(&GeolocationModule::ACCURACY_KILOMETER));
		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_NEAREST_TEN_METERS", std::mem_fn(&GeolocationModule::ACCURACY_NEAREST_TEN_METERS));
		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_THREE_KILOMETERS", std::mem_fn(&GeolocationModule::ACCURACY_THREE_KILOMETERS));
		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_HIGH", std::mem_fn(&GeolocationModule::ACCURACY_HIGH));
		JSExport<GeolocationModule>::AddValueProperty("ACCURACY_LOW", std::mem_fn(&GeolocationModule::ACCURACY_LOW));
			
		JSExport<GeolocationModule>::AddValueProperty("ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION", std::mem_fn(&GeolocationModule::ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION));
		JSExport<GeolocationModule>::AddValueProperty("ACTIVITYTYPE_FITNESS", std::mem_fn(&GeolocationModule::ACTIVITYTYPE_FITNESS));
		JSExport<GeolocationModule>::AddValueProperty("ACTIVITYTYPE_OTHER", std::mem_fn(&GeolocationModule::ACTIVITYTYPE_OTHER));
		JSExport<GeolocationModule>::AddValueProperty("ACTIVITYTYPE_OTHER_NAVIGATION", std::mem_fn(&GeolocationModule::ACTIVITYTYPE_OTHER_NAVIGATION));

		JSExport<GeolocationModule>::AddValueProperty("AUTHORIZATION_ALWAYS", std::mem_fn(&GeolocationModule::AUTHORIZATION_ALWAYS));
		JSExport<GeolocationModule>::AddValueProperty("AUTHORIZATION_AUTHORIZED", std::mem_fn(&GeolocationModule::AUTHORIZATION_AUTHORIZED));
		JSExport<GeolocationModule>::AddValueProperty("AUTHORIZATION_DENIED", std::mem_fn(&GeolocationModule::AUTHORIZATION_DENIED));
		JSExport<GeolocationModule>::AddValueProperty("AUTHORIZATION_RESTRICTED", std::mem_fn(&GeolocationModule::AUTHORIZATION_RESTRICTED));
		JSExport<GeolocationModule>::AddValueProperty("AUTHORIZATION_UNKNOWN", std::mem_fn(&GeolocationModule::AUTHORIZATION_UNKNOWN));
		JSExport<GeolocationModule>::AddValueProperty("AUTHORIZATION_WHEN_IN_USE", std::mem_fn(&GeolocationModule::AUTHORIZATION_WHEN_IN_USE));

		JSExport<GeolocationModule>::AddValueProperty("ERROR_DENIED", std::mem_fn(&GeolocationModule::ERROR_DENIED));
		JSExport<GeolocationModule>::AddValueProperty("ERROR_HEADING_FAILURE", std::mem_fn(&GeolocationModule::ERROR_HEADING_FAILURE));
		JSExport<GeolocationModule>::AddValueProperty("ERROR_LOCATION_UNKNOWN", std::mem_fn(&GeolocationModule::ERROR_LOCATION_UNKNOWN));
		JSExport<GeolocationModule>::AddValueProperty("ERROR_NETWORK", std::mem_fn(&GeolocationModule::ERROR_NETWORK));
		JSExport<GeolocationModule>::AddValueProperty("ERROR_REGION_MONITORING_DELAYED", std::mem_fn(&GeolocationModule::ERROR_REGION_MONITORING_DELAYED));
		JSExport<GeolocationModule>::AddValueProperty("ERROR_REGION_MONITORING_DENIED", std::mem_fn(&GeolocationModule::ERROR_REGION_MONITORING_DENIED));
		JSExport<GeolocationModule>::AddValueProperty("ERROR_REGION_MONITORING_FAILURE", std::mem_fn(&GeolocationModule::ERROR_REGION_MONITORING_FAILURE));
		JSExport<GeolocationModule>::AddValueProperty("ERROR_TIMEOUT", std::mem_fn(&GeolocationModule::ERROR_TIMEOUT));

		JSExport<GeolocationModule>::AddValueProperty("PROVIDER_GPS", std::mem_fn(&GeolocationModule::PROVIDER_GPS));
		JSExport<GeolocationModule>::AddValueProperty("PROVIDER_NETWORK", std::mem_fn(&GeolocationModule::PROVIDER_NETWORK));
		JSExport<GeolocationModule>::AddValueProperty("PROVIDER_PASSIVE", std::mem_fn(&GeolocationModule::PROVIDER_PASSIVE));

		JSExport<GeolocationModule>::AddValueProperty("accuracy", std::mem_fn(&GeolocationModule::js_get_accuracy), std::mem_fn(&GeolocationModule::js_set_accuracy));
		JSExport<GeolocationModule>::AddValueProperty("activityType", std::mem_fn(&GeolocationModule::js_get_activityType), std::mem_fn(&GeolocationModule::js_set_activityType));
		JSExport<GeolocationModule>::AddValueProperty("distanceFilter", std::mem_fn(&GeolocationModule::js_get_distanceFilter), std::mem_fn(&GeolocationModule::js_set_distanceFilter));
		JSExport<GeolocationModule>::AddValueProperty("headingFilter", std::mem_fn(&GeolocationModule::js_get_headingFilter), std::mem_fn(&GeolocationModule::js_set_headingFilter));
		JSExport<GeolocationModule>::AddValueProperty("hasCompass", std::mem_fn(&GeolocationModule::js_get_hasCompass));
		JSExport<GeolocationModule>::AddValueProperty("locationServicesAuthorization", std::mem_fn(&GeolocationModule::js_get_locationServicesAuthorization), std::mem_fn(&GeolocationModule::js_set_locationServicesAuthorization));
		JSExport<GeolocationModule>::AddValueProperty("locationServicesEnabled", std::mem_fn(&GeolocationModule::js_get_locationServicesEnabled));
		JSExport<GeolocationModule>::AddValueProperty("lastGeolocation", std::mem_fn(&GeolocationModule::js_get_lastGeolocation));

		JSExport<GeolocationModule>::AddFunctionProperty("forwardGeocoder", std::mem_fn(&GeolocationModule::js_forwardGeocoder));
		JSExport<GeolocationModule>::AddFunctionProperty("getCurrentHeading", std::mem_fn(&GeolocationModule::js_getCurrentHeading));
		JSExport<GeolocationModule>::AddFunctionProperty("getCurrentPosition", std::mem_fn(&GeolocationModule::js_getCurrentPosition));
		JSExport<GeolocationModule>::AddFunctionProperty("reverseGeocoder", std::mem_fn(&GeolocationModule::js_reverseGeocoder));
		JSExport<GeolocationModule>::AddFunctionProperty("getAccuracy", std::mem_fn(&GeolocationModule::js_getAccuracy));
		JSExport<GeolocationModule>::AddFunctionProperty("setAccuracy", std::mem_fn(&GeolocationModule::js_setAccuracy));
		JSExport<GeolocationModule>::AddFunctionProperty("getHasCompass", std::mem_fn(&GeolocationModule::js_getHasCompass));

		JSExport<GeolocationModule>::AddFunctionProperty("getDistanceFilter", std::mem_fn(&GeolocationModule::js_getDistanceFilter));
		JSExport<GeolocationModule>::AddFunctionProperty("setDistanceFilter", std::mem_fn(&GeolocationModule::js_setDistanceFilter));

		JSExport<GeolocationModule>::AddFunctionProperty("getHeadingFilter", std::mem_fn(&GeolocationModule::js_getHeadingFilter));
		JSExport<GeolocationModule>::AddFunctionProperty("setHeadingFilter", std::mem_fn(&GeolocationModule::js_setHeadingFilter));

		JSExport<GeolocationModule>::AddFunctionProperty("getLocationServicesEnabled", std::mem_fn(&GeolocationModule::js_getLocationServicesEnabled));
		JSExport<GeolocationModule>::AddFunctionProperty("getLastGeolocation", std::mem_fn(&GeolocationModule::js_getLastGeolocation));
	}

	JSValue GeolocationModule::js_get_accuracy() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(get_accuracy()));
	}

	bool GeolocationModule::js_set_accuracy(const JSValue& argument) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(argument.IsNumber());
		const auto accuracy = Titanium::Geolocation::Constants::to_ACCURACY(static_cast<std::underlying_type<Geolocation::ACCURACY>::type>(argument));
		set_accuracy(accuracy);
		return true;
	}

	JSValue GeolocationModule::js_get_activityType() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(get_activityType()));
	}

	bool GeolocationModule::js_set_activityType(const JSValue& argument) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(argument.IsNumber());
		const auto activityType = Titanium::Geolocation::Constants::to_ACTIVITYTYPE(static_cast<std::underlying_type<Geolocation::ACTIVITYTYPE>::type>(argument));
		set_activityType(activityType);
		return true;
	}

	JSValue GeolocationModule::js_get_distanceFilter() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(get_distanceFilter());
	}

	bool GeolocationModule::js_set_distanceFilter(const JSValue& argument) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(argument.IsNumber());
		set_distanceFilter(static_cast<double>(argument));
		return true;
	}

	JSValue GeolocationModule::js_get_headingFilter() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(get_headingFilter());
	}

	bool GeolocationModule::js_set_headingFilter(const JSValue& argument) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(argument.IsNumber());
		set_headingFilter(static_cast<double>(argument));
		return true;
	}

	JSValue GeolocationModule::js_get_hasCompass() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(get_hasCompass());
	}

	JSValue GeolocationModule::js_get_locationServicesAuthorization() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(get_locationServicesAuthorization()));
	}

	bool GeolocationModule::js_set_locationServicesAuthorization(const JSValue& argument) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(argument.IsNumber());
		const auto authorization = Titanium::Geolocation::Constants::to_AUTHORIZATION(static_cast<std::underlying_type<Geolocation::AUTHORIZATION>::type>(argument));
		set_locationServicesAuthorization(authorization);
		return true;
	}

	JSValue GeolocationModule::js_get_locationServicesEnabled() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(get_locationServicesEnabled());
	}

	JSValue GeolocationModule::js_get_lastGeolocation() const TITANIUM_NOEXCEPT
	{
		return get_lastGeolocation();
	}

	JSValue GeolocationModule::js_forwardGeocoder(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() >= 2) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_1.IsObject());
			const std::string address = static_cast<std::string>(_0);
			const auto callback = static_cast<JSObject>(_1);
			forwardGeocoder(address, callback);
		} else if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const std::string address = static_cast<std::string>(_0);
			forwardGeocoder(address, get_context().CreateObject());
		}
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getCurrentHeading(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			const auto callback = static_cast<JSObject>(_0);
			getCurrentHeading(callback);
		}
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getCurrentPosition(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			const auto callback = static_cast<JSObject>(_0);
			getCurrentPosition(callback);
		}
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_reverseGeocoder(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() >= 3) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_1.IsNumber());
			const auto _2 = arguments.at(2);
			TITANIUM_ASSERT(_2.IsObject());
			const double latitude = static_cast<double>(_0);
			const double longitude = static_cast<double>(_1);
			const auto callback = static_cast<JSObject>(_2);
			reverseGeocoder(latitude, longitude, callback);
		} else if (arguments.size() >= 2) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_1.IsNumber());
			const double latitude = static_cast<double>(_0);
			const double longitude = static_cast<double>(_1);
			reverseGeocoder(latitude, longitude, get_context().CreateObject());
		} else if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());
			const double latitude = static_cast<double>(_0);
			reverseGeocoder(latitude, 0, get_context().CreateObject());
		}
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getAccuracy(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_accuracy();
	}

	JSValue GeolocationModule::js_setAccuracy(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(arguments.size() >= 1);
		js_set_accuracy(arguments.at(0));
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getActivityType(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_activityType();
	}

	JSValue GeolocationModule::js_setActivityType(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(arguments.size() >= 1);
		js_set_activityType(arguments.at(0));
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getDistanceFilter(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_distanceFilter();
	}

	JSValue GeolocationModule::js_setDistanceFilter(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(arguments.size() >= 1);
		js_set_distanceFilter(arguments.at(0));
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getHeadingFilter(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_headingFilter();
	}

	JSValue GeolocationModule::js_setHeadingFilter(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(arguments.size() >= 1);
		js_set_headingFilter(arguments.at(0));
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getHasCompass(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_hasCompass();
	}

	JSValue GeolocationModule::js_getLocationServicesAuthorization(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_locationServicesAuthorization();
	}

	JSValue GeolocationModule::js_setLocationServicesAuthorization(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(arguments.size() >= 1);
		js_set_locationServicesAuthorization(arguments.at(0));
		return get_context().CreateUndefined();
	}

	JSValue GeolocationModule::js_getLocationServicesEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_locationServicesEnabled();
	}

	JSValue GeolocationModule::js_getLastGeolocation(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_lastGeolocation();
	}
} // namespace Titanium