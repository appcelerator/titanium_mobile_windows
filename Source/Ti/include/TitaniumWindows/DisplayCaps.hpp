/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_DISPLAYCAPS_HPP_
#define _TITANIUMWINDOWS_DISPLAYCAPS_HPP_

#include "Titanium/Platform/DisplayCaps.hpp"
#include "TitaniumWindows_Ti_EXPORT.h"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class DisplayCaps
	  @ingroup Titanium.Platform.DisplayCaps

	  @discussion This is the Titanium.Platform.DisplayCaps implementation for Windows.
	*/
	class TITANIUMWINDOWS_TI_EXPORT DisplayCaps final : public Titanium::Platform::DisplayCaps, public JSExport<DisplayCaps>
	{
	public:
		TITANIUM_PROPERTY_UNIMPLEMENTED(density);

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
		static Windows::Graphics::Display::DisplayInformation^ GetDisplayInformation();
	protected:
	private:
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_DISPLAYCAPS_HPP_
