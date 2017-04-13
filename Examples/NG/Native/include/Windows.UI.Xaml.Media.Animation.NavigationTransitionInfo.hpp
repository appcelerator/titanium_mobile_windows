/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_MEDIA_ANIMATION_NAVIGATIONTRANSITIONINFO_HPP_
#define _WINDOWS_UI_XAML_MEDIA_ANIMATION_NAVIGATIONTRANSITIONINFO_HPP_

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
					namespace Animation
					{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT NavigationTransitionInfo : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<NavigationTransitionInfo>
		{

		public:


			NavigationTransitionInfo(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~NavigationTransitionInfo() = default;
			NavigationTransitionInfo(const NavigationTransitionInfo&) = default;
			NavigationTransitionInfo& operator=(const NavigationTransitionInfo&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			NavigationTransitionInfo(NavigationTransitionInfo&&)                 = default;
			NavigationTransitionInfo& operator=(NavigationTransitionInfo&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^ unwrapWindows_UI_Xaml_Media_Animation_NavigationTransitionInfo() const;
			void wrap(::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^ object);

		private:
			::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^ unwrap() const;

		};

					} // namespace Animation
				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_MEDIA_ANIMATION_NAVIGATIONTRANSITIONINFO_HPP_
