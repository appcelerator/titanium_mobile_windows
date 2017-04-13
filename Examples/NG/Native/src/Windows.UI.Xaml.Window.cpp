/**
 * Windows Native Wrapper for Windows.UI.Xaml.Window
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Core.CoreDispatcher.hpp"
#include "Windows.UI.Core.CoreWindow.hpp"
#include "Windows.UI.Xaml.UIElement.hpp"
#include "Windows.UI.Xaml.Window.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("Window::ctor");
		}

		void Window::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Window::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Window^ Window::unwrapWindows_UI_Xaml_Window() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Window^>(wrapped__);
		}

		::Windows::UI::Xaml::Window^ Window::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Window();
		}

		void Window::wrap(::Windows::UI::Xaml::Window^ object)
		{
			wrapped__ = object;
		}

		void Window::JSExportInitialize()
		{
			JSExport<Window>::SetClassVersion(1);
			JSExport<Window>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY(Window, Content);
			TITANIUM_ADD_PROPERTY_READONLY(Window, Bounds);
			TITANIUM_ADD_PROPERTY_READONLY(Window, CoreWindow);
			TITANIUM_ADD_PROPERTY_READONLY(Window, Dispatcher);
			TITANIUM_ADD_PROPERTY_READONLY(Window, Visible);
			TITANIUM_ADD_PROPERTY_READONLY(Window, Current);
			TITANIUM_ADD_FUNCTION(Window, Activate);
			TITANIUM_ADD_FUNCTION(Window, Close);
		}

		TITANIUM_PROPERTY_SETTER(Window, Content)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_UIElement();

			unwrap()->Content = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, Content)
		{
			auto value = unwrap()->Content;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::UIElement>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::UIElement>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Window, Bounds)
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

		TITANIUM_PROPERTY_GETTER(Window, CoreWindow)
		{
			auto value = unwrap()->CoreWindow;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Core::CoreWindow>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Core::CoreWindow>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Window, Dispatcher)
		{
			auto value = unwrap()->Dispatcher;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Core::CoreDispatcher>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Core::CoreDispatcher>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Window, Visible)
		{
			auto value = unwrap()->Visible;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Window, Current)
		{
			auto value = unwrap()->Current;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Window>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Window>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(Window, Activate)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Activate();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Window::Activate with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Window, Close)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->Close();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Window::Close with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
