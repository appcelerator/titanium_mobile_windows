/**
 * Windows Native Wrapper for Windows.UI.Xaml.Navigation.PageStackEntry
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_NAVIGATION_PAGESTACKENTRY_HPP_
#define _WINDOWS_UI_XAML_NAVIGATION_PAGESTACKENTRY_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Navigation
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT PageStackEntry : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<PageStackEntry>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(NavigationTransitionInfo);
			TITANIUM_PROPERTY_READONLY_DEF(Parameter);
			TITANIUM_PROPERTY_READONLY_DEF(SourcePageType);
			TITANIUM_PROPERTY_READONLY_DEF(SourcePageTypeProperty);


			PageStackEntry(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~PageStackEntry() = default;
			PageStackEntry(const PageStackEntry&) = default;
			PageStackEntry& operator=(const PageStackEntry&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			PageStackEntry(PageStackEntry&&)                 = default;
			PageStackEntry& operator=(PageStackEntry&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Navigation::PageStackEntry^ unwrapWindows_UI_Xaml_Navigation_PageStackEntry() const;
			void wrap(::Windows::UI::Xaml::Navigation::PageStackEntry^ object);

		private:
			::Windows::UI::Xaml::Navigation::PageStackEntry^ unwrap() const;

		};

				} // namespace Navigation
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_NAVIGATION_PAGESTACKENTRY_HPP_
