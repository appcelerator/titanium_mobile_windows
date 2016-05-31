/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Platform/DisplayCaps.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	namespace Platform
	{
		DisplayCaps::DisplayCaps(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context, "Ti.Platform.DisplayCaps")
		{
		}
		void DisplayCaps::JSExportInitialize()
		{
			JSExport<DisplayCaps>::SetClassVersion(1);
			JSExport<DisplayCaps>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_PROPERTY_READONLY(DisplayCaps, density);
			TITANIUM_ADD_FUNCTION(DisplayCaps, getDensity);
			TITANIUM_ADD_PROPERTY_READONLY(DisplayCaps, dpi);
			TITANIUM_ADD_FUNCTION(DisplayCaps, getDpi);
			TITANIUM_ADD_PROPERTY_READONLY(DisplayCaps, logicalDensityFactor);
			TITANIUM_ADD_FUNCTION(DisplayCaps, getLogicalDensityFactor);
			TITANIUM_ADD_PROPERTY_READONLY(DisplayCaps, platformHeight);
			TITANIUM_ADD_FUNCTION(DisplayCaps, getPlatformHeight);
			TITANIUM_ADD_PROPERTY_READONLY(DisplayCaps, platformWidth);
			TITANIUM_ADD_FUNCTION(DisplayCaps, getPlatformWidth);
			TITANIUM_ADD_PROPERTY_READONLY(DisplayCaps, xdpi);
			TITANIUM_ADD_FUNCTION(DisplayCaps, getXdpi);
			TITANIUM_ADD_PROPERTY_READONLY(DisplayCaps, ydpi);
			TITANIUM_ADD_FUNCTION(DisplayCaps, getYdpi);
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

		TITANIUM_PROPERTY_GETTER(DisplayCaps, density)
		{
			return get_context().CreateString(density());
		}
		TITANIUM_FUNCTION(DisplayCaps, getDensity)
		{
			return this_object.get_context().CreateString(density());
		}
		TITANIUM_PROPERTY_GETTER(DisplayCaps, dpi)
		{
			return get_context().CreateNumber(dpi());
		}
		TITANIUM_FUNCTION(DisplayCaps, getDpi)
		{
			return this_object.get_context().CreateNumber(dpi());
		}
		TITANIUM_PROPERTY_GETTER(DisplayCaps, logicalDensityFactor)
		{
			return get_context().CreateNumber(logicalDensityFactor());
		}
		TITANIUM_FUNCTION(DisplayCaps, getLogicalDensityFactor)
		{
			return this_object.get_context().CreateNumber(logicalDensityFactor());
		}
		TITANIUM_PROPERTY_GETTER(DisplayCaps, platformHeight)
		{
			return get_context().CreateNumber(platformHeight());
		}
		TITANIUM_FUNCTION(DisplayCaps, getPlatformHeight)
		{
			return this_object.get_context().CreateNumber(platformHeight());
		}
		TITANIUM_PROPERTY_GETTER(DisplayCaps, platformWidth)
		{
			return get_context().CreateNumber(platformWidth());
		}
		TITANIUM_FUNCTION(DisplayCaps, getPlatformWidth)
		{
			return this_object.get_context().CreateNumber(platformWidth());
		}
		TITANIUM_PROPERTY_GETTER(DisplayCaps, xdpi)
		{
			return get_context().CreateNumber(xdpi());
		}
		TITANIUM_FUNCTION(DisplayCaps, getXdpi)
		{
			return this_object.get_context().CreateNumber(xdpi());
		}
		TITANIUM_PROPERTY_GETTER(DisplayCaps, ydpi)
		{
			return get_context().CreateNumber(ydpi());
		}
		TITANIUM_FUNCTION(DisplayCaps, getYdpi)
		{
			return this_object.get_context().CreateNumber(ydpi());
		}
	} // namespace Platform
}  // namespace Titanium
