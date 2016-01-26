/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/UIModule.hpp"
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

	auto WebView = js_context.CreateObject(JSExport<NativeWebViewExample>::Class());
	auto webview_ptr = WebView.GetPrivate<NativeWebViewExample>();
	XCTAssertNotEqual(nullptr, webview_ptr);

	JSObject webview = WebView.CallAsConstructor();
	XCTAssertTrue(webview.HasProperty("canGoBack"));

	global_object.SetProperty("webview", webview);
	auto json_result = js_context.JSEvaluateScript("JSON.stringify(webview);");
	XCTAssertTrue(static_cast<std::string>(json_result).find("\"url\":") != std::string::npos);
}
