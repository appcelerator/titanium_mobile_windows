/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual    ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue     ASSERT_TRUE
#define XCTAssertFalse    ASSERT_FALSE

using namespace Titanium;
using namespace HAL;

class UITests : public testing::Test {
 protected:
  virtual void SetUp() {
  }
  
  virtual void TearDown() {
  }
  
  JSContextGroup js_context_group;
};

TEST_F(UITests, properties) {
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

  XCTAssertTrue(UI.HasProperty("createView"));
  XCTAssertTrue(UI.HasProperty("createWindow"));
  XCTAssertTrue(UI.HasProperty("createButton"));
  XCTAssertTrue(UI.HasProperty("ANIMATION_CURVE_EASE_IN"));
  XCTAssertTrue(UI.HasProperty("ANIMATION_CURVE_EASE_IN_OUT"));
  XCTAssertTrue(UI.HasProperty("ANIMATION_CURVE_EASE_OUT"));
  XCTAssertTrue(UI.HasProperty("ANIMATION_CURVE_LINEAR"));
  XCTAssertTrue(UI.HasProperty("AUTOLINK_ALL"));
  XCTAssertTrue(UI.HasProperty("AUTOLINK_CALENDAR"));
  XCTAssertTrue(UI.HasProperty("AUTOLINK_EMAIL_ADDRESSES"));
  XCTAssertTrue(UI.HasProperty("AUTOLINK_MAP_ADDRESSES"));
  XCTAssertTrue(UI.HasProperty("AUTOLINK_NONE"));
  XCTAssertTrue(UI.HasProperty("AUTOLINK_PHONE_NUMBERS"));
  XCTAssertTrue(UI.HasProperty("AUTOLINK_URLS"));
  XCTAssertTrue(UI.HasProperty("EXTEND_EDGE_ALL"));
  XCTAssertTrue(UI.HasProperty("EXTEND_EDGE_BOTTOM"));
  XCTAssertTrue(UI.HasProperty("EXTEND_EDGE_LEFT"));
  XCTAssertTrue(UI.HasProperty("EXTEND_EDGE_NONE"));
  XCTAssertTrue(UI.HasProperty("EXTEND_EDGE_RIGHT"));
  XCTAssertTrue(UI.HasProperty("EXTEND_EDGE_TOP"));
  XCTAssertTrue(UI.HasProperty("FACE_DOWN"));
  XCTAssertTrue(UI.HasProperty("FACE_UP"));
  XCTAssertTrue(UI.HasProperty("FILL"));
  XCTAssertTrue(UI.HasProperty("INHERIT"));
  XCTAssertTrue(UI.HasProperty("INPUT_BORDERSTYLE_BEZEL"));
  XCTAssertTrue(UI.HasProperty("INPUT_BORDERSTYLE_LINE"));
  XCTAssertTrue(UI.HasProperty("INPUT_BORDERSTYLE_NONE"));
  XCTAssertTrue(UI.HasProperty("INPUT_BORDERSTYLE_ROUNDED"));
  XCTAssertTrue(UI.HasProperty("INPUT_BUTTONMODE_ALWAYS"));
  XCTAssertTrue(UI.HasProperty("INPUT_BUTTONMODE_NEVER"));
  XCTAssertTrue(UI.HasProperty("INPUT_BUTTONMODE_ONBLUR"));
  XCTAssertTrue(UI.HasProperty("INPUT_BUTTONMODE_ONFOCUS"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_APPEARANCE_ALERT"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_APPEARANCE_DEFAULT"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_ASCII"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_DECIMAL_PAD"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_DEFAULT"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_EMAIL"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_NAMEPHONE_PAD"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_NUMBERS_PUNCTUATION"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_NUMBER_PAD"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_PHONE_PAD"));
  XCTAssertTrue(UI.HasProperty("KEYBOARD_URL"));
  XCTAssertTrue(UI.HasProperty("LANDSCAPE_LEFT"));
  XCTAssertTrue(UI.HasProperty("LANDSCAPE_RIGHT"));
  XCTAssertTrue(UI.HasProperty("LIST_ACCESSORY_TYPE_CHECKMARK"));
  XCTAssertTrue(UI.HasProperty("LIST_ACCESSORY_TYPE_DETAIL"));
  XCTAssertTrue(UI.HasProperty("LIST_ACCESSORY_TYPE_DISCLOSURE"));
  XCTAssertTrue(UI.HasProperty("LIST_ACCESSORY_TYPE_NONE"));
  XCTAssertTrue(UI.HasProperty("LIST_ITEM_TEMPLATE_CONTACTS"));
  XCTAssertTrue(UI.HasProperty("LIST_ITEM_TEMPLATE_DEFAULT"));
  XCTAssertTrue(UI.HasProperty("LIST_ITEM_TEMPLATE_SETTINGS"));
  XCTAssertTrue(UI.HasProperty("LIST_ITEM_TEMPLATE_SUBTITLE"));
  XCTAssertTrue(UI.HasProperty("NOTIFICATION_DURATION_LONG"));
  XCTAssertTrue(UI.HasProperty("NOTIFICATION_DURATION_SHORT"));
  XCTAssertTrue(UI.HasProperty("PICKER_TYPE_COUNT_DOWN_TIMER"));
  XCTAssertTrue(UI.HasProperty("PICKER_TYPE_DATE"));
  XCTAssertTrue(UI.HasProperty("PICKER_TYPE_DATE_AND_TIME"));
  XCTAssertTrue(UI.HasProperty("PICKER_TYPE_PLAIN"));
  XCTAssertTrue(UI.HasProperty("PICKER_TYPE_TIME"));
  XCTAssertTrue(UI.HasProperty("PORTRAIT"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_DEFAULT"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_DONE"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_EMERGENCY_CALL"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_GO"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_GOOGLE"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_JOIN"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_NEXT"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_ROUTE"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_SEARCH"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_SEND"));
  XCTAssertTrue(UI.HasProperty("RETURNKEY_YAHOO"));
  XCTAssertTrue(UI.HasProperty("SIZE"));
  XCTAssertTrue(UI.HasProperty("TEXT_ALIGNMENT_CENTER"));
  XCTAssertTrue(UI.HasProperty("TEXT_ALIGNMENT_LEFT"));
  XCTAssertTrue(UI.HasProperty("TEXT_ALIGNMENT_RIGHT"));
  XCTAssertTrue(UI.HasProperty("TEXT_AUTOCAPITALIZATION_ALL"));
  XCTAssertTrue(UI.HasProperty("TEXT_AUTOCAPITALIZATION_NONE"));
  XCTAssertTrue(UI.HasProperty("TEXT_AUTOCAPITALIZATION_SENTENCES"));
  XCTAssertTrue(UI.HasProperty("TEXT_AUTOCAPITALIZATION_WORDS"));
  XCTAssertTrue(UI.HasProperty("TEXT_STYLE_BODY"));
  XCTAssertTrue(UI.HasProperty("TEXT_STYLE_CAPTION1"));
  XCTAssertTrue(UI.HasProperty("TEXT_STYLE_CAPTION2"));
  XCTAssertTrue(UI.HasProperty("TEXT_STYLE_FOOTNOTE"));
  XCTAssertTrue(UI.HasProperty("TEXT_STYLE_HEADLINE"));
  XCTAssertTrue(UI.HasProperty("TEXT_STYLE_SUBHEADLINE"));
  XCTAssertTrue(UI.HasProperty("TEXT_VERTICAL_ALIGNMENT_BOTTOM"));
  XCTAssertTrue(UI.HasProperty("TEXT_VERTICAL_ALIGNMENT_CENTER"));
  XCTAssertTrue(UI.HasProperty("TEXT_VERTICAL_ALIGNMENT_TOP"));
  XCTAssertTrue(UI.HasProperty("UNIT_CM"));
  XCTAssertTrue(UI.HasProperty("UNIT_DIP"));
  XCTAssertTrue(UI.HasProperty("UNIT_IN"));
  XCTAssertTrue(UI.HasProperty("UNIT_MM"));
  XCTAssertTrue(UI.HasProperty("UNIT_PX"));
  XCTAssertTrue(UI.HasProperty("UNKNOWN"));
  XCTAssertTrue(UI.HasProperty("UPSIDE_PORTRAIT"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_AUTHENTICATION"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_BAD_URL"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_CONNECT"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_FILE"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_FILE_NOT_FOUND"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_HOST_LOOKUP"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_REDIRECT_LOOP"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_SSL_FAILED"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_TIMEOUT"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_UNKNOWN"));
  XCTAssertTrue(UI.HasProperty("URL_ERROR_UNSUPPORTED_SCHEME"));
  
}
