/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeAccelerometerExample.hpp"
#include <iostream>

NativeAccelerometerExample::NativeAccelerometerExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::Accelerometer(js_context)
{
}

NativeAccelerometerExample::NativeAccelerometerExample(const NativeAccelerometerExample& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::Accelerometer(rhs, arguments)
{
}

void NativeAccelerometerExample::JSExportInitialize()
{
	JSExport<NativeAccelerometerExample>::SetClassVersion(1);
	JSExport<NativeAccelerometerExample>::SetParent(JSExport<Titanium::Accelerometer>::Class());
}

void NativeAccelerometerExample::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
{
}

void NativeAccelerometerExample::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
{
}
