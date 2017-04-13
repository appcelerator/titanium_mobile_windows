/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.DataTemplateSelector
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Controls.DataTemplateSelector.hpp"
#include "Windows.UI.Xaml.DataTemplate.hpp"
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
				namespace Controls
				{

		DataTemplateSelector::DataTemplateSelector(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("DataTemplateSelector::ctor");
		}

		void DataTemplateSelector::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("DataTemplateSelector::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Controls::DataTemplateSelector();
			}

		}

		::Windows::UI::Xaml::Controls::DataTemplateSelector^ DataTemplateSelector::unwrapWindows_UI_Xaml_Controls_DataTemplateSelector() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Controls::DataTemplateSelector^>(wrapped__);
		}

		::Windows::UI::Xaml::Controls::DataTemplateSelector^ DataTemplateSelector::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Controls_DataTemplateSelector();
		}

		void DataTemplateSelector::wrap(::Windows::UI::Xaml::Controls::DataTemplateSelector^ object)
		{
			wrapped__ = object;
		}

		void DataTemplateSelector::JSExportInitialize()
		{
			JSExport<DataTemplateSelector>::SetClassVersion(1);
			JSExport<DataTemplateSelector>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_FUNCTION(DataTemplateSelector, SelectTemplate);
		}

		TITANIUM_FUNCTION(DataTemplateSelector, SelectTemplate)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_item = static_cast<JSObject>(_0);
 
			auto wrapper_item = object_item.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto item = wrapper_item->unwrapPlatform_Object();

				auto method_result = unwrap()->SelectTemplate(item);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DataTemplate>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DataTemplate>();
			result_wrapper->wrap(method_result);

				return result;
			}

			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_item = static_cast<JSObject>(_0);
 
			auto wrapper_item = object_item.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto item = wrapper_item->unwrapPlatform_Object();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_container = static_cast<JSObject>(_1);
 
			auto wrapper_container = object_container.GetPrivate<Windows::UI::Xaml::DependencyObject>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto container = wrapper_container->unwrapWindows_UI_Xaml_DependencyObject();

				auto method_result = unwrap()->SelectTemplate(item, container);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DataTemplate>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DataTemplate>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DataTemplateSelector::SelectTemplate with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
