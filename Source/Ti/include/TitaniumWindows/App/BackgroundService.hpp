/**
* Ti.App.Windows.BackgroundService
*
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_APP_WINDOWS_BACKGROUNDSERVICE_HPP_
#define _TITANIUMWINDOWS_APP_WINDOWS_BACKGROUNDSERVICE_HPP_

#include "TitaniumWindows_Ti_EXPORT.h"
#include "Titanium/Module.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <unordered_map>
#include <atomic>

using namespace HAL;

namespace TitaniumWindows_Ti
{
	/*
	 * @class
	 * @discussion This is background task for BackgroundService maintenance.
	        This task is only used for testing/debugging purpose.
	        Entrypoint: TitaniumWindows_Ti.BackgroundServiceTask
	 */
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BackgroundServiceTask sealed : public Windows::ApplicationModel::Background::IBackgroundTask
	{
	public:
		virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance);
	};
}
namespace TitaniumWindows
{
	namespace App
	{
		// Use WindowsXaml namespace instead of "Windows"
		// because it screws up entire namespace in Xaml...
		namespace WindowsXaml
		{
			class BackgroundServiceTask;

			/*!
			  @class
			  @discussion This is the Titanium.App.Windows.BackgroundService implementation
			*/
			class TITANIUMWINDOWS_TI_EXPORT BackgroundService final : public Titanium::Module, public JSExport<BackgroundService>
			{

			public:
				BackgroundService(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~BackgroundService();
				BackgroundService(const BackgroundService&)            = default;
				BackgroundService& operator=(const BackgroundService&) = default;
	#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				BackgroundService(BackgroundService&&)                 = default;
				BackgroundService& operator=(BackgroundService&&)      = default;
	#endif

				/*!
				  @method
				  @abstract registerTimerTask
				  @param entryPoint Sets callback C++/CX class name that is invoked on time event. Callback class should implement Windows::ApplicationModel::Background::IBackgroundTask.
				  @param freshnessTime Sets interval of a time event in minutes. Windows requires at least 15 minutes
				  @param oneShot Sets whether the time event trigger will be used only once or each time the FreshnessTime interval elapses.
				  @return BackgroundServiceTask object
				  @discussion Register a time event that triggers a background task to run.
				*/
				TITANIUM_FUNCTION_DEF(registerTimerTask);

				/*!
				  @method
				  @abstract registerPushNotificationTask
				  @param entryPoint Sets callback C++/CX class name that is invoked on time event. Callback class should implement Windows::ApplicationModel::Background::IBackgroundTask.
				  @return BackgroundServiceTask object
				  @discussion Register a push notification event that triggers a background task to run.
				*/
				TITANIUM_FUNCTION_DEF(registerPushNotificationTask);

				/*!
				  @method
				  @abstract unregisterTask
				  @param task (task object or task id)
				  @discussion Unregisters registered background task associated with this application.
				*/
				TITANIUM_FUNCTION_DEF(unregisterTask);

				/*!
				  @method
				  @abstract unregisterAllTasks
				  @discussion Unregisters all registered background task associated with this application.
				*/
				TITANIUM_FUNCTION_DEF(unregisterAllTasks);

				static void JSExportInitialize();
				virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

				std::shared_ptr<BackgroundServiceTask> registerPushNotificationTask(::Platform::String^ entryPoint, Windows::ApplicationModel::Background::IBackgroundCondition^ condition = nullptr);
				std::shared_ptr<BackgroundServiceTask> registerTimerTask(::Platform::String^ entryPoint, const std::uint32_t& freshnessTime, const bool& oneShot, Windows::ApplicationModel::Background::IBackgroundCondition^ condition = nullptr);
				std::shared_ptr<BackgroundServiceTask> registerTask(::Platform::String^ entryPoint, Windows::ApplicationModel::Background::IBackgroundTrigger^ trigger, Windows::ApplicationModel::Background::IBackgroundCondition^ condition);

				static Windows::ApplicationModel::Background::IBackgroundTaskRegistration^ GetTask(const std::uint32_t& id);
				static void UnregisterTask(const std::uint32_t& id);
				static void UnregisterTasks();
			protected:
#pragma warning(push)
#pragma warning(disable : 4251)
				static std::atomic<std::uint32_t> task_id_generator__;
#pragma warning(pop)
			};
		} // namespace WindowsXaml
	}  // namespace App
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_APP_WINDOWS_BACKGROUNDSERVICE_HPP_