/**
 * Windows Native Wrapper for Windows.UI.Xaml.Style
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.SetterBaseCollection.hpp"
#include "Windows.UI.Xaml.Style.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		Style::Style(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("Style::ctor");
		}

		void Style::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Style::postCallAsConstructor ", this);
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_targetType = static_cast<JSObject>(_0);
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

				wrapped__ = ref new ::Windows::UI::Xaml::Style(targetType);
			}
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Style();
			}

		}

		::Windows::UI::Xaml::Style^ Style::unwrapWindows_UI_Xaml_Style() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Style^>(wrapped__);
		}

		::Windows::UI::Xaml::Style^ Style::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Style();
		}

		void Style::wrap(::Windows::UI::Xaml::Style^ object)
		{
			wrapped__ = object;
		}

		void Style::JSExportInitialize()
		{
			JSExport<Style>::SetClassVersion(1);
			JSExport<Style>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

			TITANIUM_ADD_PROPERTY(Style, TargetType);
			TITANIUM_ADD_PROPERTY(Style, BasedOn);
			TITANIUM_ADD_PROPERTY_READONLY(Style, IsSealed);
			TITANIUM_ADD_PROPERTY_READONLY(Style, Setters);
			TITANIUM_ADD_FUNCTION(Style, Seal);
		}

		TITANIUM_PROPERTY_SETTER(Style, TargetType)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
			::Windows::UI::Xaml::Interop::TypeName value;
			// Assign fields explicitly since we didn't use a constructor

			auto object_value_Name = object_value.GetProperty("Name"); 
			TITANIUM_ASSERT_AND_THROW(object_value_Name.IsString(), "Expected String");
			auto object_value_Name_ = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(object_value_Name));

			value.Name = object_value_Name_;

			auto object_value_Kind = object_value.GetProperty("Kind");
			TITANIUM_ASSERT_AND_THROW(object_value_Kind.IsNumber(), "Expected Number");
			auto object_value_Kind_ = static_cast<::Windows::UI::Xaml::Interop::TypeKind>(static_cast<int32_t>(object_value_Kind)); // TODO Look up enum in metadata to know what type it's value is? 

			value.Kind = object_value_Kind_;

			unwrap()->TargetType = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Style, TargetType)
		{
			auto value = unwrap()->TargetType;
			auto context = get_context();

			auto result = context.CreateObject();

 
			auto value_Name_ = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value.Name));

			result.SetProperty("Name", value_Name_);



			auto value_Kind_ = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value.Kind))); // FIXME What if the enum isn't an int based one?!

			result.SetProperty("Kind", value_Kind_);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Style, BasedOn)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Style>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Style();

			unwrap()->BasedOn = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Style, BasedOn)
		{
			auto value = unwrap()->BasedOn;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Style>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Style>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Style, IsSealed)
		{
			auto value = unwrap()->IsSealed;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Style, Setters)
		{
			auto value = unwrap()->Setters;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::SetterBaseCollection>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::SetterBaseCollection>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(Style, Seal)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Seal();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Style::Seal with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
