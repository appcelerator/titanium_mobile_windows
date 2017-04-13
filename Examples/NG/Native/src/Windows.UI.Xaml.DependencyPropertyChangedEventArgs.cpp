/**
 * Windows Native Wrapper for Windows.UI.Xaml.DependencyPropertyChangedEventArgs
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.DependencyPropertyChangedEventArgs.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		DependencyPropertyChangedEventArgs::DependencyPropertyChangedEventArgs(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("DependencyPropertyChangedEventArgs::ctor");
		}

		void DependencyPropertyChangedEventArgs::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("DependencyPropertyChangedEventArgs::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ DependencyPropertyChangedEventArgs::unwrapWindows_UI_Xaml_DependencyPropertyChangedEventArgs() const
		{
			return dynamic_cast<::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^>(wrapped__);
		}

		::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ DependencyPropertyChangedEventArgs::unwrap() const
		{
			return unwrapWindows_UI_Xaml_DependencyPropertyChangedEventArgs();
		}

		void DependencyPropertyChangedEventArgs::wrap(::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ object)
		{
			wrapped__ = object;
		}

		void DependencyPropertyChangedEventArgs::JSExportInitialize()
		{
			JSExport<DependencyPropertyChangedEventArgs>::SetClassVersion(1);
			JSExport<DependencyPropertyChangedEventArgs>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(DependencyPropertyChangedEventArgs, NewValue);
			TITANIUM_ADD_PROPERTY_READONLY(DependencyPropertyChangedEventArgs, OldValue);
			TITANIUM_ADD_PROPERTY_READONLY(DependencyPropertyChangedEventArgs, Property);
		}

		TITANIUM_PROPERTY_GETTER(DependencyPropertyChangedEventArgs, NewValue)
		{
			auto value = unwrap()->NewValue;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(DependencyPropertyChangedEventArgs, OldValue)
		{
			auto value = unwrap()->OldValue;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(DependencyPropertyChangedEventArgs, Property)
		{
			auto value = unwrap()->Property;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
