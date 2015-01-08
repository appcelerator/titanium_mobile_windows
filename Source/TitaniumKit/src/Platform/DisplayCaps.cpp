/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Platform/DisplayCaps.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium {
namespace Platform {

DisplayCaps::DisplayCaps(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Module(js_context) {
}

DisplayCaps::DisplayCaps(const DisplayCaps& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Module(rhs, arguments) {
}
void DisplayCaps::JSExportInitialize() {
  JSExport<DisplayCaps>::SetClassVersion(1);
  JSExport<DisplayCaps>::SetParent(JSExport<Module>::Class());
  JSExport<DisplayCaps>::AddValueProperty("density", std::mem_fn(&DisplayCaps::get_density_ArgumentValidator));
  JSExport<DisplayCaps>::AddFunctionProperty("getDensity", std::mem_fn(&DisplayCaps::getDensityArgumentValidator));
  JSExport<DisplayCaps>::AddValueProperty("dpi", std::mem_fn(&DisplayCaps::get_dpi_ArgumentValidator));
  JSExport<DisplayCaps>::AddFunctionProperty("getDpi", std::mem_fn(&DisplayCaps::getDpiArgumentValidator));
  JSExport<DisplayCaps>::AddValueProperty("logicalDensityFactor", std::mem_fn(&DisplayCaps::get_logicalDensityFactor_ArgumentValidator));
  JSExport<DisplayCaps>::AddFunctionProperty("getLogicalDensityFactor", std::mem_fn(&DisplayCaps::getLogicalDensityFactorArgumentValidator));
  JSExport<DisplayCaps>::AddValueProperty("platformHeight", std::mem_fn(&DisplayCaps::get_platformHeight_ArgumentValidator));
  JSExport<DisplayCaps>::AddFunctionProperty("getPlatformHeight", std::mem_fn(&DisplayCaps::getPlatformHeightArgumentValidator));
  JSExport<DisplayCaps>::AddValueProperty("platformWidth", std::mem_fn(&DisplayCaps::get_platformWidth_ArgumentValidator));
  JSExport<DisplayCaps>::AddFunctionProperty("getPlatformWidth", std::mem_fn(&DisplayCaps::getPlatformWidthArgumentValidator));
  JSExport<DisplayCaps>::AddValueProperty("xdpi", std::mem_fn(&DisplayCaps::get_xdpi_ArgumentValidator));
  JSExport<DisplayCaps>::AddFunctionProperty("getXdpi", std::mem_fn(&DisplayCaps::getXdpiArgumentValidator));
  JSExport<DisplayCaps>::AddValueProperty("ydpi", std::mem_fn(&DisplayCaps::get_ydpi_ArgumentValidator));
  JSExport<DisplayCaps>::AddFunctionProperty("getYdpi", std::mem_fn(&DisplayCaps::getYdpiArgumentValidator));
}

std::string DisplayCaps::density() const TITANIUM_NOEXCEPT {
  return "";
}
double DisplayCaps::dpi() const TITANIUM_NOEXCEPT {
  return 0;
}
double DisplayCaps::logicalDensityFactor() const TITANIUM_NOEXCEPT {
  return 0;
}
double DisplayCaps::platformHeight() const TITANIUM_NOEXCEPT {
  return 0;
}
double DisplayCaps::platformWidth() const TITANIUM_NOEXCEPT {
  return 0;
}
double DisplayCaps::xdpi() const TITANIUM_NOEXCEPT {
  return 0;
}
double DisplayCaps::ydpi() const TITANIUM_NOEXCEPT {
  return 0;
}

JSValue DisplayCaps::get_density_ArgumentValidator() const TITANIUM_NOEXCEPT {
  return get_context().CreateString(density());
}
JSValue DisplayCaps::getDensityArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
  return get_density_ArgumentValidator();
}
JSValue DisplayCaps::get_dpi_ArgumentValidator() const TITANIUM_NOEXCEPT {
  return get_context().CreateNumber(dpi());
}
JSValue DisplayCaps::getDpiArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
  return get_dpi_ArgumentValidator();
}
JSValue DisplayCaps::get_logicalDensityFactor_ArgumentValidator() const TITANIUM_NOEXCEPT {
  return get_context().CreateNumber(logicalDensityFactor());
}
JSValue DisplayCaps::getLogicalDensityFactorArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
  return get_logicalDensityFactor_ArgumentValidator();
}
JSValue DisplayCaps::get_platformHeight_ArgumentValidator() const TITANIUM_NOEXCEPT {
  return get_context().CreateNumber(platformHeight());
}
JSValue DisplayCaps::getPlatformHeightArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
  return get_platformHeight_ArgumentValidator();
}
JSValue DisplayCaps::get_platformWidth_ArgumentValidator() const TITANIUM_NOEXCEPT {
  return get_context().CreateNumber(platformWidth());
}
JSValue DisplayCaps::getPlatformWidthArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
  return get_platformWidth_ArgumentValidator();
}
JSValue DisplayCaps::get_xdpi_ArgumentValidator() const TITANIUM_NOEXCEPT {
  return get_context().CreateNumber(xdpi());
}
JSValue DisplayCaps::getXdpiArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
  return get_xdpi_ArgumentValidator();
}
JSValue DisplayCaps::get_ydpi_ArgumentValidator() const TITANIUM_NOEXCEPT {
  return get_context().CreateNumber(ydpi());
}
JSValue DisplayCaps::getYdpiArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
  return get_ydpi_ArgumentValidator();
}
}
}  // namespace Titanium { namespace Platform {
