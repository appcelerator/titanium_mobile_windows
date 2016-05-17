/**
 * Titanium.Geolocation for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Geolocation.hpp"
#include "Titanium/detail/TiImpl.hpp"

#include <boost/algorithm/string.hpp>
#include <ppltasks.h>
#include <collection.h>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <concrt.h>

#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	using namespace Windows::Devices::Geolocation;
	using namespace Windows::Foundation;
	using namespace Windows::Web::Http;

	Geolocation::Geolocation(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::GeolocationModule(js_context)
	{
		loadAppxManifest();
	}

	void Geolocation::JSExportInitialize() {
		JSExport<Geolocation>::SetClassVersion(1);
		JSExport<Geolocation>::SetParent(JSExport<Titanium::GeolocationModule>::Class());
	}

	void Geolocation::ensureLoadGeolocator() 
	{
		if (!get_locationServicesEnabled()) {
			return;
		}
		if (geolocator_ == nullptr) {

#if defined(IS_WINDOWS_10)
			TitaniumWindows::Utility::RunOnUIThread([this]() {
				concurrency::create_task(Geolocator::RequestAccessAsync()).then([this](GeolocationAccessStatus status) {
					if (status == GeolocationAccessStatus::Denied) {
						locationServicesAuthorization__ = Titanium::Geolocation::AUTHORIZATION::DENIED;
					} else if (status == GeolocationAccessStatus::Allowed) {
						locationServicesAuthorization__ = Titanium::Geolocation::AUTHORIZATION::AUTHORIZED;
					}
				});
			});
#endif
			geolocator_ = ref new Geolocator();
			geolocator_->MovementThreshold = 1;
			geolocator_->ReportInterval = 0;
			geolocator_->DesiredAccuracy = PositionAccuracy::High;
		}
	}

	void Geolocation::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::GeolocationModule::enableEvent(event_name);

		if (!get_locationServicesEnabled()) {
			return;
		}

		ensureLoadGeolocator();

		// Location event
		if (event_name == "location") {
			location_event_ = geolocator_->PositionChanged += ref new TypedEventHandler<Geolocator^, PositionChangedEventArgs^>([=](Geolocator^ locator, PositionChangedEventArgs^ args) {
				const auto latitude = args->Position->Coordinate->Point->Position.Latitude;
				const auto longitude = args->Position->Coordinate->Point->Position.Longitude;
				const auto altitude = args->Position->Coordinate->Point->Position.Altitude;
				const auto altitudeAccuracy = args->Position->Coordinate->AltitudeAccuracy;
				const auto speed = args->Position->Coordinate->Speed;

				const auto func = [=](){
					const auto ctx = get_context();

					auto coords = ctx.CreateObject();
					coords.SetProperty("latitude", ctx.CreateNumber(latitude));
					coords.SetProperty("longitude", ctx.CreateNumber(longitude));
					coords.SetProperty("altitude", ctx.CreateNumber(altitude));
					coords.SetProperty("altitudeAccuracy", altitudeAccuracy ? ctx.CreateNumber(altitudeAccuracy->Value) : ctx.CreateNumber(0));
					coords.SetProperty("speed", speed ? ctx.CreateNumber(speed->Value) : ctx.CreateNumber(0));

					lastGeolocation__.SetProperty("code", ctx.CreateNumber(0.0));
					lastGeolocation__.SetProperty("error", ctx.CreateString(""));
					lastGeolocation__.SetProperty("success", ctx.CreateBoolean(true));
					lastGeolocation__.SetProperty("coords", coords);

					this->fireEvent("location", lastGeolocation__);
				};

				// Check if we are in background, in that case we do not run it on UI thread.
				if (static_cast<bool>(get_context().JSEvaluateScript("Ti.App.Windows.BackgroundService.suspended;"))) {
					func();
				} else {
					Utility::RunOnUIThread(func);
				}
			});

		// Heading event
		} else if (event_name == "heading") {
			heading_event_ = geolocator_->PositionChanged += ref new TypedEventHandler<Geolocator^, PositionChangedEventArgs^>([=](Geolocator^ locator, PositionChangedEventArgs^ args) {
				const auto heading = args->Position->Coordinate->Heading->Value;

				const auto func = [=](){
					const auto old_heading = static_cast<double>(heading__.GetProperty("heading"));
					if (abs(heading - old_heading) > headingFilter__) {
						heading__.SetProperty("heading", get_context().CreateNumber(heading));

						this->fireEvent("heading", heading__);
					}
				};

				// Check if we are in background, in that case we do not run it on UI thread.
				if (static_cast<bool>(get_context().JSEvaluateScript("Ti.App.Windows.BackgroundService.suspended;"))) {
					func();
				} else {
					Utility::RunOnUIThread(func);
				}

			});
		}
	}

	void Geolocation::set_accuracy(const Titanium::Geolocation::ACCURACY& accuracy) TITANIUM_NOEXCEPT
	{
		using namespace Titanium::Geolocation;

		Titanium::GeolocationModule::set_accuracy(accuracy);

		if (!get_locationServicesEnabled()) {
			return;
		}

		ensureLoadGeolocator();

		switch (accuracy) {
			case ACCURACY::BEST:
			case ACCURACY::HIGH:
			case ACCURACY::BEST_FOR_NAVIGATION:
				geolocator_->DesiredAccuracyInMeters = nullptr;
				geolocator_->DesiredAccuracy = PositionAccuracy::High;
			break;

			default:
			case ACCURACY::LOW: {
				geolocator_->DesiredAccuracyInMeters = nullptr;
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
	}

	void Geolocation::set_distanceFilter(const double& distance) TITANIUM_NOEXCEPT
	{
		Titanium::GeolocationModule::set_distanceFilter(distance);

		if (!get_locationServicesEnabled()) {
			return;
		}

		ensureLoadGeolocator();

		geolocator_->MovementThreshold = distance;
	}

	void Geolocation::loadAppxManifest()
	{
		using namespace Windows::Data::Xml::Dom;
		using namespace Windows::Storage;
		using namespace concurrency;

		concurrency::event event;
		task<StorageFile^>(Windows::ApplicationModel::Package::Current->InstalledLocation->GetFileAsync("AppxManifest.xml")).then([&event, this](task<StorageFile^> fileTask) {
			try {
				task<XmlDocument^>(XmlDocument::LoadFromFileAsync(fileTask.get())).then([&event, this](task<XmlDocument^> docTask) {
					try {
						const auto doc = docTask.get();
						const auto items = doc->GetElementsByTagName("DeviceCapability");
						for (unsigned int i = 0; i < items->Length; i++) {
							const auto node = items->GetAt(i);
							const auto name = static_cast<Platform::String^>(node->Attributes->GetNamedItem("Name")->NodeValue);
							if (name == "location") {
								set_locationServicesEnabled(true);
							}
						}
					} catch (...) {
						set_locationServicesEnabled(false);
					}
					event.set();
				}, concurrency::task_continuation_context::use_arbitrary());
			} catch (...) {
				set_locationServicesEnabled(true);
				event.set();
			}
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();
	}

	void Geolocation::forwardGeocoder(const std::string& address, JSObject callback) TITANIUM_NOEXCEPT
	{
		if (!get_locationServicesEnabled()) {
			return;
		}

		auto requestString = std::string("http://api.appcelerator.net/p/v1/geo?d=f");

			//TODO : Use real GUID, MID, SID
			requestString += std::string("&aguid=") + std::string("25FE4B6E-7DA9-4344-B55B-25195570860F");
			requestString += std::string("&mid=") + std::string("com.appcelerator.uuid");
			requestString += std::string("&sid=") + std::string("sid");
			requestString += std::string("&q=") + address;
			//requestString += std::string("&c=") + std::string("US");

			const auto requestUri = ref new Windows::Foundation::Uri(Utility::ConvertString(requestString));

			const auto httpClient = ref new HttpClient();
			concurrency::create_task(httpClient->GetAsync(requestUri)).then([this, address, callback](HttpResponseMessage^ response) {
				try {
					std::vector<std::string> split_response;
					boost::split(split_response, Utility::ConvertString(response->Content->ToString()), boost::is_any_of(","));

					JSObject forwardGeocodeResponse = get_context().CreateObject();

					if (split_response.size() > 0 && split_response.at(0) == "200") {
						const double accuracy = atof(split_response.at(1).c_str());
						const double latitude = atof(split_response.at(2).c_str());
						const double longitude = atof(split_response.at(3).c_str());

						forwardGeocodeResponse.SetProperty("accuracy", get_context().CreateNumber(accuracy));
						forwardGeocodeResponse.SetProperty("address", get_context().CreateString(address));
						forwardGeocodeResponse.SetProperty("latitude", get_context().CreateNumber(latitude));
						forwardGeocodeResponse.SetProperty("longitude", get_context().CreateNumber(longitude));
						forwardGeocodeResponse.SetProperty("success", get_context().CreateBoolean(true));
						forwardGeocodeResponse.SetProperty("error", get_context().CreateString(""));
						forwardGeocodeResponse.SetProperty("code", get_context().CreateNumber(0.0));
					}
					else {
						forwardGeocodeResponse.SetProperty("success", get_context().CreateBoolean(false));
						forwardGeocodeResponse.SetProperty("error", get_context().CreateString("no results"));
						forwardGeocodeResponse.SetProperty("code", get_context().CreateNumber(static_cast<double>(-1)));
					}

					// Cast callback as non-const JSObject
					// TODO : More elegant way of doing this
					auto cb = static_cast<JSObject>(callback);
					TITANIUM_ASSERT(cb.IsFunction());
					cb({ forwardGeocodeResponse }, get_context().get_global_object());
				} catch (...) {
					// TODO: Need to revisit - Geolocation module basically lacks exception handling during callback
					TITANIUM_LOG_WARN("Error duging Geolocation::forwardGeocoder");
				}
			});
	}

	void Geolocation::getCurrentHeading(JSObject callback) TITANIUM_NOEXCEPT
	{
		if (!get_locationServicesEnabled()) {
			return;
		}

		ensureLoadGeolocator();

		concurrency::create_task(geolocator_->GetGeopositionAsync()).then([this, callback](Geoposition^ position) {
			const auto ctx = get_context();
			const auto data = position->Coordinate;
			JSObject headingResponse = ctx.CreateObject();

			headingResponse.SetProperty("code", ctx.CreateNumber(0.0));
			headingResponse.SetProperty("error", ctx.CreateString(""));

			JSObject headingData = ctx.CreateObject();
			headingData.SetProperty("accuracy", ctx.CreateNumber(data->Accuracy));
			headingData.SetProperty("magneticHeading", ctx.CreateNumber(data->Heading->Value));
			headingData.SetProperty("timestamp", ctx.CreateNumber(static_cast<double>(data->Timestamp.UniversalTime)));
			headingData.SetProperty("trueHeading", ctx.CreateNumber(data->Heading->Value));

			//heading_ = data->Heading->Value;

			headingData.SetProperty("x", ctx.CreateNumber(0.0));
			headingData.SetProperty("y", ctx.CreateNumber(0.0));
			headingData.SetProperty("z", ctx.CreateNumber(0.0));

			headingResponse.SetProperty("heading", headingData);
			headingResponse.SetProperty("success", ctx.CreateBoolean(true));

			try {
				// Cast callback as non-const JSObject
				auto cb = static_cast<JSObject>(callback);
				TITANIUM_ASSERT(cb.IsFunction());
				cb({headingResponse}, get_object());
			} catch (const HAL::detail::js_runtime_error& ex) {
				// In case callback throws JS exception, we want to catch it.
				std::ostringstream os;
				os << "Runtime Error: " << ex.js_message();

				const auto what = ctx.CreateString(os.str());
				const auto rsod = ctx.get_global_object().GetProperty("Titanium_RedScreenOfDeath");
				auto rsod_func = static_cast<JSObject>(rsod);
				rsod_func({ what }, rsod_func);
			}

		});
	}

	void Geolocation::getCurrentPosition(JSObject callback) TITANIUM_NOEXCEPT
	{
		if (!get_locationServicesEnabled()) {
			return;
		}

		ensureLoadGeolocator();

		concurrency::create_task(geolocator_->GetGeopositionAsync()).then([this, callback](Geoposition^ position) {
			const auto ctx = get_context();
			const auto data = position->Coordinate;    
			JSObject locationResult = ctx.CreateObject();

			locationResult.SetProperty("code", ctx.CreateNumber(0.0));
			locationResult.SetProperty("error", ctx.CreateString(""));

			JSObject provider = ctx.CreateObject();
			provider.SetProperty("power", ctx.CreateNumber(1.0));
			provider.SetProperty("name", ctx.CreateString("network"));
			provider.SetProperty("accuracy", ctx.CreateNumber(2.0));
			locationResult.SetProperty("provider", provider);

			JSObject coords = ctx.CreateObject();
			coords.SetProperty("altitude", ctx.CreateNumber(data->Point->Position.Altitude));
			coords.SetProperty("speed", ctx.CreateNumber(data->Speed->Value));
			coords.SetProperty("longitude", ctx.CreateNumber(data->Point->Position.Longitude));
			coords.SetProperty("heading", ctx.CreateNumber(data->Heading->Value));
			coords.SetProperty("latitude", ctx.CreateNumber(data->Point->Position.Latitude));
			coords.SetProperty("timestamp", ctx.CreateNumber(static_cast<double>(data->Timestamp.UniversalTime)));
			//coords.SetProperty("altitudeAccuracy", ctx.CreateNumber(data->AltitudeAccuracy->Value));
			coords.SetProperty("accuracy", ctx.CreateNumber(data->Accuracy));
			locationResult.SetProperty("coords", coords);

			lastGeolocation__.SetProperty("longitude", ctx.CreateNumber(data->Point->Position.Longitude));
			lastGeolocation__.SetProperty("latitude", ctx.CreateNumber(data->Point->Position.Latitude));

			locationResult.SetProperty("success", ctx.CreateBoolean(true));

			try {
				// Cast callback as non-const JSObject
				auto cb = static_cast<JSObject>(callback);
				cb({ locationResult }, get_object());
			} catch (const HAL::detail::js_runtime_error& ex) {
				// In case callback throws JS exception, we want to catch it.
				std::ostringstream os;
				os << "Runtime Error: " << ex.js_message();

				const auto what = ctx.CreateString(os.str());
				const auto rsod = ctx.get_global_object().GetProperty("Titanium_RedScreenOfDeath");
				auto rsod_func = static_cast<JSObject>(rsod);
				rsod_func({ what }, rsod_func);
			}
		});
	}

	void Geolocation::reverseGeocoder(const double& latitude, const double& longitude, JSObject callback) TITANIUM_NOEXCEPT
	{
		if (!get_locationServicesEnabled()) {
			return;
		}

		ensureLoadGeolocator();

		auto requestString = std::string("http://api.appcelerator.net/p/v1/geo?d=r");

		//TODO : Use real GUID, MID, SID
		requestString += std::string("&aguid=") + std::string("25FE4B6E-7DA9-4344-B55B-25195570860F");
		requestString += std::string("&mid=") + std::string("com.appcelerator.uuid");
		requestString += std::string("&sid=") + std::string("sid");
		requestString += std::string("&q="+boost::lexical_cast<std::string>(latitude)+","+boost::lexical_cast<std::string>(longitude));
		//requestString += std::string("&c=") + std::string("US");

		const auto requestUri = ref new Windows::Foundation::Uri(Utility::ConvertString(requestString));

		const auto httpClient = ref new HttpClient();
		concurrency::create_task(httpClient->GetAsync(requestUri)).then([this, callback](HttpResponseMessage^ response) {
			auto result = get_context().CreateValueFromJSON(Utility::ConvertString(response->Content->ToString()));

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