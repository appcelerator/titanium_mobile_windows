/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/App.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	AppModule::AppModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Titanium::AppModule(js_context, arguments)
	{
		TITANIUM_LOG_DEBUG("App::ctor Initialize");
	}

	void AppModule::JSExportInitialize() {
		JSExport<AppModule>::SetClassVersion(1);
		JSExport<AppModule>::SetParent(JSExport<Titanium::AppModule>::Class());
	}

	bool AppModule::accessibilityEnabled() const TITANIUM_NOEXCEPT
	{
		return accessibilityEnabled__;
	}

	bool AppModule::proximityDetection() const TITANIUM_NOEXCEPT
	{
		return proximityDetection__;
	}

	bool AppModule::proximityState() const TITANIUM_NOEXCEPT
	{
		return proximityState__;
	}

	std::string AppModule::sessionId() const TITANIUM_NOEXCEPT
	{
		return sessionId__;
	}

	JSValue AppModule::fireSystemEvent(const std::string& eventName, JSValue param) TITANIUM_NOEXCEPT
	{
		// TODO : Depends on WebView
		TITANIUM_LOG_WARN("App.fireSystemEvent is not implemented yet");
		return get_context().CreateUndefined();
	}

}  // namespace TitaniumWindows