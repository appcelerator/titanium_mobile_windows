/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DATABASE_RESULTSET_HPP_
#define _TITANIUM_DATABASE_RESULTSET_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Database/Constants.hpp"
#include <vector>
#include "sqlite3.h"

namespace Titanium
{
	namespace Database
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium.Database.ResultSet module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Database.ResultSet
		*/
		class TITANIUMKIT_EXPORT ResultSet : public Module, public JSExport<ResultSet>
		{
		public:
			/*!
			  @method
			  @abstract fieldCount : Number READONLY
			  @discussion The number of columns in this result set.
			*/
			virtual uint32_t get_fieldCount() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract rowCount : Number READONLY
			  @discussion The number of rows in this result set.
			*/
			virtual uint32_t get_rowCount() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract validRow : Boolean READONLY
			  @discussion Indicates whether the current row is valid.
			*/
			virtual bool get_validRow() const TITANIUM_NOEXCEPT;
	
			/*!
			  @method
			  @abstract close( ) : void
			  @discussion Closes this result set and release resources. Once closed, the result set must no longer be used.
			*/
			virtual void close() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract field( index, [type] ) : String/Number/Titanium.Blob
			  @discussion Retrieves the value for the specified field in the current row, and casts it to the specified type (String, Integer, Float or Double.)

			  All of the numeric types (Integer, Float or Double) are returned as JavaScript Number objects.

			  If no type parameter is specified, the returned data type depends on the data in the column.

			  If the data in the column is TEXT, the data is returned as a String.
			  If the data in the column is any kind of number, the data is returned as a Number.
			  If the data in the column is a BLOB, the data is returned as a Titanium.Blob object.
			  When a type is specified and the data cannot be converted to the specified type, an exception is thrown.

			  Returns null if the value in the table is NULL.
			  @param index : Number
			  	A zero-based column index for the field.
			  @param type : Number (optional)
			  	Type to cast field value
			*/
			virtual JSValue field(const uint32_t& index) TITANIUM_NOEXCEPT;
			virtual JSValue field(const uint32_t& index, const FIELD_TYPE& type) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract fieldByName( name, [type] ) : String/Number/Titanium.Blob
			  @discussion Retrieves the value for the specified field in the current row, and casts it to the specified type (String, Integer, Float or Double.)

			  All of the numeric types (Integer, Float or Double) are returned as JavaScript Number objects.

			  If no type parameter is specified, the returned data type depends on the data in the column.

			  If the data in the column is TEXT, the data is returned as a String.
			  If the data in the column is any kind of number, the data is returned as a Number.
			  If the data in the column is a BLOB, the data is returned as a Titanium.Blob object.
			  When a type is specified and the data cannot be converted to the specified type, an exception is thrown.

			  Returns null if the value in the table is NULL.
			  @param index : Number
			  	A zero-based column index for the field.
			  @param type : Number (optional)
			  	Type to cast field value
			*/
			virtual JSValue fieldByName(const std::string& name) TITANIUM_NOEXCEPT;
			virtual JSValue fieldByName(const std::string& name, const FIELD_TYPE& type) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract fieldName( index ) : String
			  @discussion Returns the field name for the specified field index.
			  @param index : Number
			  A zero-based column index for the field.
			*/
			virtual std::string fieldName(const uint32_t& index) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract getFieldName( index ) : String
			  @discussion Returns the field name for the specified field index.
			  @param index : Number
			  A zero-based column index for the field.
			*/
			virtual std::string getFieldName(const uint32_t& index) TITANIUM_NOEXCEPT final;

			/*!
			  @method
			  @abstract isValidRow( ) : Boolean
			  @discussion Returns whether the current row is valid.
			*/
			virtual bool isValidRow() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract next( ) : Boolean
			  @discussion Advances to the next row in the result set and returns true if one exists, or false otherwise.
			*/
			virtual bool next() TITANIUM_NOEXCEPT;

			ResultSet(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ResultSet() = default;
			ResultSet(const ResultSet&) = default;
			ResultSet& operator=(const ResultSet&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ResultSet(ResultSet&&) = default;
			ResultSet& operator=(ResultSet&&) = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_fieldCount() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_rowCount() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_validRow() const TITANIUM_NOEXCEPT final;

			virtual JSValue js_close(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_field(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_fieldByName(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_fieldName(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getFieldName(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_isValidRow(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_next(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			// FIXME Make these fields private
			uint32_t affected_rows__;
			uint32_t step_result__;
			sqlite3_stmt* statement__;
#pragma warning(push)
#pragma warning(disable : 4251)
			std::vector<std::string> column_names__;
#pragma warning(pop)

		private:
			/*
			  @method
			  @abstract fieldIndex( name ) : int
			  @discussion Finds the index of the field with the given name. Returns -1 if not found.
			*/
			virtual int fieldIndex(const std::string& fieldName) TITANIUM_NOEXCEPT final;

		};
	} // namespace Database
}  // namespace Titanium

#endif  // _TITANIUM_DATABASE_RESULTSET_HPP_
