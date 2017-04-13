/**
 * Windows Native Wrapper for Platform.Object
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

// INSERT_INCLUDES
#include "Titanium/detail/TiImpl.hpp"
#include "Platform.Object.hpp"
#include "Windows.Foundation.AsyncActionCompletedHandler.hpp"
#include "Windows.Foundation.Collections.IPropertySet.hpp"
#include "Windows.Foundation.IAsyncAction.hpp"
#include "Windows.Foundation.IWwwFormUrlDecoderEntry.hpp"
#include "Windows.Foundation.Uri.hpp"
#include "Windows.Foundation.WwwFormUrlDecoder.hpp"
#include "Windows.UI.Colors.hpp"
#include "Windows.UI.Core.CoreCursor.hpp"
#include "Windows.UI.Core.CoreDispatcher.hpp"
#include "Windows.UI.Core.CoreWindow.hpp"
#include "Windows.UI.Core.DispatchedHandler.hpp"
#include "Windows.UI.Core.IdleDispatchedHandler.hpp"
#include "Windows.UI.Core.IdleDispatchedHandlerArgs.hpp"
#include "Windows.UI.Xaml.Controls.AppBar.hpp"
#include "Windows.UI.Xaml.Controls.Canvas.hpp"
#include "Windows.UI.Xaml.Controls.ContentControl.hpp"
#include "Windows.UI.Xaml.Controls.Control.hpp"
#include "Windows.UI.Xaml.Controls.ControlTemplate.hpp"
#include "Windows.UI.Xaml.Controls.DataTemplateSelector.hpp"
#include "Windows.UI.Xaml.Controls.Frame.hpp"
#include "Windows.UI.Xaml.Controls.Page.hpp"
#include "Windows.UI.Xaml.Controls.Panel.hpp"
#include "Windows.UI.Xaml.Controls.TextBlock.hpp"
#include "Windows.UI.Xaml.Controls.UIElementCollection.hpp"
#include "Windows.UI.Xaml.Controls.UserControl.hpp"
#include "Windows.UI.Xaml.CreateDefaultValueCallback.hpp"
#include "Windows.UI.Xaml.Data.Binding.hpp"
#include "Windows.UI.Xaml.Data.BindingBase.hpp"
#include "Windows.UI.Xaml.Data.BindingExpression.hpp"
#include "Windows.UI.Xaml.Data.BindingExpressionBase.hpp"
#include "Windows.UI.Xaml.Data.IValueConverter.hpp"
#include "Windows.UI.Xaml.Data.RelativeSource.hpp"
#include "Windows.UI.Xaml.DataTemplate.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.DependencyPropertyChangedEventArgs.hpp"
#include "Windows.UI.Xaml.Documents.Inline.hpp"
#include "Windows.UI.Xaml.Documents.InlineCollection.hpp"
#include "Windows.UI.Xaml.Documents.TextElement.hpp"
#include "Windows.UI.Xaml.Documents.TextPointer.hpp"
#include "Windows.UI.Xaml.FrameworkElement.hpp"
#include "Windows.UI.Xaml.FrameworkTemplate.hpp"
#include "Windows.UI.Xaml.Input.Pointer.hpp"
#include "Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo.hpp"
#include "Windows.UI.Xaml.Media.Animation.Transition.hpp"
#include "Windows.UI.Xaml.Media.Animation.TransitionCollection.hpp"
#include "Windows.UI.Xaml.Media.Brush.hpp"
#include "Windows.UI.Xaml.Media.CacheMode.hpp"
#include "Windows.UI.Xaml.Media.FontFamily.hpp"
#include "Windows.UI.Xaml.Media.GeneralTransform.hpp"
#include "Windows.UI.Xaml.Media.Geometry.hpp"
#include "Windows.UI.Xaml.Media.Projection.hpp"
#include "Windows.UI.Xaml.Media.RectangleGeometry.hpp"
#include "Windows.UI.Xaml.Media.SolidColorBrush.hpp"
#include "Windows.UI.Xaml.Media.Transform.hpp"
#include "Windows.UI.Xaml.Navigation.PageStackEntry.hpp"
#include "Windows.UI.Xaml.PropertyChangedCallback.hpp"
#include "Windows.UI.Xaml.PropertyMetadata.hpp"
#include "Windows.UI.Xaml.PropertyPath.hpp"
#include "Windows.UI.Xaml.ResourceDictionary.hpp"
#include "Windows.UI.Xaml.RoutedEvent.hpp"
#include "Windows.UI.Xaml.SetterBase.hpp"
#include "Windows.UI.Xaml.SetterBaseCollection.hpp"
#include "Windows.UI.Xaml.Style.hpp"
#include "Windows.UI.Xaml.TriggerBase.hpp"
#include "Windows.UI.Xaml.TriggerCollection.hpp"
#include "Windows.UI.Xaml.UIElement.hpp"
#include "Windows.UI.Xaml.Window.hpp"
// END_INCLUDES
namespace Titanium
{
	namespace Platform
	{

		Object::Object(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context)
		{
			TITANIUM_LOG_DEBUG("Object::ctor");
		}

		void Object::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Object::postCallAsConstructor ", this);

		}

		::Platform::Object^ Object::unwrapPlatform_Object() const
		{
			return dynamic_cast<::Platform::Object^>(wrapped__);
		}

		::Platform::Object^ Object::unwrap() const
		{
			return unwrapPlatform_Object();
		}

		void Object::wrap(::Platform::Object^ object)
		{
			wrapped__ = object;
		}

		void Object::JSExportInitialize()
		{
			JSExport<Object>::SetClassVersion(1);
			JSExport<Object>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_FUNCTION(Object, cast);
		}

		TITANIUM_FUNCTION(Object, cast)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto to_cast = static_cast<std::string>(_0);
				if (to_cast == "Platform.Object") {
					auto result = context.CreateObject(JSExport<Titanium::Platform::Object>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Platform::Object>();
					result_wrapper->wrap(dynamic_cast<::Platform::Object^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.Foundation.AsyncActionCompletedHandler") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::Foundation::AsyncActionCompletedHandler>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::Foundation::AsyncActionCompletedHandler>();
					result_wrapper->wrap(dynamic_cast<::Windows::Foundation::AsyncActionCompletedHandler^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.Foundation.Collections.IPropertySet") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::Foundation::Collections::IPropertySet>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::Foundation::Collections::IPropertySet>();
					result_wrapper->wrap(dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.Foundation.IAsyncAction") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::Foundation::IAsyncAction>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::Foundation::IAsyncAction>();
					result_wrapper->wrap(dynamic_cast<::Windows::Foundation::IAsyncAction^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.Foundation.IWwwFormUrlDecoderEntry") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::Foundation::IWwwFormUrlDecoderEntry>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::Foundation::IWwwFormUrlDecoderEntry>();
					result_wrapper->wrap(dynamic_cast<::Windows::Foundation::IWwwFormUrlDecoderEntry^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.Foundation.Uri") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::Foundation::Uri>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::Foundation::Uri>();
					result_wrapper->wrap(dynamic_cast<::Windows::Foundation::Uri^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.Foundation.WwwFormUrlDecoder") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::Foundation::WwwFormUrlDecoder>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::Foundation::WwwFormUrlDecoder>();
					result_wrapper->wrap(dynamic_cast<::Windows::Foundation::WwwFormUrlDecoder^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Colors") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Colors>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Colors>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Colors^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Core.CoreCursor") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Core::CoreCursor>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Core::CoreCursor>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Core::CoreCursor^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Core.CoreDispatcher") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Core::CoreDispatcher>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Core::CoreDispatcher>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Core::CoreDispatcher^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Core.CoreWindow") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Core::CoreWindow>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Core::CoreWindow>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Core::CoreWindow^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Core.DispatchedHandler") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Core::DispatchedHandler>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Core::DispatchedHandler>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Core::DispatchedHandler^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Core.IdleDispatchedHandler") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Core::IdleDispatchedHandler>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Core::IdleDispatchedHandler>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Core::IdleDispatchedHandler^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Core.IdleDispatchedHandlerArgs") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Core::IdleDispatchedHandlerArgs>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Core::IdleDispatchedHandlerArgs>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Core::IdleDispatchedHandlerArgs^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.AppBar") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::AppBar>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::AppBar>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::AppBar^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.Canvas") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::Canvas>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::Canvas>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::Canvas^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.ContentControl") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::ContentControl>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::ContentControl>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::ContentControl^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.Control") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::Control>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::Control>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::Control^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.ControlTemplate") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::ControlTemplate>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::ControlTemplate>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::ControlTemplate^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.DataTemplateSelector") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::DataTemplateSelector>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::DataTemplateSelector>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::DataTemplateSelector^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.Frame") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::Frame>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::Frame>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::Frame^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.Page") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::Page>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::Page>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::Page^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.Panel") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::Panel>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::Panel>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::Panel^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.TextBlock") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::TextBlock>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::TextBlock>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::TextBlock^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.UIElementCollection") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::UIElementCollection>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::UIElementCollection>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::UIElementCollection^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Controls.UserControl") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Controls::UserControl>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Controls::UserControl>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Controls::UserControl^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.CreateDefaultValueCallback") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::CreateDefaultValueCallback>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::CreateDefaultValueCallback>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::CreateDefaultValueCallback^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Data.Binding") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Data::Binding>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Data::Binding>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Data::Binding^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Data.BindingBase") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Data::BindingBase>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Data::BindingBase>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Data::BindingBase^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Data.BindingExpression") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Data::BindingExpression>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Data::BindingExpression>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Data::BindingExpression^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Data.BindingExpressionBase") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Data::BindingExpressionBase>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Data::BindingExpressionBase>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Data::BindingExpressionBase^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Data.IValueConverter") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Data::IValueConverter>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Data::IValueConverter>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Data::IValueConverter^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Data.RelativeSource") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Data::RelativeSource>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Data::RelativeSource>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Data::RelativeSource^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.DataTemplate") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::DataTemplate>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::DataTemplate>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::DataTemplate^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.DependencyObject") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::DependencyObject>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::DependencyObject>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::DependencyObject^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.DependencyProperty") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::DependencyProperty>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::DependencyProperty>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::DependencyProperty^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.DependencyPropertyChangedEventArgs") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::DependencyPropertyChangedEventArgs>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::DependencyPropertyChangedEventArgs>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Documents.Inline") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Documents::Inline>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Documents::Inline>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Documents::Inline^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Documents.InlineCollection") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Documents::InlineCollection>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Documents::InlineCollection>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Documents::InlineCollection^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Documents.TextElement") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Documents::TextElement>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Documents::TextElement>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Documents::TextElement^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Documents.TextPointer") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Documents::TextPointer>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Documents::TextPointer>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Documents::TextPointer^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.FrameworkElement") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::FrameworkElement>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::FrameworkElement>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::FrameworkElement^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.FrameworkTemplate") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::FrameworkTemplate>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::FrameworkTemplate>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::FrameworkTemplate^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Input.Pointer") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Input::Pointer>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Input::Pointer>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Input::Pointer^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.Animation.NavigationTransitionInfo") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.Animation.Transition") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::Animation::Transition>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::Animation::Transition>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::Animation::Transition^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.Animation.TransitionCollection") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::Animation::TransitionCollection>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::Animation::TransitionCollection>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::Animation::TransitionCollection^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.Brush") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::Brush>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::Brush>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::Brush^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.CacheMode") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::CacheMode>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::CacheMode>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::CacheMode^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.FontFamily") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::FontFamily>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::FontFamily>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::FontFamily^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.GeneralTransform") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::GeneralTransform>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::GeneralTransform>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::GeneralTransform^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.Geometry") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::Geometry>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::Geometry>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::Geometry^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.Projection") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::Projection>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::Projection>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::Projection^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.RectangleGeometry") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::RectangleGeometry>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::RectangleGeometry>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::RectangleGeometry^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.SolidColorBrush") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::SolidColorBrush>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::SolidColorBrush>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::SolidColorBrush^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Media.Transform") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Media::Transform>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Media::Transform>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Media::Transform^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Navigation.PageStackEntry") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Navigation::PageStackEntry>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Navigation::PageStackEntry>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Navigation::PageStackEntry^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.PropertyChangedCallback") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::PropertyChangedCallback>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::PropertyChangedCallback>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::PropertyChangedCallback^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.PropertyMetadata") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::PropertyMetadata>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::PropertyMetadata>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::PropertyMetadata^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.PropertyPath") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::PropertyPath>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::PropertyPath>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::PropertyPath^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.ResourceDictionary") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::ResourceDictionary>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::ResourceDictionary>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::ResourceDictionary^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.RoutedEvent") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::RoutedEvent>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::RoutedEvent>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::RoutedEvent^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.SetterBase") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::SetterBase>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::SetterBase>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::SetterBase^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.SetterBaseCollection") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::SetterBaseCollection>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::SetterBaseCollection>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::SetterBaseCollection^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Style") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Style>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Style>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Style^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.TriggerBase") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::TriggerBase>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::TriggerBase>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::TriggerBase^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.TriggerCollection") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::TriggerCollection>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::TriggerCollection>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::TriggerCollection^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.UIElement") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::UIElement>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::UIElement>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::UIElement^>(unwrap()));
					return result;
				}
				else if (to_cast == "Windows.UI.Xaml.Window") {
					auto result = context.CreateObject(JSExport<Titanium::Windows::UI::Xaml::Window>::Class());
					auto result_wrapper = result.GetPrivate<Titanium::Windows::UI::Xaml::Window>();
					result_wrapper->wrap(dynamic_cast<::Windows::UI::Xaml::Window^>(unwrap()));
					return result;
				}

			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Object::cast with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

	} // namespace Platform
} // namespace Titanium
