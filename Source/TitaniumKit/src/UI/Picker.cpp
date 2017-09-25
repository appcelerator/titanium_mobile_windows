/**
 * TitaniumKit Titanium.UI.Picker
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/Picker.hpp"
#include "Titanium/UI/PickerColumn.hpp"
#include "Titanium/UI/PickerRow.hpp"
#include <ctime>

namespace Titanium
{
	namespace UI
	{

		PickerDialogOption js_to_PickerDialogOption(const JSObject& object)
		{

			std::string title;
			if (object.HasProperty("title")) {
				title = static_cast<std::string>(object.GetProperty("title"));
			}
			std::string okButtonTitle;
			if (object.HasProperty("okButtonTitle")) {
				okButtonTitle = static_cast<std::string>(object.GetProperty("okButtonTitle"));
			}
			bool format24 { false };
			if (object.HasProperty("format24")) {
				format24 = static_cast<bool>(object.GetProperty("format24"));
			}
			std::chrono::system_clock::time_point value;
			if (object.HasProperty("value")) {
				const std::time_t tt = static_cast<std::uint32_t>(object.GetProperty("value"));
				value = std::chrono::system_clock::from_time_t(tt);
			}
			const auto callback_property = object.GetProperty("callback");
			const auto oncallback = [callback_property](const bool& cancel, const std::chrono::system_clock::time_point& value) {
				if (callback_property.IsObject()) {
					auto func = static_cast<JSObject>(callback_property);
					if (func.IsFunction()) {
						const auto ctx = func.get_context();
						auto evt = ctx.CreateObject();
						evt.SetProperty("cancel", ctx.CreateBoolean(cancel));

						const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch()).count();
						const std::vector<JSValue> date_args = { ctx.CreateNumber(static_cast<std::uint32_t>(msec)) };
						evt.SetProperty("value", ctx.CreateDate(date_args));

						const std::vector<JSValue> args = { evt };
						func(args, func);
					}
				}
			};

			PickerDialogOption options {
				title, okButtonTitle, format24, value, callback_property, oncallback
			};

			return options;
		}

		Picker::Picker(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.Picker")
			, countDownDuration__(0)
			, format24__(false)
			, minuteInterval__(1)
			, selectionIndicator__(false)
			, selectionOpens__(false)
			, useSpinner__(false)
			, visibleItems__(5)
			, calendarViewShown__(false)
			, type__(PICKER_TYPE::PLAIN)
		{
		}

		TITANIUM_PROPERTY_READWRITE(Picker, std::vector<std::shared_ptr<PickerColumn>>, columns)
		TITANIUM_PROPERTY_READWRITE(Picker, std::chrono::milliseconds, countDownDuration)
		TITANIUM_PROPERTY_READWRITE(Picker, bool, format24)
		TITANIUM_PROPERTY_READWRITE(Picker, std::string, locale)
		TITANIUM_PROPERTY_READWRITE(Picker, boost::optional<std::chrono::system_clock::time_point>, maxDate)
		TITANIUM_PROPERTY_READWRITE(Picker, boost::optional<std::chrono::system_clock::time_point>, minDate)
		TITANIUM_PROPERTY_READWRITE(Picker, std::chrono::minutes, minuteInterval)
		TITANIUM_PROPERTY_READWRITE(Picker, bool, selectionIndicator)
		TITANIUM_PROPERTY_READWRITE(Picker, bool, selectionOpens)
		TITANIUM_PROPERTY_READWRITE(Picker, bool, useSpinner)
		TITANIUM_PROPERTY_READWRITE(Picker, boost::optional<std::chrono::system_clock::time_point>, value)
		TITANIUM_PROPERTY_READWRITE(Picker, std::uint32_t, visibleItems)
		TITANIUM_PROPERTY_READWRITE(Picker, bool, calendarViewShown)
		TITANIUM_PROPERTY_READWRITE(Picker, Font, font)
		TITANIUM_PROPERTY_READWRITE(Picker, PICKER_TYPE, type)

		void Picker::add_columns(const std::vector<std::shared_ptr<PickerColumn>>& columns) TITANIUM_NOEXCEPT
		{
			columns__.insert(columns__.end(), columns.begin(), columns.end());
		}

		void Picker::add_rows(const std::vector<std::shared_ptr<PickerRow>>& rows) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Picker::add(rows): Unimplemented");
		}

		void Picker::reloadColumn(const std::shared_ptr<PickerColumn>& column) TITANIUM_NOEXCEPT
		{
			column->reload();
		}

		std::shared_ptr<PickerRow> Picker::getSelectedRow(const std::uint32_t& columnIndex) TITANIUM_NOEXCEPT
		{
			if (columns__.size() <= columnIndex) {
				return nullptr;
			}
			return columns__.at(columnIndex)->get_selectedRow();
		}

		void Picker::setSelectedRow(const std::uint32_t& columnIndex, const std::uint32_t& rowIndex, const bool& animated) TITANIUM_NOEXCEPT
		{
			if (columns__.size() <= columnIndex) {
				return;
			}
			const auto column = columns__.at(columnIndex);
			if (column->get_rows().size() <= rowIndex) {
				return;
			}
			column->set_selectedRow(column->get_rows().at(rowIndex));
		}

		void Picker::showDatePickerDialog(const PickerDialogOption& option)
		{
			TITANIUM_LOG_WARN("Picker::showDatePickerDialog: Unimplemented");
		}

		void Picker::showTimePickerDialog(const PickerDialogOption& option)
		{
			TITANIUM_LOG_WARN("Picker::showTimePickerDialog: Unimplemented");
		}

		void Picker::JSExportInitialize()
		{
			JSExport<Picker>::SetClassVersion(1);
			JSExport<Picker>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(Picker, columns);
			TITANIUM_ADD_PROPERTY(Picker, countDownDuration);
			TITANIUM_ADD_PROPERTY(Picker, format24);
			TITANIUM_ADD_PROPERTY(Picker, locale);
			TITANIUM_ADD_PROPERTY(Picker, maxDate);
			TITANIUM_ADD_PROPERTY(Picker, minDate);
			TITANIUM_ADD_PROPERTY(Picker, minuteInterval);
			TITANIUM_ADD_PROPERTY(Picker, selectionIndicator);
			TITANIUM_ADD_PROPERTY(Picker, selectionOpens);
			TITANIUM_ADD_PROPERTY(Picker, useSpinner);
			TITANIUM_ADD_PROPERTY(Picker, value);
			TITANIUM_ADD_PROPERTY(Picker, visibleItems);
			TITANIUM_ADD_PROPERTY(Picker, calendarViewShown);
			TITANIUM_ADD_PROPERTY(Picker, font);
			TITANIUM_ADD_PROPERTY(Picker, type);

			TITANIUM_ADD_FUNCTION(Picker, add);
			TITANIUM_ADD_FUNCTION(Picker, reloadColumn);
			TITANIUM_ADD_FUNCTION(Picker, getSelectedRow);
			TITANIUM_ADD_FUNCTION(Picker, setSelectedRow);
			TITANIUM_ADD_FUNCTION(Picker, showDatePickerDialog);
			TITANIUM_ADD_FUNCTION(Picker, showTimePickerDialog);
			TITANIUM_ADD_FUNCTION(Picker, getColumns);
			TITANIUM_ADD_FUNCTION(Picker, setColumns);
			TITANIUM_ADD_FUNCTION(Picker, getCountDownDuration);
			TITANIUM_ADD_FUNCTION(Picker, setCountDownDuration);
			TITANIUM_ADD_FUNCTION(Picker, getFormat24);
			TITANIUM_ADD_FUNCTION(Picker, setFormat24);
			TITANIUM_ADD_FUNCTION(Picker, getLocale);
			TITANIUM_ADD_FUNCTION(Picker, setLocale);
			TITANIUM_ADD_FUNCTION(Picker, getMaxDate);
			TITANIUM_ADD_FUNCTION(Picker, setMaxDate);
			TITANIUM_ADD_FUNCTION(Picker, getMinDate);
			TITANIUM_ADD_FUNCTION(Picker, setMinDate);
			TITANIUM_ADD_FUNCTION(Picker, getMinuteInterval);
			TITANIUM_ADD_FUNCTION(Picker, setMinuteInterval);
			TITANIUM_ADD_FUNCTION(Picker, getSelectionIndicator);
			TITANIUM_ADD_FUNCTION(Picker, setSelectionIndicator);
			TITANIUM_ADD_FUNCTION(Picker, getSelectionOpens);
			TITANIUM_ADD_FUNCTION(Picker, setSelectionOpens);
			TITANIUM_ADD_FUNCTION(Picker, getUseSpinner);
			TITANIUM_ADD_FUNCTION(Picker, setUseSpinner);
			TITANIUM_ADD_FUNCTION(Picker, getValue);
			TITANIUM_ADD_FUNCTION(Picker, setValue);
			TITANIUM_ADD_FUNCTION(Picker, getVisibleItems);
			TITANIUM_ADD_FUNCTION(Picker, setVisibleItems);
			TITANIUM_ADD_FUNCTION(Picker, getCalendarViewShown);
			TITANIUM_ADD_FUNCTION(Picker, setCalendarViewShown);
			TITANIUM_ADD_FUNCTION(Picker, getFont);
			TITANIUM_ADD_FUNCTION(Picker, setFont);
			TITANIUM_ADD_FUNCTION(Picker, getType);
			TITANIUM_ADD_FUNCTION(Picker, setType);
		}

		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(Picker, columns)
		TITANIUM_PROPERTY_SETTER_OBJECT_ARRAY(Picker, columns, PickerColumn)
		TITANIUM_PROPERTY_GETTER_TIME(Picker, countDownDuration)
		TITANIUM_PROPERTY_SETTER_TIME(Picker, countDownDuration)
		TITANIUM_PROPERTY_GETTER_BOOL(Picker, format24)
		TITANIUM_PROPERTY_SETTER_BOOL(Picker, format24)
		TITANIUM_PROPERTY_GETTER_STRING(Picker, locale)
		TITANIUM_PROPERTY_SETTER_STRING(Picker, locale)

		TITANIUM_PROPERTY_GETTER_DATE(Picker, maxDate)
		TITANIUM_PROPERTY_SETTER_DATE(Picker, maxDate)
		TITANIUM_PROPERTY_GETTER_DATE(Picker, minDate)
		TITANIUM_PROPERTY_SETTER_DATE(Picker, minDate)
		TITANIUM_PROPERTY_GETTER_TIME(Picker, minuteInterval)
		TITANIUM_PROPERTY_SETTER_TIME_MINUTES(Picker, minuteInterval)
		TITANIUM_PROPERTY_GETTER_BOOL(Picker, selectionIndicator)
		TITANIUM_PROPERTY_SETTER_BOOL(Picker, selectionIndicator)
		TITANIUM_PROPERTY_GETTER_BOOL(Picker, selectionOpens)
		TITANIUM_PROPERTY_SETTER_BOOL(Picker, selectionOpens)
		TITANIUM_PROPERTY_GETTER_BOOL(Picker, useSpinner)
		TITANIUM_PROPERTY_SETTER_BOOL(Picker, useSpinner)
		TITANIUM_PROPERTY_GETTER_DATE(Picker, value)
		TITANIUM_PROPERTY_SETTER_DATE(Picker, value)
		TITANIUM_PROPERTY_GETTER_UINT(Picker, visibleItems)
		TITANIUM_PROPERTY_SETTER_UINT(Picker, visibleItems)
		TITANIUM_PROPERTY_GETTER_BOOL(Picker, calendarViewShown)
		TITANIUM_PROPERTY_SETTER_BOOL(Picker, calendarViewShown)

		TITANIUM_PROPERTY_GETTER_STRUCT(Picker, font, Font)
		TITANIUM_PROPERTY_SETTER_STRUCT(Picker, font, Font)
		TITANIUM_PROPERTY_GETTER_ENUM(Picker, type)
		TITANIUM_PROPERTY_SETTER_ENUM(Picker, type, PICKER_TYPE)

		TITANIUM_FUNCTION(Picker, add)
		{
			ENSURE_OBJECT_AT_INDEX(js_data, 0);
			if (js_data.IsArray()) {
				const auto js_in_data = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_data));
				if (js_in_data.size() == 0) {
					return get_context().CreateUndefined();
				}
				const auto firstObj = static_cast<JSObject>(js_in_data.at(0));
				const auto isRow    = firstObj.GetPrivate<PickerRow>() != nullptr;
				const auto isColumn = firstObj.GetPrivate<PickerColumn>() != nullptr;
				if (isRow) {
					std::vector<std::shared_ptr<PickerRow>> row_data;
					for (auto v : js_in_data) {
						row_data.push_back(static_cast<JSObject>(v).GetPrivate<PickerRow>());
					}
					add_rows(row_data);
				} else if (isColumn) {
					std::vector<std::shared_ptr<PickerColumn>> column_data;
					for (auto v : js_in_data) {
						column_data.push_back(static_cast<JSObject>(v).GetPrivate<PickerColumn>());
					}
					add_columns(column_data);
				}
			} else {
				const auto rowObj    = js_data.GetPrivate<PickerRow>();
				const auto columnObj = js_data.GetPrivate<PickerColumn>();
				if (rowObj) {
					const std::vector<std::shared_ptr<PickerRow>> row_data { rowObj };
					add_rows(row_data);
				} else if (columnObj) {
					const std::vector<std::shared_ptr<PickerColumn>> column_data { columnObj };
					add_columns(column_data);
				}
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Picker, reloadColumn)
		{
			ENSURE_OBJECT_AT_INDEX(column, 0);
			reloadColumn(column.GetPrivate<PickerColumn>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Picker, getSelectedRow)
		{
			ENSURE_UINT_AT_INDEX(index, 0);
			const auto row = getSelectedRow(index);
			if (row) {
				return row->get_object();
			} else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_FUNCTION(Picker, setSelectedRow)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_UINT_AT_INDEX(column, 0);
			ENSURE_UINT_AT_INDEX(row, 1);
			ENSURE_OPTIONAL_BOOL_AT_INDEX(animated, 2, false);
			setSelectedRow(column, row, animated);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Picker, showDatePickerDialog)
		{
			ENSURE_OBJECT_AT_INDEX(dictObj, 0);
			showDatePickerDialog(js_to_PickerDialogOption(dictObj));
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Picker, showTimePickerDialog)
		{
			ENSURE_OBJECT_AT_INDEX(dictObj, 0);
			showTimePickerDialog(js_to_PickerDialogOption(dictObj));
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(Picker, getColumns, columns)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setColumns, columns)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getCountDownDuration, countDownDuration)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setCountDownDuration, countDownDuration)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getFormat24, format24)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setFormat24, format24)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getLocale, locale)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setLocale, locale)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getMaxDate, maxDate)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setMaxDate, maxDate)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getMinDate, minDate)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setMinDate, minDate)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getMinuteInterval, minuteInterval)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setMinuteInterval, minuteInterval)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getSelectionIndicator, selectionIndicator)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setSelectionIndicator, selectionIndicator)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getSelectionOpens, selectionOpens)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setSelectionOpens, selectionOpens)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getUseSpinner, useSpinner)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setUseSpinner, useSpinner)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setValue, value)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getVisibleItems, visibleItems)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setVisibleItems, visibleItems)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getCalendarViewShown, calendarViewShown)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setCalendarViewShown, calendarViewShown)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setFont, font)
		TITANIUM_FUNCTION_AS_GETTER(Picker, getType, type)
		TITANIUM_FUNCTION_AS_SETTER(Picker, setType, type)

	} // namespace UI
} // namespace Titanium
