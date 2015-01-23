/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeModuleExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class ModuleTests : public testing::Test
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

TEST_F(ModuleTests, properties)
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

	XCTAssertFalse(Titanium.HasProperty("Module"));
	auto Module = js_context.CreateObject(JSExport<Titanium::Module>::Class());
	Titanium.SetProperty("Module", Module, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("Module"));

	XCTAssertTrue(Module.HasProperty("addEventListener"));
	XCTAssertTrue(Module.HasProperty("applyProperties"));
	XCTAssertTrue(Module.HasProperty("fireEvent"));

	auto nativeModuleExample = js_context.CreateObject(JSExport<NativeModuleExample>::Class());
	global_object.SetProperty("NativeModuleExample", nativeModuleExample, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(global_object.HasProperty("NativeModuleExample"));

	JSValue result = js_context.CreateNull();
	XCTAssertNoThrow(result = js_context.JSEvaluateScript("var module = new NativeModuleExample(); module;"));
	XCTAssertTrue(result.IsObject());

	JSObject module = static_cast<JSObject>(result);
	auto module_ptr = module.GetPrivate<NativeModuleExample>();
	XCTAssertNotEqual(nullptr, module_ptr);

	// Set the name of the event that "enables" the native module. This could be
	// the 'update' event for the Titanium.Accelerometer that turns on the
	// device's battery-consuming accelerometer measurements.
	module_ptr->set_event_name("foo");
	XCTAssertEqual("foo", module_ptr->get_event_name());

	// The native module should be disabled since there are no 'foo' event
	// listeners registered yet.
	XCTAssertNoThrow(result = js_context.JSEvaluateScript("module.enabled;"));
	XCTAssertTrue(result.IsBoolean());
	XCTAssertFalse(static_cast<bool>(result));

	// Create a listener interested in 'foo' events.
	XCTAssertNoThrow(result = js_context.JSEvaluateScript("function fooEventListener(event){};"));
	XCTAssertTrue(result.IsUndefined());

	// Add the event listener to the native module.
	XCTAssertNoThrow(js_context.JSEvaluateScript("module.addEventListener('foo', fooEventListener);"));

	// The native module should now be enabled since there is a 'foo' event
	// listeners registered.
	XCTAssertNoThrow(result = js_context.JSEvaluateScript("module.enabled;"));
	XCTAssertTrue(result.IsBoolean());
	XCTAssertTrue(static_cast<bool>(result));

	// Now remove the event listener.
	XCTAssertNoThrow(js_context.JSEvaluateScript("module.removeEventListener('foo', fooEventListener);"));

	// The native module should now be disabled since there are no more 'foo'
	// event listeners registered.
	XCTAssertNoThrow(result = js_context.JSEvaluateScript("module.enabled;"));
	XCTAssertTrue(result.IsBoolean());
	XCTAssertFalse(static_cast<bool>(result));
}
