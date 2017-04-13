/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.BindingExpressionBase
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Data.BindingExpressionBase.hpp"
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

		BindingExpressionBase::BindingExpressionBase(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("BindingExpressionBase::ctor");
		}

		void BindingExpressionBase::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("BindingExpressionBase::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Data::BindingExpressionBase^ BindingExpressionBase::unwrapWindows_UI_Xaml_Data_BindingExpressionBase() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Data::BindingExpressionBase^>(wrapped__);
		}

		::Windows::UI::Xaml::Data::BindingExpressionBase^ BindingExpressionBase::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Data_BindingExpressionBase();
		}

		void BindingExpressionBase::wrap(::Windows::UI::Xaml::Data::BindingExpressionBase^ object)
		{
			wrapped__ = object;
		}

		void BindingExpressionBase::JSExportInitialize()
		{
			JSExport<BindingExpressionBase>::SetClassVersion(1);
			JSExport<BindingExpressionBase>::SetParent(JSExport<Titanium::Platform::Object>::Class());

		}

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
