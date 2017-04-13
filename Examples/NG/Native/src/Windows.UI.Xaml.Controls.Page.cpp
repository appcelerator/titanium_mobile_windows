/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.Page
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Controls.AppBar.hpp"
#include "Windows.UI.Xaml.Controls.Frame.hpp"
#include "Windows.UI.Xaml.Controls.Page.hpp"
#include "Windows.UI.Xaml.Controls.UserControl.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
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

		Page::Page(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Controls::UserControl(js_context)
		{
			TITANIUM_LOG_DEBUG("Page::ctor");
		}

		void Page::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Page::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Controls::Page();
			}

		}

		::Windows::UI::Xaml::Controls::Page^ Page::unwrapWindows_UI_Xaml_Controls_Page() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Controls::Page^>(wrapped__);
		}

		::Windows::UI::Xaml::Controls::Page^ Page::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Controls_Page();
		}

		void Page::wrap(::Windows::UI::Xaml::Controls::Page^ object)
		{
			wrapped__ = object;
		}

		void Page::JSExportInitialize()
		{
			JSExport<Page>::SetClassVersion(1);
			JSExport<Page>::SetParent(JSExport<Windows::UI::Xaml::Controls::UserControl>::Class());

			TITANIUM_ADD_PROPERTY(Page, TopAppBar);
			TITANIUM_ADD_PROPERTY(Page, NavigationCacheMode);
			TITANIUM_ADD_PROPERTY(Page, BottomAppBar);
			TITANIUM_ADD_PROPERTY_READONLY(Page, Frame);
			TITANIUM_ADD_PROPERTY_READONLY(Page, BottomAppBarProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Page, FrameProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Page, TopAppBarProperty);
		}

		TITANIUM_PROPERTY_SETTER(Page, TopAppBar)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Controls::AppBar>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Controls_AppBar();

			unwrap()->TopAppBar = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Page, TopAppBar)
		{
			auto value = unwrap()->TopAppBar;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Controls::AppBar>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Controls::AppBar>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Page, NavigationCacheMode)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<::Windows::UI::Xaml::Navigation::NavigationCacheMode>(static_cast<int32_t>(argument)); // TODO Look up enum in metadata to know what type it's value is? 

			unwrap()->NavigationCacheMode = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Page, NavigationCacheMode)
		{
			auto value = unwrap()->NavigationCacheMode;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Page, BottomAppBar)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Controls::AppBar>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Controls_AppBar();

			unwrap()->BottomAppBar = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Page, BottomAppBar)
		{
			auto value = unwrap()->BottomAppBar;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Controls::AppBar>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Controls::AppBar>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Page, Frame)
		{
			auto value = unwrap()->Frame;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Controls::Frame>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Controls::Frame>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Page, BottomAppBarProperty)
		{
			auto value = unwrap()->BottomAppBarProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Page, FrameProperty)
		{
			auto value = unwrap()->FrameProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Page, TopAppBarProperty)
		{
			auto value = unwrap()->TopAppBarProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
