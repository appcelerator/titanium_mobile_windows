/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/detail/TiUtil.hpp"
#include <sstream>
#include <functional>
#include <boost/algorithm/string/predicate.hpp>

namespace Titanium {
  
  using namespace Titanium::detail;
  
  std::atomic<std::uint32_t> GlobalObject::timer_id_generator__;
  
  JSFunction GlobalObject::createRequireFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT{
    return get_context().CreateFunction("'use strict'; var exports={},module={};module.exports=exports;eval(module_js); return module.exports;", { "_exports_", "module_js" });
  }
  
  GlobalObject::GlobalObject(const JSContext& js_context) TITANIUM_NOEXCEPT
  : JSExportObject(js_context)
  , require_function__(createRequireFunction(js_context))
  , callback_map__(js_context.CreateObject()) {
  }
  
  GlobalObject::GlobalObject(const GlobalObject& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
  : JSExportObject(rhs, arguments)
  , require_function__(createRequireFunction(rhs.get_context()))
  , callback_map__(rhs.callback_map__)
  , timer_map__(rhs.timer_map__) {
  }
  
  JSObject GlobalObject::xrequire(const std::string& moduleId) TITANIUM_NOEXCEPT{
    TITANIUM_GLOBALOBJECT_LOCK_GUARD;
    
    // The module is initially empty.
    JSObject module = get_context().CreateObject();
    
    // Try to load the CommonJS resource.
    
    // TODO: Normalize moduleId (i.e. trim surrounding whitespace, append .js
    // if it's not already there, etc.).
    
    std::string module_path = moduleId;
    if (!boost::starts_with(module_path, "/")) {
      module_path = "/" + module_path;
    }
    if (!boost::ends_with(module_path, ".js")) {
      module_path += ".js";
    }

    std::string module_js = LoadResource(module_path);
    if (module_js.empty()) {
      TITANIUM_LOG_WARN("GlobalObject::require: module '", moduleId, "' failed to load");
      return module;
    }
    
    if (get_context().JSCheckScriptSyntax(module_js, moduleId)) {
      try {
        // Evaluate module_js to allow it to either populate the exports object
        // with properties or to replace the exports object wholesale.
        JSValue result = require_function__({ module, get_context().CreateString(module_js) });
        
        if (!result.IsObject()) {
          TITANIUM_LOG_WARN("GlobalObject::require: module '", moduleId, "' replaced 'exports' with a non-object: ", to_string(result));
        }
        else {
          module = result;
        }

        if (module.IsFunction()) {
          TITANIUM_LOG_DEBUG("GlobalObject::require: module '", moduleId, "' is a function: ", to_string(result));
        } else {
          TITANIUM_LOG_DEBUG("GlobalObject::require: module '", moduleId, "' is not a function: ", to_string(result));
        }
      }
      catch (const std::exception& exception) {
        TITANIUM_LOG_WARN("GlobalObject::require: module '", moduleId, "' threw exception ", exception.what());
      }
      catch (...) {
        TITANIUM_LOG_WARN("GlobalObject::require: module '", moduleId, "' threw unknown exception");
      }
    }
    else {
      // The script had a syntax error.
      TITANIUM_LOG_WARN("GlobalObject::require: module '", moduleId, "' has syntax error");
    }
    
    return module;
  }
  
  unsigned GlobalObject::setTimeout(JSObject&& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT{
    const auto timerId = timer_id_generator__++;
    
    RegisterCallback(std::move(function), timerId);
    
    Callback_t callback = [this, timerId]() mutable {
      InvokeCallback(timerId);
      clearTimeout(timerId);
    };
    
    StartTimer(std::move(callback), timerId, delay);
    
    return timerId;
  }
  
  void GlobalObject::clearTimeout(const unsigned& timerId) TITANIUM_NOEXCEPT{
    StopTimer(timerId);
  }
  
  unsigned GlobalObject::setInterval(JSObject&& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT{
    const auto timerId = timer_id_generator__++;
    
    RegisterCallback(std::move(function), timerId);
    
    Callback_t callback = [this, timerId]() mutable {
      InvokeCallback(timerId);
    };
    
    StartTimer(std::move(callback), timerId, delay);
    
    return timerId;
  }
  
  void GlobalObject::clearInterval(const unsigned& timerId) TITANIUM_NOEXCEPT{
    StopTimer(timerId);
  }
  
  void GlobalObject::RegisterCallback(JSObject&& function, const unsigned& timerId) TITANIUM_NOEXCEPT{
    const std::string timerId_str = "callback_" + std::to_string(timerId);
    callback_map__.SetProperty(timerId_str, function);
  }
  
  void GlobalObject::UnregisterCallback(const unsigned& timerId) TITANIUM_NOEXCEPT{
    const std::string timerId_str = "callback_" + std::to_string(timerId);
    TITANIUM_ASSERT(callback_map__.HasProperty(timerId_str));
    const bool callback_deleted = callback_map__.DeleteProperty(timerId_str);
    TITANIUM_ASSERT(callback_deleted);
  }
  
  void GlobalObject::InvokeCallback(const unsigned& timerId) TITANIUM_NOEXCEPT{
    const std::string timerId_str = "callback_" + std::to_string(timerId);
    TITANIUM_ASSERT(callback_map__.HasProperty(timerId_str));
    JSValue callback_property = callback_map__.GetProperty(timerId_str);
    TITANIUM_ASSERT(callback_property.IsObject());
    JSObject callback = callback_property;
    TITANIUM_ASSERT(callback.IsFunction());
    callback();
  }
  
  void GlobalObject::StartTimer(Callback_t&& callback, const unsigned& timerId, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT{
    auto timer = CreateTimer(callback, delay);
    const auto timer_insert_result = timer_map__.emplace(timerId, timer);
    const bool timer_inserted = timer_insert_result.second;
    TITANIUM_ASSERT(timer_inserted);
    TITANIUM_LOG_DEBUG("GlobalObject::setInterval: starting timer for timerId ", timerId);
    timer->Start();
  }
  
  void GlobalObject::StopTimer(const unsigned& timerId) TITANIUM_NOEXCEPT{
    const auto timer_position = timer_map__.find(timerId);
    const bool timer_found = timer_position != timer_map__.end();
    if (timer_found) {
      TITANIUM_LOG_DEBUG("GlobalObject::clearInterval: timerId ", timerId, " cleared");
      auto timer_ptr = timer_position->second;
      timer_ptr->Stop();
      const auto number_of_elements_removed = timer_map__.erase(timerId);
      TITANIUM_ASSERT(number_of_elements_removed == 1);
      
      const std::string timerId_str = "callback_" + std::to_string(timerId);
      TITANIUM_ASSERT(callback_map__.HasProperty(timerId_str));
      const bool callback_deleted = callback_map__.DeleteProperty(timerId_str);
      TITANIUM_ASSERT(callback_deleted);
    }
    else {
      TITANIUM_LOG_WARN("GlobalObject::clearTimeout: timerId ", timerId, " is not registered");
    }
    
  }
  
  std::string GlobalObject::LoadResource(const std::string& moduleId) const TITANIUM_NOEXCEPT{
    TITANIUM_LOG_ERROR("GlobalObject::LoadResource: Unimplemented");
    return "";
  }
  
  GlobalObject::Timer::Timer(Callback_t callback, const std::chrono::milliseconds& interval)
  : interval__(interval) {
    TITANIUM_LOG_DEBUG("GlobalObject::Timer: interval = ", interval.count(), "ms");
  }
  
  std::chrono::milliseconds GlobalObject::Timer::get_interval() const TITANIUM_NOEXCEPT{
    return interval__;
  }
  
  class UnimplementedTimer final : public GlobalObject::Timer {
  public:
    UnimplementedTimer(GlobalObject::Callback_t callback, const std::chrono::milliseconds& interval)
    : Timer(callback, interval) {
      TITANIUM_LOG_ERROR("GlobalObject::Timer: Unimplemented");
    }
    
    virtual ~UnimplementedTimer() {
    }
    
    virtual void Start() TITANIUM_NOEXCEPT override final{
      TITANIUM_LOG_ERROR("GlobalObject::Timer::Start: Unimplemented");
    }
    
    virtual void Stop() TITANIUM_NOEXCEPT override final{
      TITANIUM_LOG_ERROR("GlobalObject::Timer::Stop: Unimplemented");
    }
  };
  
  std::shared_ptr<GlobalObject::Timer> GlobalObject::CreateTimer(Callback_t callback, const std::chrono::milliseconds& interval) const TITANIUM_NOEXCEPT{
    TITANIUM_LOG_ERROR("GlobalObject::CreateTimer: Unimplemented");
    return std::make_shared<UnimplementedTimer>(callback, interval);
  }
  
  // TODO: The following functions can automatically be generated from
  // the YAML API docs.
  
  void GlobalObject::JSExportInitialize() {
    TITANIUM_LOG_DEBUG("GlobalObject::JSExportInitialize");
    JSExport<GlobalObject>::SetClassVersion(1);
    JSExport<GlobalObject>::SetParent(JSExport<JSExportObject>::Class());
    JSExport<GlobalObject>::AddValueProperty("global", std::mem_fn(&GlobalObject::globalArgumentValidator));
    JSExport<GlobalObject>::AddFunctionProperty("require", std::mem_fn(&GlobalObject::requireArgumentValidator));
    JSExport<GlobalObject>::AddFunctionProperty("setTimeout", std::mem_fn(&GlobalObject::setTimeoutArgumentValidator));
    JSExport<GlobalObject>::AddFunctionProperty("clearTimeout", std::mem_fn(&GlobalObject::clearTimeoutArgumentValidator));
    JSExport<GlobalObject>::AddFunctionProperty("setInterval", std::mem_fn(&GlobalObject::setIntervalArgumentValidator));
    JSExport<GlobalObject>::AddFunctionProperty("clearInterval", std::mem_fn(&GlobalObject::clearIntervalArgumentValidator));
  }
  
  JSValue GlobalObject::globalArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().JSEvaluateScript("this;");
  }

  JSValue GlobalObject::requireArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsString());
    std::string moduleId = static_cast<std::string>(_0);
    return xrequire(moduleId);
  }
  
  JSValue GlobalObject::setTimeoutArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(arguments.size() >= 2);
    const auto _0 = arguments.at(0);
    const auto _1 = arguments.at(1);
    TITANIUM_ASSERT(_0.IsObject());
    TITANIUM_ASSERT(_1.IsNumber());
    JSObject function = _0;
    TITANIUM_ASSERT(function.IsFunction());
    const auto delay = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(_1)));
    JSNumber timerId = get_context().CreateNumber(setTimeout(std::move(function), delay));
    return timerId;
  }
  
  JSValue GlobalObject::clearTimeoutArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsNumber());
    const auto timerId = static_cast<unsigned>(_0);
    clearTimeout(timerId);
    return get_context().CreateUndefined();
  }
  
  JSValue GlobalObject::setIntervalArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(arguments.size() >= 2);
    const auto _0 = arguments.at(0);
    const auto _1 = arguments.at(1);
    TITANIUM_ASSERT(_0.IsObject());
    TITANIUM_ASSERT(_1.IsNumber());
    JSObject function = _0;;
    TITANIUM_ASSERT(function.IsFunction());
    const auto delay = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(_1)));
    JSNumber timerId = get_context().CreateNumber(setInterval(std::move(function), delay));
    return timerId;
  }
  
  JSValue GlobalObject::clearIntervalArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) {
    // TODO: Validate these precondition checks (which could be
    // automaticaly generated) with the team.
    TITANIUM_ASSERT(arguments.size() >= 1);
    const auto _0 = arguments.at(0);
    TITANIUM_ASSERT(_0.IsNumber());
    const auto timerId = static_cast<unsigned>(_0);
    clearInterval(timerId);
    return get_context().CreateUndefined();
  }
  
} // namespace Titanium {
