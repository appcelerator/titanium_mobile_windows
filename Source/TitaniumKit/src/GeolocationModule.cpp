/**
 * TitaniumKit Titanium.Geolocation
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/GeolocationModule.hpp"

namespace Titanium
{
	LocationCoordinatesFloor js_to_LocationCoordinatesFloor(const JSObject& object)
	{
		LocationCoordinatesFloor params;
		if (object.HasProperty("level")) {
			params.level = static_cast<std::int32_t>(object.GetProperty("level"));
		}
		return params;
	};

	JSObject LocationCoordinatesFloor_to_js(const JSContext& js_context, const LocationCoordinatesFloor& params)
	{
		auto object = js_context.CreateObject();
		object.SetProperty("level", js_context.CreateNumber(params.level));
		return object;
	}

	LocationCoordinates js_to_LocationCoordinates(const JSObject& object)
	{
		LocationCoordinates params;
		if (object.HasProperty("accuracy")) {
			params.accuracy = static_cast<double>(object.GetProperty("accuracy"));
		}
		if (object.HasProperty("altitude")) {
			params.altitude = static_cast<double>(object.GetProperty("altitude"));
		}
		if (object.HasProperty("altitudeAccuracy")) {
			params.altitude = static_cast<double>(object.GetProperty("altitudeAccuracy"));
		}
		if (object.HasProperty("floor")) {
			params.floor = js_to_LocationCoordinatesFloor(static_cast<JSObject>(object.GetProperty("altitude")));
		}
		if (object.HasProperty("heading")) {
			params.heading = static_cast<double>(object.GetProperty("heading"));
		}
		if (object.HasProperty("latitude")) {
			params.latitude = static_cast<double>(object.GetProperty("latitude"));
		}
		if (object.HasProperty("longitude")) {
			params.longitude = static_cast<double>(object.GetProperty("longitude"));
		}
		if (object.HasProperty("speed")) {
			params.speed = static_cast<double>(object.GetProperty("speed"));
		}
		if (object.HasProperty("timestamp")) {
			params.timestamp = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<double>(object.GetProperty("timstamp"))));
		}
		return params;
	};

	JSObject LocationCoordinates_to_js(const JSContext& js_context, const LocationCoordinates& params)
	{
		auto object = js_context.CreateObject();
		object.SetProperty("accuracy",  js_context.CreateNumber(params.accuracy));
		object.SetProperty("altitude",  js_context.CreateNumber(params.altitude));
		object.SetProperty("altitudeAccuracy", js_context.CreateNumber(params.altitudeAccuracy));
		object.SetProperty("floor", LocationCoordinatesFloor_to_js(js_context, params.floor));
		object.SetProperty("heading",   js_context.CreateNumber(params.heading));
		object.SetProperty("latitude",  js_context.CreateNumber(params.latitude));
		object.SetProperty("longitude", js_context.CreateNumber(params.longitude));
		object.SetProperty("speed",     js_context.CreateNumber(params.speed));
		object.SetProperty("timestamp", js_context.CreateNumber(static_cast<double>(params.timestamp.count())));
		return object;
	}

	GeolocationModule::GeolocationModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.Geolocation"),
		accuracy__(Geolocation::ACCURACY::BEST),
		activityType__(Geolocation::ACTIVITYTYPE::OTHER),
		locationServicesAuthorization__(Geolocation::AUTHORIZATION::UNKNOWN),
		distanceFilter__(0),
		headingFilter__(0),
		hasCompass__(false),
		locationServicesEnabled__(false),
		lastGeolocation__(get_context().CreateObject()),
		heading__(get_context().CreateObject())
	{
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_BEST)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::BEST));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_BEST_FOR_NAVIGATION)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::BEST_FOR_NAVIGATION));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_HUNDRED_METERS)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::HUNDRED_METERS));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_KILOMETER)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::KILOMETER));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_NEAREST_TEN_METERS)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::NEAREST_TEN_METERS));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_THREE_KILOMETERS)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::THREE_KILOMETERS));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_HIGH)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::HIGH));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACCURACY_LOW)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACCURACY::LOW));
	}

	TITANIUM_PROPERTY_READWRITE(GeolocationModule, Geolocation::ACCURACY, accuracy);

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::AUTOMOTIVE_NAVIGATION));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACTIVITYTYPE_FITNESS)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::FITNESS));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACTIVITYTYPE_OTHER)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::OTHER));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ACTIVITYTYPE_OTHER_NAVIGATION)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ACTIVITYTYPE::OTHER_NAVIGATION));
	}

	TITANIUM_PROPERTY_READWRITE(GeolocationModule, Geolocation::ACTIVITYTYPE, activityType);

	TITANIUM_PROPERTY_GETTER(GeolocationModule, AUTHORIZATION_ALWAYS)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::ALWAYS));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, AUTHORIZATION_AUTHORIZED)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::AUTHORIZED));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, AUTHORIZATION_DENIED)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::DENIED));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, AUTHORIZATION_RESTRICTED)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::RESTRICTED));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, AUTHORIZATION_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::UNKNOWN));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, AUTHORIZATION_WHEN_IN_USE)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::AUTHORIZATION::WHEN_IN_USE));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_DENIED)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::DENIED));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_HEADING_FAILURE)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::HEADING_FAILIURE));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_LOCATION_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::LOCATION_UNKNOWN));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_NETWORK)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::NETWORK));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_REGION_MONITORING_DELAYED)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::REGION_MONITORING_DELAYED));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_REGION_MONITORING_DENIED)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::REGION_MONITORING_DENIED));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_REGION_MONITORING_FAILURE)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::REGION_MONITORING_FAILIURE));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, ERROR_TIMEOUT)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::ERROR::TIMEOUT));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, PROVIDER_GPS)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::PROVIDER::GPS));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, PROVIDER_NETWORK)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::PROVIDER::NETOWORK));
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, PROVIDER_PASSIVE)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(Titanium::Geolocation::PROVIDER::PASSIVE));
	}

	TITANIUM_PROPERTY_READWRITE(GeolocationModule, double, distanceFilter)

	TITANIUM_PROPERTY_READWRITE(GeolocationModule, double, headingFilter)

	TITANIUM_PROPERTY_READWRITE(GeolocationModule, bool, hasCompass)

	TITANIUM_PROPERTY_READWRITE(GeolocationModule, Geolocation::AUTHORIZATION, locationServicesAuthorization)

	TITANIUM_PROPERTY_READWRITE(GeolocationModule, bool, locationServicesEnabled)

	const JSObject& GeolocationModule::get_lastGeolocation() const TITANIUM_NOEXCEPT
	{
		return lastGeolocation__;
	}

	TITANIUM_PROPERTY_WRITE(GeolocationModule, JSObject, lastGeolocation)

	void GeolocationModule::forwardGeocoder(const std::string& address, JSObject callback) TITANIUM_NOEXCEPT
	{
		static const std::string forwardGeocoder_js = R"JS((function(self) {
			var requestUrl = 'http://api.appcelerator.com/p/v1/geo?d=f',
				client = Ti.Network.createHTTPClient({
					onload: function (e) {
						var response = this.responseText.split(','),
							response_obj = {
								success: false,
								error: 'no results',
								code: -1
							};

						if (response.length > 0 && response[0] == '200') {
							response_obj = {
								accuracy: response[1],
								address: self.address,
								latitude: Number(response[2]),
								longitude: Number(response[3]),
								success: true,
								code: 0
							};
						}
						self.callback(response_obj);
					},
					onerror: function (e) {
						Ti.API.debug(e.error);
					},
					timeout: 3000
				});

			requestUrl += '&aguid=' + Ti.App.guid;
			requestUrl += '&mid=' + Ti.App.id;
			requestUrl += '&sid=' + Ti.App.sessionId;
			requestUrl += '&q=' + self.address;

			client.open('GET', requestUrl);
			client.send();
		})(this))JS";
		const auto context = get_context();
		auto export_obj = context.CreateObject();
		export_obj.SetProperty("address", context.CreateString(address));
		export_obj.SetProperty("callback", callback);
		context.JSEvaluateScript(forwardGeocoder_js, export_obj);
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
		static const std::string reverseGeocoder_js = R"JS((function(self) {
			var requestUrl = 'http://api.appcelerator.com/p/v1/geo?d=r',
				client = Ti.Network.createHTTPClient({
					onload: function (e) {
						var response = JSON.parse(this.responseText),
							length = 0,
							i = 0;
						if (response.success) {
							response.code = 0;
							if (response.places) {
								length = response.places.length;
								for (i = 0; i < length; i++) {
									response.places[i].countryCode = response.places[i].country_code;
									response.places[i].postalCode  = response.places[i].zipcode;
									delete response.places[i].country_code;
									delete response.places[i].zipcode;
								}
							}
						} else {
							response.code = -1;
							response.error = 'no results';
						}
						self.callback(response);
					},
					onerror: function (e) {
						Ti.API.debug(e.error);
					},
					timeout: 3000
				});

			requestUrl += '&aguid=' + Ti.App.guid;
			requestUrl += '&mid=' + Ti.App.id;
			requestUrl += '&sid=' + Ti.App.sessionId;
			requestUrl += '&q=' + self.latitude + ',' + self.longitude;

			client.open('GET', requestUrl);
			client.send();
		})(this))JS";
		const auto context = get_context();
		auto export_obj = context.CreateObject();
		export_obj.SetProperty("latitude", context.CreateNumber(latitude));
		export_obj.SetProperty("longitude", context.CreateNumber(longitude));
		export_obj.SetProperty("callback", callback);
		context.JSEvaluateScript(reverseGeocoder_js, export_obj);
	}

	bool GeolocationModule::hasLocationPermissions(const Titanium::Geolocation::AUTHORIZATION& authorizationType) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("GeolocationModule::hasLocationPermissions: Unimplemented");
		return false;
	}

	void GeolocationModule::requestLocationPermissions(const Titanium::Geolocation::AUTHORIZATION& authorizationType, JSObject callback) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("GeolocationModule::requestLocationPermissions: Unimplemented");
	}

	void GeolocationModule::JSExportInitialize()
	{
		JSExport<GeolocationModule>::SetClassVersion(1);
		JSExport<GeolocationModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_BEST);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_BEST_FOR_NAVIGATION);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_HUNDRED_METERS);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_KILOMETER);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_NEAREST_TEN_METERS);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_THREE_KILOMETERS);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_HIGH);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACCURACY_LOW);

		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACTIVITYTYPE_AUTOMOTIVE_NAVIGATION);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACTIVITYTYPE_FITNESS);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACTIVITYTYPE_OTHER);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ACTIVITYTYPE_OTHER_NAVIGATION);

		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, AUTHORIZATION_ALWAYS);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, AUTHORIZATION_AUTHORIZED);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, AUTHORIZATION_DENIED);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, AUTHORIZATION_RESTRICTED);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, AUTHORIZATION_UNKNOWN);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, AUTHORIZATION_WHEN_IN_USE);

		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_DENIED);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_HEADING_FAILURE);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_LOCATION_UNKNOWN);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_NETWORK);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_REGION_MONITORING_DELAYED);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_REGION_MONITORING_DENIED);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_REGION_MONITORING_FAILURE);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, ERROR_TIMEOUT);

		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, PROVIDER_GPS);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, PROVIDER_NETWORK);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, PROVIDER_PASSIVE);

		TITANIUM_ADD_PROPERTY(GeolocationModule, accuracy);
		TITANIUM_ADD_PROPERTY(GeolocationModule, activityType);
		TITANIUM_ADD_PROPERTY(GeolocationModule, distanceFilter);
		TITANIUM_ADD_PROPERTY(GeolocationModule, headingFilter);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, hasCompass);
		TITANIUM_ADD_PROPERTY(GeolocationModule, locationServicesAuthorization);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, locationServicesEnabled);
		TITANIUM_ADD_PROPERTY_READONLY(GeolocationModule, lastGeolocation);

		TITANIUM_ADD_FUNCTION(GeolocationModule, forwardGeocoder);
		TITANIUM_ADD_FUNCTION(GeolocationModule, getCurrentHeading);
		TITANIUM_ADD_FUNCTION(GeolocationModule, getCurrentPosition);
		TITANIUM_ADD_FUNCTION(GeolocationModule, reverseGeocoder);
		TITANIUM_ADD_FUNCTION(GeolocationModule, getAccuracy);
		TITANIUM_ADD_FUNCTION(GeolocationModule, setAccuracy);
		TITANIUM_ADD_FUNCTION(GeolocationModule, getHasCompass);

		TITANIUM_ADD_FUNCTION(GeolocationModule, getDistanceFilter);
		TITANIUM_ADD_FUNCTION(GeolocationModule, setDistanceFilter);

		TITANIUM_ADD_FUNCTION(GeolocationModule, getHeadingFilter);
		TITANIUM_ADD_FUNCTION(GeolocationModule, setHeadingFilter);

		TITANIUM_ADD_FUNCTION(GeolocationModule, getLocationServicesEnabled);
		TITANIUM_ADD_FUNCTION(GeolocationModule, getLastGeolocation);

		TITANIUM_ADD_FUNCTION(GeolocationModule, hasLocationPermissions);
		TITANIUM_ADD_FUNCTION(GeolocationModule, requestLocationPermissions);
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, accuracy)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(get_accuracy()));
	}

	TITANIUM_PROPERTY_SETTER(GeolocationModule, accuracy)
	{
		if (!argument.IsNumber()) {
			HAL::detail::ThrowRuntimeError("Invalid argument supplied", "Ti.Geolocation.accuracy expects Number");
		}
		const auto accuracy = Titanium::Geolocation::Constants::to_ACCURACY(static_cast<std::underlying_type<Geolocation::ACCURACY>::type>(argument));
		set_accuracy(accuracy);
		return true;
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, activityType)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(get_activityType()));
	}

	TITANIUM_PROPERTY_SETTER(GeolocationModule, activityType)
	{
		TITANIUM_ASSERT(argument.IsNumber());
		const auto activityType = Titanium::Geolocation::Constants::to_ACTIVITYTYPE(static_cast<std::underlying_type<Geolocation::ACTIVITYTYPE>::type>(argument));
		set_activityType(activityType);
		return true;
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, distanceFilter)
	{
		return get_context().CreateNumber(get_distanceFilter());
	}

	TITANIUM_PROPERTY_SETTER(GeolocationModule, distanceFilter)
	{
		TITANIUM_ASSERT(argument.IsNumber());
		set_distanceFilter(static_cast<double>(argument));
		return true;
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, headingFilter)
	{
		return get_context().CreateNumber(get_headingFilter());
	}

	TITANIUM_PROPERTY_SETTER(GeolocationModule, headingFilter)
	{
		TITANIUM_ASSERT(argument.IsNumber());
		set_headingFilter(static_cast<double>(argument));
		return true;
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, hasCompass)
	{
		return get_context().CreateBoolean(get_hasCompass());
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, locationServicesAuthorization)
	{
		return get_context().CreateNumber(Titanium::Geolocation::Constants::to_underlying_type(get_locationServicesAuthorization()));
	}

	TITANIUM_PROPERTY_SETTER(GeolocationModule, locationServicesAuthorization)
	{
		TITANIUM_ASSERT(argument.IsNumber());
		const auto authorization = Titanium::Geolocation::Constants::to_AUTHORIZATION(static_cast<std::underlying_type<Geolocation::AUTHORIZATION>::type>(argument));
		set_locationServicesAuthorization(authorization);
		return true;
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, locationServicesEnabled)
	{
		return get_context().CreateBoolean(get_locationServicesEnabled());
	}

	TITANIUM_PROPERTY_GETTER(GeolocationModule, lastGeolocation)
	{
		return get_context().CreateString(static_cast<std::string>(static_cast<JSValue>(get_lastGeolocation()).ToJSONString()));
	}

	TITANIUM_FUNCTION(GeolocationModule, forwardGeocoder)
	{
		if (arguments.size() >= 2) {
			ENSURE_STRING_AT_INDEX(address, 0);
			ENSURE_OBJECT_AT_INDEX(callback, 1);
			forwardGeocoder(address, callback);
		} else if (arguments.size() >= 1) {
			ENSURE_STRING_AT_INDEX(address, 0);
			forwardGeocoder(address, get_context().CreateObject());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(GeolocationModule, getCurrentHeading)
	{
		ENSURE_OBJECT_AT_INDEX(callback, 0);
		getCurrentHeading(callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(GeolocationModule, getCurrentPosition)
	{
		ENSURE_OBJECT_AT_INDEX(callback, 0);
		getCurrentPosition(callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(GeolocationModule, reverseGeocoder)
	{
		if (arguments.size() >= 3) {
			ENSURE_DOUBLE_AT_INDEX(latitude, 0);
			ENSURE_DOUBLE_AT_INDEX(longitude, 1);
			ENSURE_OBJECT_AT_INDEX(callback, 2);
			reverseGeocoder(latitude, longitude, callback);
		} else if (arguments.size() >= 2) {
			ENSURE_DOUBLE_AT_INDEX(latitude, 0);
			ENSURE_DOUBLE_AT_INDEX(longitude, 1);
			reverseGeocoder(latitude, longitude, get_context().CreateObject());
		} else if (arguments.size() >= 1) {
			ENSURE_DOUBLE_AT_INDEX(latitude, 0);
			reverseGeocoder(latitude, 0, get_context().CreateObject());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(GeolocationModule, hasLocationPermissions)
	{
		ENSURE_UINT_AT_INDEX(type, 0);
		const auto authorizationType = Titanium::Geolocation::Constants::to_AUTHORIZATION(static_cast<std::underlying_type<Geolocation::AUTHORIZATION>::type>(type));
		return get_context().CreateBoolean(hasLocationPermissions(authorizationType));
	}

	TITANIUM_FUNCTION(GeolocationModule, requestLocationPermissions)
	{
		ENSURE_ARGUMENT_INDEX(1);
		ENSURE_UINT_AT_INDEX(type, 0);
		ENSURE_OBJECT_AT_INDEX(callback, 1);
		const auto authorizationType = Titanium::Geolocation::Constants::to_AUTHORIZATION(static_cast<std::underlying_type<Geolocation::AUTHORIZATION>::type>(type));
		requestLocationPermissions(authorizationType, callback);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getAccuracy, accuracy)
	TITANIUM_FUNCTION_AS_SETTER(GeolocationModule, setAccuracy, accuracy)

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getActivityType, activityType)
	TITANIUM_FUNCTION_AS_SETTER(GeolocationModule, setActivityType, activityType)

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getDistanceFilter, distanceFilter)
	TITANIUM_FUNCTION_AS_SETTER(GeolocationModule, setDistanceFilter, distanceFilter)

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getHeadingFilter, headingFilter)
	TITANIUM_FUNCTION_AS_SETTER(GeolocationModule, setHeadingFilter, headingFilter)

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getHasCompass, hasCompass)

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getLocationServicesAuthorization, locationServicesAuthorization)
	TITANIUM_FUNCTION_AS_SETTER(GeolocationModule, setLocationServicesAuthorization, locationServicesAuthorization)

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getLocationServicesEnabled, locationServicesEnabled)

	TITANIUM_FUNCTION_AS_GETTER(GeolocationModule, getLastGeolocation, lastGeolocation)

} // namespace Titanium
