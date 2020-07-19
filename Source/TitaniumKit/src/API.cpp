/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/API.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <unordered_map>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#define JOIN_ARGUMENT_STRINGS(OUT,START) \
  std::stringstream OUT; \
  for (std::size_t i = START; i < arguments.size(); i++) { \
    OUT << static_cast<std::string>(arguments.at(i)); \
    if (i < arguments.size() - 1) OUT << " "; \
  }

namespace Titanium
{
	API::API(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti.API")
	{
		TITANIUM_LOG_DEBUG("API:: ctor ", this);
	}

	void API::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
		TITANIUM_LOG_DEBUG("API:: postCallAsConstructor ", this);
	}

	API::~API() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("API:: dtor ", this);
	}

	void API::info(const std::string& message) const TITANIUM_NOEXCEPT
	{
		log(LogSeverityLevel::API_INFO, message);
	}

	void API::warn(const std::string& message) const TITANIUM_NOEXCEPT
	{
		log(LogSeverityLevel::API_WARN, message);
	}

	void API::error(const std::string& message) const TITANIUM_NOEXCEPT
	{
		log(LogSeverityLevel::API_ERROR, message);
	}

	void API::debug(const std::string& message) const TITANIUM_NOEXCEPT
	{
		log(LogSeverityLevel::API_DEBUG, message);
	}

	void API::trace(const std::string& message) const TITANIUM_NOEXCEPT
	{
		log(LogSeverityLevel::API_TRACE, message);
	}

	void API::log(const std::string& custom_level, const std::string& message) const TITANIUM_NOEXCEPT
	{
		log(ToLogLevel(custom_level), message, custom_level);
	}

	void API::log(LogSeverityLevel log_severity_level, const std::string& message, const std::string& custom_level) const TITANIUM_NOEXCEPT
	{
		std::ostringstream os;
		switch (log_severity_level) {
			case LogSeverityLevel::API_INFO:
				os << "[INFO] ";
				break;

			case LogSeverityLevel::API_WARN:
				os << "[WARN] ";
				break;

			case LogSeverityLevel::API_ERROR:
				os << "[ERROR] ";
				break;

			case LogSeverityLevel::API_DEBUG:
				os << "[DEBUG] ";
				break;

			case LogSeverityLevel::API_TRACE:
				os << "[TRACE] ";
				break;
			default:
				os << "[DEBUG] [" << boost::to_upper_copy(custom_level) << "] ";
		}

		os << message;
		log(os.str());
	}

	void API::log(const std::string& message) const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("API::log: Unimplemented. Defaulting to std::clog");
		std::clog << message << std::endl;
	}

	API::LogSeverityLevel API::ToLogLevel(const std::string& level)
	{
		static std::unordered_map<std::string, LogSeverityLevel> log_severity_level_map;
		static std::once_flag of;
		std::call_once(of, []() {
      log_severity_level_map.emplace("info" , LogSeverityLevel::API_INFO);
      log_severity_level_map.emplace("warn" , LogSeverityLevel::API_WARN);
      log_severity_level_map.emplace("error", LogSeverityLevel::API_ERROR);
      log_severity_level_map.emplace("debug", LogSeverityLevel::API_DEBUG);
      log_severity_level_map.emplace("trace", LogSeverityLevel::API_TRACE);
		});

		LogSeverityLevel log_severity_level = LogSeverityLevel::API_UNKNOWN;
		const auto position = log_severity_level_map.find(boost::to_lower_copy(level));

		if (position != log_severity_level_map.end()) {
			log_severity_level = position->second;
		}

		return log_severity_level;
	}

	// TODO: The following functions can automatically be generated from
	// the YAML API docs.

	void API::JSExportInitialize()
	{
		JSExport<API>::SetClassVersion(1);
		JSExport<API>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_FUNCTION(API, info);
		TITANIUM_ADD_FUNCTION(API, warn);
		TITANIUM_ADD_FUNCTION(API, error);
		TITANIUM_ADD_FUNCTION(API, debug);
		TITANIUM_ADD_FUNCTION(API, trace);
		TITANIUM_ADD_FUNCTION(API, log);
	}

	JSObject API::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		static JSObject cached = js_context.CreateObject();
		static std::once_flag of;
		std::call_once(of, [=] {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Object_property = Titanium.GetProperty("API");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			cached = static_cast<JSObject>(Object_property);
		});
		return cached;
	}

	TITANIUM_FUNCTION(API, info)
	{
		JOIN_ARGUMENT_STRINGS(message, 0);

		const auto js_context = this_object.get_context();
		GetStaticObject(js_context).GetPrivate<API>()->info(message.str());
		return js_context.CreateUndefined();
	}

	TITANIUM_FUNCTION(API, warn)
	{
		JOIN_ARGUMENT_STRINGS(message, 0);

		const auto js_context = this_object.get_context();
		GetStaticObject(js_context).GetPrivate<API>()->warn(message.str());
		return js_context.CreateUndefined();
	}

	TITANIUM_FUNCTION(API, error)
	{
		JOIN_ARGUMENT_STRINGS(message, 0);

		const auto js_context = this_object.get_context();
		GetStaticObject(js_context).GetPrivate<API>()->error(message.str());
		return js_context.CreateUndefined();
	}

	TITANIUM_FUNCTION(API, debug)
	{
		JOIN_ARGUMENT_STRINGS(message, 0);

		const auto js_context = this_object.get_context();
		GetStaticObject(js_context).GetPrivate<API>()->debug(message.str());
		return js_context.CreateUndefined();
	}

	TITANIUM_FUNCTION(API, trace)
	{
		JOIN_ARGUMENT_STRINGS(message, 0);

		const auto js_context = this_object.get_context();
		GetStaticObject(js_context).GetPrivate<API>()->trace(message.str());
		return js_context.CreateUndefined();
	}

	TITANIUM_FUNCTION(API, log)
	{
		const auto js_context = this_object.get_context();
		if (arguments.size() == 1) {
			ENSURE_STRING_AT_INDEX(message, 0);
			GetStaticObject(js_context).GetPrivate<API>()->log("info", message);
		} else if (arguments.size() == 2) {
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_STRING_AT_INDEX(level, 0);
			JOIN_ARGUMENT_STRINGS(message, 1);
			GetStaticObject(js_context).GetPrivate<API>()->log(level, message.str());
		}

		return js_context.CreateUndefined();
	}

}  // namespace Titanium
