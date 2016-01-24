/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/UImodule.hpp"
#include "Titanium/UI/ListSection.hpp"
#include "NativeListViewExample.hpp"
#include "Titanium/UI/listview_js.hpp"
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

	// Titanium mock functions
	std::string TI_INIT_SCRIPT = R"js(
		this.Ti = {};
		this.Ti.API = {};
		this.Ti.API.warn = function(E) {throw E;};
		this.Ti.UI  = {};
		this.Ti.UI.createView = function(option) {
			return {
				type:'Ti.UI.View',
				option:option,
				add:function(view) {
					this.view_count = this.view_count || 0;
					this.view_count++;
					this.views = this.views || [];
					this.views.push(view);
				},
				applyProperties: function(properties) {
					this.properties = properties;
				}
			};
		};
		this.Ti.UI.createImageView = function(option) {
			return {
				type:'Ti.UI.ImageView',
				option:option,
				add:function(view) {
					this.view_count = this.view_count || 0;
					this.view_count++;
					this.views = this.views || [];
					this.views.push(view);
				},
				applyProperties: function(properties) {
					this.properties = properties;
				}
			};
		};
		this.Ti.UI.createLabel = function(option) {
			return {
				type:'Ti.UI.Label',
				option:option,
				add:function(view) {
					this.view_count = this.view_count || 0;
					this.view_count++;
					this.views = this.views || [];
					this.views.push(view);
				},
				applyProperties: function(properties) {
					this.properties = properties;
				}
			};
		};

		this.Ti.UI.LIST_ITEM_TEMPLATE_DEFAULT = '1';
	)js";

	// default template
	std::string LISTVIEW_LIST_ITEM_TEMPLATE_DEFAULT = R"js(
		var LISTVIEW_LIST_ITEM_TEMPLATE_DEFAULT = {
			childTemplates: [
				{
					type: 'Ti.UI.ImageView',
					bindId: 'image',
					properties: {
						left: 0, top: 0
					}
				},
				{
					type: 'Ti.UI.Label', 
					bindId: 'text',
					properties: {
						color: 'black',
						left: 0, top: 0,
					}
				}
			]
		}; 
		LISTVIEW_LIST_ITEM_TEMPLATE_DEFAULT;
	)js";

	// custom template
	std::string LISTVIEW_LIST_ITEM_TEMPLATE_CUSTOM = R"js(
		var LISTVIEW_LIST_ITEM_TEMPLATE_CUSTOM = {
			childTemplates: [
				{                            // Image justified left
					type: 'Ti.UI.ImageView', // Use an image view for the image
					bindId: 'pic',           // Maps to a custom pic property of the item data
					properties: {            // Sets the image view  properties
						width: '50dp', height: '50dp', left: 0
					}
				},
				{                            // Title 
					type: 'Ti.UI.Label',     // Use a label for the title 
					bindId: 'info',          // Maps to a custom info property of the item data
					properties: {            // Sets the label properties
						color: 'black',
						font: { fontFamily:'Arial', fontSize: '20dp', fontWeight:'bold' },
						left: '60dp', top: 0,
					}
				},
				{                            // Subtitle
					type: 'Ti.UI.Label',     // Use a label for the subtitle
					bindId: 'es_info',       // Maps to a custom es_info property of the item data
					properties: {            // Sets the label properties
						color: 'gray',
						font: { fontFamily:'Arial', fontSize: '14dp' },
						left: '60dp', top: '25dp',
					}
				}
			]
		};
		LISTVIEW_LIST_ITEM_TEMPLATE_CUSTOM;
	)js";

	// custom template
	std::string LISTVIEW_LIST_ITEM_TEMPLATE_CORPORATE = R"js(
		var __Id0 = {};
		var __Id2 = [];
		var __Id4 = {
			type: "Ti.UI.View",
			childTemplates: function() {
				var __Id5 = [];
				var __Id6 = {
					type: "Ti.UI.ImageView",
					bindId: "userPhoto",
					properties: {
						preventDefaultImage: true,
						border: 1,
						borderColor: "#acacac",
						height: 75,
						width: Ti.UI.SIZE,
						top: 12,
						left: 0,
						borderRadius: 35,
						bindId: "userPhoto"
					}
				};
				__Id5.push(__Id6);
				var __Id8 = {
					type: "Ti.UI.View",
					childTemplates: function() {
						var __Id9 = [];
						var __Id10 = {
							type: "Ti.UI.Label",
							bindId: "userName",
							properties: {
								font: {
									fontSize: 14
								},
								left: 85,
								color: "#444",
								bindId: "userName"
							}
						};
						__Id9.push(__Id10);
						var __Id11 = {
							type: "Ti.UI.Label",
							bindId: "userEmail",
							properties: {
								font: {
									fontSize: 10
								},
								left: 85,
								height: 20,
								color: "#666",
								bindId: "userEmail"
							}
						};
						__Id9.push(__Id11);
						var __Id12 = {
							type: "Ti.UI.Label",
							bindId: "userCompany",
							properties: {
								font: {
									fontSize: 10
								},
								left: 85,
								height: 20,
								color: "#666",
								bindId: "userCompany"
							}
						};
						__Id9.push(__Id12);
						return __Id9;
					}(),
					properties: {
						layout: "vertical",
						height: Ti.UI.SIZE,
						width: Ti.UI.SIZE,
						left: 10
					}
				};
				__Id5.push(__Id8);
				var __Id14 = {
					type: "Ti.UI.View",
					properties: {
						bottom: 0,
						backgroundColor: "#ececec",
						width: Ti.UI.FILL,
						height: 1
					}
				};
				__Id5.push(__Id14);
				return __Id5;
			}(),
			properties: {
				left: 10
			}
		};
		__Id2.push(__Id4);
		var __Id1 = {
			properties: {
				height: 100,
				width: Ti.UI.FILL,
				name: "userTemplate"
			},
			childTemplates: __Id2
		};
		__Id0["userTemplate"] = __Id1;
		__Id0;
   	)js";
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

	auto ListView = js_context.CreateObject(JSExport<NativeListViewExample>::Class());
	auto ListSection = js_context.CreateObject(JSExport<Titanium::UI::ListSection>::Class());

	XCTAssertTrue(UI.HasProperty("ListView"));
	XCTAssertTrue(UI.HasProperty("ListSection"));

	JSObject view = ListView.CallAsConstructor();

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

	JSObject section = ListSection.CallAsConstructor();

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

}

TEST_F(ListViewTests, resource_listview_js_default)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	js_context.JSEvaluateScript(TI_INIT_SCRIPT, global_object);
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createImageView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createLabel").IsObject());

	auto export_object = js_context.CreateObject();
	export_object.SetProperty("global", global_object);

	js_context.JSEvaluateScript(listview_js, export_object);

	XCTAssertTrue(export_object.HasProperty("exports"));
	auto js_exports = static_cast<JSObject>(export_object.GetProperty("exports"));

	auto js_func = js_exports.GetProperty("processTemplates");
	XCTAssertTrue(js_func.IsObject());
	auto func = static_cast<JSObject>(js_func);
	XCTAssertTrue(func.IsFunction());

	JSValue js_listview_template = js_context.CreateNull();
	XCTAssertNoThrow(js_listview_template = js_context.JSEvaluateScript(LISTVIEW_LIST_ITEM_TEMPLATE_DEFAULT));
	XCTAssertTrue(js_listview_template.IsObject());

	global_object.SetProperty("TEST_TEMPLATE", js_listview_template);

	XCTAssertNoThrow(func({js_listview_template}, func));

	XCTAssertTrue(js_context.JSEvaluateScript("TEST_TEMPLATE").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates[0].createView").IsObject());

	// Test if UI constructor functions are looked up
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates[0].createView === Ti.UI.createImageView")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates[1].createView === Ti.UI.createLabel")));

}

TEST_F(ListViewTests, resource_listview_js_custom)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	js_context.JSEvaluateScript(TI_INIT_SCRIPT, global_object);
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createImageView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createLabel").IsObject());

	auto export_object = js_context.CreateObject();
	export_object.SetProperty("global", global_object);

	js_context.JSEvaluateScript(listview_js, export_object);

	XCTAssertTrue(export_object.HasProperty("exports"));
	auto js_exports = static_cast<JSObject>(export_object.GetProperty("exports"));

	auto js_func = js_exports.GetProperty("processTemplates");
	XCTAssertTrue(js_func.IsObject());
	auto func = static_cast<JSObject>(js_func);
	XCTAssertTrue(func.IsFunction());

	JSValue js_listview_template = js_context.CreateNull();
	XCTAssertNoThrow(js_listview_template = js_context.JSEvaluateScript(LISTVIEW_LIST_ITEM_TEMPLATE_CUSTOM));
	XCTAssertTrue(js_listview_template.IsObject());

	global_object.SetProperty("TEST_TEMPLATE", js_listview_template);

	XCTAssertNoThrow(func({js_listview_template}, func));

	XCTAssertTrue(js_context.JSEvaluateScript("TEST_TEMPLATE").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates[0].createView").IsObject());

	// Test if UI constructor functions are looked up
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates[0].createView === Ti.UI.createImageView")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates[1].createView === Ti.UI.createLabel")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("TEST_TEMPLATE.childTemplates[2].createView === Ti.UI.createLabel")));

}

TEST_F(ListViewTests, createSectionView_resource_listview_js_default)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	js_context.JSEvaluateScript(TI_INIT_SCRIPT, global_object);
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createImageView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createLabel").IsObject());

	auto export_object = js_context.CreateObject();
	export_object.SetProperty("global", global_object);

	js_context.JSEvaluateScript(listview_js, export_object);

	XCTAssertTrue(export_object.HasProperty("exports"));
	auto js_exports = static_cast<JSObject>(export_object.GetProperty("exports"));

	auto js_func = js_exports.GetProperty("createSectionView");
	XCTAssertTrue(js_func.IsObject());
	auto func = static_cast<JSObject>(js_func);
	XCTAssertTrue(func.IsFunction());

	// Ti.UI.ListView
	std::string js_listview_script = R"js(
		var listview = {
			defaultItemTemplate: Ti.UI.LIST_ITEM_TEMPLATE_DEFAULT
		};
		listview;
	)js";

	// Ti.UI.ListSection
	std::string js_section_script = R"js(
		var section = {
			items: [
				{properties: { title: 'Carrots'}},
				{properties: { title: 'Potatoes'}}
			]
		};
		section;
	)js";

	JSValue result = js_context.CreateNull();
	auto js_listview = static_cast<JSObject>(js_context.JSEvaluateScript(js_listview_script));
	auto js_section  = static_cast<JSObject>(js_context.JSEvaluateScript(js_section_script));

	XCTAssertTrue(js_listview.HasProperty("defaultItemTemplate"));
	XCTAssertTrue(js_section.HasProperty("items"));

	// Run createSectionView
	const std::vector<JSValue> args {js_listview, js_section};
	result = func(args, js_exports);

	XCTAssertTrue(result.IsObject());
	auto js_result = static_cast<JSObject>(result);

	XCTAssertTrue(js_result.IsArray());
	XCTAssertTrue(static_cast<uint32_t>(js_result.GetProperty("length"))==2);

	auto view1 = static_cast<JSObject>(js_result.GetProperty(0));
	auto view2 = static_cast<JSObject>(js_result.GetProperty(1));

	XCTAssertEqual("Ti.UI.View", static_cast<std::string>(view1.GetProperty("type")));
	XCTAssertEqual("Ti.UI.View", static_cast<std::string>(view2.GetProperty("type")));

	XCTAssertEqual(2, static_cast<uint32_t>(view1.GetProperty("view_count")));
	XCTAssertEqual(2, static_cast<uint32_t>(view2.GetProperty("view_count")));

	global_object.SetProperty("result", result);
	XCTAssertEqual(2, static_cast<uint32_t>(js_context.JSEvaluateScript("result[0].views.length")));
	XCTAssertEqual("Ti.UI.ImageView", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[0].type")));
	XCTAssertEqual("Ti.UI.Label",     static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[1].type")));

	XCTAssertEqual("Carrots",  static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[1].properties.text")));
	XCTAssertEqual("Potatoes", static_cast<std::string>(js_context.JSEvaluateScript("result[1].views[1].properties.text")));
}

TEST_F(ListViewTests, createSectionView_resource_listview_js_custom)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	js_context.JSEvaluateScript(TI_INIT_SCRIPT, global_object);
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createImageView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createLabel").IsObject());

	auto export_object = js_context.CreateObject();
	export_object.SetProperty("global", global_object);

	js_context.JSEvaluateScript(listview_js, export_object);

	XCTAssertTrue(export_object.HasProperty("exports"));
	auto js_exports = static_cast<JSObject>(export_object.GetProperty("exports"));

	auto js_func = js_exports.GetProperty("createSectionView");
	XCTAssertTrue(js_func.IsObject());
	auto func = static_cast<JSObject>(js_func);
	XCTAssertTrue(func.IsFunction());

	// Ti.UI.ListView
	std::string js_listview_script = R"js(
		var listview = {
			templates: {
				TEST: LISTVIEW_LIST_ITEM_TEMPLATE_CUSTOM
			},
			defaultItemTemplate: 'TEST'
		};
		listview;
	)js";

	// Ti.UI.ListSection
	std::string js_section_script = R"js(
		var section = {
			items: [
				{ info: {text: 'Carrot'}, es_info: {text: 'Zanahoria'}, pic: {image: 'carrot.png'}},
				{ info: {text: 'Potato'}, es_info: {text: 'Patata'}, pic: {image: 'potato.png'}}
			]
		};
		section;
	)js";

	JSValue result = js_context.CreateNull();
	auto js_listview_custom_template = js_context.JSEvaluateScript(LISTVIEW_LIST_ITEM_TEMPLATE_CUSTOM);
	XCTAssertTrue(js_listview_custom_template.IsObject());
	global_object.SetProperty("LISTVIEW_LIST_ITEM_TEMPLATE_CUSTOM", js_listview_custom_template);

	auto js_listview = static_cast<JSObject>(js_context.JSEvaluateScript(js_listview_script));
	auto js_section  = static_cast<JSObject>(js_context.JSEvaluateScript(js_section_script));

	XCTAssertTrue(js_listview.HasProperty("defaultItemTemplate"));
	XCTAssertTrue(js_listview.HasProperty("templates"));
	auto js_listview_templates = js_listview.GetProperty("templates");
	XCTAssertTrue(js_listview_templates.IsObject());
	XCTAssertTrue(static_cast<JSObject>(js_listview_templates).HasProperty("TEST"));
	XCTAssertTrue(js_section.HasProperty("items"));

	// Run createSectionView
	const std::vector<JSValue> args {js_listview, js_section};
	result = func(args, js_exports);

	XCTAssertTrue(result.IsObject());
	auto js_result = static_cast<JSObject>(result);

	XCTAssertTrue(js_result.IsArray());
	XCTAssertTrue(static_cast<uint32_t>(js_result.GetProperty("length"))==2);

	auto view1 = static_cast<JSObject>(js_result.GetProperty(0));
	auto view2 = static_cast<JSObject>(js_result.GetProperty(1));

	XCTAssertEqual("Ti.UI.View", static_cast<std::string>(view1.GetProperty("type")));
	XCTAssertEqual("Ti.UI.View", static_cast<std::string>(view2.GetProperty("type")));

	XCTAssertEqual(3, static_cast<uint32_t>(view1.GetProperty("view_count")));
	XCTAssertEqual(3, static_cast<uint32_t>(view2.GetProperty("view_count")));

	global_object.SetProperty("result", result);
	XCTAssertEqual(3, static_cast<uint32_t>(js_context.JSEvaluateScript("result[0].views.length")));
	XCTAssertEqual("Ti.UI.ImageView", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[0].type")));
	XCTAssertEqual("Ti.UI.Label",     static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[1].type")));
	XCTAssertEqual("Ti.UI.Label",     static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[2].type")));

	XCTAssertEqual("carrot.png", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[0].properties.image")));
	XCTAssertEqual("potato.png", static_cast<std::string>(js_context.JSEvaluateScript("result[1].views[0].properties.image")));

	XCTAssertEqual("Carrot", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[1].properties.text")));
	XCTAssertEqual("Potato", static_cast<std::string>(js_context.JSEvaluateScript("result[1].views[1].properties.text")));

	XCTAssertEqual("Zanahoria", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[2].properties.text")));
	XCTAssertEqual("Patata", static_cast<std::string>(js_context.JSEvaluateScript("result[1].views[2].properties.text")));
}

TEST_F(ListViewTests, resource_listview_js_corporate)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	js_context.JSEvaluateScript(TI_INIT_SCRIPT, global_object);
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createImageView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createLabel").IsObject());

	auto export_object = js_context.CreateObject();
	export_object.SetProperty("global", global_object);

	js_context.JSEvaluateScript(listview_js, export_object);

	XCTAssertTrue(export_object.HasProperty("exports"));
	auto js_exports = static_cast<JSObject>(export_object.GetProperty("exports"));

	auto js_func = js_exports.GetProperty("processTemplates");
	XCTAssertTrue(js_func.IsObject());
	auto func = static_cast<JSObject>(js_func);
	XCTAssertTrue(func.IsFunction());

	JSValue js_listview_templates = js_context.CreateNull();
	XCTAssertNoThrow(js_listview_templates = js_context.JSEvaluateScript(LISTVIEW_LIST_ITEM_TEMPLATE_CORPORATE));
	XCTAssertTrue(js_listview_templates.IsObject());

	JSValue js_userTemplate = static_cast<JSObject>(js_listview_templates).GetProperty("userTemplate");
	JSValue js_childTemplate = static_cast<JSObject>(js_userTemplate).GetProperty("childTemplates");
	JSValue js_listview_template = static_cast<JSObject>(js_childTemplate).GetProperty(0);

	XCTAssertTrue(js_listview_template.IsObject());
	global_object.SetProperty("userTemplate", js_listview_template);

	XCTAssertNoThrow(func({js_listview_template}, func));

	XCTAssertTrue(js_context.JSEvaluateScript("userTemplate").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("userTemplate.childTemplates").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("userTemplate.childTemplates[0]").IsObject());

	// Test if UI constructor functions are looked up
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("userTemplate.childTemplates[0].createView === Ti.UI.createImageView")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("userTemplate.childTemplates[1].createView === Ti.UI.createView")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("userTemplate.childTemplates[2].createView === Ti.UI.createView")));

	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("userTemplate.childTemplates[1].childTemplates[0].createView === Ti.UI.createLabel")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("userTemplate.childTemplates[1].childTemplates[1].createView === Ti.UI.createLabel")));
	XCTAssertTrue(static_cast<bool>(js_context.JSEvaluateScript("userTemplate.childTemplates[1].childTemplates[2].createView === Ti.UI.createLabel")));

}

TEST_F(ListViewTests, createSectionView_resource_listview_js_corporate)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	js_context.JSEvaluateScript(TI_INIT_SCRIPT, global_object);
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createImageView").IsObject());
	XCTAssertTrue(js_context.JSEvaluateScript("Ti.UI.createLabel").IsObject());

	auto export_object = js_context.CreateObject();
	export_object.SetProperty("global", global_object);

	js_context.JSEvaluateScript(listview_js, export_object);

	XCTAssertTrue(export_object.HasProperty("exports"));
	auto js_exports = static_cast<JSObject>(export_object.GetProperty("exports"));

	auto js_func = js_exports.GetProperty("createSectionView");
	XCTAssertTrue(js_func.IsObject());
	auto func = static_cast<JSObject>(js_func);
	XCTAssertTrue(func.IsFunction());

	// Ti.UI.ListView
	std::string js_listview_script = R"js(
		var listview = {
			templates: {
				TEST: userTemplate
			},
			defaultItemTemplate: 'TEST'
		};
		listview;
	)js";

	// Ti.UI.ListSection
	std::string js_section_script = R"js(
		var section = {
			items: [
				{ userName: {text: 'Carrot'}, userEmail: {text: 'Zanahoria'}, userPhoto: {image: 'carrot.png'}, userCompany: {text: 'Appcelerator, Inc'}},
				{ userName: {text: 'Potato'}, userEmail: {text: 'Patata'}, userPhoto: {image: 'potato.png'}, userCompany: {text: 'Appcelerator, Inc'}}
			]
		};
		section;
	)js";

	JSValue js_corporate_templates = js_context.CreateNull();
	XCTAssertNoThrow(js_corporate_templates = js_context.JSEvaluateScript(LISTVIEW_LIST_ITEM_TEMPLATE_CORPORATE));
	XCTAssertTrue(js_corporate_templates.IsObject());

	JSValue js_userTemplate = static_cast<JSObject>(js_corporate_templates).GetProperty("userTemplate");
	JSValue js_childTemplate = static_cast<JSObject>(js_userTemplate).GetProperty("childTemplates");
	JSValue js_listview_template = static_cast<JSObject>(js_childTemplate).GetProperty(0);

	XCTAssertTrue(js_listview_template.IsObject());
	global_object.SetProperty("userTemplate", js_listview_template);

	auto js_listview = static_cast<JSObject>(js_context.JSEvaluateScript(js_listview_script));
	auto js_section  = static_cast<JSObject>(js_context.JSEvaluateScript(js_section_script));

	XCTAssertTrue(js_listview.HasProperty("defaultItemTemplate"));
	XCTAssertTrue(js_listview.HasProperty("templates"));
	auto js_listview_templates = js_listview.GetProperty("templates");
	XCTAssertTrue(js_listview_templates.IsObject());
	XCTAssertTrue(static_cast<JSObject>(js_listview_templates).HasProperty("TEST"));
	XCTAssertTrue(js_section.HasProperty("items"));

	// Run createSectionView
	const std::vector<JSValue> args {js_listview, js_section};
	auto result = func(args, js_exports);

	XCTAssertTrue(result.IsObject());
	auto js_result = static_cast<JSObject>(result);

	XCTAssertTrue(js_result.IsArray());
	XCTAssertTrue(static_cast<uint32_t>(js_result.GetProperty("length"))==2);

	auto view1 = static_cast<JSObject>(js_result.GetProperty(0));
	auto view2 = static_cast<JSObject>(js_result.GetProperty(1));

	XCTAssertEqual("Ti.UI.View", static_cast<std::string>(view1.GetProperty("type")));
	XCTAssertEqual("Ti.UI.View", static_cast<std::string>(view2.GetProperty("type")));

	XCTAssertEqual(3, static_cast<uint32_t>(view1.GetProperty("view_count")));
	XCTAssertEqual(3, static_cast<uint32_t>(view2.GetProperty("view_count")));

	global_object.SetProperty("result", result);
	XCTAssertEqual(3, static_cast<uint32_t>(js_context.JSEvaluateScript("result[0].views.length")));
	XCTAssertEqual("Ti.UI.ImageView", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[0].type")));
	XCTAssertEqual("Ti.UI.View",     static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[1].type")));
	XCTAssertEqual("Ti.UI.View",     static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[2].type")));

	XCTAssertEqual("carrot.png", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[0].properties.image")));
	XCTAssertEqual("potato.png", static_cast<std::string>(js_context.JSEvaluateScript("result[1].views[0].properties.image")));

	XCTAssertEqual(3, static_cast<uint32_t>(js_context.JSEvaluateScript("result[0].views[1].view_count")));
	XCTAssertEqual(3, static_cast<uint32_t>(js_context.JSEvaluateScript("result[1].views[1].view_count")));

	XCTAssertEqual("Carrot", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[1].views[0].properties.text")));
	XCTAssertEqual("Potato", static_cast<std::string>(js_context.JSEvaluateScript("result[1].views[1].views[0].properties.text")));

	XCTAssertEqual("Zanahoria", static_cast<std::string>(js_context.JSEvaluateScript("result[0].views[1].views[1].properties.text")));
	XCTAssertEqual("Patata", static_cast<std::string>(js_context.JSEvaluateScript("result[1].views[1].views[1].properties.text")));
}