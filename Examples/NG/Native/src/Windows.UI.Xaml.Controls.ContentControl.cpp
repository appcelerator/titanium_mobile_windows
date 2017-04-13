/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.ContentControl
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Controls.ContentControl.hpp"
#include "Windows.UI.Xaml.Controls.Control.hpp"
#include "Windows.UI.Xaml.Controls.DataTemplateSelector.hpp"
#include "Windows.UI.Xaml.DataTemplate.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.Media.Animation.TransitionCollection.hpp"
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

		ContentControl::ContentControl(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Controls::Control(js_context)
		{
			TITANIUM_LOG_DEBUG("ContentControl::ctor");
		}

		void ContentControl::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("ContentControl::postCallAsConstructor ", this);
			if (arguments.size() == 0) {

				wrapped__ = ref new ::Windows::UI::Xaml::Controls::ContentControl();
			}

		}

		::Windows::UI::Xaml::Controls::ContentControl^ ContentControl::unwrapWindows_UI_Xaml_Controls_ContentControl() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Controls::ContentControl^>(wrapped__);
		}

		::Windows::UI::Xaml::Controls::ContentControl^ ContentControl::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Controls_ContentControl();
		}

		void ContentControl::wrap(::Windows::UI::Xaml::Controls::ContentControl^ object)
		{
			wrapped__ = object;
		}

		void ContentControl::JSExportInitialize()
		{
			JSExport<ContentControl>::SetClassVersion(1);
			JSExport<ContentControl>::SetParent(JSExport<Windows::UI::Xaml::Controls::Control>::Class());

			TITANIUM_ADD_PROPERTY(ContentControl, ContentTransitions);
			TITANIUM_ADD_PROPERTY(ContentControl, ContentTemplateSelector);
			TITANIUM_ADD_PROPERTY(ContentControl, ContentTemplate);
			TITANIUM_ADD_PROPERTY(ContentControl, Content);
			TITANIUM_ADD_PROPERTY_READONLY(ContentControl, ContentTemplateRoot);
			TITANIUM_ADD_PROPERTY_READONLY(ContentControl, ContentProperty);
			TITANIUM_ADD_PROPERTY_READONLY(ContentControl, ContentTemplateProperty);
			TITANIUM_ADD_PROPERTY_READONLY(ContentControl, ContentTemplateSelectorProperty);
			TITANIUM_ADD_PROPERTY_READONLY(ContentControl, ContentTransitionsProperty);
		}

		TITANIUM_PROPERTY_SETTER(ContentControl, ContentTransitions)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Animation::TransitionCollection>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Animation_TransitionCollection();

			unwrap()->ContentTransitions = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentTransitions)
		{
			auto value = unwrap()->ContentTransitions;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Animation::TransitionCollection>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Animation::TransitionCollection>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(ContentControl, ContentTemplateSelector)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Controls::DataTemplateSelector>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Controls_DataTemplateSelector();

			unwrap()->ContentTemplateSelector = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentTemplateSelector)
		{
			auto value = unwrap()->ContentTemplateSelector;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Controls::DataTemplateSelector>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Controls::DataTemplateSelector>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(ContentControl, ContentTemplate)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::DataTemplate>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_DataTemplate();

			unwrap()->ContentTemplate = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentTemplate)
		{
			auto value = unwrap()->ContentTemplate;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DataTemplate>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DataTemplate>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(ContentControl, Content)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapPlatform_Object();

			unwrap()->Content = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, Content)
		{
			auto value = unwrap()->Content;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Platform::Object>::Class());
			auto result_wrapper = result.GetPrivate<Platform::Object>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentTemplateRoot)
		{
			auto value = unwrap()->ContentTemplateRoot;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::UIElement>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::UIElement>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentProperty)
		{
			auto value = unwrap()->ContentProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentTemplateProperty)
		{
			auto value = unwrap()->ContentTemplateProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentTemplateSelectorProperty)
		{
			auto value = unwrap()->ContentTemplateSelectorProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(ContentControl, ContentTransitionsProperty)
		{
			auto value = unwrap()->ContentTransitionsProperty;
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
