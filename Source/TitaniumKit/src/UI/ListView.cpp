/**
 * TitaniumKit Titanium.UI.ListView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListView.hpp"
#include "Titanium/UI/ListViewAnimationProperties.hpp"
#include "Titanium/UI/SearchBar.hpp"
#include "Titanium/UI/listview_js.hpp"
#include <boost/algorithm/string.hpp>

namespace Titanium
{
	namespace UI
	{
		ListView::ListView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.ListView"),
			listviewAnimationProperties_ctor__(js_context.CreateObject(JSExport<Titanium::UI::ListViewAnimationProperties>::Class())),
			footerTitle__(""),
			headerTitle__(""),
			searchText__(""),
			caseInsensitiveSearch__(true),
			showVerticalScrollIndicator__(true),
			separatorColor__(""),
			ti_listview_exports__(js_context.CreateObject()),
			sectionViewCreateFunction__(js_context.CreateObject()),
			sectionViewItemCreateFunction__(js_context.CreateObject()),
			model__(std::make_shared<ListModel<ListSection>>())
		{
		}

		std::vector<std::shared_ptr<ListSection>> ListView::get_sections() const TITANIUM_NOEXCEPT
		{
			// ListView should return original data even when it's filtered
			if (model__->isSaved()) {
				return model__->get_saved_sections();
			}
			return model__->get_sections();
		}

		void ListView::set_sections(const std::vector<std::shared_ptr<ListSection>>& sections) TITANIUM_NOEXCEPT
		{
			return model__->set_sections(sections);
		}

		void ListView::loadJS()
		{
			if (sectionViewCreateFunction__.IsFunction()) {
				return;
			}

			auto context = get_context();
			auto export_object = context.CreateObject();
			export_object.SetProperty("global", context.get_global_object());

			context.JSEvaluateScript(listview_js, export_object);

			TITANIUM_ASSERT(export_object.HasProperty("exports"));
			ti_listview_exports__ = static_cast<JSObject>(export_object.GetProperty("exports"));

			auto js_sectionViewCreateFunction = ti_listview_exports__.GetProperty("createSectionView");
			TITANIUM_ASSERT(js_sectionViewCreateFunction.IsObject());
			sectionViewCreateFunction__ = static_cast<JSObject>(js_sectionViewCreateFunction);
			TITANIUM_ASSERT(sectionViewCreateFunction__.IsFunction());

			auto js_createSectionViewItemAt = ti_listview_exports__.GetProperty("createSectionItemAt");
			TITANIUM_ASSERT(js_createSectionViewItemAt.IsObject());
			sectionViewItemCreateFunction__ = static_cast<JSObject>(js_createSectionViewItemAt);
			TITANIUM_ASSERT(sectionViewItemCreateFunction__.IsFunction());
		}

		TITANIUM_PROPERTY_READWRITE(ListView, std::string, footerTitle)
		TITANIUM_PROPERTY_READWRITE(ListView, std::string, headerTitle)
		TITANIUM_PROPERTY_READWRITE(ListView, std::shared_ptr<View>, footerView)
		TITANIUM_PROPERTY_READWRITE(ListView, std::shared_ptr<View>, headerView)
		TITANIUM_PROPERTY_READWRITE(ListView, std::string, searchText)
		TITANIUM_PROPERTY_READWRITE(ListView, bool, caseInsensitiveSearch)
		TITANIUM_PROPERTY_READ(ListView, std::shared_ptr<SearchBar>, searchView)
		void ListView::set_searchView(const std::shared_ptr<SearchBar>& searchView) TITANIUM_NOEXCEPT
		{
			searchView__ = searchView;

			if (searchView__) {
				searchView__->set_querySubmitted([this](const std::string& query) {
					try {
						querySubmitted(query);
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at ListView::querySubmitted");
					}
				});
				searchView__->set_suggestionRequested([this](const std::string& query) {
					try {
						return suggestionRequested(query);
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at ListView::suggestionRequested");
					}
					return std::vector<std::string>();
				});
			}

		}

		void ListView::querySubmitted(const std::string& query)
		{
			if (query.empty()) {
				//
				// query finished, recover saved data
				//
				if (model__->isSaved()) {
					model__->restore();
				}
				set_sections(model__->get_sections());
				return;
			}

			// Create default section to show results
			const auto section = static_cast<JSObject>(get_context().JSEvaluateScript("Ti.UI.createListSection({ headerTitle: 'Search Results' });")).GetPrivate<Titanium::UI::ListSection>();
			const std::vector<std::shared_ptr<ListSection>> sections { section };
			const auto caseInsensitive = get_caseInsensitiveSearch();
			const auto normalizedQuery = caseInsensitive ? boost::algorithm::to_lower_copy(query) : query;
			const auto saved_sections = model__->get_saved_sections();
			std::vector<std::tuple<size_t, size_t>> saved_position;
			std::vector<ListDataItem> items;
			for (size_t sectionIndex = 0; sectionIndex < saved_sections.size(); sectionIndex++) {
				const auto savedItems = saved_sections.at(sectionIndex)->get_items();
				for (size_t itemIndex = 0; itemIndex < savedItems.size(); itemIndex++) {
					const auto item = savedItems.at(itemIndex);
					if (ListDataItem_contains(item, normalizedQuery, caseInsensitive)) {
						// Save "original" position so we can search it easily later on
						saved_position.push_back(std::make_tuple(sectionIndex, itemIndex));
						items.push_back(item);
					}
				}
			}
			model__->save_positions(saved_position);
			section->appendItems(items, nullptr);
			set_sections(sections);
		}

		std::vector<std::string> ListView::suggestionRequested(const std::string& query)
		{
			if (!model__->isSaved()) {
				model__->save();
			}

			const auto caseInsensitive = get_caseInsensitiveSearch();
			const auto normalizedQuery = caseInsensitive ? boost::algorithm::to_lower_copy(query) : query;
			std::vector<std::string> suggestions;
			for (const auto section : model__->get_saved_sections()) {
				for (const auto item : section->get_items()) {
					if (ListDataItem_contains(item, normalizedQuery, caseInsensitive)) {
						suggestions.push_back(static_cast<std::string>(item.properties.at("title")));
					}
				}
			}
			return suggestions;
		}

		std::uint32_t ListView::get_sectionCount() const TITANIUM_NOEXCEPT
		{
			if (model__->isSaved()) {
				return model__->get_savedSectionCount();
			}
			return model__->get_sectionCount();
		}

		TITANIUM_PROPERTY_READWRITE(ListView, bool, showVerticalScrollIndicator)
		TITANIUM_PROPERTY_READWRITE(ListView, std::string, separatorColor)
		TITANIUM_PROPERTY_READWRITE(ListView, std::string, defaultItemTemplate)

		void ListView::scrollToItem(const uint32_t& sectionIndex, const uint32_t& itemIndex, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ListView::scrollToItem: Unimplemented");
		}

		void ListView::appendSection(const std::vector<std::shared_ptr<ListSection>>& sections, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			model__->appendSection(sections);
		}

		void ListView::deleteSectionAt(const uint32_t& index, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			model__->deleteSectionAt(index);
		}

		void ListView::insertSectionAt(const uint32_t& index, const std::vector<std::shared_ptr<ListSection>>& section, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			model__->insertSectionAt(index, section);
		}

		void ListView::replaceSectionAt(const uint32_t& index, const std::vector<std::shared_ptr<ListSection>>& sections, const std::shared_ptr<ListViewAnimationProperties>& animationn) TITANIUM_NOEXCEPT
		{
			model__->replaceSectionAt(index, sections);
		}

		void ListView::addMarker(const ListViewMarkerProps& marker) TITANIUM_NOEXCEPT
		{
			markers__.push_back(marker);
		}

		void ListView::setMarker(const ListViewMarkerProps& marker) TITANIUM_NOEXCEPT
		{
			markers__.clear();
			markers__.push_back(marker);
		}

		void ListView::fireListSectionEvent(const std::string& name, const std::shared_ptr<ListSection>& section, const std::uint32_t& itemIndex, const std::uint32_t& itemCount, const std::uint32_t& affectedRows)
		{
			const auto ctx = get_context();
			auto event_args = ctx.CreateObject();
			event_args.SetProperty("section", get_object());
			event_args.SetProperty("itemIndex", ctx.CreateNumber(itemIndex));
			event_args.SetProperty("itemCount", ctx.CreateNumber(itemCount));
			event_args.SetProperty("sectionIndex", get_context().CreateNumber(model__->getSectionIndex(section)));

			fireEvent(name, event_args);
		}

		void ListView::JSExportInitialize()
		{
			JSExport<ListView>::SetClassVersion(1);
			JSExport<ListView>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(ListView, sections);
			TITANIUM_ADD_PROPERTY(ListView, footerTitle);
			TITANIUM_ADD_PROPERTY(ListView, headerTitle);
			TITANIUM_ADD_PROPERTY(ListView, searchText);

			TITANIUM_ADD_PROPERTY(ListView, footerView);
			TITANIUM_ADD_PROPERTY(ListView, headerView);
			TITANIUM_ADD_PROPERTY(ListView, searchView);

			TITANIUM_ADD_PROPERTY(ListView, caseInsensitiveSearch);
			TITANIUM_ADD_PROPERTY_READONLY(ListView, sectionCount);
			TITANIUM_ADD_PROPERTY(ListView, showVerticalScrollIndicator);
			TITANIUM_ADD_PROPERTY(ListView, separatorColor);
			TITANIUM_ADD_PROPERTY(ListView, defaultItemTemplate);

			TITANIUM_ADD_FUNCTION(ListView, scrollToItem);
			TITANIUM_ADD_FUNCTION(ListView, appendSection);
			TITANIUM_ADD_FUNCTION(ListView, deleteSectionAt);
			TITANIUM_ADD_FUNCTION(ListView, insertSectionAt);
			TITANIUM_ADD_FUNCTION(ListView, replaceSectionAt);
			TITANIUM_ADD_FUNCTION(ListView, addMarker);
			TITANIUM_ADD_FUNCTION(ListView, setMarker);
			TITANIUM_ADD_FUNCTION(ListView, getTemplates);
			TITANIUM_ADD_FUNCTION(ListView, setTemplates);
			TITANIUM_ADD_FUNCTION(ListView, getSections);
			TITANIUM_ADD_FUNCTION(ListView, setSections);
			TITANIUM_ADD_FUNCTION(ListView, getFooterTitle);
			TITANIUM_ADD_FUNCTION(ListView, setFooterTitle);
			TITANIUM_ADD_FUNCTION(ListView, getFooterView);
			TITANIUM_ADD_FUNCTION(ListView, setFooterView);
			TITANIUM_ADD_FUNCTION(ListView, getHeaderTitle);
			TITANIUM_ADD_FUNCTION(ListView, setHeaderTitle);
			TITANIUM_ADD_FUNCTION(ListView, getHeaderView);
			TITANIUM_ADD_FUNCTION(ListView, setHeaderView);
			TITANIUM_ADD_FUNCTION(ListView, getSearchView);
			TITANIUM_ADD_FUNCTION(ListView, setSearchView);
			TITANIUM_ADD_FUNCTION(ListView, getSearchText);
			TITANIUM_ADD_FUNCTION(ListView, setSearchText);
			TITANIUM_ADD_FUNCTION(ListView, getCaseInsensitiveSearch);
			TITANIUM_ADD_FUNCTION(ListView, setCaseInsensitiveSearch);
			TITANIUM_ADD_FUNCTION(ListView, getSectionCount);
			TITANIUM_ADD_FUNCTION(ListView, getShowVerticalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ListView, setShowVerticalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ListView, getSeparatorColor);
			TITANIUM_ADD_FUNCTION(ListView, setSeparatorColor);
			TITANIUM_ADD_FUNCTION(ListView, getDefaultItemTemplate);
			TITANIUM_ADD_FUNCTION(ListView, setDefaultItemTemplate);
		}

		TITANIUM_PROPERTY_GETTER(ListView, sections)
		{
			std::vector<JSValue> js_sections;
			const auto sections = get_sections();
			for (auto section : sections) {
				js_sections.push_back(section->get_object());
			}
			return get_context().CreateArray(js_sections);
		}

		TITANIUM_PROPERTY_SETTER(ListView, sections)
		{
			if (!argument.IsObject()) {
				return false;
			}
			const auto sections = static_cast<JSObject>(argument);
			if (!sections.IsArray()) {
				return false;
			}
			set_sections(static_cast<JSArray>(sections).GetPrivateItems<ListSection>());
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, sectionCount)
		{
			return get_context().CreateNumber(static_cast<uint32_t>(get_sectionCount()));
		}

		TITANIUM_PROPERTY_GETTER(ListView, footerTitle)
		{
			return get_context().CreateString(get_footerTitle());
		}

		TITANIUM_PROPERTY_SETTER(ListView, footerTitle)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_footerTitle(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, headerTitle)
		{
			return get_context().CreateString(get_headerTitle());
		}

		TITANIUM_PROPERTY_SETTER(ListView, headerTitle)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_headerTitle(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, footerView)
		{
			auto view = get_footerView();
			if (view) {
				return view->get_object();
			}  else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_PROPERTY_SETTER(ListView, footerView)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_footerView(static_cast<JSObject>(argument).GetPrivate<View>());
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, headerView)
		{
			auto view = get_headerView();
			if (view) {
				return view->get_object();
			}  else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_PROPERTY_SETTER(ListView, headerView)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_headerView(static_cast<JSObject>(argument).GetPrivate<View>());
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, searchView)
		{
			auto view = get_searchView();
			if (view) {
				return view->get_object();
			}  else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_PROPERTY_SETTER(ListView, searchView)
		{
			if (argument.IsObject()) {
				set_searchView(static_cast<JSObject>(argument).GetPrivate<SearchBar>());
			} else {
				set_searchView(nullptr);
			}
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, searchText)
		{
			return get_context().CreateString(get_searchText());
		}

		TITANIUM_PROPERTY_SETTER(ListView, searchText)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_searchText(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, caseInsensitiveSearch)
		{
			return get_context().CreateBoolean(get_caseInsensitiveSearch());
		}

		TITANIUM_PROPERTY_SETTER(ListView, caseInsensitiveSearch)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_caseInsensitiveSearch(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, showVerticalScrollIndicator)
		{
			return get_context().CreateBoolean(get_showVerticalScrollIndicator());
		}

		TITANIUM_PROPERTY_SETTER(ListView, showVerticalScrollIndicator)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_showVerticalScrollIndicator(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, separatorColor)
		{
			return get_context().CreateString(get_separatorColor());
		}

		TITANIUM_PROPERTY_SETTER(ListView, separatorColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_separatorColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ListView, defaultItemTemplate)
		{
			return get_context().CreateString(get_defaultItemTemplate());
		}

		TITANIUM_PROPERTY_SETTER(ListView, defaultItemTemplate)
		{
			set_defaultItemTemplate(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION(ListView, scrollToItem)
		{
			const auto js_context = this_object.get_context();
			if (arguments.size() >= 2) {
				JSObject animation = js_context.CreateObject();

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());

				const auto sectionIndex = static_cast<uint32_t>(_0);
				const auto itemIndex    = static_cast<uint32_t>(_1);

				if (arguments.size() >= 3) {
					const auto _3 = arguments.at(2);
					if (_3.IsObject()) {
						animation = listviewAnimationProperties_ctor__.CallAsConstructor({_3});
					}
				}

				scrollToItem(sectionIndex, itemIndex, animation.GetPrivate<ListViewAnimationProperties>());
			}

			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ListView, appendSection)
		{
			const auto js_context = this_object.get_context();
			if (arguments.size() >= 1) {
				JSObject animation = js_context.CreateObject();
				std::vector<std::shared_ptr<ListSection>> sections;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto js_sections = static_cast<JSObject>(_0);

				if (js_sections.IsArray()) {
					sections = static_cast<JSArray>(js_sections).GetPrivateItems<ListSection>();
				} else {
					sections.push_back(js_sections.GetPrivate<ListSection>());
				}

				if (arguments.size() >= 2) {
					const auto _1 = arguments.at(1);
					if (_1.IsObject()) {
						animation = listviewAnimationProperties_ctor__.CallAsConstructor({_1});
					}
				}

				appendSection(sections, animation.GetPrivate<ListViewAnimationProperties>());
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ListView, deleteSectionAt)
		{
			const auto js_context = this_object.get_context();
			if (arguments.size() >= 1) {
				JSObject animation = js_context.CreateObject();

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());

				const auto sectionIndex = static_cast<uint32_t>(_0);

				if (arguments.size() >= 2) {
					const auto _1 = arguments.at(1);
					if (_1.IsObject()) {
						animation = listviewAnimationProperties_ctor__.CallAsConstructor({_1});
					}
				}
				deleteSectionAt(sectionIndex, animation.GetPrivate<ListViewAnimationProperties>());
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ListView, insertSectionAt)
		{
			const auto js_context = this_object.get_context();
			if (arguments.size() >= 2) {
				JSObject animation = js_context.CreateObject();
				std::vector<std::shared_ptr<ListSection>> sections;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto sectionIndex = static_cast<uint32_t>(_0);

				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsObject());
				const auto js_sections = static_cast<JSObject>(_1);

				if (js_sections.IsArray()) {
					sections = static_cast<JSArray>(js_sections).GetPrivateItems<ListSection>();
				} else {
					sections.push_back(js_sections.GetPrivate<ListSection>());
				}

				if (arguments.size() >= 3) {
					const auto _2 = arguments.at(2);
					if (_2.IsObject()) {
						animation = listviewAnimationProperties_ctor__.CallAsConstructor({_2});
					}
				}

				insertSectionAt(sectionIndex, sections, animation.GetPrivate<ListViewAnimationProperties>());
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ListView, replaceSectionAt)
		{
			const auto js_context = this_object.get_context();
			if (arguments.size() >= 2) {
				JSObject animation = js_context.CreateObject();
				std::vector<std::shared_ptr<ListSection>> sections;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsNumber());
				const auto sectionIndex = static_cast<uint32_t>(_0);

				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsObject());
				const auto js_sections = static_cast<JSObject>(_1);

				if (js_sections.IsArray()) {
					sections = static_cast<JSArray>(js_sections).GetPrivateItems<ListSection>();
				} else {
					sections.push_back(js_sections.GetPrivate<ListSection>());
				}

				if (arguments.size() >= 3) {
					const auto _2 = arguments.at(2);
					if (_2.IsObject()) {
						animation = listviewAnimationProperties_ctor__.CallAsConstructor({_2});
					}
				}

				replaceSectionAt(sectionIndex, sections, animation.GetPrivate<ListViewAnimationProperties>());
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ListView, addMarker)
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				addMarker(js_to_ListViewMarkerProps(static_cast<JSObject>(_0)));
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ListView, setMarker)
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				setMarker(js_to_ListViewMarkerProps(static_cast<JSObject>(_0)));
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ListView, getTemplates)
		{
			return this_object.GetProperty("templates");
		}

		TITANIUM_FUNCTION(ListView, setTemplates)
		{
			if (arguments.size() >= 1) {
				this_object.SetProperty("templates", arguments.at(0));
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(ListView, getSections, sections)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setSections, sections)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getFooterTitle, footerTitle)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setFooterTitle, footerTitle)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getFooterView, footerView)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setFooterView, footerView)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getHeaderTitle, headerTitle)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setHeaderTitle, headerTitle)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getHeaderView, headerView)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setHeaderView, headerView)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getSearchView, searchView)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setSearchView, searchView)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getSearchText, searchText)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setSearchText, searchText)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getCaseInsensitiveSearch, caseInsensitiveSearch)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setCaseInsensitiveSearch, caseInsensitiveSearch)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getSectionCount, sectionCount)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getShowVerticalScrollIndicator, showVerticalScrollIndicator)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setShowVerticalScrollIndicator, showVerticalScrollIndicator)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getSeparatorColor, separatorColor)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setSeparatorColor, separatorColor)

		TITANIUM_FUNCTION_AS_GETTER(ListView, getDefaultItemTemplate, defaultItemTemplate)
		TITANIUM_FUNCTION_AS_SETTER(ListView, setDefaultItemTemplate, defaultItemTemplate)

	} // namespace UI
} // namespace Titanium
