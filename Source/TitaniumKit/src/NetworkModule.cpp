/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/NetworkModule.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	NetworkModule::NetworkModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti.Network")
		, networkType__(Titanium::Network::TYPE::UNKNOWN)
		, networkTypeName__(Titanium::Network::Constants::to_string(Titanium::Network::TYPE::UNKNOWN))
		, online__(false)
		, remoteDeviceUUID__("")
		, remoteNotificationsEnabled__(false)
		, httpURLFormatter__(js_context.CreateNull())
	{

	}

	TITANIUM_PROPERTY_READ(NetworkModule, Network::TYPE, networkType);
	TITANIUM_PROPERTY_READ(NetworkModule, std::string, networkTypeName);
	TITANIUM_PROPERTY_READ(NetworkModule, std::string, remoteDeviceUUID);
	TITANIUM_PROPERTY_READ(NetworkModule, std::vector<Network::NOTIFICATION_TYPE>, remoteNotificationTypes);
	TITANIUM_PROPERTY_READ(NetworkModule, bool, remoteNotificationsEnabled);
	TITANIUM_PROPERTY_READ(NetworkModule, bool, online);

	NetworkModule& NetworkModule::HTTPClientClass(const JSClass& httpclient) TITANIUM_NOEXCEPT
	{
		httpclient__ = httpclient;
		return *this;
	}

	NetworkModule& NetworkModule::CookieClass(const JSClass& cookie) TITANIUM_NOEXCEPT
	{
		cookie__ = cookie;
		return *this;
	}

	void NetworkModule::addHTTPCookie(std::shared_ptr<Network::Cookie> cookie) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::addHTTPCookie: unimplemented");
	}

	void NetworkModule::addSystemCookie(std::shared_ptr<Network::Cookie> cookie) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::addSystemCookie: unimplemented");
	}

	std::vector<std::shared_ptr<Network::Cookie>> NetworkModule::get_allHTTPCookies() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::get_allHTTPCookies: unimplemented");
		return std::vector<std::shared_ptr<Network::Cookie>>();
	}

	std::vector<std::shared_ptr<Network::Cookie>> NetworkModule::getHTTPCookies(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::getHTTPCookies: unimplemented");
		return std::vector<std::shared_ptr<Network::Cookie>>();
	}

	std::vector<std::shared_ptr<Network::Cookie>> NetworkModule::getHTTPCookiesForDomain(const std::string& domain) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::getHTTPCookiesForDomain: unimplemented");
		return std::vector<std::shared_ptr<Network::Cookie>>();
	}

	std::vector<std::shared_ptr<Network::Cookie>> NetworkModule::getSystemCookies(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::getSystemCookies: unimplemented");
		return std::vector<std::shared_ptr<Network::Cookie>>();
	}

	void NetworkModule::removeAllHTTPCookies() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::removeAllHTTPCookies: unimplemented");
	}

	void NetworkModule::removeAllSystemCookies() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::removeAllSystemCookies: unimplemented");
	}

	void NetworkModule::removeHTTPCookie(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::removeHTTPCookie: unimplemented");
	}

	void NetworkModule::removeHTTPCookiesForDomain(const std::string& domain) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::removeHTTPCookiesForDomain: unimplemented");
	}

	void NetworkModule::removeSystemCookie(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::removeSystemCookie: unimplemented");
	}

	void NetworkModule::registerForPushNotifications(const Network::PushNotificationConfig& config) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::registerForPushNotifications: unimplemented");
	}

	void NetworkModule::unregisterForPushNotifications() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("NetworkModule::unregisterForPushNotifications: unimplemented");
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, HTTPClient)
	{
		return get_context().CreateObject(httpclient__);
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, Cookie)
	{
		return get_context().CreateObject(cookie__);
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NETWORK_LAN)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TYPE::LAN));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NETWORK_MOBILE)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TYPE::MOBILE));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NETWORK_NONE)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TYPE::NONE));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NETWORK_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TYPE::UNKNOWN));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NETWORK_WIFI)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TYPE::WIFI));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NOTIFICATION_TYPE_ALERT)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::NOTIFICATION_TYPE::ALERT));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NOTIFICATION_TYPE_BADGE)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::NOTIFICATION_TYPE::BADGE));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NOTIFICATION_TYPE_NEWSSTAND)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::NOTIFICATION_TYPE::NEWSSTAND));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, NOTIFICATION_TYPE_SOUND)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::NOTIFICATION_TYPE::SOUND));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, PROGRESS_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::PROGRESS_UNKNOWN);
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, TLS_VERSION_1_0)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TLS_VERSION::_1_0));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, TLS_VERSION_1_1)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TLS_VERSION::_1_1));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, TLS_VERSION_1_2)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(Titanium::Network::TLS_VERSION::_1_2));
	}

	void NetworkModule::JSExportInitialize()
	{
		JSExport<NetworkModule>::SetClassVersion(1);
		JSExport<NetworkModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, HTTPClient);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, Cookie);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NETWORK_LAN);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NETWORK_MOBILE);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NETWORK_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NETWORK_UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NETWORK_WIFI);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NOTIFICATION_TYPE_ALERT);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NOTIFICATION_TYPE_BADGE);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NOTIFICATION_TYPE_SOUND);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, NOTIFICATION_TYPE_NEWSSTAND);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, TLS_VERSION_1_0);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, TLS_VERSION_1_1);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, TLS_VERSION_1_2);
		TITANIUM_ADD_CONSTANT_PROPERTY(NetworkModule, PROGRESS_UNKNOWN);
		TITANIUM_ADD_PROPERTY_READONLY(NetworkModule, allHTTPCookies);
		TITANIUM_ADD_PROPERTY_READONLY(NetworkModule, networkType);
		TITANIUM_ADD_PROPERTY_READONLY(NetworkModule, networkTypeName);
		TITANIUM_ADD_PROPERTY_READONLY(NetworkModule, online);
		TITANIUM_ADD_PROPERTY_READONLY(NetworkModule, remoteDeviceUUID);
		TITANIUM_ADD_PROPERTY_READONLY(NetworkModule, remoteNotificationTypes);
		TITANIUM_ADD_PROPERTY_READONLY(NetworkModule, remoteNotificationsEnabled);
		TITANIUM_ADD_PROPERTY(NetworkModule, httpURLFormatter);

		TITANIUM_ADD_FUNCTION(NetworkModule, addHTTPCookie);
		TITANIUM_ADD_FUNCTION(NetworkModule, addSystemCookie);
		TITANIUM_ADD_FUNCTION(NetworkModule, createBonjourBrowser);
		TITANIUM_ADD_FUNCTION(NetworkModule, createBonjourService);
		TITANIUM_ADD_FUNCTION(NetworkModule, getHTTPCookies);
		TITANIUM_ADD_FUNCTION(NetworkModule, getHTTPCookiesForDomain);
		TITANIUM_ADD_FUNCTION(NetworkModule, getSystemCookies);
		TITANIUM_ADD_FUNCTION(NetworkModule, removeAllHTTPCookies);
		TITANIUM_ADD_FUNCTION(NetworkModule, removeAllSystemCookies);
		TITANIUM_ADD_FUNCTION(NetworkModule, removeHTTPCookie);
		TITANIUM_ADD_FUNCTION(NetworkModule, removeHTTPCookiesForDomain);
		TITANIUM_ADD_FUNCTION(NetworkModule, removeSystemCookie);
		TITANIUM_ADD_FUNCTION(NetworkModule, registerForPushNotifications);
		TITANIUM_ADD_FUNCTION(NetworkModule, unregisterForPushNotifications);
		TITANIUM_ADD_FUNCTION(NetworkModule, createCookie);
		TITANIUM_ADD_FUNCTION(NetworkModule, createHTTPClient);
		TITANIUM_ADD_FUNCTION(NetworkModule, getAllHTTPCookies);
		TITANIUM_ADD_FUNCTION(NetworkModule, getNetworkType);
		TITANIUM_ADD_FUNCTION(NetworkModule, getNetworkTypeName);
		TITANIUM_ADD_FUNCTION(NetworkModule, getOnline);
		TITANIUM_ADD_FUNCTION(NetworkModule, getRemoteDeviceUUID);
		TITANIUM_ADD_FUNCTION(NetworkModule, getRemoteNotificationTypes);
		TITANIUM_ADD_FUNCTION(NetworkModule, getRemoteNotificationsEnabled);
		TITANIUM_ADD_FUNCTION(NetworkModule, getHttpURLFormatter);
		TITANIUM_ADD_FUNCTION(NetworkModule, setHttpURLFormatter);
	}

	TITANIUM_FUNCTION(NetworkModule, createBonjourBrowser)
	{
		TITANIUM_LOG_DEBUG("Network::createBonjourBrowser: ");

		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Network_property = Titanium.GetProperty("Network");
		TITANIUM_ASSERT(Network_property.IsObject());  // precondition
		JSObject Network = static_cast<JSObject>(Network_property);

		JSValue Object_property = Network.GetProperty("BonjourBrowser");
		TITANIUM_ASSERT(Object_property.IsObject());  // precondition
		JSObject Obj = static_cast<JSObject>(Object_property);

		auto object = Obj.CallAsConstructor();
		applyProperties(parameters, object);
		return object;
	}

	TITANIUM_FUNCTION(NetworkModule, createBonjourService)
	{
		TITANIUM_LOG_DEBUG("Network::createBonjourService: ");

		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Network_property = Titanium.GetProperty("Network");
		TITANIUM_ASSERT(Network_property.IsObject());  // precondition
		JSObject Network = static_cast<JSObject>(Network_property);

		JSValue Object_property = Network.GetProperty("BonjourService");
		TITANIUM_ASSERT(Object_property.IsObject());  // precondition
		JSObject Obj = static_cast<JSObject>(Object_property);

		auto object = Obj.CallAsConstructor();
		applyProperties(parameters, object);
		return object;
	}

	TITANIUM_FUNCTION(NetworkModule, createCookie)
	{
		TITANIUM_LOG_DEBUG("Network::createCookie: ");

		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Network_property = Titanium.GetProperty("Network");
		TITANIUM_ASSERT(Network_property.IsObject());  // precondition
		JSObject Network = static_cast<JSObject>(Network_property);

		JSValue Cookie_property = Network.GetProperty("Cookie");
		TITANIUM_ASSERT(Cookie_property.IsObject());  // precondition
		JSObject Cookie = static_cast<JSObject>(Cookie_property);

		auto cookie = Cookie.CallAsConstructor();
		applyProperties(parameters, cookie);
		return cookie;
	}

	TITANIUM_FUNCTION(NetworkModule, createHTTPClient)
	{
		TITANIUM_LOG_DEBUG("Network::createHTTPClient: ");

		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Network_property = Titanium.GetProperty("Network");
		TITANIUM_ASSERT(Network_property.IsObject());  // precondition
		JSObject Network = static_cast<JSObject>(Network_property);

		JSValue HTTPClient_property = Network.GetProperty("HTTPClient");
		TITANIUM_ASSERT(HTTPClient_property.IsObject());  // precondition
		JSObject HTTPClient = static_cast<JSObject>(HTTPClient_property);

		auto httpClient = HTTPClient.CallAsConstructor();
		applyProperties(parameters, httpClient);
		return httpClient;
	}

	TITANIUM_FUNCTION(NetworkModule, addHTTPCookie)
	{
		ENSURE_OBJECT_AT_INDEX(cookie, 0);
		addHTTPCookie(cookie.GetPrivate<Network::Cookie>());
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, addSystemCookie)
	{
		ENSURE_OBJECT_AT_INDEX(cookie, 0);
		addSystemCookie(cookie.GetPrivate<Network::Cookie>());
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, removeAllHTTPCookies)
	{
		removeAllHTTPCookies();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, removeAllSystemCookies)
	{
		removeAllSystemCookies();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, removeHTTPCookie)
	{
		ENSURE_STRING_AT_INDEX(domain, 0);
		ENSURE_STRING_AT_INDEX(path, 1);
		ENSURE_STRING_AT_INDEX(name, 2);
		removeHTTPCookie(domain, path, name);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, removeHTTPCookiesForDomain)
	{
		ENSURE_STRING_AT_INDEX(domain, 0);
		removeHTTPCookiesForDomain(domain);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, removeSystemCookie)
	{
		ENSURE_STRING_AT_INDEX(domain, 0);
		ENSURE_STRING_AT_INDEX(path, 1);
		ENSURE_STRING_AT_INDEX(name, 2);
		removeSystemCookie(domain, path, name);
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, registerForPushNotifications)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(config, 0);
		registerForPushNotifications(Network::js_to_PushNotificationConfig(config));
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, unregisterForPushNotifications)
	{
		unregisterForPushNotifications();
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(NetworkModule, getHTTPCookies)
	{
		ENSURE_STRING_AT_INDEX(domain, 0);
		ENSURE_STRING_AT_INDEX(path, 1);
		ENSURE_STRING_AT_INDEX(name, 2);

		std::vector<JSValue> values;
		for (const auto value : getHTTPCookies(domain, path, name)) {
			values.push_back(value->get_object());
		}
		return get_context().CreateArray(values);
	}

	TITANIUM_FUNCTION(NetworkModule, getHTTPCookiesForDomain)
	{
		ENSURE_STRING_AT_INDEX(domain, 0);

		std::vector<JSValue> values;
		for (const auto value : getHTTPCookiesForDomain(domain)) {
			values.push_back(value->get_object());
		}
		return get_context().CreateArray(values);
	}

	TITANIUM_FUNCTION(NetworkModule, getSystemCookies)
	{
		ENSURE_STRING_AT_INDEX(domain, 0);
		ENSURE_STRING_AT_INDEX(path, 1);
		ENSURE_STRING_AT_INDEX(name, 2);

		std::vector<JSValue> values;
		for (const auto value : getSystemCookies(domain, path, name)) {
			values.push_back(value->get_object());
		}
		return get_context().CreateArray(values);
	}

	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getAllHTTPCookies, allHTTPCookies)
	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getNetworkType, networkType)
	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getNetworkTypeName, networkTypeName)
	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getOnline, online)
	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getRemoteDeviceUUID, remoteDeviceUUID)
	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getRemoteNotificationTypes, remoteNotificationTypes)
	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getRemoteNotificationsEnabled, remoteNotificationsEnabled)
	TITANIUM_FUNCTION_AS_GETTER(NetworkModule, getHttpURLFormatter, httpURLFormatter)
	TITANIUM_FUNCTION_AS_SETTER(NetworkModule, setHttpURLFormatter, httpURLFormatter)

	TITANIUM_PROPERTY_GETTER_BOOL(NetworkModule, online);
	TITANIUM_PROPERTY_GETTER_STRING(NetworkModule, remoteDeviceUUID);
	TITANIUM_PROPERTY_GETTER_BOOL(NetworkModule, remoteNotificationsEnabled);
	TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(NetworkModule, allHTTPCookies);

	TITANIUM_PROPERTY_GETTER(NetworkModule, networkType)
	{
		return get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(get_networkType()));
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, networkTypeName)
	{
		const auto type = Titanium::Network::Constants::to_string(get_networkType());
		return get_context().CreateString(type);
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, remoteNotificationTypes)
	{
		std::vector<JSValue> types;
		for (const auto t : get_remoteNotificationTypes()) {
			types.push_back(get_context().CreateNumber(Titanium::Network::Constants::to_underlying_type(t)));
		}
		return get_context().CreateArray(types);
	}

	TITANIUM_PROPERTY_GETTER(NetworkModule, httpURLFormatter)
	{
		return httpURLFormatter__;
	}

	TITANIUM_PROPERTY_SETTER(NetworkModule, httpURLFormatter)
	{
		TITANIUM_ASSERT(argument.IsObject());
		httpURLFormatter__ = static_cast<JSObject>(argument);
		return true;
	}
}
