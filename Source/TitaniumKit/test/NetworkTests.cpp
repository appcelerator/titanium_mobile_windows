/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/NetworkModule.hpp"
#include "Titanium/Network/Cookie.hpp"
#include "Titanium/Network/HTTPClient.hpp"
#include "Titanium/XML.hpp"
#include "NativeHTTPClientExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class NetworkTests : public testing::Test
{
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

	JSContextGroup js_context_group;
};

TEST_F(NetworkTests, BasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());

	auto global_object = js_context.get_global_object();
	auto Titanium = js_context.CreateObject();
	global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	auto Network = js_context.CreateObject(JSExport<Titanium::NetworkModule>::Class());
	auto Network_ptr = Network.GetPrivate<Titanium::NetworkModule>()->
		HTTPClientClass(JSExport<Titanium::Network::HTTPClient>::Class()).
		CookieClass(JSExport<Titanium::Network::Cookie>::Class());

	Titanium.SetProperty("Network", Network);

	XCTAssertTrue(Network.HasProperty("NETWORK_LAN"));
	XCTAssertTrue(Network.HasProperty("NETWORK_MOBILE"));
	XCTAssertTrue(Network.HasProperty("NETWORK_NONE"));
	XCTAssertTrue(Network.HasProperty("NETWORK_UNKNOWN"));
	XCTAssertTrue(Network.HasProperty("NETWORK_WIFI"));
	XCTAssertTrue(Network.HasProperty("NOTIFICATION_TYPE_ALERT"));
	XCTAssertTrue(Network.HasProperty("NOTIFICATION_TYPE_BADGE"));
	XCTAssertTrue(Network.HasProperty("NOTIFICATION_TYPE_SOUND"));
	XCTAssertTrue(Network.HasProperty("NOTIFICATION_TYPE_NEWSSTAND"));
	XCTAssertTrue(Network.HasProperty("TLS_VERSION_1_0"));
	XCTAssertTrue(Network.HasProperty("TLS_VERSION_1_1"));
	XCTAssertTrue(Network.HasProperty("TLS_VERSION_1_2"));
	XCTAssertTrue(Network.HasProperty("PROGRESS_UNKNOWN"));
	XCTAssertTrue(Network.HasProperty("allHTTPCookies"));
	XCTAssertTrue(Network.HasProperty("networkType"));
	XCTAssertTrue(Network.HasProperty("networkTypeName"));
	XCTAssertTrue(Network.HasProperty("online"));
	XCTAssertTrue(Network.HasProperty("remoteDeviceUUID"));
	XCTAssertTrue(Network.HasProperty("remoteNotificationTypes"));
	XCTAssertTrue(Network.HasProperty("remoteNotificationsEnabled"));
	XCTAssertTrue(Network.HasProperty("httpURLFormatter"));

	XCTAssertTrue(Network.HasProperty("addHTTPCookie"));
	XCTAssertTrue(Network.HasProperty("addSystemCookie"));
	XCTAssertTrue(Network.HasProperty("createBonjourBrowser"));
	XCTAssertTrue(Network.HasProperty("createBonjourService"));
	XCTAssertTrue(Network.HasProperty("getHTTPCookies"));
	XCTAssertTrue(Network.HasProperty("getHTTPCookiesForDomain"));
	XCTAssertTrue(Network.HasProperty("getSystemCookies"));
	XCTAssertTrue(Network.HasProperty("removeAllHTTPCookies"));
	XCTAssertTrue(Network.HasProperty("removeAllSystemCookies"));
	XCTAssertTrue(Network.HasProperty("removeHTTPCookie"));
	XCTAssertTrue(Network.HasProperty("removeHTTPCookiesForDomain"));
	XCTAssertTrue(Network.HasProperty("removeSystemCookie"));
	XCTAssertTrue(Network.HasProperty("registerForPushNotifications"));
	XCTAssertTrue(Network.HasProperty("unregisterForPushNotifications"));
	XCTAssertTrue(Network.HasProperty("createCookie"));
	XCTAssertTrue(Network.HasProperty("createHTTPClient"));
	XCTAssertTrue(Network.HasProperty("getAllHTTPCookies"));
	XCTAssertTrue(Network.HasProperty("getNetworkType"));
	XCTAssertTrue(Network.HasProperty("getNetworkTypeName"));
	XCTAssertTrue(Network.HasProperty("getOnline"));
	XCTAssertTrue(Network.HasProperty("getRemoteDeviceUUID"));
	XCTAssertTrue(Network.HasProperty("getRemoteNotificationTypes"));
	XCTAssertTrue(Network.HasProperty("getRemoteNotificationsEnabled"));
	XCTAssertTrue(Network.HasProperty("getHttpURLFormatter"));
	XCTAssertTrue(Network.HasProperty("setHttpURLFormatter"));
}

TEST_F(NetworkTests, CookieBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto Cookie = js_context.CreateObject(JSExport<Titanium::Network::Cookie>::Class());

	XCTAssertTrue(Cookie.HasProperty("comment"));
	XCTAssertTrue(Cookie.HasProperty("domain"));
	XCTAssertTrue(Cookie.HasProperty("expiryDate"));
	XCTAssertTrue(Cookie.HasProperty("httponly"));
	XCTAssertTrue(Cookie.HasProperty("name"));
	XCTAssertTrue(Cookie.HasProperty("originalUrl"));
	XCTAssertTrue(Cookie.HasProperty("path"));
	XCTAssertTrue(Cookie.HasProperty("secure"));
	XCTAssertTrue(Cookie.HasProperty("value"));
	XCTAssertTrue(Cookie.HasProperty("version"));
	XCTAssertTrue(Cookie.HasProperty("isValid"));
	XCTAssertTrue(Cookie.HasProperty("getComment"));
	XCTAssertTrue(Cookie.HasProperty("setComment"));
	XCTAssertTrue(Cookie.HasProperty("getDomain"));
	XCTAssertTrue(Cookie.HasProperty("setDomain"));
	XCTAssertTrue(Cookie.HasProperty("getExpiryDate"));
	XCTAssertTrue(Cookie.HasProperty("setExpiryDate"));
	XCTAssertTrue(Cookie.HasProperty("getHttponly"));
	XCTAssertTrue(Cookie.HasProperty("setHttponly"));
	XCTAssertTrue(Cookie.HasProperty("getName"));
	XCTAssertTrue(Cookie.HasProperty("getOriginalUrl"));
	XCTAssertTrue(Cookie.HasProperty("setOriginalUrl"));
	XCTAssertTrue(Cookie.HasProperty("getPath"));
	XCTAssertTrue(Cookie.HasProperty("setPath"));
	XCTAssertTrue(Cookie.HasProperty("getSecure"));
	XCTAssertTrue(Cookie.HasProperty("setSecure"));
	XCTAssertTrue(Cookie.HasProperty("getValue"));
	XCTAssertTrue(Cookie.HasProperty("setValue"));
	XCTAssertTrue(Cookie.HasProperty("getVersion"));
	XCTAssertTrue(Cookie.HasProperty("setVersion"));
}

TEST_F(NetworkTests, HTTPClientBasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();
	auto Titanium = js_context.CreateObject();
	global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

	auto Network = js_context.CreateObject(JSExport<Titanium::NetworkModule>::Class());
	auto Network_ptr = Network.GetPrivate<Titanium::NetworkModule>()->
		HTTPClientClass(JSExport<Titanium::Network::HTTPClient>::Class()).
		CookieClass(JSExport<Titanium::Network::Cookie>::Class());

	Titanium.SetProperty("Network", Network);

	auto HTTPClient = static_cast<JSObject>(Network.GetProperty("HTTPClient"));

	XCTAssertTrue(HTTPClient.HasProperty("autoEncodeUrl"));
	XCTAssertTrue(HTTPClient.HasProperty("autoRedirect"));
	XCTAssertTrue(HTTPClient.HasProperty("cache"));
	XCTAssertTrue(HTTPClient.HasProperty("domain"));
	XCTAssertTrue(HTTPClient.HasProperty("enableKeepAlive"));
	XCTAssertTrue(HTTPClient.HasProperty("file"));
	XCTAssertTrue(HTTPClient.HasProperty("ondatastream"));
	XCTAssertTrue(HTTPClient.HasProperty("onerror"));
	XCTAssertTrue(HTTPClient.HasProperty("onload"));
	XCTAssertTrue(HTTPClient.HasProperty("onreadystatechange"));
	XCTAssertTrue(HTTPClient.HasProperty("onsendstream"));
	XCTAssertTrue(HTTPClient.HasProperty("password"));
	XCTAssertTrue(HTTPClient.HasProperty("securityManager"));
	XCTAssertTrue(HTTPClient.HasProperty("timeout"));
	XCTAssertTrue(HTTPClient.HasProperty("tlsVersion"));
	XCTAssertTrue(HTTPClient.HasProperty("username"));
	XCTAssertTrue(HTTPClient.HasProperty("validatesSecureCertificate"));
	XCTAssertTrue(HTTPClient.HasProperty("withCredentials"));
	XCTAssertTrue(HTTPClient.HasProperty("DONE"));
	XCTAssertTrue(HTTPClient.HasProperty("HEADERS_RECEIVED"));
	XCTAssertTrue(HTTPClient.HasProperty("LOADING"));
	XCTAssertTrue(HTTPClient.HasProperty("OPENED"));
	XCTAssertTrue(HTTPClient.HasProperty("UNSENT"));
	XCTAssertTrue(HTTPClient.HasProperty("allResponseHeaders"));
	XCTAssertTrue(HTTPClient.HasProperty("connected"));
	XCTAssertTrue(HTTPClient.HasProperty("connectionType"));
	XCTAssertTrue(HTTPClient.HasProperty("location"));
	XCTAssertTrue(HTTPClient.HasProperty("readyState"));
	XCTAssertTrue(HTTPClient.HasProperty("responseData"));
	XCTAssertTrue(HTTPClient.HasProperty("responseText"));
	XCTAssertTrue(HTTPClient.HasProperty("responseXML"));
	XCTAssertTrue(HTTPClient.HasProperty("status"));
	XCTAssertTrue(HTTPClient.HasProperty("statusText"));
	XCTAssertTrue(HTTPClient.HasProperty("abort"));
	XCTAssertTrue(HTTPClient.HasProperty("addAuthFactory"));
	XCTAssertTrue(HTTPClient.HasProperty("addKeyManager"));
	XCTAssertTrue(HTTPClient.HasProperty("addTrustManager"));
	XCTAssertTrue(HTTPClient.HasProperty("clearCookies"));
	XCTAssertTrue(HTTPClient.HasProperty("getAllResponseHeaders"));
	XCTAssertTrue(HTTPClient.HasProperty("getAutoEncodeUrl"));
	XCTAssertTrue(HTTPClient.HasProperty("getAutoRedirect"));
	XCTAssertTrue(HTTPClient.HasProperty("getCache"));
	XCTAssertTrue(HTTPClient.HasProperty("getConnected"));
	XCTAssertTrue(HTTPClient.HasProperty("getConnectionType"));
	XCTAssertTrue(HTTPClient.HasProperty("getDomain"));
	XCTAssertTrue(HTTPClient.HasProperty("getEnableKeepAlive"));
	XCTAssertTrue(HTTPClient.HasProperty("getFile"));
	XCTAssertTrue(HTTPClient.HasProperty("getLocation"));
	XCTAssertTrue(HTTPClient.HasProperty("getOndatastream"));
	XCTAssertTrue(HTTPClient.HasProperty("getOnerror"));
	XCTAssertTrue(HTTPClient.HasProperty("getOnload"));
	XCTAssertTrue(HTTPClient.HasProperty("getOnreadystatechange"));
	XCTAssertTrue(HTTPClient.HasProperty("getOnsendstream"));
	XCTAssertTrue(HTTPClient.HasProperty("getPassword"));
	XCTAssertTrue(HTTPClient.HasProperty("getReadyState"));
	XCTAssertTrue(HTTPClient.HasProperty("getResponseData"));
	XCTAssertTrue(HTTPClient.HasProperty("getResponseHeader"));
	XCTAssertTrue(HTTPClient.HasProperty("getResponseText"));
	XCTAssertTrue(HTTPClient.HasProperty("getResponseXML"));
	XCTAssertTrue(HTTPClient.HasProperty("getSecurityManager"));
	XCTAssertTrue(HTTPClient.HasProperty("getStatus"));
	XCTAssertTrue(HTTPClient.HasProperty("getStatusText"));
	XCTAssertTrue(HTTPClient.HasProperty("getTimeout"));
	XCTAssertTrue(HTTPClient.HasProperty("getTlsVersion"));
	XCTAssertTrue(HTTPClient.HasProperty("getUsername"));
	XCTAssertTrue(HTTPClient.HasProperty("getValidatesSecureCertificate"));
	XCTAssertTrue(HTTPClient.HasProperty("getWithCredentials"));
	XCTAssertTrue(HTTPClient.HasProperty("open"));
	XCTAssertTrue(HTTPClient.HasProperty("send"));
	XCTAssertTrue(HTTPClient.HasProperty("setAutoEncodeUrl"));
	XCTAssertTrue(HTTPClient.HasProperty("setAutoRedirect"));
	XCTAssertTrue(HTTPClient.HasProperty("setCache"));
	XCTAssertTrue(HTTPClient.HasProperty("setDomain"));
	XCTAssertTrue(HTTPClient.HasProperty("setEnableKeepAlive"));
	XCTAssertTrue(HTTPClient.HasProperty("setFile"));
	XCTAssertTrue(HTTPClient.HasProperty("setOndatastream"));
	XCTAssertTrue(HTTPClient.HasProperty("setOnerror"));
	XCTAssertTrue(HTTPClient.HasProperty("setOnload"));
	XCTAssertTrue(HTTPClient.HasProperty("setOnreadystatechange"));
	XCTAssertTrue(HTTPClient.HasProperty("setOnsendstream"));
	XCTAssertTrue(HTTPClient.HasProperty("setPassword"));
	XCTAssertTrue(HTTPClient.HasProperty("setRequestHeader"));
	XCTAssertTrue(HTTPClient.HasProperty("setSecurityManager"));
	XCTAssertTrue(HTTPClient.HasProperty("setTimeout"));
	XCTAssertTrue(HTTPClient.HasProperty("setTlsVersion"));
	XCTAssertTrue(HTTPClient.HasProperty("setUsername"));
	XCTAssertTrue(HTTPClient.HasProperty("setValidatesSecureCertificate"));
	XCTAssertTrue(HTTPClient.HasProperty("setWithCredentials"));
}