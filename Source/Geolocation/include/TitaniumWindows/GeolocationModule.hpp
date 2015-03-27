/**
 * Titanium.Geolocation for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_GEOLOCATION_HPP_
#define _TITANIUMWINDOWS_GEOLOCATION_HPP_

#include "TitaniumWindows/detail/GeolocationBase.hpp"
#include "Titanium/Geolocation/Constants.hpp"

using namespace Windows::Devices::Geolocation;
using namespace Windows::Foundation;
using namespace Windows::Services::Maps;
using namespace Windows::Web::Http;

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Titanium.Geolocation implementation for Windows.
	*/
	class TITANIUMWINDOWS_GEOLOCATION_EXPORT GeolocationModule final : public Titanium::GeolocationModule, public JSExport<GeolocationModule>
	{

	public:
		GeolocationModule(const JSContext&) TITANIUM_NOEXCEPT;
		virtual ~GeolocationModule()                  = default;
		GeolocationModule(const GeolocationModule&)            = default;
		GeolocationModule& operator=(const GeolocationModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		GeolocationModule(GeolocationModule&&)                 = default;
		GeolocationModule& operator=(GeolocationModule&&)      = default;
#endif

		static void JSExportInitialize();

		virtual void set_accuracy(const Titanium::Geolocation::ACCURACY accuracy) TITANIUM_NOEXCEPT override;
		virtual void set_distanceFilter(const double distance) TITANIUM_NOEXCEPT override;
		virtual bool get_locationServicesEnabled() const TITANIUM_NOEXCEPT override;

		virtual void forwardGeocoder(const std::string& address, JSObject callback) TITANIUM_NOEXCEPT override;
		virtual void getCurrentHeading(JSObject callback) TITANIUM_NOEXCEPT override;
		virtual void getCurrentPosition(JSObject callback) TITANIUM_NOEXCEPT override;
		virtual void reverseGeocoder(const double& latitude, const double& longitude, JSObject callback) TITANIUM_NOEXCEPT override;

		virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

	private:

		Geolocator^ geolocator_;

		EventRegistrationToken positionToken_;
		EventRegistrationToken statusToken_;

		Windows::Foundation::EventRegistrationToken location_event_;
		unsigned int location_event_count_{ 0 };

		Windows::Foundation::EventRegistrationToken heading_event_;
		unsigned int heading_event_count_{ 0 };
	};
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_GEOLOCATION_HPP_