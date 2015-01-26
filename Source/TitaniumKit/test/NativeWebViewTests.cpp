/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeWebViewExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class WebViewTests : public testing::Test
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

TEST_F(WebViewTests, basic_functionality)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	XCTAssertFalse(global_object.HasProperty("Titanium"));
	auto Titanium = js_context.CreateObject();
	global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(global_object.HasProperty("Titanium"));

	XCTAssertFalse(global_object.HasProperty("Ti"));
	global_object.SetProperty("Ti", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(global_object.HasProperty("Ti"));

	XCTAssertFalse(Titanium.HasProperty("UI"));
	auto UI = js_context.CreateObject(JSExport<Titanium::UIModule>::Class());
	Titanium.SetProperty("UI", UI, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("UI"));

	XCTAssertTrue(UI.HasProperty("createWebView"));

	auto WebView = js_context.CreateObject(JSExport<NativeWebViewExample>::Class());
	auto webview_ptr = WebView.GetPrivate<NativeWebViewExample>();
	XCTAssertNotEqual(nullptr, webview_ptr);

	UI.SetProperty("WebView", WebView);
	XCTAssertTrue(UI.HasProperty("WebView"));

	auto result = js_context.JSEvaluateScript("Ti.UI.createWebView();");
	XCTAssertTrue(result.IsObject());
	JSObject webview = static_cast<JSObject>(result);
	XCTAssertTrue(webview.HasProperty("canGoBack"));

}
