/**
 * Titanium.Analytics for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include <string>
#include "Titanium/Analytics.hpp"
#include "Titanium/analytics_js.hpp"

namespace Titanium
{

    Analytics::Analytics(const JSContext& js_context) TITANIUM_NOEXCEPT
	  : Module(js_context),
		ti_analytics__(js_context.CreateObject())
    {
		TITANIUM_LOG_DEBUG("Analytics:: ctor ", this);
    }

	void Analytics::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
		HAL_LOG_DEBUG("Analytics:: postCallAsConstructor ", this);
	}

	bool Analytics::loadJS()
	{
		if (ti_analytics__.HasProperty("lastEvent") && ti_analytics__.HasProperty("featureEvent") && ti_analytics__.HasProperty("navEvent")) {
			return true;
		}

		JSContext context = get_context();
		auto export_object = context.CreateObject();
		export_object.SetProperty("global", context.get_global_object());

		context.JSEvaluateScript(analytics_js, export_object);

		if (export_object.HasProperty("exports")) {
			ti_analytics__ = static_cast<JSObject>(export_object.GetProperty("exports"));
		} else {
			return false;
		}
		return true;
	}

	void Analytics::JSExportInitialize() {
		JSExport<Analytics>::SetClassVersion(1);
		JSExport<Analytics>::SetParent(JSExport<Module>::Class());

		//JSExport<Analytics>::AddValueProperty("lastEvent", std::mem_fn(&Analytics::js_lastEvent));

		JSExport<Analytics>::AddFunctionProperty("featureEvent", std::mem_fn(&Analytics::js_featureEvent));
		JSExport<Analytics>::AddFunctionProperty("navEvent", std::mem_fn(&Analytics::js_navEvent));
		JSExport<Analytics>::AddFunctionProperty("getLastEvent", std::mem_fn(&Analytics::js_getLastEvent));
	}

	JSValue Analytics::js_lastEvent() const TITANIUM_NOEXCEPT
	{
//		// lazy loading
//		const auto loaded = loadJS();
//		if (loaded) {
//			return ti_analytics__.GetProperty("lastEvent");
//		} else {
//			TITANIUM_LOG_ERROR("Failed to execute Analytics.lastEvent");
			return get_context().CreateNull();
//		}
	}

	JSValue Analytics::js_featureEvent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(arguments.size() >= 1);

		const auto _0 = arguments.at(0);
		TITANIUM_ASSERT(_0.IsString());
		
		if (arguments.size() == 2) {
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_1.IsObject());
		}

		// lazy loading
		const auto loaded = loadJS();
		if (loaded) {
			auto func = ti_analytics__.GetProperty("featureEvent");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Database.featureEvent");
			return get_context().CreateNull();
		}
	}

	JSValue Analytics::js_navEvent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(arguments.size() >= 2 && arguments.size() <= 4);

		// from {String}
		const auto _0 = arguments.at(0);
		TITANIUM_ASSERT(_0.IsString());

		// to {String}
		const auto _1 = arguments.at(1);
		TITANIUM_ASSERT(_1.IsString());
		
		if (arguments.size() > 2) {
			// name {String} optional
			const auto _2 = arguments.at(2);
			TITANIUM_ASSERT(_2.IsString());

			// data {Object} optional
			if (arguments.size() > 3) {
				const auto _3 = arguments.at(3);
				TITANIUM_ASSERT(_3.IsObject());
			}
		}

		// lazy loading
		const auto loaded = loadJS();
		if (loaded) {
			auto func = ti_analytics__.GetProperty("navEvent");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Database.navEvent");
			return get_context().CreateNull();
		}
	}

	JSValue Analytics::js_getLastEvent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_lastEvent();
	}

} // namespace Titanium