/**
 * Windows Native Wrapper for Windows.UI.Xaml.UIElement
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_UIELEMENT_HPP_
#define _WINDOWS_UI_XAML_UIELEMENT_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT UIElement : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<UIElement>
		{

		public:
			TITANIUM_PROPERTY_DEF(CompositeMode);
			TITANIUM_PROPERTY_DEF(IsTapEnabled);
			TITANIUM_PROPERTY_DEF(IsRightTapEnabled);
			TITANIUM_PROPERTY_DEF(IsHoldingEnabled);
			TITANIUM_PROPERTY_DEF(IsHitTestVisible);
			TITANIUM_PROPERTY_DEF(IsDoubleTapEnabled);
			TITANIUM_PROPERTY_DEF(ManipulationMode);
			TITANIUM_PROPERTY_DEF(Clip);
			TITANIUM_PROPERTY_DEF(CacheMode);
			TITANIUM_PROPERTY_DEF(AllowDrop);
			TITANIUM_PROPERTY_DEF(Visibility);
			TITANIUM_PROPERTY_DEF(UseLayoutRounding);
			TITANIUM_PROPERTY_DEF(Transitions);
			TITANIUM_PROPERTY_DEF(RenderTransformOrigin);
			TITANIUM_PROPERTY_DEF(RenderTransform);
			TITANIUM_PROPERTY_DEF(Projection);
			TITANIUM_PROPERTY_DEF(Opacity);
			TITANIUM_PROPERTY_READONLY_DEF(PointerCaptures);
			TITANIUM_PROPERTY_READONLY_DEF(RenderSize);
			TITANIUM_PROPERTY_READONLY_DEF(DesiredSize);
			TITANIUM_PROPERTY_READONLY_DEF(CompositeModeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(AllowDropProperty);
			TITANIUM_PROPERTY_READONLY_DEF(CacheModeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ClipProperty);
			TITANIUM_PROPERTY_READONLY_DEF(DoubleTappedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(DragEnterEvent);
			TITANIUM_PROPERTY_READONLY_DEF(DragLeaveEvent);
			TITANIUM_PROPERTY_READONLY_DEF(DragOverEvent);
			TITANIUM_PROPERTY_READONLY_DEF(DropEvent);
			TITANIUM_PROPERTY_READONLY_DEF(HoldingEvent);
			TITANIUM_PROPERTY_READONLY_DEF(IsDoubleTapEnabledProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsHitTestVisibleProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsHoldingEnabledProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsRightTapEnabledProperty);
			TITANIUM_PROPERTY_READONLY_DEF(IsTapEnabledProperty);
			TITANIUM_PROPERTY_READONLY_DEF(KeyDownEvent);
			TITANIUM_PROPERTY_READONLY_DEF(KeyUpEvent);
			TITANIUM_PROPERTY_READONLY_DEF(ManipulationCompletedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(ManipulationDeltaEvent);
			TITANIUM_PROPERTY_READONLY_DEF(ManipulationInertiaStartingEvent);
			TITANIUM_PROPERTY_READONLY_DEF(ManipulationModeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ManipulationStartedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(ManipulationStartingEvent);
			TITANIUM_PROPERTY_READONLY_DEF(OpacityProperty);
			TITANIUM_PROPERTY_READONLY_DEF(PointerCanceledEvent);
			TITANIUM_PROPERTY_READONLY_DEF(PointerCaptureLostEvent);
			TITANIUM_PROPERTY_READONLY_DEF(PointerCapturesProperty);
			TITANIUM_PROPERTY_READONLY_DEF(PointerEnteredEvent);
			TITANIUM_PROPERTY_READONLY_DEF(PointerExitedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(PointerMovedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(PointerPressedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(PointerReleasedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(PointerWheelChangedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(ProjectionProperty);
			TITANIUM_PROPERTY_READONLY_DEF(RenderTransformOriginProperty);
			TITANIUM_PROPERTY_READONLY_DEF(RenderTransformProperty);
			TITANIUM_PROPERTY_READONLY_DEF(RightTappedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(TappedEvent);
			TITANIUM_PROPERTY_READONLY_DEF(TransitionsProperty);
			TITANIUM_PROPERTY_READONLY_DEF(UseLayoutRoundingProperty);
			TITANIUM_PROPERTY_READONLY_DEF(VisibilityProperty);

			TITANIUM_FUNCTION_DEF(Measure);
			TITANIUM_FUNCTION_DEF(Arrange);
			TITANIUM_FUNCTION_DEF(CapturePointer);
			TITANIUM_FUNCTION_DEF(ReleasePointerCapture);
			TITANIUM_FUNCTION_DEF(ReleasePointerCaptures);
			TITANIUM_FUNCTION_DEF(AddHandler);
			TITANIUM_FUNCTION_DEF(RemoveHandler);
			TITANIUM_FUNCTION_DEF(TransformToVisual);
			TITANIUM_FUNCTION_DEF(InvalidateMeasure);
			TITANIUM_FUNCTION_DEF(InvalidateArrange);
			TITANIUM_FUNCTION_DEF(UpdateLayout);
			TITANIUM_FUNCTION_DEF(CancelDirectManipulations);

			UIElement(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~UIElement() = default;
			UIElement(const UIElement&) = default;
			UIElement& operator=(const UIElement&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			UIElement(UIElement&&)                 = default;
			UIElement& operator=(UIElement&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::UIElement^ unwrapWindows_UI_Xaml_UIElement() const;
			void wrap(::Windows::UI::Xaml::UIElement^ object);

		private:
			::Windows::UI::Xaml::UIElement^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_UIELEMENT_HPP_
