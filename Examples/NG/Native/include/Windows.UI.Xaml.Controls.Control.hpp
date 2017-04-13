/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.Control
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_CONTROL_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_CONTROL_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Control : public ::Titanium::Windows::UI::Xaml::FrameworkElement, public JSExport<Control>
		{

		public:
			TITANIUM_PROPERTY_DEF(FontStyle);
			TITANIUM_PROPERTY_DEF(FontStretch);
			TITANIUM_PROPERTY_DEF(FontSize);
			TITANIUM_PROPERTY_DEF(FontFamily);
			TITANIUM_PROPERTY_DEF(FontWeight);
			TITANIUM_PROPERTY_DEF(CharacterSpacing);
			TITANIUM_PROPERTY_DEF(BorderThickness);
			TITANIUM_PROPERTY_DEF(BorderBrush);
			TITANIUM_PROPERTY_DEF(Background);
			TITANIUM_PROPERTY_DEF(VerticalContentAlignment);
			TITANIUM_PROPERTY_DEF(Template);
			TITANIUM_PROPERTY_DEF(TabNavigation);
			TITANIUM_PROPERTY_DEF(TabIndex);
			TITANIUM_PROPERTY_DEF(Padding);
			TITANIUM_PROPERTY_DEF(IsTabStop);
			TITANIUM_PROPERTY_DEF(IsEnabled);
			TITANIUM_PROPERTY_DEF(HorizontalContentAlignment);
			TITANIUM_PROPERTY_DEF(Foreground);
			TITANIUM_PROPERTY_READONLY_DEF(FocusState);
			TITANIUM_PROPERTY_DEF(DefaultStyleKey);
			TITANIUM_PROPERTY_READONLY_DEF(BackgroundProperty);
			TITANIUM_PROPERTY_READONLY_DEF(BorderBrushProperty);
			TITANIUM_PROPERTY_READONLY_DEF(BorderThicknessProperty);
			TITANIUM_PROPERTY_READONLY_DEF(CharacterSpacingProperty);
			TITANIUM_PROPERTY_READONLY_DEF(DefaultStyleKeyProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FocusStateProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontFamilyProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontSizeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontStretchProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontStyleProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontWeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ForegroundProperty);
			TITANIUM_PROPERTY_READONLY_DEF(HorizontalContentAlignmentProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsEnabledProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsTabStopProperty);
			TITANIUM_PROPERTY_READONLY_DEF(PaddingProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TabIndexProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TabNavigationProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TemplateProperty);
			TITANIUM_PROPERTY_READONLY_DEF(VerticalContentAlignmentProperty);

			TITANIUM_FUNCTION_DEF(ApplyTemplate);
			TITANIUM_FUNCTION_DEF(Focus);

			Control(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Control() = default;
			Control(const Control&) = default;
			Control& operator=(const Control&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Control(Control&&)                 = default;
			Control& operator=(Control&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::Control^ unwrapWindows_UI_Xaml_Controls_Control() const;
			void wrap(::Windows::UI::Xaml::Controls::Control^ object);

		private:
			::Windows::UI::Xaml::Controls::Control^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_CONTROL_HPP_
