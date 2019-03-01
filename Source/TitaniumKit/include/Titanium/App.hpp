/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUM_APP_HPP_
#define _TITANIUM_APP_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Titanium App Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.AppModule
	*/
	class TITANIUMKIT_EXPORT AppModule : public Module, public JSExport<AppModule> {

	public:

		/*!
		  @property
		  @abstract EVENT_ACCESSIBILITY_ANNOUNCEMENT
		  @discussion Convenience constant for system event "accessibilityannouncement".
		*/
		TITANIUM_PROPERTY_READONLY_DEF(EVENT_ACCESSIBILITY_ANNOUNCEMENT);

		/*!
		  @property
		  @abstract EVENT_ACCESSIBILITY_CHANGED
		  @discussion Convenience constant for system event "accessibilitychanged".
		*/
		TITANIUM_PROPERTY_READONLY_DEF(EVENT_ACCESSIBILITY_CHANGED);
		/*!
		  @property
		  @abstract accessibilityEnabled
		  @discussion Indicates whether Accessibility is enabled by the system.
		*/
		virtual bool accessibilityEnabled() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract analytics
		  @discussion Indicates whether Analytics is enabled, determined by `tiapp.xml`.
		*/
		virtual bool analytics() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract copyright
		  @discussion Application copyright statement, determined by `tiapp.xml`.
		*/
		virtual std::string copyright() const TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract deployType
		  @discussion Build type that reflects how the application was packaged; either `test`, `development` or `production`.
		*/
		virtual std::string deployType() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract description
		  @discussion Application description, determined by `tiapp.xml`.
		*/
		virtual std::string description() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract disableNetworkActivityIndicator
		  @discussion Prevents network activity indicator from being displayed.
		*/
		virtual bool disableNetworkActivityIndicator() const TITANIUM_NOEXCEPT; 
		/*!
		  @property
		  @abstract forceSplashAsSnapshot
		  @discussion Shows the application's splash screen on app resume.
		*/
		virtual bool forceSplashAsSnapshot() const TITANIUM_NOEXCEPT;
		
		/*!
		  @property
		  @abstract guid
		  @discussion Application globally-unique ID, determined by `tiapp.xml`.
		*/
		virtual std::string guid() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract id
		  @discussion Application ID, from `tiapp.xml`.
		*/
		virtual std::string id() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract idleTimerDisabled
		  @discussion Determines whether the screen is locked when the device is idle.
		*/
		virtual bool idleTimerDisabled() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract installId
		  @discussion The install ID for this application.
		*/
		virtual std::string installId() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract keyboardVisible
		  @discussion Indicates whether or not the soft keyboard is visible.
		*/
		virtual bool keyboardVisible() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract name
		  @discussion Application name, determined by `tiapp.xml`.
		*/
		virtual std::string name() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract proximityDetection
		  @discussion Determines whether proximity detection is enabled.
		*/
		virtual bool getProximityDetection() const TITANIUM_NOEXCEPT;
		virtual void setProximityDetection(const bool&) TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract proximityState
		  @discussion Indicates the state of the device's proximity sensor, according to the <Titanium.App.proximity> event.
		*/
		virtual bool proximityState() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract publisher
		  @discussion Application publisher, from `tiapp.xml`.
		*/
		virtual std::string publisher() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract sessionId
		  @discussion Unique session identifier for the current continuous run of the application.
		*/
		virtual std::string sessionId() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract url
		  @discussion Application URL, from `tiapp.xml`.
		*/
		virtual std::string url() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract version
		  @discussion Application version, from `tiapp.xml`.
		*/
		virtual std::string version() const TITANIUM_NOEXCEPT;

		// FIXME This is a giant hack to stuff the SDK version into _app_info_.json at build-time. Should be on TiModule!
		virtual std::string _sdkVersion() const TITANIUM_NOEXCEPT;

		/*!
		  @property
		  @abstract trackUserInteraction
		  @discussion Indicates whether or not the user interaction shoud be tracked.
		*/
		TITANIUM_PROPERTY_IMPL_DEF(bool, trackUserInteraction);

		/*!
		  @method
		  @abstract fireSystemEvent
		  @discussion Fire a system-level event such as <Titanium.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT>.
		*/
		virtual void fireSystemEvent(const std::string& eventName, const JSObject& param) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract _restart
		  @discussion Terminates the application
		*/
		virtual void _restart() TITANIUM_NOEXCEPT;

		template<typename _T> _T getAppInfo(std::string property, _T defaultValue);
		virtual void loadAppInfo() TITANIUM_NOEXCEPT;
		TITANIUM_FUNCTION_DEF(_loadAppInfo);

		AppModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~AppModule() = default;
		AppModule(const AppModule&) = default;
		AppModule& operator=(const AppModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		AppModule(AppModule&&) = default;
		AppModule& operator=(AppModule&&) = default;
#endif

		static void JSExportInitialize();
		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

		TITANIUM_PROPERTY_READONLY_DEF(accessibilityEnabled);
		TITANIUM_PROPERTY_READONLY_DEF(analytics);
		TITANIUM_PROPERTY_READONLY_DEF(copyright);
		TITANIUM_PROPERTY_READONLY_DEF(deployType);
		TITANIUM_PROPERTY_READONLY_DEF(description);
		TITANIUM_PROPERTY_READONLY_DEF(disableNetworkActivityIndicator);
		TITANIUM_PROPERTY_READONLY_DEF(forceSplashAsSnapshot);
		TITANIUM_PROPERTY_READONLY_DEF(guid);
		TITANIUM_PROPERTY_READONLY_DEF(id);
		TITANIUM_PROPERTY_READONLY_DEF(idleTimerDisabled);
		TITANIUM_PROPERTY_READONLY_DEF(installId);
		TITANIUM_PROPERTY_READONLY_DEF(keyboardVisible);
		TITANIUM_PROPERTY_READONLY_DEF(name);
		TITANIUM_PROPERTY_READONLY_DEF(proximityDetection);
		TITANIUM_PROPERTY_READONLY_DEF(proximityState);
		TITANIUM_PROPERTY_READONLY_DEF(publisher);
		TITANIUM_PROPERTY_READONLY_DEF(sessionId);
		TITANIUM_PROPERTY_READONLY_DEF(url);
		TITANIUM_PROPERTY_READONLY_DEF(version);
		TITANIUM_PROPERTY_READONLY_DEF(_sdkVersion);
		TITANIUM_PROPERTY_READONLY_DEF(Properties);
		TITANIUM_PROPERTY_DEF(trackUserInteraction);

		TITANIUM_FUNCTION_DEF(fireSystemEvent);
		TITANIUM_FUNCTION_DEF(getAccessibilityEnabled);
		TITANIUM_FUNCTION_DEF(getAnalytics);
		TITANIUM_FUNCTION_DEF(getCopyright);
		TITANIUM_FUNCTION_DEF(getDeployType);
		TITANIUM_FUNCTION_DEF(getDescription);
		TITANIUM_FUNCTION_DEF(getDisableNetworkActivityIndicator);
		TITANIUM_FUNCTION_DEF(getForceSplashAsSnapshot);
		TITANIUM_FUNCTION_DEF(getGuid);
		TITANIUM_FUNCTION_DEF(getId);
		TITANIUM_FUNCTION_DEF(getIdleTimerDisabled);
		TITANIUM_FUNCTION_DEF(getInstallId);
		TITANIUM_FUNCTION_DEF(getKeyboardVisible);
		TITANIUM_FUNCTION_DEF(getName);
		TITANIUM_FUNCTION_DEF(getProximityDetection);
		TITANIUM_FUNCTION_DEF(setProximityDetection);
		TITANIUM_FUNCTION_DEF(getProximityState);
		TITANIUM_FUNCTION_DEF(getPublisher);
		TITANIUM_FUNCTION_DEF(getSessionId);
		TITANIUM_FUNCTION_DEF(getUrl);
		TITANIUM_FUNCTION_DEF(getVersion);
		TITANIUM_FUNCTION_DEF(_restart);

		AppModule& PropertiesClass(const JSClass&) TITANIUM_NOEXCEPT;

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		JSClass properties__;
		JSValue app_info__;
		bool accessibilityEnabled__;
		bool analytics__;
		std::string copyright__;
		std::string deployType__;
		std::string description__;
		bool disableNetworkActivityIndicator__;
		bool forceSplashAsSnapshot__;
		std::string guid__;
		std::string id__;
		bool idleTimerDisabled__;
		std::string installId__;
		bool keyboardVisible__;
		std::string name__;
		bool proximityDetection__;
		bool proximityState__;
		std::string publisher__;
		std::string sessionId__;
		std::string url__;
		std::string version__;
		std::string _sdkVersion__;
		bool trackUserInteraction__;
#pragma warning(pop)
	};
}
#endif // _TITANIUM_APP_HPP_