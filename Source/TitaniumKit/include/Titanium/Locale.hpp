/**
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_LOCALE_HPP_
#define _TITANIUM_LOCALE_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Ti.Locale Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Ti.Locale
	*/
	class TITANIUMKIT_EXPORT Locale : public Module, public JSExport<Locale>
	{
	public:

		/*!
		  @property
		  @abstract currentCountry
		  @discussion Country of the current system locale, as an ISO 2-letter code.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, currentCountry);

		/*!
		  @property
		  @abstract currentLanguage
		  @discussion Language of the current system locale, as an ISO 2-letter code.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, currentLanguage);

		/*!
		  @property
		  @abstract currentLocale
		  @discussion Current system locale, as a combination of ISO 2-letter language and country codes.
		*/
		TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::string, currentLocale);

		/*!
		  @method
		  @abstract formatTelephoneNumber
		  @discussion Formats a telephone number according to the current system locale.
		*/
		virtual std::string formatTelephoneNumber(const std::string& number) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getCurrencyCode
		  @discussion Returns the ISO 3-letter currency code for the specified locale.
		*/
		virtual std::string getCurrencyCode(const std::string& locale) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getCurrencySymbol
		  @discussion Returns the currency symbol for the specified currency code.
		*/
		virtual std::string getCurrencySymbol(const std::string& currencyCode) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getLocaleCurrencySymbol
		  @discussion Returns the currency symbol for the specified locale.
		*/
		virtual std::string getLocaleCurrencySymbol(const std::string& locale) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract getString
		  @discussion Returns a string, localized according to the current system locale
		*/
		virtual std::string getString(const std::string& key, const std::string& hint) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract setLanguage
		  @discussion Set the current language.
		*/
		virtual void setLanguage(const std::string& language) TITANIUM_NOEXCEPT;

		Locale(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~Locale() = default;
		Locale(const Locale&) = default;
		Locale& operator=(const Locale&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Locale(Locale&&) = default;
		Locale& operator=(Locale&&) = default;
#endif

		static void JSExportInitialize();
		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

		TITANIUM_PROPERTY_READONLY_DEF(currentCountry);
		TITANIUM_PROPERTY_READONLY_DEF(currentLanguage);
		TITANIUM_PROPERTY_READONLY_DEF(currentLocale);

		TITANIUM_FUNCTION_DEF(formatTelephoneNumber);
		TITANIUM_FUNCTION_DEF(getCurrencyCode);
		TITANIUM_FUNCTION_DEF(getCurrencySymbol);
		TITANIUM_FUNCTION_DEF(getLocaleCurrencySymbol);
		TITANIUM_FUNCTION_DEF(getCurrentCountry);
		TITANIUM_FUNCTION_DEF(getCurrentLanguage);
		TITANIUM_FUNCTION_DEF(getCurrentLocale);
		TITANIUM_FUNCTION_DEF(getString);
		TITANIUM_FUNCTION_DEF(setLanguage);

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		std::string currentCountry__;
		std::string currentLanguage__;
		std::string currentLocale__;
#pragma warning(pop)
	};

}  // namespace Titanium

#endif  // _TITANIUM_LOCALE_HPP_
