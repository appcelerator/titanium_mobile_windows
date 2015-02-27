/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Database/ResultSet.hpp"
#include <type_traits>

namespace Titanium
{
	namespace Database
	{
		ResultSet::ResultSet(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context)
		{
			TITANIUM_LOG_DEBUG("ResultSet:: ctor ", this);
		}

		void ResultSet::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			HAL_LOG_DEBUG("ResultSet:: postCallAsConstructor ", this);
		}

		uint32_t ResultSet::get_fieldCount() const TITANIUM_NOEXCEPT
		{
			return column_names__.size();
		}

		uint32_t ResultSet::get_rowCount() const TITANIUM_NOEXCEPT
		{
			return affected_rows__;
		}

		bool ResultSet::get_validRow() const TITANIUM_NOEXCEPT
		{
			return step_result__ == SQLITE_ROW;
		}
	
		void ResultSet::close() TITANIUM_NOEXCEPT
		{
			if (column_names__.size()) {
				sqlite3_finalize(statement__);
			}
		}

		JSValue ResultSet::field(const uint32_t& index) TITANIUM_NOEXCEPT
		{
			int columnType = sqlite3_column_type(statement__, index);
			switch (columnType) {
				case SQLITE_TEXT:{
					std::string text(reinterpret_cast<const char*>(sqlite3_column_text(statement__, index)));
					return get_context().CreateString(text);
				}
				case SQLITE_INTEGER:{
					return get_context().CreateNumber(static_cast<double>(sqlite3_column_int(statement__, index)));
				}
				case SQLITE_FLOAT:{
					return get_context().CreateNumber(static_cast<double>(sqlite3_column_double(statement__, index)));
				}
				case SQLITE_BLOB:{
					// TODO: create a Ti Blob from this
					return get_context().CreateNull(); //sqlite3_column_blob(statement, index)
				}
				case SQLITE_NULL:{
					return get_context().CreateNull();
				}
			}
			return get_context().CreateNull();
		}

		JSValue ResultSet::field(const uint32_t& index, const FIELD_TYPE& fieldType) TITANIUM_NOEXCEPT
		{
			switch (fieldType) {
				case FIELD_TYPE::STRING:{
					std::string text(reinterpret_cast<const char*>(sqlite3_column_text(statement__, index)));
					return get_context().CreateString(text);
				}
				case FIELD_TYPE::INT:{
					return get_context().CreateNumber(static_cast<double>(sqlite3_column_int(statement__, index)));
				}
				case FIELD_TYPE::DOUBLE:
				case FIELD_TYPE::FLOAT:{
					return get_context().CreateNumber(static_cast<double>(sqlite3_column_double(statement__, index)));
				}
				default:{
					return get_context().CreateNull();
				}
			}
			return get_context().CreateNull();
		}

		JSValue ResultSet::fieldByName(const std::string& name) TITANIUM_NOEXCEPT
		{
			int index = fieldIndex(name);
			if (index == -1) {
				return get_context().CreateNull();
			}
			return field(index);
		}

		JSValue ResultSet::fieldByName(const std::string& name, const FIELD_TYPE& fieldType) TITANIUM_NOEXCEPT
		{
			int index = fieldIndex(name);
			if (index == -1) {
				return get_context().CreateNull();
			}
			return field(index, fieldType);
		}

		int ResultSet::fieldIndex(const std::string& name) TITANIUM_NOEXCEPT
		{
			for (size_t i = 0, len = column_names__.size(); i < len; i++) {
				if (column_names__[i] == name) {
					return i;
				}
			}
			return -1;
		}

		std::string ResultSet::fieldName(const uint32_t& index) TITANIUM_NOEXCEPT
		{
			if (index <= (size_t) sqlite3_column_count(statement__) && strlen(reinterpret_cast<const char*>(sqlite3_column_text(statement__, index))) > 0) {
				std::string text(reinterpret_cast<const char*>(sqlite3_column_name(statement__, index)));
				return text;
			}
			return nullptr;
		}

		std::string ResultSet::getFieldName(const uint32_t& index) TITANIUM_NOEXCEPT
		{
			return fieldName(index);
		}

		bool ResultSet::isValidRow() TITANIUM_NOEXCEPT
		{
			return get_validRow();
		}

		bool ResultSet::next() TITANIUM_NOEXCEPT
		{
			step_result__ = sqlite3_step(statement__);
			return isValidRow();
		}

		void ResultSet::JSExportInitialize()
		{
			JSExport<ResultSet>::SetClassVersion(1);
			JSExport<ResultSet>::SetParent(JSExport<Module>::Class());
			JSExport<ResultSet>::AddValueProperty("fieldCount", std::mem_fn(&ResultSet::js_get_fieldCount));
			JSExport<ResultSet>::AddValueProperty("rowCount", std::mem_fn(&ResultSet::js_get_rowCount));
			JSExport<ResultSet>::AddValueProperty("validRow", std::mem_fn(&ResultSet::js_get_validRow));

			JSExport<ResultSet>::AddFunctionProperty("close", std::mem_fn(&ResultSet::js_close));
			JSExport<ResultSet>::AddFunctionProperty("field", std::mem_fn(&ResultSet::js_field));
			JSExport<ResultSet>::AddFunctionProperty("fieldByName", std::mem_fn(&ResultSet::js_fieldByName));
			JSExport<ResultSet>::AddFunctionProperty("fieldName", std::mem_fn(&ResultSet::js_fieldName));
			JSExport<ResultSet>::AddFunctionProperty("getFieldName", std::mem_fn(&ResultSet::js_getFieldName));
			JSExport<ResultSet>::AddFunctionProperty("isValidRow", std::mem_fn(&ResultSet::js_isValidRow));
			JSExport<ResultSet>::AddFunctionProperty("next", std::mem_fn(&ResultSet::js_next));
		}
	
		JSValue ResultSet::js_get_fieldCount() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_fieldCount());
		}

		JSValue ResultSet::js_get_rowCount() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_rowCount());
		}

		JSValue ResultSet::js_get_validRow() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_validRow());
		}

		JSValue ResultSet::js_close(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			close();
			return get_context().CreateUndefined();
		}

		JSValue ResultSet::js_field(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() >= 1);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());
			const auto index = static_cast<uint32_t>(_0);
			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());
				const auto fieldType = Constants::to_FIELD_TYPE(static_cast<std::underlying_type<FIELD_TYPE>::type>(_1));
				return field(index, fieldType);
			}
			return field(index);
		}

		JSValue ResultSet::js_fieldByName(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() >= 1);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsString());
			const auto name = static_cast<std::string>(_0);
			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());
				const auto fieldType = Constants::to_FIELD_TYPE(static_cast<std::underlying_type<FIELD_TYPE>::type>(_1));
				return fieldByName(name, fieldType);
			}
			return fieldByName(name);
		}

		JSValue ResultSet::js_fieldName(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());
			const auto index = static_cast<uint32_t>(_0);
			std::string result = fieldName(index);
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return get_context().CreateString(result);
		}

		JSValue ResultSet::js_getFieldName(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 1);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsNumber());
			const auto index = static_cast<uint32_t>(_0);

			std::string result = getFieldName(index);
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return get_context().CreateString(result);
		}

		JSValue ResultSet::js_isValidRow(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			return get_context().CreateBoolean(isValidRow());
		}

		JSValue ResultSet::js_next(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			return get_context().CreateBoolean(next());
		}
	} // namespace Database
}  // namespace Titanium
