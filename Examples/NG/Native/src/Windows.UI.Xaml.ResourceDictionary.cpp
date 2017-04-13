/**
 * Windows Native Wrapper for Windows.UI.Xaml.ResourceDictionary
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Platform.Object.hpp"
#include "Windows.Foundation.Uri.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.ResourceDictionary.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		ResourceDictionary::ResourceDictionary(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("ResourceDictionary::ctor");
		}

		void ResourceDictionary::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("ResourceDictionary::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::ResourceDictionary();
			}

		}

		::Windows::UI::Xaml::ResourceDictionary^ ResourceDictionary::unwrapWindows_UI_Xaml_ResourceDictionary() const
		{
			return dynamic_cast<::Windows::UI::Xaml::ResourceDictionary^>(wrapped__);
		}

		::Windows::UI::Xaml::ResourceDictionary^ ResourceDictionary::unwrap() const
		{
			return unwrapWindows_UI_Xaml_ResourceDictionary();
		}

		void ResourceDictionary::wrap(::Windows::UI::Xaml::ResourceDictionary^ object)
		{
			wrapped__ = object;
		}

		void ResourceDictionary::JSExportInitialize()
		{
			JSExport<ResourceDictionary>::SetClassVersion(1);
			JSExport<ResourceDictionary>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(ResourceDictionary, Size);
			TITANIUM_ADD_PROPERTY(ResourceDictionary, Source);
			TITANIUM_ADD_PROPERTY_READONLY(ResourceDictionary, MergedDictionaries);
			TITANIUM_ADD_PROPERTY_READONLY(ResourceDictionary, ThemeDictionaries);
			TITANIUM_ADD_FUNCTION(ResourceDictionary, Lookup);
			TITANIUM_ADD_FUNCTION(ResourceDictionary, HasKey);
			TITANIUM_ADD_FUNCTION(ResourceDictionary, GetView);
			TITANIUM_ADD_FUNCTION(ResourceDictionary, Insert);
			TITANIUM_ADD_FUNCTION(ResourceDictionary, Remove);
			TITANIUM_ADD_FUNCTION(ResourceDictionary, Clear);
			TITANIUM_ADD_FUNCTION(ResourceDictionary, First);
		}

		TITANIUM_PROPERTY_GETTER(ResourceDictionary, Size)
		{
			auto value = unwrap()->Size;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(ResourceDictionary, Source)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::Foundation::Uri>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_Foundation_Uri();

			unwrap()->Source = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ResourceDictionary, Source)
		{
			auto value = unwrap()->Source;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::Foundation::Uri>::Class());
			auto result_wrapper = result.GetPrivate<Windows::Foundation::Uri>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(ResourceDictionary, MergedDictionaries)
		{
			auto value = unwrap()->MergedDictionaries;
			auto context = get_context();

			std::vector<JSValue> result_vector;
			for (uint32_t i = 0; i < value->Size; ++i) {
				

			auto value_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::ResourceDictionary>::Class());
			auto value_tmp_wrapper = value_tmp.GetPrivate<Windows::UI::Xaml::ResourceDictionary>();
			value_tmp_wrapper->wrap(value->GetAt(i));


        		result_vector.push_back(value_tmp);
			}

			auto result = get_context().CreateArray(result_vector);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(ResourceDictionary, ThemeDictionaries)
		{
			auto value = unwrap()->ThemeDictionaries;
			auto context = get_context();


			auto result_iter = value->First();
			
			std::vector<JSValue> result_vector;
			while (result_iter->HasCurrent) {
				

			auto result_iter_tmp = context.CreateObject();
			

			auto result_iter_tmp_key_tmp = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_iter_tmp_key_tmp_wrapper = result_iter_tmp_key_tmp.GetPrivate<Platform::Object>();
			result_iter_tmp_key_tmp_wrapper->wrap(result_iter->Current->Key);


			

			auto result_iter_tmp_value_tmp = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_iter_tmp_value_tmp_wrapper = result_iter_tmp_value_tmp.GetPrivate<Platform::Object>();
			result_iter_tmp_value_tmp_wrapper->wrap(result_iter->Current->Value);


        	result_iter_tmp.SetProperty("key", result_iter_tmp_key_tmp);
        	result_iter_tmp.SetProperty("value", result_iter_tmp_value_tmp);


        		result_vector.push_back(result_iter_tmp);
        		result_iter->MoveNext();
			}

			auto result = get_context().CreateArray(result_vector);



			return result;
		}

		TITANIUM_FUNCTION(ResourceDictionary, Lookup)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_key = static_cast<JSObject>(_0);
 
			auto wrapper_key = object_key.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto key = wrapper_key->unwrapPlatform_Object();

				auto method_result = unwrap()->Lookup(key);

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched ResourceDictionary::Lookup with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(ResourceDictionary, HasKey)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_key = static_cast<JSObject>(_0);
 
			auto wrapper_key = object_key.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto key = wrapper_key->unwrapPlatform_Object();

				auto method_result = unwrap()->HasKey(key);
 
			auto result = context.CreateBoolean(method_result); 

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched ResourceDictionary::HasKey with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(ResourceDictionary, GetView)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->GetView();


			auto result_iter = method_result->First();
			
			std::vector<JSValue> result_vector;
			while (result_iter->HasCurrent) {
				

			auto result_iter_tmp = context.CreateObject();
			

			auto result_iter_tmp_key_tmp = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_iter_tmp_key_tmp_wrapper = result_iter_tmp_key_tmp.GetPrivate<Platform::Object>();
			result_iter_tmp_key_tmp_wrapper->wrap(result_iter->Current->Key);


			

			auto result_iter_tmp_value_tmp = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_iter_tmp_value_tmp_wrapper = result_iter_tmp_value_tmp.GetPrivate<Platform::Object>();
			result_iter_tmp_value_tmp_wrapper->wrap(result_iter->Current->Value);


        	result_iter_tmp.SetProperty("key", result_iter_tmp_key_tmp);
        	result_iter_tmp.SetProperty("value", result_iter_tmp_value_tmp);


        		result_vector.push_back(result_iter_tmp);
        		result_iter->MoveNext();
			}

			auto result = get_context().CreateArray(result_vector);



				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched ResourceDictionary::GetView with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(ResourceDictionary, Insert)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_key = static_cast<JSObject>(_0);
 
			auto wrapper_key = object_key.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto key = wrapper_key->unwrapPlatform_Object();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

				auto method_result = unwrap()->Insert(key, value);
 
			auto result = context.CreateBoolean(method_result); 

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched ResourceDictionary::Insert with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(ResourceDictionary, Remove)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_key = static_cast<JSObject>(_0);
 
			auto wrapper_key = object_key.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto key = wrapper_key->unwrapPlatform_Object();

				unwrap()->Remove(key);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched ResourceDictionary::Remove with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(ResourceDictionary, Clear)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Clear();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched ResourceDictionary::Clear with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(ResourceDictionary, First)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->First();

			std::vector<JSValue> result_vector;
			while (method_result->HasCurrent) {
				

			auto method_result_tmp = context.CreateObject();
			

			auto method_result_tmp_key_tmp = context.CreateObject(JSExport<Platform::Object>::Class());
			auto method_result_tmp_key_tmp_wrapper = method_result_tmp_key_tmp.GetPrivate<Platform::Object>();
			method_result_tmp_key_tmp_wrapper->wrap(method_result->Current->Key);


			

			auto method_result_tmp_value_tmp = context.CreateObject(JSExport<Platform::Object>::Class());
			auto method_result_tmp_value_tmp_wrapper = method_result_tmp_value_tmp.GetPrivate<Platform::Object>();
			method_result_tmp_value_tmp_wrapper->wrap(method_result->Current->Value);


        	method_result_tmp.SetProperty("key", method_result_tmp_key_tmp);
        	method_result_tmp.SetProperty("value", method_result_tmp_value_tmp);


        		result_vector.push_back(method_result_tmp);
        		method_result->MoveNext();
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched ResourceDictionary::First with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
