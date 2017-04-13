/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Projection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.Media.Projection.hpp"
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

		Projection::Projection(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("Projection::ctor");
		}

		void Projection::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Projection::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Media::Projection^ Projection::unwrapWindows_UI_Xaml_Media_Projection() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::Projection^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::Projection^ Projection::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_Projection();
		}

		void Projection::wrap(::Windows::UI::Xaml::Media::Projection^ object)
		{
			wrapped__ = object;
		}

		void Projection::JSExportInitialize()
		{
			JSExport<Projection>::SetClassVersion(1);
			JSExport<Projection>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

		}

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
