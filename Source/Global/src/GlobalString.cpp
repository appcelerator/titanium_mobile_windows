/**
 * Global.String for Windows
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/GlobalString.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{

	GlobalString::GlobalString(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::GlobalString(js_context)
	{
		TITANIUM_LOG_DEBUG("GlobalString::ctor");
	}

	void GlobalString::JSExportInitialize()
	{
		JSExport<GlobalString>::SetClassVersion(1);
		JSExport<GlobalString>::SetParent(JSExport<Titanium::GlobalString>::Class());
	}

	std::string GlobalString::formatCurrency(double value) TITANIUM_NOEXCEPT
	{
		const auto userCurrency = Windows::System::UserProfile::GlobalizationPreferences::Currencies->First()->Current;
		const auto formatter = ref new Windows::Globalization::NumberFormatting::CurrencyFormatter(userCurrency);

		return TitaniumWindows::Utility::ConvertString(formatter->Format(value));
	}

	std::string GlobalString::formatDate(JSObject dateObject, std::string format) TITANIUM_NOEXCEPT
	{
		using namespace Windows::Globalization::DateTimeFormatting;
		DateTimeFormatter^ formatter;
		if (format == "short") {
			formatter = ref new DateTimeFormatter("shortdate");
		} else {
			formatter = ref new DateTimeFormatter("longdate");
		}
		const auto date = TitaniumWindows::Utility::GetDateTime(dateObject);
		return TitaniumWindows::Utility::ConvertString(formatter->Format(date));
	}

	std::string GlobalString::formatDecimal(double value, std::string locale, std::string pattern) TITANIUM_NOEXCEPT
	{
		// TODO: support locale and pattern
		const auto formatter = ref new Windows::Globalization::NumberFormatting::DecimalFormatter();
		return TitaniumWindows::Utility::ConvertString(formatter->FormatDouble(value));
	}

	std::string GlobalString::formatTime(JSObject dateObject, std::string format) TITANIUM_NOEXCEPT
	{
		using namespace Windows::Globalization::DateTimeFormatting;
		DateTimeFormatter^ formatter;
		if (format == "short") {
			formatter = ref new DateTimeFormatter("shorttime");
		} else {
			formatter = ref new DateTimeFormatter("longtime");
		}
		const auto date = TitaniumWindows::Utility::GetDateTime(dateObject);
		return TitaniumWindows::Utility::ConvertString(formatter->Format(date));
	}

}  // namespace TitaniumWindows
