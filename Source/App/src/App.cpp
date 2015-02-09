/**
* Titanium.App for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/App.hpp"
#include "Titanium/detail/TiBase.hpp"

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

		bool AppModule::analytics() const TITANIUM_NOEXCEPT
	{
		return analytics__;
	}

		std::string AppModule::copyright() const TITANIUM_NOEXCEPT
	{
		return copyright__;
	}

		std::string AppModule::deployType() const TITANIUM_NOEXCEPT
	{
		return deployType__;
	}

		std::string AppModule::description() const TITANIUM_NOEXCEPT
	{
		return description__;
	}

		std::string AppModule::guid() const TITANIUM_NOEXCEPT
	{
		return guid__;
	}

		std::string AppModule::id() const TITANIUM_NOEXCEPT
	{
		return id__;
	}

		std::string AppModule::name() const TITANIUM_NOEXCEPT
	{
		return name__;
	}

		bool AppModule::proximityDetection() const TITANIUM_NOEXCEPT
	{
		return proximityDetection__;
	}

		bool AppModule::proximityState() const TITANIUM_NOEXCEPT
	{
		return proximityState__;
	}

		std::string AppModule::publisher() const TITANIUM_NOEXCEPT
	{
		return publisher__;
	}

		std::string AppModule::sessionId() const TITANIUM_NOEXCEPT
	{
		return sessionId__;
	}

		std::string AppModule::url() const TITANIUM_NOEXCEPT
	{
		return url__;
	}

		std::string AppModule::version() const TITANIUM_NOEXCEPT
	{
		return version__;
	}

		JSValue AppModule::fireSystemEvent(const std::string& eventName, JSValue param) TITANIUM_NOEXCEPT
	{
		// TODO : Depends on WebView
		TITANIUM_LOG_WARN("App.fireSystemEvent is not implemented yet");
		return get_context().CreateUndefined();
	}

}  // namespace TitaniumWindows