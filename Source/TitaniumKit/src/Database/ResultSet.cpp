/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Database/ResultSet.hpp"
#include "Titanium/Database/DB.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <type_traits>
#include <boost/algorithm/string.hpp>

namespace Titanium
{
	namespace Database
	{
		ResultSet::ResultSet(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context, "Ti.Database.ResultSet")
		{
			TITANIUM_LOG_DEBUG("ResultSet:: ctor ", this);
		}

		ResultSet::~ResultSet() {
			TITANIUM_LOG_DEBUG("ResultSet:: dtor ", this);
			close();
		}

		void ResultSet::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			HAL_LOG_DEBUG("ResultSet:: postCallAsConstructor ", this);
		}

		uint32_t ResultSet::get_fieldCount() const TITANIUM_NOEXCEPT
		{
			return static_cast<uint32_t>(column_names__.size());
		}

		uint32_t ResultSet::get_rowCount() const TITANIUM_NOEXCEPT
		{
			return affected_rows__;
		}

		bool ResultSet::get_validRow() const TITANIUM_NOEXCEPT
		{
			return step_result__ == SQLITE_ROW;
		}

		void ResultSet::close(bool needCallback) TITANIUM_NOEXCEPT
		{
			if (statement__ != nullptr && column_names__.size()) {
				sqlite3_finalize(statement__);

				if (needCallback && database__ != nullptr) {
					database__->removeStatement(statement__);
				}
			}

			statement__ = nullptr;
			step_result__ = 0;
			affected_rows__ = 0;
			column_names__.clear();
			database__ = nullptr;
		}

		JSValue ResultSet::field(const uint32_t& index) TITANIUM_NOEXCEPT
		{
			if (statement__ == nullptr) {
				return get_context().CreateNull();
			}

			const auto columnType = sqlite3_column_type(statement__, index);
			switch (columnType) {
				case SQLITE_TEXT:{
					std::string text(reinterpret_cast<const char*>(sqlite3_column_text(statement__, index)));
					return get_context().CreateString(text);
				}
				case SQLITE_INTEGER:{
					return get_context().CreateNumber(static_cast<double>(sqlite3_column_int64(statement__, index)));
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
			if (statement__ == nullptr) {
				return get_context().CreateNull();
			}

			switch (fieldType) {
				case FIELD_TYPE::STRING:{
					std::string text(reinterpret_cast<const char*>(sqlite3_column_text(statement__, index)));
					return get_context().CreateString(text);
				}
				case FIELD_TYPE::INT:{
					return get_context().CreateNumber(static_cast<double>(sqlite3_column_int64(statement__, index)));
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
			const auto index = fieldIndex(name);
			if (index == -1) {
				return get_context().CreateNull();
			}
			return field(index);
		}

		JSValue ResultSet::fieldByName(const std::string& name, const FIELD_TYPE& fieldType) TITANIUM_NOEXCEPT
		{
			const auto index = fieldIndex(name);
			if (index == -1) {
				return get_context().CreateNull();
			}
			return field(index, fieldType);
		}

		uint32_t ResultSet::fieldIndex(const std::string& name) TITANIUM_NOEXCEPT
		{
			for (uint32_t i = 0, len = static_cast<uint32_t>(column_names__.size()); i < len; i++) {
				// Case insensitive string comparison
				if (boost::iequals(column_names__[i], name)) {
					return i;
				}
			}
			return -1;
		}

		std::string ResultSet::fieldName(const uint32_t& index) TITANIUM_NOEXCEPT
		{
			if (statement__ == nullptr) {
				return nullptr;
			}

			auto _text = reinterpret_cast<const char*>(sqlite3_column_name(statement__, index));
			if (_text != nullptr && index <= static_cast<size_t>(sqlite3_column_count(statement__)) && strlen(_text) > 0) {
				std::string text(_text);
				return text;
			}
			return std::string();
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
			if (statement__ == nullptr) {
				return false;
			}

			step_result__ = sqlite3_step(statement__);
			return isValidRow();
		}

		void ResultSet::JSExportInitialize()
		{
			JSExport<ResultSet>::SetClassVersion(1);
			JSExport<ResultSet>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_PROPERTY_READONLY(ResultSet, fieldCount);
			TITANIUM_ADD_PROPERTY_READONLY(ResultSet, rowCount);
			TITANIUM_ADD_PROPERTY_READONLY(ResultSet, validRow);

			TITANIUM_ADD_FUNCTION(ResultSet, close);
			TITANIUM_ADD_FUNCTION(ResultSet, field);
			TITANIUM_ADD_FUNCTION(ResultSet, fieldByName);
			TITANIUM_ADD_FUNCTION(ResultSet, fieldName);
			TITANIUM_ADD_FUNCTION(ResultSet, getFieldName);
			TITANIUM_ADD_FUNCTION(ResultSet, isValidRow);
			TITANIUM_ADD_FUNCTION(ResultSet, next);
		}

		TITANIUM_PROPERTY_GETTER(ResultSet, fieldCount)
		{
			return get_context().CreateNumber(get_fieldCount());
		}

		TITANIUM_PROPERTY_GETTER(ResultSet, rowCount)
		{
			return get_context().CreateNumber(get_rowCount());
		}

		TITANIUM_PROPERTY_GETTER(ResultSet, validRow)
		{
			return get_context().CreateBoolean(get_validRow());
		}

		TITANIUM_FUNCTION(ResultSet, close)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			close();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ResultSet, field)
		{
			ENSURE_UINT_AT_INDEX(index, 0);

			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());
				const auto fieldType = Constants::to_FIELD_TYPE(static_cast<std::underlying_type<FIELD_TYPE>::type>(_1));
				return field(index, fieldType);
			}
			return field(index);
		}

		TITANIUM_FUNCTION(ResultSet, fieldByName)
		{
			ENSURE_STRING_AT_INDEX(name, 0);

			if (arguments.size() > 1) {
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsNumber());
				const auto fieldType = Constants::to_FIELD_TYPE(static_cast<std::underlying_type<FIELD_TYPE>::type>(_1));
				return fieldByName(name, fieldType);
			}
			return fieldByName(name);
		}

		TITANIUM_FUNCTION(ResultSet, fieldName)
		{
			ENSURE_UINT_AT_INDEX(index, 0);

			const std::string result = fieldName(index);
			if (result.empty()) {
				return get_context().CreateNull();
			}
			return get_context().CreateString(result);
		}

		TITANIUM_FUNCTION(ResultSet, getFieldName)
		{
			ENSURE_UINT_AT_INDEX(index, 0);

			const std::string result = getFieldName(index);
			if (result == nullptr) {
				return get_context().CreateNull();
			}
			return get_context().CreateString(result);
		}

		TITANIUM_FUNCTION(ResultSet, isValidRow)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			return get_context().CreateBoolean(isValidRow());
		}

		TITANIUM_FUNCTION(ResultSet, next)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			return get_context().CreateBoolean(next());
		}
	} // namespace Database
}  // namespace Titanium
