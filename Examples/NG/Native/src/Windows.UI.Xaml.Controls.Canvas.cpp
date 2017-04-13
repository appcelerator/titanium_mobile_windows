/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.Canvas
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Controls.Canvas.hpp"
#include "Windows.UI.Xaml.Controls.Panel.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.UIElement.hpp"
#include "Titanium/detail/TiImpl.hpp"

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

		Canvas::Canvas(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Controls::Panel(js_context)
		{
			TITANIUM_LOG_DEBUG("Canvas::ctor");
		}

		void Canvas::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Canvas::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Controls::Canvas();
			}

		}

		::Windows::UI::Xaml::Controls::Canvas^ Canvas::unwrapWindows_UI_Xaml_Controls_Canvas() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Controls::Canvas^>(wrapped__);
		}

		::Windows::UI::Xaml::Controls::Canvas^ Canvas::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Controls_Canvas();
		}

		void Canvas::wrap(::Windows::UI::Xaml::Controls::Canvas^ object)
		{
			wrapped__ = object;
		}

		void Canvas::JSExportInitialize()
		{
			JSExport<Canvas>::SetClassVersion(1);
			JSExport<Canvas>::SetParent(JSExport<Windows::UI::Xaml::Controls::Panel>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Canvas, LeftProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Canvas, TopProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Canvas, ZIndexProperty);
			TITANIUM_ADD_FUNCTION(Canvas, GetLeft);
			TITANIUM_ADD_FUNCTION(Canvas, SetLeft);
			TITANIUM_ADD_FUNCTION(Canvas, GetTop);
			TITANIUM_ADD_FUNCTION(Canvas, SetTop);
			TITANIUM_ADD_FUNCTION(Canvas, GetZIndex);
			TITANIUM_ADD_FUNCTION(Canvas, SetZIndex);
		}

		TITANIUM_PROPERTY_GETTER(Canvas, LeftProperty)
		{
			auto value = unwrap()->LeftProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Canvas, TopProperty)
		{
			auto value = unwrap()->TopProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Canvas, ZIndexProperty)
		{
			auto value = unwrap()->ZIndexProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(Canvas, GetLeft)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_element = static_cast<JSObject>(_0);
 
			auto wrapper_element = object_element.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto element = wrapper_element->unwrapWindows_UI_Xaml_UIElement();

				auto method_result = ::Windows::UI::Xaml::Controls::Canvas::GetLeft(element);

			auto result = context.CreateNumber(static_cast<double>(method_result));

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Canvas::GetLeft with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Canvas, SetLeft)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_element = static_cast<JSObject>(_0);
 
			auto wrapper_element = object_element.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto element = wrapper_element->unwrapWindows_UI_Xaml_UIElement();

				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto length = static_cast<float>(static_cast<double>(_1));

				::Windows::UI::Xaml::Controls::Canvas::SetLeft(element, length);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Canvas::SetLeft with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Canvas, GetTop)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_element = static_cast<JSObject>(_0);
 
			auto wrapper_element = object_element.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto element = wrapper_element->unwrapWindows_UI_Xaml_UIElement();

				auto method_result = ::Windows::UI::Xaml::Controls::Canvas::GetTop(element);

			auto result = context.CreateNumber(static_cast<double>(method_result));

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Canvas::GetTop with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Canvas, SetTop)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_element = static_cast<JSObject>(_0);
 
			auto wrapper_element = object_element.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto element = wrapper_element->unwrapWindows_UI_Xaml_UIElement();

				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto length = static_cast<float>(static_cast<double>(_1));

				::Windows::UI::Xaml::Controls::Canvas::SetTop(element, length);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Canvas::SetTop with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Canvas, GetZIndex)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_element = static_cast<JSObject>(_0);
 
			auto wrapper_element = object_element.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto element = wrapper_element->unwrapWindows_UI_Xaml_UIElement();

				auto method_result = ::Windows::UI::Xaml::Controls::Canvas::GetZIndex(element);
 
			auto result = context.CreateNumber(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Canvas::GetZIndex with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Canvas, SetZIndex)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_element = static_cast<JSObject>(_0);
 
			auto wrapper_element = object_element.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto element = wrapper_element->unwrapWindows_UI_Xaml_UIElement();

				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto value = static_cast<int32_t>(_1);

				::Windows::UI::Xaml::Controls::Canvas::SetZIndex(element, value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Canvas::SetZIndex with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
