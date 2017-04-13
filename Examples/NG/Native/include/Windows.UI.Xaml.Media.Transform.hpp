/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Transform
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_TRANSFORM_HPP_
#define _WINDOWS_UI_XAML_MEDIA_TRANSFORM_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Media.GeneralTransform.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Transform : public ::Titanium::Windows::UI::Xaml::Media::GeneralTransform, public JSExport<Transform>
		{

		public:


			Transform(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Transform() = default;
			Transform(const Transform&) = default;
			Transform& operator=(const Transform&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Transform(Transform&&)                 = default;
			Transform& operator=(Transform&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::Transform^ unwrapWindows_UI_Xaml_Media_Transform() const;
			void wrap(::Windows::UI::Xaml::Media::Transform^ object);

		private:
			::Windows::UI::Xaml::Media::Transform^ unwrap() const;

		};

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_TRANSFORM_HPP_
