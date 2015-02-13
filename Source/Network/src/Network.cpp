/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Network.hpp"
#include "Titanium/detail/TiBase.hpp"

namespace TitaniumWindows
{
	NetworkModule::NetworkModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Titanium::NetworkModule(js_context, arguments)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::NetworkModule::ctor Initialize");
	}


	NetworkModule::~NetworkModule()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::NetworkModule::dtor");
	}

	void NetworkModule::JSExportInitialize()
	{
		JSExport<NetworkModule>::SetClassVersion(1);
		JSExport<NetworkModule>::SetParent(JSExport<Titanium::NetworkModule>::Class());
	}

}  
