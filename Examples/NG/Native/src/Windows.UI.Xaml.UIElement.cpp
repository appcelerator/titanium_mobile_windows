/**
 * Windows Native Wrapper for Windows.UI.Xaml.UIElement
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.DependencyProperty.hpp"
#include "Windows.UI.Xaml.Input.Pointer.hpp"
#include "Windows.UI.Xaml.Media.Animation.TransitionCollection.hpp"
#include "Windows.UI.Xaml.Media.CacheMode.hpp"
#include "Windows.UI.Xaml.Media.GeneralTransform.hpp"
#include "Windows.UI.Xaml.Media.Projection.hpp"
#include "Windows.UI.Xaml.Media.RectangleGeometry.hpp"
#include "Windows.UI.Xaml.Media.Transform.hpp"
#include "Windows.UI.Xaml.RoutedEvent.hpp"
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

		UIElement::UIElement(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("UIElement::ctor");
		}

		void UIElement::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("UIElement::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::UIElement^ UIElement::unwrapWindows_UI_Xaml_UIElement() const
		{
			return dynamic_cast<::Windows::UI::Xaml::UIElement^>(wrapped__);
		}

		::Windows::UI::Xaml::UIElement^ UIElement::unwrap() const
		{
			return unwrapWindows_UI_Xaml_UIElement();
		}

		void UIElement::wrap(::Windows::UI::Xaml::UIElement^ object)
		{
			wrapped__ = object;
		}

		void UIElement::JSExportInitialize()
		{
			JSExport<UIElement>::SetClassVersion(1);
			JSExport<UIElement>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

			TITANIUM_ADD_PROPERTY(UIElement, CompositeMode);
			TITANIUM_ADD_PROPERTY(UIElement, IsTapEnabled);
			TITANIUM_ADD_PROPERTY(UIElement, IsRightTapEnabled);
			TITANIUM_ADD_PROPERTY(UIElement, IsHoldingEnabled);
			TITANIUM_ADD_PROPERTY(UIElement, IsHitTestVisible);
			TITANIUM_ADD_PROPERTY(UIElement, IsDoubleTapEnabled);
			TITANIUM_ADD_PROPERTY(UIElement, ManipulationMode);
			TITANIUM_ADD_PROPERTY(UIElement, Clip);
			TITANIUM_ADD_PROPERTY(UIElement, CacheMode);
			TITANIUM_ADD_PROPERTY(UIElement, AllowDrop);
			TITANIUM_ADD_PROPERTY(UIElement, Visibility);
			TITANIUM_ADD_PROPERTY(UIElement, UseLayoutRounding);
			TITANIUM_ADD_PROPERTY(UIElement, Transitions);
			TITANIUM_ADD_PROPERTY(UIElement, RenderTransformOrigin);
			TITANIUM_ADD_PROPERTY(UIElement, RenderTransform);
			TITANIUM_ADD_PROPERTY(UIElement, Projection);
			TITANIUM_ADD_PROPERTY(UIElement, Opacity);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerCaptures);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, RenderSize);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, DesiredSize);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, CompositeModeProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, AllowDropProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, CacheModeProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ClipProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, DoubleTappedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, DragEnterEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, DragLeaveEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, DragOverEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, DropEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, HoldingEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, IsDoubleTapEnabledProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, IsHitTestVisibleProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, IsHoldingEnabledProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, IsRightTapEnabledProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, IsTapEnabledProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, KeyDownEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, KeyUpEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ManipulationCompletedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ManipulationDeltaEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ManipulationInertiaStartingEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ManipulationModeProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ManipulationStartedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ManipulationStartingEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, OpacityProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerCanceledEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerCaptureLostEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerCapturesProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerEnteredEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerExitedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerMovedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerPressedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerReleasedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, PointerWheelChangedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, ProjectionProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, RenderTransformOriginProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, RenderTransformProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, RightTappedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, TappedEvent);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, TransitionsProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, UseLayoutRoundingProperty);
			TITANIUM_ADD_PROPERTY_READONLY(UIElement, VisibilityProperty);
			TITANIUM_ADD_FUNCTION(UIElement, Measure);
			TITANIUM_ADD_FUNCTION(UIElement, Arrange);
			TITANIUM_ADD_FUNCTION(UIElement, CapturePointer);
			TITANIUM_ADD_FUNCTION(UIElement, ReleasePointerCapture);
			TITANIUM_ADD_FUNCTION(UIElement, ReleasePointerCaptures);
			TITANIUM_ADD_FUNCTION(UIElement, AddHandler);
			TITANIUM_ADD_FUNCTION(UIElement, RemoveHandler);
			TITANIUM_ADD_FUNCTION(UIElement, TransformToVisual);
			TITANIUM_ADD_FUNCTION(UIElement, InvalidateMeasure);
			TITANIUM_ADD_FUNCTION(UIElement, InvalidateArrange);
			TITANIUM_ADD_FUNCTION(UIElement, UpdateLayout);
			TITANIUM_ADD_FUNCTION(UIElement, CancelDirectManipulations);
		}

		TITANIUM_PROPERTY_SETTER(UIElement, CompositeMode)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<::Windows::UI::Xaml::Media::ElementCompositeMode>(static_cast<int32_t>(argument)); // TODO Look up enum in metadata to know what type it's value is? 

			unwrap()->CompositeMode = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, CompositeMode)
		{
			auto value = unwrap()->CompositeMode;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, IsTapEnabled)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsBoolean(), "Expected boolean");
			auto value = static_cast<bool>(argument);

			unwrap()->IsTapEnabled = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsTapEnabled)
		{
			auto value = unwrap()->IsTapEnabled;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, IsRightTapEnabled)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsBoolean(), "Expected boolean");
			auto value = static_cast<bool>(argument);

			unwrap()->IsRightTapEnabled = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsRightTapEnabled)
		{
			auto value = unwrap()->IsRightTapEnabled;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, IsHoldingEnabled)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsBoolean(), "Expected boolean");
			auto value = static_cast<bool>(argument);

			unwrap()->IsHoldingEnabled = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsHoldingEnabled)
		{
			auto value = unwrap()->IsHoldingEnabled;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, IsHitTestVisible)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsBoolean(), "Expected boolean");
			auto value = static_cast<bool>(argument);

			unwrap()->IsHitTestVisible = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsHitTestVisible)
		{
			auto value = unwrap()->IsHitTestVisible;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, IsDoubleTapEnabled)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsBoolean(), "Expected boolean");
			auto value = static_cast<bool>(argument);

			unwrap()->IsDoubleTapEnabled = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsDoubleTapEnabled)
		{
			auto value = unwrap()->IsDoubleTapEnabled;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, ManipulationMode)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<::Windows::UI::Xaml::Input::ManipulationModes>(static_cast<int32_t>(argument)); // TODO Look up enum in metadata to know what type it's value is? 

			unwrap()->ManipulationMode = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ManipulationMode)
		{
			auto value = unwrap()->ManipulationMode;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, Clip)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::RectangleGeometry>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_RectangleGeometry();

			unwrap()->Clip = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, Clip)
		{
			auto value = unwrap()->Clip;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::RectangleGeometry>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::RectangleGeometry>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, CacheMode)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::CacheMode>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_CacheMode();

			unwrap()->CacheMode = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, CacheMode)
		{
			auto value = unwrap()->CacheMode;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::CacheMode>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::CacheMode>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, AllowDrop)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsBoolean(), "Expected boolean");
			auto value = static_cast<bool>(argument);

			unwrap()->AllowDrop = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, AllowDrop)
		{
			auto value = unwrap()->AllowDrop;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, Visibility)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<::Windows::UI::Xaml::Visibility>(static_cast<int32_t>(argument)); // TODO Look up enum in metadata to know what type it's value is? 

			unwrap()->Visibility = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, Visibility)
		{
			auto value = unwrap()->Visibility;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, UseLayoutRounding)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsBoolean(), "Expected boolean");
			auto value = static_cast<bool>(argument);

			unwrap()->UseLayoutRounding = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, UseLayoutRounding)
		{
			auto value = unwrap()->UseLayoutRounding;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, Transitions)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Animation::TransitionCollection>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Animation_TransitionCollection();

			unwrap()->Transitions = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, Transitions)
		{
			auto value = unwrap()->Transitions;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Animation::TransitionCollection>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Animation::TransitionCollection>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, RenderTransformOrigin)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
			::Windows::Foundation::Point value;
			// Assign fields explicitly since we didn't use a constructor

			auto object_value_X = object_value.GetProperty("X"); 
			TITANIUM_ASSERT_AND_THROW(object_value_X.IsNumber(), "Expected Number");
			auto object_value_X_ = static_cast<float>(static_cast<double>(object_value_X));

			value.X = object_value_X_;

			auto object_value_Y = object_value.GetProperty("Y"); 
			TITANIUM_ASSERT_AND_THROW(object_value_Y.IsNumber(), "Expected Number");
			auto object_value_Y_ = static_cast<float>(static_cast<double>(object_value_Y));

			value.Y = object_value_Y_;

			unwrap()->RenderTransformOrigin = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, RenderTransformOrigin)
		{
			auto value = unwrap()->RenderTransformOrigin;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_X_ = context.CreateNumber(static_cast<double>(value.X));

			result.SetProperty("X", value_X_);



			auto value_Y_ = context.CreateNumber(static_cast<double>(value.Y));

			result.SetProperty("Y", value_Y_);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, RenderTransform)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Transform>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Transform();

			unwrap()->RenderTransform = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, RenderTransform)
		{
			auto value = unwrap()->RenderTransform;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Transform>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Transform>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, Projection)
		{
			TITANIUM_ASSERT_AND_THROW(argument.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(argument);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Media::Projection>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Media_Projection();

			unwrap()->Projection = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, Projection)
		{
			auto value = unwrap()->Projection;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::Projection>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::Projection>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_SETTER(UIElement, Opacity)
		{ 
			TITANIUM_ASSERT_AND_THROW(argument.IsNumber(), "Expected Number");
			auto value = static_cast<float>(static_cast<double>(argument));

			unwrap()->Opacity = value;
			return true;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, Opacity)
		{
			auto value = unwrap()->Opacity;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<double>(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerCaptures)
		{
			auto value = unwrap()->PointerCaptures;
			auto context = get_context();

			std::vector<JSValue> result_vector;
			for (uint32_t i = 0; i < value->Size; ++i) {
				

			auto value_tmp = context.CreateObject(JSExport<Windows::UI::Xaml::Input::Pointer>::Class());
			auto value_tmp_wrapper = value_tmp.GetPrivate<Windows::UI::Xaml::Input::Pointer>();
			value_tmp_wrapper->wrap(value->GetAt(i));


        		result_vector.push_back(value_tmp);
			}

			auto result = get_context().CreateArray(result_vector);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, RenderSize)
		{
			auto value = unwrap()->RenderSize;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_Width_ = context.CreateNumber(static_cast<double>(value.Width));

			result.SetProperty("Width", value_Width_);



			auto value_Height_ = context.CreateNumber(static_cast<double>(value.Height));

			result.SetProperty("Height", value_Height_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, DesiredSize)
		{
			auto value = unwrap()->DesiredSize;
			auto context = get_context();

			auto result = context.CreateObject();


			auto value_Width_ = context.CreateNumber(static_cast<double>(value.Width));

			result.SetProperty("Width", value_Width_);



			auto value_Height_ = context.CreateNumber(static_cast<double>(value.Height));

			result.SetProperty("Height", value_Height_);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, CompositeModeProperty)
		{
			auto value = unwrap()->CompositeModeProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, AllowDropProperty)
		{
			auto value = unwrap()->AllowDropProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, CacheModeProperty)
		{
			auto value = unwrap()->CacheModeProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ClipProperty)
		{
			auto value = unwrap()->ClipProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, DoubleTappedEvent)
		{
			auto value = unwrap()->DoubleTappedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, DragEnterEvent)
		{
			auto value = unwrap()->DragEnterEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, DragLeaveEvent)
		{
			auto value = unwrap()->DragLeaveEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, DragOverEvent)
		{
			auto value = unwrap()->DragOverEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, DropEvent)
		{
			auto value = unwrap()->DropEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, HoldingEvent)
		{
			auto value = unwrap()->HoldingEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsDoubleTapEnabledProperty)
		{
			auto value = unwrap()->IsDoubleTapEnabledProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsHitTestVisibleProperty)
		{
			auto value = unwrap()->IsHitTestVisibleProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsHoldingEnabledProperty)
		{
			auto value = unwrap()->IsHoldingEnabledProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsRightTapEnabledProperty)
		{
			auto value = unwrap()->IsRightTapEnabledProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, IsTapEnabledProperty)
		{
			auto value = unwrap()->IsTapEnabledProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, KeyDownEvent)
		{
			auto value = unwrap()->KeyDownEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, KeyUpEvent)
		{
			auto value = unwrap()->KeyUpEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ManipulationCompletedEvent)
		{
			auto value = unwrap()->ManipulationCompletedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ManipulationDeltaEvent)
		{
			auto value = unwrap()->ManipulationDeltaEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ManipulationInertiaStartingEvent)
		{
			auto value = unwrap()->ManipulationInertiaStartingEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ManipulationModeProperty)
		{
			auto value = unwrap()->ManipulationModeProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ManipulationStartedEvent)
		{
			auto value = unwrap()->ManipulationStartedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ManipulationStartingEvent)
		{
			auto value = unwrap()->ManipulationStartingEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, OpacityProperty)
		{
			auto value = unwrap()->OpacityProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerCanceledEvent)
		{
			auto value = unwrap()->PointerCanceledEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerCaptureLostEvent)
		{
			auto value = unwrap()->PointerCaptureLostEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerCapturesProperty)
		{
			auto value = unwrap()->PointerCapturesProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerEnteredEvent)
		{
			auto value = unwrap()->PointerEnteredEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerExitedEvent)
		{
			auto value = unwrap()->PointerExitedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerMovedEvent)
		{
			auto value = unwrap()->PointerMovedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerPressedEvent)
		{
			auto value = unwrap()->PointerPressedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerReleasedEvent)
		{
			auto value = unwrap()->PointerReleasedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, PointerWheelChangedEvent)
		{
			auto value = unwrap()->PointerWheelChangedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, ProjectionProperty)
		{
			auto value = unwrap()->ProjectionProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, RenderTransformOriginProperty)
		{
			auto value = unwrap()->RenderTransformOriginProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, RenderTransformProperty)
		{
			auto value = unwrap()->RenderTransformProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, RightTappedEvent)
		{
			auto value = unwrap()->RightTappedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, TappedEvent)
		{
			auto value = unwrap()->TappedEvent;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::RoutedEvent>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, TransitionsProperty)
		{
			auto value = unwrap()->TransitionsProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, UseLayoutRoundingProperty)
		{
			auto value = unwrap()->UseLayoutRoundingProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(UIElement, VisibilityProperty)
		{
			auto value = unwrap()->VisibilityProperty;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::DependencyProperty>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::DependencyProperty>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_FUNCTION(UIElement, Measure)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_availableSize = static_cast<JSObject>(_0);
			::Windows::Foundation::Size availableSize;
			// Assign fields explicitly since we didn't use a constructor

			auto object_availableSize_Width = object_availableSize.GetProperty("Width"); 
			TITANIUM_ASSERT_AND_THROW(object_availableSize_Width.IsNumber(), "Expected Number");
			auto object_availableSize_Width_ = static_cast<float>(static_cast<double>(object_availableSize_Width));

			availableSize.Width = object_availableSize_Width_;

			auto object_availableSize_Height = object_availableSize.GetProperty("Height"); 
			TITANIUM_ASSERT_AND_THROW(object_availableSize_Height.IsNumber(), "Expected Number");
			auto object_availableSize_Height_ = static_cast<float>(static_cast<double>(object_availableSize_Height));

			availableSize.Height = object_availableSize_Height_;

				unwrap()->Measure(availableSize);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::Measure with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, Arrange)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_finalRect = static_cast<JSObject>(_0);
			::Windows::Foundation::Rect finalRect;
			// Assign fields explicitly since we didn't use a constructor

			auto object_finalRect_X = object_finalRect.GetProperty("X"); 
			TITANIUM_ASSERT_AND_THROW(object_finalRect_X.IsNumber(), "Expected Number");
			auto object_finalRect_X_ = static_cast<float>(static_cast<double>(object_finalRect_X));

			finalRect.X = object_finalRect_X_;

			auto object_finalRect_Y = object_finalRect.GetProperty("Y"); 
			TITANIUM_ASSERT_AND_THROW(object_finalRect_Y.IsNumber(), "Expected Number");
			auto object_finalRect_Y_ = static_cast<float>(static_cast<double>(object_finalRect_Y));

			finalRect.Y = object_finalRect_Y_;

			auto object_finalRect_Width = object_finalRect.GetProperty("Width"); 
			TITANIUM_ASSERT_AND_THROW(object_finalRect_Width.IsNumber(), "Expected Number");
			auto object_finalRect_Width_ = static_cast<float>(static_cast<double>(object_finalRect_Width));

			finalRect.Width = object_finalRect_Width_;

			auto object_finalRect_Height = object_finalRect.GetProperty("Height"); 
			TITANIUM_ASSERT_AND_THROW(object_finalRect_Height.IsNumber(), "Expected Number");
			auto object_finalRect_Height_ = static_cast<float>(static_cast<double>(object_finalRect_Height));

			finalRect.Height = object_finalRect_Height_;

				unwrap()->Arrange(finalRect);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::Arrange with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, CapturePointer)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Input::Pointer>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Input_Pointer();

				auto method_result = unwrap()->CapturePointer(value);
 
			auto result = context.CreateBoolean(method_result); 

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::CapturePointer with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, ReleasePointerCapture)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_value = static_cast<JSObject>(_0);
 
			auto wrapper_value = object_value.GetPrivate<Windows::UI::Xaml::Input::Pointer>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto value = wrapper_value->unwrapWindows_UI_Xaml_Input_Pointer();

				unwrap()->ReleasePointerCapture(value);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::ReleasePointerCapture with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, ReleasePointerCaptures)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->ReleasePointerCaptures();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::ReleasePointerCaptures with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, AddHandler)
		{
			auto context = get_context();
			if (arguments.size() == 3) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_routedEvent = static_cast<JSObject>(_0);
 
			auto wrapper_routedEvent = object_routedEvent.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto routedEvent = wrapper_routedEvent->unwrapWindows_UI_Xaml_RoutedEvent();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_handler = static_cast<JSObject>(_1);
 
			auto wrapper_handler = object_handler.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto handler = wrapper_handler->unwrapPlatform_Object();

				auto _2 = arguments.at(2); 
			TITANIUM_ASSERT_AND_THROW(_2.IsBoolean(), "Expected boolean");
			auto handledEventsToo = static_cast<bool>(_2);

				unwrap()->AddHandler(routedEvent, handler, handledEventsToo);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::AddHandler with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, RemoveHandler)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_routedEvent = static_cast<JSObject>(_0);
 
			auto wrapper_routedEvent = object_routedEvent.GetPrivate<Windows::UI::Xaml::RoutedEvent>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto routedEvent = wrapper_routedEvent->unwrapWindows_UI_Xaml_RoutedEvent();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_handler = static_cast<JSObject>(_1);
 
			auto wrapper_handler = object_handler.GetPrivate<Platform::Object>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto handler = wrapper_handler->unwrapPlatform_Object();

				unwrap()->RemoveHandler(routedEvent, handler);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::RemoveHandler with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, TransformToVisual)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_visual = static_cast<JSObject>(_0);
 
			auto wrapper_visual = object_visual.GetPrivate<Windows::UI::Xaml::UIElement>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto visual = wrapper_visual->unwrapWindows_UI_Xaml_UIElement();

				auto method_result = unwrap()->TransformToVisual(visual);

			auto result = context.CreateObject(JSExport<Windows::UI::Xaml::Media::GeneralTransform>::Class());
			auto result_wrapper = result.GetPrivate<Windows::UI::Xaml::Media::GeneralTransform>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::TransformToVisual with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, InvalidateMeasure)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->InvalidateMeasure();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::InvalidateMeasure with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, InvalidateArrange)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->InvalidateArrange();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::InvalidateArrange with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, UpdateLayout)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				unwrap()->UpdateLayout();
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::UpdateLayout with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(UIElement, CancelDirectManipulations)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->CancelDirectManipulations();
 
			auto result = context.CreateBoolean(method_result); 

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched UIElement::CancelDirectManipulations with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
