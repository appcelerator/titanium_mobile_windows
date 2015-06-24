/**
 * Global.String for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_GLOBALSTRING_HPP_
#define _TITANIUMWINDOWS_GLOBALSTRING_HPP_

#include "TitaniumWindows_Global_EXPORT.h"
#include "Titanium/GlobalString.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium Global.String implementation for Windows.
	*/
	class TITANIUMWINDOWS_GLOBAL_EXPORT GlobalString final : public Titanium::GlobalString, public JSExport<GlobalString>
	{
	public:

		virtual std::string formatCurrency(double value) TITANIUM_NOEXCEPT override;
		virtual std::string formatDate(JSObject date, std::string format) TITANIUM_NOEXCEPT override;
		virtual std::string formatDecimal(double value, std::string locale, std::string pattern) TITANIUM_NOEXCEPT override;
		virtual std::string formatTime(JSObject date, std::string format) TITANIUM_NOEXCEPT override;

		GlobalString(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~GlobalString() = default;
		GlobalString(const GlobalString&) = default;
		GlobalString& operator=(const GlobalString&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		GlobalString(GlobalString&&) = default;
		GlobalString& operator=(GlobalString&&) = default;
#endif

		static void JSExportInitialize();

	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_GLOBALSTRING_HPP_
