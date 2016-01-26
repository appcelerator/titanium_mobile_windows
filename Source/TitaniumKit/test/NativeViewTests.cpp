/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/API.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/UI/Button.hpp"
#include "Titanium/UI/Window.hpp"
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

	auto UI = js_context.CreateObject(JSExport<Titanium::UIModule>::Class());

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

	JSObject view = View.CallAsConstructor();
	
	XCTAssertTrue(view.HasProperty("accessibilityHidden"));
	XCTAssertTrue(view.HasProperty("accessibilityHint"));
	XCTAssertTrue(view.HasProperty("accessibilityLabel"));
	XCTAssertTrue(view.HasProperty("accessibilityValue"));
	XCTAssertTrue(view.HasProperty("anchorPoint"));
	XCTAssertTrue(view.HasProperty("animatedCenter"));
	XCTAssertTrue(view.HasProperty("backgroundDisabledColor"));
	XCTAssertTrue(view.HasProperty("backgroundDisabledImage"));
	XCTAssertTrue(view.HasProperty("backgroundFocusedColor"));
	XCTAssertTrue(view.HasProperty("backgroundFocusedImage"));
	XCTAssertTrue(view.HasProperty("backgroundGradient"));
	XCTAssertTrue(view.HasProperty("backgroundImage"));
	XCTAssertTrue(view.HasProperty("backgroundRepeat"));
	XCTAssertTrue(view.HasProperty("backgroundLeftCap"));
	XCTAssertTrue(view.HasProperty("backgroundSelectedColor"));
	XCTAssertTrue(view.HasProperty("backgroundSelectedImage"));
	XCTAssertTrue(view.HasProperty("backgroundTopCap"));
	XCTAssertTrue(view.HasProperty("borderColor"));
	XCTAssertTrue(view.HasProperty("borderRadius"));
	XCTAssertTrue(view.HasProperty("borderWidth"));
	XCTAssertTrue(view.HasProperty("clipMode"));
	XCTAssertTrue(view.HasProperty("enabled"));
	XCTAssertTrue(view.HasProperty("focusable"));
	XCTAssertTrue(view.HasProperty("opacity"));
	XCTAssertTrue(view.HasProperty("overrideCurrentAnimation"));
	XCTAssertTrue(view.HasProperty("pullBackgroundColor"));
	XCTAssertTrue(view.HasProperty("rect"));
	XCTAssertTrue(view.HasProperty("size"));
	XCTAssertTrue(view.HasProperty("softKeyboardOnFocus"));
	XCTAssertTrue(view.HasProperty("tintColor"));
	XCTAssertTrue(view.HasProperty("touchEnabled"));
	XCTAssertTrue(view.HasProperty("transform"));
	XCTAssertTrue(view.HasProperty("viewShadowRadius"));
	XCTAssertTrue(view.HasProperty("viewShadowColor"));
	XCTAssertTrue(view.HasProperty("viewShadowOffset"));
	XCTAssertTrue(view.HasProperty("visible"));
	XCTAssertTrue(view.HasProperty("horizontalWrap"));
	XCTAssertTrue(view.HasProperty("zIndex"));
	XCTAssertTrue(view.HasProperty("keepScreenOn"));
	XCTAssertTrue(view.HasProperty("children"));
	XCTAssertTrue(view.HasProperty("backgroundColor"));
	XCTAssertTrue(view.HasProperty("top"));
	XCTAssertTrue(view.HasProperty("left"));
	XCTAssertTrue(view.HasProperty("bottom"));
	XCTAssertTrue(view.HasProperty("center"));
	XCTAssertTrue(view.HasProperty("right"));
	XCTAssertTrue(view.HasProperty("width"));
	XCTAssertTrue(view.HasProperty("height"));
	XCTAssertTrue(view.HasProperty("layout"));

	XCTAssertTrue(view.HasProperty("animate"));
	XCTAssertTrue(view.HasProperty("remove"));
	XCTAssertTrue(view.HasProperty("removeAllChildren"));
	XCTAssertTrue(view.HasProperty("toImage"));
	XCTAssertTrue(view.HasProperty("convertPointToView"));
	XCTAssertTrue(view.HasProperty("add"));
	XCTAssertTrue(view.HasProperty("hide"));
	XCTAssertTrue(view.HasProperty("show"));
	XCTAssertTrue(view.HasProperty("getAccessibilityHidden"));
	XCTAssertTrue(view.HasProperty("setAccessibilityHidden"));
	XCTAssertTrue(view.HasProperty("getAccessibilityHint"));
	XCTAssertTrue(view.HasProperty("setAccessibilityHint"));
	XCTAssertTrue(view.HasProperty("getAccessibilityLabel"));
	XCTAssertTrue(view.HasProperty("setAccessibilityLabel"));
	XCTAssertTrue(view.HasProperty("getAccessibilityValue"));
	XCTAssertTrue(view.HasProperty("setAccessibilityValue"));
	XCTAssertTrue(view.HasProperty("getAnchorPoint"));
	XCTAssertTrue(view.HasProperty("setAnchorPoint"));
	XCTAssertTrue(view.HasProperty("getAnimatedCenter"));
	XCTAssertTrue(view.HasProperty("getBackgroundDisabledColor"));
	XCTAssertTrue(view.HasProperty("setBackgroundDisabledColor"));
	XCTAssertTrue(view.HasProperty("getBackgroundDisabledImage"));
	XCTAssertTrue(view.HasProperty("setBackgroundDisabledImage"));
	XCTAssertTrue(view.HasProperty("getBackgroundFocusedColor"));
	XCTAssertTrue(view.HasProperty("setBackgroundFocusedColor"));
	XCTAssertTrue(view.HasProperty("getBackgroundFocusedImage"));
	XCTAssertTrue(view.HasProperty("setBackgroundFocusedImage"));
	XCTAssertTrue(view.HasProperty("getBackgroundGradient"));
	XCTAssertTrue(view.HasProperty("setBackgroundGradient"));
	XCTAssertTrue(view.HasProperty("getBackgroundImage"));
	XCTAssertTrue(view.HasProperty("setBackgroundImage"));
	XCTAssertTrue(view.HasProperty("getBackgroundRepeat"));
	XCTAssertTrue(view.HasProperty("setBackgroundRepeat"));
	XCTAssertTrue(view.HasProperty("getBackgroundLeftCap"));
	XCTAssertTrue(view.HasProperty("setBackgroundLeftCap"));
	XCTAssertTrue(view.HasProperty("getBackgroundSelectedColor"));
	XCTAssertTrue(view.HasProperty("setBackgroundSelectedColor"));
	XCTAssertTrue(view.HasProperty("getBackgroundSelectedImage"));
	XCTAssertTrue(view.HasProperty("setBackgroundSelectedImage"));
	XCTAssertTrue(view.HasProperty("getBackgroundTopCap"));
	XCTAssertTrue(view.HasProperty("setBackgroundTopCap"));
	XCTAssertTrue(view.HasProperty("getBorderColor"));
	XCTAssertTrue(view.HasProperty("setBorderColor"));
	XCTAssertTrue(view.HasProperty("getBorderRadius"));
	XCTAssertTrue(view.HasProperty("setBorderRadius"));
	XCTAssertTrue(view.HasProperty("getBorderWidth"));
	XCTAssertTrue(view.HasProperty("setBorderWidth"));
	XCTAssertTrue(view.HasProperty("getClipMode"));
	XCTAssertTrue(view.HasProperty("setClipMode"));
	XCTAssertTrue(view.HasProperty("getEnabled"));
	XCTAssertTrue(view.HasProperty("setEnabled"));
	XCTAssertTrue(view.HasProperty("getFocusable"));
	XCTAssertTrue(view.HasProperty("setFocusable"));
	XCTAssertTrue(view.HasProperty("getOpacity"));
	XCTAssertTrue(view.HasProperty("setOpacity"));
	XCTAssertTrue(view.HasProperty("getOverrideCurrentAnimation"));
	XCTAssertTrue(view.HasProperty("setOverrideCurrentAnimation"));
	XCTAssertTrue(view.HasProperty("getPullBackgroundColor"));
	XCTAssertTrue(view.HasProperty("setPullBackgroundColor"));
	XCTAssertTrue(view.HasProperty("getRect"));
	XCTAssertTrue(view.HasProperty("getSize"));
	XCTAssertTrue(view.HasProperty("getSoftKeyboardOnFocus"));
	XCTAssertTrue(view.HasProperty("setSoftKeyboardOnFocus"));
	XCTAssertTrue(view.HasProperty("getTintColor"));
	XCTAssertTrue(view.HasProperty("setTintColor"));
	XCTAssertTrue(view.HasProperty("getTouchEnabled"));
	XCTAssertTrue(view.HasProperty("setTouchEnabled"));
	XCTAssertTrue(view.HasProperty("getTransform"));
	XCTAssertTrue(view.HasProperty("setTransform"));
	XCTAssertTrue(view.HasProperty("getViewShadowRadius"));
	XCTAssertTrue(view.HasProperty("setViewShadowRadius"));
	XCTAssertTrue(view.HasProperty("getViewShadowColor"));
	XCTAssertTrue(view.HasProperty("setViewShadowColor"));
	XCTAssertTrue(view.HasProperty("getViewShadowOffset"));
	XCTAssertTrue(view.HasProperty("setViewShadowOffset"));
	XCTAssertTrue(view.HasProperty("getVisible"));
	XCTAssertTrue(view.HasProperty("setVisible"));
	XCTAssertTrue(view.HasProperty("getHorizontalWrap"));
	XCTAssertTrue(view.HasProperty("setHorizontalWrap"));
	XCTAssertTrue(view.HasProperty("getZIndex"));
	XCTAssertTrue(view.HasProperty("setZIndex"));
	XCTAssertTrue(view.HasProperty("getKeepScreenOn"));
	XCTAssertTrue(view.HasProperty("setKeepScreenOn"));
	XCTAssertTrue(view.HasProperty("getChildren"));
	XCTAssertTrue(view.HasProperty("getBackgroundColor"));
	XCTAssertTrue(view.HasProperty("setBackgroundColor"));
	XCTAssertTrue(view.HasProperty("getTop"));
	XCTAssertTrue(view.HasProperty("setTop"));
	XCTAssertTrue(view.HasProperty("getLeft"));
	XCTAssertTrue(view.HasProperty("setLeft"));
	XCTAssertTrue(view.HasProperty("getBottom"));
	XCTAssertTrue(view.HasProperty("setBottom"));
	XCTAssertTrue(view.HasProperty("getCenter"));
	XCTAssertTrue(view.HasProperty("setCenter"));
	XCTAssertTrue(view.HasProperty("getRight"));
	XCTAssertTrue(view.HasProperty("setRight"));
	XCTAssertTrue(view.HasProperty("getWidth"));
	XCTAssertTrue(view.HasProperty("setWidth"));
	XCTAssertTrue(view.HasProperty("getHeight"));
	XCTAssertTrue(view.HasProperty("setHeight"));
	XCTAssertTrue(view.HasProperty("getLayout"));
	XCTAssertTrue(view.HasProperty("setLayout"));

	XCTAssertTrue(view.HasProperty("insertAt"));
	XCTAssertTrue(view.HasProperty("replaceAt"));

	XCTAssertTrue(view.HasProperty("NativeViewLayoutDelegate_called"));
	XCTAssertTrue(static_cast<bool>(view.GetProperty("NativeViewLayoutDelegate_called")));

	UI.SetProperty("Window", js_context.CreateObject(JSExport<Titanium::UI::Window>::Class()));
	XCTAssertTrue(UI.HasProperty("Window"));

	UI.SetProperty("Button", js_context.CreateObject(JSExport<Titanium::UI::Button>::Class()));
	XCTAssertTrue(UI.HasProperty("Button"));

}
