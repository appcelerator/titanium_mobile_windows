/**
 * Titanium
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#import <XCTest/XCTest.h>

using namespace HAL;

@interface UITests : XCTestCase
@end

@implementation UITests {
  JSContextGroup js_context_group;
}

- (void)setUp {
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
  // Put teardown code here. This method is called after the invocation of each test method in the class.
  [super tearDown];
}

- (void)testUI {
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

  XCTAssertTrue(UI.HasProperty("createView"));
  XCTAssertTrue(UI.HasProperty("createWindow"));
  XCTAssertTrue(UI.HasProperty("createButton"));
}

@end
