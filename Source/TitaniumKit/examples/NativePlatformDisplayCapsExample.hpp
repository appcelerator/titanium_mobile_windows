/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEPLATFORMDISPLAYCAPSEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEPLATFORMDISPLAYCAPSEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"
#include "Titanium/Platform/DisplayCaps.hpp"

using namespace HAL;

/*!
 @class
 @discussion This is an example of how to implement Titanium::Platform::DisplayCaps
 for a native platform.
 */
class NativePlatformDisplayCapsExample final : public Titanium::Platform::DisplayCaps, public JSExport<NativePlatformDisplayCapsExample>
{
   public:
	NativePlatformDisplayCapsExample(const JSContext& js_context) TITANIUM_NOEXCEPT;
	NativePlatformDisplayCapsExample(const NativePlatformDisplayCapsExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

	virtual ~NativePlatformDisplayCapsExample() = default;
	NativePlatformDisplayCapsExample(const NativePlatformDisplayCapsExample&) = default;
	NativePlatformDisplayCapsExample& operator=(const NativePlatformDisplayCapsExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	NativePlatformDisplayCapsExample(NativePlatformDisplayCapsExample&&) = default;
	NativePlatformDisplayCapsExample& operator=(NativePlatformDisplayCapsExample&&) = default;
#endif

	static void JSExportInitialize();

   protected:
};

#endif  // _TITANIUM_EXAMPLES_NATIVEPLATFORMDISPLAYCAPSEXAMPLE_HPP_
