/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo.hpp"
#include "Titanium/detail/TiImpl.hpp"

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

		NavigationTransitionInfo::NavigationTransitionInfo(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("NavigationTransitionInfo::ctor");
		}

		void NavigationTransitionInfo::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("NavigationTransitionInfo::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^ NavigationTransitionInfo::unwrapWindows_UI_Xaml_Media_Animation_NavigationTransitionInfo() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^ NavigationTransitionInfo::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_Animation_NavigationTransitionInfo();
		}

		void NavigationTransitionInfo::wrap(::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^ object)
		{
			wrapped__ = object;
		}

		void NavigationTransitionInfo::JSExportInitialize()
		{
			JSExport<NavigationTransitionInfo>::SetClassVersion(1);
			JSExport<NavigationTransitionInfo>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

		}

					} // namespace Animation
				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
