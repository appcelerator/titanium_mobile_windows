/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/PlatformModule.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Platform/DisplayCaps.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	PlatformModule::PlatformModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti.Platform"),
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

	std::uint64_t PlatformModule::availableMemory() const TITANIUM_NOEXCEPT
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

	void PlatformModule::set_batteryMonitoring(const bool& batteryMonitoring) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("PlatformModule::set_batteryMonitoring: Unimplemented");
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

	TITANIUM_PROPERTY_GETTER(PlatformModule, address)
	{
		return get_context().CreateString(address());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, architecture)
	{
		return get_context().CreateString(architecture());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, availableMemory)
	{
		return get_context().CreateNumber(static_cast<double>(availableMemory()));
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, batteryLevel)
	{
		return get_context().CreateNumber(batteryLevel());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, batteryMonitoring)
	{
		return get_context().CreateBoolean(batteryMonitoring());
	}

	TITANIUM_PROPERTY_SETTER(PlatformModule, batteryMonitoring)
	{
		TITANIUM_ASSERT(argument.IsBoolean());
		set_batteryMonitoring(static_cast<bool>(argument));
		return true;
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, batteryState)
	{
		return get_context().CreateNumber(batteryState());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, id)
	{
		return get_context().CreateString(id());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, locale)
	{
		return get_context().CreateString(locale());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, macaddress)
	{
		return get_context().CreateString(macaddress());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, manufacturer)
	{
		return get_context().CreateString(manufacturer());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, model)
	{
		return get_context().CreateString(model());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, name)
	{
		return get_context().CreateString(name());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, netmask)
	{
		return get_context().CreateString(netmask());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, osname)
	{
		return get_context().CreateString(osname());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, ostype)
	{
		return get_context().CreateString(ostype());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, processorCount)
	{
		return get_context().CreateNumber(processorCount());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, runtime)
	{
		return get_context().CreateString(runtime());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, username)
	{
		return get_context().CreateString(username());
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, version)
	{
		return get_context().CreateString(version());
	}

	TITANIUM_FUNCTION(PlatformModule, getAddress)
	{
		return js_get_address();
	}

	TITANIUM_FUNCTION(PlatformModule, getArchitecture)
	{
		return js_get_architecture();
	}

	TITANIUM_FUNCTION(PlatformModule, getAvailableMemory)
	{
		return js_get_availableMemory();
	}

	TITANIUM_FUNCTION(PlatformModule, getBatteryLevel)
	{
		return js_get_batteryLevel();
	}

	TITANIUM_FUNCTION(PlatformModule, getBatteryMonitoring)
	{
		return js_get_batteryMonitoring();
	}

	TITANIUM_FUNCTION(PlatformModule, setBatteryMonitoring)
	{
		TITANIUM_ASSERT(arguments.size() == 1);

		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();

		platform_ptr->js_set_batteryMonitoring(arguments.at(0));

		return this_object.get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(PlatformModule, getBatteryState)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_batteryState();
	}

	TITANIUM_FUNCTION(PlatformModule, getId)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_id();
	}

	TITANIUM_FUNCTION(PlatformModule, getLocale)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_locale();
	}

	TITANIUM_FUNCTION(PlatformModule, getMacaddress)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_macaddress();
	}

	TITANIUM_FUNCTION(PlatformModule, getManufacturer)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_manufacturer();
	}

	TITANIUM_FUNCTION(PlatformModule, getModel)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_model();
	}

	TITANIUM_FUNCTION(PlatformModule, getName)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_name();
	}

	TITANIUM_FUNCTION(PlatformModule, getNetmask)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_netmask();
	}

	TITANIUM_FUNCTION(PlatformModule, getOsname)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_osname();
	}

	TITANIUM_FUNCTION(PlatformModule, getOstype)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_ostype();
	}

	TITANIUM_FUNCTION(PlatformModule, getProcessorCount)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_processorCount();
	}
	TITANIUM_FUNCTION(PlatformModule, getRuntime)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_runtime();
	}

	TITANIUM_FUNCTION(PlatformModule, getUsername)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_username();
	}

	TITANIUM_FUNCTION(PlatformModule, getVersion)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_version();
	}

	TITANIUM_FUNCTION(PlatformModule, createUUID)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return js_context.CreateString(platform_ptr->createUUID());
	}

	TITANIUM_FUNCTION(PlatformModule, canOpenURL)
	{
		const auto js_context = this_object.get_context();
		if (arguments.size() < 1) {
			return js_context.CreateBoolean(false);
		}
		const auto _0 = static_cast<std::string>(arguments.at(0));
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return js_context.CreateBoolean(platform_ptr->canOpenURL(_0));
	}
	TITANIUM_FUNCTION(PlatformModule, openURL)
	{
		const auto js_context = this_object.get_context();
		if (arguments.size() < 1) {
			return get_context().CreateBoolean(false);
		}
		const auto _0 = static_cast<std::string>(arguments.at(0));
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return js_context.CreateBoolean(platform_ptr->openURL(_0));
	}

	TITANIUM_FUNCTION(PlatformModule, is24HourTimeFormat)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return js_context.CreateBoolean(platform_ptr->is24HourTimeFormat());
	}

	void PlatformModule::setDisplayCaps(const JSValue& displayCaps) TITANIUM_NOEXCEPT
	{
		displayCaps__ = displayCaps;
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, displayCaps)
	{
		return displayCaps__;
	}

	TITANIUM_FUNCTION(PlatformModule, getDisplayCaps)
	{
		const auto js_context = this_object.get_context();
		const auto platform_ptr = GetStaticObject(js_context).GetPrivate<PlatformModule>();
		return platform_ptr->js_get_displayCaps();
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, BATTERY_STATE_CHARGING)
	{
		return BATTERY_STATE_CHARGING__;
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, BATTERY_STATE_FULL)
	{
		return BATTERY_STATE_FULL__;
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, BATTERY_STATE_UNKNOWN)
	{
		return BATTERY_STATE_UNKNOWN__;
	}

	TITANIUM_PROPERTY_GETTER(PlatformModule, BATTERY_STATE_UNPLUGGED)
	{
		return BATTERY_STATE_UNPLUGGED__;
	}

	JSObject PlatformModule::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Object_property = Titanium.GetProperty("Platform");
		TITANIUM_ASSERT(Object_property.IsObject());  // precondition
		return static_cast<JSObject>(Object_property);
	}

	void PlatformModule::JSExportInitialize()
	{
		JSExport<PlatformModule>::SetClassVersion(1);
		JSExport<PlatformModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, address);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, architecture);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, availableMemory);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, batteryLevel);
		TITANIUM_ADD_PROPERTY(PlatformModule, batteryMonitoring);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, batteryState);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, id);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, locale);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, macaddress);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, manufacturer);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, model);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, name);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, netmask);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, osname);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, ostype);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, processorCount);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, runtime);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, username);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, version);
		TITANIUM_ADD_FUNCTION(PlatformModule, getAddress);
		TITANIUM_ADD_FUNCTION(PlatformModule, getArchitecture);
		TITANIUM_ADD_FUNCTION(PlatformModule, getAvailableMemory);
		TITANIUM_ADD_FUNCTION(PlatformModule, getBatteryLevel);
		TITANIUM_ADD_FUNCTION(PlatformModule, getBatteryMonitoring);
		TITANIUM_ADD_FUNCTION(PlatformModule, setBatteryMonitoring);
		TITANIUM_ADD_FUNCTION(PlatformModule, getBatteryState);
		TITANIUM_ADD_FUNCTION(PlatformModule, getId);
		TITANIUM_ADD_FUNCTION(PlatformModule, getLocale);
		TITANIUM_ADD_FUNCTION(PlatformModule, getMacaddress);
		TITANIUM_ADD_FUNCTION(PlatformModule, getManufacturer);
		TITANIUM_ADD_FUNCTION(PlatformModule, getModel);
		TITANIUM_ADD_FUNCTION(PlatformModule, getName);
		TITANIUM_ADD_FUNCTION(PlatformModule, getNetmask);
		TITANIUM_ADD_FUNCTION(PlatformModule, getOsname);
		TITANIUM_ADD_FUNCTION(PlatformModule, getOstype);
		TITANIUM_ADD_FUNCTION(PlatformModule, getProcessorCount);
		TITANIUM_ADD_FUNCTION(PlatformModule, getRuntime);
		TITANIUM_ADD_FUNCTION(PlatformModule, getUsername);
		TITANIUM_ADD_FUNCTION(PlatformModule, getVersion);
		TITANIUM_ADD_FUNCTION(PlatformModule, createUUID);
		TITANIUM_ADD_FUNCTION(PlatformModule, canOpenURL);
		TITANIUM_ADD_FUNCTION(PlatformModule, openURL);
		TITANIUM_ADD_FUNCTION(PlatformModule, getDisplayCaps);
		TITANIUM_ADD_FUNCTION(PlatformModule, is24HourTimeFormat);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, displayCaps);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, BATTERY_STATE_CHARGING);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, BATTERY_STATE_FULL);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, BATTERY_STATE_UNKNOWN);
		TITANIUM_ADD_PROPERTY_READONLY(PlatformModule, BATTERY_STATE_UNPLUGGED);
	}

}  // namespace Titanium
