/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.UserControl
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Controls.Control.hpp"
#include "Windows.UI.Xaml.Controls.UserControl.hpp"
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

		UserControl::UserControl(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Controls::Control(js_context)
		{
			TITANIUM_LOG_DEBUG("UserControl::ctor");
		}

		void UserControl::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("UserControl::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Controls::UserControl();
			}

		}

		::Windows::UI::Xaml::Controls::UserControl^ UserControl::unwrapWindows_UI_Xaml_Controls_UserControl() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Controls::UserControl^>(wrapped__);
		}

		::Windows::UI::Xaml::Controls::UserControl^ UserControl::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Controls_UserControl();
		}

		void UserControl::wrap(::Windows::UI::Xaml::Controls::UserControl^ object)
		{
			wrapped__ = object;
		}

		void UserControl::JSExportInitialize()
		{
			JSExport<UserControl>::SetClassVersion(1);
			JSExport<UserControl>::SetParent(JSExport<Windows::UI::Xaml::Controls::Control>::Class());

			TITANIUM_ADD_PROPERTY(UserControl, Content);
			TITANIUM_ADD_PROPERTY_READONLY(UserControl, ContentProperty);
		}

		TITANIUM_PROPERTY_SETTER(UserControl, Content)
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

		TITANIUM_PROPERTY_GETTER(UserControl, Content)
		{
			auto value = unwrap()->Content;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::UIElement>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::UIElement>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UserControl, ContentProperty)
		{
			auto value = unwrap()->ContentProperty;
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
