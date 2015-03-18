/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeAPIExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class APITests : public testing::Test
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

TEST_F(APITests, logging)
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

	XCTAssertFalse(Titanium.HasProperty("API"));
	auto API = js_context.CreateObject(JSExport<NativeAPIExample>::Class());
	Titanium.SetProperty("API", API, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("API"));

	auto api_ptr = API.GetPrivate<NativeAPIExample>();
	XCTAssertNotEqual(nullptr, api_ptr);

	XCTAssertTrue(API.HasProperty("info"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("Ti.API.info('Hello, world');"));

	XCTAssertTrue(API.HasProperty("warn"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("Ti.API.warn('Hello, world');"));

	XCTAssertTrue(API.HasProperty("error"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("Ti.API.error('Hello, world');"));

	XCTAssertTrue(API.HasProperty("debug"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("Ti.API.debug('Hello, world');"));

	XCTAssertTrue(API.HasProperty("trace"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("Ti.API.trace('Hello, world');"));
}

TEST_F(APITests, function_parent)
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

	XCTAssertFalse(Titanium.HasProperty("API"));
	auto API = js_context.CreateObject(JSExport<NativeAPIExample>::Class());
	Titanium.SetProperty("API", API, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("API"));

	XCTAssertNoThrow(js_context.JSEvaluateScript("var API  = Ti.API; API.info('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var info = Ti.API.info; info('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var API  = {info:Ti.API.info}; API.info('Hello, world');"));

	XCTAssertNoThrow(js_context.JSEvaluateScript("var API  = Ti.API; API.warn('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var warn = Ti.API.warn; warn('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var API  = {warn:Ti.API.warn}; API.warn('Hello, world');"));

	XCTAssertNoThrow(js_context.JSEvaluateScript("var API   = Ti.API; API.error('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var error = Ti.API.error; error('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var API   = {error:Ti.API.error}; API.error('Hello, world');"));

	XCTAssertNoThrow(js_context.JSEvaluateScript("var API   = Ti.API; API.debug('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var debug = Ti.API.debug; debug('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var API   = {debug:Ti.API.debug}; API.debug('Hello, world');"));

	XCTAssertNoThrow(js_context.JSEvaluateScript("var API   = Ti.API; API.trace('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var trace = Ti.API.trace; trace('Hello, world');"));
	XCTAssertNoThrow(js_context.JSEvaluateScript("var API   = {trace:Ti.API.trace}; API.trace('Hello, world');"));
}
