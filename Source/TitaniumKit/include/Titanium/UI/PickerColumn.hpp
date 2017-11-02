/**
 * TitaniumKit Titanium.UI.PickerColumn
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_PICKERCOLUMN_HPP_
#define _TITANIUM_UI_PICKERCOLUMN_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Font.hpp"
#include <vector>

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		class PickerRow;

		/*!
		  @class
		  @discussion This is the Titanium PickerColumn Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.PickerColumn
		*/
		class TITANIUMKIT_EXPORT PickerColumn : public View, public JSExport<PickerColumn>
		{

		public:

			/*!
			  @property
			  @abstract rowCount
			  @discussion Number of rows in this column.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::uint32_t, rowCount);

			/*!
			  @property
			  @abstract rows
			  @discussion Rows of this column.
			*/
			TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::vector<std::shared_ptr<PickerRow>>, rows);

			/*!
			  @property
			  @abstract selectedRow
			  @discussion The selected row in this column.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<PickerRow>, selectedRow);

			/*!
			  @property
			  @abstract font
			  @discussion Font to use for text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Font, font);

			/*!
			  @method
			  @abstract addRow
			  @discussion Adds a row to this column.
			*/
			virtual void addRow(const std::shared_ptr<PickerRow>& row) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract removeRow
			  @discussion Removes a row from this column.
			*/
			virtual void removeRow(const std::shared_ptr<PickerRow>& row) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract reload
			  @discussion reload this column.
			*/
			virtual void reload() TITANIUM_NOEXCEPT;

			PickerColumn(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~PickerColumn()                      = default;
			PickerColumn(const PickerColumn&)            = default;
			PickerColumn& operator=(const PickerColumn&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			PickerColumn(PickerColumn&&)                 = default;
			PickerColumn& operator=(PickerColumn&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(rowCount);
			TITANIUM_PROPERTY_READONLY_DEF(rows);
			TITANIUM_PROPERTY_DEF(selectedRow);
			TITANIUM_PROPERTY_DEF(font);

			TITANIUM_FUNCTION_DEF(addRow);
			TITANIUM_FUNCTION_DEF(removeRow);
			TITANIUM_FUNCTION_DEF(getRowCount);
			TITANIUM_FUNCTION_DEF(getRows);
			TITANIUM_FUNCTION_DEF(getSelectedRow);
			TITANIUM_FUNCTION_DEF(setSelectedRow);
			TITANIUM_FUNCTION_DEF(getFont);
			TITANIUM_FUNCTION_DEF(setFont);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::vector<std::shared_ptr<PickerRow>> rows__;
			std::shared_ptr<PickerRow> selectedRow__;
			Font font__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_PICKERCOLUMN_HPP_