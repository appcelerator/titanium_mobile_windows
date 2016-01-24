/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "NativeTiExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE

using namespace Titanium;
using namespace HAL;

class TitaniumTests : public testing::Test
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

TEST_F(TitaniumTests, logging)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	auto Titanium = js_context.CreateObject(JSExport<NativeTiExample>::Class());
	auto Titanium_ptr = Titanium.GetPrivate<NativeTiExample>();
	XCTAssertNotEqual(nullptr, Titanium_ptr);

	XCTAssertTrue(Titanium.HasProperty("version"));
	XCTAssertTrue(Titanium.HasProperty("getVersion"));
	XCTAssertTrue(Titanium.HasProperty("createBuffer"));

	global_object.SetProperty("Ti", Titanium);

	auto result = js_context.JSEvaluateScript("Ti.version;");
	XCTAssertTrue(result.IsString());
	std::string version = static_cast<std::string>(result);
	XCTAssertEqual("__TITANIUM_VERSION__", version);

	result = js_context.JSEvaluateScript("Ti.buildDate;");
	XCTAssertTrue(result.IsString());
	std::string buildDate = static_cast<std::string>(result);
	XCTAssertEqual("__TITANIUM_BUILD_DATE__", buildDate);

	result = js_context.JSEvaluateScript("Ti.buildHash;");
	XCTAssertTrue(result.IsString());
	std::string buildHash = static_cast<std::string>(result);
	XCTAssertEqual("__TITANIUM_BUILD_HASH__", buildHash);

	result = js_context.JSEvaluateScript("Ti.userAgent;");
	XCTAssertTrue(result.IsString());
	std::string userAgent = static_cast<std::string>(result);
	XCTAssertEqual("__TITANIUM_USER_AGENT__", userAgent);

}
