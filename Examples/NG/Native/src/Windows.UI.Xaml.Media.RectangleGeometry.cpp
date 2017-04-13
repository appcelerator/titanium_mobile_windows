/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.RectangleGeometry
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.Media.Geometry.hpp"
#include "Windows.UI.Xaml.Media.RectangleGeometry.hpp"
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

		RectangleGeometry::RectangleGeometry(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Media::Geometry(js_context)
		{
			TITANIUM_LOG_DEBUG("RectangleGeometry::ctor");
		}

		void RectangleGeometry::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("RectangleGeometry::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Media::RectangleGeometry();
			}

		}

		::Windows::UI::Xaml::Media::RectangleGeometry^ RectangleGeometry::unwrapWindows_UI_Xaml_Media_RectangleGeometry() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::RectangleGeometry^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::RectangleGeometry^ RectangleGeometry::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_RectangleGeometry();
		}

		void RectangleGeometry::wrap(::Windows::UI::Xaml::Media::RectangleGeometry^ object)
		{
			wrapped__ = object;
		}

		void RectangleGeometry::JSExportInitialize()
		{
			JSExport<RectangleGeometry>::SetClassVersion(1);
			JSExport<RectangleGeometry>::SetParent(JSExport<Windows::UI::Xaml::Media::Geometry>::Class());

			TITANIUM_ADD_PROPERTY(RectangleGeometry, Rect);
			TITANIUM_ADD_PROPERTY_READONLY(RectangleGeometry, RectProperty);
		}

		TITANIUM_PROPERTY_SETTER(RectangleGeometry, Rect)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
			::Windows::Foundation::Rect value;
			// Assign fields explicitly since we didn't use a constructor

			auto object_value_X = object_value.GetProperty("X"); 
			TITANIUM_ASSERT_AND_THROW(object_value_X.IsNumber(), "Expected Number");
			auto object_value_X_ = static_cast<float>(static_cast<double>(object_value_X));

			value.X = object_value_X_;

			auto object_value_Y = object_value.GetProperty("Y"); 
			TITANIUM_ASSERT_AND_THROW(object_value_Y.IsNumber(), "Expected Number");
			auto object_value_Y_ = static_cast<float>(static_cast<double>(object_value_Y));

			value.Y = object_value_Y_;

			auto object_value_Width = object_value.GetProperty("Width"); 
			TITANIUM_ASSERT_AND_THROW(object_value_Width.IsNumber(), "Expected Number");
			auto object_value_Width_ = static_cast<float>(static_cast<double>(object_value_Width));

			value.Width = object_value_Width_;

			auto object_value_Height = object_value.GetProperty("Height"); 
			TITANIUM_ASSERT_AND_THROW(object_value_Height.IsNumber(), "Expected Number");
			auto object_value_Height_ = static_cast<float>(static_cast<double>(object_value_Height));

			value.Height = object_value_Height_;

			unwrap()->Rect = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(RectangleGeometry, Rect)
		{
			auto value = unwrap()->Rect;
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

		TITANIUM_PROPERTY_GETTER(RectangleGeometry, RectProperty)
		{
			auto value = unwrap()->RectProperty;
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
