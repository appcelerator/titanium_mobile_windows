/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_PLATFORM_DISPLAYCAPS_HPP_
#define _TITANIUM_PLATFORM_DISPLAYCAPS_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace Platform
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Ti.Platform.DisplayCaps Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Ti.Platform.DisplayCaps
		*/
		class TITANIUMKIT_EXPORT DisplayCaps : public Module, public JSExport<DisplayCaps>
		{
		public:
			virtual std::string density() const TITANIUM_NOEXCEPT;
			virtual double dpi() const TITANIUM_NOEXCEPT;
			virtual double logicalDensityFactor() const TITANIUM_NOEXCEPT;
			virtual double platformHeight() const TITANIUM_NOEXCEPT;
			virtual double platformWidth() const TITANIUM_NOEXCEPT;
			virtual double xdpi() const TITANIUM_NOEXCEPT;
			virtual double ydpi() const TITANIUM_NOEXCEPT;

			DisplayCaps(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~DisplayCaps() = default;
			DisplayCaps(const DisplayCaps&) = default;
			DisplayCaps& operator=(const DisplayCaps&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			DisplayCaps(DisplayCaps&&) = default;
			DisplayCaps& operator=(DisplayCaps&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(density);
			TITANIUM_FUNCTION_DEF(getDensity);
			TITANIUM_PROPERTY_READONLY_DEF(dpi);
			TITANIUM_FUNCTION_DEF(getDpi);
			TITANIUM_PROPERTY_READONLY_DEF(logicalDensityFactor);
			TITANIUM_FUNCTION_DEF(getLogicalDensityFactor);
			TITANIUM_PROPERTY_READONLY_DEF(platformHeight);
			TITANIUM_FUNCTION_DEF(getPlatformHeight);
			TITANIUM_PROPERTY_READONLY_DEF(platformWidth);
			TITANIUM_FUNCTION_DEF(getPlatformWidth);
			TITANIUM_PROPERTY_READONLY_DEF(xdpi);
			TITANIUM_FUNCTION_DEF(getXdpi);
			TITANIUM_PROPERTY_READONLY_DEF(ydpi);
			TITANIUM_FUNCTION_DEF(getYdpi);
		};
	} // namespace Platform
}  // namespace Titanium
#endif  // _TITANIUM_PLATFORM_DISPLAYCAPS_HPP_
