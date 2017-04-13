/**
 * Windows Native Wrapper for Windows.UI.Xaml.DependencyProperty
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyProperty.hpp"
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

		DependencyProperty::DependencyProperty(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("DependencyProperty::ctor");
		}

		void DependencyProperty::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("DependencyProperty::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::DependencyProperty^ DependencyProperty::unwrapWindows_UI_Xaml_DependencyProperty() const
		{
			return dynamic_cast<::Windows::UI::Xaml::DependencyProperty^>(wrapped__);
		}

		::Windows::UI::Xaml::DependencyProperty^ DependencyProperty::unwrap() const
		{
			return unwrapWindows_UI_Xaml_DependencyProperty();
		}

		void DependencyProperty::wrap(::Windows::UI::Xaml::DependencyProperty^ object)
		{
			wrapped__ = object;
		}

		void DependencyProperty::JSExportInitialize()
		{
			JSExport<DependencyProperty>::SetClassVersion(1);
			JSExport<DependencyProperty>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(DependencyProperty, UnsetValue);
			TITANIUM_ADD_FUNCTION(DependencyProperty, GetMetadata);
			TITANIUM_ADD_FUNCTION(DependencyProperty, Register);
			TITANIUM_ADD_FUNCTION(DependencyProperty, RegisterAttached);
		}

		TITANIUM_PROPERTY_GETTER(DependencyProperty, UnsetValue)
		{
			auto value = unwrap()->UnsetValue;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(DependencyProperty, GetMetadata)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_forType = static_cast<JSObject>(_0);
			::Windows::UI::Xaml::Interop::TypeName forType;
			// Assign fields explicitly since we didn't use a constructor

			auto object_forType_Name = object_forType.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_forType_Name.IsString(), "Expected String");
			auto object_forType_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_forType_Name));

			forType.Name = object_forType_Name_;

			auto object_forType_Kind = object_forType.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_forType_Kind.IsNumber(), "Expected Number");
			auto object_forType_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_forType_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			forType.Kind = object_forType_Kind_;

				auto method_result = unwrap()->GetMetadata(forType);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::PropertyMetadata>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::PropertyMetadata>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyProperty::GetMetadata with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(DependencyProperty, Register)
		{
			auto context = get_context();
			if (arguments.size() == 4) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto name = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_propertyType = static_cast<JSObject>(_1);
			::Windows::UI::Xaml::Interop::TypeName propertyType;
			// Assign fields explicitly since we didn't use a constructor

			auto object_propertyType_Name = object_propertyType.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_propertyType_Name.IsString(), "Expected String");
			auto object_propertyType_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_propertyType_Name));

			propertyType.Name = object_propertyType_Name_;

			auto object_propertyType_Kind = object_propertyType.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_propertyType_Kind.IsNumber(), "Expected Number");
			auto object_propertyType_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_propertyType_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			propertyType.Kind = object_propertyType_Kind_;

				auto _2 = arguments.at(2);
			TITANIUM_ASSERT_AND_THROW(_2.IsObject(), "Expected Object");
			auto object_ownerType = static_cast<JSObject>(_2);
			::Windows::UI::Xaml::Interop::TypeName ownerType;
			// Assign fields explicitly since we didn't use a constructor

			auto object_ownerType_Name = object_ownerType.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_ownerType_Name.IsString(), "Expected String");
			auto object_ownerType_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_ownerType_Name));

			ownerType.Name = object_ownerType_Name_;

			auto object_ownerType_Kind = object_ownerType.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_ownerType_Kind.IsNumber(), "Expected Number");
			auto object_ownerType_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_ownerType_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			ownerType.Kind = object_ownerType_Kind_;

				auto _3 = arguments.at(3);
			TITANIUM_ASSERT_AND_THROW(_3.IsObject(), "Expected Object");
			auto object_typeMetadata = static_cast<JSObject>(_3);
 
			auto wrapper_typeMetadata = object_typeMetadata.GetPrivate<Windows::UI::Xaml::PropertyMetadata>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto typeMetadata = wrapper_typeMetadata->unwrapWindows_UI_Xaml_PropertyMetadata();

				auto method_result = ::Windows::UI::Xaml::DependencyProperty::Register(name, propertyType, ownerType, typeMetadata);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyProperty::Register with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(DependencyProperty, RegisterAttached)
		{
			auto context = get_context();
			if (arguments.size() == 4) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto name = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_propertyType = static_cast<JSObject>(_1);
			::Windows::UI::Xaml::Interop::TypeName propertyType;
			// Assign fields explicitly since we didn't use a constructor

			auto object_propertyType_Name = object_propertyType.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_propertyType_Name.IsString(), "Expected String");
			auto object_propertyType_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_propertyType_Name));

			propertyType.Name = object_propertyType_Name_;

			auto object_propertyType_Kind = object_propertyType.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_propertyType_Kind.IsNumber(), "Expected Number");
			auto object_propertyType_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_propertyType_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			propertyType.Kind = object_propertyType_Kind_;

				auto _2 = arguments.at(2);
			TITANIUM_ASSERT_AND_THROW(_2.IsObject(), "Expected Object");
			auto object_ownerType = static_cast<JSObject>(_2);
			::Windows::UI::Xaml::Interop::TypeName ownerType;
			// Assign fields explicitly since we didn't use a constructor

			auto object_ownerType_Name = object_ownerType.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_ownerType_Name.IsString(), "Expected String");
			auto object_ownerType_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_ownerType_Name));

			ownerType.Name = object_ownerType_Name_;

			auto object_ownerType_Kind = object_ownerType.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_ownerType_Kind.IsNumber(), "Expected Number");
			auto object_ownerType_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_ownerType_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			ownerType.Kind = object_ownerType_Kind_;

				auto _3 = arguments.at(3);
			TITANIUM_ASSERT_AND_THROW(_3.IsObject(), "Expected Object");
			auto object_defaultMetadata = static_cast<JSObject>(_3);
 
			auto wrapper_defaultMetadata = object_defaultMetadata.GetPrivate<Windows::UI::Xaml::PropertyMetadata>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto defaultMetadata = wrapper_defaultMetadata->unwrapWindows_UI_Xaml_PropertyMetadata();

				auto method_result = ::Windows::UI::Xaml::DependencyProperty::RegisterAttached(name, propertyType, ownerType, defaultMetadata);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched DependencyProperty::RegisterAttached with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
