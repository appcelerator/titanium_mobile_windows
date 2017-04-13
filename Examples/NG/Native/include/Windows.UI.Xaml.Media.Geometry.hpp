/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Geometry
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_GEOMETRY_HPP_
#define _WINDOWS_UI_XAML_MEDIA_GEOMETRY_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Geometry : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<Geometry>
		{

		public:
			TITANIUM_PROPERTY_DEF(Transform);
			TITANIUM_PROPERTY_READONLY_DEF(Bounds);
			TITANIUM_PROPERTY_READONLY_DEF(Empty);
			TITANIUM_PROPERTY_READONLY_DEF(StandardFlatteningTolerance);
			TITANIUM_PROPERTY_READONLY_DEF(TransformProperty);


			Geometry(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Geometry() = default;
			Geometry(const Geometry&) = default;
			Geometry& operator=(const Geometry&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Geometry(Geometry&&)                 = default;
			Geometry& operator=(Geometry&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::Geometry^ unwrapWindows_UI_Xaml_Media_Geometry() const;
			void wrap(::Windows::UI::Xaml::Media::Geometry^ object);

		private:
			::Windows::UI::Xaml::Media::Geometry^ unwrap() const;

		};

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_GEOMETRY_HPP_
