/**
* Ti.App.Windows.BackgroundService
*
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/App/BackgroundService.hpp"
#include "TitaniumWindows/App/BackgroundServiceTask.hpp"
#include "Titanium/GeolocationModule.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <boost/algorithm/string/predicate.hpp>

using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Background;
using namespace Windows::Storage;

namespace TitaniumWindows_Ti
{
	void BackgroundServiceTask::Run(IBackgroundTaskInstance^ taskInstance)
	{
		//
		// For debugging purpose: 
		//   Saves run count to the local property so we can check if background task is running.
		//   Saving value to local settings because background task runs on each interval and it does not have state.
		//
		//   var task = Ti.App.Windows.BackgroundService.registerTimerTask("TitaniumWindows_Ti.BackgroundServiceTask", 15, false);
		// 
		//   // you can check if task is running in about 15 mininutes later...note that Windows usually does not run tasks on time though.
		//   Ti.API.info(Ti.App.Properties.getInt("TitaniumWindows_Ti.BackgroundServiceTask.count"));
		//
		//
		const auto deferral = taskInstance->GetDeferral();

		int count = 0;
		const auto settings = ApplicationData::Current->LocalSettings;
		const auto values = settings->Values;
		Platform::String^ key = "TitaniumWindows_Ti.BackgroundServiceTask.count";
		if (values->HasKey(key)) {
			count = safe_cast<IPropertyValue^>(values->Lookup(key))->GetInt32();
		}
		count++;
		settings->Values->Insert("TitaniumWindows_Ti.BackgroundServiceTask.count", dynamic_cast<PropertyValue^>(PropertyValue::CreateInt32(count)));

		deferral->Complete();
	}
}

namespace TitaniumWindows
{
	namespace App
	{
		namespace WindowsXaml 
		{
			std::atomic<std::uint32_t> BackgroundService::task_id_generator__;

			BackgroundService::BackgroundService(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Titanium.App.Windows.BackgroundService")
			{
				TITANIUM_LOG_DEBUG("BackgroundService::ctor Initialize");
			}

			BackgroundService::~BackgroundService() 
			{
				TITANIUM_LOG_DEBUG("BackgroundService::dtor");
				UnregisterTasks();
			}

			void BackgroundService::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
			{
				Titanium::Module::postCallAsConstructor(js_context, arguments);
				TITANIUM_LOG_DEBUG("BackgroundService::postCallAsConstructor");
			}

			void BackgroundService::JSExportInitialize() 
			{
				JSExport<BackgroundService>::SetClassVersion(1);
				JSExport<BackgroundService>::SetParent(JSExport<Titanium::Module>::Class());

				TITANIUM_ADD_FUNCTION(BackgroundService, registerTimerTask);
				TITANIUM_ADD_FUNCTION(BackgroundService, unregisterTask);
				TITANIUM_ADD_FUNCTION(BackgroundService, unregisterAllTasks);
			}

			std::shared_ptr<BackgroundServiceTask> BackgroundService::registerTimerTask(::Platform::String^ entryPoint, const std::uint32_t& freshnessTime, const bool& oneShot, IBackgroundCondition^ condition)
			{
				return registerTask(entryPoint, ref new TimeTrigger(freshnessTime, oneShot), condition);
			}

			std::shared_ptr<BackgroundServiceTask> BackgroundService::registerTask(::Platform::String^ entryPoint, IBackgroundTrigger^ trigger, IBackgroundCondition^ condition)
			{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
				BackgroundExecutionManager::RequestAccessAsync();
#endif
				const auto taskId   = task_id_generator__++;
				const auto taskName = Windows::ApplicationModel::Package::Current->Id->Name + "." + taskId;

				// Make sure to unregister all task which has same name
				// This could happen when last process doesn't unregister tasks properly.
				UnregisterTask(taskId);

				const auto builder = ref new BackgroundTaskBuilder();
				builder->Name = taskName;
				builder->TaskEntryPoint = entryPoint;
				builder->SetTrigger(trigger);

				if (condition != nullptr)
				{
					builder->AddCondition(condition);
					builder->CancelOnConditionLoss = true;
				}

				auto task = get_context().CreateObject(JSExport<BackgroundServiceTask>::Class()).CallAsConstructor().GetPrivate<BackgroundServiceTask>();
				task->construct(taskId, builder->Register());

				return task;
			}

			IBackgroundTaskRegistration^ BackgroundService::GetTask(const std::uint32_t& id) 
			{
				const auto taskName = Windows::ApplicationModel::Package::Current->Id->Name + "." + id;
				const auto iter = BackgroundTaskRegistration::AllTasks->First();
				auto hasCurrent = iter->HasCurrent;
				while (hasCurrent)
				{
					const auto cur = iter->Current->Value;
					if (cur->Name == taskName)
					{
						return cur;
					}
					hasCurrent = iter->MoveNext();
				}

				return nullptr;
			}

			void BackgroundService::UnregisterTask(const std::uint32_t& id)
			{
				const auto taskName = Windows::ApplicationModel::Package::Current->Id->Name + "." + id;
				const auto iter = BackgroundTaskRegistration::AllTasks->First();
				auto hasCurrent = iter->HasCurrent;
				while (hasCurrent)
				{
					const auto cur = iter->Current->Value;
					if (cur->Name == taskName)
					{
						cur->Unregister(true);
					}
					hasCurrent = iter->MoveNext();
				}
			}

			void BackgroundService::UnregisterTasks() 
			{
				const auto taskName = TitaniumWindows::Utility::ConvertString(Windows::ApplicationModel::Package::Current->Id->Name);
				const auto iter = BackgroundTaskRegistration::AllTasks->First();
				auto hasCurrent = iter->HasCurrent;
				while (hasCurrent)
				{
					const auto cur = iter->Current->Value;
					if (boost::starts_with(TitaniumWindows::Utility::ConvertString(cur->Name), taskName))
					{
						cur->Unregister(true);
					}
					hasCurrent = iter->MoveNext();
				}
			}

			TITANIUM_FUNCTION(BackgroundService, registerTimerTask)
			{
				ENSURE_STRING_AT_INDEX(entryPoint, 0);
				ENSURE_OPTIONAL_UINT_AT_INDEX(freshnessTime, 1, 15);
				ENSURE_OPTIONAL_BOOL_AT_INDEX(oneShot, 2, false);
				const auto task = registerTimerTask(TitaniumWindows::Utility::ConvertString(entryPoint), freshnessTime, oneShot);
				if (task) {
					return task->get_object();
				}
				return get_context().CreateNull();
			}

			TITANIUM_FUNCTION(BackgroundService, unregisterTask)
			{
				if (arguments.size() <= 0) {
					return get_context().CreateUndefined();
				}
				const auto _0 = arguments.at(0);

				if (_0.IsNumber()) {
					// unregister with task id
					UnregisterTask(static_cast<std::uint32_t>(_0));
				} else if (_0.IsObject()) {
					// unregister with task object
					const auto task = static_cast<JSObject>(_0).GetPrivate<BackgroundServiceTask>();
					if (task) {
						UnregisterTask(task->get_taskId());
					} else {
						TITANIUM_LOG_WARN("BackgroundService.unregisterTask: Not a task object");
					}
				}
				return get_context().CreateUndefined();
			}

			TITANIUM_FUNCTION(BackgroundService, unregisterAllTasks) 
			{
				UnregisterTasks();
				return get_context().CreateUndefined();
			}

		} // namespace WindowsXaml
	}  // namespace App
}  // namespace TitaniumWindows
