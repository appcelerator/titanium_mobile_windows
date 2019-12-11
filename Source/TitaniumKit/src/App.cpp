/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/App.hpp"
#include "Titanium/App/Properties.hpp"
#include "Titanium/UI/Window.hpp"
#include "Titanium/GlobalObject.hpp"

namespace Titanium
{

	template<typename _T> _T AppModule::getAppInfo(std::string property, _T defaultValue) {

		// Skip
		static bool skip = false;
		if (skip) return defaultValue;

		// Statically create loadJson javascript function
		static JSFunction loadJson = get_context().CreateFunction(
			"var file = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory+Ti.Filesystem.separator+'_app_info_.json');"
			"if (file.exists()) return JSON.parse(file.read().text);"
		);

		// Statically create readJson javascript function
		static JSFunction readJson = get_context().CreateFunction(
			"if (json != undefined && property in json) return json[property];"
			"return null;",
			{JSString("json"), JSString("property")}
		);

		// Load _app_info_.json
		if (app_info__.IsUndefined()) {
			app_info__ = loadJson(get_context().get_global_object());

			// _app_info_.json does not exist, skip attempting to load it
			if (app_info__.IsUndefined()) {
				skip = true;
				return defaultValue;
			}
		}

		// Read property
		std::vector<JSValue> args = {app_info__, get_context().CreateString(property)};
		auto result = readJson(args, get_context().get_global_object());

		// Return property value if it exists
		if (!result.IsNull()) return static_cast<_T>(result);

		// Return default value
		return defaultValue;
	}

	AppModule::AppModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.App"),
		app_info__(get_context().CreateUndefined()),
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
		trackUserInteraction__(false),
		url__("__URL__"),
		version__("__VERSION__"),
		_sdkVersion__("__TITANIUM_VERSION__") // FIXME This should live in TiModule!
	{
		TITANIUM_LOG_DEBUG("AppModule:: ctor ", this);
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
		_sdkVersion__ = getAppInfo<std::string>("sdkVersion", _sdkVersion__);
	}

	TITANIUM_PROPERTY_GETTER(AppModule, EVENT_ACCESSIBILITY_ANNOUNCEMENT)
	{
		return get_context().CreateString("accessibilityannouncement");
	}

	TITANIUM_PROPERTY_GETTER(AppModule, EVENT_ACCESSIBILITY_CHANGED)
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

	bool AppModule::getProximityDetection() const TITANIUM_NOEXCEPT
	{
		return proximityDetection__;
	}

	void AppModule::setProximityDetection(const bool& value) TITANIUM_NOEXCEPT
	{
		proximityDetection__ = value;
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

	std::string AppModule::_sdkVersion() const TITANIUM_NOEXCEPT
	{
		return _sdkVersion__;
	}

	TITANIUM_PROPERTY_READWRITE(AppModule, bool, trackUserInteraction);

	void AppModule::fireSystemEvent(const std::string& eventName, const JSObject& param) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("AppModule::fireSystemEvent: Unimplemented");
	}

	void AppModule::_restart() TITANIUM_NOEXCEPT
	{
		Titanium::UI::Window::Restart();
		const auto globalObject = get_context().get_global_object();
		const auto globalObject_ptr = globalObject.GetPrivate<Titanium::GlobalObject>();
		globalObject_ptr->requireModule(globalObject, "/app", true);
	}

	AppModule& AppModule::PropertiesClass(const JSClass& Properties) TITANIUM_NOEXCEPT
	{
		properties__ = Properties;
		return *this;
	}

	void AppModule::JSExportInitialize() {
		JSExport<AppModule>::SetClassVersion(1);
		JSExport<AppModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_FUNCTION(AppModule, _loadAppInfo);

		TITANIUM_ADD_CONSTANT_PROPERTY(AppModule, EVENT_ACCESSIBILITY_ANNOUNCEMENT);
		TITANIUM_ADD_CONSTANT_PROPERTY(AppModule, EVENT_ACCESSIBILITY_CHANGED);
		TITANIUM_ADD_CONSTANT_PROPERTY(AppModule, Properties);

		TITANIUM_ADD_PROPERTY_READONLY(AppModule, accessibilityEnabled);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, analytics);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, copyright);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, deployType);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, description);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, disableNetworkActivityIndicator);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, forceSplashAsSnapshot);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, guid);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, id);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, installId);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, idleTimerDisabled);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, keyboardVisible);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, name);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, proximityDetection);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, proximityState);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, publisher);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, sessionId);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, url);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, version);
		TITANIUM_ADD_PROPERTY_READONLY(AppModule, _sdkVersion);
		TITANIUM_ADD_PROPERTY(AppModule, trackUserInteraction);

		TITANIUM_ADD_FUNCTION(AppModule, fireSystemEvent);
		TITANIUM_ADD_FUNCTION(AppModule, getAccessibilityEnabled);
		TITANIUM_ADD_FUNCTION(AppModule, getAnalytics);
		TITANIUM_ADD_FUNCTION(AppModule, getCopyright);
		TITANIUM_ADD_FUNCTION(AppModule, getDeployType);
		TITANIUM_ADD_FUNCTION(AppModule, getDescription);
		TITANIUM_ADD_FUNCTION(AppModule, getDisableNetworkActivityIndicator);
		TITANIUM_ADD_FUNCTION(AppModule, getForceSplashAsSnapshot);
		TITANIUM_ADD_FUNCTION(AppModule, getGuid);
		TITANIUM_ADD_FUNCTION(AppModule, getId);
		TITANIUM_ADD_FUNCTION(AppModule, getIdleTimerDisabled);
		TITANIUM_ADD_FUNCTION(AppModule, getInstallId);
		TITANIUM_ADD_FUNCTION(AppModule, getKeyboardVisible);
		TITANIUM_ADD_FUNCTION(AppModule, getName);
		TITANIUM_ADD_FUNCTION(AppModule, getProximityDetection);
		TITANIUM_ADD_FUNCTION(AppModule, setProximityDetection);
		TITANIUM_ADD_FUNCTION(AppModule, getProximityState);
		TITANIUM_ADD_FUNCTION(AppModule, getPublisher);
		TITANIUM_ADD_FUNCTION(AppModule, getSessionId);
		TITANIUM_ADD_FUNCTION(AppModule, getUrl);
		TITANIUM_ADD_FUNCTION(AppModule, getVersion);
		TITANIUM_ADD_FUNCTION(AppModule, _restart);
	}

	JSObject AppModule::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		static JSObject cached = js_context.CreateObject();
		static std::once_flag of;
		std::call_once(of, [=] {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Object_property = Titanium.GetProperty("App");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			cached = static_cast<JSObject>(Object_property);
		});
		return cached;
	}

	TITANIUM_FUNCTION(AppModule, _restart)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		object_ptr->_restart();

		return get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(AppModule, _loadAppInfo)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		object_ptr->loadAppInfo();

		return get_context().CreateUndefined();
	}

	TITANIUM_PROPERTY_GETTER(AppModule, Properties)
	{
		return get_context().CreateObject(properties__);
	}

	TITANIUM_PROPERTY_GETTER(AppModule, accessibilityEnabled)
	{
		return get_context().CreateBoolean(accessibilityEnabled());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, analytics)
	{
		return get_context().CreateBoolean(analytics());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, copyright)
	{
		return get_context().CreateString(copyright());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, deployType)
	{
		return get_context().CreateString(deployType());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, description)
	{
		return get_context().CreateString(description());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, disableNetworkActivityIndicator)
	{
		return get_context().CreateBoolean(disableNetworkActivityIndicator());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, forceSplashAsSnapshot)
	{
		return get_context().CreateBoolean(forceSplashAsSnapshot());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, guid)
	{
		return get_context().CreateString(guid());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, id)
	{
		return get_context().CreateString(id());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, idleTimerDisabled)
	{
		return get_context().CreateBoolean(idleTimerDisabled());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, installId)
	{
		return get_context().CreateString(installId());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, keyboardVisible)
	{
		return get_context().CreateBoolean(keyboardVisible());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, name)
	{
		return get_context().CreateString(name());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, proximityDetection)
	{
		return get_context().CreateBoolean(getProximityDetection());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, proximityState)
	{
		return get_context().CreateBoolean(proximityState());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, publisher)
	{
		return get_context().CreateString(publisher());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, sessionId)
	{
		return get_context().CreateString(sessionId());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, url)
	{
		return get_context().CreateString(url());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, version)
	{
		return get_context().CreateString(version());
	}

	TITANIUM_PROPERTY_GETTER(AppModule, _sdkVersion)
	{
		return get_context().CreateString(_sdkVersion());
	}

	TITANIUM_PROPERTY_GETTER_BOOL(AppModule, trackUserInteraction);
	TITANIUM_PROPERTY_SETTER_BOOL(AppModule, trackUserInteraction);

	TITANIUM_FUNCTION(AppModule, fireSystemEvent)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		if (arguments.size() >= 1) {
			ENSURE_STRING_AT_INDEX(eventName, 0);
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(param, 1);

			object_ptr->fireSystemEvent(eventName, param);
		}

		return js_context.CreateUndefined();
	}

	TITANIUM_FUNCTION(AppModule, getAccessibilityEnabled)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->accessibilityEnabled());
	}

	TITANIUM_FUNCTION(AppModule, getAnalytics)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->analytics());
	}

	TITANIUM_FUNCTION(AppModule, getCopyright)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->copyright());
	}

	TITANIUM_FUNCTION(AppModule, getDeployType)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->deployType());
	}

	TITANIUM_FUNCTION(AppModule, getDescription)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->description());
	}

	TITANIUM_FUNCTION(AppModule, getDisableNetworkActivityIndicator)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->disableNetworkActivityIndicator());
	}

	TITANIUM_FUNCTION(AppModule, getForceSplashAsSnapshot)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->forceSplashAsSnapshot());
	}

	TITANIUM_FUNCTION(AppModule, getGuid)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->guid());
	}

	TITANIUM_FUNCTION(AppModule, getId)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->id());
	}

	TITANIUM_FUNCTION(AppModule, getIdleTimerDisabled)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->idleTimerDisabled());
	}

	TITANIUM_FUNCTION(AppModule, getInstallId)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->installId());
	}

	TITANIUM_FUNCTION(AppModule, getKeyboardVisible)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->keyboardVisible());
	}

	TITANIUM_FUNCTION(AppModule, getName)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->name());
	}

	TITANIUM_FUNCTION(AppModule, getProximityDetection)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->getProximityDetection());
	}

	TITANIUM_FUNCTION(AppModule, setProximityDetection)
	{
		if (arguments.size() < 1) {
			return this_object.get_context().CreateUndefined();
		}

		ENSURE_BOOL_AT_INDEX(proximityDetection, 0);

		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		object_ptr->setProximityDetection(proximityDetection);

		return js_context.CreateUndefined();
	}

	TITANIUM_FUNCTION(AppModule, getProximityState)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateBoolean(object_ptr->proximityState());
	}

	TITANIUM_FUNCTION(AppModule, getPublisher)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->publisher());
	}

	TITANIUM_FUNCTION(AppModule, getSessionId)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->sessionId());
	}

	TITANIUM_FUNCTION(AppModule, getUrl)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->url());
	}

	TITANIUM_FUNCTION(AppModule, getVersion)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<AppModule>();

		return js_context.CreateString(object_ptr->version());
	}
}
