/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.Panel
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Controls.Panel.hpp"
#include "Windows.UI.Xaml.Controls.UIElementCollection.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.FrameworkElement.hpp"
#include "Windows.UI.Xaml.Media.Animation.TransitionCollection.hpp"
#include "Windows.UI.Xaml.Media.Brush.hpp"
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

		Panel::Panel(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::FrameworkElement(js_context)
		{
			TITANIUM_LOG_DEBUG("Panel::ctor");
		}

		void Panel::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Panel::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Controls::Panel^ Panel::unwrapWindows_UI_Xaml_Controls_Panel() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Controls::Panel^>(wrapped__);
		}

		::Windows::UI::Xaml::Controls::Panel^ Panel::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Controls_Panel();
		}

		void Panel::wrap(::Windows::UI::Xaml::Controls::Panel^ object)
		{
			wrapped__ = object;
		}

		void Panel::JSExportInitialize()
		{
			JSExport<Panel>::SetClassVersion(1);
			JSExport<Panel>::SetParent(JSExport<Windows::UI::Xaml::FrameworkElement>::Class());

			TITANIUM_ADD_PROPERTY(Panel, ChildrenTransitions);
			TITANIUM_ADD_PROPERTY(Panel, Background);
			TITANIUM_ADD_PROPERTY_READONLY(Panel, Children);
			TITANIUM_ADD_PROPERTY_READONLY(Panel, IsItemsHost);
			TITANIUM_ADD_PROPERTY_READONLY(Panel, BackgroundProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Panel, ChildrenTransitionsProperty);
			TITANIUM_ADD_PROPERTY_READONLY(Panel, IsItemsHostProperty);
		}

		TITANIUM_PROPERTY_SETTER(Panel, ChildrenTransitions)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Animation::TransitionCollection>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Animation_TransitionCollection();

			unwrap()->ChildrenTransitions = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Panel, ChildrenTransitions)
		{
			auto value = unwrap()->ChildrenTransitions;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Animation::TransitionCollection>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Animation::TransitionCollection>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(Panel, Background)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Brush>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Brush();

			unwrap()->Background = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Panel, Background)
		{
			auto value = unwrap()->Background;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Brush>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Brush>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Panel, Children)
		{
			auto value = unwrap()->Children;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Controls::UIElementCollection>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Controls::UIElementCollection>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Panel, IsItemsHost)
		{
			auto value = unwrap()->IsItemsHost;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Panel, BackgroundProperty)
		{
			auto value = unwrap()->BackgroundProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Panel, ChildrenTransitionsProperty)
		{
			auto value = unwrap()->ChildrenTransitionsProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Panel, IsItemsHostProperty)
		{
			auto value = unwrap()->IsItemsHostProperty;
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
