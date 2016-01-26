/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/UIModule.hpp"
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
	auto UI = js_context.CreateObject(JSExport<Titanium::UIModule>::Class());

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

	auto button = Button.CallAsConstructor();
	XCTAssertTrue(button.HasProperty("title"));

	global_object.SetProperty("button", button);

	auto json_result = js_context.JSEvaluateScript("JSON.stringify(button);");
	XCTAssertTrue(static_cast<std::string>(json_result).find("\"textAlign\":") != std::string::npos);
}
