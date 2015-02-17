/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVELISTVIEWEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVELISTVIEWEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"
#include <string>

using namespace HAL;

/*!
 @class
 
 @discussion This is an example of how to implement Titanium::UI::ListView
 for a native platform.
 */
class NativeListViewExample final : public Titanium::UI::ListView, public JSExport<NativeListViewExample>
{
public:
	NativeListViewExample(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

	virtual ~NativeListViewExample() TITANIUM_NOEXCEPT;  //= default;
	NativeListViewExample(const NativeListViewExample&) = default;
	NativeListViewExample& operator=(const NativeListViewExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	NativeListViewExample(NativeListViewExample&&) = default;
	NativeListViewExample& operator=(NativeListViewExample&&) = default;
#endif

	static void JSExportInitialize();
};

#endif  // _TITANIUM_EXAMPLES_NATIVELISTVIEWEXAMPLE_HPP_
