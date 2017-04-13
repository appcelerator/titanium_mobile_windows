/**
 * Windows Native Wrapper for Windows.UI.Xaml.TriggerBase
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.TriggerBase.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		TriggerBase::TriggerBase(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("TriggerBase::ctor");
		}

		void TriggerBase::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("TriggerBase::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::TriggerBase^ TriggerBase::unwrapWindows_UI_Xaml_TriggerBase() const
		{
			return dynamic_cast<::Windows::UI::Xaml::TriggerBase^>(wrapped__);
		}

		::Windows::UI::Xaml::TriggerBase^ TriggerBase::unwrap() const
		{
			return unwrapWindows_UI_Xaml_TriggerBase();
		}

		void TriggerBase::wrap(::Windows::UI::Xaml::TriggerBase^ object)
		{
			wrapped__ = object;
		}

		void TriggerBase::JSExportInitialize()
		{
			JSExport<TriggerBase>::SetClassVersion(1);
			JSExport<TriggerBase>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
