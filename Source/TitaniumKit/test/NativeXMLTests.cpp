/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeXMLExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual    ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue     ASSERT_TRUE
#define XCTAssertFalse    ASSERT_FALSE
#define XCTAssertNoThrow  ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class XMLTests : public testing::Test {
 protected:
  virtual void SetUp() {
  }
  
  virtual void TearDown() {
  }
  
  JSContextGroup js_context_group;
};

TEST_F(XMLTests, logging) {
  JSContext js_context   = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
  auto global_object     = js_context.get_global_object();

  XCTAssertFalse(global_object.HasProperty("Titanium"));
  auto Titanium = js_context.CreateObject();
  global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(global_object.HasProperty("Titanium"));
  
  // Make the alias "Ti" for the "Titanium" property.
  XCTAssertFalse(global_object.HasProperty("Ti"));
  global_object.SetProperty("Ti", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(global_object.HasProperty("Ti"));

  XCTAssertFalse(Titanium.HasProperty("XML"));
  auto XML = js_context.CreateObject(JSExport<NativeXMLExample>::Class());
  Titanium.SetProperty("XML", XML, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
  XCTAssertTrue(Titanium.HasProperty("XML"));
  
  auto XML_ptr = XML.GetPrivate<NativeXMLExample>();
  XCTAssertNotEqual(nullptr, XML_ptr);
  
  XCTAssertTrue(XML.HasProperty("addEventListener"));
  XCTAssertTrue(XML.HasProperty("parseString"));
  XCTAssertTrue(XML.HasProperty("serializeToString"));
}
