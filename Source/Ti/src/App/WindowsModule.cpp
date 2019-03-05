/**
* Ti.App.Windows module
*
* Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/App/WindowsModule.hpp"
#include "TitaniumWindows/App/BackgroundService.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <ppltasks.h>

#define CREATE_TITANIUM_APP_WINDOWS(NAME) \
  JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue App_property = Titanium.GetProperty("App"); \
  TITANIUM_ASSERT(App_property.IsObject()); \
  JSObject App = static_cast<JSObject>(App_property); \
  JSValue App_WIN_property = App.GetProperty("Windows"); \
  TITANIUM_ASSERT(App_WIN_property.IsObject()); \
  JSObject App_WIN = static_cast<JSObject>(App_WIN_property); \
  JSValue NAME##_property = App_WIN.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  JSObject NAME = static_cast<JSObject>(NAME##_property); \
  auto NAME##_obj = NAME.CallAsConstructor(parameters); \
  applyProperties(parameters, NAME##_obj); \
  return NAME##_obj;

namespace TitaniumWindows
{
	namespace App
	{
		using namespace ::Windows::UI::Xaml;

		WindowsModule::WindowsModule(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Module(js_context)
		{
			TITANIUM_LOG_DEBUG("App::WindowsModule::ctor Initialize");
		}

		void WindowsModule::JSExportInitialize() 
		{
			JSExport<WindowsModule>::SetClassVersion(1);
			JSExport<WindowsModule>::SetParent(JSExport<Titanium::Module>::Class());
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, BackgroundService);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, EXTENDED_EXECUTION_REASON_LOCATION_TRACKING);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, EXTENDED_EXECUTION_REASON_SAVING_DATA);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, EXTENDED_EXECUTION_REASON_UNSPECIFIED);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, EXTENDED_EXECUTION_REVOKED_REASON_RESUMED);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, EXTENDED_EXECUTION_REVOKED_REASON_SYSTEM_POLICY);
			TITANIUM_ADD_FUNCTION(WindowsModule, requestExtendedExecution);
			TITANIUM_ADD_FUNCTION(WindowsModule, closeExtendedExecution);
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, BackgroundService)
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::App::WindowsXaml::BackgroundService>::Class());
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, EXTENDED_EXECUTION_REASON_UNSPECIFIED)
		{
#if defined(IS_WINDOWS_10)
			return get_context().CreateNumber(static_cast<std::uint32_t>(Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionReason::Unspecified));
#else
			return get_context().CreateNumber(0);
#endif
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, EXTENDED_EXECUTION_REASON_LOCATION_TRACKING)
		{
#if defined(IS_WINDOWS_10)
			return get_context().CreateNumber(static_cast<std::uint32_t>(Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionReason::LocationTracking));
#else
			return get_context().CreateNumber(1);
#endif
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, EXTENDED_EXECUTION_REASON_SAVING_DATA)
		{
#if defined(IS_WINDOWS_10)
			return get_context().CreateNumber(static_cast<std::uint32_t>(Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionReason::SavingData));
#else
			return get_context().CreateNumber(2);
#endif
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, EXTENDED_EXECUTION_REVOKED_REASON_RESUMED)
		{
#if defined(IS_WINDOWS_10)
			return get_context().CreateNumber(static_cast<std::uint32_t>(Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionRevokedReason::Resumed));
#else
			return get_context().CreateNumber(0);
#endif
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, EXTENDED_EXECUTION_REVOKED_REASON_SYSTEM_POLICY)
		{
#if defined(IS_WINDOWS_10)
			return get_context().CreateNumber(static_cast<std::uint32_t>(Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionRevokedReason::SystemPolicy));
#else
			return get_context().CreateNumber(1);
#endif
		}

		TITANIUM_FUNCTION(WindowsModule, requestExtendedExecution)
		{
#if defined(IS_WINDOWS_10)
			using namespace Windows::ApplicationModel::ExtendedExecution;

			ENSURE_OPTIONAL_OBJECT_AT_INDEX(extendedExecutionArgs, 0);
			auto reason = ExtendedExecutionReason::Unspecified;
			if (extendedExecutionArgs.HasProperty("reason")) {
				reason = static_cast<ExtendedExecutionReason>(static_cast<std::uint32_t>(extendedExecutionArgs.GetProperty("reason")));
			}
			auto result_callback = get_context().CreateObject();
			if (extendedExecutionArgs.HasProperty("result")) {
				result_callback = static_cast<JSObject>(extendedExecutionArgs.GetProperty("result"));
			}
			auto revoked_callback = get_context().CreateObject();
			if (extendedExecutionArgs.HasProperty("revoked")) {
				revoked_callback = static_cast<JSObject>(extendedExecutionArgs.GetProperty("revoked"));
			}

			beginExtendedExecution(reason, result_callback, revoked_callback);
#endif
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WindowsModule, closeExtendedExecution)
		{
#if defined(IS_WINDOWS_10)
			endExtendedExecution();
#endif
			return get_context().CreateUndefined();
		}

#if defined(IS_WINDOWS_10)
		void WindowsModule::beginExtendedExecution(Windows::ApplicationModel::ExtendedExecution::ExtendedExecutionReason reason, JSObject& result_callback, JSObject& revoked_callback)
		{
			using namespace ::Windows::ApplicationModel::ExtendedExecution;

			clearExtendedExecution();

			auto session = ref new ExtendedExecutionSession();
			session->Reason = reason;

			extendedExecution_revoked_token__ = session->Revoked += 
				ref new Windows::Foundation::TypedEventHandler<Platform::Object^, ExtendedExecutionRevokedEventArgs^>
					([this, revoked_callback](Platform::Object^, ExtendedExecutionRevokedEventArgs^ e) {
				TITANIUM_EXCEPTION_CATCH_START {
					endExtendedExecution();
					if (revoked_callback.IsFunction()) {
						const std::vector<JSValue> args = {
							get_context().CreateNumber(static_cast<std::uint32_t>(e->Reason))
						};
						static_cast<JSObject>(revoked_callback)(args, get_object());
					}
				} TITANIUM_EXCEPTION_CATCH_END
			});

			concurrency::create_task(session->RequestExtensionAsync()).then([this, result_callback](ExtendedExecutionResult result) {
				TITANIUM_EXCEPTION_CATCH_START {
					TITANIUM_LOG_DEBUG("ExtendedExecutionSession has been ", (result == ExtendedExecutionResult::Allowed ? "allowed" : "denied"));
					if (result_callback.IsFunction()) {
						const std::vector<JSValue> args = {
							get_context().CreateBoolean(result == ExtendedExecutionResult::Allowed)
						};
						static_cast<JSObject>(result_callback)(args, get_object());
					}
				} TITANIUM_EXCEPTION_CATCH_END
			});

			extendedExecutionSession__ = session;
		}

		void WindowsModule::endExtendedExecution()
		{
			clearExtendedExecution();
		}

		void WindowsModule::clearExtendedExecution()
		{
			if (extendedExecutionSession__) {
				extendedExecutionSession__->Revoked -= extendedExecution_revoked_token__;
				delete extendedExecutionSession__; // Do we usually do this? Added because this is there in the sample code
				extendedExecutionSession__ = nullptr;
				TITANIUM_LOG_DEBUG("ExtendedExecutionSession has ended");
			}
		}
#endif
	}  // namespace UI
}  // namespace TitaniumWindows
