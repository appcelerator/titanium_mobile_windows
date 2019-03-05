/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Network.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <boost/format.hpp>
#include <boost/algorithm/string/replace.hpp>

namespace TitaniumWindows
{
	using namespace Windows::Networking::Connectivity;
	using namespace Windows::Web::Http;

	NetworkModule::NetworkModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::NetworkModule(js_context)
	{
		filter__ = ref new Windows::Web::Http::Filters::HttpBaseProtocolFilter();

		change_event__ = NetworkInformation::NetworkStatusChanged += ref new NetworkStatusChangedEventHandler([this](Platform::Object^ sender) {
			updateNetworkStatus();
			if (hasEventListener("change")) {
				TitaniumWindows::Utility::RunOnUIThread([this]() {
					const auto ctx = get_context();
					auto object = ctx.CreateObject();
					object.SetProperty("networkType", js_get_networkType());
					object.SetProperty("networkTypeName", js_get_networkTypeName());
					object.SetProperty("online", js_get_online());
					fireEvent("change", object);
				});
			}
		});
		updateNetworkStatus();
	}

	NetworkModule::~NetworkModule()
	{
		NetworkInformation::NetworkStatusChanged -= change_event__;
	}

	std::shared_ptr<Titanium::Network::Cookie> NetworkModule::createCookie(Windows::Web::Http::HttpCookie^ cookie)
	{
		// Get Cookie constructor
		static auto Cookie_ctor = static_cast<JSObject>(get_object().GetProperty("Cookie"));

		auto cookie_ptr = Cookie_ctor.CallAsConstructor().GetPrivate<Titanium::Network::Cookie>();
		cookie_ptr->set_domain(TitaniumWindows::Utility::ConvertString(cookie->Domain));
		cookie_ptr->set_path(TitaniumWindows::Utility::ConvertString(cookie->Path));
		cookie_ptr->set_name(TitaniumWindows::Utility::ConvertString(cookie->Name));
		cookie_ptr->set_value(TitaniumWindows::Utility::ConvertString(cookie->Value));
		cookie_ptr->set_httponly(cookie->HttpOnly);
		cookie_ptr->set_secure(cookie->Secure);

		if (cookie->Expires != nullptr) {
			// Date format is "yyyy-MM-ddTHH:mm:ss.SSS+0000" to align with Titanium iOS
			const auto formatter = ref new Windows::Globalization::DateTimeFormatting::DateTimeFormatter("{year.full}-{month.integer(2)}-{day.integer(2)}T{hour.integer(2)}:{minute.integer(2)}:{second.integer(2)}.000+0000");
			const auto expires = formatter->Format(cookie->Expires->Value, "UTC"); // HTTP dates are always expressed in UTC
			cookie_ptr->set_expiryDate(TitaniumWindows::Utility::ConvertString(expires));
		}

		return cookie_ptr;
	}

	Windows::Web::Http::HttpCookie^ NetworkModule::createCookie(const std::shared_ptr<Titanium::Network::Cookie>& cookie)
	{
		const auto httpCookie = ref new Windows::Web::Http::HttpCookie(
			TitaniumWindows::Utility::ConvertString(cookie->get_name()),
			TitaniumWindows::Utility::ConvertString(cookie->get_domain()),
			TitaniumWindows::Utility::ConvertString(cookie->get_path()));

		httpCookie->HttpOnly = cookie->get_httponly();
		httpCookie->Secure = cookie->get_secure();
		httpCookie->Value = TitaniumWindows::Utility::ConvertString(cookie->get_value());

		auto expiryDate = cookie->get_expiryDate();
		if (!expiryDate.empty()) {

			// Ti.Network.Cookie.expiryDate has strange format unlike JavaScript Date standard.
			// Such as "yyyy-MM-ddTHH:mm:ss.SSS+0000" which JavaScript can't recognize.
			// The trailing '+0000' should be replaced with 'Z' here.
			expiryDate = boost::algorithm::replace_last_copy(expiryDate, "+0000", "Z");

			const auto ctx = get_context();
			const std::vector<JSValue> args = { ctx.CreateString(expiryDate) };
			const auto expires = TitaniumWindows::Utility::GetDateTime(ctx.CreateDate(args));
			httpCookie->Expires = expires;
		}

		return httpCookie;
	}

	void NetworkModule::addHTTPCookie(std::shared_ptr<Titanium::Network::Cookie> cookie) TITANIUM_NOEXCEPT
	{
		filter__->CookieManager->SetCookie(createCookie(cookie));
	}

	std::vector<std::shared_ptr<Titanium::Network::Cookie>> NetworkModule::getHTTPCookies(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT
	{
		auto cookies = std::vector<std::shared_ptr<Titanium::Network::Cookie>>();

		const auto cookieName = TitaniumWindows::Utility::ConvertString(name);
		const auto uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString((boost::format("https://%1%%2%") % domain % path).str()));
		const auto iterator = filter__->CookieManager->GetCookies(uri)->First();
		while (iterator->HasCurrent) {
			const auto cookie = iterator->Current;
			iterator->MoveNext();
			if (!cookieName->IsEmpty() && !cookieName->Equals(cookie->Name)) {
				continue;
			}
			cookies.push_back(createCookie(cookie));
		}

		return cookies;
	}

	void NetworkModule::removeHTTPCookie(const std::string& domain, const std::string& path, const std::string& name) TITANIUM_NOEXCEPT
	{
		const auto cookieName = TitaniumWindows::Utility::ConvertString(name);
		const auto uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString((boost::format("https://%1%%2%") % domain % path).str()));
		const auto iterator = filter__->CookieManager->GetCookies(uri)->First();
		while (iterator->HasCurrent) {
			const auto cookie = iterator->Current;
			if (cookieName->Equals(cookie->Name)) {
				filter__->CookieManager->DeleteCookie(cookie);
			}
			iterator->MoveNext();
		}

	}

	void NetworkModule::updateNetworkStatus()
	{
		const auto profile = NetworkInformation::GetInternetConnectionProfile();
		if (profile == nullptr) {
			online__ = false;
			networkType__ = Titanium::Network::TYPE::UNKNOWN;
			return;
		}

		// online property
		switch (profile->GetNetworkConnectivityLevel()) {
		case NetworkConnectivityLevel::None:
			online__ = false;
			break;
		case NetworkConnectivityLevel::LocalAccess:
			online__ = false;
			break;
		case NetworkConnectivityLevel::ConstrainedInternetAccess:
			online__ = true;
			break;
		case NetworkConnectivityLevel::InternetAccess:
			online__ = true;
			break;
		}

		// networkType property
		if (profile->IsWlanConnectionProfile) {
			networkType__ = Titanium::Network::TYPE::WIFI;
		} else if (profile->IsWwanConnectionProfile) {
			networkType__ = Titanium::Network::TYPE::MOBILE;
		} else {
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
				networkType__ = Titanium::Network::TYPE::WIFI;
				break;
			default:
				networkType__ = Titanium::Network::TYPE::LAN;
				break;
			}
		}
	}

	void NetworkModule::JSExportInitialize()
	{
		JSExport<NetworkModule>::SetClassVersion(1);
		JSExport<NetworkModule>::SetParent(JSExport<Titanium::NetworkModule>::Class());
	}
}
