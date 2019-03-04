/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/DisplayCaps.hpp"
#include "Titanium/detail/TiLogger.hpp"
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

	Windows::Graphics::Display::DisplayInformation^ DisplayCaps::GetDisplayInformation()
	{
		static Windows::Graphics::Display::DisplayInformation^ display;
		static std::once_flag of;
		std::call_once(of, [=] {
			display = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
		});
		return display;
	}

	double DisplayCaps::dpi() const TITANIUM_NOEXCEPT
	{
		static double value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = GetDisplayInformation()->LogicalDpi;
		});
		return value;
	}

	double DisplayCaps::logicalDensityFactor() const TITANIUM_NOEXCEPT
	{
		static double value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = GetDisplayInformation()->RawPixelsPerViewPixel;
		});
		return value;
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
		static double value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = GetDisplayInformation()->RawDpiX;
		});
		return value;
	}

	double DisplayCaps::ydpi() const TITANIUM_NOEXCEPT
	{
		static double value;
		static std::once_flag of;
		std::call_once(of, [=] {
			value = GetDisplayInformation()->RawDpiY;
		});
		return value;
	}
}  // namespace TitaniumWindows
