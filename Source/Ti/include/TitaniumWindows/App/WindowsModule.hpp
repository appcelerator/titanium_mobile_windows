/**
* Ti.App.Windows module
*
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_APP_WINDOWSMODULE_HPP_
#define _TITANIUMWINDOWS_APP_WINDOWSMODULE_HPP_

#include "Titanium/Module.hpp"
#include "TitaniumWindows_Ti_EXPORT.h"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	namespace App
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.App.Windows implementation
		*/
		class TITANIUMWINDOWS_TI_EXPORT WindowsModule final : public Titanium::Module, public JSExport<WindowsModule>
		{

		public:
			WindowsModule(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~WindowsModule()                = default;
			WindowsModule(const WindowsModule&)            = default;
			WindowsModule& operator=(const WindowsModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WindowsModule(WindowsModule&&)                 = default;
			WindowsModule& operator=(WindowsModule&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(BackgroundService);
			TITANIUM_PROPERTY_READONLY_DEF(EXTENDED_EXECUTION_REASON_LOCATION_TRACKING);
			TITANIUM_PROPERTY_READONLY_DEF(EXTENDED_EXECUTION_REASON_SAVING_DATA);
			TITANIUM_PROPERTY_READONLY_DEF(EXTENDED_EXECUTION_REASON_UNSPECIFIED);
			TITANIUM_PROPERTY_READONLY_DEF(EXTENDED_EXECUTION_REVOKED_REASON_RESUMED);
			TITANIUM_PROPERTY_READONLY_DEF(EXTENDED_EXECUTION_REVOKED_REASON_SYSTEM_POLICY);
			TITANIUM_FUNCTION_DEF(requestExtendedExecution);
			TITANIUM_FUNCTION_DEF(closeExtendedExecution);

		private:
#if defined(IS_WINDOWS_10)
			Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionSession^ extendedExecutionSession__;
			Windows::Foundation::EventRegistrationToken extendedExecution_revoked_token__;

			void beginExtendedExecution(Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionReason, JSObject& result_callback, JSObject& revoked_callback);
			void endExtendedExecution();
			void clearExtendedExecution();
#endif
		};
	}  // namespace App
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_APP)WINDOWSMODULE_HPP_