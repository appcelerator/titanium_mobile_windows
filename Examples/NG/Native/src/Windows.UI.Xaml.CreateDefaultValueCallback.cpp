/**
 * Windows Native Wrapper for Windows.UI.Xaml.CreateDefaultValueCallback
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.CreateDefaultValueCallback.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		CreateDefaultValueCallback::CreateDefaultValueCallback(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("CreateDefaultValueCallback::ctor");
		}

		void CreateDefaultValueCallback::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("CreateDefaultValueCallback::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::CreateDefaultValueCallback^ CreateDefaultValueCallback::unwrapWindows_UI_Xaml_CreateDefaultValueCallback() const
		{
			return dynamic_cast<::Windows::UI::Xaml::CreateDefaultValueCallback^>(wrapped__);
		}

		::Windows::UI::Xaml::CreateDefaultValueCallback^ CreateDefaultValueCallback::unwrap() const
		{
			return unwrapWindows_UI_Xaml_CreateDefaultValueCallback();
		}

		void CreateDefaultValueCallback::wrap(::Windows::UI::Xaml::CreateDefaultValueCallback^ object)
		{
			wrapped__ = object;
		}

		void CreateDefaultValueCallback::JSExportInitialize()
		{
			JSExport<CreateDefaultValueCallback>::SetClassVersion(1);
			JSExport<CreateDefaultValueCallback>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_FUNCTION(CreateDefaultValueCallback, Invoke);
		}

		TITANIUM_FUNCTION(CreateDefaultValueCallback, Invoke)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->Invoke();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched CreateDefaultValueCallback::Invoke with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
