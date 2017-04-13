/**
 * Windows Native Wrapper for Windows.UI.Core.DispatchedHandler
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Core.DispatchedHandler.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Core
			{

		DispatchedHandler::DispatchedHandler(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("DispatchedHandler::ctor");
		}

		void DispatchedHandler::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("DispatchedHandler::postCallAsConstructor ", this);

		}

		::Windows::UI::Core::DispatchedHandler^ DispatchedHandler::unwrapWindows_UI_Core_DispatchedHandler() const
		{
			return dynamic_cast<::Windows::UI::Core::DispatchedHandler^>(wrapped__);
		}

		::Windows::UI::Core::DispatchedHandler^ DispatchedHandler::unwrap() const
		{
			return unwrapWindows_UI_Core_DispatchedHandler();
		}

		void DispatchedHandler::wrap(::Windows::UI::Core::DispatchedHandler^ object)
		{
			wrapped__ = object;
		}

		void DispatchedHandler::JSExportInitialize()
		{
			JSExport<DispatchedHandler>::SetClassVersion(1);
			JSExport<DispatchedHandler>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_FUNCTION(DispatchedHandler, Invoke);
		}

		TITANIUM_FUNCTION(DispatchedHandler, Invoke)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Invoke();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DispatchedHandler::Invoke with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
