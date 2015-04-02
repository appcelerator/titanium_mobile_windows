/**
 * Titanium.Geolocation for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/GeolocationModule.hpp"
#include "Titanium/detail/TiBase.hpp"

#include <boost/algorithm/string.hpp>
#include <ppltasks.h>
#include <boost/lexical_cast.hpp>

#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	GeolocationModule::GeolocationModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::GeolocationModule(js_context)
	{
		geolocator_ = ref new Geolocator();
		geolocator_->MovementThreshold = 1;
		geolocator_->ReportInterval = 0;
		geolocator_->DesiredAccuracy = PositionAccuracy::High;
	}

	void GeolocationModule::JSExportInitialize() {
		JSExport<GeolocationModule>::SetClassVersion(1);
		JSExport<GeolocationModule>::SetParent(JSExport<Titanium::GeolocationModule>::Class());
	}

	void GeolocationModule::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		// Location event
		if (event_name == "location") {
			if (location_event_count_ == 0) {
				location_event_ = geolocator_->PositionChanged += ref new TypedEventHandler<Geolocator^, PositionChangedEventArgs^>([=](Geolocator^ locator, PositionChangedEventArgs^ args) {
					auto latitude = args->Position->Coordinate->Point->Position.Latitude;
					auto longitude = args->Position->Coordinate->Point->Position.Longitude;
					auto altitude = args->Position->Coordinate->Point->Position.Altitude;
					auto altitudeAccuracy = args->Position->Coordinate->AltitudeAccuracy->Value;
					auto speed = args->Position->Coordinate->Speed->Value;

					Utility::RunOnUIThread([=](){
						lastGeolocation__.SetProperty("latitude", get_context().CreateNumber(latitude));
						lastGeolocation__.SetProperty("longitude", get_context().CreateNumber(longitude));
						lastGeolocation__.SetProperty("altitude", get_context().CreateNumber(altitude));
						lastGeolocation__.SetProperty("altitudeAccuracy", get_context().CreateNumber(altitudeAccuracy));
						lastGeolocation__.SetProperty("speed", get_context().CreateNumber(speed));

						this->fireEvent("location", lastGeolocation__);
					});
				});
			}
			location_event_count_++;

		// Heading event
		} else if (event_name == "heading") {
			if (heading_event_count_ == 0) {
				heading_event_ = geolocator_->PositionChanged += ref new TypedEventHandler<Geolocator^, PositionChangedEventArgs^>([=](Geolocator^ locator, PositionChangedEventArgs^ args) {
					auto heading = args->Position->Coordinate->Heading->Value;

					Utility::RunOnUIThread([=](){
						auto old_heading = static_cast<double>(heading__.GetProperty("heading"));
						if (abs(heading - old_heading) > headingFilter__) {
							heading__.SetProperty("heading", get_context().CreateNumber(heading));

							this->fireEvent("heading", heading__);
						}
					});
				});
			}
			heading_event_count_++;
		}
	}

	void GeolocationModule::set_accuracy(const Titanium::Geolocation::ACCURACY accuracy) TITANIUM_NOEXCEPT
	{
		using namespace Titanium::Geolocation;

		switch (accuracy) {
			case ACCURACY::BEST:
			case ACCURACY::HIGH:
			case ACCURACY::BEST_FOR_NAVIGATION:
				geolocator_->DesiredAccuracyInMeters = 0U;
				geolocator_->DesiredAccuracy = PositionAccuracy::High;
			break;

			default:
			case ACCURACY::LOW: {
				geolocator_->DesiredAccuracyInMeters = 0U;
				geolocator_->DesiredAccuracy = PositionAccuracy::Default;
			}
			break;

			case ACCURACY::NEAREST_TEN_METERS: {
				geolocator_->DesiredAccuracyInMeters = 10U;
			}
			break;

			case ACCURACY::HUNDRED_METERS: {
				geolocator_->DesiredAccuracyInMeters = 100U;
			}
			break;

			case ACCURACY::KILOMETER: {
				geolocator_->DesiredAccuracyInMeters = 1000U;
			}
			break;

			case ACCURACY::THREE_KILOMETERS: {
				geolocator_->DesiredAccuracyInMeters = 3000U;
			}
			break;
		}
		Titanium::GeolocationModule::set_accuracy(accuracy);
	}

	void GeolocationModule::set_distanceFilter(const double distance) TITANIUM_NOEXCEPT
	{
		geolocator_->MovementThreshold = distance;
		Titanium::GeolocationModule::set_distanceFilter(distance);
	}

	bool GeolocationModule::get_locationServicesEnabled() const TITANIUM_NOEXCEPT
	{
		PositionStatus status = geolocator_->LocationStatus;
			switch (status) {
				case PositionStatus::Ready:
					// This is bad, should set locationServicesEnabled__ as mutable?
					const_cast<GeolocationModule*>(this)->set_locationServicesEnabled(true);
					break;
				case PositionStatus::Disabled:
				case PositionStatus::Initializing:
				case PositionStatus::NoData:
				case PositionStatus::NotAvailable:
				case PositionStatus::NotInitialized:
				default:
					// This is bad, should set locationServicesEnabled__ as mutable?
					const_cast<GeolocationModule*>(this)->set_locationServicesEnabled(false);
					break;
			};
		return Titanium::GeolocationModule::get_locationServicesEnabled();
	}

	void GeolocationModule::forwardGeocoder(const std::string& address, JSObject callback) TITANIUM_NOEXCEPT
	{
		auto requestString = std::string("http://api.appcelerator.net/p/v1/geo?d=f");

			//TODO : Use real GUID, MID, SID
			requestString += std::string("&aguid=") + std::string("25FE4B6E-7DA9-4344-B55B-25195570860F");
			requestString += std::string("&mid=") + std::string("com.appcelerator.uuid");
			requestString += std::string("&sid=") + std::string("sid");
			requestString += std::string("&q=") + address;
			//requestString += std::string("&c=") + std::string("US");

			auto requestUri = ref new Windows::Foundation::Uri(Utility::ConvertString(requestString));

			auto httpClient = ref new HttpClient();
			concurrency::create_task(httpClient->GetAsync(requestUri)).then([this, address, callback](HttpResponseMessage^ response) {
				std::vector<std::string> split_response;
				boost::split(split_response, Utility::ConvertString(response->Content->ToString()), boost::is_any_of(","));

				JSObject forwardGeocodeResponse = get_context().CreateObject();

				if (split_response.size() > 0 && split_response.at(0) == "200") {
					double accuracy = atof(split_response.at(1).c_str());
					double latitude = atof(split_response.at(2).c_str());
					double longitude = atof(split_response.at(3).c_str());

					forwardGeocodeResponse.SetProperty("accuracy", get_context().CreateNumber(accuracy));
					forwardGeocodeResponse.SetProperty("address", get_context().CreateString(address));
					forwardGeocodeResponse.SetProperty("latitude", get_context().CreateNumber(latitude));
					forwardGeocodeResponse.SetProperty("longitude", get_context().CreateNumber(longitude));
					forwardGeocodeResponse.SetProperty("success", get_context().CreateBoolean(true));
					forwardGeocodeResponse.SetProperty("error", get_context().CreateString(""));
					forwardGeocodeResponse.SetProperty("code", get_context().CreateNumber(0.0));
				} else {
					forwardGeocodeResponse.SetProperty("success", get_context().CreateBoolean(false));
					forwardGeocodeResponse.SetProperty("error", get_context().CreateString("no results"));
					forwardGeocodeResponse.SetProperty("code", get_context().CreateNumber(static_cast<double>(-1)));
				}

				// Cast callback as non-const JSObject
				// TODO : More elegant way of doing this
				auto cb = static_cast<JSObject>(callback);
				TITANIUM_ASSERT(cb.IsFunction());
				cb({forwardGeocodeResponse}, get_context().get_global_object());
			});
	}

	void GeolocationModule::getCurrentHeading(JSObject callback) TITANIUM_NOEXCEPT
	{
		concurrency::create_task(geolocator_->GetGeopositionAsync()).then([this, callback](Geoposition^ position) {
			auto data = position->Coordinate;
			JSObject headingResponse = get_context().CreateObject();

			headingResponse.SetProperty("code", get_context().CreateNumber(0.0));
			headingResponse.SetProperty("error", get_context().CreateString(""));

			JSObject headingData = get_context().CreateObject();
			headingData.SetProperty("accuracy", get_context().CreateNumber(data->Accuracy));
			headingData.SetProperty("magneticHeading", get_context().CreateNumber(data->Heading->Value));
			headingData.SetProperty("timestamp", get_context().CreateNumber(static_cast<double>(data->Timestamp.UniversalTime)));
			headingData.SetProperty("trueHeading", get_context().CreateNumber(data->Heading->Value));

			//heading_ = data->Heading->Value;

			headingData.SetProperty("x", get_context().CreateNumber(0.0));
			headingData.SetProperty("y", get_context().CreateNumber(0.0));
			headingData.SetProperty("z", get_context().CreateNumber(0.0));

			headingResponse.SetProperty("heading", headingData);
			headingResponse.SetProperty("success", get_context().CreateBoolean(true));

			// Cast callback as non-const JSObject
			// TODO : More elegant way of doing this
			auto cb = static_cast<JSObject>(callback);
			TITANIUM_ASSERT(cb.IsFunction());
			cb({headingResponse}, get_context().get_global_object());
		});
	}

	void GeolocationModule::getCurrentPosition(JSObject callback) TITANIUM_NOEXCEPT
	{
		concurrency::create_task(geolocator_->GetGeopositionAsync()).then([this, callback](Geoposition^ position) {
			auto data = position->Coordinate;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
			JSObject locationResult = get_context().CreateObject();

			locationResult.SetProperty("code", get_context().CreateNumber(0.0));

			JSObject provider = get_context().CreateObject();
			provider.SetProperty("power", get_context().CreateNumber(1.0));
			provider.SetProperty("name", get_context().CreateString("network"));
			provider.SetProperty("accuracy", get_context().CreateNumber(2.0));
			locationResult.SetProperty("provider", provider);

			JSObject coords = get_context().CreateObject();
			coords.SetProperty("altitude", get_context().CreateNumber(data->Point->Position.Altitude));
			coords.SetProperty("speed", get_context().CreateNumber(data->Speed->Value));
			coords.SetProperty("longitude", get_context().CreateNumber(data->Point->Position.Longitude));
			coords.SetProperty("heading", get_context().CreateNumber(data->Heading->Value));
			coords.SetProperty("latitude", get_context().CreateNumber(data->Point->Position.Latitude));
			coords.SetProperty("timestamp", get_context().CreateNumber(static_cast<double>(data->Timestamp.UniversalTime)));
			coords.SetProperty("altitudeAccuracy", get_context().CreateNumber(data->AltitudeAccuracy->Value));
			coords.SetProperty("accuracy", get_context().CreateNumber(data->Accuracy));
			locationResult.SetProperty("coords", coords);

			lastGeolocation__.SetProperty("longitude", get_context().CreateNumber(data->Point->Position.Longitude));
			lastGeolocation__.SetProperty("latitude", get_context().CreateNumber(data->Point->Position.Latitude));

			locationResult.SetProperty("success", get_context().CreateBoolean(true));

			// Cast callback as non-const JSObject
			// TODO : More elegant way of doing this
			auto cb = static_cast<JSObject>(callback);
			TITANIUM_ASSERT(cb.IsFunction());
			cb({locationResult}, get_context().get_global_object());
		});
	}

	void GeolocationModule::reverseGeocoder(const double& latitude, const double& longitude, JSObject callback) TITANIUM_NOEXCEPT
	{
		auto requestString = std::string("http://api.appcelerator.net/p/v1/geo?d=r");

		//TODO : Use real GUID, MID, SID
		requestString += std::string("&aguid=") + std::string("25FE4B6E-7DA9-4344-B55B-25195570860F");
		requestString += std::string("&mid=") + std::string("com.appcelerator.uuid");
		requestString += std::string("&sid=") + std::string("sid");
		requestString += std::string("&q="+boost::lexical_cast<std::string>(latitude)+","+boost::lexical_cast<std::string>(longitude));
		//requestString += std::string("&c=") + std::string("US");

		auto requestUri = ref new Windows::Foundation::Uri(Utility::ConvertString(requestString));

		auto httpClient = ref new HttpClient();
		concurrency::create_task(httpClient->GetAsync(requestUri)).then([this, callback](HttpResponseMessage^ response) {
			auto result = get_context().CreateString(Utility::ConvertString(response->Content->ToString()));

			// Cast callback as non-const JSObject
			// TODO : More elegant way of doing this
			auto cb = static_cast<JSObject>(callback);
			TITANIUM_ASSERT(cb.IsFunction());
			try {
				cb({result}, get_context().get_global_object());
			} catch (...) {
			}
		});
	}
}  // namespace TitaniumWindows