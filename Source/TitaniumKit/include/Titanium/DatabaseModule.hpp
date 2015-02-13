/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DATABASE_HPP_
#define _TITANIUM_DATABASE_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/Database/Constants.hpp"
#include "Titanium/Database/DB.hpp"
#include "Titanium/Database/ResultSet.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class

	  @discussion The top-level Database module, used for creating and accessing the in-application SQLite database.

	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Database
	*/
	class TITANIUMKIT_EXPORT DatabaseModule : public Module, public JSExport<DatabaseModule>
	{
	public:
		virtual JSValue FIELD_TYPE_DOUBLE() const TITANIUM_NOEXCEPT final;
		virtual JSValue FIELD_TYPE_FLOAT() const TITANIUM_NOEXCEPT final;
		virtual JSValue FIELD_TYPE_INT() const TITANIUM_NOEXCEPT final;
		virtual JSValue FIELD_TYPE_STRING() const TITANIUM_NOEXCEPT final;

		DatabaseModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

		virtual ~DatabaseModule() TITANIUM_NOEXCEPT;  //= default;
		DatabaseModule(const DatabaseModule&) = default;
		DatabaseModule& operator=(const DatabaseModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		DatabaseModule(DatabaseModule&&) = default;
		DatabaseModule& operator=(DatabaseModule&&) = default;
#endif

		static void JSExportInitialize();

		/*!
		  @method

		  @abstract install( path, dbName ) : Titanium.Database.DB

		  @discussion Installs an SQLite database to device's internal storage.

		  Copies an SQLite database file to the device's internal storage (only) and creates a persistent name that is available for the lifetime of the app. On Android, if the source file does not exist, an empty database is created.

		  Returns a reference to the opened database. If the destination file already exists, behaves as open.

		  @param path : String
		  Path and filename of the database file to copy to internal storage. File location is relative to the script's context unless an absolute path, such as one constructed with a Titanium.Filesystem constant, is used.

		  @param dbName : String
		  Destination filename, which will subsequently be passed to open.

		  @result Titanium.Database.DB
		*/
		JSValue js_install(const std::vector<JSValue>& arguments, JSObject& this_object);

		/*!
		  @method

		  @abstract open( dbName ) : Titanium.Database.DB

		  @discussion Opens an SQLite database.

		  Opens an SQLite database and returns a reference to it. If the database does not exist, creates an empty database file and returns a reference to this opened database.

		  With Titanium 1.8.0.1 on iOS, the default database location changed in accordance with Apple's guidelines. If a database file already exists in the old location, open will automatically move it to the new location.

		  Always close the database after use.

		  @param dbName : String
		  The dbname previously passed to install. On Android, an absolute path to the file, including one that is constructed with a Titanium.Filesystem constant, may be used.

		  @result Titanium.Database.DB
		*/
		JSValue js_open(const std::vector<JSValue>& arguments, JSObject& this_object);

		bool loadJS();

	private:
		JSValue field_type_double__;
		JSValue field_type_float__;
		JSValue field_type_int__;
		JSValue field_type_string__;
		JSObject ti_db__;

	};

}  // namespace Titanium

#endif  // _TITANIUM_DATABASE_HPP_
