/**
 * Titanium
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeAPIExample.hpp"
#import <XCTest/XCTest.h>

using namespace JavaScriptCoreCPP;

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
  JSContext js_context   = js_context_group.CreateContext();
  auto global_object     = js_context.get_global_object();
    
  auto custom_global_object = js_context.CreateObject(JSExport<Titanium::GlobalObject>::Class());
  for (const auto& property_name : static_cast<std::vector<JSString>>(custom_global_object.GetPropertyNames())) {
    global_object.SetProperty(property_name, custom_global_object.GetProperty(property_name));
  }

  XCTAssertFalse(global_object.HasProperty("Titanium"));
  auto Titanium = js_context.CreateObject();
  global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(global_object.HasProperty("Titanium"));
  
  // Make the alias "Ti" for the "Titanium" property.
  XCTAssertFalse(global_object.HasProperty("Ti"));
  global_object.SetProperty("Ti", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(global_object.HasProperty("Ti"));

  XCTAssertFalse(Titanium.HasProperty("API"));
  auto API = js_context.CreateObject(JSExport<NativeAPIExample>::Class());
  Titanium.SetProperty("API", API, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(Titanium.HasProperty("API"));
  
  auto api_ptr = API.GetPrivate<NativeAPIExample>();
  XCTAssertNotEqual(nullptr, api_ptr);
  
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
}

@end
