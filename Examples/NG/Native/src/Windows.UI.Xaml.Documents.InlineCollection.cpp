/**
 * Windows Native Wrapper for Windows.UI.Xaml.Documents.InlineCollection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Documents.Inline.hpp"
#include "Windows.UI.Xaml.Documents.InlineCollection.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Documents
				{

		InlineCollection::InlineCollection(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("InlineCollection::ctor");
		}

		void InlineCollection::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("InlineCollection::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Documents::InlineCollection^ InlineCollection::unwrapWindows_UI_Xaml_Documents_InlineCollection() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Documents::InlineCollection^>(wrapped__);
		}

		::Windows::UI::Xaml::Documents::InlineCollection^ InlineCollection::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Documents_InlineCollection();
		}

		void InlineCollection::wrap(::Windows::UI::Xaml::Documents::InlineCollection^ object)
		{
			wrapped__ = object;
		}

		void InlineCollection::JSExportInitialize()
		{
			JSExport<InlineCollection>::SetClassVersion(1);
			JSExport<InlineCollection>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(InlineCollection, Size);
			TITANIUM_ADD_FUNCTION(InlineCollection, GetAt);
			TITANIUM_ADD_FUNCTION(InlineCollection, GetView);
			TITANIUM_ADD_FUNCTION(InlineCollection, IndexOf);
			TITANIUM_ADD_FUNCTION(InlineCollection, SetAt);
			TITANIUM_ADD_FUNCTION(InlineCollection, InsertAt);
			TITANIUM_ADD_FUNCTION(InlineCollection, RemoveAt);
			TITANIUM_ADD_FUNCTION(InlineCollection, Append);
			TITANIUM_ADD_FUNCTION(InlineCollection, RemoveAtEnd);
			TITANIUM_ADD_FUNCTION(InlineCollection, Clear);
			TITANIUM_ADD_FUNCTION(InlineCollection, GetMany);
			TITANIUM_ADD_FUNCTION(InlineCollection, ReplaceAll);
			TITANIUM_ADD_FUNCTION(InlineCollection, First);
		}

		TITANIUM_PROPERTY_GETTER(InlineCollection, Size)
		{
			auto value = unwrap()->Size;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_FUNCTION(InlineCollection, GetAt)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto method_result = unwrap()->GetAt(index);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Documents::Inline>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::GetAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, GetView)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->GetView();

			std::vector<JSValue> result_vector;
			for (uint32_t i = 0; i < method_result->Size; ++i) {
				

			auto method_result_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::Documents::Inline>::Class());
			auto method_result_tmp_wrapper = method_result_tmp.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			method_result_tmp_wrapper->wrap(method_result->GetAt(i));


        		result_vector.push_back(method_result_tmp);
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::GetView with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, IndexOf)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Documents_Inline();

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
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::IndexOf with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, SetAt)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Documents_Inline();

				unwrap()->SetAt(index, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::SetAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, InsertAt)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Documents_Inline();

				unwrap()->InsertAt(index, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::InsertAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, RemoveAt)
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
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::RemoveAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, Append)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Documents_Inline();

				unwrap()->Append(value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::Append with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, RemoveAtEnd)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->RemoveAtEnd();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::RemoveAtEnd with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, Clear)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Clear();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::Clear with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, GetMany)
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
			auto items_items = array_items.GetPrivateItems<Windows::UI::Xaml::Documents::Inline>(); // std::vector<std::shared_ptr<Windows::UI::Xaml::Documents::Inline>
			auto items = ref new ::Platform::Array<::Windows::UI::Xaml::Documents::Inline^>(items_items.size());
			for (size_t i = 0; i < items_items.size(); ++i) {
				items[i] = items_items.at(i)->unwrapWindows_UI_Xaml_Documents_Inline();
			}

				auto method_result = unwrap()->GetMany(startIndex, items);
 
			auto result = context.CreateNumber(method_result);



			std::vector<JSValue> out_1_vector;
			for (size_t i = 0; i < items->Length; ++i) {
				
			auto items_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::Documents::Inline>::Class());
			auto items_tmp_wrapper = items_tmp.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			items_tmp_wrapper->wrap(items[i]);
		
        		out_1_vector.push_back(items_tmp);
			}

			auto out_1 = get_context().CreateArray(out_1_vector);

				_1 = out_1;
				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::GetMany with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, ReplaceAll)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_items = static_cast<JSObject>(_0);

			TITANIUM_ASSERT(object_items.IsArray());
			const auto array_items = static_cast<JSArray>(object_items);
			auto items_items = array_items.GetPrivateItems<Windows::UI::Xaml::Documents::Inline>(); // std::vector<std::shared_ptr<Windows::UI::Xaml::Documents::Inline>
			auto items = ref new ::Platform::Array<::Windows::UI::Xaml::Documents::Inline^>(items_items.size());
			for (size_t i = 0; i < items_items.size(); ++i) {
				items[i] = items_items.at(i)->unwrapWindows_UI_Xaml_Documents_Inline();
			}

				unwrap()->ReplaceAll(items);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::ReplaceAll with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(InlineCollection, First)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->First();

			std::vector<JSValue> result_vector;
			while (method_result->HasCurrent) {
				

			auto method_result_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::Documents::Inline>::Class());
			auto method_result_tmp_wrapper = method_result_tmp.GetPrivate<Windows::UI::Xaml::Documents::Inline>();
			method_result_tmp_wrapper->wrap(method_result->Current);


        		result_vector.push_back(method_result_tmp);
        		method_result->MoveNext();
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched InlineCollection::First with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Documents
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
