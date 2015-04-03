/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DATABASE_DB_HPP_
#define _TITANIUM_DATABASE_DB_HPP_

#include "Titanium/Database/ResultSet.hpp"

namespace Titanium
{
	namespace Database
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium.Database.DB module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Database.DB
		*/
		class TITANIUMKIT_EXPORT DB : public Module, public JSExport<DB>
		{
		public:
			/*!
			  @method
			  @abstract file : Titanium.Filesystem.File READONLY
			  @discussion A File object representing the file where this database is stored. Must only be used for setting file properties.
			*/
			virtual JSValue get_file() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract lastInsertRowId : Number
			  @discussion The identifier of the last populated row.
			*/
			virtual int64_t get_lastInsertRowId() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract name : String
			  @discussion The name of the database.
			*/
			virtual std::string get_name() const TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract rowsAffected : Number
			  @discussion The number of rows affected by the last query.
			*/
			virtual uint32_t get_rowsAffected() const TITANIUM_NOEXCEPT;
	
			/*!
			  @method
			  @abstract close( ) : void
			  @discussion Closes the database and releases resources from memory. Once closed, this instance is no longer valid and should not be used. On iOS, also closes all Titanium.Database.ResultSet instances that exist.
			*/
			virtual void close() TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract execute( sql, [vararg] ) : Titanium.Database.ResultSet
			  @discussion Executes an SQL statement against the database and returns a ResultSet.
			*/
			virtual JSValue execute(const std::string& sql, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			DB(const JSContext&) TITANIUM_NOEXCEPT;
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual ~DB() = default;
			DB(const DB&) = default;
			DB& operator=(const DB&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			DB(DB&&) = default;
			DB& operator=(DB&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(file);
			TITANIUM_PROPERTY_READONLY_DEF(lastInsertRowId);
			TITANIUM_PROPERTY_READONLY_DEF(name);
			TITANIUM_PROPERTY_READONLY_DEF(rowsAffected);

			TITANIUM_FUNCTION_DEF(close);
			TITANIUM_FUNCTION_DEF(execute);
			/*!
			  @method
			  @abstract remove( ) : void
			  @discussion Removes the database files for this instance from disk. WARNING: this is a destructive operation and cannot be reversed. All data in the database will be lost; use with caution.
			*/
			TITANIUM_FUNCTION_DEF(remove);
		
		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string name__;
			std::string path__;
#pragma warning(pop)
			sqlite3* db__;
			uint32_t affected_rows__;
		};
	} // namespace Database
}  // namespace Titanium

#endif  // _TITANIUM_DATABASE_DB_HPP_
