/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/PlatformModule.hpp"
#include "Titanium/Platform/DisplayCaps.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	PlatformModule::PlatformModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Module(js_context, arguments),
	      displayCaps__(get_context().CreateObject(JSExport<Titanium::Platform::DisplayCaps>::Class())),
	      BATTERY_STATE_CHARGING__(get_context().CreateNumber(Platform::BatteryState::CHARGING)),
	      BATTERY_STATE_FULL__(get_context().CreateNumber(Platform::BatteryState::FULL)),
	      BATTERY_STATE_UNKNOWN__(get_context().CreateNumber(Platform::BatteryState::UNKNOWN)),
	      BATTERY_STATE_UNPLUGGED__(get_context().CreateNumber(Platform::BatteryState::UNPLUGGED))
	{
	}

	std::string PlatformModule::address() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::architecture() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	unsigned PlatformModule::availableMemory() const TITANIUM_NOEXCEPT
	{
		return 0;
	}
	double PlatformModule::batteryLevel() const TITANIUM_NOEXCEPT
	{
		return 0;
	}
	bool PlatformModule::batteryMonitoring() const TITANIUM_NOEXCEPT
	{
		return false;
	}
	Platform::BatteryState PlatformModule::batteryState() const TITANIUM_NOEXCEPT
	{
		return Platform::BatteryState::UNKNOWN;
	}
	std::string PlatformModule::id() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::locale() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::macaddress() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::manufacturer() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::model() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::name() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::netmask() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::osname() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::ostype() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	unsigned PlatformModule::processorCount() const TITANIUM_NOEXCEPT
	{
		return 0;
	}
	std::string PlatformModule::runtime() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::username() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::version() const TITANIUM_NOEXCEPT
	{
		return "";
	}
	std::string PlatformModule::createUUID() TITANIUM_NOEXCEPT
	{
		return "";
	}

	bool PlatformModule::canOpenURL(const std::string& url) TITANIUM_NOEXCEPT
	{
		return false;
	}
	bool PlatformModule::openURL(const std::string& url) TITANIUM_NOEXCEPT
	{
		return false;
	}
	bool PlatformModule::is24HourTimeFormat() TITANIUM_NOEXCEPT
	{
		return false;
	}

	JSValue PlatformModule::js_get_address() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(address());
	}
	JSValue PlatformModule::js_get_architecture() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(architecture());
	}
	JSValue PlatformModule::js_get_availableMemory() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(availableMemory());
	}
	JSValue PlatformModule::js_get_batteryLevel() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(batteryLevel());
	}
	JSValue PlatformModule::js_get_batteryMonitoring() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(batteryMonitoring());
	}
	JSValue PlatformModule::js_get_batteryState() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(batteryState());
	}
	JSValue PlatformModule::js_get_id() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(id());
	}
	JSValue PlatformModule::js_get_locale() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(locale());
	}
	JSValue PlatformModule::js_get_macaddress() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(macaddress());
	}
	JSValue PlatformModule::js_get_manufacturer() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(manufacturer());
	}
	JSValue PlatformModule::js_get_model() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(model());
	}
	JSValue PlatformModule::js_get_name() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(name());
	}
	JSValue PlatformModule::js_get_netmask() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(netmask());
	}
	JSValue PlatformModule::js_get_osname() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(osname());
	}
	JSValue PlatformModule::js_get_ostype() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(ostype());
	}
	JSValue PlatformModule::js_get_processorCount() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(processorCount());
	}
	JSValue PlatformModule::js_get_runtime() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(runtime());
	}
	JSValue PlatformModule::js_get_username() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(username());
	}
	JSValue PlatformModule::js_get_version() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(version());
	}

	JSValue PlatformModule::js_getAddress(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_address();
	}
	JSValue PlatformModule::js_getArchitecture(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_architecture();
	}
	JSValue PlatformModule::js_getAvailableMemory(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_availableMemory();
	}
	JSValue PlatformModule::js_getBatteryLevel(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_batteryLevel();
	}
	JSValue PlatformModule::js_getBatteryMonitoring(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_batteryMonitoring();
	}
	JSValue PlatformModule::js_getBatteryState(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_batteryState();
	}
	JSValue PlatformModule::js_getId(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_id();
	}
	JSValue PlatformModule::js_getLocale(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_locale();
	}
	JSValue PlatformModule::js_getMacaddress(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_macaddress();
	}
	JSValue PlatformModule::js_getManufacturer(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_manufacturer();
	}
	JSValue PlatformModule::js_getModel(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_model();
	}
	JSValue PlatformModule::js_getName(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_name();
	}
	JSValue PlatformModule::js_getNetmask(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_netmask();
	}
	JSValue PlatformModule::js_getOsname(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_osname();
	}
	JSValue PlatformModule::js_getOstype(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_ostype();
	}
	JSValue PlatformModule::js_getProcessorCount(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_processorCount();
	}
	JSValue PlatformModule::js_getRuntime(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_runtime();
	}
	JSValue PlatformModule::js_getUsername(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_username();
	}
	JSValue PlatformModule::js_getVersion(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
	{
		return js_get_version();
	}

	JSValue PlatformModule::js_createUUID(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(createUUID());
	}

	JSValue PlatformModule::js_canOpenURL(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() < 1) {
			return get_context().CreateBoolean(false);
		}
		const auto _0 = static_cast<std::string>(arguments.at(0));
		return get_context().CreateBoolean(canOpenURL(_0));
	}
	JSValue PlatformModule::js_openURL(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() < 1) {
			return get_context().CreateBoolean(false);
		}
		const auto _0 = static_cast<std::string>(arguments.at(0));
		return get_context().CreateBoolean(openURL(_0));
	}
	JSValue PlatformModule::js_is24HourTimeFormat(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(is24HourTimeFormat());
	}

	void PlatformModule::setDisplayCaps(const JSValue& displayCaps) TITANIUM_NOEXCEPT
	{
		displayCaps__ = displayCaps;
	}

	JSValue PlatformModule::js_get_displayCaps() const TITANIUM_NOEXCEPT
	{
		return displayCaps__;
	}

	JSValue PlatformModule::js_getDisplayCaps(const std::vector<JSValue>& arguments, JSObject& this_object) const TITANIUM_NOEXCEPT
	{
		return js_get_displayCaps();
	}

	JSValue PlatformModule::js_get_BATTERY_STATE_CHARGING() const TITANIUM_NOEXCEPT
	{
		return BATTERY_STATE_CHARGING__;
	}

	JSValue PlatformModule::js_get_BATTERY_STATE_FULL() const TITANIUM_NOEXCEPT
	{
		return BATTERY_STATE_FULL__;
	}

	JSValue PlatformModule::js_get_BATTERY_STATE_UNKNOWN() const TITANIUM_NOEXCEPT
	{
		return BATTERY_STATE_UNKNOWN__;
	}

	JSValue PlatformModule::js_get_BATTERY_STATE_UNPLUGGED() const TITANIUM_NOEXCEPT
	{
		return BATTERY_STATE_UNPLUGGED__;
	}

	void PlatformModule::JSExportInitialize()
	{
		JSExport<PlatformModule>::SetClassVersion(1);
		JSExport<PlatformModule>::SetParent(JSExport<Module>::Class());
		JSExport<PlatformModule>::AddValueProperty("address", std::mem_fn(&PlatformModule::js_get_address));
		JSExport<PlatformModule>::AddValueProperty("architecture", std::mem_fn(&PlatformModule::js_get_architecture));
		JSExport<PlatformModule>::AddValueProperty("availableMemory", std::mem_fn(&PlatformModule::js_get_availableMemory));
		JSExport<PlatformModule>::AddValueProperty("batteryState", std::mem_fn(&PlatformModule::js_get_batteryState));
		JSExport<PlatformModule>::AddValueProperty("id", std::mem_fn(&PlatformModule::js_get_id));
		JSExport<PlatformModule>::AddValueProperty("locale", std::mem_fn(&PlatformModule::js_get_locale));
		JSExport<PlatformModule>::AddValueProperty("macaddress", std::mem_fn(&PlatformModule::js_get_macaddress));
		JSExport<PlatformModule>::AddValueProperty("manufacturer", std::mem_fn(&PlatformModule::js_get_manufacturer));
		JSExport<PlatformModule>::AddValueProperty("model", std::mem_fn(&PlatformModule::js_get_model));
		JSExport<PlatformModule>::AddValueProperty("name", std::mem_fn(&PlatformModule::js_get_name));
		JSExport<PlatformModule>::AddValueProperty("netmask", std::mem_fn(&PlatformModule::js_get_netmask));
		JSExport<PlatformModule>::AddValueProperty("osname", std::mem_fn(&PlatformModule::js_get_osname));
		JSExport<PlatformModule>::AddValueProperty("ostype", std::mem_fn(&PlatformModule::js_get_ostype));
		JSExport<PlatformModule>::AddValueProperty("processorCount", std::mem_fn(&PlatformModule::js_get_processorCount));
		JSExport<PlatformModule>::AddValueProperty("runtime", std::mem_fn(&PlatformModule::js_get_runtime));
		JSExport<PlatformModule>::AddValueProperty("username", std::mem_fn(&PlatformModule::js_get_username));
		JSExport<PlatformModule>::AddValueProperty("version", std::mem_fn(&PlatformModule::js_get_version));
		JSExport<PlatformModule>::AddFunctionProperty("getAddress", std::mem_fn(&PlatformModule::js_getAddress));
		JSExport<PlatformModule>::AddFunctionProperty("getArchitecture", std::mem_fn(&PlatformModule::js_getArchitecture));
		JSExport<PlatformModule>::AddFunctionProperty("getAvailableMemory", std::mem_fn(&PlatformModule::js_getAvailableMemory));
		JSExport<PlatformModule>::AddFunctionProperty("getBatteryLevel", std::mem_fn(&PlatformModule::js_getBatteryLevel));
		JSExport<PlatformModule>::AddFunctionProperty("getBatteryMonitoring", std::mem_fn(&PlatformModule::js_getBatteryMonitoring));
		JSExport<PlatformModule>::AddFunctionProperty("getBatteryState", std::mem_fn(&PlatformModule::js_getBatteryState));
		JSExport<PlatformModule>::AddFunctionProperty("getId", std::mem_fn(&PlatformModule::js_getId));
		JSExport<PlatformModule>::AddFunctionProperty("getLocale", std::mem_fn(&PlatformModule::js_getLocale));
		JSExport<PlatformModule>::AddFunctionProperty("getMacaddress", std::mem_fn(&PlatformModule::js_getMacaddress));
		JSExport<PlatformModule>::AddFunctionProperty("getManufacturer", std::mem_fn(&PlatformModule::js_getManufacturer));
		JSExport<PlatformModule>::AddFunctionProperty("getModel", std::mem_fn(&PlatformModule::js_getModel));
		JSExport<PlatformModule>::AddFunctionProperty("getName", std::mem_fn(&PlatformModule::js_getName));
		JSExport<PlatformModule>::AddFunctionProperty("getNetmask", std::mem_fn(&PlatformModule::js_getNetmask));
		JSExport<PlatformModule>::AddFunctionProperty("getOsname", std::mem_fn(&PlatformModule::js_getOsname));
		JSExport<PlatformModule>::AddFunctionProperty("getOstype", std::mem_fn(&PlatformModule::js_getOstype));
		JSExport<PlatformModule>::AddFunctionProperty("getProcessorCount", std::mem_fn(&PlatformModule::js_getProcessorCount));
		JSExport<PlatformModule>::AddFunctionProperty("getRuntime", std::mem_fn(&PlatformModule::js_getRuntime));
		JSExport<PlatformModule>::AddFunctionProperty("getUsername", std::mem_fn(&PlatformModule::js_getUsername));
		JSExport<PlatformModule>::AddFunctionProperty("getVersion", std::mem_fn(&PlatformModule::js_getVersion));
		JSExport<PlatformModule>::AddFunctionProperty("createUUID", std::mem_fn(&PlatformModule::js_createUUID));
		JSExport<PlatformModule>::AddFunctionProperty("canOpenURL", std::mem_fn(&PlatformModule::js_canOpenURL));
		JSExport<PlatformModule>::AddFunctionProperty("openURL", std::mem_fn(&PlatformModule::js_openURL));
		JSExport<PlatformModule>::AddFunctionProperty("is24HourTimeFormat", std::mem_fn(&PlatformModule::js_is24HourTimeFormat));
		JSExport<PlatformModule>::AddValueProperty("displayCaps", std::mem_fn(&PlatformModule::js_get_displayCaps));
		JSExport<PlatformModule>::AddFunctionProperty("getDisplayCaps", std::mem_fn(&PlatformModule::js_getDisplayCaps));
		JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_CHARGING", std::mem_fn(&PlatformModule::js_get_BATTERY_STATE_CHARGING));
		JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_FULL", std::mem_fn(&PlatformModule::js_get_BATTERY_STATE_FULL));
		JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_UNKNOWN", std::mem_fn(&PlatformModule::js_get_BATTERY_STATE_UNKNOWN));
		JSExport<PlatformModule>::AddValueProperty("BATTERY_STATE_UNPLUGGED", std::mem_fn(&PlatformModule::js_get_BATTERY_STATE_UNPLUGGED));
	}

}  // namespace Titanium
