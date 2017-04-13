/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.Geometry
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.Media.Geometry.hpp"
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

		Geometry::Geometry(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("Geometry::ctor");
		}

		void Geometry::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Geometry::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Media::Geometry^ Geometry::unwrapWindows_UI_Xaml_Media_Geometry() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::Geometry^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::Geometry^ Geometry::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_Geometry();
		}

		void Geometry::wrap(::Windows::UI::Xaml::Media::Geometry^ object)
		{
			wrapped__ = object;
		}

		void Geometry::JSExportInitialize()
		{
			JSExport<Geometry>::SetClassVersion(1);
			JSExport<Geometry>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

			TITANIUM_ADD_PROPERTY(Geometry, Transform);
			TITANIUM_ADD_PROPERTY_READONLY(Geometry, Bounds);
			TITANIUM_ADD_PROPERTY_READONLY(Geometry, Empty);
			TITANIUM_ADD_PROPERTY_READONLY(Geometry, StandardFlatteningTolerance);
			TITANIUM_ADD_PROPERTY_READONLY(Geometry, TransformProperty);
		}

		TITANIUM_PROPERTY_SETTER(Geometry, Transform)
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

		TITANIUM_PROPERTY_GETTER(Geometry, Transform)
		{
			auto value = unwrap()->Transform;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Transform>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Transform>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Geometry, Bounds)
		{
			auto value = unwrap()->Bounds;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_X_ = context.CreateNumber(static_cast<double>(value.X));

			result.SetProperty("X", value_X_);



			auto value_Y_ = context.CreateNumber(static_cast<double>(value.Y));

			result.SetProperty("Y", value_Y_);



			auto value_Width_ = context.CreateNumber(static_cast<double>(value.Width));

			result.SetProperty("Width", value_Width_);



			auto value_Height_ = context.CreateNumber(static_cast<double>(value.Height));

			result.SetProperty("Height", value_Height_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Geometry, Empty)
		{
			auto value = unwrap()->Empty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Geometry>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Geometry>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Geometry, StandardFlatteningTolerance)
		{
			auto value = unwrap()->StandardFlatteningTolerance;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Geometry, TransformProperty)
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
