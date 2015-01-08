/**
 * Titanium
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeGlobalObjectExample.hpp"
#import <XCTest/XCTest.h>

using namespace HAL;

@interface GlobalObjectTests : XCTestCase
@end

@implementation GlobalObjectTests {
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

- (void)testGlobalObject {
  JSContext js_context = js_context_group.CreateContext(JSExport<NativeGlobalObjectExample>::Class());
  auto global_object = js_context.get_global_object();

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

  std::string app1_js = R"js(
  "use strict";
  var hello = require("hello");
  hello('world');
  )js";

  std::string hello1_js = R"js(
  "use strict";
  exports = sayHello;
  function sayHello(name) {
    return 'Hello, ' + name;
  }
  )js";

  auto global_object_ptr = global_object.GetPrivate<NativeGlobalObjectExample>();
  XCTAssertNotEqual(nullptr, global_object_ptr);

  JSValue result = js_context.CreateNull();

  global_object_ptr->set_example_resource(hello1_js);
  XCTAssertNoThrow(result = js_context.JSEvaluateScript(app1_js));

  std::string app2_js = R"js(
  "use strict";
  var hello = require("hello");
  hello.sayHello('world');
  )js";

  std::string hello2_js = R"js(
  "use strict";
  exports.sayHello = sayHello;
  function sayHello(name) {
    return 'Hello, ' + name;
  }
  )js";

  global_object_ptr->set_example_resource(hello2_js);
  XCTAssertNoThrow(result = js_context.JSEvaluateScript(app2_js));
}

@end
