/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/DatabaseModule.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	static const std::string ti_db_js = R"TI_DB_JS(
	var self = this;
	this.exports = {};
	this.exports.install = function(path,dbName) {
		var dbResourceFilePath = Ti.Filesystem.applicationDirectory + Ti.Filesystem.separator + path;
		var dbResourceFile = Ti.Filesystem.getFile(dbResourceFilePath);
		var dbDirPath = Ti.Filesystem.applicationDataDirectory + Ti.Filesystem.separator + "databases";
		var dbDir = Ti.Filesystem.getFile(dbDirPath);
		if (!dbDir.exists()) {
			dbDir.createDirectory();
		}
		var dbFilePath = dbDirPath + Ti.Filesystem.separator + dbName;
		var dbFile = Ti.Filesystem.getFile(dbFilePath);
		if ((!dbFile.exists() || dbFile.size == 0) && dbResourceFile.exists()) {
			dbResourceFile.copy(dbFilePath);
		}
		return exports.open(dbName);
	};
	this.exports.open = function(dbName) {
		var dbDirPath = Ti.Filesystem.applicationDataDirectory + Ti.Filesystem.separator + "databases";
		var dbDir = Ti.Filesystem.getFile(dbDirPath);
		if (!dbDir.exists()) {
			dbDir.createDirectory();
		}
		var dbFilePath = dbDirPath + Ti.Filesystem.separator + dbName;
		var db = new self.TiDatabaseDB(dbName, dbFilePath);
		return db;
	};
	)TI_DB_JS";

	DatabaseModule::DatabaseModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context),
	      ti_db__(js_context.CreateObject()),
	      field_type_double__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::DOUBLE))),
	      field_type_float__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::FLOAT))),
	      field_type_int__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::INT))),
	      field_type_string__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::STRING)))
	{
		TITANIUM_LOG_DEBUG("DatabaseModule:: ctor ", this);
	}

	void DatabaseModule::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
		HAL_LOG_DEBUG("DatabaseModule:: postCallAsConstructor ", this);
	}

	DatabaseModule::~DatabaseModule() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("DatabaseModule:: dtor ", this);
	}

	JSValue DatabaseModule::FIELD_TYPE_DOUBLE() const TITANIUM_NOEXCEPT
	{
		return field_type_double__;
	}

	JSValue DatabaseModule::FIELD_TYPE_FLOAT() const TITANIUM_NOEXCEPT
	{
		return field_type_float__;
	}

	JSValue DatabaseModule::FIELD_TYPE_INT() const TITANIUM_NOEXCEPT
	{
		return field_type_int__;
	}

	JSValue DatabaseModule::FIELD_TYPE_STRING() const TITANIUM_NOEXCEPT
	{
		return field_type_string__;
	}

	bool DatabaseModule::loadJS()
	{
		if (ti_db__.HasProperty("install") && ti_db__.HasProperty("open")) {
			return true;
		}

		JSContext context = get_context();
		auto export_object = context.CreateObject();
		export_object.SetProperty("global", context.get_global_object());
		export_object.SetProperty("TiDatabase", context.CreateObject<Titanium::DatabaseModule>());
		export_object.SetProperty("TiDatabaseDB", context.CreateObject<Titanium::Database::DB>());
		export_object.SetProperty("TiDatabaseResultSet", context.CreateObject<Titanium::Database::ResultSet>());

		context.JSEvaluateScript(ti_db_js, export_object);
		if (export_object.HasProperty("exports")) {
			ti_db__ = static_cast<JSObject>(export_object.GetProperty("exports"));
		} else {
			return false;
		}
		return true;
	}

	void DatabaseModule::JSExportInitialize()
	{
		JSExport<DatabaseModule>::SetClassVersion(1);
		JSExport<DatabaseModule>::SetParent(JSExport<Module>::Class());
		JSExport<DatabaseModule>::AddFunctionProperty("install", std::mem_fn(&DatabaseModule::js_install));
		JSExport<DatabaseModule>::AddFunctionProperty("open", std::mem_fn(&DatabaseModule::js_open));
		JSExport<DatabaseModule>::AddValueProperty("FIELD_TYPE_DOUBLE", std::mem_fn(&DatabaseModule::FIELD_TYPE_DOUBLE));
		JSExport<DatabaseModule>::AddValueProperty("FIELD_TYPE_FLOAT", std::mem_fn(&DatabaseModule::FIELD_TYPE_FLOAT));
		JSExport<DatabaseModule>::AddValueProperty("FIELD_TYPE_INT", std::mem_fn(&DatabaseModule::FIELD_TYPE_INT));
		JSExport<DatabaseModule>::AddValueProperty("FIELD_TYPE_STRING", std::mem_fn(&DatabaseModule::FIELD_TYPE_STRING));
	}

	JSValue DatabaseModule::js_install(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		TITANIUM_ASSERT(arguments.size() == 2);

		const auto _0 = arguments.at(0);
		const auto _1 = arguments.at(1);

		TITANIUM_ASSERT(_0.IsString());
		TITANIUM_ASSERT(_1.IsString());

		// lazy loading
		const auto loaded = loadJS();
		if (loaded) {
			auto func = ti_db__.GetProperty("install");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Database.install");
			return get_context().CreateNull();
		}
	}

	JSValue DatabaseModule::js_open(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		TITANIUM_ASSERT(arguments.size() == 1);

		const auto _0 = arguments.at(0);
		TITANIUM_ASSERT(_0.IsString());

		// lazy loading
		const auto loaded = loadJS();
		if (loaded) {
			auto func = ti_db__.GetProperty("open");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Database.open");
			return get_context().CreateNull();
		}
	}
}  // namespace Titanium
