/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEWEBVIEWEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEWEBVIEWEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
  @class
  @discussion This is an example of how to implement Titanium::UI::WebView
  for a native platform.
 */
class NativeWebViewExample final : public Titanium::UI::WebView, public JSExport<NativeWebViewExample>
{
public:
	virtual bool canGoBack() TITANIUM_NOEXCEPT override final;

	NativeWebViewExample(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

	virtual ~NativeWebViewExample() TITANIUM_NOEXCEPT;  //= default;
	NativeWebViewExample(const NativeWebViewExample&) = default;
	NativeWebViewExample& operator=(const NativeWebViewExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	NativeWebViewExample(NativeWebViewExample&&) = default;
	NativeWebViewExample& operator=(NativeWebViewExample&&) = default;
#endif

	static void JSExportInitialize();
};

#endif  // _TITANIUM_EXAMPLES_NATIVEWEBVIEWEXAMPLE_HPP_
