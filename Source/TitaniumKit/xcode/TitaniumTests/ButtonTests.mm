/**
 * Titanium
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeButtonExample.hpp"
#import <XCTest/XCTest.h>

using namespace JavaScriptCoreCPP;

@interface ButtonTests : XCTestCase
@end

@implementation ButtonTests {
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

- (void)testButton {
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
  JSObject button = result;
  XCTAssertTrue(button.HasProperty("title"));
}

@end
