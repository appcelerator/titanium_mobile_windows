/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_EXAMPLES_NATIVEGLOBALOBJECTEXAMPLE_HPP_
#define _TITANIUM_EXAMPLES_NATIVEGLOBALOBJECTEXAMPLE_HPP_

#include "Titanium/GlobalObject.hpp"
#include <unordered_map>

using namespace HAL;

/*!
 @class
 
 @discussion This is an example of how to implement Titanium::GlobalObject
 for a native platform.
 */
class NativeGlobalObjectExample final : public Titanium::GlobalObject, public JSExport<NativeGlobalObjectExample>
{
public:
	void add_require(const std::string& name, const std::string& body) TITANIUM_NOEXCEPT;

	NativeGlobalObjectExample(const JSContext&) TITANIUM_NOEXCEPT;

	virtual ~NativeGlobalObjectExample() TITANIUM_NOEXCEPT;  //= default;
	NativeGlobalObjectExample(const NativeGlobalObjectExample&) = default;
	NativeGlobalObjectExample& operator=(const NativeGlobalObjectExample&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	NativeGlobalObjectExample(NativeGlobalObjectExample&&) = default;
	NativeGlobalObjectExample& operator=(NativeGlobalObjectExample&&) = default;
#endif

	static void JSExportInitialize();

protected:
	virtual std::string readRequiredModule(const JSObject& parent, const std::string& path) const override final;
	virtual bool requiredModuleExists(const std::string& path) const TITANIUM_NOEXCEPT override final;

private:
	std::unordered_map<std::string, std::string> require_resource__;
};

#endif  // _TITANIUM_EXAMPLES_NATIVEGLOBALOBJECTEXAMPLE_HPP_
