/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.SolidColorBrush
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_SOLIDCOLORBRUSH_HPP_
#define _WINDOWS_UI_XAML_MEDIA_SOLIDCOLORBRUSH_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Media.Brush.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Media
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT SolidColorBrush : public ::Titanium::Windows::UI::Xaml::Media::Brush, public JSExport<SolidColorBrush>
		{

		public:
			TITANIUM_PROPERTY_DEF(Color);
			TITANIUM_PROPERTY_READONLY_DEF(ColorProperty);


			SolidColorBrush(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~SolidColorBrush() = default;
			SolidColorBrush(const SolidColorBrush&) = default;
			SolidColorBrush& operator=(const SolidColorBrush&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			SolidColorBrush(SolidColorBrush&&)                 = default;
			SolidColorBrush& operator=(SolidColorBrush&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::SolidColorBrush^ unwrapWindows_UI_Xaml_Media_SolidColorBrush() const;
			void wrap(::Windows::UI::Xaml::Media::SolidColorBrush^ object);

		private:
			::Windows::UI::Xaml::Media::SolidColorBrush^ unwrap() const;

		};

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_SOLIDCOLORBRUSH_HPP_
