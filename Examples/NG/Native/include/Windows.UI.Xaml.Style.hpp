/**
 * Windows Native Wrapper for Windows.UI.Xaml.Style
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_STYLE_HPP_
#define _WINDOWS_UI_XAML_STYLE_HPP_

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


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT Style : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<Style>
		{

		public:
			TITANIUM_PROPERTY_DEF(TargetType);
			TITANIUM_PROPERTY_DEF(BasedOn);
			TITANIUM_PROPERTY_READONLY_DEF(IsSealed);
			TITANIUM_PROPERTY_READONLY_DEF(Setters);

			TITANIUM_FUNCTION_DEF(Seal);

			Style(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Style() = default;
			Style(const Style&) = default;
			Style& operator=(const Style&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Style(Style&&)                 = default;
			Style& operator=(Style&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Style^ unwrapWindows_UI_Xaml_Style() const;
			void wrap(::Windows::UI::Xaml::Style^ object);

		private:
			::Windows::UI::Xaml::Style^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_STYLE_HPP_
