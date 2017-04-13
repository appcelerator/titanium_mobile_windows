/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.GeneralTransform
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_GENERALTRANSFORM_HPP_
#define _WINDOWS_UI_XAML_MEDIA_GENERALTRANSFORM_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT GeneralTransform : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<GeneralTransform>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Inverse);
			TITANIUM_PROPERTY_READONLY_DEF(InverseCore);

			TITANIUM_FUNCTION_DEF(TransformPoint);
			TITANIUM_FUNCTION_DEF(TryTransform);
			TITANIUM_FUNCTION_DEF(TransformBounds);

			GeneralTransform(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~GeneralTransform() = default;
			GeneralTransform(const GeneralTransform&) = default;
			GeneralTransform& operator=(const GeneralTransform&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			GeneralTransform(GeneralTransform&&)                 = default;
			GeneralTransform& operator=(GeneralTransform&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::GeneralTransform^ unwrapWindows_UI_Xaml_Media_GeneralTransform() const;
			void wrap(::Windows::UI::Xaml::Media::GeneralTransform^ object);

		private:
			::Windows::UI::Xaml::Media::GeneralTransform^ unwrap() const;

		};

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_GENERALTRANSFORM_HPP_
