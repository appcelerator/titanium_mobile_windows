/**
 * Windows Native Wrapper for Windows.UI.Xaml.DataTemplate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DataTemplate.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.FrameworkTemplate.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		DataTemplate::DataTemplate(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::FrameworkTemplate(js_context)
		{
			TITANIUM_LOG_DEBUG("DataTemplate::ctor");
		}

		void DataTemplate::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("DataTemplate::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::DataTemplate();
			}

		}

		::Windows::UI::Xaml::DataTemplate^ DataTemplate::unwrapWindows_UI_Xaml_DataTemplate() const
		{
			return dynamic_cast<::Windows::UI::Xaml::DataTemplate^>(wrapped__);
		}

		::Windows::UI::Xaml::DataTemplate^ DataTemplate::unwrap() const
		{
			return unwrapWindows_UI_Xaml_DataTemplate();
		}

		void DataTemplate::wrap(::Windows::UI::Xaml::DataTemplate^ object)
		{
			wrapped__ = object;
		}

		void DataTemplate::JSExportInitialize()
		{
			JSExport<DataTemplate>::SetClassVersion(1);
			JSExport<DataTemplate>::SetParent(JSExport<Windows::UI::Xaml::FrameworkTemplate>::Class());

			TITANIUM_ADD_FUNCTION(DataTemplate, LoadContent);
		}

		TITANIUM_FUNCTION(DataTemplate, LoadContent)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->LoadContent();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyObject>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyObject>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DataTemplate::LoadContent with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
