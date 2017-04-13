/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.Panel
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_PANEL_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_PANEL_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.FrameworkElement.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Panel : public ::Titanium::Windows::UI::Xaml::FrameworkElement, public JSExport<Panel>
		{

		public:
			TITANIUM_PROPERTY_DEF(ChildrenTransitions);
			TITANIUM_PROPERTY_DEF(Background);
			TITANIUM_PROPERTY_READONLY_DEF(Children);
			TITANIUM_PROPERTY_READONLY_DEF(IsItemsHost);
			TITANIUM_PROPERTY_READONLY_DEF(BackgroundProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ChildrenTransitionsProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsItemsHostProperty);


			Panel(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Panel() = default;
			Panel(const Panel&) = default;
			Panel& operator=(const Panel&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Panel(Panel&&)                 = default;
			Panel& operator=(Panel&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::Panel^ unwrapWindows_UI_Xaml_Controls_Panel() const;
			void wrap(::Windows::UI::Xaml::Controls::Panel^ object);

		private:
			::Windows::UI::Xaml::Controls::Panel^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_PANEL_HPP_
