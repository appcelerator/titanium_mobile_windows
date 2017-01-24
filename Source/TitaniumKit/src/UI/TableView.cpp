/**
 * Titanium.UI.TableView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TableView.hpp"
#include "Titanium/UI/TableViewRow.hpp"
#include "Titanium/UI/TableViewSection.hpp"
#include "Titanium/UI/TableViewAnimationProperties.hpp"
#include "Titanium/UI/SearchBar.hpp"
#include "Titanium/detail/TiImpl.hpp"

#define CREATE_TITANIUM_UI_INSTANCE(OUT, PARAM, NAME) \
  JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue UI_property = Titanium.GetProperty("UI"); \
  TITANIUM_ASSERT(UI_property.IsObject()); \
  JSObject UI = static_cast<JSObject>(UI_property); \
  JSValue NAME##_property = UI.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  JSObject NAME##_obj = static_cast<JSObject>(NAME##_property); \
  auto OUT = NAME##_obj.CallAsConstructor(PARAM); \
  Titanium::Module::applyProperties(PARAM, OUT);

namespace Titanium
{
	namespace UI
	{
		TableView::TableView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.TableView"),
			tableviewAnimationProperties_ctor__(js_context.CreateObject(JSExport<Titanium::UI::TableViewAnimationProperties>::Class())),
			filterAttribute__(""),
			filterAnchored__(false),
			filterCaseInsensitive__(true),
			footerTitle__(""),
			headerTitle__(""),
			maxRowHeight__(0),
			minRowHeight__(0),
			rowHeight__(0),
			separatorColor__(""),
			model__(std::make_shared<ListModel<TableViewSection>>(false))

		{
			TITANIUM_LOG_INFO("TableView ctor");
		}

		std::vector<std::shared_ptr<TableViewSection>> TableView::get_sections() const TITANIUM_NOEXCEPT
		{
			return model__->get_sections();
		}

		void TableView::set_sections(const std::vector<std::shared_ptr<TableViewSection>>& sections) TITANIUM_NOEXCEPT
		{
			model__->set_sections(sections);
		}

		std::vector<JSObject> TableView::get_data() const TITANIUM_NOEXCEPT
		{
			std::vector<JSObject> data;
			const auto sections = get_sections();
			for (const auto section : sections) {
				// this indicates data is constructed from array of rows without header
				if (sections.size() == 1 && !section->hasHeader())
				{
					for (const auto row : section->get_rows())
					{
						data.push_back(row->get_data());
					}
				} else {
					data.push_back(section->get_object());
				}
			}
			return data;
		}

		void TableView::set_data(const std::vector<JSObject>& data) TITANIUM_NOEXCEPT
		{
			model__->clear();
			for (std::uint32_t i = 0; i < data.size(); i++) {
				const auto datum    = data.at(i);
				const auto section  = datum.GetPrivate<Titanium::UI::TableViewSection>();
				if (section != nullptr) {
					model__->appendSection(section);
				} else {
					// if there's no sections create new one and add rows into it.
					if (model__->empty()) {
						createEmptyTableViewSection();
					}
					auto row = datum.GetPrivate<Titanium::UI::TableViewRow>();

					// if row is not TableViewRow, create new one.
					if (row == nullptr) {
						CREATE_TITANIUM_UI_INSTANCE(js_row, datum, TableViewRow);
						row = js_row.GetPrivate<Titanium::UI::TableViewRow>();
						row->set_data(datum);
					}
					model__->first()->add(row, false);
				}
			}
		}

		void TableView::setData(const std::vector<JSObject>& data, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			set_data(data);
		}

		TITANIUM_PROPERTY_READWRITE(TableView, bool, allowsSelection)
		TITANIUM_PROPERTY_READWRITE(TableView, bool, allowsSelectionDuringEditing)
		TITANIUM_PROPERTY_READWRITE(TableView, std::string, filterAttribute)
		TITANIUM_PROPERTY_READWRITE(TableView, bool, filterAnchored)
		TITANIUM_PROPERTY_READWRITE(TableView, bool, filterCaseInsensitive)
		TITANIUM_PROPERTY_READWRITE(TableView, std::string, footerTitle)
		TITANIUM_PROPERTY_READWRITE(TableView, std::shared_ptr<View>, footerView)
		TITANIUM_PROPERTY_READWRITE(TableView, std::string, headerTitle)
		TITANIUM_PROPERTY_READWRITE(TableView, std::shared_ptr<View>, headerView)
		TITANIUM_PROPERTY_READWRITE(TableView, double, maxRowHeight)
		TITANIUM_PROPERTY_READWRITE(TableView, double, minRowHeight)
		TITANIUM_PROPERTY_READWRITE(TableView, double, rowHeight)
		TITANIUM_PROPERTY_READWRITE(TableView, std::string, separatorColor)
		TITANIUM_PROPERTY_READ(TableView, std::shared_ptr<SearchBar>, search)
		void TableView::set_search(const std::shared_ptr<SearchBar>& search) TITANIUM_NOEXCEPT
		{
			search__ = search;
			search__->set_querySubmitted([this](const std::string& query) {
				querySubmitted(query);
			});
			search__->set_suggestionRequested([this](const std::string& query) {
				return suggestionRequested(query);
			});
		}

		void TableView::querySubmitted(const std::string& query)
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

			std::vector<std::shared_ptr<TableViewSection>> sections;
			std::vector<std::tuple<size_t, size_t>> saved_position;

			// Create new section to show the result
			JSObject param = get_context().CreateObject();
			CREATE_TITANIUM_UI_INSTANCE(js_section, param, TableViewSection);
			auto section = js_section.GetPrivate<TableViewSection>();
			const auto saved_sections = model__->get_saved_sections();
			for (size_t sectionIndex = 0; sectionIndex < saved_sections.size(); sectionIndex++) {
				const auto savedItems = saved_sections.at(sectionIndex)->get_rows();
				for (size_t itemIndex = 0; itemIndex < savedItems.size(); itemIndex++) {
					const auto row = savedItems.at(itemIndex);
					if (row->contains(query)) {
						// Save "original" position so we can search it easily later on
						saved_position.push_back(std::make_tuple(sectionIndex, itemIndex));
						section->add(row);
					}
				}
			}

			model__->save_positions(saved_position);
			sections.push_back(section);
			set_sections(sections);
		}

		std::vector<std::string> TableView::suggestionRequested(const std::string& query)
		{
			if (!model__->isSaved()) {
				model__->save();
			}

			std::vector<std::string> suggestions;
			for (const auto section : model__->get_saved_sections()) {
				for (const auto row : section->get_rows()) {
					if (row->contains(query)) {
						suggestions.push_back(row->get_title());
					}
				}
			}
			return suggestions;
		}

		std::uint32_t TableView::get_sectionCount() const TITANIUM_NOEXCEPT
		{
			return model__->get_sectionCount();
		}

		void TableView::createEmptyTableViewSection()
		{
			const auto properties = get_context().CreateObject();
			CREATE_TITANIUM_UI_INSTANCE(js_section, properties, TableViewSection);
			model__->appendSection(js_section.GetPrivate<Titanium::UI::TableViewSection>());
		}

		void TableView::appendRow(const std::vector<std::shared_ptr<TableViewRow>>& rows, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			// create new section if there's no one
			if (model__->empty()) {
				createEmptyTableViewSection();
			}

			appendRowAtSection(static_cast<std::uint32_t>(model__->get_sectionCount() - 1), rows);
		}

		void TableView::appendRowAtSection(const std::uint32_t& sectionIndex, const std::vector<std::shared_ptr<TableViewRow>>& rows) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(model__->get_sectionCount() > sectionIndex);

			std::shared_ptr<Titanium::UI::TableViewSection> section = model__->getSectionAtIndex(sectionIndex);
			for (const auto row : rows) {
				section->add(row);
			}
		}

		void TableView::appendSection(const std::vector<std::shared_ptr<TableViewSection>>& sections, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			for (const auto section : sections) {
				model__->appendSection(section);
			}
		}

		ListRowSearchResult TableView::searchRowByIndex(const std::uint32_t& index) TITANIUM_NOEXCEPT
		{
			ListRowSearchResult result;
			std::uint32_t sectionIndex = 0;
			std::uint32_t rowCount = 0;
			for (const auto section : model__->get_sections()) {
				auto sectionRowCount = section->get_rowCount();
				if (sectionRowCount + rowCount > index) {
					std::uint32_t rowIndexInSection = index - rowCount;
					if (section->get_rowCount() > rowIndexInSection) {
						result.found = true;
						result.rowIndex = rowIndexInSection;
						break;
					}
				} else {
					rowCount += sectionRowCount;
				}
				sectionIndex++;
			}
			result.sectionIndex = sectionIndex;
			return result;
		}

		void TableView::deleteRow(const std::uint32_t& index, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			const auto result = searchRowByIndex(index);
			if (result.found) {
				model__->getSectionAtIndex(result.sectionIndex)->remove(result.rowIndex);
			}
		}

		void TableView::deleteRow(const std::shared_ptr<TableViewRow>& row, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			for (const auto section : model__->get_sections()) {
				if (section->remove(row)) {
					break;
				}
			}
		}

		void TableView::deleteSection(const uint32_t& sectionIndex, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			model__->deleteSectionAt(sectionIndex);
		}

		void TableView::insertRowAfter(const uint32_t& index, const std::shared_ptr<TableViewRow>& row, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			const auto result = searchRowByIndex(index);
			if (result.found) {
				model__->getSectionAtIndex(result.sectionIndex)->add(row, result.rowIndex + 1);
			}
		}

		void TableView::insertSectionAfter(const uint32_t& index, const std::shared_ptr<TableViewSection>& section, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			model__->insertSectionAfter(index, { section });
		}

		void TableView::insertRowBefore(const uint32_t& index, const std::shared_ptr<TableViewRow>& row, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			const auto result = searchRowByIndex(index);
			if (result.found) {
				model__->getSectionAtIndex(result.sectionIndex)->add(row, result.rowIndex);
			}
		}

		void TableView::insertSectionBefore(const uint32_t& index, const std::shared_ptr<TableViewSection>& section, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			model__->insertSectionBefore(index, { section });
		}

		void TableView::scrollToIndex(const uint32_t& index, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TableView::scrollToIndex: Unimplemented");
		}

		void TableView::scrollToTop(const uint32_t& top, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TableView::scrollToTop: Unimplemented");
		}

		void TableView::selectRow(const uint32_t& row) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TableView::selectRow: Unimplemented");
		}

		void TableView::deselectRow(const uint32_t& row) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TableView::deselectRow: Unimplemented");
		}

		void TableView::updateRow(const uint32_t& index, const std::shared_ptr<TableViewRow>& row, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			const auto result = searchRowByIndex(index);
			if (result.found) {
				model__->getSectionAtIndex(result.sectionIndex)->update(result.rowIndex, row);
			}
		}

		void TableView::updateSection(const uint32_t& index, const std::shared_ptr<TableViewSection>& section, const std::shared_ptr<TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			model__->updateSection(index, section);
		}

		void TableView::fireTableViewSectionEvent(const std::string& name, const std::shared_ptr<TableViewSection>& section, const std::shared_ptr<TableViewRow>& row, const std::uint32_t& rowIndex, const std::shared_ptr<TableViewRow>& old_row)
		{
			const auto ctx = get_context();
			auto event_args = ctx.CreateObject();
			event_args.SetProperty("section", get_object());
			event_args.SetProperty("index", ctx.CreateNumber(rowIndex));

			fireEvent(name, event_args);
		}

		void TableView::JSExportInitialize()
		{
			JSExport<TableView>::SetClassVersion(1);
			JSExport<TableView>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(TableView, data);
			TITANIUM_ADD_FUNCTION(TableView, getData);
			TITANIUM_ADD_FUNCTION(TableView, setData);

			TITANIUM_ADD_PROPERTY(TableView, allowsSelection);
			TITANIUM_ADD_PROPERTY(TableView, allowsSelectionDuringEditing);
			TITANIUM_ADD_PROPERTY(TableView, filterAttribute);
			TITANIUM_ADD_PROPERTY(TableView, filterAnchored);
			TITANIUM_ADD_PROPERTY(TableView, filterCaseInsensitive);
			TITANIUM_ADD_PROPERTY(TableView, footerTitle);
			TITANIUM_ADD_PROPERTY(TableView, footerView);
			TITANIUM_ADD_PROPERTY(TableView, headerTitle);
			TITANIUM_ADD_PROPERTY(TableView, headerView);
			TITANIUM_ADD_PROPERTY(TableView, maxRowHeight);
			TITANIUM_ADD_PROPERTY(TableView, minRowHeight);
			TITANIUM_ADD_PROPERTY(TableView, rowHeight);
			TITANIUM_ADD_PROPERTY(TableView, search);
			TITANIUM_ADD_PROPERTY_READONLY(TableView, sectionCount);
			TITANIUM_ADD_PROPERTY(TableView, sections);
			TITANIUM_ADD_PROPERTY(TableView, separatorColor);

			TITANIUM_ADD_FUNCTION(TableView, appendRow);
			TITANIUM_ADD_FUNCTION(TableView, appendSection);
			TITANIUM_ADD_FUNCTION(TableView, deleteRow);
			TITANIUM_ADD_FUNCTION(TableView, deleteSection);
			TITANIUM_ADD_FUNCTION(TableView, insertRowAfter);
			TITANIUM_ADD_FUNCTION(TableView, insertSectionAfter);
			TITANIUM_ADD_FUNCTION(TableView, insertRowBefore);
			TITANIUM_ADD_FUNCTION(TableView, insertSectionBefore);
			TITANIUM_ADD_FUNCTION(TableView, scrollToIndex);
			TITANIUM_ADD_FUNCTION(TableView, scrollToTop);
			TITANIUM_ADD_FUNCTION(TableView, selectRow);
			TITANIUM_ADD_FUNCTION(TableView, deselectRow);
			TITANIUM_ADD_FUNCTION(TableView, updateRow);
			TITANIUM_ADD_FUNCTION(TableView, updateSection);
			TITANIUM_ADD_FUNCTION(TableView, getAllowsSelection);
			TITANIUM_ADD_FUNCTION(TableView, setAllowsSelection);
			TITANIUM_ADD_FUNCTION(TableView, getAllowsSelectionDuringEditing);
			TITANIUM_ADD_FUNCTION(TableView, setAllowsSelectionDuringEditing);
			TITANIUM_ADD_FUNCTION(TableView, getFilterAttribute);
			TITANIUM_ADD_FUNCTION(TableView, setFilterAttribute);
			TITANIUM_ADD_FUNCTION(TableView, getFilterAnchored);
			TITANIUM_ADD_FUNCTION(TableView, setFilterAnchored);
			TITANIUM_ADD_FUNCTION(TableView, getFilterCaseInsensitive);
			TITANIUM_ADD_FUNCTION(TableView, setFilterCaseInsensitive);
			TITANIUM_ADD_FUNCTION(TableView, getFooterTitle);
			TITANIUM_ADD_FUNCTION(TableView, setFooterTitle);
			TITANIUM_ADD_FUNCTION(TableView, getFooterView);
			TITANIUM_ADD_FUNCTION(TableView, setFooterView);
			TITANIUM_ADD_FUNCTION(TableView, getHeaderTitle);
			TITANIUM_ADD_FUNCTION(TableView, setHeaderTitle);
			TITANIUM_ADD_FUNCTION(TableView, getHeaderView);
			TITANIUM_ADD_FUNCTION(TableView, setHeaderView);
			TITANIUM_ADD_FUNCTION(TableView, getMaxRowHeight);
			TITANIUM_ADD_FUNCTION(TableView, setMaxRowHeight);
			TITANIUM_ADD_FUNCTION(TableView, getMinRowHeight);
			TITANIUM_ADD_FUNCTION(TableView, setMinRowHeight);
			TITANIUM_ADD_FUNCTION(TableView, getRowHeight);
			TITANIUM_ADD_FUNCTION(TableView, setRowHeight);
			TITANIUM_ADD_FUNCTION(TableView, getSearch);
			TITANIUM_ADD_FUNCTION(TableView, setSearch);
			TITANIUM_ADD_FUNCTION(TableView, getSectionCount);
			TITANIUM_ADD_FUNCTION(TableView, getSections);
			TITANIUM_ADD_FUNCTION(TableView, setSections);
			TITANIUM_ADD_FUNCTION(TableView, getSeparatorColor);
			TITANIUM_ADD_FUNCTION(TableView, setSeparatorColor);
		}

		TITANIUM_PROPERTY_GETTER(TableView, data)
		{
			std::vector<JSValue> data_array;
			const auto rows = get_data();
			for (auto row : rows) {
				data_array.push_back(row);
			}
			return get_context().CreateArray(data_array);
		}

		TITANIUM_PROPERTY_SETTER(TableView, data)
		{
			TITANIUM_ASSERT(argument.IsObject());

			auto data_obj = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(data_obj.IsArray());
			auto data = static_cast<JSArray>(data_obj);
			const auto length = data.GetLength();
			std::vector<JSObject> tableObjects;
			tableObjects.reserve(length);
			for (std::size_t i = 0; i < length; i++) {
				tableObjects.push_back(static_cast<JSObject>(data.GetProperty(i)));
			}
			set_data(tableObjects);

			return true;
		}

		TITANIUM_PROPERTY_GETTER_BOOL(TableView, allowsSelection)
		TITANIUM_PROPERTY_SETTER_BOOL(TableView, allowsSelection)
		TITANIUM_PROPERTY_GETTER_BOOL(TableView, allowsSelectionDuringEditing)
		TITANIUM_PROPERTY_SETTER_BOOL(TableView, allowsSelectionDuringEditing)

		TITANIUM_PROPERTY_GETTER_STRING(TableView, filterAttribute)
		TITANIUM_PROPERTY_SETTER_STRING(TableView, filterAttribute)
		TITANIUM_PROPERTY_GETTER_BOOL(TableView, filterAnchored)
		TITANIUM_PROPERTY_SETTER_BOOL(TableView, filterAnchored)
		TITANIUM_PROPERTY_GETTER_BOOL(TableView, filterCaseInsensitive)
		TITANIUM_PROPERTY_SETTER_BOOL(TableView, filterCaseInsensitive)
		TITANIUM_PROPERTY_GETTER_STRING(TableView, footerTitle)
		TITANIUM_PROPERTY_SETTER_STRING(TableView, footerTitle)
		TITANIUM_PROPERTY_GETTER_OBJECT(TableView, footerView)
		TITANIUM_PROPERTY_SETTER_OBJECT(TableView, footerView, View)
		TITANIUM_PROPERTY_GETTER_STRING(TableView, headerTitle)
		TITANIUM_PROPERTY_SETTER_STRING(TableView, headerTitle)
		TITANIUM_PROPERTY_GETTER_OBJECT(TableView, headerView)
		TITANIUM_PROPERTY_SETTER_OBJECT(TableView, headerView, View)
		TITANIUM_PROPERTY_GETTER_DOUBLE(TableView, maxRowHeight)
		TITANIUM_PROPERTY_SETTER_DOUBLE(TableView, maxRowHeight)
		TITANIUM_PROPERTY_GETTER_DOUBLE(TableView, minRowHeight)
		TITANIUM_PROPERTY_SETTER_DOUBLE(TableView, minRowHeight)
		TITANIUM_PROPERTY_GETTER_DOUBLE(TableView, rowHeight)
		TITANIUM_PROPERTY_SETTER_DOUBLE(TableView, rowHeight)

		TITANIUM_PROPERTY_GETTER(TableView, search)
		{
			const auto bar = get_search();
			if (bar) {
				return bar->get_object();
			}
			return get_context().CreateNull();
		}
		TITANIUM_PROPERTY_SETTER(TableView, search)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_search(static_cast<JSObject>(argument).GetPrivate<SearchBar>());
			return true;
		}

		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(TableView, sections)
		TITANIUM_PROPERTY_SETTER_OBJECT_ARRAY(TableView, sections, TableViewSection)
		TITANIUM_PROPERTY_GETTER_UINT(TableView, sectionCount)
		TITANIUM_PROPERTY_GETTER_STRING(TableView, separatorColor)
		TITANIUM_PROPERTY_SETTER_STRING(TableView, separatorColor)

		TITANIUM_FUNCTION(TableView, appendRow)
		{
			const auto js_context = this_object.get_context();

			if (arguments.size() >= 1) {
				JSObject animation = js_context.CreateObject();
				std::vector<std::shared_ptr<TableViewRow>> rows;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto params = static_cast<JSObject>(_0);

				if (params.IsArray()) {
					const auto js_rows_array = static_cast<JSArray>(params);
					for (uint32_t i = 0; i < js_rows_array.GetLength(); i++) {
						auto item = js_rows_array.GetProperty(i);
						// appendRow accepts array of TableViewRow or JS Dictionary Object
						if (item.IsObject()) {
							const auto item_obj = static_cast<JSObject>(item);
							const auto row = item_obj.GetPrivate<TableViewRow>();
							if (row) {
								rows.push_back(row);
							} else {
								CREATE_TITANIUM_UI_INSTANCE(newrow, item_obj, TableViewRow);
								rows.push_back(newrow.GetPrivate<TableViewRow>());
							}
						}
					}

				} else {
					auto row = params.GetPrivate<TableViewRow>();
					if (row) {
						rows.push_back(row);
					} else {
						CREATE_TITANIUM_UI_INSTANCE(newrow, params, TableViewRow);
						rows.push_back(newrow.GetPrivate<TableViewRow>());
					}
				}

				if (arguments.size() >= 2) {
					const auto _1 = arguments.at(1);
					if (_1.IsObject()) {
						animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_1});
					}
				}

				appendRow(rows, animation.GetPrivate<TableViewAnimationProperties>());
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, appendSection)
		{
			const auto js_context = this_object.get_context();

			if (arguments.size() >= 1) {
				JSObject animation = js_context.CreateObject();
				std::vector<std::shared_ptr<TableViewSection>> sections;

				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto js_sections = static_cast<JSObject>(_0);

				if (js_sections.IsArray()) {
					sections = static_cast<JSArray>(js_sections).GetPrivateItems<TableViewSection>();
				} else {
					sections.push_back(js_sections.GetPrivate<TableViewSection>());
				}

				if (arguments.size() >= 2) {
					const auto _1 = arguments.at(1);
					if (_1.IsObject()) {
						animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_1});
					}
				}

				appendSection(sections, animation.GetPrivate<TableViewAnimationProperties>());
			}
			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, deleteRow)
		{
			const auto js_context = this_object.get_context();

			ENSURE_ARGUMENT_BOUNDS(0);
			const auto _0 = arguments.at(0);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 2) {
				const auto _1 = arguments.at(1);
				if (_1.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_1});
				}
			}

			if (_0.IsNumber()) {
				deleteRow(static_cast<std::uint32_t>(_0), animation.GetPrivate<TableViewAnimationProperties>());
			} else if (_0.IsObject()) {
				deleteRow(static_cast<JSObject>(_0).GetPrivate<TableViewRow>(), animation.GetPrivate<TableViewAnimationProperties>());
			}

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, deleteSection)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(sectionIndex, 0);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 2) {
				const auto _1 = arguments.at(1);
				if (_1.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_1});
				}
			}

			deleteSection(sectionIndex, animation.GetPrivate<TableViewAnimationProperties>());

			return this_object.get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, insertRowAfter)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(rowIndex, 0);
			ENSURE_OBJECT_AT_INDEX(js_row, 1);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 3) {
				const auto _2 = arguments.at(2);
				if (_2.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_2});
				}
			}

			auto row = js_row.GetPrivate<TableViewRow>();
			if (row == nullptr) {
				// create new row, assuming js_row is JS dictionary object
				CREATE_TITANIUM_UI_INSTANCE(new_row, js_row, TableViewRow);
				row = new_row.GetPrivate<Titanium::UI::TableViewRow>();
			}

			insertRowAfter(rowIndex, row, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, insertSectionAfter)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(sectionIndex, 0);
			ENSURE_OBJECT_AT_INDEX(js_section, 1);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 3) {
				const auto _2 = arguments.at(2);
				if (_2.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_2});
				}
			}

			auto section = js_section.GetPrivate<TableViewSection>();
			if (section == nullptr) {
				// create new section, assuming js_section is JS dictionary object
				CREATE_TITANIUM_UI_INSTANCE(new_section, js_section, TableViewSection);
				section = new_section.GetPrivate<Titanium::UI::TableViewSection>();
			}

			insertSectionAfter(sectionIndex, section, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, insertRowBefore)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(rowIndex, 0);
			ENSURE_OBJECT_AT_INDEX(js_row, 1);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 3) {
				const auto _2 = arguments.at(2);
				if (_2.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_2});
				}
			}

			auto row = js_row.GetPrivate<TableViewRow>();
			if (row == nullptr) {
				// create new row, assuming js_row is JS dictionary object
				CREATE_TITANIUM_UI_INSTANCE(new_row, js_row, TableViewRow);
				row = new_row.GetPrivate<Titanium::UI::TableViewRow>();
			}

			insertRowBefore(rowIndex, row, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, insertSectionBefore)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(sectionIndex, 0);
			ENSURE_OBJECT_AT_INDEX(js_section, 1);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 3) {
				const auto _2 = arguments.at(2);
				if (_2.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_2});
				}
			}

			auto section = js_section.GetPrivate<TableViewSection>();
			if (section == nullptr) {
				// create new section, assuming js_section is JS dictionary object
				CREATE_TITANIUM_UI_INSTANCE(new_section, js_section, TableViewSection);
				section = new_section.GetPrivate<Titanium::UI::TableViewSection>();
			}

			insertSectionBefore(sectionIndex, section, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, scrollToIndex)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(index, 0);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 2) {
				const auto _1 = arguments.at(1);
				if (_1.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_1});
				}
			}

			scrollToIndex(index, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, scrollToTop)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(index, 0);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 2) {
				const auto _1 = arguments.at(1);
				if (_1.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_1});
				}
			}

			scrollToTop(index, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, selectRow)
		{
			ENSURE_UINT_AT_INDEX(index, 0);
			selectRow(index);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, deselectRow)
		{
			ENSURE_UINT_AT_INDEX(index, 0);
			deselectRow(index);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, updateRow)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(rowIndex, 0);
			ENSURE_OBJECT_AT_INDEX(js_row, 1);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 3) {
				const auto _2 = arguments.at(2);
				if (_2.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_2});
				}
			}

			auto row = js_row.GetPrivate<TableViewRow>();
			if (row == nullptr) {
				// create new row, assuming js_row is JS dictionary object
				CREATE_TITANIUM_UI_INSTANCE(new_row, js_row, TableViewRow);
				row = new_row.GetPrivate<Titanium::UI::TableViewRow>();
			}

			updateRow(rowIndex, row, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableView, updateSection)
		{
			const auto js_context = this_object.get_context();

			ENSURE_UINT_AT_INDEX(sectionIndex, 0);
			ENSURE_OBJECT_AT_INDEX(js_section, 1);

			JSObject animation = js_context.CreateObject();
			if (arguments.size() >= 3) {
				const auto _2 = arguments.at(2);
				if (_2.IsObject()) {
					animation = tableviewAnimationProperties_ctor__.CallAsConstructor({_2});
				}
			}

			auto section = js_section.GetPrivate<TableViewSection>();
			if (section == nullptr) {
				// create new section, assuming js_section is JS dictionary object
				CREATE_TITANIUM_UI_INSTANCE(new_section, js_section, TableViewSection);
				section = new_section.GetPrivate<Titanium::UI::TableViewSection>();
			}

			updateSection(sectionIndex, section, animation.GetPrivate<TableViewAnimationProperties>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(TableView, getAllowsSelection, allowsSelection)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setAllowsSelection, allowsSelection)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getAllowsSelectionDuringEditing, allowsSelectionDuringEditing)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setAllowsSelectionDuringEditing, allowsSelectionDuringEditing)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getData, data)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setData, data)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getFilterAttribute, filterAttribute)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setFilterAttribute, filterAttribute)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getFilterAnchored, filterAnchored)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setFilterAnchored, filterAnchored)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getFilterCaseInsensitive, filterCaseInsensitive)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setFilterCaseInsensitive, filterCaseInsensitive)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getFooterTitle, footerTitle)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setFooterTitle, footerTitle)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getFooterView, footerView)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setFooterView, footerView)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getHeaderTitle, headerTitle)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setHeaderTitle, headerTitle)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getHeaderView, headerView)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setHeaderView, headerView)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getMaxRowHeight, maxRowHeight)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setMaxRowHeight, maxRowHeight)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getMinRowHeight, minRowHeight)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setMinRowHeight, minRowHeight)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getRowHeight, rowHeight)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setRowHeight, rowHeight)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getSearch, search)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setSearch, search)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getSectionCount, sectionCount)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getSections, search)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setSections, search)
		TITANIUM_FUNCTION_AS_GETTER(TableView, getSeparatorColor, separatorColor)
		TITANIUM_FUNCTION_AS_SETTER(TableView, setSeparatorColor, separatorColor)

	} // namespace UI
} // namespace Titanium
