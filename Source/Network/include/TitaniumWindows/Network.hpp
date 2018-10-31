/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_NETWORKMODULE_HPP_
#define _TITANIUMWINDOWS_NETWORKMODULE_HPP_

#include "TitaniumWindows_Network_EXPORT.h"
#include "Titanium/NetworkModule.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
      @class NetworkModule
      @ingroup Titanium.Network

      @discussion This is the Titanium.Network implementation for Windows.
    */
	class TITANIUMWINDOWS_NETWORK_EXPORT NetworkModule final : public Titanium::NetworkModule, public JSExport<NetworkModule>
	{
	public:

		TITANIUM_PROPERTY_UNIMPLEMENTED(allHTTPCookies);
		TITANIUM_PROPERTY_UNIMPLEMENTED(remoteDeviceUUID);
		TITANIUM_PROPERTY_UNIMPLEMENTED(remoteNotificationTypes);
		TITANIUM_PROPERTY_UNIMPLEMENTED(remoteNotificationsEnabled);

		TITANIUM_FUNCTION_UNIMPLEMENTED(addSystemCookie);
		TITANIUM_FUNCTION_UNIMPLEMENTED(createBonjourBrowser);
		TITANIUM_FUNCTION_UNIMPLEMENTED(createBonjourService);
		TITANIUM_FUNCTION_UNIMPLEMENTED(getHTTPCookiesForDomain);
		TITANIUM_FUNCTION_UNIMPLEMENTED(getSystemCookies);
		TITANIUM_FUNCTION_UNIMPLEMENTED(removeAllHTTPCookies);
		TITANIUM_FUNCTION_UNIMPLEMENTED(removeHTTPCookiesForDomain);
		TITANIUM_FUNCTION_UNIMPLEMENTED(removeAllSystemCookies);
		TITANIUM_FUNCTION_UNIMPLEMENTED(removeSystemCookie);
		TITANIUM_FUNCTION_UNIMPLEMENTED(registerForPushNotifications);
		TITANIUM_FUNCTION_UNIMPLEMENTED(unregisterForPushNotifications);

		virtual std::vector<std::shared_ptr<Titanium::Network::Cookie>> getHTTPCookies(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT override;
		virtual void removeHTTPCookie(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT override;
		virtual void addHTTPCookie(std::shared_ptr<Titanium::Network::Cookie> cookie) TITANIUM_NOEXCEPT override;

		NetworkModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~NetworkModule();
		NetworkModule(const NetworkModule&) = default;
		NetworkModule& operator=(const NetworkModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		NetworkModule(NetworkModule&&) = default;
		NetworkModule& operator=(NetworkModule&&) = default;
#endif

		static void JSExportInitialize();

	protected:
		std::shared_ptr<Titanium::Network::Cookie> createCookie(Windows::Web::Http::HttpCookie^ cookie);
		Windows::Web::Http::HttpCookie^ createCookie(const std::shared_ptr<Titanium::Network::Cookie>& cookie);

		void updateNetworkStatus();
		Windows::Foundation::EventRegistrationToken change_event__;
		Windows::Web::Http::Filters::HttpBaseProtocolFilter^ filter__;
	};

}

#endif  // _TITANIUMWINDOWS_NETWORKMODULE_HPP_
