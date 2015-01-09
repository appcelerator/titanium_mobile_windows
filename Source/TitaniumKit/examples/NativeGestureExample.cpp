/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeGestureExample.hpp"
#include <iostream>

NativeGestureExample::NativeGestureExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::Gesture(js_context)
{
}

NativeGestureExample::NativeGestureExample(const NativeGestureExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::Gesture(rhs, arguments)
{
}

void NativeGestureExample::JSExportInitialize()
{
	JSExport<NativeGestureExample>::SetClassVersion(1);
	JSExport<NativeGestureExample>::SetParent(JSExport<Titanium::Gesture>::Class());
}

void NativeGestureExample::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
{
}

void NativeGestureExample::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
{
}

Titanium::UI::ORIENTATION NativeGestureExample::get_orientation() const TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeGestureExample::get_orientation");
	return Titanium::UI::ORIENTATION::UNKNOWN;
}
