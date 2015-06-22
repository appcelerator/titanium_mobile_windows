/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GLOBALSTRING_HPP_
#define _TITANIUM_GLOBALSTRING_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium GlobalString that implements the
	  Titanium API documented at
	  http://docs.appcelerator.com/titanium/latest/#!/api/Global.String
	*/
	class TITANIUMKIT_EXPORT GlobalString : public JSExportObject, public JSExport<GlobalString>
	{
	public:

		virtual std::string formatCurrency(double value) TITANIUM_NOEXCEPT;
		virtual std::string formatDate(JSObject date, std::string format) TITANIUM_NOEXCEPT;
		virtual std::string formatDecimal(double value, std::string locale, std::string pattern) TITANIUM_NOEXCEPT;
		virtual std::string formatTime(JSObject date, std::string format) TITANIUM_NOEXCEPT;

		GlobalString(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postInitialize(JSObject& object) override;

		virtual ~GlobalString() TITANIUM_NOEXCEPT;
		GlobalString(const GlobalString&) = default;
		GlobalString& operator=(const GlobalString&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		GlobalString(GlobalString&&) = default;
		GlobalString& operator=(GlobalString&&) = default;
#endif

		static void JSExportInitialize();

		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;
		
		TITANIUM_FUNCTION_DEF(formatCurrency);
		TITANIUM_FUNCTION_DEF(formatDate);
		TITANIUM_FUNCTION_DEF(formatDecimal);
		TITANIUM_FUNCTION_DEF(formatTime);

	};

}  // namespace Titanium

#endif  // _TITANIUM_GLOBALSTRING_HPP_
