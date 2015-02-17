/**
 * TitaniumKit Titanium.UI.ListView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListView.hpp"

namespace Titanium
{
	namespace UI
	{
		// TODO: move to utility class
		static std::vector<JSValue> js_to_array(const JSObject& js_array) 
		{
			std::vector<JSValue> items;
			const auto length = static_cast<uint32_t>(js_array.GetProperty("length"));
			for (uint32_t i = 0; i < length; i++) {
				items.push_back(js_array.GetProperty(i));
			}
			return items;
		}

		static std::unordered_map<std::string, JSValue> js_to_dictionary(const JSObject& js_dictionary) 
		{
			std::unordered_map<std::string, JSValue> dictionary;
			for (const auto& name : static_cast<std::vector<JSString>>(js_dictionary.GetPropertyNames())) {
				dictionary.emplace(name, js_dictionary.GetProperty(name));
			}
			return dictionary;
		}

		static JSObject dictionary_to_js(const JSContext& js_context, const std::unordered_map<std::string, JSValue>& dictionary) 
		{
			auto js_dictionary = js_context.CreateObject();
			for (auto kv : dictionary) {
				js_dictionary.SetProperty(kv.first, kv.second);
			}
			return js_dictionary;
		}

		ListView::ListView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: View(js_context, arguments),
			footerTitle__(""),
			headerTitle__(""),
			searchText__(""),
			caseInsensitiveSearch__(true),
			showVerticalScrollIndicator__(true),
			separatorColor__(""),
			footerView__(js_context.CreateNull()),
			headerView__(js_context.CreateNull()),
			searchView__(js_context.CreateNull())
		{
		}

		std::unordered_map<std::string, JSValue> ListView::get_templates() const TITANIUM_NOEXCEPT
		{
			return templates__;
		}

		void ListView::set_templates(const std::unordered_map<std::string, JSValue>& templates) TITANIUM_NOEXCEPT
		{
			templates__ = templates;
		}

		std::vector<JSValue> ListView::get_sections() const TITANIUM_NOEXCEPT
		{
			return sections__;
		}

		void ListView::set_sections(const std::vector<JSValue>& sections) TITANIUM_NOEXCEPT
		{
			sections__ = sections;
			sections_set_notify();
		}
		
		void ListView::sections_set_notify()
		{
			// for subclass
		}

		std::vector<JSObject> ListView::createSectionViewAt(uint32_t index)
		{
			std::vector<JSObject> items;
			auto section = sections__.at(index);

			items.push_back(static_cast<JSObject>(get_context().JSEvaluateScript("Ti.UI.createLabel({text:'Test Item 1', color:'white'});"))); // FIXME
			items.push_back(static_cast<JSObject>(get_context().JSEvaluateScript("Ti.UI.createLabel({text:'Test Item 2', color:'yellow'});"))); // FIXME
			items.push_back(static_cast<JSObject>(get_context().JSEvaluateScript("Ti.UI.createLabel({text:'Test Item 3', color:'red'});"))); // FIXME

			return items;
		}

		std::string ListView::get_footerTitle() const TITANIUM_NOEXCEPT
		{
			return footerTitle__;
		}

		void ListView::set_footerTitle(const std::string& footerTitle) TITANIUM_NOEXCEPT
		{
			footerTitle__ = footerTitle;
		}

		JSValue ListView::get_footerView() const TITANIUM_NOEXCEPT
		{
			return footerView__;
		}

		void ListView::set_footerView(const JSValue& footerView) TITANIUM_NOEXCEPT
		{
			footerView__ = footerView;
			if (footerView__.IsObject()) {
				auto view = static_cast<JSObject>(footerView__).GetPrivate<Titanium::UI::View>();
				if (view != nullptr) {
					footerView_set_notify(*view);
				}
			}
		}

		std::string ListView::get_headerTitle() const TITANIUM_NOEXCEPT
		{
			return headerTitle__;
		}

		void ListView::set_headerTitle(const std::string& headerTitle) TITANIUM_NOEXCEPT
		{
			headerTitle__ = headerTitle;
		}

		JSValue ListView::get_headerView() const TITANIUM_NOEXCEPT
		{
			return headerView__;
		}

		void ListView::set_headerView(const JSValue& headerView) TITANIUM_NOEXCEPT
		{
			headerView__ = headerView;
			if (headerView__.IsObject()) {
				auto view = static_cast<JSObject>(headerView__).GetPrivate<Titanium::UI::View>();
				if (view != nullptr) {
					headerView_set_notify(*view);
				}
			}
		}
		
		void ListView::headerView_set_notify(View& view)
		{
			// for subclass
		}
		
		void ListView::footerView_set_notify(View& view)
		{
			// for subclass
		}

		JSValue ListView::get_searchView() const TITANIUM_NOEXCEPT
		{
			return searchView__;
		}

		void ListView::set_searchView(const JSValue& searchView) TITANIUM_NOEXCEPT
		{
			searchView__ = searchView;
		}

		std::string ListView::get_searchText() const TITANIUM_NOEXCEPT
		{
			return searchText__;
		}

		void ListView::set_searchText(const std::string& searchText) TITANIUM_NOEXCEPT
		{
			searchText__ = searchText;
		}

		bool ListView::get_caseInsensitiveSearch() const TITANIUM_NOEXCEPT
		{
			return caseInsensitiveSearch__;
		}

		void ListView::set_caseInsensitiveSearch(bool value) TITANIUM_NOEXCEPT
		{
			caseInsensitiveSearch__ = value;
		}

		uint32_t ListView::get_sectionCount() const TITANIUM_NOEXCEPT
		{
			return static_cast<uint32_t>(sections__.size());
		}

		bool ListView::get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return showVerticalScrollIndicator__;
		}

		void ListView::set_showVerticalScrollIndicator(bool value) TITANIUM_NOEXCEPT
		{
			showVerticalScrollIndicator__ = value;
		}

		std::string ListView::get_separatorColor() const TITANIUM_NOEXCEPT
		{
			return separatorColor__;
		}

		void ListView::set_separatorColor(std::string value) TITANIUM_NOEXCEPT
		{
			separatorColor__ = value;
		}

		std::string ListView::get_defaultItemTemplate() const TITANIUM_NOEXCEPT
		{
			return defaultItemTemplate__;
		}
		
		void ListView::set_defaultItemTemplate(std::string value) TITANIUM_NOEXCEPT
		{
			defaultItemTemplate__ = value;
		}

		void ListView::scrollToItem(uint32_t sectionIndex, uint32_t itemIndex, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView::scrollToItem: Unimplemented");
		}

		void ListView::appendSection(const std::vector<JSValue>& section, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView::appendSection: Unimplemented");
		}

		void ListView::deleteSectionAt(uint32_t sectionIndex, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView::deleteSectionAt: Unimplemented");
		}

		void ListView::insertSectionAt(uint32_t sectionIndex, const std::vector<JSValue>& section, const ListViewAnimationProperties& animation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView::insertSectionAt: Unimplemented");
		}

		void ListView::replaceSectionAt(uint32_t sectionIndex, const std::vector<JSValue>& section, const ListViewAnimationProperties& animationn) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView::replaceSectionAt: Unimplemented");
		}

		void ListView::setMarker(const std::unordered_map<std::string, JSValue>& props) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView::setMarker: Unimplemented");
		}

		void ListView::JSExportInitialize() {
			JSExport<ListView>::SetClassVersion(1);
			JSExport<ListView>::SetParent(JSExport<Module>::Class());

			JSExport<ListView>::AddValueProperty("templates", std::mem_fn(&ListView::js_get_templates),     std::mem_fn(&ListView::js_set_templates));
			JSExport<ListView>::AddValueProperty("sections", std::mem_fn(&ListView::js_get_sections),       std::mem_fn(&ListView::js_set_sections));
			JSExport<ListView>::AddValueProperty("footerTitle", std::mem_fn(&ListView::js_get_footerTitle), std::mem_fn(&ListView::js_set_footerTitle));
			JSExport<ListView>::AddValueProperty("footerView", std::mem_fn(&ListView::js_get_footerView),   std::mem_fn(&ListView::js_set_footerView));
			JSExport<ListView>::AddValueProperty("headerTitle", std::mem_fn(&ListView::js_get_headerTitle), std::mem_fn(&ListView::js_set_headerTitle));
			JSExport<ListView>::AddValueProperty("headerView", std::mem_fn(&ListView::js_get_headerView),   std::mem_fn(&ListView::js_set_headerView));
			JSExport<ListView>::AddValueProperty("searchView", std::mem_fn(&ListView::js_get_searchView),   std::mem_fn(&ListView::js_set_searchView));
			JSExport<ListView>::AddValueProperty("searchText", std::mem_fn(&ListView::js_get_searchText),   std::mem_fn(&ListView::js_set_searchText));
			JSExport<ListView>::AddValueProperty("caseInsensitiveSearch", std::mem_fn(&ListView::js_get_caseInsensitiveSearch), std::mem_fn(&ListView::js_set_caseInsensitiveSearch));
			JSExport<ListView>::AddValueProperty("sectionCount", std::mem_fn(&ListView::js_get_sectionCount));
			JSExport<ListView>::AddValueProperty("showVerticalScrollIndicator", std::mem_fn(&ListView::js_get_showVerticalScrollIndicator), std::mem_fn(&ListView::js_set_showVerticalScrollIndicator));
			JSExport<ListView>::AddValueProperty("separatorColor", std::mem_fn(&ListView::js_get_separatorColor), std::mem_fn(&ListView::js_set_separatorColor));
			JSExport<ListView>::AddValueProperty("defaultItemTemplate", std::mem_fn(&ListView::js_get_defaultItemTemplate), std::mem_fn(&ListView::js_set_defaultItemTemplate));

			JSExport<ListView>::AddFunctionProperty("scrollToItem", std::mem_fn(&ListView::js_scrollToItem));
			JSExport<ListView>::AddFunctionProperty("appendSection", std::mem_fn(&ListView::js_appendSection));
			JSExport<ListView>::AddFunctionProperty("deleteSectionAt", std::mem_fn(&ListView::js_deleteSectionAt));
			JSExport<ListView>::AddFunctionProperty("insertSectionAt", std::mem_fn(&ListView::js_insertSectionAt));
			JSExport<ListView>::AddFunctionProperty("replaceSectionAt", std::mem_fn(&ListView::js_replaceSectionAt));
			JSExport<ListView>::AddFunctionProperty("setMarker", std::mem_fn(&ListView::js_setMarker));
			JSExport<ListView>::AddFunctionProperty("getTemplates", std::mem_fn(&ListView::js_getTemplates));
			JSExport<ListView>::AddFunctionProperty("setTemplates", std::mem_fn(&ListView::js_setTemplates));
			JSExport<ListView>::AddFunctionProperty("getSections", std::mem_fn(&ListView::js_getSections));
			JSExport<ListView>::AddFunctionProperty("setSections", std::mem_fn(&ListView::js_setSections));
			JSExport<ListView>::AddFunctionProperty("getFooterTitle", std::mem_fn(&ListView::js_getFooterTitle));
			JSExport<ListView>::AddFunctionProperty("setFooterTitle", std::mem_fn(&ListView::js_setFooterTitle));
			JSExport<ListView>::AddFunctionProperty("getFooterView", std::mem_fn(&ListView::js_getFooterView));
			JSExport<ListView>::AddFunctionProperty("setFooterView", std::mem_fn(&ListView::js_setFooterView));
			JSExport<ListView>::AddFunctionProperty("getHeaderTitle", std::mem_fn(&ListView::js_getHeaderTitle));
			JSExport<ListView>::AddFunctionProperty("setHeaderTitle", std::mem_fn(&ListView::js_setHeaderTitle));
			JSExport<ListView>::AddFunctionProperty("getHeaderView", std::mem_fn(&ListView::js_getHeaderView));
			JSExport<ListView>::AddFunctionProperty("setHeaderView", std::mem_fn(&ListView::js_setHeaderView));
			JSExport<ListView>::AddFunctionProperty("getSearchView", std::mem_fn(&ListView::js_getSearchView));
			JSExport<ListView>::AddFunctionProperty("setSearchView", std::mem_fn(&ListView::js_setSearchView));
			JSExport<ListView>::AddFunctionProperty("getSearchText", std::mem_fn(&ListView::js_getSearchText));
			JSExport<ListView>::AddFunctionProperty("setSearchText", std::mem_fn(&ListView::js_setSearchText));
			JSExport<ListView>::AddFunctionProperty("getCaseInsensitiveSearch", std::mem_fn(&ListView::js_getCaseInsensitiveSearch));
			JSExport<ListView>::AddFunctionProperty("setCaseInsensitiveSearch", std::mem_fn(&ListView::js_setCaseInsensitiveSearch));
			JSExport<ListView>::AddFunctionProperty("getSectionCount", std::mem_fn(&ListView::js_getSectionCount));
			JSExport<ListView>::AddFunctionProperty("getShowVerticalScrollIndicator", std::mem_fn(&ListView::js_getShowVerticalScrollIndicator));
			JSExport<ListView>::AddFunctionProperty("setShowVerticalScrollIndicator", std::mem_fn(&ListView::js_setShowVerticalScrollIndicator));
			JSExport<ListView>::AddFunctionProperty("getSeparatorColor", std::mem_fn(&ListView::js_getSeparatorColor));
			JSExport<ListView>::AddFunctionProperty("setSeparatorColor", std::mem_fn(&ListView::js_setSeparatorColor));
			JSExport<ListView>::AddFunctionProperty("getDefaultItemTemplate", std::mem_fn(&ListView::js_getDefaultItemTemplate));
			JSExport<ListView>::AddFunctionProperty("setDefaultItemTemplate", std::mem_fn(&ListView::js_setDefaultItemTemplate));
		}

		JSValue ListView::js_get_templates() const TITANIUM_NOEXCEPT
		{
			return dictionary_to_js(get_context(), get_templates());
		}

		bool ListView::js_set_templates(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			if (!argument.IsObject()) {
				return false;
			}
			set_templates(js_to_dictionary(static_cast<JSObject>(argument)));
			return true;
		}

		JSValue ListView::js_get_sections() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateArray(get_sections());
		}

		bool ListView::js_set_sections(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			if (!argument.IsObject()) {
				return false;
			}
			const auto sections = static_cast<JSObject>(argument);
			if (!sections.IsArray()) {
				return false;
			}
			set_sections(js_to_array(sections));
			return true;
		}

		JSValue ListView::js_get_sectionCount() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<uint32_t>(get_sectionCount()));
		}

		JSValue ListView::js_get_footerTitle() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_footerTitle());
		}

		bool ListView::js_set_footerTitle(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_footerTitle(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListView::js_get_footerView() const TITANIUM_NOEXCEPT
		{
			return get_footerView();
		}

		bool ListView::js_set_footerView(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			if (!argument.IsObject()) {
				return false;
			}
			set_footerView(argument);
			return true;
		}

		JSValue ListView::js_get_headerTitle() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_headerTitle());
		}

		bool ListView::js_set_headerTitle(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_headerTitle(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListView::js_get_headerView() const TITANIUM_NOEXCEPT
		{
			return get_headerView();
		}

		bool ListView::js_set_headerView(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			if (!argument.IsObject()) {
				return false;
			}
			set_headerView(argument);
			return true;
		}

		JSValue ListView::js_get_searchView() const TITANIUM_NOEXCEPT
		{
			return get_searchView();
		}

		bool ListView::js_set_searchView(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			set_searchView(argument);
			return true;
		}

		JSValue ListView::js_get_searchText() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_searchText());
		}

		bool ListView::js_set_searchText(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_searchText(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListView::js_get_caseInsensitiveSearch() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_caseInsensitiveSearch());
		}

		bool ListView::js_set_caseInsensitiveSearch(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_caseInsensitiveSearch(static_cast<bool>(argument));
			return true;
		}

		JSValue ListView::js_get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_showVerticalScrollIndicator());
		}

		bool ListView::js_set_showVerticalScrollIndicator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_showVerticalScrollIndicator(static_cast<bool>(argument));
			return true;
		}

		JSValue ListView::js_get_separatorColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_separatorColor());
		}

		bool ListView::js_set_separatorColor(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_separatorColor(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListView::js_get_defaultItemTemplate() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_defaultItemTemplate());
		}

		bool ListView::js_set_defaultItemTemplate(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			set_defaultItemTemplate(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListView::js_scrollToItem(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 2) {
				ListViewAnimationProperties animation;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());

				const auto sectionIndex = static_cast<uint32_t>(_0);
				const auto itemIndex    = static_cast<uint32_t>(_1);

				if (arguments.size() >= 3) {
					const auto _3 = arguments.at(2);
					if (_3.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_3));
					}
				}

				scrollToItem(sectionIndex, itemIndex, animation);
			}

			return get_context().CreateUndefined();
		}

		JSValue ListView::js_appendSection(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView.appendSection is not implemented yet");

			if (arguments.size() >= 2) {
				ListViewAnimationProperties animation;
				std::vector<JSValue> sections;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto js_sections = static_cast<JSObject>(_0);

				if (js_sections.IsArray()) {
					sections = js_to_array(js_sections);
				} else {
					sections.push_back(_0);
				}

				if (arguments.size() >= 3) {
					const auto _3 = arguments.at(2);
					if (_3.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_3));
					}
				}

				appendSection(sections, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_deleteSectionAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				ListViewAnimationProperties animation;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());

				const auto sectionIndex = static_cast<uint32_t>(_0);

				if (arguments.size() >= 2) {
					const auto _2 = arguments.at(1);
					if (_2.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_2));
					}
				}
				deleteSectionAt(sectionIndex, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_insertSectionAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 2) {
				ListViewAnimationProperties animation;
				std::vector<JSValue> sections;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto sectionIndex = static_cast<uint32_t>(_0);

				const auto _1 = arguments.at(0);
				TITANIUM_ASSERT(_1.IsObject());
				const auto js_sections = static_cast<JSObject>(_1);

				if (js_sections.IsArray()) {
					sections = js_to_array(js_sections);
				} else {
					sections.push_back(_1);
				}

				if (arguments.size() >= 3) {
					const auto _3 = arguments.at(2);
					if (_3.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_3));
					}
				}

				insertSectionAt(sectionIndex, sections, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_replaceSectionAt(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 2) {
				ListViewAnimationProperties animation;
				std::vector<JSValue> sections;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto sectionIndex = static_cast<uint32_t>(_0);

				const auto _1 = arguments.at(0);
				TITANIUM_ASSERT(_1.IsObject());
				const auto js_sections = static_cast<JSObject>(_1);

				if (js_sections.IsArray()) {
					sections = js_to_array(js_sections);
				} else {
					sections.push_back(_1);
				}

				if (arguments.size() >= 3) {
					const auto _3 = arguments.at(2);
					if (_3.IsObject()) {
						animation = js_to_ListViewAnimationProperties(static_cast<JSObject>(_3));
					}
				}

				replaceSectionAt(sectionIndex, sections, animation);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_setMarker(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				setMarker(js_to_dictionary(static_cast<JSObject>(_0)));
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getTemplates(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_templates();
		}

		JSValue ListView::js_setTemplates(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_templates(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getSections(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_sections();
		}

		JSValue ListView::js_setSections(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_sections(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getFooterTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_footerTitle();
		}

		JSValue ListView::js_setFooterTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_footerTitle(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getFooterView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_footerView();
		}

		JSValue ListView::js_setFooterView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_footerView(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getHeaderTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_headerTitle();
		}

		JSValue ListView::js_setHeaderTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_headerTitle(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getHeaderView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_headerView();
		}

		JSValue ListView::js_setHeaderView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_headerView(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getSearchView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_searchView();
		}

		JSValue ListView::js_setSearchView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_searchView(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getSearchText(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_searchText();
		}

		JSValue ListView::js_setSearchText(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_searchText(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getCaseInsensitiveSearch(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_caseInsensitiveSearch();
		}

		JSValue ListView::js_setCaseInsensitiveSearch(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_caseInsensitiveSearch(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getSectionCount(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_sectionCount();
		}

		JSValue ListView::js_getShowVerticalScrollIndicator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_showVerticalScrollIndicator();
		}

		JSValue ListView::js_setShowVerticalScrollIndicator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_showVerticalScrollIndicator(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getSeparatorColor(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_separatorColor();
		}

		JSValue ListView::js_setSeparatorColor(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_separatorColor(_0);
			}
			return get_context().CreateUndefined();
		}

		JSValue ListView::js_getDefaultItemTemplate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			return js_get_defaultItemTemplate();
		}

		JSValue ListView::js_setDefaultItemTemplate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				js_set_defaultItemTemplate(_0);
			}
			return get_context().CreateUndefined();
		}

	} // namespace UI
} // namespace Titanium