/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativePlatformExample.hpp"
#include "NativePlatformDisplayCapsExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE

using namespace Titanium;
using namespace HAL;

class PlatformTests : public testing::Test
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

TEST_F(PlatformTests, logging)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	XCTAssertFalse(global_object.HasProperty("Titanium"));
	auto Titanium = js_context.CreateObject();
	global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(global_object.HasProperty("Titanium"));

	// Make the alias "Ti" for the "Titanium" property.
	XCTAssertFalse(global_object.HasProperty("Ti"));
	global_object.SetProperty("Ti", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(global_object.HasProperty("Ti"));

	XCTAssertFalse(Titanium.HasProperty("Platform"));
	auto Platform = js_context.CreateObject(JSExport<NativePlatformExample>::Class());
	Titanium.SetProperty("Platform", Platform, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("Platform"));

	auto Platform_ptr = Platform.GetPrivate<NativePlatformExample>();
	XCTAssertNotEqual(nullptr, Platform_ptr);

	XCTAssertTrue(Platform.HasProperty("BATTERY_STATE_CHARGING"));
	XCTAssertTrue(Platform.HasProperty("BATTERY_STATE_FULL"));
	XCTAssertTrue(Platform.HasProperty("BATTERY_STATE_UNKNOWN"));
	XCTAssertTrue(Platform.HasProperty("BATTERY_STATE_UNPLUGGED"));
	XCTAssertTrue(Platform.HasProperty("address"));
	XCTAssertTrue(Platform.HasProperty("architecture"));
	XCTAssertTrue(Platform.HasProperty("availableMemory"));
	XCTAssertTrue(Platform.HasProperty("batteryState"));
	XCTAssertTrue(Platform.HasProperty("id"));
	XCTAssertTrue(Platform.HasProperty("locale"));
	XCTAssertTrue(Platform.HasProperty("macaddress"));
	XCTAssertTrue(Platform.HasProperty("manufacturer"));
	XCTAssertTrue(Platform.HasProperty("model"));
	XCTAssertTrue(Platform.HasProperty("name"));
	XCTAssertTrue(Platform.HasProperty("netmask"));
	XCTAssertTrue(Platform.HasProperty("osname"));
	XCTAssertTrue(Platform.HasProperty("ostype"));
	XCTAssertTrue(Platform.HasProperty("processorCount"));
	XCTAssertTrue(Platform.HasProperty("runtime"));
	XCTAssertTrue(Platform.HasProperty("username"));
	XCTAssertTrue(Platform.HasProperty("version"));

	XCTAssertTrue(Platform.HasProperty("getAddress"));
	XCTAssertTrue(Platform.HasProperty("getArchitecture"));
	XCTAssertTrue(Platform.HasProperty("getAvailableMemory"));
	XCTAssertTrue(Platform.HasProperty("getBatteryState"));
	XCTAssertTrue(Platform.HasProperty("getId"));
	XCTAssertTrue(Platform.HasProperty("getLocale"));
	XCTAssertTrue(Platform.HasProperty("getMacaddress"));
	XCTAssertTrue(Platform.HasProperty("getManufacturer"));
	XCTAssertTrue(Platform.HasProperty("getModel"));
	XCTAssertTrue(Platform.HasProperty("getName"));
	XCTAssertTrue(Platform.HasProperty("getNetmask"));
	XCTAssertTrue(Platform.HasProperty("getOsname"));
	XCTAssertTrue(Platform.HasProperty("getOstype"));
	XCTAssertTrue(Platform.HasProperty("getProcessorCount"));
	XCTAssertTrue(Platform.HasProperty("getRuntime"));
	XCTAssertTrue(Platform.HasProperty("getUsername"));
	XCTAssertTrue(Platform.HasProperty("getVersion"));

	XCTAssertTrue(Platform.HasProperty("createUUID"));
	XCTAssertTrue(Platform.HasProperty("canOpenURL"));
	XCTAssertTrue(Platform.HasProperty("openURL"));
	XCTAssertTrue(Platform.HasProperty("is24HourTimeFormat"));

	XCTAssertTrue(Platform.HasProperty("displayCaps"));
	XCTAssertTrue(Platform.HasProperty("getDisplayCaps"));

	auto DisplayCaps = Platform.GetProperty("displayCaps");
	XCTAssertTrue(DisplayCaps.IsObject());
	JSObject displayCaps = static_cast<JSObject>(DisplayCaps);
	auto displayCaps_ptr = displayCaps.GetPrivate<NativePlatformDisplayCapsExample>();
	XCTAssertNotEqual(nullptr, displayCaps_ptr);

	XCTAssertTrue(displayCaps.HasProperty("density"));
	XCTAssertTrue(displayCaps.HasProperty("dpi"));
	XCTAssertTrue(displayCaps.HasProperty("logicalDensityFactor"));
	XCTAssertTrue(displayCaps.HasProperty("platformHeight"));
	XCTAssertTrue(displayCaps.HasProperty("platformWidth"));
	XCTAssertTrue(displayCaps.HasProperty("xdpi"));
	XCTAssertTrue(displayCaps.HasProperty("ydpi"));

	auto result = js_context.JSEvaluateScript("Ti.Platform.osname;");
	XCTAssertTrue(result.IsString());
	std::string SIZE = static_cast<std::string>(result);
	XCTAssertEqual("osx", SIZE);
}
