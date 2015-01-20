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

			DisplayCaps(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

			virtual ~DisplayCaps() = default;
			DisplayCaps(const DisplayCaps&) = default;
			DisplayCaps& operator=(const DisplayCaps&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			DisplayCaps(DisplayCaps&&) = default;
			DisplayCaps& operator=(DisplayCaps&&) = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_density() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getDensity(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_dpi() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getDpi(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_logicalDensityFactor() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getLogicalDensityFactor(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_platformHeight() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getPlatformHeight(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_platformWidth() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getPlatformWidth(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_xdpi() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getXdpi(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_ydpi() const TITANIUM_NOEXCEPT final;
			virtual JSValue js_getYdpi(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT final;
		};
	} // namespace Platform
}  // namespace Titanium
#endif  // _TITANIUM_PLATFORM_DISPLAYCAPS_HPP_
