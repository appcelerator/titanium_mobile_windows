/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.Page
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_PAGE_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_PAGE_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Controls.UserControl.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Page : public ::Titanium::Windows::UI::Xaml::Controls::UserControl, public JSExport<Page>
		{

		public:
			TITANIUM_PROPERTY_DEF(TopAppBar);
			TITANIUM_PROPERTY_DEF(NavigationCacheMode);
			TITANIUM_PROPERTY_DEF(BottomAppBar);
			TITANIUM_PROPERTY_READONLY_DEF(Frame);
			TITANIUM_PROPERTY_READONLY_DEF(BottomAppBarProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FrameProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TopAppBarProperty);


			Page(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Page() = default;
			Page(const Page&) = default;
			Page& operator=(const Page&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Page(Page&&)                 = default;
			Page& operator=(Page&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::Page^ unwrapWindows_UI_Xaml_Controls_Page() const;
			void wrap(::Windows::UI::Xaml::Controls::Page^ object);

		private:
			::Windows::UI::Xaml::Controls::Page^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_PAGE_HPP_
