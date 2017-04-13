/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.IValueConverter
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Data.IValueConverter.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Data
				{

		IValueConverter::IValueConverter(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("IValueConverter::ctor");
		}

		void IValueConverter::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("IValueConverter::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Data::IValueConverter^ IValueConverter::unwrapWindows_UI_Xaml_Data_IValueConverter() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Data::IValueConverter^>(wrapped__);
		}

		::Windows::UI::Xaml::Data::IValueConverter^ IValueConverter::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Data_IValueConverter();
		}

		void IValueConverter::wrap(::Windows::UI::Xaml::Data::IValueConverter^ object)
		{
			wrapped__ = object;
		}

		void IValueConverter::JSExportInitialize()
		{
			JSExport<IValueConverter>::SetClassVersion(1);
			JSExport<IValueConverter>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_FUNCTION(IValueConverter, Convert);
			TITANIUM_ADD_FUNCTION(IValueConverter, ConvertBack);
		}

		TITANIUM_FUNCTION(IValueConverter, Convert)
		{
			auto context = get_context();
			if (arguments.size() == 4) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_targetType = static_cast<JSObject>(_1);
			::Windows::UI::Xaml::Interop::TypeName targetType;
			// Assign fields explicitly since we didn't use a constructor

			auto object_targetType_Name = object_targetType.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_targetType_Name.IsString(), "Expected String");
			auto object_targetType_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_targetType_Name));

			targetType.Name = object_targetType_Name_;

			auto object_targetType_Kind = object_targetType.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_targetType_Kind.IsNumber(), "Expected Number");
			auto object_targetType_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_targetType_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			targetType.Kind = object_targetType_Kind_;

				auto _2 = arguments.at(2);
			TITANIUM_ASSERT_AND_THROW(_2.IsObject(), "Expected Object");
			auto object_parameter = static_cast<JSObject>(_2);
 
			auto wrapper_parameter = object_parameter.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto parameter = wrapper_parameter->unwrapPlatform_Object();

				auto _3 = arguments.at(3); 
			TITANIUM_ASSERT_AND_THROW(_3.IsString(), "Expected String");
			auto language = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_3));

				auto method_result = unwrap()->Convert(value, targetType, parameter, language);

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched IValueConverter::Convert with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(IValueConverter, ConvertBack)
		{
			auto context = get_context();
			if (arguments.size() == 4) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_targetType = static_cast<JSObject>(_1);
			::Windows::UI::Xaml::Interop::TypeName targetType;
			// Assign fields explicitly since we didn't use a constructor

			auto object_targetType_Name = object_targetType.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_targetType_Name.IsString(), "Expected String");
			auto object_targetType_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_targetType_Name));

			targetType.Name = object_targetType_Name_;

			auto object_targetType_Kind = object_targetType.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_targetType_Kind.IsNumber(), "Expected Number");
			auto object_targetType_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_targetType_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			targetType.Kind = object_targetType_Kind_;

				auto _2 = arguments.at(2);
			TITANIUM_ASSERT_AND_THROW(_2.IsObject(), "Expected Object");
			auto object_parameter = static_cast<JSObject>(_2);
 
			auto wrapper_parameter = object_parameter.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto parameter = wrapper_parameter->unwrapPlatform_Object();

				auto _3 = arguments.at(3); 
			TITANIUM_ASSERT_AND_THROW(_3.IsString(), "Expected String");
			auto language = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_3));

				auto method_result = unwrap()->ConvertBack(value, targetType, parameter, language);

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched IValueConverter::ConvertBack with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
