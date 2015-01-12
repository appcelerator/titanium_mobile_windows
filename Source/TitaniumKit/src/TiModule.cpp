/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/TiModule.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium {

  TiModule::TiModule(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Module(js_context),
        userAgent__(js_context.CreateString()) {
  }

  TiModule::TiModule(const TiModule& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Module(rhs, arguments),
        userAgent__(rhs.userAgent__) {
  }

  void TiModule::JSExportInitialize() {
      JSExport<TiModule>::SetClassVersion(1);
      JSExport<TiModule>::SetParent(JSExport<Module>::Class());
      JSExport<TiModule>::AddValueProperty("version", std::mem_fn(&TiModule::get_version_ArgumentValidator));
      JSExport<TiModule>::AddFunctionProperty("getVersion", std::mem_fn(&TiModule::getVersionArgumentValidator));
      JSExport<TiModule>::AddValueProperty("buildDate", std::mem_fn(&TiModule::get_buildDate_ArgumentValidator));
      JSExport<TiModule>::AddFunctionProperty("getBuildDate", std::mem_fn(&TiModule::getBuildDateArgumentValidator));
      JSExport<TiModule>::AddValueProperty("buildHash", std::mem_fn(&TiModule::get_buildHash_ArgumentValidator));
      JSExport<TiModule>::AddFunctionProperty("getBuildHash", std::mem_fn(&TiModule::getBuildHashArgumentValidator));
      JSExport<TiModule>::AddValueProperty("userAgent", std::mem_fn(&TiModule::get_userAgent_ArgumentValidator), std::mem_fn(&TiModule::set_userAgent_ArgumentValidator));
      JSExport<TiModule>::AddFunctionProperty("getUserAgent", std::mem_fn(&TiModule::getUserAgentArgumentValidator));
      JSExport<TiModule>::AddFunctionProperty("setUserAgent", std::mem_fn(&TiModule::setUserAgentArgumentValidator));
      JSExport<TiModule>::AddFunctionProperty("createBuffer", std::mem_fn(&TiModule::createBufferArgumentValidator));
  }
    
    std::string TiModule::version() const TITANIUM_NOEXCEPT {
        TITANIUM_LOG_WARN("TiModule::version: Unimplemented");
        return "";
    }

    JSValue TiModule::get_version_ArgumentValidator() const TITANIUM_NOEXCEPT {
        return get_context().CreateString(version());
    }
    
    JSValue TiModule::getVersionArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
        return get_version_ArgumentValidator();
    }

    std::string TiModule::buildDate() const TITANIUM_NOEXCEPT {
        TITANIUM_LOG_WARN("TiModule::buildDate: Unimplemented");
        return "";
    }

    JSValue TiModule::get_buildDate_ArgumentValidator() const TITANIUM_NOEXCEPT {
        return get_context().CreateString(buildDate());
    }
    
    JSValue TiModule::getBuildDateArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
        return get_buildDate_ArgumentValidator();
    }

    std::string TiModule::buildHash() const TITANIUM_NOEXCEPT {
        TITANIUM_LOG_WARN("TiModule::buildHash: Unimplemented");
        return "";
    }

    JSValue TiModule::get_buildHash_ArgumentValidator() const TITANIUM_NOEXCEPT {
        return get_context().CreateString(buildHash());
    }
    
    JSValue TiModule::getBuildHashArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
        return get_buildHash_ArgumentValidator();
    }

    JSValue TiModule::get_userAgent_ArgumentValidator() const TITANIUM_NOEXCEPT {
        return userAgent__;
    }
    
    JSValue TiModule::getUserAgentArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
        return get_userAgent_ArgumentValidator();
    }

    JSValue TiModule::setUserAgentArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
      if (arguments.size() < 1) {
        return get_context().CreateUndefined();
      }
      const auto _0 = arguments.at(0);
      TITANIUM_ASSERT(_0.IsString());
      setUserAgent(_0);
      return get_context().CreateUndefined();
    }

    void TiModule::setUserAgent(const JSValue& userAgent) TITANIUM_NOEXCEPT {
        userAgent__ = userAgent;
    }

    bool TiModule::set_userAgent_ArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
        setUserAgent(argument);
        return true; 
    }

    JSValue TiModule::createBufferArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
        TITANIUM_LOG_WARN("TiModule::createBufferArgumentValidator: Unimplemented");
        return get_context().CreateNull();
    }


} // namespace Titanium
