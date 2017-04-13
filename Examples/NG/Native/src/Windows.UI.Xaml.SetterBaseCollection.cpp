/**
 * Windows Native Wrapper for Windows.UI.Xaml.SetterBaseCollection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.SetterBase.hpp"
#include "Windows.UI.Xaml.SetterBaseCollection.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		SetterBaseCollection::SetterBaseCollection(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("SetterBaseCollection::ctor");
		}

		void SetterBaseCollection::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("SetterBaseCollection::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::SetterBaseCollection();
			}

		}

		::Windows::UI::Xaml::SetterBaseCollection^ SetterBaseCollection::unwrapWindows_UI_Xaml_SetterBaseCollection() const
		{
			return dynamic_cast<::Windows::UI::Xaml::SetterBaseCollection^>(wrapped__);
		}

		::Windows::UI::Xaml::SetterBaseCollection^ SetterBaseCollection::unwrap() const
		{
			return unwrapWindows_UI_Xaml_SetterBaseCollection();
		}

		void SetterBaseCollection::wrap(::Windows::UI::Xaml::SetterBaseCollection^ object)
		{
			wrapped__ = object;
		}

		void SetterBaseCollection::JSExportInitialize()
		{
			JSExport<SetterBaseCollection>::SetClassVersion(1);
			JSExport<SetterBaseCollection>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(SetterBaseCollection, IsSealed);
			TITANIUM_ADD_PROPERTY_READONLY(SetterBaseCollection, Size);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, GetAt);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, GetView);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, IndexOf);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, SetAt);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, InsertAt);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, RemoveAt);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, Append);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, RemoveAtEnd);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, Clear);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, GetMany);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, ReplaceAll);
			TITANIUM_ADD_FUNCTION(SetterBaseCollection, First);
		}

		TITANIUM_PROPERTY_GETTER(SetterBaseCollection, IsSealed)
		{
			auto value = unwrap()->IsSealed;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_GETTER(SetterBaseCollection, Size)
		{
			auto value = unwrap()->Size;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_FUNCTION(SetterBaseCollection, GetAt)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto method_result = unwrap()->GetAt(index);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::SetterBase>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::SetterBase>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::GetAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, GetView)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->GetView();

			std::vector<JSValue> result_vector;
			for (uint32_t i = 0; i < method_result->Size; ++i) {
				

			auto method_result_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::SetterBase>::Class());
			auto method_result_tmp_wrapper = method_result_tmp.GetPrivate<Windows::UI::Xaml::SetterBase>();
			method_result_tmp_wrapper->wrap(method_result->GetAt(i));


        		result_vector.push_back(method_result_tmp);
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::GetView with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, IndexOf)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::SetterBase>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_SetterBase();

				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_1);

				auto method_result = unwrap()->IndexOf(value, &index);
 
			auto result = context.CreateBoolean(method_result); 


 
			auto out_1 = context.CreateNumber(index);

				_1 = out_1;
				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::IndexOf with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, SetAt)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::SetterBase>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_SetterBase();

				unwrap()->SetAt(index, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::SetAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, InsertAt)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::SetterBase>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_SetterBase();

				unwrap()->InsertAt(index, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::InsertAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, RemoveAt)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				unwrap()->RemoveAt(index);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::RemoveAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, Append)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::SetterBase>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_SetterBase();

				unwrap()->Append(value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::Append with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, RemoveAtEnd)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->RemoveAtEnd();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::RemoveAtEnd with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, Clear)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Clear();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::Clear with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, GetMany)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto startIndex = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_items = static_cast<JSObject>(_1);

			TITANIUM_ASSERT(object_items.IsArray());
			const auto array_items = static_cast<JSArray>(object_items);
			auto items_items = array_items.GetPrivateItems<Windows::UI::Xaml::SetterBase>(); // std::vector<std::shared_ptr<Windows::UI::Xaml::SetterBase>
			auto items = ref new ::Platform::Array<::Windows::UI::Xaml::SetterBase^>(items_items.size());
			for (size_t i = 0; i < items_items.size(); ++i) {
				items[i] = items_items.at(i)->unwrapWindows_UI_Xaml_SetterBase();
			}

				auto method_result = unwrap()->GetMany(startIndex, items);
 
			auto result = context.CreateNumber(method_result);



			std::vector<JSValue> out_1_vector;
			for (size_t i = 0; i < items->Length; ++i) {
				
			auto items_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::SetterBase>::Class());
			auto items_tmp_wrapper = items_tmp.GetPrivate<Windows::UI::Xaml::SetterBase>();
			items_tmp_wrapper->wrap(items[i]);
		
        		out_1_vector.push_back(items_tmp);
			}

			auto out_1 = get_context().CreateArray(out_1_vector);

				_1 = out_1;
				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::GetMany with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, ReplaceAll)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_items = static_cast<JSObject>(_0);

			TITANIUM_ASSERT(object_items.IsArray());
			const auto array_items = static_cast<JSArray>(object_items);
			auto items_items = array_items.GetPrivateItems<Windows::UI::Xaml::SetterBase>(); // std::vector<std::shared_ptr<Windows::UI::Xaml::SetterBase>
			auto items = ref new ::Platform::Array<::Windows::UI::Xaml::SetterBase^>(items_items.size());
			for (size_t i = 0; i < items_items.size(); ++i) {
				items[i] = items_items.at(i)->unwrapWindows_UI_Xaml_SetterBase();
			}

				unwrap()->ReplaceAll(items);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::ReplaceAll with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(SetterBaseCollection, First)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->First();

			std::vector<JSValue> result_vector;
			while (method_result->HasCurrent) {
				

			auto method_result_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::SetterBase>::Class());
			auto method_result_tmp_wrapper = method_result_tmp.GetPrivate<Windows::UI::Xaml::SetterBase>();
			method_result_tmp_wrapper->wrap(method_result->Current);


        		result_vector.push_back(method_result_tmp);
        		method_result->MoveNext();
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched SetterBaseCollection::First with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
