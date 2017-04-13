/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Projection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_PROJECTION_HPP_
#define _WINDOWS_UI_XAML_MEDIA_PROJECTION_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Projection : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<Projection>
		{

		public:


			Projection(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Projection() = default;
			Projection(const Projection&) = default;
			Projection& operator=(const Projection&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Projection(Projection&&)                 = default;
			Projection& operator=(Projection&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::Projection^ unwrapWindows_UI_Xaml_Media_Projection() const;
			void wrap(::Windows::UI::Xaml::Media::Projection^ object);

		private:
			::Windows::UI::Xaml::Media::Projection^ unwrap() const;

		};

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_PROJECTION_HPP_
