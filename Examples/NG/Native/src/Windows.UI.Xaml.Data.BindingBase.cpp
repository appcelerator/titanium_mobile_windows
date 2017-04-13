/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.BindingBase
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Data.BindingBase.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Data
				{

		BindingBase::BindingBase(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("BindingBase::ctor");
		}

		void BindingBase::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("BindingBase::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Data::BindingBase();
			}

		}

		::Windows::UI::Xaml::Data::BindingBase^ BindingBase::unwrapWindows_UI_Xaml_Data_BindingBase() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Data::BindingBase^>(wrapped__);
		}

		::Windows::UI::Xaml::Data::BindingBase^ BindingBase::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Data_BindingBase();
		}

		void BindingBase::wrap(::Windows::UI::Xaml::Data::BindingBase^ object)
		{
			wrapped__ = object;
		}

		void BindingBase::JSExportInitialize()
		{
			JSExport<BindingBase>::SetClassVersion(1);
			JSExport<BindingBase>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

		}

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
