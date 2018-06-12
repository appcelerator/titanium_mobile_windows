/**
 * Titanium.UI.TableViewSection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TableViewSection.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/UI/TableView.hpp"
#include "Titanium/UI/TableViewRow.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		TableViewSection::TableViewSection(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.TableViewSection"),
			footerTitle__(""),
			headerTitle__("")
		{
			TITANIUM_LOG_INFO("Titanium::UI::TableViewSection ctor");
		}

		TITANIUM_PROPERTY_READWRITE(TableViewSection, std::string, footerTitle)
		TITANIUM_PROPERTY_READWRITE(TableViewSection, std::shared_ptr<View>, footerView)
		TITANIUM_PROPERTY_READWRITE(TableViewSection, std::string, headerTitle)
		TITANIUM_PROPERTY_READWRITE(TableViewSection, std::shared_ptr<View>, headerView)
		TITANIUM_PROPERTY_READ(TableViewSection, std::vector<std::shared_ptr<TableViewRow>>, rows)

		std::shared_ptr<TableViewRow> TableViewSection::MakeSafeRowCopy(const JSContext& ctx, const std::shared_ptr<TableViewRow>& row) TITANIUM_NOEXCEPT
		{
			if (!row->get_added()) {
				return row;
			}
			JSValue Titanium_property = ctx.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());
			JSObject Titanium = static_cast<JSObject>(Titanium_property);
			JSValue UI_property = Titanium.GetProperty("UI");
			TITANIUM_ASSERT(UI_property.IsObject());
			JSObject UI = static_cast<JSObject>(UI_property);
			JSValue TableViewRow_property = UI.GetProperty("TableViewRow");
			TITANIUM_ASSERT(TableViewRow_property.IsObject());
			JSObject TableViewRow_obj = static_cast<JSObject>(TableViewRow_property);
			auto js_row = TableViewRow_obj.CallAsConstructor();

			Module::applyProperties(row->getCtorProperties(), js_row);

			return js_row.GetPrivate<TableViewRow>();
		}

		std::uint32_t TableViewSection::get_rowCount() const TITANIUM_NOEXCEPT
		{
			return static_cast<std::uint32_t>(rows__.size());
		}

		void TableViewSection::add(const std::shared_ptr<TableViewRow>& row_, const bool& fireEvent) TITANIUM_NOEXCEPT
		{
			// Check if row is already added, make new row then.
			std::shared_ptr<TableViewRow> row = MakeSafeRowCopy(get_context(), row_);

			row->set_section(get_object().GetPrivate<TableViewSection>());
			row->set_added(true);
			rows__.push_back(row);
			if (fireEvent) {
				const auto index = static_cast<std::uint32_t>(rows__.size() - 1);
				fireTableViewSectionEvent("append", rows__.at(index), index);
			}
		}

		void TableViewSection::add(const std::shared_ptr<TableViewRow>& row_, const std::uint32_t& index) TITANIUM_NOEXCEPT
		{
			std::shared_ptr<TableViewRow> row = MakeSafeRowCopy(get_context(), row_);

			row->set_section(get_object().GetPrivate<TableViewSection>());
			row->set_added(true);
			rows__.insert(rows__.begin() + index, row);
			fireTableViewSectionEvent("append", rows__.at(index), index);
		}

		bool TableViewSection::remove(const std::shared_ptr<TableViewRow>& row) TITANIUM_NOEXCEPT
		{
			const auto it = find(rows__.begin(), rows__.end(), row);
			if (it != rows__.end()) {
				const auto index = static_cast<std::uint32_t>(std::distance(rows__.begin(), it));
				row->set_section(nullptr);
				row->set_added(false);
				rows__.erase(it);
				fireTableViewSectionEvent("remove", row, index);
				return true;
			} else {
				return false;
			}
		}

		bool TableViewSection::remove(const std::uint32_t& index) TITANIUM_NOEXCEPT
		{
			if (rows__.size() > index) {
				const auto row = rows__.at(index);
				row->set_section(nullptr);
				row->set_added(false);
				rows__.erase(rows__.begin() + index);
				fireTableViewSectionEvent("remove", row, index);
				return true;
			} else {
				return false;
			}
		}


		std::shared_ptr<TableViewRow> TableViewSection::rowAtIndex(const std::uint32_t& index) TITANIUM_NOEXCEPT
		{
			return rows__.at(index);
		}

		bool TableViewSection::update(const std::uint32_t& index, const std::shared_ptr<TableViewRow>& row) TITANIUM_NOEXCEPT
		{
			if (rows__.size() > index) {
				const auto old_row = rows__.at(index);
				rows__.at(index) = row;
				fireTableViewSectionEvent("update", row, index, old_row);
				return true;
			}
			else {
				return false;
			}
		}

		void TableViewSection::fireTableViewSectionEvent(const std::string& event_name, const std::shared_ptr<TableViewRow>& row, const std::uint32_t& rowIndex, const std::shared_ptr<TableViewRow>& old_row)
		{
			// return if no table view attached to this section
			if (tableView__ == nullptr) {
				return;
			}
			tableView__->fireTableViewSectionEvent(event_name, get_object().GetPrivate<TableViewSection>(), row, rowIndex, old_row);
		}

		void TableViewSection::JSExportInitialize()
		{
			JSExport<TableViewSection>::SetClassVersion(1);
			JSExport<TableViewSection>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(TableViewSection, footerTitle);
			TITANIUM_ADD_PROPERTY(TableViewSection, footerView);
			TITANIUM_ADD_PROPERTY(TableViewSection, headerTitle);
			TITANIUM_ADD_PROPERTY(TableViewSection, headerView);
			TITANIUM_ADD_PROPERTY_READONLY(TableViewSection, rowCount);
			TITANIUM_ADD_PROPERTY_READONLY(TableViewSection, rows);

			TITANIUM_ADD_FUNCTION(TableViewSection, add);
			TITANIUM_ADD_FUNCTION(TableViewSection, remove);
			TITANIUM_ADD_FUNCTION(TableViewSection, rowAtIndex);
			TITANIUM_ADD_FUNCTION(TableViewSection, getFooterTitle);
			TITANIUM_ADD_FUNCTION(TableViewSection, setFooterTitle);
			TITANIUM_ADD_FUNCTION(TableViewSection, getFooterView);
			TITANIUM_ADD_FUNCTION(TableViewSection, setFooterView);
			TITANIUM_ADD_FUNCTION(TableViewSection, getHeaderTitle);
			TITANIUM_ADD_FUNCTION(TableViewSection, setHeaderTitle);
			TITANIUM_ADD_FUNCTION(TableViewSection, getHeaderView);
			TITANIUM_ADD_FUNCTION(TableViewSection, setHeaderView);
			TITANIUM_ADD_FUNCTION(TableViewSection, getRowCount);
			TITANIUM_ADD_FUNCTION(TableViewSection, getRows);
		}

		TITANIUM_PROPERTY_GETTER_STRING(TableViewSection, footerTitle)
		TITANIUM_PROPERTY_SETTER_STRING(TableViewSection, footerTitle)
		TITANIUM_PROPERTY_GETTER_OBJECT(TableViewSection, footerView)
		TITANIUM_PROPERTY_SETTER_OBJECT(TableViewSection, footerView, View)
		TITANIUM_PROPERTY_GETTER_STRING(TableViewSection, headerTitle)
		TITANIUM_PROPERTY_SETTER_STRING(TableViewSection, headerTitle)
		TITANIUM_PROPERTY_GETTER_OBJECT(TableViewSection, headerView)
		TITANIUM_PROPERTY_SETTER_OBJECT(TableViewSection, headerView, View)
		TITANIUM_PROPERTY_GETTER_UINT(TableViewSection, rowCount)

		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(TableViewSection, rows)

		TITANIUM_FUNCTION(TableViewSection, add)
		{
			ENSURE_OBJECT_AT_INDEX(row, 0)
			add(row.GetPrivate<TableViewRow>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableViewSection, remove)
		{
			ENSURE_OBJECT_AT_INDEX(row, 0)
			remove(row.GetPrivate<TableViewRow>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TableViewSection, rowAtIndex)
		{
			ENSURE_UINT_AT_INDEX(index, 0)
			const auto row = rowAtIndex(index);
			if (row != nullptr) {
				return row->get_object();
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(TableViewSection, getFooterTitle, footerTitle)
		TITANIUM_FUNCTION_AS_SETTER(TableViewSection, setFooterTitle, footerTitle)
		TITANIUM_FUNCTION_AS_GETTER(TableViewSection, getFooterView, footerView)
		TITANIUM_FUNCTION_AS_SETTER(TableViewSection, setFooterView, footerView)
		TITANIUM_FUNCTION_AS_GETTER(TableViewSection, getHeaderTitle, headerTitle)
		TITANIUM_FUNCTION_AS_SETTER(TableViewSection, setHeaderTitle, headerTitle)
		TITANIUM_FUNCTION_AS_GETTER(TableViewSection, getHeaderView, headerView)
		TITANIUM_FUNCTION_AS_SETTER(TableViewSection, setHeaderView, headerView)
		TITANIUM_FUNCTION_AS_GETTER(TableViewSection, getRowCount, rowCount)
		TITANIUM_FUNCTION_AS_GETTER(TableViewSection, getRows, rows)
	} // namespace UI
} // namespace Titanium
