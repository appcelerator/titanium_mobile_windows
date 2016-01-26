/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/ActivityIndicator.hpp"
#include "Titanium/UI/ActivityIndicatorStyle.hpp"
#include "Titanium/UI/AttributedString.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class UITests : public testing::Test
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

TEST_F(UITests, properties)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto UI = js_context.CreateObject(JSExport<Titanium::UIModule>::Class());

	// Inherited from Titanium::Module.
	XCTAssertTrue(UI.HasProperty("addEventListener"));
	XCTAssertTrue(UI.HasProperty("applyProperties"));
	XCTAssertTrue(UI.HasProperty("fireEvent"));

	XCTAssertTrue(UI.HasProperty("createView"));
	XCTAssertTrue(UI.HasProperty("createWindow"));
	XCTAssertTrue(UI.HasProperty("createButton"));
	XCTAssertTrue(UI.HasProperty("createAttributedString"));
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
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_FONT"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_FOREGROUND_COLOR"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_BACKGROUND_COLOR"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_STRIKETHROUGH_STYLE"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINES_STYLE"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINK"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_COLOR"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_KERN"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_STROKE_COLOR"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_STROKE_WIDTH"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_SHADOW"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_WRITING_DIRECTION"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_TEXT_EFFECT"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_BASELINE_OFFSET"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_STRIKETHROUGH_COLOR"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_OBLIQUENESS"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_EXPANSION"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINE_BREAK"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_STYLE_NONE"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_STYLE_SINGLE"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_STYLE_THICK"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_STYLE_DOUBLE"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_PATTERN_SOLID"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_PATTERN_DOT"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_PATTERN_DASH"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT_DOT"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_UNDERLINE_BY_WORD"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_WRITING_DIRECTION_EMBEDDING"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_WRITING_DIRECTION_OVERRIDE"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_WRITING_DIRECTION_NATURAL"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_WRITING_DIRECTION_LEFT_TO_RIGHT"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_WRITING_DIRECTION_RIGHT_TO_LEFT"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LETTERPRESS_STYLE"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINE_BREAK_BY_WORD_WRAPPING"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINE_BREAK_BY_CHAR_WRAPPING"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINE_BREAK_BY_CLIPPING"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_HEAD"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_TAIL"));
	XCTAssertTrue(UI.HasProperty("ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_MIDDLE"));
}

TEST_F(UITests, Attribute)
{
	// Pickup attribute styles randomly and check if it properly finds styles
	auto styles_num = 
		Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_SINGLE) |
		Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_THICK) |
		Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT) |
		Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_RIGHT_TO_LEFT) |
		Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_CLIPPING);
	auto styles = Titanium::UI::Constants::to_ATTRIBUTE_STYLE(styles_num);

	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_SINGLE) != styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_THICK) != styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT) != styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_RIGHT_TO_LEFT) != styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_CLIPPING) != styles.end());

	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_CHAR_WRAPPING) == styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_BY_WORD) == styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_NONE) == styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_EMBEDDING) == styles.end());
	XCTAssertTrue(styles.find(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_MIDDLE) == styles.end());
}

TEST_F(UITests, AttributedString)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());

	auto global_object = js_context.get_global_object();
	auto Titanium = js_context.CreateObject();
	global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	auto UI = js_context.CreateObject(JSExport<Titanium::UIModule>::Class());
	auto UI_ptr = UI.GetPrivate<Titanium::UIModule>()->AttributedStringClass(JSExport<Titanium::UI::AttributedString>::Class());
	Titanium.SetProperty("UI", UI);

	std::string script = R"js(
	var text =  'Bacon ipsum dolor Appcelerator Titanium rocks!';
	var attr = Titanium.UI.createAttributedString({
	    text: text,
	    attributes: [
	        {
	            type: Titanium.UI.ATTRIBUTE_UNDERLINES_STYLE,
	            range: [0, text.length]
	        },
	        {
	            type: Titanium.UI.ATTRIBUTE_BACKGROUND_COLOR,
	            value: 'red',
	            range: [text.indexOf('Appcelerator'), ('Appcelerator').length]
	        },
	    ]
		});
	)js";

	XCTAssertNoThrow(js_context.JSEvaluateScript(script));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.text == text;")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes.length == 2;")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes[0].type == Titanium.UI.ATTRIBUTE_UNDERLINES_STYLE;")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes[0].range[0] == 0;")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes[0].range[1] == text.length;")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes[1].type  == Titanium.UI.ATTRIBUTE_BACKGROUND_COLOR;")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes[1].value = 'red';")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes[1].range[0] == text.indexOf('Appcelerator');")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("attr.attributes[1].range[1] == ('Appcelerator').length;")));
}

TEST_F(UITests, ActivityIndicator)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());

	auto global_object = js_context.get_global_object();
	auto Titanium = js_context.CreateObject();
	global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	auto UI = js_context.CreateObject(JSExport<Titanium::UIModule>::Class());
	auto UI_ptr = UI.GetPrivate<Titanium::UIModule>()->
		ActivityIndicatorClass(JSExport<Titanium::UI::ActivityIndicator>::Class()).
		ActivityIndicatorStyleClass(JSExport<Titanium::UI::ActivityIndicatorStyle>::Class());
	Titanium.SetProperty("UI", UI);

	XCTAssertTrue(UI.HasProperty("ActivityIndicator"));
	XCTAssertTrue(UI.HasProperty("ActivityIndicatorStyle"));

	auto ActivityIndicator = static_cast<JSObject>(UI.GetProperty("ActivityIndicator"));
	auto ActivityIndicatorStyle = static_cast<JSObject>(UI.GetProperty("ActivityIndicatorStyle"));

	XCTAssertTrue(ActivityIndicatorStyle.HasProperty("BIG"));
	XCTAssertTrue(ActivityIndicatorStyle.HasProperty("BIG_DARK"));
	XCTAssertTrue(ActivityIndicatorStyle.HasProperty("DARK"));
	XCTAssertTrue(ActivityIndicatorStyle.HasProperty("PLAIN"));

	XCTAssertTrue(ActivityIndicator.HasProperty("color"));
	XCTAssertTrue(ActivityIndicator.HasProperty("font"));
	XCTAssertTrue(ActivityIndicator.HasProperty("message"));
	XCTAssertTrue(ActivityIndicator.HasProperty("messageid"));
	XCTAssertTrue(ActivityIndicator.HasProperty("style"));

	XCTAssertTrue(UI.HasProperty("createActivityIndicator"));

	XCTAssertNoThrow(js_context.JSEvaluateScript("var indicator = Titanium.UI.createActivityIndicator();"));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("indicator.style == Titanium.UI.ActivityIndicatorStyle.PLAIN")));

	// make sure JSON.stringify returns ActivityIndicatorStyle-specific property
	auto json_result = js_context.JSEvaluateScript("JSON.stringify(indicator);");
	XCTAssertTrue(static_cast<std::string>(json_result).find("\"indicatorColor\":\"\"") != std::string::npos);

}
