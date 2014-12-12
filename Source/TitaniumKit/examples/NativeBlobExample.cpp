/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeBlobExample.hpp"
#include <iostream>

NativeBlobExample::NativeBlobExample(const JSContext& js_context) TITANIUM_NOEXCEPT
: Titanium::Blob(js_context) {
}

NativeBlobExample::NativeBlobExample(const NativeBlobExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
: Titanium::Blob(rhs, arguments) {
}

void NativeBlobExample::JSExportInitialize() {
  JSExport<NativeBlobExample>::SetClassVersion(1);
  JSExport<NativeBlobExample>::SetParent(JSExport<Titanium::Blob>::Class());
}

unsigned NativeBlobExample::get_length() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::get_length");
  return 0;
}

unsigned NativeBlobExample::get_height() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::get_height");
  return 0;
}

std::string NativeBlobExample::get_mimeType() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::get_mimeType");
  return "";
}

std::string NativeBlobExample::get_nativePath() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::get_nativePath");
  return "";
}

unsigned NativeBlobExample::get_size() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::get_size");
  return 0;
}

std::string NativeBlobExample::get_text() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::get_text");
  return "";
}

unsigned NativeBlobExample::get_width() const TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::get_width");
  return 0;
}

void NativeBlobExample::append(std::shared_ptr<Blob>&) TITANIUM_NOEXCEPT {
  TITANIUM_LOG_DEBUG("NativeBlobExample::append");
}
