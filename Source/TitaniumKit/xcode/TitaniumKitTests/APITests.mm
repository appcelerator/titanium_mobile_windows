/**
 * Titanium
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/Titanium.hpp"
#include "NativeAPIExample.hpp"
#import <XCTest/XCTest.h>

using namespace HAL;

@interface APITests : XCTestCase
@end

@implementation APITests {
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

- (void)testAPI {
  TITANIUM_LOG_DEBUG("  JSContext js_context   = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());");
  JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
  TITANIUM_LOG_DEBUG("  auto global_object     = js_context.get_global_object();");
  auto global_object = js_context.get_global_object();

  TITANIUM_LOG_DEBUG("  XCTAssertFalse(global_object.HasProperty(\"Titanium\"));");
  //XCTAssertFalse(global_object.HasProperty("Titanium"));
  bool has_property = global_object.HasProperty("Titanium");
  XCTAssertFalse(has_property);

  TITANIUM_LOG_DEBUG("  auto Titanium = js_context.CreateObject();");
  auto Titanium = js_context.CreateObject();
  TITANIUM_LOG_DEBUG("  global_object.SetProperty(\"Titanium\", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});");
  global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

  TITANIUM_LOG_DEBUG("  XCTAssertTrue(global_object.HasProperty(\"Titanium\"));");
  //XCTAssertTrue(global_object.HasProperty("Titanium"));
  has_property = global_object.HasProperty("Titanium");
  XCTAssertTrue(has_property);

  // Make the alias "Ti" for the "Titanium" property.
  TITANIUM_LOG_DEBUG("  XCTAssertFalse(global_object.HasProperty(\"Ti\"));");
  XCTAssertFalse(global_object.HasProperty("Ti"));
  TITANIUM_LOG_DEBUG("  global_object.SetProperty(\"Ti\", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});");
  global_object.SetProperty("Ti", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  TITANIUM_LOG_DEBUG("  XCTAssertTrue(global_object.HasProperty(\"Ti\"));");
  XCTAssertTrue(global_object.HasProperty("Ti"));

  TITANIUM_LOG_DEBUG("XCTAssertFalse(Titanium.HasProperty(\"API\"));");
  XCTAssertFalse(Titanium.HasProperty("API"));
  TITANIUM_LOG_DEBUG("  auto API = js_context.CreateObject(JSExport<NativeAPIExample>::Class());");
  auto API = js_context.CreateObject<NativeAPIExample>();
  TITANIUM_LOG_DEBUG("Titanium.SetProperty(\"API\", API, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});");
  Titanium.SetProperty("API", API, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  TITANIUM_LOG_DEBUG("XCTAssertTrue(Titanium.HasProperty(\"API\"));");
  XCTAssertTrue(Titanium.HasProperty("API"));

  TITANIUM_LOG_DEBUG("  auto api_ptr = API.GetPrivate<NativeAPIExample>();");
  auto api_ptr = API.GetPrivate<NativeAPIExample>();
  XCTAssertNotEqual(nullptr, api_ptr);
  /*
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
*/
  //js_context.JSEvaluateScript("var a = {}; a.xtrace = Ti.API.trace; a.xtrace('Hello, world');");
  TITANIUM_LOG_DEBUG("  js_context.JSEvaluateScript(\"var a = {};\");");
  js_context.JSEvaluateScript("var a = {};");
  TITANIUM_LOG_DEBUG("  js_context.JSEvaluateScript(\"a.xtrace = Ti.API.trace;\");");
  js_context.JSEvaluateScript("a.xtrace = Ti.API.trace;");
  TITANIUM_LOG_DEBUG("  js_context.JSEvaluateScript(\"a.xtrace('Hello, world');\");");
  //js_context.JSEvaluateScript("a.xtrace('Hello, world');");
}

@end
