/**
 * Windows Native Wrapper for Windows.UI.Xaml.FrameworkElement
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_FRAMEWORKELEMENT_HPP_
#define _WINDOWS_UI_XAML_FRAMEWORKELEMENT_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.UIElement.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT FrameworkElement : public ::Titanium::Windows::UI::Xaml::UIElement, public JSExport<FrameworkElement>
		{

		public:
			TITANIUM_PROPERTY_DEF(Language);
			TITANIUM_PROPERTY_DEF(HorizontalAlignment);
			TITANIUM_PROPERTY_DEF(Height);
			TITANIUM_PROPERTY_DEF(MaxWidth);
			TITANIUM_PROPERTY_DEF(FlowDirection);
			TITANIUM_PROPERTY_DEF(DataContext);
			TITANIUM_PROPERTY_DEF(MaxHeight);
			TITANIUM_PROPERTY_DEF(Name);
			TITANIUM_PROPERTY_DEF(Width);
			TITANIUM_PROPERTY_DEF(VerticalAlignment);
			TITANIUM_PROPERTY_DEF(Tag);
			TITANIUM_PROPERTY_DEF(Style);
			TITANIUM_PROPERTY_DEF(Resources);
			TITANIUM_PROPERTY_DEF(Margin);
			TITANIUM_PROPERTY_DEF(MinWidth);
			TITANIUM_PROPERTY_DEF(MinHeight);
			TITANIUM_PROPERTY_READONLY_DEF(ActualHeight);
			TITANIUM_PROPERTY_READONLY_DEF(ActualWidth);
			TITANIUM_PROPERTY_READONLY_DEF(BaseUri);
			TITANIUM_PROPERTY_READONLY_DEF(Parent);
			TITANIUM_PROPERTY_READONLY_DEF(Triggers);
			TITANIUM_PROPERTY_DEF(RequestedTheme);
			TITANIUM_PROPERTY_READONLY_DEF(RequestedThemeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ActualHeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ActualWidthProperty);
			TITANIUM_PROPERTY_READONLY_DEF(DataContextProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FlowDirectionProperty);
			TITANIUM_PROPERTY_READONLY_DEF(HeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(HorizontalAlignmentProperty);
			TITANIUM_PROPERTY_READONLY_DEF(LanguageProperty);
			TITANIUM_PROPERTY_READONLY_DEF(MarginProperty);
			TITANIUM_PROPERTY_READONLY_DEF(MaxHeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(MaxWidthProperty);
			TITANIUM_PROPERTY_READONLY_DEF(MinHeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(MinWidthProperty);
			TITANIUM_PROPERTY_READONLY_DEF(NameProperty);
			TITANIUM_PROPERTY_READONLY_DEF(StyleProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TagProperty);
			TITANIUM_PROPERTY_READONLY_DEF(VerticalAlignmentProperty);
			TITANIUM_PROPERTY_READONLY_DEF(WidthProperty);

			TITANIUM_FUNCTION_DEF(FindName);
			TITANIUM_FUNCTION_DEF(SetBinding);
			TITANIUM_FUNCTION_DEF(GetBindingExpression);

			FrameworkElement(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~FrameworkElement() = default;
			FrameworkElement(const FrameworkElement&) = default;
			FrameworkElement& operator=(const FrameworkElement&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			FrameworkElement(FrameworkElement&&)                 = default;
			FrameworkElement& operator=(FrameworkElement&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::FrameworkElement^ unwrapWindows_UI_Xaml_FrameworkElement() const;
			void wrap(::Windows::UI::Xaml::FrameworkElement^ object);

		private:
			::Windows::UI::Xaml::FrameworkElement^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_FRAMEWORKELEMENT_HPP_
