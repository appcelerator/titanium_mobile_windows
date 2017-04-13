/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.GeneralTransform
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.Media.GeneralTransform.hpp"
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

		GeneralTransform::GeneralTransform(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("GeneralTransform::ctor");
		}

		void GeneralTransform::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("GeneralTransform::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Media::GeneralTransform^ GeneralTransform::unwrapWindows_UI_Xaml_Media_GeneralTransform() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::GeneralTransform^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::GeneralTransform^ GeneralTransform::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_GeneralTransform();
		}

		void GeneralTransform::wrap(::Windows::UI::Xaml::Media::GeneralTransform^ object)
		{
			wrapped__ = object;
		}

		void GeneralTransform::JSExportInitialize()
		{
			JSExport<GeneralTransform>::SetClassVersion(1);
			JSExport<GeneralTransform>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(GeneralTransform, Inverse);
			TITANIUM_ADD_PROPERTY_READONLY(GeneralTransform, InverseCore);
			TITANIUM_ADD_FUNCTION(GeneralTransform, TransformPoint);
			TITANIUM_ADD_FUNCTION(GeneralTransform, TryTransform);
			TITANIUM_ADD_FUNCTION(GeneralTransform, TransformBounds);
		}

		TITANIUM_PROPERTY_GETTER(GeneralTransform, Inverse)
		{
			auto value = unwrap()->Inverse;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::GeneralTransform>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::GeneralTransform>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(GeneralTransform, InverseCore)
		{
			auto value = unwrap()->InverseCore;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::GeneralTransform>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::GeneralTransform>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(GeneralTransform, TransformPoint)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_point = static_cast<JSObject>(_0);
			::Windows::Foundation::Point point;
			// Assign fields explicitly since we didn't use a constructor

			auto object_point_X = object_point.GetProperty("X"); 
			TITANIUM_ASSERT_AND_THROW(object_point_X.IsNumber(), "Expected Number");
			auto object_point_X_ = static_cast<float>(static_cast<double>(object_point_X));

			point.X = object_point_X_;

			auto object_point_Y = object_point.GetProperty("Y"); 
			TITANIUM_ASSERT_AND_THROW(object_point_Y.IsNumber(), "Expected Number");
			auto object_point_Y_ = static_cast<float>(static_cast<double>(object_point_Y));

			point.Y = object_point_Y_;

				auto method_result = unwrap()->TransformPoint(point);

			auto result = context.CreateObject();


			auto method_result_X_ = context.CreateNumber(static_cast<double>(method_result.X));

			result.SetProperty("X", method_result_X_);



			auto method_result_Y_ = context.CreateNumber(static_cast<double>(method_result.Y));

			result.SetProperty("Y", method_result_Y_);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched GeneralTransform::TransformPoint with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(GeneralTransform, TryTransform)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_inPoint = static_cast<JSObject>(_0);
			::Windows::Foundation::Point inPoint;
			// Assign fields explicitly since we didn't use a constructor

			auto object_inPoint_X = object_inPoint.GetProperty("X"); 
			TITANIUM_ASSERT_AND_THROW(object_inPoint_X.IsNumber(), "Expected Number");
			auto object_inPoint_X_ = static_cast<float>(static_cast<double>(object_inPoint_X));

			inPoint.X = object_inPoint_X_;

			auto object_inPoint_Y = object_inPoint.GetProperty("Y"); 
			TITANIUM_ASSERT_AND_THROW(object_inPoint_Y.IsNumber(), "Expected Number");
			auto object_inPoint_Y_ = static_cast<float>(static_cast<double>(object_inPoint_Y));

			inPoint.Y = object_inPoint_Y_;

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_outPoint = static_cast<JSObject>(_1);
			::Windows::Foundation::Point outPoint;
			// Assign fields explicitly since we didn't use a constructor

			auto object_outPoint_X = object_outPoint.GetProperty("X"); 
			TITANIUM_ASSERT_AND_THROW(object_outPoint_X.IsNumber(), "Expected Number");
			auto object_outPoint_X_ = static_cast<float>(static_cast<double>(object_outPoint_X));

			outPoint.X = object_outPoint_X_;

			auto object_outPoint_Y = object_outPoint.GetProperty("Y"); 
			TITANIUM_ASSERT_AND_THROW(object_outPoint_Y.IsNumber(), "Expected Number");
			auto object_outPoint_Y_ = static_cast<float>(static_cast<double>(object_outPoint_Y));

			outPoint.Y = object_outPoint_Y_;

				auto method_result = unwrap()->TryTransform(inPoint, &outPoint);
 
			auto result = context.CreateBoolean(method_result); 



			auto out_1 = context.CreateObject();


			auto outPoint_X_ = context.CreateNumber(static_cast<double>(outPoint.X));

			out_1.SetProperty("X", outPoint_X_);



			auto outPoint_Y_ = context.CreateNumber(static_cast<double>(outPoint.Y));

			out_1.SetProperty("Y", outPoint_Y_);

				_1 = out_1;
				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched GeneralTransform::TryTransform with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(GeneralTransform, TransformBounds)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_rect = static_cast<JSObject>(_0);
			::Windows::Foundation::Rect rect;
			// Assign fields explicitly since we didn't use a constructor

			auto object_rect_X = object_rect.GetProperty("X"); 
			TITANIUM_ASSERT_AND_THROW(object_rect_X.IsNumber(), "Expected Number");
			auto object_rect_X_ = static_cast<float>(static_cast<double>(object_rect_X));

			rect.X = object_rect_X_;

			auto object_rect_Y = object_rect.GetProperty("Y"); 
			TITANIUM_ASSERT_AND_THROW(object_rect_Y.IsNumber(), "Expected Number");
			auto object_rect_Y_ = static_cast<float>(static_cast<double>(object_rect_Y));

			rect.Y = object_rect_Y_;

			auto object_rect_Width = object_rect.GetProperty("Width"); 
			TITANIUM_ASSERT_AND_THROW(object_rect_Width.IsNumber(), "Expected Number");
			auto object_rect_Width_ = static_cast<float>(static_cast<double>(object_rect_Width));

			rect.Width = object_rect_Width_;

			auto object_rect_Height = object_rect.GetProperty("Height"); 
			TITANIUM_ASSERT_AND_THROW(object_rect_Height.IsNumber(), "Expected Number");
			auto object_rect_Height_ = static_cast<float>(static_cast<double>(object_rect_Height));

			rect.Height = object_rect_Height_;

				auto method_result = unwrap()->TransformBounds(rect);

			auto result = context.CreateObject();


			auto method_result_X_ = context.CreateNumber(static_cast<double>(method_result.X));

			result.SetProperty("X", method_result_X_);



			auto method_result_Y_ = context.CreateNumber(static_cast<double>(method_result.Y));

			result.SetProperty("Y", method_result_Y_);



			auto method_result_Width_ = context.CreateNumber(static_cast<double>(method_result.Width));

			result.SetProperty("Width", method_result_Width_);



			auto method_result_Height_ = context.CreateNumber(static_cast<double>(method_result.Height));

			result.SetProperty("Height", method_result_Height_);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched GeneralTransform::TransformBounds with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
