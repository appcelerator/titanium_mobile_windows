/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.AppBar
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_APPBAR_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_APPBAR_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Controls.ContentControl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Controls
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT AppBar : public ::Titanium::Windows::UI::Xaml::Controls::ContentControl, public JSExport<AppBar>
		{

		public:
			TITANIUM_PROPERTY_DEF(IsSticky);
			TITANIUM_PROPERTY_DEF(IsOpen);
			TITANIUM_PROPERTY_READONLY_DEF(IsOpenProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsStickyProperty);


			AppBar(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~AppBar() = default;
			AppBar(const AppBar&) = default;
			AppBar& operator=(const AppBar&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			AppBar(AppBar&&)                 = default;
			AppBar& operator=(AppBar&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::AppBar^ unwrapWindows_UI_Xaml_Controls_AppBar() const;
			void wrap(::Windows::UI::Xaml::Controls::AppBar^ object);

		private:
			::Windows::UI::Xaml::Controls::AppBar^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_APPBAR_HPP_
