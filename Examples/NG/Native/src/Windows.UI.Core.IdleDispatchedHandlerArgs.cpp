/**
 * Windows Native Wrapper for Windows.UI.Core.IdleDispatchedHandlerArgs
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Core.IdleDispatchedHandlerArgs.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Core
			{

		IdleDispatchedHandlerArgs::IdleDispatchedHandlerArgs(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("IdleDispatchedHandlerArgs::ctor");
		}

		void IdleDispatchedHandlerArgs::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("IdleDispatchedHandlerArgs::postCallAsConstructor ", this);

		}

		::Windows::UI::Core::IdleDispatchedHandlerArgs^ IdleDispatchedHandlerArgs::unwrapWindows_UI_Core_IdleDispatchedHandlerArgs() const
		{
			return dynamic_cast<::Windows::UI::Core::IdleDispatchedHandlerArgs^>(wrapped__);
		}

		::Windows::UI::Core::IdleDispatchedHandlerArgs^ IdleDispatchedHandlerArgs::unwrap() const
		{
			return unwrapWindows_UI_Core_IdleDispatchedHandlerArgs();
		}

		void IdleDispatchedHandlerArgs::wrap(::Windows::UI::Core::IdleDispatchedHandlerArgs^ object)
		{
			wrapped__ = object;
		}

		void IdleDispatchedHandlerArgs::JSExportInitialize()
		{
			JSExport<IdleDispatchedHandlerArgs>::SetClassVersion(1);
			JSExport<IdleDispatchedHandlerArgs>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(IdleDispatchedHandlerArgs, IsDispatcherIdle);
		}

		TITANIUM_PROPERTY_GETTER(IdleDispatchedHandlerArgs, IsDispatcherIdle)
		{
			auto value = unwrap()->IsDispatcherIdle;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
