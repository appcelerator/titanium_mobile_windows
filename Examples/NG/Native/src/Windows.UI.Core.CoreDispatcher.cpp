/**
 * Windows Native Wrapper for Windows.UI.Core.CoreDispatcher
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.Foundation.IAsyncAction.hpp"
#include "Windows.UI.Core.CoreDispatcher.hpp"
#include "Windows.UI.Core.DispatchedHandler.hpp"
#include "Windows.UI.Core.IdleDispatchedHandler.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Core
			{

		CoreDispatcher::CoreDispatcher(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("CoreDispatcher::ctor");
		}

		void CoreDispatcher::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("CoreDispatcher::postCallAsConstructor ", this);

		}

		::Windows::UI::Core::CoreDispatcher^ CoreDispatcher::unwrapWindows_UI_Core_CoreDispatcher() const
		{
			return dynamic_cast<::Windows::UI::Core::CoreDispatcher^>(wrapped__);
		}

		::Windows::UI::Core::CoreDispatcher^ CoreDispatcher::unwrap() const
		{
			return unwrapWindows_UI_Core_CoreDispatcher();
		}

		void CoreDispatcher::wrap(::Windows::UI::Core::CoreDispatcher^ object)
		{
			wrapped__ = object;
		}

		void CoreDispatcher::JSExportInitialize()
		{
			JSExport<CoreDispatcher>::SetClassVersion(1);
			JSExport<CoreDispatcher>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY(CoreDispatcher, CurrentPriority);
			TITANIUM_ADD_PROPERTY_READONLY(CoreDispatcher, HasThreadAccess);
			TITANIUM_ADD_FUNCTION(CoreDispatcher, ProcessEvents);
			TITANIUM_ADD_FUNCTION(CoreDispatcher, RunAsync);
			TITANIUM_ADD_FUNCTION(CoreDispatcher, RunIdleAsync);
			TITANIUM_ADD_FUNCTION(CoreDispatcher, ShouldYield);
			TITANIUM_ADD_FUNCTION(CoreDispatcher, StopProcessEvents);
		}

		TITANIUM_PROPERTY_SETTER(CoreDispatcher, CurrentPriority)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<::Windows::UI::Core::CoreDispatcherPriority>(static_cast<int32_t>(argument)); // TODO Look up enum in metadata to know what type it's value is? 

			unwrap()->CurrentPriority = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(CoreDispatcher, CurrentPriority)
		{
			auto value = unwrap()->CurrentPriority;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_GETTER(CoreDispatcher, HasThreadAccess)
		{
			auto value = unwrap()->HasThreadAccess;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_FUNCTION(CoreDispatcher, ProcessEvents)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto options = static_cast<::Windows::UI::Core::CoreProcessEventsOption>(static_cast<int32_t>(_0)); // TODO Look up enum in metadata to know what type it's value is? 

				unwrap()->ProcessEvents(options);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched CoreDispatcher::ProcessEvents with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(CoreDispatcher, RunAsync)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto priority = static_cast<::Windows::UI::Core::CoreDispatcherPriority>(static_cast<int32_t>(_0)); // TODO Look up enum in metadata to know what type it's value is? 

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_agileCallback = static_cast<JSObject>(_1);
 
			auto wrapper_agileCallback = object_agileCallback.GetPrivate<Windows::UI::Core::DispatchedHandler>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto agileCallback = wrapper_agileCallback->unwrapWindows_UI_Core_DispatchedHandler();

				auto method_result = unwrap()->RunAsync(priority, agileCallback);

			auto result = context.CreateObject(JSExport<Windows::Foundation::IAsyncAction>::Class());
			auto result_wrapper = result.GetPrivate<Windows::Foundation::IAsyncAction>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched CoreDispatcher::RunAsync with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(CoreDispatcher, RunIdleAsync)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_agileCallback = static_cast<JSObject>(_0);
 
			auto wrapper_agileCallback = object_agileCallback.GetPrivate<Windows::UI::Core::IdleDispatchedHandler>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto agileCallback = wrapper_agileCallback->unwrapWindows_UI_Core_IdleDispatchedHandler();

				auto method_result = unwrap()->RunIdleAsync(agileCallback);

			auto result = context.CreateObject(JSExport<Windows::Foundation::IAsyncAction>::Class());
			auto result_wrapper = result.GetPrivate<Windows::Foundation::IAsyncAction>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched CoreDispatcher::RunIdleAsync with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(CoreDispatcher, ShouldYield)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto priority = static_cast<::Windows::UI::Core::CoreDispatcherPriority>(static_cast<int32_t>(_0)); // TODO Look up enum in metadata to know what type it's value is? 

				auto method_result = unwrap()->ShouldYield(priority);
 
			auto result = context.CreateBoolean(method_result); 

				return result;
			}

			if (arguments.size() == 0) {
				auto method_result = unwrap()->ShouldYield();
 
			auto result = context.CreateBoolean(method_result); 

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched CoreDispatcher::ShouldYield with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(CoreDispatcher, StopProcessEvents)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->StopProcessEvents();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched CoreDispatcher::StopProcessEvents with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
