/**
 * Windows Native Wrapper for Windows.Foundation.AsyncActionCompletedHandler
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

		AsyncActionCompletedHandler::AsyncActionCompletedHandler(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("AsyncActionCompletedHandler::ctor");
		}

		void AsyncActionCompletedHandler::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("AsyncActionCompletedHandler::postCallAsConstructor ", this);

		}

		::Windows::Foundation::AsyncActionCompletedHandler^ AsyncActionCompletedHandler::unwrapWindows_Foundation_AsyncActionCompletedHandler() const
		{
			return dynamic_cast<::Windows::Foundation::AsyncActionCompletedHandler^>(wrapped__);
		}

		::Windows::Foundation::AsyncActionCompletedHandler^ AsyncActionCompletedHandler::unwrap() const
		{
			return unwrapWindows_Foundation_AsyncActionCompletedHandler();
		}

		void AsyncActionCompletedHandler::wrap(::Windows::Foundation::AsyncActionCompletedHandler^ object)
		{
			wrapped__ = object;
		}

		void AsyncActionCompletedHandler::JSExportInitialize()
		{
			JSExport<AsyncActionCompletedHandler>::SetClassVersion(1);
			JSExport<AsyncActionCompletedHandler>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_FUNCTION(AsyncActionCompletedHandler, Invoke);
		}

		TITANIUM_FUNCTION(AsyncActionCompletedHandler, Invoke)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_asyncInfo = static_cast<JSObject>(_0);
 
			auto wrapper_asyncInfo = object_asyncInfo.GetPrivate<Windows::Foundation::IAsyncAction>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto asyncInfo = wrapper_asyncInfo->unwrapWindows_Foundation_IAsyncAction();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto asyncStatus = static_cast<::Windows::Foundation::AsyncStatus>(static_cast<int32_t>(_1)); // TODO Look up enum in metadata to know what type it's value is? 

				unwrap()->Invoke(asyncInfo, asyncStatus);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched AsyncActionCompletedHandler::Invoke with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
