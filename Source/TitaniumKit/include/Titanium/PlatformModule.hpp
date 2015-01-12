/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_PLATFORMMODULE_HPP_
#define _TITANIUM_PLATFORMMODULE_HPP_

#include "Titanium/Module.hpp"

namespace Titanium {

	namespace Platform {
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
	class TITANIUMKIT_EXPORT PlatformModule : public Module, public JSExport < PlatformModule > {

	public:

		virtual std::string address() const TITANIUM_NOEXCEPT;
		virtual std::string architecture() const TITANIUM_NOEXCEPT;
		virtual unsigned availableMemory() const TITANIUM_NOEXCEPT;
		virtual double batteryLevel() const TITANIUM_NOEXCEPT;
		virtual bool batteryMonitoring() const TITANIUM_NOEXCEPT;
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

		PlatformModule(const JSContext& js_context)											 TITANIUM_NOEXCEPT;
		PlatformModule(const PlatformModule&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

		virtual ~PlatformModule() = default;
		PlatformModule(const PlatformModule&) = default;
		PlatformModule& operator=(const PlatformModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		PlatformModule(PlatformModule&&)								 = default;
		PlatformModule& operator=(PlatformModule&&)			= default;
#endif

		static void JSExportInitialize();
		
		virtual JSValue get_address_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_architecture_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_availableMemory_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_batteryLevel_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_batteryMonitoring_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_batteryState_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_id_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_locale_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_macaddress_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_manufacturer_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_model_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_name_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_netmask_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_osname_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_ostype_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_processorCount_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_runtime_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_username_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_version_ArgumentValidator() const TITANIUM_NOEXCEPT final;

		virtual JSValue getAddressArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getArchitectureArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getAvailableMemoryArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getBatteryLevelArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getBatteryMonitoringArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getBatteryStateArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getIdArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getLocaleArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getMacaddressArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getManufacturerArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getModelArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getNameArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getNetmaskArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getOsnameArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getOstypeArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getProcessorCountArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getRuntimeArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getUsernameArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		virtual JSValue getVersionArgumentValidator(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;

		virtual JSValue createUUIDArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue canOpenURLArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue openURLArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue is24HourTimeFormatArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

		virtual JSValue get_displayCaps_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue getDisplayCapsArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) const TITANIUM_NOEXCEPT final;
		
		virtual JSValue get_BATTERY_STATE_CHARGING() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_BATTERY_STATE_FULL() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_BATTERY_STATE_UNKNOWN() const TITANIUM_NOEXCEPT final;
		virtual JSValue get_BATTERY_STATE_UNPLUGGED() const TITANIUM_NOEXCEPT final;
		
		virtual void setDisplayCaps(const JSValue&) TITANIUM_NOEXCEPT final;
	private:
		JSValue displayCaps__;
		JSValue BATTERY_STATE_CHARGING__;
		JSValue BATTERY_STATE_FULL__;
		JSValue BATTERY_STATE_UNKNOWN__;
		JSValue BATTERY_STATE_UNPLUGGED__;
	};

} // namespace Titanium

#endif // _TITANIUM_PLATFORMMODULE_HPP_
