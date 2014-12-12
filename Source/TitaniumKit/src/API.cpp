/**
 * TitaniumKit
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/API.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium {
  
  API::API(const JSContext& js_context) TITANIUM_NOEXCEPT
  : Module(js_context) {
  }
  
  API::API(const API& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : Module(rhs, arguments) {
  }
  
  void API::info(const std::string& message) const TITANIUM_NOEXCEPT {
    log(LogSeverityLevel::API_INFO, message);
  }
  
  void API::warn(const std::string& message) const TITANIUM_NOEXCEPT {
    log(LogSeverityLevel::API_WARN, message);
  }
  
  void API::error(const std::string& message) const TITANIUM_NOEXCEPT {
    log(LogSeverityLevel::API_ERROR, message);
  }
  
  void API::debug(const std::string& message) const TITANIUM_NOEXCEPT {
    log(LogSeverityLevel::API_DEBUG, message);
  }
  
  void API::trace(const std::string& message) const TITANIUM_NOEXCEPT {
    log(LogSeverityLevel::API_TRACE, message);
  }
  
  void API::log(const std::string& level, const std::string& message) const TITANIUM_NOEXCEPT {
    log(ToLogLevel(level), message);
  }
  
  void API::log(LogSeverityLevel log_severity_level, const std::string& message) const TITANIUM_NOEXCEPT {
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
        os << "[INFO] ";
        break;
    }
    
    os << message;
    log(os.str());
  }
  
  void API::log(const std::string& message) const TITANIUM_NOEXCEPT {
    TITANIUM_LOG_WARN("API::log: Unimplemented. Defaulting to std::clog");
    std::clog << message << std::endl;
  }
  
  API::LogSeverityLevel API::ToLogLevel(const std::string& level) {
    static std::unordered_map<std::string, LogSeverityLevel> log_severity_level_map;
    static std::once_flag of;
    std::call_once(of, []() {
      log_severity_level_map.emplace("info" , LogSeverityLevel::API_INFO);
      log_severity_level_map.emplace("warn" , LogSeverityLevel::API_WARN);
      log_severity_level_map.emplace("error", LogSeverityLevel::API_ERROR);
      log_severity_level_map.emplace("debug", LogSeverityLevel::API_DEBUG);
      log_severity_level_map.emplace("trace", LogSeverityLevel::API_TRACE);
    });
    
    LogSeverityLevel log_severity_level = LogSeverityLevel::API_INFO;
    const auto position = log_severity_level_map.find(level);
    
    if (position != log_severity_level_map.end()) {
      log_severity_level = position -> second;
    }
    
    return log_severity_level;
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void API::JSExportInitialize() {
    JSExport<API>::SetClassVersion(1);
    JSExport<API>::SetParent(JSExport<Module>::Class());
    JSExport<API>::AddFunctionProperty("info" , std::mem_fn(&API::infoArgumentValidator));
    JSExport<API>::AddFunctionProperty("warn" , std::mem_fn(&API::warnArgumentValidator));
    JSExport<API>::AddFunctionProperty("error", std::mem_fn(&API::errorArgumentValidator));
    JSExport<API>::AddFunctionProperty("debug", std::mem_fn(&API::debugArgumentValidator));
    JSExport<API>::AddFunctionProperty("trace", std::mem_fn(&API::traceArgumentValidator));
    JSExport<API>::AddFunctionProperty("log"  , std::mem_fn(&API::logArgumentValidator));
  }
  
  JSValue API::infoArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    std::string message = static_cast<std::string>(_0);
    info(message);
    return get_context().CreateUndefined();
  }
  
  JSValue API::warnArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    std::string message = static_cast<std::string>(_0);
    warn(message);
    return get_context().CreateUndefined();
  }
  
  JSValue API::errorArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    std::string message = static_cast<std::string>(_0);
    error(message);
    return get_context().CreateUndefined();
  }
  
  JSValue API::debugArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    std::string message = static_cast<std::string>(_0);
    debug(message);
    return get_context().CreateUndefined();
  }
  
  JSValue API::traceArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    std::string message = static_cast<std::string>(_0);
    trace(message);
    return get_context().CreateUndefined();
  }
  
  JSValue API::logArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    TITANIUM_ASSERT(arguments.size() >= 2);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    std::string level = static_cast<std::string>(_0);
    const auto _1 = arguments.at(1);
    TITANIUM_ASSERT(_1.IsString());
    std::string message = static_cast<std::string>(_1);
    log(level, message);
    return get_context().CreateUndefined();
  }
  
} // namespace Titanium
