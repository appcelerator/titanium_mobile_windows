/**
 * Titanium.Analytics for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Analytics.hpp"
#include "Titanium/analytics_js.hpp"

namespace Titanium
{

    Analytics::Analytics(const JSContext& js_context) TITANIUM_NOEXCEPT
	  : Module(js_context,  "Ti.Analytics"),
		ti_analytics__(js_context.CreateObject())
    {
		TITANIUM_LOG_DEBUG("Analytics:: ctor ", this);
    }

	void Analytics::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
		TITANIUM_LOG_DEBUG("Analytics:: postCallAsConstructor ", this);
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

		TITANIUM_ADD_PROPERTY(Analytics, _receivedResponse);
		TITANIUM_ADD_PROPERTY_READONLY(Analytics, lastEvent);
		TITANIUM_ADD_FUNCTION(Analytics, _start);
		TITANIUM_ADD_FUNCTION(Analytics, _startPostingEvents);
		TITANIUM_ADD_FUNCTION(Analytics, featureEvent);
		TITANIUM_ADD_FUNCTION(Analytics, navEvent);
		TITANIUM_ADD_FUNCTION(Analytics, getLastEvent);
		TITANIUM_ADD_PROPERTY(Analytics, optedOut);
		TITANIUM_ADD_FUNCTION(Analytics, setOptedOut);
		TITANIUM_ADD_FUNCTION(Analytics, getOptedOut);
	}

	JSObject Analytics::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Object_property = Titanium.GetProperty("Analytics");
		TITANIUM_ASSERT(Object_property.IsObject());  // precondition
		return static_cast<JSObject>(Object_property);
	}

	TITANIUM_PROPERTY_GETTER(Analytics, _receivedResponse)
	{
		if (ti_analytics__.HasProperty("getReceivedResponse")) {
			auto func = ti_analytics__.GetProperty("getReceivedResponse");
			return static_cast<JSObject>(func)(get_context().get_global_object());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_PROPERTY_SETTER(Analytics, _receivedResponse)
	{
		if (ti_analytics__.HasProperty("setReceivedResponse")) {
			auto func = ti_analytics__.GetProperty("setReceivedResponse");
			static_cast<JSObject>(func)({argument}, get_context().get_global_object());
			return true;
		}
		return false;
	}

	TITANIUM_PROPERTY_GETTER(Analytics, lastEvent)
	{
		if (ti_analytics__.HasProperty("lastEvent")) {
			auto func = ti_analytics__.GetProperty("lastEvent");
			return static_cast<JSObject>(func)(get_context().get_global_object());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Analytics, _start)
	{
		const auto analytics = GetStaticObject(this_object.get_context()).GetPrivate<Analytics>();
		return this_object.get_context().CreateBoolean(analytics->loadJS());
	}

	TITANIUM_FUNCTION(Analytics, _startPostingEvents)
	{
		if (ti_analytics__.HasProperty("startPostingEvents")) {
			auto func = ti_analytics__.GetProperty("startPostingEvents");
			static_cast<JSObject>(func)(get_context().get_global_object());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Analytics, featureEvent)
	{
		const auto js_context = this_object.get_context();
		const auto analytics = GetStaticObject(js_context).GetPrivate<Analytics>();

		// lazy loading
		const auto loaded = analytics->loadJS();
		if (loaded) {
			auto func = analytics->getTiObject().GetProperty("featureEvent");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Analytics.featureEvent");
			return this_object.get_context().CreateNull();
		}
	}

	TITANIUM_FUNCTION(Analytics, navEvent)
	{
		const auto js_context = this_object.get_context();
		const auto analytics = GetStaticObject(js_context).GetPrivate<Analytics>();

		// lazy loading
		const auto loaded = analytics->loadJS();
		if (loaded) {
			auto func = analytics->getTiObject().GetProperty("navEvent");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute Analytics.navEvent");
			return get_context().CreateNull();
		}
	}

	TITANIUM_PROPERTY_GETTER(Analytics, optedOut)
	{
		if (ti_analytics__.HasProperty("getOptedOut")) {
			auto func = ti_analytics__.GetProperty("getOptedOut");
			return static_cast<JSObject>(func)(get_context().get_global_object());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_PROPERTY_SETTER(Analytics, optedOut)
	{
		if (ti_analytics__.HasProperty("setOptedOut")) {
			auto func = ti_analytics__.GetProperty("setOptedOut");
			static_cast<JSObject>(func)({ argument }, get_context().get_global_object());
			return true;
		}
		return false;
	}

	TITANIUM_FUNCTION(Analytics, setOptedOut)
	{
		ENSURE_ARGUMENT_INDEX(0);
		if (ti_analytics__.HasProperty("setOptedOut")) {
			auto func = ti_analytics__.GetProperty("setOptedOut");
			static_cast<JSObject>(func)({ arguments.at(0) }, get_context().get_global_object());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(Analytics, getOptedOut)
	{
		if (ti_analytics__.HasProperty("getOptedOut")) {
			auto func = ti_analytics__.GetProperty("getOptedOut");
			return static_cast<JSObject>(func)(get_context().get_global_object());
		}
		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION_AS_GETTER(Analytics, getLastEvent, lastEvent);

} // namespace Titanium
