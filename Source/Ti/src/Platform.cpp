/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Platform.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/DisplayCaps.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <iostream>
#include <objbase.h>
#include <ppltasks.h>
#include <algorithm>
#include <collection.h>
#include <regex>
#include <concrt.h>
#include <boost/algorithm/string.hpp>

namespace TitaniumWindows
{
	Platform::Platform(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::PlatformModule(js_context)
		, osname__(TitaniumWindows::Utility::IsWindowsPhoneOrMobile() ? "windowsphone" : "windowsstore")
	{
		TITANIUM_LOG_DEBUG("Platform::ctor");
		setDisplayCaps(get_context().CreateObject(JSExport<TitaniumWindows::DisplayCaps>::Class()));
	}

	std::string Platform::osname() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Platform::osname");
		return osname__;
	}

	std::string Platform::createUUID() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Platform::createUUID");
		GUID gdn;
		CoCreateGuid(&gdn);
		::Platform::Guid guid(gdn);
		auto guid_str = guid.ToString();
		return std::string((guid_str->Begin()) + 1, (guid_str->End()) - 1);
	}

	std::string Platform::address() const TITANIUM_NOEXCEPT
	{
		using namespace Windows::Networking;
		using namespace Windows::Networking::Connectivity;
		const auto hosts = NetworkInformation::GetHostNames();
		// Check if it's ipaddress because Windows returns muliple result which contains both host name and ip address
		const std::regex pattern("(\\d{1,3}(\\.\\d{1,3}){3})");
		std::string result;
		std::for_each(begin(hosts), end(hosts), [&result, &pattern](HostName^ host) {
			// Let's take the first one and ignore others
			if (!result.empty()) {
				return;
			}
			// Enforce Wifi? This definitely doesn't work for Simulator properly. We also may not want to enforce wifi for desktop...
			//if (host->IPInformation && host->IPInformation->NetworkAdapter->IanaInterfaceType == 71) {
				const auto hostname = TitaniumWindows::Utility::ConvertString(host->CanonicalName);
				std::smatch match;
				if (std::regex_search(hostname, match, pattern)) {
					result = hostname;
				}
			//}
		});
		return result;
	}

	std::string Platform::architecture() const TITANIUM_NOEXCEPT
	{
		_SYSTEM_INFO sysInfo;
		GetNativeSystemInfo(&sysInfo);
		unsigned value = sysInfo.wProcessorArchitecture;
		if (value == 9) {
			return "x64";
		}
		if (value == 6) {
			return "ia64";
		}
		if (value == 5) {
			return "ARM";
		}
		if (value == 0) {
			return "x86";
		}
		return "unknown";
	}

	std::uint64_t Platform::availableMemory() const TITANIUM_NOEXCEPT
	{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
		return Windows::System::MemoryManager::AppMemoryUsageLimit - Windows::System::MemoryManager::AppMemoryUsage;
#else
		return 0;
#endif
	}

	double Platform::batteryLevel() const TITANIUM_NOEXCEPT
	{
#if defined(IS_WINDOWS_PHONE)
		return Windows::Phone::Devices::Power::Battery::GetDefault()->RemainingChargePercent;
#endif
		return 0;
	}

	bool Platform::batteryMonitoring() const TITANIUM_NOEXCEPT
	{
#if defined(IS_WINDOWS_PHONE)
		return true;
#else
		return false;
#endif
	}

	Titanium::Platform::BatteryState Platform::batteryState() const TITANIUM_NOEXCEPT
	{
#if defined(IS_WINDOWS_PHONE)
		// We can detect if it's fully charged, but we don't know if it's plugged or not.
		// In this case let's return FULL if 100% charged, otherwise return UNKNOWN.
		const auto percent = Windows::Phone::Devices::Power::Battery::GetDefault()->RemainingChargePercent;
		if (percent == 100) {
			return Titanium::Platform::BatteryState::FULL;
		} else {
			return Titanium::Platform::BatteryState::UNKNOWN;
		}
#else
		return Titanium::Platform::BatteryState::UNKNOWN;
#endif
	}

	std::string Platform::id() const TITANIUM_NOEXCEPT
	{
		return TitaniumWindows::Utility::ConvertString(Windows::System::UserProfile::AdvertisingManager::AdvertisingId);
	}

	std::string Platform::locale() const TITANIUM_NOEXCEPT
	{
		return std::locale("").name();
	}

	std::string Platform::macaddress() const TITANIUM_NOEXCEPT
	{
		return "";
	}

	std::string Platform::manufacturer() const TITANIUM_NOEXCEPT
	{
		const auto deviceInfo = ref new Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();
		return TitaniumWindows::Utility::ConvertString(deviceInfo->SystemManufacturer);
	}

	std::string Platform::model() const TITANIUM_NOEXCEPT
	{
		const auto deviceInfo = ref new Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();
		if (deviceInfo->SystemSku->IsEmpty()) {
			return TitaniumWindows::Utility::ConvertString(deviceInfo->SystemProductName);
		} else {
			return TitaniumWindows::Utility::ConvertString(deviceInfo->SystemSku);
		}
	}

	std::string Platform::name() const TITANIUM_NOEXCEPT
	{
		return "windows";
	}

	std::string Platform::netmask() const TITANIUM_NOEXCEPT
	{
		using namespace Windows::Networking;
		using namespace Windows::Networking::Connectivity;
		const auto hosts = NetworkInformation::GetHostNames();
		std::string result = "";
		std::for_each(begin(hosts), end(hosts), [&result](HostName^ host) {
			if (host->IPInformation) {
				// FIXME How can we ensure this is the Wifi connection?
				auto prefix = host->IPInformation->PrefixLength;
				if (prefix) {
					auto value = prefix->Value;
					// Convert to subnet mask! Any way to do this more conveniently? a giant switch is just plain bad.
					// http://www.gadgetwiz.com/network/netmask.html
					switch (value) {
					case 0:
						result = "0.0.0.0";
						break;
					case 1:
						result = "128.0.0.0";
						break;
					case 2:
						result = "192.0.0.0";
						break;
					case 3:
						result = "224.0.0.0";
						break;
					case 4:
						result = "240.0.0.0";
						break;
					case 5:
						result = "248.0.0.0";
						break;
					case 6:
						result = "252.0.0.0";
						break;
					case 7:
						result = "254.0.0.0";
						break;
					case 8:
						result = "255.0.0.0";
						break;
					case 9:
						result = "255.128.0.0";
						break;
					case 10:
						result = "255.192.0.0";
						break;
					case 11:
						result = "255.224.0.0";
						break;
					case 12:
						result = "255.240.0.0";
						break;
					case 13:
						result = "255.248.0.0";
						break;
					case 14:
						result = "255.252.0.0";
						break;
					case 15:
						result = "255.254.0.0";
						break;
					case 16:
						result = "255.255.0.0";
						break;
					case 17:
						result = "255.255.128.0";
						break;
					case 18:
						result = "255.255.192.0";
						break;
					case 19:
						result = "255.255.224.0";
						break;
					case 20:
						result = "255.255.240.0";
						break;
					case 21:
						result = "255.255.248.0";
						break;
					case 22:
						result = "255.255.252.0";
						break;
					case 23:
						result = "255.255.254.0";
						break;
					case 24:
						result = "255.255.255.0";
						break;
					case 25:
						result = "255.255.255.128";
						break;
					case 26:
						result = "255.255.255.192";
						break;
					case 27:
						result = "255.255.255.224";
						break;
					case 28:
						result = "255.255.255.240";
						break;
					case 29:
						result = "255.255.255.248";
						break;
					case 30:
						result = "255.255.255.252";
						break;
					case 31:
						result = "255.255.255.254";
						break;
					case 32:
						result = "255.255.255.255";
						break;
					default:
						break;
					}
				}
			}
		});
		return result;
	}

	std::string Platform::ostype() const TITANIUM_NOEXCEPT
	{
		_SYSTEM_INFO sysInfo;
		GetNativeSystemInfo(&sysInfo);
		unsigned value = sysInfo.wProcessorArchitecture;
		if (value == 9 || value == 6) { // 9 = x64, 6 = ia64
			return "64bit";
		}
		if (value == 5 || value == 0) { // 5 = ARM, 0 = x86
			return "32bit";
		}
		return "unknown";
	}

	unsigned Platform::processorCount() const TITANIUM_NOEXCEPT
	{
		_SYSTEM_INFO sysInfo;
		GetNativeSystemInfo(&sysInfo);
		return sysInfo.dwNumberOfProcessors;
	}

	std::string Platform::runtime() const TITANIUM_NOEXCEPT
	{
		return "javascriptcore";
	}

	std::string Platform::username() const TITANIUM_NOEXCEPT
	{
		const auto info = ref new Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();
		const auto name = info->FriendlyName;
		return TitaniumWindows::Utility::ConvertString(name);
	}
	std::string Platform::version() const TITANIUM_NOEXCEPT
	{
		using namespace Windows::Devices::Enumeration::Pnp;
		auto requestedProperties = ref new ::Platform::Collections::Vector<::Platform::String^>();
		requestedProperties->Append("{A8B865DD-2E3D-4094-AD97-E593A70C75D6},3"); // version
		requestedProperties->Append("{A45C254E-DF1C-4EFD-8020-67D146A850E0},10"); // device

		std::string os_version = "6.3.9600"; // Win 8.1 base value
		concurrency::event event;
		concurrency::create_task(PnpObject::FindAllAsync(PnpObjectType::Device, requestedProperties)).then([&event, &os_version](concurrency::task<PnpObjectCollection^> t) {
			try {
				auto found = false;
				auto collection = t.get();
				for (auto object : collection) {
					auto deviceClass = object->Properties->Lookup("{A45C254E-DF1C-4EFD-8020-67D146A850E0},10")->ToString();
					if (deviceClass == "{4d36e966-e325-11ce-bfc1-08002be10318}") {
						auto version = object->Properties->Lookup("{A8B865DD-2E3D-4094-AD97-E593A70C75D6},3")->ToString();
						os_version = Utility::ConvertUTF8String(version);
						found = true;
						break;
					}
					if (found) break;
				}
			}
			catch (::Platform::Exception^ ce) {
			}
			catch (...) {}
			event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();
		return os_version;
	}

	bool Platform::canOpenURL(const std::string& url) TITANIUM_NOEXCEPT
	{
		// On Windows, just check if it's a well-formed uri or not, because
		// the operating system provides the user with a link to search for app from the store on launch.
		const auto uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString(url));
		return !uri->Suspicious;
	}

	bool Platform::openURL(const std::string& url) TITANIUM_NOEXCEPT
	{
		const auto uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString(url));

		// If this url can be considered as application URI
		if (boost::starts_with(url, "ms-")) {
			using namespace Windows::Storage;
			concurrency::task<StorageFile^>(StorageFile::GetFileFromApplicationUriAsync(uri)).then([](concurrency::task<StorageFile^> task) {
				try {
					Windows::System::Launcher::LaunchFileAsync(task.get());
				} catch (...) { }
			});
		} else {
			Windows::System::Launcher::LaunchUriAsync(uri);
		}
		// It turns out that use of arbitrary thread (task_continuation_context::use_arbitrary) makes launcher unstable.
		// We just launch uri in async and always return true.
		return true;
	}

	bool Platform::is24HourTimeFormat() TITANIUM_NOEXCEPT
	{
		return false;
	}

	void Platform::JSExportInitialize()
	{
		JSExport<Platform>::SetClassVersion(1);
		JSExport<Platform>::SetParent(JSExport<Titanium::PlatformModule>::Class());
	}

}  // namespace TitaniumWindows
