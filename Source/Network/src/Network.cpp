/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Network.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	using namespace Windows::Networking::Connectivity;

	NetworkModule::NetworkModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::NetworkModule(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::NetworkModule::ctor Initialize");
	}

	NetworkModule::~NetworkModule()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::NetworkModule::dtor");
	}

	Titanium::Network::TYPE NetworkModule::get_networkType() const TITANIUM_NOEXCEPT
	{
		const auto profile = NetworkInformation::GetInternetConnectionProfile();

		if (profile == nullptr) {
			return Titanium::Network::TYPE::UNKNOWN;
		}
		if (profile->IsWlanConnectionProfile) {
			return Titanium::Network::TYPE::WIFI;
		}
		if (profile->IsWwanConnectionProfile) {
			return Titanium::Network::TYPE::MOBILE;
		}
		/*
			Value	Meaning
			1		Some other type of network interface.
			6		An Ethernet network interface.
			9		A token ring network interface.
			23		A PPP network interface.
			24		A software loopback network interface.
			37		An ATM network interface.
			71		An IEEE 802.11 wireless network interface.
			131		A tunnel type encapsulation network interface.
			144		An IEEE 1394 (Firewire) high performance serial bus network interface.
		*/
		switch (profile->NetworkAdapter->IanaInterfaceType) {
		case 71:
			return Titanium::Network::TYPE::WIFI;
		default:
			return Titanium::Network::TYPE::LAN;
		}
		return Titanium::Network::TYPE::UNKNOWN;
	}

	bool NetworkModule::get_online() const TITANIUM_NOEXCEPT {
		const auto profile = NetworkInformation::GetInternetConnectionProfile();
		if (profile == nullptr) {
			return false;
		}
		switch (profile->GetNetworkConnectivityLevel()) {
		case NetworkConnectivityLevel::None:
			return false;
		case NetworkConnectivityLevel::LocalAccess:
			return false;
		case NetworkConnectivityLevel::ConstrainedInternetAccess:
			return true;
		case NetworkConnectivityLevel::InternetAccess:
			return true;
		}
		return false;
	}

	void NetworkModule::JSExportInitialize()
	{
		JSExport<NetworkModule>::SetClassVersion(1);
		JSExport<NetworkModule>::SetParent(JSExport<Titanium::NetworkModule>::Class());
	}

	void NetworkModule::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::Module::enableEvent(event_name);
		if (event_name == "change") {
			change_event__ = NetworkInformation::NetworkStatusChanged += ref new NetworkStatusChangedEventHandler([this](Platform::Object^ sender) {
				TitaniumWindows::Utility::RunOnUIThread([this]() {
					const auto ctx = get_context();
					auto object = ctx.CreateObject();
					object.SetProperty("networkType", js_get_networkType());
					object.SetProperty("networkTypeName", js_get_networkTypeName());
					object.SetProperty("online", js_get_online());
					fireEvent("change", object);
				});
			});
		}
	}

	void NetworkModule::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::Module::disableEvent(event_name);
		if (event_name == "change") {
			NetworkInformation::NetworkStatusChanged -= change_event__;
		}
	}
}
