/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeListViewExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class ListViewTests : public testing::Test
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

TEST_F(ListViewTests, basic_functionality)
{
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

	XCTAssertTrue(UI.HasProperty("createListView"));
	XCTAssertTrue(UI.HasProperty("createListSection"));
	XCTAssertTrue(UI.HasProperty("createListItem"));

	auto View = js_context.CreateObject(JSExport<NativeListViewExample>::Class());
	auto view_ptr = View.GetPrivate<NativeListViewExample>();
	XCTAssertNotEqual(nullptr, view_ptr);

	UI.SetProperty("ListView", View);
	UI.SetProperty("ListSection", js_context.CreateObject(JSExport<Titanium::UI::ListSection>::Class()));
	UI.SetProperty("ListItem", js_context.CreateObject(JSExport<Titanium::UI::ListItem>::Class()));

	XCTAssertTrue(UI.HasProperty("ListView"));
	XCTAssertTrue(UI.HasProperty("ListSection"));
	XCTAssertTrue(UI.HasProperty("ListItem"));

	JSValue result = js_context.CreateNull();
	XCTAssertNoThrow(result = js_context.JSEvaluateScript("Ti.UI.createListView();"));
	XCTAssertTrue(result.IsObject());
	JSObject view = static_cast<JSObject>(result);

	XCTAssertTrue(view.HasProperty("templates"));
	XCTAssertTrue(view.HasProperty("sections"));
	XCTAssertTrue(view.HasProperty("footerTitle"));
	XCTAssertTrue(view.HasProperty("headerTitle"));
	XCTAssertTrue(view.HasProperty("searchText"));
	XCTAssertTrue(view.HasProperty("footerView"));
	XCTAssertTrue(view.HasProperty("headerView"));
	XCTAssertTrue(view.HasProperty("searchView"));
	XCTAssertTrue(view.HasProperty("sectionCount"));
	XCTAssertTrue(view.HasProperty("caseInsensitiveSearch"));
	XCTAssertTrue(view.HasProperty("showVerticalScrollIndicator"));
	XCTAssertTrue(view.HasProperty("separatorColor"));
	XCTAssertTrue(view.HasProperty("defaultItemTemplate"));

	XCTAssertTrue(view.HasProperty("scrollToItem"));
	XCTAssertTrue(view.HasProperty("appendSection"));
	XCTAssertTrue(view.HasProperty("deleteSectionAt"));
	XCTAssertTrue(view.HasProperty("insertSectionAt"));
	XCTAssertTrue(view.HasProperty("replaceSectionAt"));
	XCTAssertTrue(view.HasProperty("setMarker"));

	XCTAssertNoThrow(result = js_context.JSEvaluateScript("Ti.UI.createListSection();"));
	XCTAssertTrue(result.IsObject());
	JSObject section = static_cast<JSObject>(result);

	XCTAssertTrue(section.HasProperty("footerTitle"));
	XCTAssertTrue(section.HasProperty("footerView"));
	XCTAssertTrue(section.HasProperty("headerTitle"));
	XCTAssertTrue(section.HasProperty("headerView"));
	XCTAssertTrue(section.HasProperty("items"));
	XCTAssertTrue(section.HasProperty("appendItems"));
	XCTAssertTrue(section.HasProperty("deleteItemsAt"));
	XCTAssertTrue(section.HasProperty("insertItemsAt"));
	XCTAssertTrue(section.HasProperty("replaceItemsAt"));
	XCTAssertTrue(section.HasProperty("updateItemAt"));
	XCTAssertTrue(section.HasProperty("getItemAt"));

	XCTAssertNoThrow(result = js_context.JSEvaluateScript("Ti.UI.createListItem();"));
	XCTAssertTrue(result.IsObject());
	JSObject item = static_cast<JSObject>(result);

	XCTAssertTrue(item.HasProperty("backgroundColor"));
	XCTAssertTrue(item.HasProperty("backgroundGradient"));
	XCTAssertTrue(item.HasProperty("backgroundImage"));
	XCTAssertTrue(item.HasProperty("selectedBackgroundColor"));
	XCTAssertTrue(item.HasProperty("selectedBackgroundImage"));
	XCTAssertTrue(item.HasProperty("canEdit"));
	XCTAssertTrue(item.HasProperty("canMove"));
	XCTAssertTrue(item.HasProperty("color"));
	XCTAssertTrue(item.HasProperty("font"));
	XCTAssertTrue(item.HasProperty("height"));
	XCTAssertTrue(item.HasProperty("image"));
	XCTAssertTrue(item.HasProperty("itemId"));
	XCTAssertTrue(item.HasProperty("searchableText"));
	XCTAssertTrue(item.HasProperty("title"));
	XCTAssertTrue(item.HasProperty("subtitle"));
}
