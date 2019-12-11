/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Database/DB.hpp"
#include "Titanium/Database/ResultSet.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/detail/TiImpl.hpp"

// Taken from iOS SDK
#define SQLITE_BUSY_TIMEOUT 5000

namespace Titanium
{
	namespace Database
	{
		DB::DB(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context, "Ti.Database.DB")
		{
			TITANIUM_LOG_DEBUG("DB:: ctor ", this);
		}

		DB::~DB()
		{
			TITANIUM_LOG_DEBUG("DB:: dtor ", this);
			close();
		}

		void DB::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			// When called to represent class
			if (arguments.empty()) {
				return;
			}

			// When constructing an instance
			// Expect two args: db name and then filepath
			name__ = static_cast<std::string>(arguments.at(0));
			path__ = static_cast<std::string>(arguments.at(1));
			if (db__ == nullptr) {
				if (name__.size() == 0) {
					TITANIUM_LOG_WARN(L"[ERROR] Invalid database name!\n");
					return;
				}
				if (path__.size() == 0) {
					TITANIUM_LOG_WARN(L"[ERROR] Invalid database file path!\n");
					return;
				}
				auto error = sqlite3_open_v2(path__.c_str(), &db__, SQLITE_OPEN_SHAREDCACHE | SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
				if (error != SQLITE_OK) {
					//sqlite3_errmsg(db_); // Error message
					TITANIUM_LOG_WARN(L"[ERROR] Could not open database!\n");
					sqlite3_close(db__);
					db__ = nullptr;
				}else {
					error = sqlite3_busy_timeout(db__, SQLITE_BUSY_TIMEOUT);
					if (error != SQLITE_OK) {
						//sqlite3_errmsg(db_); // Error message
						TITANIUM_LOG_WARN(L"[ERROR] Timeout error!\n");
						sqlite3_close(db__);
						db__ = nullptr;
					}
				}
			}
		}

		JSValue DB::get_file() const TITANIUM_NOEXCEPT
		{
			JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Filesystem_property = Titanium.GetProperty("Filesystem");
			TITANIUM_ASSERT(Filesystem_property.IsObject());  // precondition
			JSObject Filesystem = static_cast<JSObject>(Filesystem_property);

			JSValue File_property = Filesystem.GetProperty("File");
			TITANIUM_ASSERT(File_property.IsObject());  // precondition
			JSObject File = static_cast<JSObject>(File_property);

			return File.CallAsConstructor(get_context().CreateString(path__));
		}

		int64_t DB::get_lastInsertRowId() const TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(db__);
			return sqlite3_last_insert_rowid(db__);
		}

		std::string DB::get_name() const TITANIUM_NOEXCEPT
		{
			return name__;
		}

		uint32_t DB::get_rowsAffected() const TITANIUM_NOEXCEPT
		{
			return affected_rows__;
		}

		void DB::close() TITANIUM_NOEXCEPT
		{
			for (auto resultSet : resultSets__) {
				resultSet.second->close(false);
			}
			resultSets__.clear();

			if (db__ != nullptr) {
				sqlite3_close(db__);
				db__ = nullptr;
			}
		}

		JSValue DB::execute(const std::string& sql, const std::vector<JSValue>& args) TITANIUM_NOEXCEPT
		{
			if (db__ == nullptr) {
				return get_context().CreateNull();
			}

			sqlite3_stmt* statement;

			auto error = sqlite3_prepare_v2(db__, sql.c_str(), static_cast<int>(sql.size()), &statement, NULL);
			if (error != SQLITE_OK) {
				TITANIUM_LOG_WARN("[ERROR] SQLite prepare error!");
				sqlite3_finalize(statement);
				return get_context().CreateNull();
			}

			if (args.size() > 1) {
				for (int i = 1, len = static_cast<int>(args.size()); i < len; i++) {
					JSValue arg = args.at(i);
					auto parameter_count = 1;
					JSObject arg_object = get_context().CreateObject();
					if (arg.IsObject()) {
						arg_object = static_cast<JSObject>(arg);
						if (arg_object.IsArray()) {
							parameter_count = static_cast<uint32_t>(arg_object.GetProperty("length"));
						}
					}

					for (int j = 0; j < parameter_count; j++) {
						auto bind_index = i;
						if (arg_object.IsArray()) {
							arg = arg_object.GetProperty(j);
							bind_index = j + 1;
						}
						if (arg.IsString()) {
							const std::string str = static_cast<std::string>(arg);
							error = sqlite3_bind_text(statement, bind_index, str.c_str(), static_cast<int>(str.size()), SQLITE_TRANSIENT);
						} else if (arg.IsBoolean()) {
							// SQLite cant bind booleans so the next best is an integer
							error = sqlite3_bind_int(statement, bind_index, static_cast<int>(static_cast<bool>(arg)));
						} else if (arg.IsNumber()) {
							error = sqlite3_bind_double(statement, bind_index, static_cast<double>(arg));
						}
						if (error) {
							TITANIUM_LOG_WARN("[ERROR] SQLite bind error!");
							sqlite3_finalize(statement);
							return get_context().CreateNull();
						}
					}
				}
			}

			// Execute query statement
			auto stepResult = sqlite3_step(statement);

			// Now let's wrap the results in our ResultSet proxy
			// FIXME Pass these values into the constructor, don't expose the fields
			// How would we pass along the statement pointer?
			const auto resultSet_object = get_context().CreateObject(JSExport<Titanium::Database::ResultSet>::Class());
			const auto resultSet = resultSet_object.GetPrivate<Titanium::Database::ResultSet>();
			resultSet->setDatabase(this);
			const auto insert_result = resultSets__.emplace(statement, resultSet);
			TITANIUM_ASSERT(insert_result.second);

			int affectedRows = 0;
			if (stepResult == SQLITE_DONE) {
				int columns = sqlite3_column_count(statement);
				sqlite3_finalize(statement);
				affected_rows__ = 1; // FIXME Why do we set the DB's affected rows to 1 while the result set says 0?
				if (columns == 0) {
					return get_context().CreateNull();
				}
				resultSet->affected_rows__ = 0;
				resultSet->statement__ = statement;
				return resultSet_object;
			}

			while (stepResult != SQLITE_DONE) {
				if (stepResult == SQLITE_ROW) {
					affectedRows++;
				} else {
					sqlite3_finalize(statement);
					TITANIUM_LOG_WARN("[ERROR] While stepping through statement, an error has occurred!");
					return get_context().CreateNull();
				}
				stepResult = sqlite3_step(statement);
			}

			resultSet->affected_rows__ = affectedRows;
			affected_rows__ = resultSet->affected_rows__;
			sqlite3_reset(statement);
			resultSet->step_result__ = sqlite3_step(statement);
			resultSet->statement__ = statement;

			for (int i = 0, len = sqlite3_column_count(statement); i < len; i++) {
				resultSet->column_names__.push_back(sqlite3_column_name(statement,i));
			}

			return resultSet_object;
		}

		void DB::removeStatement(sqlite3_stmt* statement)
		{
			resultSets__.erase(statement);
		}

		void DB::JSExportInitialize()
		{
			JSExport<DB>::SetClassVersion(1);
			JSExport<DB>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_PROPERTY_READONLY(DB, file);
			TITANIUM_ADD_PROPERTY_READONLY(DB, lastInsertRowId);
			TITANIUM_ADD_PROPERTY_READONLY(DB, name);
			TITANIUM_ADD_PROPERTY_READONLY(DB, rowsAffected);

			TITANIUM_ADD_FUNCTION(DB, close);
			TITANIUM_ADD_FUNCTION(DB, execute);
			TITANIUM_ADD_FUNCTION(DB, remove);
		}

		TITANIUM_PROPERTY_GETTER(DB, file)
		{
			return get_file();
		}

		TITANIUM_PROPERTY_GETTER(DB, lastInsertRowId)
		{
			return get_context().CreateNumber(static_cast<double>(get_lastInsertRowId()));
		}

		TITANIUM_PROPERTY_GETTER(DB, name)
		{
			return get_context().CreateString(get_name());
		}

		TITANIUM_PROPERTY_GETTER(DB, rowsAffected)
		{
			return get_context().CreateNumber(get_rowsAffected());
		}

		TITANIUM_FUNCTION(DB, close)
		{
			close();

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(DB, execute)
		{
			ENSURE_STRING_AT_INDEX(sql, 0);

			if (arguments.size() > 1) {
				// TODO Drop the first arg (the sql statement) and grab all the varargs
				//std::vector<JSValue> varargs = std::vector<JSValue>(arguments.begin() + 1, arguments.end()).swap(arguments);
				return execute(sql, arguments);
			} else {
				return execute(sql);
			}
		}

		TITANIUM_FUNCTION(DB, remove)
		{
			close();

			// Now we grab the file object and call deleteFile on it
			JSValue file = get_file();
			TITANIUM_ASSERT(file.IsObject());  // precondition
			JSObject FileObject = static_cast<JSObject>(file);

			const auto file_ptr = FileObject.GetPrivate<Titanium::Filesystem::File>();

			if (file_ptr != nullptr && file_ptr->exists()) {
				file_ptr->deleteFile();
			}

			return get_context().CreateUndefined();
		}
	} // namespace Database
}  // namespace Titanium
