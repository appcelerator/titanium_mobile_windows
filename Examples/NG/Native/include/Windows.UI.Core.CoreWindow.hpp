/**
 * Windows Native Wrapper for Windows.UI.Core.CoreWindow
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_CORE_COREWINDOW_HPP_
#define _WINDOWS_UI_CORE_COREWINDOW_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT CoreWindow : public ::Titanium::Platform::Object, public JSExport<CoreWindow>
		{

		public:
			TITANIUM_PROPERTY_DEF(PointerCursor);
			TITANIUM_PROPERTY_DEF(IsInputEnabled);
			TITANIUM_PROPERTY_DEF(FlowDirection);
			TITANIUM_PROPERTY_READONLY_DEF(AutomationHostProvider);
			TITANIUM_PROPERTY_READONLY_DEF(Bounds);
			TITANIUM_PROPERTY_READONLY_DEF(CustomProperties);
			TITANIUM_PROPERTY_READONLY_DEF(Dispatcher);
			TITANIUM_PROPERTY_READONLY_DEF(PointerPosition);
			TITANIUM_PROPERTY_READONLY_DEF(Visible);

			TITANIUM_FUNCTION_DEF(Activate);
			TITANIUM_FUNCTION_DEF(Close);
			TITANIUM_FUNCTION_DEF(GetAsyncKeyState);
			TITANIUM_FUNCTION_DEF(GetKeyState);
			TITANIUM_FUNCTION_DEF(ReleasePointerCapture);
			TITANIUM_FUNCTION_DEF(SetPointerCapture);
			TITANIUM_FUNCTION_DEF(GetForCurrentThread);

			CoreWindow(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~CoreWindow() = default;
			CoreWindow(const CoreWindow&) = default;
			CoreWindow& operator=(const CoreWindow&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			CoreWindow(CoreWindow&&)                 = default;
			CoreWindow& operator=(CoreWindow&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Core::CoreWindow^ unwrapWindows_UI_Core_CoreWindow() const;
			void wrap(::Windows::UI::Core::CoreWindow^ object);

		private:
			::Windows::UI::Core::CoreWindow^ unwrap() const;

		};

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_CORE_COREWINDOW_HPP_
