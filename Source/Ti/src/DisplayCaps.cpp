/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/DisplayCaps.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <iostream>
#include <objbase.h>

namespace TitaniumWindows
{
	DisplayCaps::DisplayCaps(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::Platform::DisplayCaps(js_context)
	{
		TITANIUM_LOG_DEBUG("DisplayCaps::ctor");
	}

	void DisplayCaps::JSExportInitialize()
	{
		JSExport<DisplayCaps>::SetClassVersion(1);
		JSExport<DisplayCaps>::SetParent(JSExport<Titanium::Platform::DisplayCaps>::Class());
	}

	double DisplayCaps::dpi() const TITANIUM_NOEXCEPT
	{
		auto display = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
		if (display) {
			return display->LogicalDpi;
		}
		return Titanium::Platform::DisplayCaps::dpi();
	}

	double DisplayCaps::logicalDensityFactor() const TITANIUM_NOEXCEPT
	{
		auto display = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
		if (display) {
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			return display->RawPixelsPerViewPixel;
#else
			return static_cast<int>(display->ResolutionScale) / 100.0;
#endif
		}
		return Titanium::Platform::DisplayCaps::logicalDensityFactor();
	}

	double DisplayCaps::platformHeight() const TITANIUM_NOEXCEPT
	{
		auto current = Windows::UI::Xaml::Window::Current;
		if (current) {
			return current->Bounds.Height;
		}
		return Titanium::Platform::DisplayCaps::platformHeight();
	}

	double DisplayCaps::platformWidth() const TITANIUM_NOEXCEPT
	{
		auto current = Windows::UI::Xaml::Window::Current;
		if (current) {
			return current->Bounds.Width;
		}
		return Titanium::Platform::DisplayCaps::platformWidth();
	}

	double DisplayCaps::xdpi() const TITANIUM_NOEXCEPT
	{
		auto display = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
		if (display) {
			return display->RawDpiX;
		}
		return Titanium::Platform::DisplayCaps::xdpi();
	}

	double DisplayCaps::ydpi() const TITANIUM_NOEXCEPT
	{
		auto display = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
		if (display) {
			return display->RawDpiY;
		}
		return Titanium::Platform::DisplayCaps::ydpi();
	}
}  // namespace TitaniumWindows
