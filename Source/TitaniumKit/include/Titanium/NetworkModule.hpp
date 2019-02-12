/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_NETWORK_HPP_
#define _TITANIUM_NETWORK_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Network/Constants.hpp"
#include "Titanium/Network/PushNotificationConfig.hpp"

namespace Titanium
{
	using namespace HAL;

	namespace Network
	{
		class Cookie;
	}

	/*!
      @class
      @discussion This is the Ti.Network Module.
      See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Network
    */
	class TITANIUMKIT_EXPORT NetworkModule : public Module, public JSExport<NetworkModule>
	{
	public:

		/*!
		  @property
		  @abstract allHTTPCookies
		  @discussion A list of all cookies in the cookie storage.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<Network::Cookie>>, allHTTPCookies);

		/*!
		  @property
		  @abstract networkType
		  @discussion Network type value as a constant.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(Network::TYPE, networkType);

		/*!
		  @property
		  @abstract online
		  @discussion Boolean value indicating if the device can reach the Internet.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(bool, online);

		/*!
		  @property
		  @abstract remoteDeviceUUID
		  @discussion Remote device UUID if the device is registered with the Apple Push NotificationService, or null if it is not registered.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, remoteDeviceUUID);

		/*!
		  @property
		  @abstract remoteNotificationTypes
		  @discussion Array of push notification type constants enabled for the application.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<Network::NOTIFICATION_TYPE>, remoteNotificationTypes);

		/*!
		  @property
		  @abstract remoteNotificationsEnabled
		  @discussion Indicates whether push  notifications have been enabled using [registerForPushNotifications](Titanium.Network.registerForPushNotifications).
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(bool, remoteNotificationsEnabled);

		/*!
		  @method
		  @abstract addHTTPCookie
		  @discussion Adds a cookie to the HTTP client cookie store.
		*/
		virtual void addHTTPCookie(std::shared_ptr<Network::Cookie> cookie) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract addSystemCookie
		  @discussion Adds a cookie to the system cookie store.
		*/
		virtual void addSystemCookie(std::shared_ptr<Network::Cookie> cookie) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getHTTPCookies
		  @discussion Gets all the cookies with the domain, path and name matched with the given values from the HTTP client cookie store.
		*/
		virtual std::vector<std::shared_ptr<Network::Cookie>> getHTTPCookies(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getHTTPCookiesForDomain
		  @discussion Gets all the cookies with the domain matched with the given values from the HTTP client cookie store.
		*/
		virtual std::vector<std::shared_ptr<Network::Cookie>> getHTTPCookiesForDomain(const std::string& domain) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getSystemCookies
		  @discussion Gets all the cookies with the domain, path and name matched with the given values from the system cookie store.
		*/
		virtual std::vector<std::shared_ptr<Network::Cookie>> getSystemCookies(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract removeAllHTTPCookies
		  @discussion Removes all the cookies from the HTTP client cookie store.
		*/
		virtual void removeAllHTTPCookies() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract removeAllSystemCookies
		  @discussion Removes all the cookie from the system client cookie store.
		*/
		virtual void removeAllSystemCookies() TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract removeHTTPCookie
		  @discussion Removes the cookie with the domain, path and name exactly the same as the given values from the HTTP client cookie store.
		*/
		virtual void removeHTTPCookie(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract removeHTTPCookiesForDomain
		  @discussion Removes the cookies with the domain matched with the given values from the HTTP client cookie store.
		*/
		virtual void removeHTTPCookiesForDomain(const std::string& domain) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract removeSystemCookie
		  @discussion Removes the cookie with the domain, path and name exactly the same as the given values from the system cookie store.
		*/
		virtual void removeSystemCookie(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract registerForPushNotifications
		  @discussion Registers for push notifications with the Apple Push Notification Service.
		*/
		virtual void registerForPushNotifications(const Network::PushNotificationConfig& config) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract unregisterForPushNotifications
		  @discussion Unregisters the application for push notifications.
		*/
		virtual void unregisterForPushNotifications() TITANIUM_NOEXCEPT;

		NetworkModule& HTTPClientClass(const JSClass&) TITANIUM_NOEXCEPT;
		NetworkModule& CookieClass(const JSClass&) TITANIUM_NOEXCEPT;
		
		TITANIUM_PROPERTY_READONLY_DEF(HTTPClient);
		TITANIUM_PROPERTY_READONLY_DEF(Cookie);
		TITANIUM_PROPERTY_READONLY_DEF(NETWORK_LAN);
		TITANIUM_PROPERTY_READONLY_DEF(NETWORK_MOBILE);
		TITANIUM_PROPERTY_READONLY_DEF(NETWORK_NONE);
		TITANIUM_PROPERTY_READONLY_DEF(NETWORK_UNKNOWN);
		TITANIUM_PROPERTY_READONLY_DEF(NETWORK_WIFI);
		TITANIUM_PROPERTY_READONLY_DEF(NOTIFICATION_TYPE_ALERT);
		TITANIUM_PROPERTY_READONLY_DEF(NOTIFICATION_TYPE_BADGE);
		TITANIUM_PROPERTY_READONLY_DEF(NOTIFICATION_TYPE_SOUND);
		TITANIUM_PROPERTY_READONLY_DEF(NOTIFICATION_TYPE_NEWSSTAND);
		TITANIUM_PROPERTY_READONLY_DEF(TLS_VERSION_1_0);
		TITANIUM_PROPERTY_READONLY_DEF(TLS_VERSION_1_1);
		TITANIUM_PROPERTY_READONLY_DEF(TLS_VERSION_1_2);
		TITANIUM_PROPERTY_READONLY_DEF(PROGRESS_UNKNOWN);
		TITANIUM_PROPERTY_READONLY_DEF(allHTTPCookies);
		TITANIUM_PROPERTY_READONLY_DEF(networkType);
		TITANIUM_PROPERTY_READONLY_DEF(networkTypeName);
		TITANIUM_PROPERTY_READONLY_DEF(online);
		TITANIUM_PROPERTY_READONLY_DEF(remoteDeviceUUID);
		TITANIUM_PROPERTY_READONLY_DEF(remoteNotificationTypes);
		TITANIUM_PROPERTY_READONLY_DEF(remoteNotificationsEnabled);
		TITANIUM_PROPERTY_DEF(httpURLFormatter);

		TITANIUM_FUNCTION_DEF(addHTTPCookie);
		TITANIUM_FUNCTION_DEF(addSystemCookie);
		TITANIUM_FUNCTION_DEF(createBonjourBrowser);
		TITANIUM_FUNCTION_DEF(createBonjourService);
		TITANIUM_FUNCTION_DEF(getHTTPCookies);
		TITANIUM_FUNCTION_DEF(getHTTPCookiesForDomain);
		TITANIUM_FUNCTION_DEF(getSystemCookies);
		TITANIUM_FUNCTION_DEF(removeAllHTTPCookies);
		TITANIUM_FUNCTION_DEF(removeAllSystemCookies);
		TITANIUM_FUNCTION_DEF(removeHTTPCookie);
		TITANIUM_FUNCTION_DEF(removeHTTPCookiesForDomain);
		TITANIUM_FUNCTION_DEF(removeSystemCookie);
		TITANIUM_FUNCTION_DEF(registerForPushNotifications);
		TITANIUM_FUNCTION_DEF(unregisterForPushNotifications);
		TITANIUM_FUNCTION_DEF(createCookie);
		TITANIUM_FUNCTION_DEF(createHTTPClient);
		TITANIUM_FUNCTION_DEF(getAllHTTPCookies);
		TITANIUM_FUNCTION_DEF(getNetworkType);
		TITANIUM_FUNCTION_DEF(getNetworkTypeName);
		TITANIUM_FUNCTION_DEF(getOnline);
		TITANIUM_FUNCTION_DEF(getRemoteDeviceUUID);
		TITANIUM_FUNCTION_DEF(getRemoteNotificationTypes);
		TITANIUM_FUNCTION_DEF(getRemoteNotificationsEnabled);
		TITANIUM_FUNCTION_DEF(getHttpURLFormatter);
		TITANIUM_FUNCTION_DEF(setHttpURLFormatter);

		NetworkModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~NetworkModule() = default;
		NetworkModule(const NetworkModule&) = default;
		NetworkModule& operator=(const NetworkModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		NetworkModule(NetworkModule&&) = default;
		NetworkModule& operator=(NetworkModule&&) = default;
#endif

		static void JSExportInitialize();

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		JSClass httpclient__;
		JSClass cookie__;
		
		Network::TYPE networkType__;
		bool online__;
		std::string remoteDeviceUUID__;
		std::vector<Network::NOTIFICATION_TYPE> remoteNotificationTypes__;
		bool remoteNotificationsEnabled__;
		
		// User-defined function that is called everytime HTTPClient connects to a remote resource.
		JSValue httpURLFormatter__;
#pragma warning(pop)

	};
} // namespace Titanium

#endif  // _TITANIUM_NETWORK_HPP_
