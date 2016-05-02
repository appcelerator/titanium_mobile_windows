/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Locale.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <collection.h>
#include <algorithm>

using namespace Windows::System::UserProfile;
using namespace Windows::Globalization;

namespace TitaniumWindows
{
	Locale::Locale(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::Locale(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Locale::ctor");

		const auto region = ref new GeographicRegion(GlobalizationPreferences::HomeGeographicRegion);

		currentCountry__ = TitaniumWindows::Utility::ConvertString(region->CodeTwoLetter);
		const auto languages = GlobalizationPreferences::Languages;
		if (languages->Size > 0) {
			currentLocale__ = TitaniumWindows::Utility::ConvertString(languages->GetAt(0));
		} // else default is "en-US"

		const auto pos = currentLocale__.find("-");
		if (pos != std::string::npos) {
			currentLanguage__ = currentLocale__.substr(0, pos);
		} else {
			currentLanguage__ = currentLocale__;
			currentLocale__   = currentLanguage__ + "-" + currentCountry__;
		}
	}

	Locale::~Locale()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Locale::dtor");
	}

	std::string Locale::getCurrencyCode(const std::string& locale) TITANIUM_NOEXCEPT
	{
		std::string country;
		const auto pos = locale.find("-");
		if (pos != std::string::npos) {
			country = locale.substr(pos+1);
		} else {
			//
			// Some locales don't have "-". (tr, hu etc)
			// See also: https://msdn.microsoft.com/en-us/library/ms533052%28v=vs.85%29.aspx
			//
			country = locale;
			std::transform(country.cbegin(), country.cend(), country.begin(), toupper);;
		}

		const auto region = ref new GeographicRegion(TitaniumWindows::Utility::ConvertString(country));
		const auto currencies = region->CurrenciesInUse;

		if (currencies->Size > 0) {
			return TitaniumWindows::Utility::ConvertString(region->CurrenciesInUse->GetAt(0));
		} else {
			HAL::detail::ThrowRuntimeError("Locale::getCurrencyCode", "Currency code does not found for " + locale);
		}
		return "";
	}

	std::string Locale::getCurrencySymbol(const std::string& currencyCode) TITANIUM_NOEXCEPT
	{
		const auto formatter = ref new NumberFormatting::CurrencyFormatter(TitaniumWindows::Utility::ConvertString(currencyCode));
		const auto format = TitaniumWindows::Utility::ConvertUTF8String(formatter->Format(0.0));

		//
		// Assuming currency symbol appears first ("$0.0", "¥0", "NT$0.0" etc...) 
		// 
		const auto pos = format.find("0");
		if (pos != std::string::npos) {
			return format.substr(0, pos);
		}

		return "";
	}

	std::string Locale::getString(const std::string& key, const std::string& hint) TITANIUM_NOEXCEPT
	{
		try {
			const auto loader = Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
			const auto value = loader->GetString(TitaniumWindows::Utility::ConvertUTF8String(key));
			if (value) {
				return TitaniumWindows::Utility::ConvertUTF8String(value);
			}
		} catch (...) {
			TITANIUM_LOG_ERROR("Error during Locale::getString");
		}
		return hint.empty() ? key : hint;
	}

	void Locale::JSExportInitialize()
	{
		JSExport<Locale>::SetClassVersion(1);
		JSExport<Locale>::SetParent(JSExport<Titanium::Locale>::Class());
	}

}  // namespace TitaniumWindows
