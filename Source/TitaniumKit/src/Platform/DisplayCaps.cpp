/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Platform/DisplayCaps.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	namespace Platform
	{
		DisplayCaps::DisplayCaps(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Module(js_context, arguments)
		{
		}

		void DisplayCaps::JSExportInitialize()
		{
			JSExport<DisplayCaps>::SetClassVersion(1);
			JSExport<DisplayCaps>::SetParent(JSExport<Module>::Class());
			JSExport<DisplayCaps>::AddValueProperty("density", std::mem_fn(&DisplayCaps::js_get_density));
			JSExport<DisplayCaps>::AddFunctionProperty("getDensity", std::mem_fn(&DisplayCaps::js_getDensity));
			JSExport<DisplayCaps>::AddValueProperty("dpi", std::mem_fn(&DisplayCaps::js_get_dpi));
			JSExport<DisplayCaps>::AddFunctionProperty("getDpi", std::mem_fn(&DisplayCaps::js_getDpi));
			JSExport<DisplayCaps>::AddValueProperty("logicalDensityFactor", std::mem_fn(&DisplayCaps::js_get_logicalDensityFactor));
			JSExport<DisplayCaps>::AddFunctionProperty("getLogicalDensityFactor", std::mem_fn(&DisplayCaps::js_getLogicalDensityFactor));
			JSExport<DisplayCaps>::AddValueProperty("platformHeight", std::mem_fn(&DisplayCaps::js_get_platformHeight));
			JSExport<DisplayCaps>::AddFunctionProperty("getPlatformHeight", std::mem_fn(&DisplayCaps::js_getPlatformHeight));
			JSExport<DisplayCaps>::AddValueProperty("platformWidth", std::mem_fn(&DisplayCaps::js_get_platformWidth));
			JSExport<DisplayCaps>::AddFunctionProperty("getPlatformWidth", std::mem_fn(&DisplayCaps::js_getPlatformWidth));
			JSExport<DisplayCaps>::AddValueProperty("xdpi", std::mem_fn(&DisplayCaps::js_get_xdpi));
			JSExport<DisplayCaps>::AddFunctionProperty("getXdpi", std::mem_fn(&DisplayCaps::js_getXdpi));
			JSExport<DisplayCaps>::AddValueProperty("ydpi", std::mem_fn(&DisplayCaps::js_get_ydpi));
			JSExport<DisplayCaps>::AddFunctionProperty("getYdpi", std::mem_fn(&DisplayCaps::js_getYdpi));
		}

		std::string DisplayCaps::density() const TITANIUM_NOEXCEPT
		{
			return "";
		}
		double DisplayCaps::dpi() const TITANIUM_NOEXCEPT
		{
			return 0;
		}
		double DisplayCaps::logicalDensityFactor() const TITANIUM_NOEXCEPT
		{
			return 0;
		}
		double DisplayCaps::platformHeight() const TITANIUM_NOEXCEPT
		{
			return 0;
		}
		double DisplayCaps::platformWidth() const TITANIUM_NOEXCEPT
		{
			return 0;
		}
		double DisplayCaps::xdpi() const TITANIUM_NOEXCEPT
		{
			return 0;
		}
		double DisplayCaps::ydpi() const TITANIUM_NOEXCEPT
		{
			return 0;
		}

		JSValue DisplayCaps::js_get_density() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(density());
		}
		JSValue DisplayCaps::js_getDensity(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
		{
			return js_get_density();
		}
		JSValue DisplayCaps::js_get_dpi() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(dpi());
		}
		JSValue DisplayCaps::js_getDpi(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
		{
			return js_get_dpi();
		}
		JSValue DisplayCaps::js_get_logicalDensityFactor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(logicalDensityFactor());
		}
		JSValue DisplayCaps::js_getLogicalDensityFactor(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
		{
			return js_get_logicalDensityFactor();
		}
		JSValue DisplayCaps::js_get_platformHeight() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(platformHeight());
		}
		JSValue DisplayCaps::js_getPlatformHeight(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
		{
			return js_get_platformHeight();
		}
		JSValue DisplayCaps::js_get_platformWidth() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(platformWidth());
		}
		JSValue DisplayCaps::js_getPlatformWidth(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
		{
			return js_get_platformWidth();
		}
		JSValue DisplayCaps::js_get_xdpi() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(xdpi());
		}
		JSValue DisplayCaps::js_getXdpi(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
		{
			return js_get_xdpi();
		}
		JSValue DisplayCaps::js_get_ydpi() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(ydpi());
		}
		JSValue DisplayCaps::js_getYdpi(const std::vector<JSValue>&, JSObject&) const TITANIUM_NOEXCEPT
		{
			return js_get_ydpi();
		}
	} // namespace Platform
}  // namespace Titanium
