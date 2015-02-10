/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/NetworkModule.hpp"

namespace Titanium
{
	static void applyProperties(JSObject& obj, const JSObject& parameters)
	{
		if (parameters.GetPropertyNames().GetCount() > 0) {
			const auto propertyNames = parameters.GetPropertyNames();
			for (const auto& property_name : static_cast<std::vector<JSString>>(propertyNames)) {
				obj.SetProperty(property_name, parameters.GetProperty(property_name));
			}
		}
	}

	NetworkModule::NetworkModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Module(js_context)
	{
	}

	JSObject NetworkModule::createHTTPClient(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Network::createHTTPClient: ");

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Network_property = Titanium.GetProperty("Network");
		TITANIUM_ASSERT(Network_property.IsObject());  // precondition
		JSObject Network = static_cast<JSObject>(Network_property);

		JSValue HTTPClient_property = Network.GetProperty("HTTPClient");
		TITANIUM_ASSERT(HTTPClient_property.IsObject());  // precondition
		JSObject HTTPClient = static_cast<JSObject>(HTTPClient_property);

		auto httpClient = HTTPClient.CallAsConstructor();
		Titanium::applyProperties(httpClient, parameters);
		return httpClient;
	}

	void NetworkModule::JSExportInitialize()
	{
		JSExport<NetworkModule>::SetClassVersion(1);
		JSExport<NetworkModule>::SetParent(JSExport<Module>::Class());
		JSExport<NetworkModule>::AddFunctionProperty("createHTTPClient", std::mem_fn(&NetworkModule::js_createHTTPClient));
	}

	JSObject NetworkModule::js_createHTTPClient(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = static_cast<JSObject>(_0);
		}

		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue network_property = Titanium.GetProperty("Network");
		TITANIUM_ASSERT(network_property.IsObject());  // precondition

		return createHTTPClient(parameters, this_object);
	}
}
