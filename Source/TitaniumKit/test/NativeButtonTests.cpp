/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeButtonExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class ButtonTests : public testing::Test
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

TEST_F(ButtonTests, basic_functionality)
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

	XCTAssertFalse(Titanium.HasProperty("UI"));
	auto UI = js_context.CreateObject(JSExport<Titanium::UIModule>::Class());
	Titanium.SetProperty("UI", UI, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("UI"));

	// Inherited from Titanium::Module.
	XCTAssertTrue(UI.HasProperty("addEventListener"));
	XCTAssertTrue(UI.HasProperty("applyProperties"));
	XCTAssertTrue(UI.HasProperty("fireEvent"));

	// Rrom Titanium::UI module.
	XCTAssertTrue(UI.HasProperty("createView"));
	XCTAssertTrue(UI.HasProperty("createWindow"));
	XCTAssertTrue(UI.HasProperty("createButton"));

	auto Button = js_context.CreateObject(JSExport<NativeButtonExample>::Class());
	auto button_ptr = Button.GetPrivate<NativeButtonExample>();
	XCTAssertNotEqual(nullptr, button_ptr);

	UI.SetProperty("Button", Button);
	XCTAssertTrue(UI.HasProperty("Button"));

	JSValue result = js_context.CreateNull();
	XCTAssertNoThrow(result = js_context.JSEvaluateScript("Ti.UI.createButton();"));
	XCTAssertTrue(result.IsObject());
	JSObject button = static_cast<JSObject>(result);
	XCTAssertTrue(button.HasProperty("title"));
}
