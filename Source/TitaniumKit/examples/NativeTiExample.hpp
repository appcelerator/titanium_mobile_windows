/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVETIEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVETIEXAMPLE_HPP_

#include "Titanium/Titanium.hpp"

using namespace HAL;

/*!
 @class
 @discussion This is an example of how to implement Titanium::Titanium
 for a native Titanium.
 */
class NativeTiExample final : public Titanium::TiModule, public JSExport<NativeTiExample>
{
   public:
	NativeTiExample(const JSContext& js_context) TITANIUM_NOEXCEPT;
	NativeTiExample(const NativeTiExample&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

	virtual ~NativeTiExample() = default;
	NativeTiExample(const NativeTiExample&) = default;
	NativeTiExample& operator=(const NativeTiExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	NativeTiExample(NativeTiExample&&) = default;
	NativeTiExample& operator=(NativeTiExample&&) = default;
#endif

	static void JSExportInitialize();

   protected:
	virtual std::string version() const TITANIUM_NOEXCEPT override final;
	virtual std::string buildDate() const TITANIUM_NOEXCEPT override final;
	virtual std::string buildHash() const TITANIUM_NOEXCEPT override final;
};

#endif  // _TITANIUM_EXAMPLES_NATIVETIEXAMPLE_HPP_
