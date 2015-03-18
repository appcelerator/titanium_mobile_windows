/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_PLATFORMMODULE_HPP_
#define _TITANIUM_PLATFORMMODULE_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace Platform
	{
		enum BatteryState {
			UNKNOWN = 0,
			UNPLUGGED,
			CHARGING,
			FULL
		};
	}

	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Titanium Platform Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Platform
	*/
	class TITANIUMKIT_EXPORT PlatformModule : public Module, public JSExport<PlatformModule>
	{
	public:
		virtual std::string address() const TITANIUM_NOEXCEPT;
		virtual std::string architecture() const TITANIUM_NOEXCEPT;
		virtual unsigned availableMemory() const TITANIUM_NOEXCEPT;
		virtual double batteryLevel() const TITANIUM_NOEXCEPT;
		virtual bool batteryMonitoring() const TITANIUM_NOEXCEPT;
		virtual void set_batteryMonitoring(const bool& batteryMonitoring) TITANIUM_NOEXCEPT;
		virtual Platform::BatteryState batteryState() const TITANIUM_NOEXCEPT;
		virtual std::string id() const TITANIUM_NOEXCEPT;
		virtual std::string locale() const TITANIUM_NOEXCEPT;
		virtual std::string macaddress() const TITANIUM_NOEXCEPT;
		virtual std::string manufacturer() const TITANIUM_NOEXCEPT;
		virtual std::string model() const TITANIUM_NOEXCEPT;
		virtual std::string name() const TITANIUM_NOEXCEPT;
		virtual std::string netmask() const TITANIUM_NOEXCEPT;
		virtual std::string osname() const TITANIUM_NOEXCEPT;
		virtual std::string ostype() const TITANIUM_NOEXCEPT;
		virtual unsigned processorCount() const TITANIUM_NOEXCEPT;
		virtual std::string runtime() const TITANIUM_NOEXCEPT;
		virtual std::string username() const TITANIUM_NOEXCEPT;
		virtual std::string version() const TITANIUM_NOEXCEPT;
		virtual std::string createUUID() TITANIUM_NOEXCEPT;
		virtual bool canOpenURL(const std::string& url) TITANIUM_NOEXCEPT;
		virtual bool openURL(const std::string& url) TITANIUM_NOEXCEPT;
		virtual bool is24HourTimeFormat() TITANIUM_NOEXCEPT;

		PlatformModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~PlatformModule() = default;
		PlatformModule(const PlatformModule&) = default;
		PlatformModule& operator=(const PlatformModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		PlatformModule(PlatformModule&&) = default;
		PlatformModule& operator=(PlatformModule&&) = default;
#endif

		static void JSExportInitialize();

		virtual JSValue js_get_address() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_architecture() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_availableMemory() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_batteryLevel() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_batteryMonitoring() const TITANIUM_NOEXCEPT final;
		virtual bool js_set_batteryMonitoring(const JSValue& argument) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_batteryState() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_id() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_locale() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_macaddress() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_manufacturer() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_model() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_name() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_netmask() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_osname() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_ostype() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_processorCount() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_runtime() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_username() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_version() const TITANIUM_NOEXCEPT final;

		virtual JSValue js_getAddress(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getArchitecture(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getAvailableMemory(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getBatteryLevel(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getBatteryMonitoring(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_setBatteryMonitoring(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getBatteryState(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getId(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getLocale(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getMacaddress(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getManufacturer(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getModel(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getName(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getNetmask(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getOsname(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getOstype(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getProcessorCount(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getRuntime(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getUsername(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getVersion(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;

		virtual JSValue js_createUUID(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_canOpenURL(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_openURL(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_is24HourTimeFormat(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

		virtual JSValue js_get_displayCaps() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getDisplayCaps(const std::vector<JSValue>& arguments, JSObject& this_object) const TITANIUM_NOEXCEPT final;

		virtual JSValue js_get_BATTERY_STATE_CHARGING() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_BATTERY_STATE_FULL() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_BATTERY_STATE_UNKNOWN() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_BATTERY_STATE_UNPLUGGED() const TITANIUM_NOEXCEPT final;

		virtual void setDisplayCaps(const JSValue&) TITANIUM_NOEXCEPT final;
		JSObject GetPlatformObject(const JSContext& js_context) const TITANIUM_NOEXCEPT;

	private:
		JSValue displayCaps__;
		JSValue BATTERY_STATE_CHARGING__;
		JSValue BATTERY_STATE_FULL__;
		JSValue BATTERY_STATE_UNKNOWN__;
		JSValue BATTERY_STATE_UNPLUGGED__;
	};

}  // namespace Titanium

#endif  // _TITANIUM_PLATFORMMODULE_HPP_
