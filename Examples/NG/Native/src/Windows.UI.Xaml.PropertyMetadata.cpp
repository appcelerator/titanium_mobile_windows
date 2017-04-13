/**
 * Windows Native Wrapper for Windows.UI.Xaml.PropertyMetadata
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.CreateDefaultValueCallback.hpp"
#include "Windows.UI.Xaml.PropertyChangedCallback.hpp"
#include "Windows.UI.Xaml.PropertyMetadata.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		PropertyMetadata::PropertyMetadata(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("PropertyMetadata::ctor");
		}

		void PropertyMetadata::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("PropertyMetadata::postCallAsConstructor ", this);
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_defaultValue = static_cast<JSObject>(_0);
 
			auto wrapper_defaultValue = object_defaultValue.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto defaultValue = wrapper_defaultValue->unwrapPlatform_Object();
				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_propertyChangedCallback = static_cast<JSObject>(_1);
 
			auto wrapper_propertyChangedCallback = object_propertyChangedCallback.GetPrivate<Windows::UI::Xaml::PropertyChangedCallback>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto propertyChangedCallback = wrapper_propertyChangedCallback->unwrapWindows_UI_Xaml_PropertyChangedCallback();

				wrapped__ = ref new ::Windows::UI::Xaml::PropertyMetadata(defaultValue, propertyChangedCallback);
			}
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_defaultValue = static_cast<JSObject>(_0);
 
			auto wrapper_defaultValue = object_defaultValue.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto defaultValue = wrapper_defaultValue->unwrapPlatform_Object();

				wrapped__ = ref new ::Windows::UI::Xaml::PropertyMetadata(defaultValue);
			}

		}

		::Windows::UI::Xaml::PropertyMetadata^ PropertyMetadata::unwrapWindows_UI_Xaml_PropertyMetadata() const
		{
			return dynamic_cast<::Windows::UI::Xaml::PropertyMetadata^>(wrapped__);
		}

		::Windows::UI::Xaml::PropertyMetadata^ PropertyMetadata::unwrap() const
		{
			return unwrapWindows_UI_Xaml_PropertyMetadata();
		}

		void PropertyMetadata::wrap(::Windows::UI::Xaml::PropertyMetadata^ object)
		{
			wrapped__ = object;
		}

		void PropertyMetadata::JSExportInitialize()
		{
			JSExport<PropertyMetadata>::SetClassVersion(1);
			JSExport<PropertyMetadata>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(PropertyMetadata, CreateDefaultValueCallback);
			TITANIUM_ADD_PROPERTY_READONLY(PropertyMetadata, DefaultValue);
			TITANIUM_ADD_FUNCTION(PropertyMetadata, Create);
		}

		TITANIUM_PROPERTY_GETTER(PropertyMetadata, CreateDefaultValueCallback)
		{
			auto value = unwrap()->CreateDefaultValueCallback;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::CreateDefaultValueCallback>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::CreateDefaultValueCallback>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(PropertyMetadata, DefaultValue)
		{
			auto value = unwrap()->DefaultValue;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(PropertyMetadata, Create)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_createDefaultValueCallback = static_cast<JSObject>(_0);
 
			auto wrapper_createDefaultValueCallback = object_createDefaultValueCallback.GetPrivate<Windows::UI::Xaml::CreateDefaultValueCallback>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto createDefaultValueCallback = wrapper_createDefaultValueCallback->unwrapWindows_UI_Xaml_CreateDefaultValueCallback();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_propertyChangedCallback = static_cast<JSObject>(_1);
 
			auto wrapper_propertyChangedCallback = object_propertyChangedCallback.GetPrivate<Windows::UI::Xaml::PropertyChangedCallback>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto propertyChangedCallback = wrapper_propertyChangedCallback->unwrapWindows_UI_Xaml_PropertyChangedCallback();

				auto method_result = ::Windows::UI::Xaml::PropertyMetadata::Create(createDefaultValueCallback, propertyChangedCallback);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::PropertyMetadata>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::PropertyMetadata>();
			result_wrapper->wrap(method_result);

				return result;
			}

			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_createDefaultValueCallback = static_cast<JSObject>(_0);
 
			auto wrapper_createDefaultValueCallback = object_createDefaultValueCallback.GetPrivate<Windows::UI::Xaml::CreateDefaultValueCallback>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto createDefaultValueCallback = wrapper_createDefaultValueCallback->unwrapWindows_UI_Xaml_CreateDefaultValueCallback();

				auto method_result = ::Windows::UI::Xaml::PropertyMetadata::Create(createDefaultValueCallback);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::PropertyMetadata>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::PropertyMetadata>();
			result_wrapper->wrap(method_result);

				return result;
			}

			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_defaultValue = static_cast<JSObject>(_0);
 
			auto wrapper_defaultValue = object_defaultValue.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto defaultValue = wrapper_defaultValue->unwrapPlatform_Object();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_propertyChangedCallback = static_cast<JSObject>(_1);
 
			auto wrapper_propertyChangedCallback = object_propertyChangedCallback.GetPrivate<Windows::UI::Xaml::PropertyChangedCallback>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto propertyChangedCallback = wrapper_propertyChangedCallback->unwrapWindows_UI_Xaml_PropertyChangedCallback();

				auto method_result = ::Windows::UI::Xaml::PropertyMetadata::Create(defaultValue, propertyChangedCallback);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::PropertyMetadata>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::PropertyMetadata>();
			result_wrapper->wrap(method_result);

				return result;
			}

			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_defaultValue = static_cast<JSObject>(_0);
 
			auto wrapper_defaultValue = object_defaultValue.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto defaultValue = wrapper_defaultValue->unwrapPlatform_Object();

				auto method_result = ::Windows::UI::Xaml::PropertyMetadata::Create(defaultValue);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::PropertyMetadata>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::PropertyMetadata>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched PropertyMetadata::Create with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
