/**
 * Titanium.API for Windows
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/API.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>

namespace TitaniumWindows {

  API::API(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::API(js_context) {
    TITANIUM_LOG_DEBUG("API::ctor Initialize");
  }

  API::API(const API& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::API(rhs, arguments) {
    TITANIUM_LOG_DEBUG("API::ctor CallAsConstructor");
  }

  void API::log(const std::string& message) const TITANIUM_NOEXCEPT{
    TITANIUM_LOG_DEBUG("API::log");
    std::clog << message << std::endl;
  }

    void API::JSExportInitialize() {
    JSExport<API>::SetClassVersion(1);
    JSExport<API>::SetParent(JSExport<Titanium::API>::Class());
  }

}  // namespace TitaniumWindows
