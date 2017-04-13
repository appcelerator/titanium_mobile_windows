/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Transform
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Media.GeneralTransform.hpp"
#include "Windows.UI.Xaml.Media.Transform.hpp"
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

		Transform::Transform(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Media::GeneralTransform(js_context)
		{
			TITANIUM_LOG_DEBUG("Transform::ctor");
		}

		void Transform::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Transform::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Media::Transform^ Transform::unwrapWindows_UI_Xaml_Media_Transform() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::Transform^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::Transform^ Transform::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_Transform();
		}

		void Transform::wrap(::Windows::UI::Xaml::Media::Transform^ object)
		{
			wrapped__ = object;
		}

		void Transform::JSExportInitialize()
		{
			JSExport<Transform>::SetClassVersion(1);
			JSExport<Transform>::SetParent(JSExport<Windows::UI::Xaml::Media::GeneralTransform>::Class());

		}

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
