/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.SolidColorBrush
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.Media.Brush.hpp"
#include "Windows.UI.Xaml.Media.SolidColorBrush.hpp"
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

		SolidColorBrush::SolidColorBrush(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Media::Brush(js_context)
		{
			TITANIUM_LOG_DEBUG("SolidColorBrush::ctor");
		}

		void SolidColorBrush::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("SolidColorBrush::postCallAsConstructor ", this);
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_color = static_cast<JSObject>(_0);
			::Windows::UI::Color color;
			// Assign fields explicitly since we didn't use a constructor

			auto object_color_A = object_color.GetProperty("A"); 
			TITANIUM_ASSERT_AND_THROW(object_color_A.IsNumber(), "Expected Number");
			auto object_color_A_ = static_cast<uint32_t>(object_color_A);

			color.A = object_color_A_;

			auto object_color_R = object_color.GetProperty("R"); 
			TITANIUM_ASSERT_AND_THROW(object_color_R.IsNumber(), "Expected Number");
			auto object_color_R_ = static_cast<uint32_t>(object_color_R);

			color.R = object_color_R_;

			auto object_color_G = object_color.GetProperty("G"); 
			TITANIUM_ASSERT_AND_THROW(object_color_G.IsNumber(), "Expected Number");
			auto object_color_G_ = static_cast<uint32_t>(object_color_G);

			color.G = object_color_G_;

			auto object_color_B = object_color.GetProperty("B"); 
			TITANIUM_ASSERT_AND_THROW(object_color_B.IsNumber(), "Expected Number");
			auto object_color_B_ = static_cast<uint32_t>(object_color_B);

			color.B = object_color_B_;

				wrapped__ = ref new ::Windows::UI::Xaml::Media::SolidColorBrush(color);
			}
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Media::SolidColorBrush();
			}

		}

		::Windows::UI::Xaml::Media::SolidColorBrush^ SolidColorBrush::unwrapWindows_UI_Xaml_Media_SolidColorBrush() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::SolidColorBrush^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::SolidColorBrush^ SolidColorBrush::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_SolidColorBrush();
		}

		void SolidColorBrush::wrap(::Windows::UI::Xaml::Media::SolidColorBrush^ object)
		{
			wrapped__ = object;
		}

		void SolidColorBrush::JSExportInitialize()
		{
			JSExport<SolidColorBrush>::SetClassVersion(1);
			JSExport<SolidColorBrush>::SetParent(JSExport<Windows::UI::Xaml::Media::Brush>::Class());

			TITANIUM_ADD_PROPERTY(SolidColorBrush, Color);
			TITANIUM_ADD_PROPERTY_READONLY(SolidColorBrush, ColorProperty);
		}

		TITANIUM_PROPERTY_SETTER(SolidColorBrush, Color)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
			::Windows::UI::Color value;
			// Assign fields explicitly since we didn't use a constructor

			auto object_value_A = object_value.GetProperty("A"); 
			TITANIUM_ASSERT_AND_THROW(object_value_A.IsNumber(), "Expected Number");
			auto object_value_A_ = static_cast<uint32_t>(object_value_A);

			value.A = object_value_A_;

			auto object_value_R = object_value.GetProperty("R"); 
			TITANIUM_ASSERT_AND_THROW(object_value_R.IsNumber(), "Expected Number");
			auto object_value_R_ = static_cast<uint32_t>(object_value_R);

			value.R = object_value_R_;

			auto object_value_G = object_value.GetProperty("G"); 
			TITANIUM_ASSERT_AND_THROW(object_value_G.IsNumber(), "Expected Number");
			auto object_value_G_ = static_cast<uint32_t>(object_value_G);

			value.G = object_value_G_;

			auto object_value_B = object_value.GetProperty("B"); 
			TITANIUM_ASSERT_AND_THROW(object_value_B.IsNumber(), "Expected Number");
			auto object_value_B_ = static_cast<uint32_t>(object_value_B);

			value.B = object_value_B_;

			unwrap()->Color = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(SolidColorBrush, Color)
		{
			auto value = unwrap()->Color;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_A_ = context.CreateNumber(static_cast<uint32_t>(value.A));

			result.SetProperty("A", value_A_);



			auto value_R_ = context.CreateNumber(static_cast<uint32_t>(value.R));

			result.SetProperty("R", value_R_);



			auto value_G_ = context.CreateNumber(static_cast<uint32_t>(value.G));

			result.SetProperty("G", value_G_);



			auto value_B_ = context.CreateNumber(static_cast<uint32_t>(value.B));

			result.SetProperty("B", value_B_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(SolidColorBrush, ColorProperty)
		{
			auto value = unwrap()->ColorProperty;
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
