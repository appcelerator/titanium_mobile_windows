/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Brush
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.Media.Brush.hpp"
#include "Windows.UI.Xaml.Media.Transform.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Media
				{

		Brush::Brush(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("Brush::ctor");
		}

		void Brush::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Brush::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Media::Brush^ Brush::unwrapWindows_UI_Xaml_Media_Brush() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::Brush^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::Brush^ Brush::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_Brush();
		}

		void Brush::wrap(::Windows::UI::Xaml::Media::Brush^ object)
		{
			wrapped__ = object;
		}

		void Brush::JSExportInitialize()
		{
			JSExport<Brush>::SetClassVersion(1);
			JSExport<Brush>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

			TITANIUM_ADD_PROPERTY(Brush, Transform);
			TITANIUM_ADD_PROPERTY(Brush, RelativeTransform);
			TITANIUM_ADD_PROPERTY(Brush, Opacity);
			TITANIUM_ADD_PROPERTY_READONLY(Brush, OpacityProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Brush, RelativeTransformProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Brush, TransformProperty);
		}

		TITANIUM_PROPERTY_SETTER(Brush, Transform)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Transform>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Transform();

			unwrap()->Transform = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Brush, Transform)
		{
			auto value = unwrap()->Transform;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Transform>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Transform>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Brush, RelativeTransform)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Transform>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Transform();

			unwrap()->RelativeTransform = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Brush, RelativeTransform)
		{
			auto value = unwrap()->RelativeTransform;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Transform>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Transform>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Brush, Opacity)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<float>(static_cast<double>(argument));

			unwrap()->Opacity = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Brush, Opacity)
		{
			auto value = unwrap()->Opacity;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<double>(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Brush, OpacityProperty)
		{
			auto value = unwrap()->OpacityProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Brush, RelativeTransformProperty)
		{
			auto value = unwrap()->RelativeTransformProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Brush, TransformProperty)
		{
			auto value = unwrap()->TransformProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
