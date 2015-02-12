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
	template<typename _T> _T AppModule::getAppInfo(std::string property, _T default) const {
		static JSFunction readAppInfo = get_context().CreateFunction(
			"var file = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory+'\\\\_app_info_.json');"
			"if (file.exists()) {"
			"    var json = JSON.parse(file.read().text);"
			"    if (property in json) return json[property];"
			"    return null;"
			"}",
			{"property"});

		const auto result = readAppInfo({get_context().CreateString(property)}, get_context().get_global_object());
		
		if (!result.IsNull()) return static_cast<_T>(result);
		return default;
	}

	void AppModule::loadAppInfo() const TITANIUM_NOEXCEPT
	{
		analytics__ = getAppInfo<bool>("analytics", analytics__);
		copyright__ = getAppInfo<std::string>("copyright", copyright__);
		deployType__ = getAppInfo<std::string>("deployType", deployType__);
		description__ = getAppInfo<std::string>("description", description__);
		guid__ = getAppInfo<std::string>("guid", guid__);
		id__ = getAppInfo<std::string>("id", id__);
		name__ = getAppInfo<std::string>("name", name__);
		publisher__ = getAppInfo<std::string>("publisher", publisher__);
		url__ = getAppInfo<std::string>("url", url__);
		version__ = getAppInfo<std::string>("version", version__);
	}

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