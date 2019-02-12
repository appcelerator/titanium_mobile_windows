/**
* Ti.App.Windows.BackgroundServiceTask
*
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_APP_WINDOWS_BACKGROUNDSERVICETASK_HPP_
#define _TITANIUMWINDOWS_APP_WINDOWS_BACKGROUNDSERVICETASK_HPP_

#include "TitaniumWindows_Ti_EXPORT.h"
#include "Titanium/Module.hpp"

using namespace Windows::ApplicationModel::Background;
using namespace HAL;

namespace TitaniumWindows
{
	namespace App
	{
		// Use WindowsXaml namespace instead of "Windows"
		// because it screws up entire namespace in Xaml...
		namespace WindowsXaml
		{
			/*!
			  @class BackgroundServiceTask
			  @discussion This is the Titanium.App.Windows.BackgroundServiceTask implementation
			      This class holds task id which can be used to query BackgroundTaskRegistration.
			      Note that this class doesn't hold reference to the task (BackgroundTaskRegistration) intentionally
			      because Windows itself should manage life-cycle of the task and we don't want to keep reference to it.
			*/
			class TITANIUMWINDOWS_TI_EXPORT BackgroundServiceTask final : public Titanium::Module, public JSExport<BackgroundServiceTask>
			{

			public:
				BackgroundServiceTask(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~BackgroundServiceTask();
				BackgroundServiceTask(const BackgroundServiceTask&)            = default;
				BackgroundServiceTask& operator=(const BackgroundServiceTask&) = default;
	#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				BackgroundServiceTask(BackgroundServiceTask&&)                 = default;
				BackgroundServiceTask& operator=(BackgroundServiceTask&&)      = default;
	#endif
				static void JSExportInitialize();
				virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

				void construct(const std::uint32_t& id, BackgroundTaskRegistration^ registration);
				void unregister();

				/*!
				  @property
				  @abstract taskId
				  @discussiona taskId that is associated with this task. Read-Only.
				*/
				TITANIUM_PROPERTY_IMPL_READONLY_DEF(std::uint32_t, taskId);
				TITANIUM_PROPERTY_READONLY_DEF(taskId);

				/*!
				  method
				  @abstract unregister
				  @discussiona Unregisters this background task.
				*/
				TITANIUM_FUNCTION_DEF(unregister);

			protected:
#pragma warning(push)
#pragma warning(disable : 4251)
				std::uint32_t taskId__{ 0 };
#pragma warning(pop)
			};
		} // namespace WindowsXaml
	}  // namespace App
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_APP_WINDOWS_BACKGROUNDSERVICETASK_HPP_