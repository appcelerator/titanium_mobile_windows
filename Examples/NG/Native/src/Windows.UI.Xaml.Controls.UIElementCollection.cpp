/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.UIElementCollection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

#include "Windows.UI.Xaml.Controls.UIElementCollection.hpp"
#include "Windows.UI.Xaml.UIElement.hpp"


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

		UIElementCollection::UIElementCollection(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("UIElementCollection::ctor");
		}

		void UIElementCollection::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("UIElementCollection::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Controls::UIElementCollection^ UIElementCollection::unwrapWindows_UI_Xaml_Controls_UIElementCollection() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Controls::UIElementCollection^>(wrapped__);
		}

		::Windows::UI::Xaml::Controls::UIElementCollection^ UIElementCollection::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Controls_UIElementCollection();
		}

		void UIElementCollection::wrap(::Windows::UI::Xaml::Controls::UIElementCollection^ object)
		{
			wrapped__ = object;
		}

		void UIElementCollection::JSExportInitialize()
		{
			JSExport<UIElementCollection>::SetClassVersion(1);
			JSExport<UIElementCollection>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(UIElementCollection, Size);
			TITANIUM_ADD_FUNCTION(UIElementCollection, GetAt);
			TITANIUM_ADD_FUNCTION(UIElementCollection, GetView);
			TITANIUM_ADD_FUNCTION(UIElementCollection, IndexOf);
			TITANIUM_ADD_FUNCTION(UIElementCollection, SetAt);
			TITANIUM_ADD_FUNCTION(UIElementCollection, InsertAt);
			TITANIUM_ADD_FUNCTION(UIElementCollection, RemoveAt);
			TITANIUM_ADD_FUNCTION(UIElementCollection, Append);
			TITANIUM_ADD_FUNCTION(UIElementCollection, RemoveAtEnd);
			TITANIUM_ADD_FUNCTION(UIElementCollection, Clear);
			TITANIUM_ADD_FUNCTION(UIElementCollection, GetMany);
			TITANIUM_ADD_FUNCTION(UIElementCollection, ReplaceAll);
			TITANIUM_ADD_FUNCTION(UIElementCollection, First);
			TITANIUM_ADD_FUNCTION(UIElementCollection, Move);
		}

		TITANIUM_PROPERTY_GETTER(UIElementCollection, Size)
		{
			auto value = unwrap()->Size;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_FUNCTION(UIElementCollection, GetAt)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto method_result = unwrap()->GetAt(index);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::UIElement>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::UIElement>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::GetAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, GetView)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->GetView();

			std::vector<JSValue> result_vector;
			for (uint32_t i = 0; i < method_result->Size; ++i) {
				

			auto method_result_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::UIElement>::Class());
			auto method_result_tmp_wrapper = method_result_tmp.GetPrivate<Windows::UI::Xaml::UIElement>();
			method_result_tmp_wrapper->wrap(method_result->GetAt(i));


        		result_vector.push_back(method_result_tmp);
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::GetView with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, IndexOf)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_UIElement();

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
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::IndexOf with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, SetAt)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_UIElement();

				unwrap()->SetAt(index, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::SetAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, InsertAt)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto index = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_1);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_UIElement();

				unwrap()->InsertAt(index, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::InsertAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, RemoveAt)
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
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::RemoveAt with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, Append)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
				TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
				auto object_value = static_cast<JSObject>(_0);

				auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::UIElement>();
				if (wrapper_value) {
					auto value = wrapper_value->unwrapWindows_UI_Xaml_UIElement();
					unwrap()->Append(value);
					return context.CreateUndefined();
				} else {
					auto view = object_value.GetPrivate<::Titanium::UI::View>();
					if (view) {
						auto component = view->getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>()->getComponent();
						unwrap()->Append(component);
						return context.CreateUndefined();
					}
				}
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::Append with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, RemoveAtEnd)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->RemoveAtEnd();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::RemoveAtEnd with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, Clear)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Clear();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::Clear with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, GetMany)
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
			auto items_items = array_items.GetPrivateItems<Windows::UI::Xaml::UIElement>(); // std::vector<std::shared_ptr<Windows::UI::Xaml::UIElement>
			auto items = ref new ::Platform::Array<::Windows::UI::Xaml::UIElement^>(items_items.size());
			for (size_t i = 0; i < items_items.size(); ++i) {
				items[i] = items_items.at(i)->unwrapWindows_UI_Xaml_UIElement();
			}

				auto method_result = unwrap()->GetMany(startIndex, items);
 
			auto result = context.CreateNumber(method_result);



			std::vector<JSValue> out_1_vector;
			for (size_t i = 0; i < items->Length; ++i) {
				
			auto items_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::UIElement>::Class());
			auto items_tmp_wrapper = items_tmp.GetPrivate<Windows::UI::Xaml::UIElement>();
			items_tmp_wrapper->wrap(items[i]);
		
        		out_1_vector.push_back(items_tmp);
			}

			auto out_1 = get_context().CreateArray(out_1_vector);

				_1 = out_1;
				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::GetMany with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, ReplaceAll)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_items = static_cast<JSObject>(_0);

			TITANIUM_ASSERT(object_items.IsArray());
			const auto array_items = static_cast<JSArray>(object_items);
			auto items_items = array_items.GetPrivateItems<Windows::UI::Xaml::UIElement>(); // std::vector<std::shared_ptr<Windows::UI::Xaml::UIElement>
			auto items = ref new ::Platform::Array<::Windows::UI::Xaml::UIElement^>(items_items.size());
			for (size_t i = 0; i < items_items.size(); ++i) {
				items[i] = items_items.at(i)->unwrapWindows_UI_Xaml_UIElement();
			}

				unwrap()->ReplaceAll(items);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::ReplaceAll with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, First)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->First();

			std::vector<JSValue> result_vector;
			while (method_result->HasCurrent) {
				

			auto method_result_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::UIElement>::Class());
			auto method_result_tmp_wrapper = method_result_tmp.GetPrivate<Windows::UI::Xaml::UIElement>();
			method_result_tmp_wrapper->wrap(method_result->Current);


        		result_vector.push_back(method_result_tmp);
        		method_result->MoveNext();
			}

			auto result = get_context().CreateArray(result_vector);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::First with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElementCollection, Move)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto oldIndex = static_cast<uint32_t>(_0);

				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto newIndex = static_cast<uint32_t>(_1);

				unwrap()->Move(oldIndex, newIndex);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElementCollection::Move with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
