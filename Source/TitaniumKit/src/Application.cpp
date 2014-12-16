/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Application.hpp"
#include "Titanium/ApplicationBuilder.hpp"
#include <sstream>

namespace Titanium {
  
  Application::Application(const ApplicationBuilder& builder)
  : js_context_group__(builder.js_context_group__)
  , js_context__(builder.js_context__) {
  }
  
  JSValue Application::Run(const std::string& app_js) {
    std::ostringstream os;
    os << "require('" << app_js << "');\n";
    return js_context__.JSEvaluateScript(os.str());
  }
  
  JSContext Application::get_context() const {
    return js_context__;
  }

} // namespace Titanium {
