/**
 * TitaniumKit
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeGlobalObjectExample.hpp"
#include "NativeAPIExample.hpp"
#include "NativeWindowExample.hpp"
#include "NativeButtonExample.hpp"
#include "NativePlatformExample.hpp"
#include "NativeAccelerometerExample.hpp"
#include "NativeGestureExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual    ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue     ASSERT_TRUE
#define XCTAssertFalse    ASSERT_FALSE

using namespace JavaScriptCoreCPP;

TEST(ApplicationTests, build_and_run) {
  std::string app_js = R"js(
  'use strict';
  
  var view = Ti.UI.createView({
  bottom: 50,
  right: 50,
  width: 300,
  height: Ti.UI.SIZE
  });
  
  var button = Ti.UI.createButton({
  title: 'Neeraj Says...',
  top: 20,
  bottom: 20,
  width: 200,
  height: Ti.UI.SIZE
  });
  
  button.addEventListener('click', function(e) {
    Ti.API.warn('Goals without a timeline are just a dream.');
  });
  
  view.add(button);
  
  var window = Ti.UI.createWindow();
  window.add(view);
  
  window.open();
  
  Ti.API.info(Ti.Platform.osname);
  Ti.API.info('ng.js running...');
  )js";
  
  Titanium::Application app = Titanium::ApplicationBuilder(std::make_shared<JSClass>(JSExport<NativeGlobalObjectExample>::Class()))
  .APIClass(std::make_shared<JSClass>(JSExport<NativeAPIExample>::Class()))
  .WindowClass(std::make_shared<JSClass>(JSExport<NativeWindowExample>::Class()))
  .ButtonClass(std::make_shared<JSClass>(JSExport<NativeButtonExample>::Class()))
  .PlatformClass(std::make_shared<JSClass>(JSExport<NativePlatformExample>::Class()))
  .AccelerometerClass(std::make_shared<JSClass>(JSExport<NativeAccelerometerExample>::Class()))
  .GestureClass(std::make_shared<JSClass>(JSExport<NativeGestureExample>::Class()))
  .build();
  
  JSValue reslut = app.Run("app.js");
}
