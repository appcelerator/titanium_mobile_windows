/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Animation.Transition
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.Media.Animation.Transition.hpp"
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

		Transition::Transition(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("Transition::ctor");
		}

		void Transition::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Transition::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Media::Animation::Transition^ Transition::unwrapWindows_UI_Xaml_Media_Animation_Transition() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::Animation::Transition^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::Animation::Transition^ Transition::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_Animation_Transition();
		}

		void Transition::wrap(::Windows::UI::Xaml::Media::Animation::Transition^ object)
		{
			wrapped__ = object;
		}

		void Transition::JSExportInitialize()
		{
			JSExport<Transition>::SetClassVersion(1);
			JSExport<Transition>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

		}

					} // namespace Animation
				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
