/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "Titanium/App.hpp"

namespace Titanium
{

	template<typename _T> _T AppModule::getAppInfo(std::string property, _T default) {
		
		// Statically create json JSValue to load _app_info_.json once
		static JSValue json = get_context().CreateUndefined();

		// Statically create loadJson javascript function
		static JSFunction loadJson = get_context().CreateFunction(
			"var file = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory+Ti.Filesystem.separator+'_app_info_.json');"
			"if (file.exists()) return JSON.parse(file.read().text);"
		);

		// Statically create readJson javascript function
		static JSFunction readJson = get_context().CreateFunction(
			"if (json != undefined && property in json) return json[property];"
			"return null;",
			{"json", "property"}
		);

		// Load _app_info_.json
		if (json.IsUndefined()) json = loadJson(get_context().get_global_object());

		// Read property
		std::vector<JSValue> args = {json, get_context().CreateString(property)};
		auto result = readJson(args, get_context().get_global_object());
		
		// Return property value if it exists
		if (!result.IsNull()) return static_cast<_T>(result);

		// Return default value
		return default;
	}

	AppModule::AppModule(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Module(js_context, arguments),
		accessibilityEnabled__(false),
		analytics__(false),
		copyright__("__COPYRIGHT__"),
		deployType__("__DEPLOY_TYPE__"),
		description__("__DESCRIPTION__"),
		disableNetworkActivityIndicator__(false),
		forceSplashAsSnapshot__(false),
		guid__("__GUID__"),
		id__("__ID__"),
		idleTimerDisabled__(false),
		keyboardVisible__(false),
		name__("__NAME__"),
		proximityDetection__(false),
		proximityState__(false),
		publisher__("__PUBLISHER__"),
		sessionId__("__SESSION_ID__"),
		url__("__URL__"),
		version__("__VERSION__")
	{
	}

	void AppModule::loadAppInfo() TITANIUM_NOEXCEPT
	{
		analytics__ = getAppInfo<bool>("analytics", analytics__);
		copyright__ = getAppInfo<std::string>("copyright", copyright__);
		deployType__ = getAppInfo<std::string>("deployType", deployType__);
		description__ = getAppInfo<std::string>("description", description__);
		disableNetworkActivityIndicator__ = getAppInfo<bool>("disableNetworkActivityIndicator", disableNetworkActivityIndicator__);
		forceSplashAsSnapshot__ = getAppInfo<bool>("forceSplashAsSnapshot ", forceSplashAsSnapshot__);
		guid__ = getAppInfo<std::string>("guid", guid__);
		id__ = getAppInfo<std::string>("id", id__);
		idleTimerDisabled__ = getAppInfo<bool>("idleTimerDisabled__", idleTimerDisabled__);
		installId__ = getAppInfo<std::string>("installId", installId__);
		keyboardVisible__ = getAppInfo<bool>("keyboardVisible", keyboardVisible__);
		name__ = getAppInfo<std::string>("name", name__);
		publisher__ = getAppInfo<std::string>("publisher", publisher__);
		url__ = getAppInfo<std::string>("url", url__);
		version__ = getAppInfo<std::string>("version", version__);
	}

	JSValue AppModule::EVENT_ACCESSIBILITY_ANNOUNCEMENT() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString("accessibilityannouncement");
	}

	JSValue AppModule::EVENT_ACCESSIBILITY_CHANGED() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString("accessibilitychanged");
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

	bool AppModule::disableNetworkActivityIndicator() const TITANIUM_NOEXCEPT
	{
		return disableNetworkActivityIndicator__;
	}

	bool AppModule::forceSplashAsSnapshot() const TITANIUM_NOEXCEPT
	{
		return forceSplashAsSnapshot__;
	}

	std::string AppModule::guid() const TITANIUM_NOEXCEPT
	{
		return guid__;
	}

	std::string AppModule::id() const TITANIUM_NOEXCEPT
	{
		return id__;
	}

	bool AppModule::idleTimerDisabled() const TITANIUM_NOEXCEPT
	{
		return idleTimerDisabled__;
	}

	std::string AppModule::installId() const TITANIUM_NOEXCEPT
	{
		return installId__;
	}

	bool AppModule::keyboardVisible() const TITANIUM_NOEXCEPT
	{
		return keyboardVisible__;
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
		TITANIUM_LOG_WARN("AppModule::fireSystemEvent: Unimplemented");
		return get_context().CreateUndefined();
	}

	void AppModule::JSExportInitialize() {
		JSExport<AppModule>::SetClassVersion(1);
		JSExport<AppModule>::SetParent(JSExport<Module>::Class());

		JSExport<AppModule>::AddFunctionProperty("_loadAppInfo", std::mem_fn(&AppModule::js_loadAppInfo));

		JSExport<AppModule>::AddValueProperty("EVENT_ACCESSIBILITY_ANNOUNCEMENT", std::mem_fn(&AppModule::EVENT_ACCESSIBILITY_ANNOUNCEMENT));
		JSExport<AppModule>::AddValueProperty("EVENT_ACCESSIBILITY_CHANGED", std::mem_fn(&AppModule::EVENT_ACCESSIBILITY_CHANGED));

		JSExport<AppModule>::AddValueProperty("accessibilityEnabled", std::mem_fn(&AppModule::js_accessibilityEnabled));
		JSExport<AppModule>::AddValueProperty("analytics", std::mem_fn(&AppModule::js_analytics));
		JSExport<AppModule>::AddValueProperty("copyright", std::mem_fn(&AppModule::js_copyright));
		JSExport<AppModule>::AddValueProperty("deployType", std::mem_fn(&AppModule::js_deployType));
		JSExport<AppModule>::AddValueProperty("description", std::mem_fn(&AppModule::js_description));
		JSExport<AppModule>::AddValueProperty("disableNetworkActivityIndicator", std::mem_fn(&AppModule::js_disableNetworkActivityIndicator));
		JSExport<AppModule>::AddValueProperty("forceSplashAsSnapshot", std::mem_fn(&AppModule::js_forceSplashAsSnapshot));
		JSExport<AppModule>::AddValueProperty("guid", std::mem_fn(&AppModule::js_guid));
		JSExport<AppModule>::AddValueProperty("id", std::mem_fn(&AppModule::js_id));
		JSExport<AppModule>::AddValueProperty("installId", std::mem_fn(&AppModule::js_installId));
		JSExport<AppModule>::AddValueProperty("idleTimerDisabled", std::mem_fn(&AppModule::js_idleTimerDisabled));
		JSExport<AppModule>::AddValueProperty("keyboardVisible", std::mem_fn(&AppModule::js_keyboardVisible));
		JSExport<AppModule>::AddValueProperty("name", std::mem_fn(&AppModule::js_name));
		JSExport<AppModule>::AddValueProperty("proximityDetection", std::mem_fn(&AppModule::js_proximityDetection));
		JSExport<AppModule>::AddValueProperty("proximityState", std::mem_fn(&AppModule::js_proximityState));
		JSExport<AppModule>::AddValueProperty("publisher", std::mem_fn(&AppModule::js_publisher));
		JSExport<AppModule>::AddValueProperty("sessionId", std::mem_fn(&AppModule::js_sessionId));
		JSExport<AppModule>::AddValueProperty("url", std::mem_fn(&AppModule::js_url));
		JSExport<AppModule>::AddValueProperty("version", std::mem_fn(&AppModule::js_version));

		JSExport<AppModule>::AddFunctionProperty("fireSystemEvent", std::mem_fn(&AppModule::js_fireSystemEvent));
		JSExport<AppModule>::AddFunctionProperty("getAccessibilityEnabled", std::mem_fn(&AppModule::js_getAccessibilityEnabled));
		JSExport<AppModule>::AddFunctionProperty("getAnalytics", std::mem_fn(&AppModule::js_getAnalytics));
		JSExport<AppModule>::AddFunctionProperty("getCopyright", std::mem_fn(&AppModule::js_getCopyright));
		JSExport<AppModule>::AddFunctionProperty("getDeployType", std::mem_fn(&AppModule::js_getDeployType));
		JSExport<AppModule>::AddFunctionProperty("getDescription", std::mem_fn(&AppModule::js_getDescription));
		JSExport<AppModule>::AddFunctionProperty("getDisableNetworkActivityIndicator", std::mem_fn(&AppModule::js_getDisableNetworkActivityIndicator));
		JSExport<AppModule>::AddFunctionProperty("getForceSplashAsSnapshot", std::mem_fn(&AppModule::js_getForceSplashAsSnapshot));
		JSExport<AppModule>::AddFunctionProperty("getGuid", std::mem_fn(&AppModule::js_getGuid));
		JSExport<AppModule>::AddFunctionProperty("getId", std::mem_fn(&AppModule::js_getId));
		JSExport<AppModule>::AddFunctionProperty("getIdleTimerDisabled", std::mem_fn(&AppModule::js_getIdleTimerDisabled));
		JSExport<AppModule>::AddFunctionProperty("getInstallId", std::mem_fn(&AppModule::js_getInstallId));
		JSExport<AppModule>::AddFunctionProperty("getKeyboardVisible", std::mem_fn(&AppModule::js_getKeyboardVisible));
		JSExport<AppModule>::AddFunctionProperty("getName", std::mem_fn(&AppModule::js_getName));
		JSExport<AppModule>::AddFunctionProperty("getProximityDetection", std::mem_fn(&AppModule::js_getProximityDetection));
		JSExport<AppModule>::AddFunctionProperty("setProximityDetection", std::mem_fn(&AppModule::js_setProximityDetection));
		JSExport<AppModule>::AddFunctionProperty("getProximityState", std::mem_fn(&AppModule::js_getProximityState));
		JSExport<AppModule>::AddFunctionProperty("getPublisher", std::mem_fn(&AppModule::js_getPublisher));
		JSExport<AppModule>::AddFunctionProperty("getSessionId", std::mem_fn(&AppModule::js_getSessionId));
		JSExport<AppModule>::AddFunctionProperty("getUrl", std::mem_fn(&AppModule::js_getUrl));
		JSExport<AppModule>::AddFunctionProperty("getVersion", std::mem_fn(&AppModule::js_getVersion));
	}

	JSValue AppModule::js_loadAppInfo(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT
	{
		loadAppInfo();
		return get_context().CreateUndefined();
	}

	JSValue AppModule::js_accessibilityEnabled() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(accessibilityEnabled());
	}

	JSValue AppModule::js_analytics() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(analytics());
	}

	JSValue AppModule::js_copyright() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(copyright());
	}

	JSValue AppModule::js_deployType() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(deployType());
	}

	JSValue AppModule::js_description() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(description());
	}

	JSValue AppModule::js_disableNetworkActivityIndicator() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(disableNetworkActivityIndicator());
	}

	JSValue AppModule::js_forceSplashAsSnapshot() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(forceSplashAsSnapshot());
	}

	JSValue AppModule::js_guid() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(guid());
	}

	JSValue AppModule::js_id() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(id());
	}

	JSValue AppModule::js_idleTimerDisabled() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(idleTimerDisabled());
	}

	JSValue AppModule::js_installId() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(installId());
	}

	JSValue AppModule::js_keyboardVisible() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(keyboardVisible());
	}

	JSValue AppModule::js_name() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(name());
	}

	JSValue AppModule::js_proximityDetection() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(proximityDetection());
	}

	JSValue AppModule::js_proximityState() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(proximityState());
	}

	JSValue AppModule::js_publisher() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(publisher());
	}

	JSValue AppModule::js_sessionId() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(sessionId());
	}

	JSValue AppModule::js_url() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(url());
	}

	JSValue AppModule::js_version() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(version());
	}

	JSValue AppModule::js_fireSystemEvent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("App.fireSystemEvent is not implemented yet");

		if (arguments.size() < 1) {
			return get_context().CreateUndefined();

		} else if (arguments.size() >= 2) {

			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);

			TITANIUM_ASSERT(_0.IsString());
			TITANIUM_ASSERT(_1.IsObject());

			const std::string eventName = static_cast<std::string>(_0);
			const auto param = _1;

		} else if (arguments.size() >= 1) {

			const auto _0 = arguments.at(0);

			TITANIUM_ASSERT(_0.IsString());

			const std::string eventName = static_cast<std::string>(_0);

		}

		return get_context().CreateUndefined();
	}

	JSValue AppModule::js_getAccessibilityEnabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(accessibilityEnabled());
	}

	JSValue AppModule::js_getAnalytics(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(analytics());
	}

	JSValue AppModule::js_getCopyright(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(copyright());
	}

	JSValue AppModule::js_getDeployType(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(deployType());
	}

	JSValue AppModule::js_getDescription(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(description());
	}

	JSValue AppModule::js_getDisableNetworkActivityIndicator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(disableNetworkActivityIndicator());
	}

	JSValue AppModule::js_getForceSplashAsSnapshot(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(forceSplashAsSnapshot());
	}

	JSValue AppModule::js_getGuid(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(guid());
	}

	JSValue AppModule::js_getId(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(id());
	}

	JSValue AppModule::js_getIdleTimerDisabled(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(idleTimerDisabled());
	}

	JSValue AppModule::js_getInstallId(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(installId());
	}

	JSValue AppModule::js_getKeyboardVisible(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(keyboardVisible());
	}

	JSValue AppModule::js_getName(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(name());
	}

	JSValue AppModule::js_getProximityDetection(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(proximityDetection());
	}

	JSValue AppModule::js_setProximityDetection(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() < 1) {
			return get_context().CreateUndefined();
		}
		const auto _0 = arguments.at(0);

		TITANIUM_ASSERT(_0.IsBoolean());

		const bool proximityDetection = static_cast<bool>(_0);
		proximityDetection__ = proximityDetection;

		return get_context().CreateUndefined();
	}

	JSValue AppModule::js_getProximityState(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateBoolean(proximityState());
	}

	JSValue AppModule::js_getPublisher(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(publisher());
	}

	JSValue AppModule::js_getSessionId(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(sessionId());
	}

	JSValue AppModule::js_getUrl(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(url());
	}

	JSValue AppModule::js_getVersion(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(version());
	}
}