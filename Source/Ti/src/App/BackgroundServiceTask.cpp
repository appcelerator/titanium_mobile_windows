/**
* Ti.App.Windows.BackgroundServiceTask
*
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/App/BackgroundServiceTask.hpp"
#include "TitaniumWindows/App/BackgroundService.hpp"
#include "Titanium/GeolocationModule.hpp"
#include <ppltasks.h>

namespace TitaniumWindows
{
	namespace App
	{
		namespace WindowsXaml
		{
			BackgroundServiceTask::BackgroundServiceTask(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.App.Windows.BackgroundServiceTask")
			{
				TITANIUM_LOG_DEBUG("BackgroundServiceTask::ctor Initialize");
			}

			BackgroundServiceTask::~BackgroundServiceTask()
			{
				TITANIUM_LOG_DEBUG("BackgroundServiceTask::dtor");
			}

			void BackgroundServiceTask::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
			{
				Titanium::Module::postCallAsConstructor(js_context, arguments);
				TITANIUM_LOG_DEBUG("BackgroundServiceTask::postCallAsConstructor");
			}

			void BackgroundServiceTask::JSExportInitialize()
			{
				JSExport<BackgroundServiceTask>::SetClassVersion(1);
				JSExport<BackgroundServiceTask>::SetParent(JSExport<Titanium::Module>::Class());
				TITANIUM_ADD_FUNCTION(BackgroundServiceTask, unregister);
				TITANIUM_ADD_PROPERTY_READONLY(BackgroundServiceTask, taskId);
			}

			TITANIUM_PROPERTY_READ(BackgroundServiceTask, std::uint32_t, taskId);

			void BackgroundServiceTask::construct(const std::uint32_t& id, BackgroundTaskRegistration^ registration)
			{
				taskId__   = id;
			}

			void BackgroundServiceTask::unregister()
			{
				const auto task = BackgroundService::GetTask(taskId__);
				if (task) {
					task->Unregister(true);
				}
			}

			TITANIUM_PROPERTY_GETTER_INT(BackgroundServiceTask, taskId);

			TITANIUM_FUNCTION(BackgroundServiceTask, unregister)
			{
				unregister();
				return get_context().CreateUndefined();
			}
		} // namespace WindowsXaml
	}  // namespace App
}  // namespace TitaniumWindows
