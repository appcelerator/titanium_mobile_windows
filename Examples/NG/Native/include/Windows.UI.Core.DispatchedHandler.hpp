/**
 * Windows Native Wrapper for Windows.UI.Core.DispatchedHandler
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_CORE_DISPATCHEDHANDLER_HPP_
#define _WINDOWS_UI_CORE_DISPATCHEDHANDLER_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Platform.Object.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Core
			{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT DispatchedHandler : public ::Titanium::Platform::Object, public JSExport<DispatchedHandler>
		{

		public:

			TITANIUM_FUNCTION_DEF(Invoke);

			DispatchedHandler(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~DispatchedHandler() = default;
			DispatchedHandler(const DispatchedHandler&) = default;
			DispatchedHandler& operator=(const DispatchedHandler&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			DispatchedHandler(DispatchedHandler&&)                 = default;
			DispatchedHandler& operator=(DispatchedHandler&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Core::DispatchedHandler^ unwrapWindows_UI_Core_DispatchedHandler() const;
			void wrap(::Windows::UI::Core::DispatchedHandler^ object);

		private:
			::Windows::UI::Core::DispatchedHandler^ unwrap() const;

		};

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_CORE_DISPATCHEDHANDLER_HPP_
