/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeViewExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class ViewTests : public testing::Test
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

TEST_F(ViewTests, basic_functionality)
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
	auto API = js_context.CreateObject(JSExport<Titanium::API>::Class());
	Titanium.SetProperty("API", API, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("API"));

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
	XCTAssertTrue(UI.HasProperty("SIZE"));

	auto View = js_context.CreateObject(JSExport<NativeViewExample>::Class());
	auto view_ptr = View.GetPrivate<NativeViewExample>();
	XCTAssertNotEqual(nullptr, view_ptr);

	UI.SetProperty("View", View);
	XCTAssertTrue(UI.HasProperty("View"));

	auto result = js_context.JSEvaluateScript("Ti.UI.createView();");
	XCTAssertTrue(result.IsObject());
	JSObject view = static_cast<JSObject>(result);
	XCTAssertTrue(view.HasProperty("add"));

	UI.SetProperty("Window", js_context.CreateObject(JSExport<Titanium::UI::Window>::Class()));
	XCTAssertTrue(UI.HasProperty("Window"));

	UI.SetProperty("Button", js_context.CreateObject(JSExport<Titanium::UI::Button>::Class()));
	XCTAssertTrue(UI.HasProperty("Button"));

	std::string app_js = R"js(
  'use strict';
  
  var view = Ti.UI.createView({
  bottom: 50,
  right: 50,
  width: 300,
  height: Ti.UI.SIZE
  });
  
  var button = Ti.UI.createButton({
  top: 20,
  bottom: 20,
  width: 200,
  height: Ti.UI.SIZE
  });
  
  button.title = 'Neeraj Says...';
  
  button.addEventListener('click', function(e) {
    Ti.API.warn('Goals without a timeline are just a dream.');
  });
  
  view.add(button);
  
  var window = Ti.UI.createWindow();
  window.add(view);
  
  window.open();
  
  Ti.API.info('ng.js running...');
  )js";

	XCTAssertNoThrow(result = js_context.JSEvaluateScript(app_js));
}
