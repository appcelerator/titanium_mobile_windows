/**
 * Windows Native Wrapper for Windows.UI.Xaml.DependencyObject
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Core.CoreDispatcher.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		DependencyObject::DependencyObject(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("DependencyObject::ctor");
		}

		void DependencyObject::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("DependencyObject::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::DependencyObject^ DependencyObject::unwrapWindows_UI_Xaml_DependencyObject() const
		{
			return dynamic_cast<::Windows::UI::Xaml::DependencyObject^>(wrapped__);
		}

		::Windows::UI::Xaml::DependencyObject^ DependencyObject::unwrap() const
		{
			return unwrapWindows_UI_Xaml_DependencyObject();
		}

		void DependencyObject::wrap(::Windows::UI::Xaml::DependencyObject^ object)
		{
			wrapped__ = object;
		}

		void DependencyObject::JSExportInitialize()
		{
			JSExport<DependencyObject>::SetClassVersion(1);
			JSExport<DependencyObject>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(DependencyObject, Dispatcher);
			TITANIUM_ADD_FUNCTION(DependencyObject, GetValue);
			TITANIUM_ADD_FUNCTION(DependencyObject, SetValue);
			TITANIUM_ADD_FUNCTION(DependencyObject, ClearValue);
			TITANIUM_ADD_FUNCTION(DependencyObject, ReadLocalValue);
			TITANIUM_ADD_FUNCTION(DependencyObject, GetAnimationBaseValue);
		}

		TITANIUM_PROPERTY_GETTER(DependencyObject, Dispatcher)
		{
			auto value = unwrap()->Dispatcher;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Core::CoreDispatcher>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Core::CoreDispatcher>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(DependencyObject, GetValue)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_dp = static_cast<JSObject>(_0);
 
			auto wrapper_dp = object_dp.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto dp = wrapper_dp->unwrapWindows_UI_Xaml_DependencyProperty();

				auto method_result = unwrap()->GetValue(dp);

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyObject::GetValue with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(DependencyObject, SetValue)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_dp = static_cast<JSObject>(_0);
 
			auto wrapper_dp = object_dp.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto dp = wrapper_dp->unwrapWindows_UI_Xaml_DependencyProperty();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

				unwrap()->SetValue(dp, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyObject::SetValue with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(DependencyObject, ClearValue)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_dp = static_cast<JSObject>(_0);
 
			auto wrapper_dp = object_dp.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto dp = wrapper_dp->unwrapWindows_UI_Xaml_DependencyProperty();

				unwrap()->ClearValue(dp);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyObject::ClearValue with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(DependencyObject, ReadLocalValue)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_dp = static_cast<JSObject>(_0);
 
			auto wrapper_dp = object_dp.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto dp = wrapper_dp->unwrapWindows_UI_Xaml_DependencyProperty();

				auto method_result = unwrap()->ReadLocalValue(dp);

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyObject::ReadLocalValue with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(DependencyObject, GetAnimationBaseValue)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_dp = static_cast<JSObject>(_0);
 
			auto wrapper_dp = object_dp.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto dp = wrapper_dp->unwrapWindows_UI_Xaml_DependencyProperty();

				auto method_result = unwrap()->GetAnimationBaseValue(dp);

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyObject::GetAnimationBaseValue with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
