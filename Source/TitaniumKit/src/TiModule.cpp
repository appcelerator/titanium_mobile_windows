/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/TiModule.hpp"
#include <unordered_map>
#include <sstream>

namespace Titanium
{
	TiModule::TiModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Module(js_context, arguments),
	      userAgent__(js_context.CreateString())
	{
	}

	void TiModule::JSExportInitialize()
	{
		JSExport<TiModule>::SetClassVersion(1);
		JSExport<TiModule>::SetParent(JSExport<Module>::Class());
		JSExport<TiModule>::AddValueProperty("version", std::mem_fn(&TiModule::js_get_version));
		JSExport<TiModule>::AddFunctionProperty("getVersion", std::mem_fn(&TiModule::js_getVersion));
		JSExport<TiModule>::AddValueProperty("buildDate", std::mem_fn(&TiModule::js_get_buildDate));
		JSExport<TiModule>::AddFunctionProperty("getBuildDate", std::mem_fn(&TiModule::js_getBuildDate));
		JSExport<TiModule>::AddValueProperty("buildHash", std::mem_fn(&TiModule::js_get_buildHash));
		JSExport<TiModule>::AddFunctionProperty("getBuildHash", std::mem_fn(&TiModule::js_getBuildHash));
		JSExport<TiModule>::AddValueProperty("userAgent", std::mem_fn(&TiModule::js_get_userAgent), std::mem_fn(&TiModule::js_set_userAgent));
		JSExport<TiModule>::AddFunctionProperty("getUserAgent", std::mem_fn(&TiModule::js_getUserAgent));
		JSExport<TiModule>::AddFunctionProperty("setUserAgent", std::mem_fn(&TiModule::js_setUserAgent));
		JSExport<TiModule>::AddFunctionProperty("createBuffer", std::mem_fn(&TiModule::js_createBuffer));
	}

	std::string TiModule::version() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("TiModule::version: Unimplemented");
		return "";
	}

	JSValue TiModule::js_get_version() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(version());
	}

	JSValue TiModule::js_getVersion(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_version();
	}

	std::string TiModule::buildDate() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("TiModule::buildDate: Unimplemented");
		return "";
	}

	JSValue TiModule::js_get_buildDate() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(buildDate());
	}

	JSValue TiModule::js_getBuildDate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_buildDate();
	}

	std::string TiModule::buildHash() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("TiModule::buildHash: Unimplemented");
		return "";
	}

	JSValue TiModule::js_get_buildHash() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(buildHash());
	}

	JSValue TiModule::js_getBuildHash(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_buildHash();
	}

	JSValue TiModule::js_get_userAgent() const TITANIUM_NOEXCEPT
	{
		return userAgent__;
	}

	JSValue TiModule::js_getUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_userAgent();
	}

	JSValue TiModule::js_setUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() < 1) {
			return get_context().CreateUndefined();
		}
		const auto _0 = arguments.at(0);
		TITANIUM_ASSERT(_0.IsString());
		setUserAgent(_0);
		return get_context().CreateUndefined();
	}

	void TiModule::setUserAgent(const JSValue& userAgent) TITANIUM_NOEXCEPT
	{
		userAgent__ = userAgent;
	}

	bool TiModule::js_set_userAgent(const JSValue& argument) TITANIUM_NOEXCEPT
	{
		setUserAgent(argument);
		return true;
	}

	JSValue TiModule::js_createBuffer(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("TiModule::js_createBuffer: Unimplemented");
		return get_context().CreateNull();
	}

}  // namespace Titanium
