/**
 * Windows Native Wrapper for Windows.Foundation.IAsyncAction
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.Foundation.AsyncActionCompletedHandler.hpp"
#include "Windows.Foundation.IAsyncAction.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace Foundation
		{

		IAsyncAction::IAsyncAction(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("IAsyncAction::ctor");
		}

		void IAsyncAction::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("IAsyncAction::postCallAsConstructor ", this);

		}

		::Windows::Foundation::IAsyncAction^ IAsyncAction::unwrapWindows_Foundation_IAsyncAction() const
		{
			return dynamic_cast<::Windows::Foundation::IAsyncAction^>(wrapped__);
		}

		::Windows::Foundation::IAsyncAction^ IAsyncAction::unwrap() const
		{
			return unwrapWindows_Foundation_IAsyncAction();
		}

		void IAsyncAction::wrap(::Windows::Foundation::IAsyncAction^ object)
		{
			wrapped__ = object;
		}

		void IAsyncAction::JSExportInitialize()
		{
			JSExport<IAsyncAction>::SetClassVersion(1);
			JSExport<IAsyncAction>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY(IAsyncAction, Completed);
			TITANIUM_ADD_FUNCTION(IAsyncAction, GetResults);
		}

		TITANIUM_PROPERTY_SETTER(IAsyncAction, Completed)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::Foundation::AsyncActionCompletedHandler>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_Foundation_AsyncActionCompletedHandler();

			unwrap()->Completed = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(IAsyncAction, Completed)
		{
			auto value = unwrap()->Completed;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::Foundation::AsyncActionCompletedHandler>::Class());
			auto result_wrapper = result.GetPrivate<Windows::Foundation::AsyncActionCompletedHandler>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(IAsyncAction, GetResults)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->GetResults();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched IAsyncAction::GetResults with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
