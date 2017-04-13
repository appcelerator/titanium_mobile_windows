/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.FontFamily
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_FONTFAMILY_HPP_
#define _WINDOWS_UI_XAML_MEDIA_FONTFAMILY_HPP_

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
			namespace Xaml
			{
				namespace Media
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT FontFamily : public ::Titanium::Platform::Object, public JSExport<FontFamily>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Source);


			FontFamily(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~FontFamily() = default;
			FontFamily(const FontFamily&) = default;
			FontFamily& operator=(const FontFamily&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			FontFamily(FontFamily&&)                 = default;
			FontFamily& operator=(FontFamily&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::FontFamily^ unwrapWindows_UI_Xaml_Media_FontFamily() const;
			void wrap(::Windows::UI::Xaml::Media::FontFamily^ object);

		private:
			::Windows::UI::Xaml::Media::FontFamily^ unwrap() const;

		};

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_FONTFAMILY_HPP_
