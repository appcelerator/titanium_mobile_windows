/**
 * TitaniumKit Titanium.UI.PickerColumn
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/PickerColumn.hpp"
#include "Titanium/UI/PickerRow.hpp"

namespace Titanium
{
	namespace UI
	{

		PickerColumn::PickerColumn(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.PickerColumn")
			, selectedRow__(nullptr)
		{
		}

		std::uint32_t PickerColumn::get_rowCount() const TITANIUM_NOEXCEPT
		{
			return static_cast<std::uint32_t>(rows__.size());
		}

		TITANIUM_PROPERTY_READ(PickerColumn, std::vector<std::shared_ptr<PickerRow>>, rows)
		TITANIUM_PROPERTY_READWRITE(PickerColumn, std::shared_ptr<PickerRow>, selectedRow)
		TITANIUM_PROPERTY_READWRITE(PickerColumn, Font, font)

		void PickerColumn::addRow(const std::shared_ptr<PickerRow>& row) TITANIUM_NOEXCEPT
		{
			rows__.push_back(row);
		}

		void PickerColumn::removeRow(const std::shared_ptr<PickerRow>& row) TITANIUM_NOEXCEPT
		{
			const auto it = std::find(rows__.begin(), rows__.end(), row);
			if (it != rows__.end()) {
				rows__.erase(it);
			}
		}

		void PickerColumn::reload() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("PickerColumn::reload() is not implemented");
		}

		void PickerColumn::JSExportInitialize()
		{
			JSExport<PickerColumn>::SetClassVersion(1);
			JSExport<PickerColumn>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(PickerColumn, rowCount);
			TITANIUM_ADD_PROPERTY_READONLY(PickerColumn, rows);
			TITANIUM_ADD_PROPERTY(PickerColumn, selectedRow);
			TITANIUM_ADD_PROPERTY(PickerColumn, font);

			TITANIUM_ADD_FUNCTION(PickerColumn, addRow);
			TITANIUM_ADD_FUNCTION(PickerColumn, removeRow);
			TITANIUM_ADD_FUNCTION(PickerColumn, getRowCount);
			TITANIUM_ADD_FUNCTION(PickerColumn, getRows);
			TITANIUM_ADD_FUNCTION(PickerColumn, getSelectedRow);
			TITANIUM_ADD_FUNCTION(PickerColumn, setSelectedRow);
			TITANIUM_ADD_FUNCTION(PickerColumn, getFont);
			TITANIUM_ADD_FUNCTION(PickerColumn, setFont);
		}

		TITANIUM_PROPERTY_GETTER_UINT(PickerColumn, rowCount)
		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(PickerColumn, rows)
		TITANIUM_PROPERTY_GETTER_OBJECT(PickerColumn, selectedRow)
		TITANIUM_PROPERTY_SETTER_OBJECT(PickerColumn, selectedRow, PickerRow)

		TITANIUM_PROPERTY_GETTER_STRUCT(PickerColumn, font, Font)
		TITANIUM_PROPERTY_SETTER_STRUCT(PickerColumn, font, Font)

		TITANIUM_FUNCTION(PickerColumn, addRow)
		{
			ENSURE_OBJECT_AT_INDEX(row_object, 0);
			const auto row = row_object.GetPrivate<PickerRow>();
			if (row) {
				addRow(row);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(PickerColumn, removeRow)
		{
			ENSURE_OBJECT_AT_INDEX(row_object, 0);
			const auto row = row_object.GetPrivate<PickerRow>();
			if (row) {
				removeRow(row);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(PickerColumn, getRowCount, rowCount)
		TITANIUM_FUNCTION_AS_GETTER(PickerColumn, getRows, rows)
		TITANIUM_FUNCTION_AS_GETTER(PickerColumn, getSelectedRow, selectedRow)
		TITANIUM_FUNCTION_AS_SETTER(PickerColumn, setSelectedRow, selectedRow)
		TITANIUM_FUNCTION_AS_GETTER(PickerColumn, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(PickerColumn, setFont, font)

	} // namespace UI
} // namespace Titanium
