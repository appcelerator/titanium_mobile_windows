/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.Binding
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Data.Binding.hpp"
#include "Windows.UI.Xaml.Data.BindingBase.hpp"
#include "Windows.UI.Xaml.Data.IValueConverter.hpp"
#include "Windows.UI.Xaml.Data.RelativeSource.hpp"
#include "Windows.UI.Xaml.PropertyPath.hpp"
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

		Binding::Binding(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Data::BindingBase(js_context)
		{
			TITANIUM_LOG_DEBUG("Binding::ctor");
		}

		void Binding::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Binding::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Data::Binding();
			}

		}

		::Windows::UI::Xaml::Data::Binding^ Binding::unwrapWindows_UI_Xaml_Data_Binding() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Data::Binding^>(wrapped__);
		}

		::Windows::UI::Xaml::Data::Binding^ Binding::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Data_Binding();
		}

		void Binding::wrap(::Windows::UI::Xaml::Data::Binding^ object)
		{
			wrapped__ = object;
		}

		void Binding::JSExportInitialize()
		{
			JSExport<Binding>::SetClassVersion(1);
			JSExport<Binding>::SetParent(JSExport<Windows::UI::Xaml::Data::BindingBase>::Class());

			TITANIUM_ADD_PROPERTY(Binding, UpdateSourceTrigger);
			TITANIUM_ADD_PROPERTY(Binding, TargetNullValue);
			TITANIUM_ADD_PROPERTY(Binding, FallbackValue);
			TITANIUM_ADD_PROPERTY(Binding, Source);
			TITANIUM_ADD_PROPERTY(Binding, RelativeSource);
			TITANIUM_ADD_PROPERTY(Binding, Path);
			TITANIUM_ADD_PROPERTY(Binding, Mode);
			TITANIUM_ADD_PROPERTY(Binding, ElementName);
			TITANIUM_ADD_PROPERTY(Binding, ConverterParameter);
			TITANIUM_ADD_PROPERTY(Binding, ConverterLanguage);
			TITANIUM_ADD_PROPERTY(Binding, Converter);
		}

		TITANIUM_PROPERTY_SETTER(Binding, UpdateSourceTrigger)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<::Windows::UI::Xaml::Data::UpdateSourceTrigger>(static_cast<int32_t>(argument)); // TODO Look up enum in metadata to know what type it's value is? 

			unwrap()->UpdateSourceTrigger = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, UpdateSourceTrigger)
		{
			auto value = unwrap()->UpdateSourceTrigger;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, TargetNullValue)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

			unwrap()->TargetNullValue = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, TargetNullValue)
		{
			auto value = unwrap()->TargetNullValue;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, FallbackValue)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

			unwrap()->FallbackValue = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, FallbackValue)
		{
			auto value = unwrap()->FallbackValue;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, Source)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

			unwrap()->Source = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, Source)
		{
			auto value = unwrap()->Source;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, RelativeSource)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Data::RelativeSource>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Data_RelativeSource();

			unwrap()->RelativeSource = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, RelativeSource)
		{
			auto value = unwrap()->RelativeSource;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Data::RelativeSource>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Data::RelativeSource>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, Path)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::PropertyPath>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_PropertyPath();

			unwrap()->Path = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, Path)
		{
			auto value = unwrap()->Path;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::PropertyPath>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::PropertyPath>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, Mode)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<::Windows::UI::Xaml::Data::BindingMode>(static_cast<int32_t>(argument)); // TODO Look up enum in metadata to know what type it's value is? 

			unwrap()->Mode = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, Mode)
		{
			auto value = unwrap()->Mode;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, ElementName)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsString(), "Expected String");
			auto value = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(argument));

			unwrap()->ElementName = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, ElementName)
		{
			auto value = unwrap()->ElementName;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, ConverterParameter)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

			unwrap()->ConverterParameter = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, ConverterParameter)
		{
			auto value = unwrap()->ConverterParameter;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, ConverterLanguage)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsString(), "Expected String");
			auto value = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(argument));

			unwrap()->ConverterLanguage = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, ConverterLanguage)
		{
			auto value = unwrap()->ConverterLanguage;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Binding, Converter)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Data::IValueConverter>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Data_IValueConverter();

			unwrap()->Converter = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Binding, Converter)
		{
			auto value = unwrap()->Converter;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Data::IValueConverter>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Data::IValueConverter>();
			result_wrapper->wrap(value);

			return result;
		}

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
