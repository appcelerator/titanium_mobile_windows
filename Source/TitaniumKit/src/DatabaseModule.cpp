/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/DatabaseModule.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Database/Constants.hpp"
#include "Titanium/Database/DB.hpp"
#include "Titanium/Database/ResultSet.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	static const std::string ti_db_js = R"TI_DB_JS(
	var self = this;
	this.exports = {};
	this.exports.install = function(dbResourceFilePath,dbName) {
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
		return self.TiDatabase.open(dbName);
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
	    : Module(js_context, "Ti.Database"),
	      field_type_double__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::DOUBLE))),
	      field_type_float__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::FLOAT))),
	      field_type_int__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::INT))),
	      field_type_string__(js_context.CreateNumber(Titanium::Database::Constants::to_underlying_type(Titanium::Database::FIELD_TYPE::STRING))),
	      ti_db__(js_context.CreateObject())
	{
		TITANIUM_LOG_DEBUG("DatabaseModule:: ctor ", this);
	}

	DatabaseModule::~DatabaseModule() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("DatabaseModule:: dtor ", this);
	}

	TITANIUM_PROPERTY_GETTER(DatabaseModule, FIELD_TYPE_DOUBLE)
	{
		return field_type_double__;
	}

	TITANIUM_PROPERTY_GETTER(DatabaseModule, FIELD_TYPE_FLOAT)
	{
		return field_type_float__;
	}

	TITANIUM_PROPERTY_GETTER(DatabaseModule, FIELD_TYPE_INT)
	{
		return field_type_int__;
	}

	TITANIUM_PROPERTY_GETTER(DatabaseModule, FIELD_TYPE_STRING)
	{
		return field_type_string__;
	}

	bool DatabaseModule::loadJS()
	{
		if (ti_db__.HasProperty("install") && ti_db__.HasProperty("open")) {
			return true;
		}

		const auto js_context = get_context();

		auto export_object = js_context.CreateObject();
		export_object.SetProperty("global", js_context.get_global_object());
		export_object.SetProperty("TiDatabase", js_context.CreateObject(JSExport<Titanium::DatabaseModule>::Class()));
		export_object.SetProperty("TiDatabaseDB", js_context.CreateObject(JSExport<Titanium::Database::DB>::Class()));
		export_object.SetProperty("TiDatabaseResultSet", js_context.CreateObject(JSExport<Titanium::Database::ResultSet>::Class()));

		js_context.JSEvaluateScript(ti_db_js, export_object);
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
		TITANIUM_ADD_FUNCTION(DatabaseModule, install);
		TITANIUM_ADD_FUNCTION(DatabaseModule, open);
		TITANIUM_ADD_PROPERTY_READONLY(DatabaseModule, FIELD_TYPE_DOUBLE);
		TITANIUM_ADD_PROPERTY_READONLY(DatabaseModule, FIELD_TYPE_FLOAT);
		TITANIUM_ADD_PROPERTY_READONLY(DatabaseModule, FIELD_TYPE_INT);
		TITANIUM_ADD_PROPERTY_READONLY(DatabaseModule, FIELD_TYPE_STRING);
	}

	JSObject DatabaseModule::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		static JSObject cached = js_context.CreateObject();
		static std::once_flag of;
		std::call_once(of, [=] {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Object_property = Titanium.GetProperty("Database");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			cached = static_cast<JSObject>(Object_property);
		});
		return cached;
	}

	TITANIUM_FUNCTION(DatabaseModule, install)
	{
		const auto js_context = this_object.get_context();
		const auto database = GetStaticObject(js_context).GetPrivate<DatabaseModule>();

		// lazy loading
		const auto loaded = database->loadJS();
		if (loaded) {
			auto func = database->getTiObject().GetProperty("install");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Database.install");
			return js_context.CreateNull();
		}
	}

	TITANIUM_FUNCTION(DatabaseModule, open)
	{
		const auto js_context = this_object.get_context();
		const auto database = GetStaticObject(js_context).GetPrivate<DatabaseModule>();

		// lazy loading
		const auto loaded = database->loadJS();
		if (loaded) {
			auto func = database->getTiObject().GetProperty("open");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Database.open");
			return js_context.CreateNull();
		}
	}
}  // namespace Titanium
