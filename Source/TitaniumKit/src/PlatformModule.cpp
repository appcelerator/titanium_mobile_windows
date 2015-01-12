/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/PlatformModule.hpp"
#include "Titanium/Platform/DisplayCaps.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium {

  PlatformModule::PlatformModule(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Module(js_context)
  , displayCaps__(get_context().CreateObject(JSExport<Titanium::Platform::DisplayCaps>::Class()))
  , BATTERY_STATE_CHARGING__(get_context().CreateNumber(Platform::BatteryState::CHARGING))
  , BATTERY_STATE_FULL__(get_context().CreateNumber(Platform::BatteryState::FULL))
  , BATTERY_STATE_UNKNOWN__(get_context().CreateNumber(Platform::BatteryState::UNKNOWN))
  , BATTERY_STATE_UNPLUGGED__(get_context().CreateNumber(Platform::BatteryState::UNPLUGGED))
  {
  }

  PlatformModule::PlatformModule(const PlatformModule& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Module(rhs, arguments)
  , displayCaps__(rhs.displayCaps__)
  , BATTERY_STATE_CHARGING__(rhs.BATTERY_STATE_CHARGING__)
  , BATTERY_STATE_FULL__(rhs.BATTERY_STATE_FULL__)
  , BATTERY_STATE_UNKNOWN__(rhs.BATTERY_STATE_UNKNOWN__)
  , BATTERY_STATE_UNPLUGGED__(rhs.BATTERY_STATE_UNPLUGGED__)
  {
  }

  std::string PlatformModule::address() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::architecture() const TITANIUM_NOEXCEPT {
    return "";
  }
  unsigned PlatformModule::availableMemory() const TITANIUM_NOEXCEPT {
    return 0;
  }
  double PlatformModule::batteryLevel() const TITANIUM_NOEXCEPT {
    return 0;
  }
  bool PlatformModule::batteryMonitoring() const TITANIUM_NOEXCEPT {
    return false;
  }
    Platform::BatteryState PlatformModule::batteryState() const TITANIUM_NOEXCEPT {
    return Platform::BatteryState::UNKNOWN;
  }
  std::string PlatformModule::id() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::locale() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::macaddress() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::manufacturer() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::model() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::name() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::netmask() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::osname() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::ostype() const TITANIUM_NOEXCEPT {
    return "";
  }
  unsigned PlatformModule::processorCount() const TITANIUM_NOEXCEPT {
    return 0;
  }
  std::string PlatformModule::runtime() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::username() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::version() const TITANIUM_NOEXCEPT {
    return "";
  }
  std::string PlatformModule::createUUID() TITANIUM_NOEXCEPT{
    return "";
  }

  bool PlatformModule::canOpenURL(const std::string& url) TITANIUM_NOEXCEPT {
    return false;
  }
  bool PlatformModule::openURL(const std::string& url) TITANIUM_NOEXCEPT {
    return false;
  }
  bool PlatformModule::is24HourTimeFormat() TITANIUM_NOEXCEPT {
    return false;
  }
  
  JSValue PlatformModule::get_address_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(address());
  }
  JSValue PlatformModule::get_architecture_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(architecture());
  }
  JSValue PlatformModule::get_availableMemory_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(availableMemory());
  }
  JSValue PlatformModule::get_batteryLevel_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(batteryLevel());
  }
  JSValue PlatformModule::get_batteryMonitoring_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(batteryMonitoring());
  }
  JSValue PlatformModule::get_batteryState_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(batteryState());
  }
  JSValue PlatformModule::get_id_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(id());
  }
  JSValue PlatformModule::get_locale_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(locale());
  }
  JSValue PlatformModule::get_macaddress_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(macaddress());
  }
  JSValue PlatformModule::get_manufacturer_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(manufacturer());
  }
  JSValue PlatformModule::get_model_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(model());
  }
  JSValue PlatformModule::get_name_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(name());
  }
  JSValue PlatformModule::get_netmask_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(netmask());
  }
  JSValue PlatformModule::get_osname_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(osname());
  }
  JSValue PlatformModule::get_ostype_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(ostype());
  }
  JSValue PlatformModule::get_processorCount_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateNumber(processorCount());
  }
  JSValue PlatformModule::get_runtime_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(runtime());
  }
  JSValue PlatformModule::get_username_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(username());
  }
  JSValue PlatformModule::get_version_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return get_context().CreateString(version());
  }

  JSValue PlatformModule::getAddressArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_address_ArgumentValidator();    
  }
  JSValue PlatformModule::getArchitectureArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_architecture_ArgumentValidator();    
  }
  JSValue PlatformModule::getAvailableMemoryArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_availableMemory_ArgumentValidator();    
  }
    JSValue PlatformModule::getBatteryLevelArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_batteryLevel_ArgumentValidator();
  }
    JSValue PlatformModule::getBatteryMonitoringArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_batteryMonitoring_ArgumentValidator();
  }
  JSValue PlatformModule::getBatteryStateArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_batteryState_ArgumentValidator();    
  }
  JSValue PlatformModule::getIdArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_id_ArgumentValidator();    
  }
  JSValue PlatformModule::getLocaleArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_locale_ArgumentValidator();    
  }
  JSValue PlatformModule::getMacaddressArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_macaddress_ArgumentValidator();    
  }
  JSValue PlatformModule::getManufacturerArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_manufacturer_ArgumentValidator();    
  }
  JSValue PlatformModule::getModelArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_model_ArgumentValidator();    
  }
  JSValue PlatformModule::getNameArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_name_ArgumentValidator();    
  }
  JSValue PlatformModule::getNetmaskArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_netmask_ArgumentValidator();    
  }
  JSValue PlatformModule::getOsnameArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_osname_ArgumentValidator();    
  }
  JSValue PlatformModule::getOstypeArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_ostype_ArgumentValidator();    
  }
  JSValue PlatformModule::getProcessorCountArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_processorCount_ArgumentValidator();    
  }
  JSValue PlatformModule::getRuntimeArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_runtime_ArgumentValidator();    
  }
  JSValue PlatformModule::getUsernameArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_username_ArgumentValidator();    
  }
  JSValue PlatformModule::getVersionArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT {
    return get_version_ArgumentValidator();    
  }

  JSValue PlatformModule::createUUIDArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT{
    return get_context().CreateString(createUUID());
  }

  JSValue PlatformModule::canOpenURLArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() < 1) {
      return get_context().CreateBoolean(false);
    }
    const auto _0 = static_cast<std::string>(arguments.at(0));
    return get_context().CreateBoolean(canOpenURL(_0));
  }
  JSValue PlatformModule::openURLArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    if (arguments.size() < 1) {
      return get_context().CreateBoolean(false);
    }
    const auto _0 = static_cast<std::string>(arguments.at(0));
    return get_context().CreateBoolean(openURL(_0));
  }
  JSValue PlatformModule::is24HourTimeFormatArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT {
    return get_context().CreateBoolean(is24HourTimeFormat());
  }

  void PlatformModule::setDisplayCaps(const JSValue& displayCaps) TITANIUM_NOEXCEPT {
    displayCaps__ = displayCaps;
  }
  
  JSValue PlatformModule::get_displayCaps_ArgumentValidator() const TITANIUM_NOEXCEPT {
    return displayCaps__;
  }
  
  JSValue PlatformModule::getDisplayCapsArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) const TITANIUM_NOEXCEPT {
    return get_displayCaps_ArgumentValidator();
  }
  
  JSValue PlatformModule::get_BATTERY_STATE_CHARGING() const TITANIUM_NOEXCEPT {
    return BATTERY_STATE_CHARGING__;
  }
  
  JSValue PlatformModule::get_BATTERY_STATE_FULL() const TITANIUM_NOEXCEPT {
    return BATTERY_STATE_FULL__;
  }
  
  JSValue PlatformModule::get_BATTERY_STATE_UNKNOWN() const TITANIUM_NOEXCEPT {
    return BATTERY_STATE_UNKNOWN__;
  }
  
  JSValue PlatformModule::get_BATTERY_STATE_UNPLUGGED() const TITANIUM_NOEXCEPT {
    return BATTERY_STATE_UNPLUGGED__;
  }

  void PlatformModule::JSExportInitialize() {
    JSExport<PlatformModule>::SetClassVersion(1);
    JSExport<PlatformModule>::SetParent(JSExport<Module>::Class());
    JSExport<PlatformModule>::AddValueProperty("address", std::mem_fn(&PlatformModule::get_address_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("architecture", std::mem_fn(&PlatformModule::get_architecture_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("availableMemory", std::mem_fn(&PlatformModule::get_availableMemory_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("batteryState", std::mem_fn(&PlatformModule::get_batteryState_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("id", std::mem_fn(&PlatformModule::get_id_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("locale", std::mem_fn(&PlatformModule::get_locale_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("macaddress", std::mem_fn(&PlatformModule::get_macaddress_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("manufacturer", std::mem_fn(&PlatformModule::get_manufacturer_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("model", std::mem_fn(&PlatformModule::get_model_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("name", std::mem_fn(&PlatformModule::get_name_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("netmask", std::mem_fn(&PlatformModule::get_netmask_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("osname", std::mem_fn(&PlatformModule::get_osname_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("ostype", std::mem_fn(&PlatformModule::get_ostype_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("processorCount", std::mem_fn(&PlatformModule::get_processorCount_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("runtime", std::mem_fn(&PlatformModule::get_runtime_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("username", std::mem_fn(&PlatformModule::get_username_ArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("version", std::mem_fn(&PlatformModule::get_version_ArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getAddress", std::mem_fn(&PlatformModule::getAddressArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getArchitecture", std::mem_fn(&PlatformModule::getArchitectureArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getAvailableMemory", std::mem_fn(&PlatformModule::getAvailableMemoryArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getBatteryLevel", std::mem_fn(&PlatformModule::getBatteryLevelArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getBatteryMonitoring", std::mem_fn(&PlatformModule::getBatteryMonitoringArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getBatteryState", std::mem_fn(&PlatformModule::getBatteryStateArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getId", std::mem_fn(&PlatformModule::getIdArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getLocale", std::mem_fn(&PlatformModule::getLocaleArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getMacaddress", std::mem_fn(&PlatformModule::getMacaddressArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getManufacturer", std::mem_fn(&PlatformModule::getManufacturerArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getModel", std::mem_fn(&PlatformModule::getModelArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getName", std::mem_fn(&PlatformModule::getNameArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getNetmask", std::mem_fn(&PlatformModule::getNetmaskArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getOsname", std::mem_fn(&PlatformModule::getOsnameArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getOstype", std::mem_fn(&PlatformModule::getOstypeArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getProcessorCount", std::mem_fn(&PlatformModule::getProcessorCountArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getRuntime", std::mem_fn(&PlatformModule::getRuntimeArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getUsername", std::mem_fn(&PlatformModule::getUsernameArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getVersion", std::mem_fn(&PlatformModule::getVersionArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("createUUID", std::mem_fn(&PlatformModule::createUUIDArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("canOpenURL", std::mem_fn(&PlatformModule::canOpenURLArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("openURL", std::mem_fn(&PlatformModule::openURLArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("is24HourTimeFormat", std::mem_fn(&PlatformModule::is24HourTimeFormatArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("displayCaps", std::mem_fn(&PlatformModule::get_displayCaps_ArgumentValidator));
    JSExport<PlatformModule>::AddFunctionProperty("getDisplayCaps", std::mem_fn(&PlatformModule::getDisplayCapsArgumentValidator));
    JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_CHARGING", std::mem_fn(&PlatformModule::get_BATTERY_STATE_CHARGING));
    JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_FULL", std::mem_fn(&PlatformModule::get_BATTERY_STATE_FULL));
    JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_UNKNOWN", std::mem_fn(&PlatformModule::get_BATTERY_STATE_UNKNOWN));
    JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_UNPLUGGED", std::mem_fn(&PlatformModule::get_BATTERY_STATE_UNPLUGGED));
  }

} // namespace Titanium
