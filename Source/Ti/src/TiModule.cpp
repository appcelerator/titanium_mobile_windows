/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/TiModule.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>
#include <objbase.h>

namespace TitaniumWindows {

  TiModule::TiModule(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::TiModule(js_context) {
    TITANIUM_LOG_DEBUG("TitaniumWindows::TiModule::ctor Initialize");
    setUserAgent(get_context().CreateString("__TITANIUM_USER_AGENT__"));
  }

  TiModule::TiModule(const TiModule& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::TiModule(rhs, arguments) {
    TITANIUM_LOG_DEBUG("TitaniumWindows::TiModule::ctor CallAsConstructor");
  }

  TiModule::~TiModule() {
    TITANIUM_LOG_DEBUG("TitaniumWindows::TiModule::dtor");
  }

  void TiModule::JSExportInitialize() {
    JSExport<TiModule>::SetClassVersion(1);
    JSExport<TiModule>::SetParent(JSExport<Titanium::TiModule>::Class());
  }

  std::string TiModule::version() const TITANIUM_NOEXCEPT {
    return "__TITANIUM_VERSION__";
  }

  std::string TiModule::buildDate() const TITANIUM_NOEXCEPT {
    return "__TITANIUM_BUILD_DATE__";
  }

  std::string TiModule::buildHash() const TITANIUM_NOEXCEPT {
    return "__TITANIUM_BUILD_HASH__";
  }

}  // namespace TitaniumWindows
