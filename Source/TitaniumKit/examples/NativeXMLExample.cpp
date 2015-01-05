/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeXMLExample.hpp"

NativeXMLExample::NativeXMLExample(const JSContext& js_context) TITANIUM_NOEXCEPT
: Titanium::XML(js_context) {
}

NativeXMLExample::NativeXMLExample(const NativeXMLExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
: Titanium::XML(rhs, arguments) {
}

void NativeXMLExample::JSExportInitialize() {
  JSExport<NativeXMLExample>::SetClassVersion(1);
  JSExport<NativeXMLExample>::SetParent(JSExport<Titanium::XML>::Class());
}
