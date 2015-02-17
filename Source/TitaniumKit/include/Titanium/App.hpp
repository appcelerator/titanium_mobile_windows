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
#include "Titanium/App/Properties.hpp"

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
		virtual JSValue EVENT_ACCESSIBILITY_ANNOUNCEMENT() const TITANIUM_NOEXCEPT;
		/*!
		  @property
		  @abstract EVENT_ACCESSIBILITY_CHANGED
		  @discussion Convenience constant for system event "accessibilitychanged".
		*/
		virtual JSValue EVENT_ACCESSIBILITY_CHANGED() const TITANIUM_NOEXCEPT;
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
		virtual bool proximityDetection() const TITANIUM_NOEXCEPT;
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
		/*!
		  @method
		  @abstract fireSystemEvent
		  @discussion Fire a system-level event such as <Titanium.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT>.
		*/
		virtual JSValue fireSystemEvent(const std::string& eventName, JSValue param) TITANIUM_NOEXCEPT;

		template<typename _T> _T getAppInfo(std::string property, _T default);
		virtual void loadAppInfo() TITANIUM_NOEXCEPT;
		virtual JSValue js_loadAppInfo(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		AppModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

		virtual ~AppModule() = default;
		AppModule(const AppModule&) = default;
		AppModule& operator=(const AppModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		AppModule(AppModule&&) = default;
		AppModule& operator=(AppModule&&) = default;
#endif

		static void JSExportInitialize();

		virtual JSValue js_accessibilityEnabled() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_analytics() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_copyright() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_deployType() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_description() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_disableNetworkActivityIndicator() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_forceSplashAsSnapshot() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_guid() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_id() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_idleTimerDisabled() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_installId() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_keyboardVisible() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_name() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_proximityDetection() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_proximityState() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_publisher() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_sessionId() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_url() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_version() const TITANIUM_NOEXCEPT final;

		virtual JSValue js_fireSystemEvent(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getAccessibilityEnabled(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getAnalytics(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getCopyright(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getDeployType(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getDescription(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getDisableNetworkActivityIndicator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getForceSplashAsSnapshot(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getGuid(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getId(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getIdleTimerDisabled(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getInstallId(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getKeyboardVisible(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getName(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getProximityDetection(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_setProximityDetection(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getProximityState(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getPublisher(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getSessionId(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getUrl(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_getVersion(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
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
#pragma warning(pop)
	};
}
#endif // _TITANIUM_APP_HPP_