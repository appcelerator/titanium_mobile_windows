/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Brush
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_BRUSH_HPP_
#define _WINDOWS_UI_XAML_MEDIA_BRUSH_HPP_

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
				namespace Media
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT Brush : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<Brush>
		{

		public:
			TITANIUM_PROPERTY_DEF(Transform);
			TITANIUM_PROPERTY_DEF(RelativeTransform);
			TITANIUM_PROPERTY_DEF(Opacity);
			TITANIUM_PROPERTY_READONLY_DEF(OpacityProperty);
			TITANIUM_PROPERTY_READONLY_DEF(RelativeTransformProperty);
			TITANIUM_PROPERTY_READONLY_DEF(TransformProperty);


			Brush(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Brush() = default;
			Brush(const Brush&) = default;
			Brush& operator=(const Brush&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Brush(Brush&&)                 = default;
			Brush& operator=(Brush&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::Brush^ unwrapWindows_UI_Xaml_Media_Brush() const;
			void wrap(::Windows::UI::Xaml::Media::Brush^ object);

		private:
			::Windows::UI::Xaml::Media::Brush^ unwrap() const;

		};

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_BRUSH_HPP_
