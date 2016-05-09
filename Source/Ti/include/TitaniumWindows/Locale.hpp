/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_LOCALE_HPP_
#define _TITANIUMWINDOWS_LOCALE_HPP_

#include "Titanium/Locale.hpp"
#include "TitaniumWindows_Ti_EXPORT.h"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class Locale
	  @ingroup Titanium.Locale

	  @discussion This is the Titanium.Locale module implementation for Windows.
	*/
	class TITANIUMWINDOWS_TI_EXPORT Locale final : public Titanium::Locale, public JSExport<Locale>
	{
	public:
		TITANIUM_FUNCTION_UNIMPLEMENTED(formatTelephoneNumber);

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
		  @abstract getString
		  @discussion Returns a string, localized according to the current system locale
		*/
		virtual std::string getString(const std::string& key, const std::string& hint) TITANIUM_NOEXCEPT override;

		/*!
		  @method
		  @abstract setLanguage
		  @discussion Set the current language for the app.
		*/
		virtual void setLanguage(const std::string& language) TITANIUM_NOEXCEPT override;

		Locale(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~Locale();
		Locale(const Locale&) = default;
		Locale& operator=(const Locale&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Locale(Locale&&) = default;
		Locale& operator=(Locale&&) = default;
#endif

		static void JSExportInitialize();

	private:
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_LOCALE_HPP_
