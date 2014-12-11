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
#include "gtest/gtest.h"

#define XCTAssertEqual    ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue     ASSERT_TRUE
#define XCTAssertFalse    ASSERT_FALSE
#define XCTAssertNoThrow  ASSERT_NO_THROW

using namespace JavaScriptCoreCPP;

class GlobalObjectTests : public testing::Test {
 protected:
  virtual void SetUp() {
  }
  
  virtual void TearDown() {
  }
  
  JSContextGroup js_context_group;
};


TEST_F(GlobalObjectTests, require) {
  JSContext js_context   = js_context_group.CreateContext();
  auto global_object     = js_context.get_global_object();
    
  auto custom_global_object = js_context.CreateObject(JSExport<NativeGlobalObjectExample>::Class());
  for (const auto& property_name : static_cast<std::vector<JSString>>(custom_global_object.GetPropertyNames())) {
    global_object.SetProperty(property_name, custom_global_object.GetProperty(property_name));
  }

  auto foo = js_context.CreateObject();
  
  XCTAssertFalse(foo.HasProperty("bar"));
  auto bar = js_context.CreateObject();
  foo.SetProperty("bar", bar, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(foo.HasProperty("bar"));

  XCTAssertFalse(bar.HasProperty("baz"));
  auto baz = js_context.CreateObject();
  bar.SetProperty("baz", baz, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(bar.HasProperty("baz"));

  XCTAssertFalse(baz.HasProperty("number"));
  baz.SetProperty("number", js_context.CreateNumber(42), {JSPropertyAttribute::DontDelete});
  XCTAssertTrue(baz.HasProperty("number"));
  
  XCTAssertFalse(global_object.HasProperty("foo"));
  global_object.SetProperty("foo", foo, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(global_object.HasProperty("foo"));
  
  auto number = js_context.JSEvaluateScript("foo.bar.baz.number;");
  XCTAssertEqual(42, static_cast<uint32_t>(number));
  //std::clog << "MDL: number = " << number << std::endl;
  
  number = js_context.JSEvaluateScript("foo.bar.baz.number = 24;");
  XCTAssertEqual(24, static_cast<uint32_t>(number));

  for (const auto& property_name : static_cast<std::vector<JSString>>(global_object.GetPropertyNames())) {
    std::clog << "MDL: property_name = " << property_name << std::endl;
  }
  
  JSString app_js = R"js(
  "use strict";
  var hello = require("hello");
  //hello.sayHello('world');
  hello('world');
  )js";
  
  JSString hello1_js = R"js(
  "use strict";
  exports = sayHello;
  function sayHello(name) {
    return 'Hello, ' + name;
  }
  )js";
  
  auto global_object_ptr = custom_global_object.GetPrivate<NativeGlobalObjectExample>();
  XCTAssertNotEqual(nullptr, global_object_ptr);
  
  JSValue result = js_context.CreateNull();
  
  global_object_ptr -> set_example_resource(hello1_js);
  XCTAssertNoThrow(result = js_context.JSEvaluateScript(app_js));

  JSString hello2_js = R"js(
  "use strict";
  exports.sayHello = sayHello;
  function sayHello(name) {
    return 'Hello, ' + name;
  }
  )js";
  
  global_object_ptr -> set_example_resource(hello2_js);
  XCTAssertNoThrow(result = js_context.JSEvaluateScript(app_js));
}

TEST_F(GlobalObjectTests, timeout) {
}

TEST_F(GlobalObjectTests, interval) {
}
