/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.BindingExpression
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Data.Binding.hpp"
#include "Windows.UI.Xaml.Data.BindingExpression.hpp"
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

		BindingExpression::BindingExpression(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Data::BindingExpressionBase(js_context)
		{
			TITANIUM_LOG_DEBUG("BindingExpression::ctor");
		}

		void BindingExpression::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("BindingExpression::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Data::BindingExpression^ BindingExpression::unwrapWindows_UI_Xaml_Data_BindingExpression() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Data::BindingExpression^>(wrapped__);
		}

		::Windows::UI::Xaml::Data::BindingExpression^ BindingExpression::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Data_BindingExpression();
		}

		void BindingExpression::wrap(::Windows::UI::Xaml::Data::BindingExpression^ object)
		{
			wrapped__ = object;
		}

		void BindingExpression::JSExportInitialize()
		{
			JSExport<BindingExpression>::SetClassVersion(1);
			JSExport<BindingExpression>::SetParent(JSExport<Windows::UI::Xaml::Data::BindingExpressionBase>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(BindingExpression, DataItem);
			TITANIUM_ADD_PROPERTY_READONLY(BindingExpression, ParentBinding);
			TITANIUM_ADD_FUNCTION(BindingExpression, UpdateSource);
		}

		TITANIUM_PROPERTY_GETTER(BindingExpression, DataItem)
		{
			auto value = unwrap()->DataItem;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(BindingExpression, ParentBinding)
		{
			auto value = unwrap()->ParentBinding;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Data::Binding>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Data::Binding>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(BindingExpression, UpdateSource)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->UpdateSource();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched BindingExpression::UpdateSource with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
