/**
 * TitaniumKit ViewLayoutDelegate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <collection.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace TitaniumWindows
{
	namespace UI
	{
		WindowsViewLayoutDelegate::WindowsViewLayoutDelegate() TITANIUM_NOEXCEPT
			: ViewLayoutDelegate()
		{
			TITANIUM_LOG_DEBUG("WindowsViewLayoutDelegate::ctor");
		}

		void WindowsViewLayoutDelegate::postInitialize() TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::postInitialize();
		}

		// TODO: implement this
		void WindowsViewLayoutDelegate::remove(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::remove(view);

			TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::remove not implemented");
		}

		void WindowsViewLayoutDelegate::add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::add(view);

			auto nativeView = dynamic_cast<Windows::UI::Xaml::Controls::Panel^>(getComponent());

			if (nativeView == nullptr) {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::add: Unknown component");
				return;
			}

			auto newView = view->getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>();
			auto nativeChildView = newView->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeAddChild(layout_node__, newView->getLayoutNode());
				if (isLoaded()) {
					requestLayout();
				}

				nativeView->Children->Append(nativeChildView);
			} else {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::add: Unknown child component");
			}
		}

		void WindowsViewLayoutDelegate::hide() TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::hide();
			getComponent()->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		}

		void WindowsViewLayoutDelegate::show() TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::show();
			getComponent()->Visibility = Windows::UI::Xaml::Visibility::Visible;
		}

		void WindowsViewLayoutDelegate::animate(const std::shared_ptr<Titanium::UI::Animation>& animation, JSObject& callback, const JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// Storyboard where we attach all the animations
			const auto storyboard = ref new Windows::UI::Xaml::Media::Animation::Storyboard();

			// delay
			const std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> delay_ticks = animation->get_delay();
			Windows::Foundation::TimeSpan delay;
			delay.Duration = delay_ticks.count();
			storyboard->BeginTime = delay; // FIXME This seems to apply to every iteration of repeat, but we probably only want it to happen the first time?

			// duration
			const std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = animation->get_duration();
			Windows::Foundation::TimeSpan duration;
			duration.Duration = timer_interval_ticks.count() + delay.Duration;
			storyboard->Duration = duration;
			
			// autoreverse
			storyboard->AutoReverse = animation->get_autoreverse();
			
			// repeat
			const double repeat = animation->get_repeat();
			if (repeat == 0) {
				storyboard->RepeatBehavior = Windows::UI::Xaml::Media::Animation::RepeatBehaviorHelper::Forever;
			} else if (repeat != 1) {
				storyboard->RepeatBehavior = Windows::UI::Xaml::Media::Animation::RepeatBehaviorHelper::FromCount(repeat);
			}

			// curve/ease
			const auto curve = animation->get_curve();
			// TODO Expand the set of animation curves available to encompass all the ones from Windows!
			// http://iphonedevelopment.blogspot.com/2010/12/more-animation-curves-than-you-can.html
			// Here's where iOS defines it's Bezier control points! 
			// https://developer.apple.com/library/mac/documentation/Cocoa/Reference/CAMediaTimingFunction_class/index.html#//apple_ref/doc/constant_group/Predefined_Timing_Functions
			// There are no equivalent easing functions on Windows!!!! They look/behave differently.
			// You can compare the values used here: http://easings.net/
			Windows::UI::Xaml::Media::Animation::EasingFunctionBase^ ease;
			switch (curve) {
			case Titanium::UI::ANIMATION_CURVE::EASE_IN:
				ease = ref new Windows::UI::Xaml::Media::Animation::CubicEase();
				ease->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseIn;
				break;
			case Titanium::UI::ANIMATION_CURVE::EASE_IN_OUT:
				ease = ref new Windows::UI::Xaml::Media::Animation::CubicEase();
				ease->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseInOut;
				break;
			case Titanium::UI::ANIMATION_CURVE::EASE_OUT:
				ease = ref new Windows::UI::Xaml::Media::Animation::CubicEase();
				ease->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut;
				break;
			case Titanium::UI::ANIMATION_CURVE::LINEAR:
				ease = nullptr;
				break;
			default:
				break;
			}

			const auto component = getComponent();

			// transform
			if (animation->get_transform() != nullptr) {

				const auto a = animation->get_transform()->get_a(); // scale x
				const auto b = animation->get_transform()->get_b(); // shear y
				const auto c = animation->get_transform()->get_c(); // shear x
				const auto d = animation->get_transform()->get_d(); // scale y

				auto rotation = 0.0;
				auto scale_x = 1.0;
				auto scale_y = 1.0;
				auto skew_x = 0.0;
				auto skew_y = 0.0;

				const auto delta = a * d - b * c;

				// We can decompose using QR/LU, then we can create a TransformGroup that applies the transformations in necessary order according to the decomposition!
				// http://www.maths-informatique-jeux.com/blog/frederic/?post/2013/12/01/Decomposition-of-2D-transform-matrices
				// Do QR decomposition
				if (a || b) {
					const auto r = sqrt(a*a + b*b);
					rotation = b > 0 ? acos(a / r) : -acos(a / r);
					scale_x = r;
					scale_y = delta / r;
					skew_x = atan((a*c + b*d) / (r*r));
				} else if (c || d) {
					const auto s = sqrt(c*c + d*d);
					rotation = M_PI * 0.5 - (d > 0 ? acos(-c / s) : -acos(c / s));
					skew_x = delta / s;
					skew_y = s;
					skew_y = atan((a*c + b*d) / (s*s));
				} else { // a = b = c = d = 0
					scale_x = 0;
					scale_y = 0; // = invalid matrix
				}

				// Convert rotation from rads to degrees!
				rotation = (180.0 * rotation) / M_PI;

				// Now we need to apply the transformations in a specific order to be equivalent to the final matrix:
				// translate -> rotate -> scale -> skew X
				const auto group = ref new Windows::UI::Xaml::Media::TransformGroup();
				const auto translate = ref new Windows::UI::Xaml::Media::TranslateTransform();
				const auto rotate = ref new Windows::UI::Xaml::Media::RotateTransform();
				const auto composite = ref new Windows::UI::Xaml::Media::CompositeTransform(); // cheat and use composite to do scale and then skew
				group->Children->Append(translate);
				group->Children->Append(rotate);
				group->Children->Append(composite);

				component->RenderTransform = group;

				const auto rotation_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
				rotation_anim->To = rotation;
				rotation_anim->EasingFunction = ease;
				storyboard->SetTargetProperty(rotation_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[1].(RotateTransform.Angle)");
				storyboard->SetTarget(rotation_anim, component);
				storyboard->Children->Append(rotation_anim);

				const auto scale_x_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
				scale_x_anim->To = a;
				scale_x_anim->EasingFunction = ease;
				storyboard->SetTargetProperty(scale_x_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleX)");
				storyboard->SetTarget(scale_x_anim, component);
				storyboard->Children->Append(scale_x_anim);

				const auto scale_y_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
				scale_y_anim->To = d;
				scale_y_anim->EasingFunction = ease;
				storyboard->SetTargetProperty(scale_y_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleY)");
				storyboard->SetTarget(scale_y_anim, component);
				storyboard->Children->Append(scale_y_anim);

				const auto tx_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
				tx_anim->To = animation->get_transform()->get_tx();
				tx_anim->EasingFunction = ease;
				storyboard->SetTargetProperty(tx_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateX)");
				storyboard->SetTarget(tx_anim, component);
				storyboard->Children->Append(tx_anim);

				const auto ty_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
				ty_anim->To = animation->get_transform()->get_ty();
				ty_anim->EasingFunction = ease;
				storyboard->SetTargetProperty(ty_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateY)");
				storyboard->SetTarget(ty_anim, component);
				storyboard->Children->Append(ty_anim);
			} else {
				// I'm assuming that we can only do transform *OR* top/left/right/center/bottom/width/height animations - not mix them.

				// TODO What are the relative priorities of these properties?
				// Should we prefer transform to any of these others?
				// What about if they animate top AND bottom, and also height? Which wins? Can top/bottom only translate and not scale?

				// See https://github.com/appcelerator/titanium_mobile_windows/blob/master/Examples/NMocha/src/Assets/ti.ui.layout.test.js
				// https://github.com/appcelerator/titanium_mobile/blob/58198c641d77e17d156431666e80bae732b5c130/android/titanium/src/java/org/appcelerator/titanium/util/TiAnimationBuilder.java#L430
				// When left, right and center are specified, left and center win (for determining width and position)
				// When top, bottom and height are specified, height and top win (for determining height and position)
				// when top, bottom and center are specified, top and center win (for determining height and position)

				// Need to group up the transforms like we do above so we can do both translate and scale!
				const auto group = ref new Windows::UI::Xaml::Media::TransformGroup();
				const auto translate = ref new Windows::UI::Xaml::Media::TranslateTransform();
				const auto rotate = ref new Windows::UI::Xaml::Media::RotateTransform();
				const auto composite = ref new Windows::UI::Xaml::Media::CompositeTransform(); // cheat and use composite to do scale and then skew
				group->Children->Append(translate);
				group->Children->Append(rotate);
				group->Children->Append(composite);

				component->RenderTransform = group;

				const auto top = animation->get_top();
				if (top) {
					// TODO Bottom
					// Because we're animating a transform, the value behaves like setting By, not To. So we need to calculate the difference and set our target To to that value
					const auto current_top = Windows::UI::Xaml::Controls::Canvas::GetTop(component);
					const auto diff = *top - current_top;
					
					const auto top_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
					top_anim->To = diff;
					top_anim->EasingFunction = ease;
					storyboard->SetTargetProperty(top_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateY)");
					storyboard->SetTarget(top_anim, component);
					storyboard->Children->Append(top_anim);
				}

				// TODO if they specify top AND bottom and DON'T specify height, we should translate top, and treat bottom - top as height.
				// If they specify bottom AND height, BUT NOT top; we should translate bottom and scale height?
				// If they specify just bottom, no top or height, just translate bottom?

				const auto left = animation->get_left(); // TODO Right
				if (left) {
					// TODO If "right", we need to calculate the current position of "right", take the diff and then do a transform By, not To
					const auto current_left = Windows::UI::Xaml::Controls::Canvas::GetLeft(component);
					const auto diff = *left - current_left;

					const auto left_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
					left_anim->To = diff;
					left_anim->EasingFunction = ease;
					storyboard->SetTargetProperty(left_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateX)");
					storyboard->SetTarget(left_anim, component);
					storyboard->Children->Append(left_anim);
				}


				// For width and height, we have to calculate the scale to use to achieve desired height/width, since animating the Height or Width properties are ppor performance-wise and best avoided.
				const auto height = animation->get_height();
				if (height) {
					const auto height_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
					const auto current_height = component->Height;
					const auto scaleY = *height / current_height;
					height_anim->To = scaleY;  // TODO Need to determine scale to use to achieve the desired height!
					height_anim->EasingFunction = ease;
					storyboard->SetTargetProperty(height_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleY)");
					storyboard->SetTarget(height_anim, component);
					storyboard->Children->Append(height_anim);
				}

				const auto width = animation->get_width();
				if (width) {
					const auto width_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
					const auto current_width = component->Width;
					const auto scaleX = *width / current_width;
					width_anim->To = scaleX;
					width_anim->EasingFunction = ease;
					storyboard->SetTargetProperty(width_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleX)");
					storyboard->SetTarget(width_anim, component);
					storyboard->Children->Append(width_anim);
				}
			}

			// backgroundColor
			const auto bg_color = animation->get_backgroundColor();
			if (!bg_color.empty()) {
				const auto color_anim = ref new Windows::UI::Xaml::Media::Animation::ColorAnimation();
				const auto color = ColorForName(bg_color);
				color_anim->To = color;
				color_anim->EasingFunction = ease;

				if (is_panel__) {
					storyboard->SetTargetProperty(color_anim, "(Panel.Background).(SolidColorBrush.Color)");
				} else if (is_control__) {
					storyboard->SetTargetProperty(color_anim, "(Control.Background).(SolidColorBrush.Color)");
				}
				storyboard->SetTarget(color_anim, component);
				storyboard->Children->Append(color_anim);
			}

			// color
			const auto fg_color = animation->get_color();
			if (!fg_color.empty()) {
				const auto color_anim = ref new Windows::UI::Xaml::Media::Animation::ColorAnimation();
				const auto color = ColorForName(fg_color);
				color_anim->To = color;
				color_anim->EasingFunction = ease;

				if (is_panel__) {
					storyboard->SetTargetProperty(color_anim, "(Panel.Background).(SolidColorBrush.Color)");
				} else if (is_control__) {
					storyboard->SetTargetProperty(color_anim, "(Control.Background).(SolidColorBrush.Color)");
				}
				storyboard->SetTarget(color_anim, component);
				storyboard->Children->Append(color_anim);
			}

			// opacity
			const auto opacity = animation->get_opacity();
			if (opacity) {
				const auto double_anim = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
				double_anim->To = *opacity;
				double_anim->EasingFunction = ease;

				storyboard->SetTargetProperty(double_anim, "Opacity");
				storyboard->SetTarget(double_anim, component);
				storyboard->Children->Append(double_anim);
			}

			// zIndex
			const auto zIndex = animation->get_zIndex();
			if (zIndex) {
				const auto zIndex_anim = ref new Windows::UI::Xaml::Media::Animation::ObjectAnimationUsingKeyFrames();
			
				const auto current_zIndex = Windows::UI::Xaml::Controls::Canvas::GetZIndex(component);
				// FIXME This just transitions from current zIndex to new all at once at end of animation. We need to do our own interpolation based on the curve!
				const auto start_frame = ref new Windows::UI::Xaml::Media::Animation::DiscreteObjectKeyFrame();
				start_frame->Value = current_zIndex;
				Windows::Foundation::TimeSpan start_timespan;
				start_timespan.Duration = 0;
				Windows::UI::Xaml::Media::Animation::KeyTime start_time;
				start_time.TimeSpan = start_timespan;
				start_frame->KeyTime = start_time;
				zIndex_anim->KeyFrames->Append(start_frame);

				const auto end_frame = ref new Windows::UI::Xaml::Media::Animation::DiscreteObjectKeyFrame();
				end_frame->Value = *zIndex;
				end_frame->KeyTime = Windows::UI::Xaml::Media::Animation::KeyTimeHelper::FromTimeSpan(duration);
				zIndex_anim->KeyFrames->Append(end_frame);

				storyboard->SetTargetProperty(zIndex_anim, "(Canvas.ZIndex)");
				storyboard->SetTarget(zIndex_anim, component);
				storyboard->Children->Append(zIndex_anim);
			}

			storyboard->Completed += ref new Windows::Foundation::EventHandler<Platform::Object ^>([callback, this_object, animation](Platform::Object^ sender, Platform::Object ^ e) mutable {
				if (callback.IsFunction()) {
					callback(this_object);
				}
				animation->fireEvent("complete");
			});
			animation->fireEvent("start");
			storyboard->Begin();
		}

		void WindowsViewLayoutDelegate::set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundColor(backgroundColor);

			const auto background = ref new Windows::UI::Xaml::Media::SolidColorBrush(ColorForName(backgroundColor));

			if (is_panel__) {
				dynamic_cast<Windows::UI::Xaml::Controls::Panel^>(component__)->Background = background;
			} else if (is_control__) {
				dynamic_cast<Windows::UI::Xaml::Controls::Control^>(component__)->Background = background;
			} else {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::set_backgroundColor: Unknown component");
			}
		}

		void WindowsViewLayoutDelegate::set_borderColor(const std::string& borderColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_borderColor(borderColor);
		}

		void WindowsViewLayoutDelegate::set_borderRadius(const uint32_t& borderRadius) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_borderRadius(borderRadius);
		}

		void WindowsViewLayoutDelegate::set_borderWidth(const uint32_t& borderWidth) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_borderWidth(borderWidth);

			if (is_control__) {
				dynamic_cast<Windows::UI::Xaml::Controls::Control^>(component__)->BorderThickness = borderWidth;
			} else {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::set_borderWidth: Unknown component");
			}
		}

		void WindowsViewLayoutDelegate::set_opacity(const double& opacity) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_opacity(opacity);
			getComponent()->Opacity = opacity;
		}

		Titanium::UI::Dimension WindowsViewLayoutDelegate::get_rect() const TITANIUM_NOEXCEPT
		{
			Titanium::UI::Dimension d;
			d.x = static_cast<uint32_t>(std::round(oldRect__.x));
			d.y = static_cast<uint32_t>(std::round(oldRect__.y));
			d.width = static_cast<uint32_t>(std::round(oldRect__.width));
			d.height = static_cast<uint32_t>(std::round(oldRect__.height));
			return d;
		}

		Titanium::UI::Dimension WindowsViewLayoutDelegate::get_size() const TITANIUM_NOEXCEPT
		{
			Titanium::UI::Dimension d;
			d.x = 0;
			d.y = 0;
			d.width = static_cast<uint32_t>(std::round(oldRect__.width));
			d.height = static_cast<uint32_t>(std::round(oldRect__.height));
			return d;
		}
		void WindowsViewLayoutDelegate::set_tintColor(const std::string& tintColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_tintColor(tintColor);
		}

		void WindowsViewLayoutDelegate::set_touchEnabled(const bool& touchEnabled) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_touchEnabled(touchEnabled);
		}

		void WindowsViewLayoutDelegate::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_top(top);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void WindowsViewLayoutDelegate::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_left(left);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void WindowsViewLayoutDelegate::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_bottom(bottom);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void WindowsViewLayoutDelegate::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_right(right);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void WindowsViewLayoutDelegate::set_center(const Titanium::UI::Point& center) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_center(center);
		}

		void WindowsViewLayoutDelegate::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_width(width);
			if (width == "auto") {
				setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, Titanium::UI::Constants::to_string(get_autoLayoutForWidth()));
			} else {
				setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
			}
			is_width_size__ = layout_node__->properties.width.valueType == Titanium::LayoutEngine::ValueType::Size;
		}

		void WindowsViewLayoutDelegate::set_minWidth(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_minWidth(width);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::MinWidth, width);
		}

		void WindowsViewLayoutDelegate::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_height(height);
			if (height == "auto") {
				setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, Titanium::UI::Constants::to_string(get_autoLayoutForHeight()));
			} else {
				setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
			}
			is_height_size__ = layout_node__->properties.height.valueType == Titanium::LayoutEngine::ValueType::Size;
		}

		void WindowsViewLayoutDelegate::set_minHeight(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_minHeight(height);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::MinHeight, height);
		}

		void WindowsViewLayoutDelegate::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_layout(layout);

			if (layout == "horizontal") {
				layout_node__->element.layoutType = Titanium::LayoutEngine::LayoutType::Horizontal;
			} else if (layout == "vertical") {
				layout_node__->element.layoutType = Titanium::LayoutEngine::LayoutType::Vertical;
			} else {
				layout_node__->element.layoutType = Titanium::LayoutEngine::LayoutType::Composite;
			}

			if (isLoaded()) {
				requestLayout();
			}
		}

		void WindowsViewLayoutDelegate::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			if (event_name == "focus") {
				getComponent()->GotFocus -= focus_event__;
				return;
			} else if (event_name == "postlayout") {
				postlayout_listening__ = false;
				return;
			}
		}

		void WindowsViewLayoutDelegate::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			 if (event_name == "focus") {
				 focus_event__ = getComponent()->GotFocus += ref new Windows::UI::Xaml::RoutedEventHandler([this](Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
				 	auto event_delegate = event_delegate__.lock();
				 	if (event_delegate != nullptr) {
					 	JSContext js_context = event_delegate->get_context();
						JSObject eventArgs = js_context.CreateObject();
						eventArgs.SetProperty("source", event_delegate->get_object());
						event_delegate->fireEvent("focus", eventArgs);
				 	}
				});
				return;
			 } else if (event_name == "postlayout") {
				 postlayout_listening__ = true;
				 return;
			 }
		}

		static void onLayoutCallback(Titanium::LayoutEngine::Node* node)
		{
			auto view = static_cast<WindowsViewLayoutDelegate*>(node->data);
			auto rect = Titanium::LayoutEngine::RectMake(node->element.measuredLeft, node->element.measuredTop, node->element.measuredWidth, node->element.measuredHeight);
			view->onLayoutEngineCallback(rect, node->name);
		}

		void WindowsViewLayoutDelegate::setComponent(Windows::UI::Xaml::FrameworkElement^ component)
		{
			using namespace Windows::UI::Xaml;
			using namespace Windows::UI::Xaml::Controls;

			TITANIUM_ASSERT(component__ == nullptr);

			component__  = component;
			is_panel__   = dynamic_cast<Windows::UI::Xaml::Controls::Panel^>(component__) != nullptr;
			is_control__ = dynamic_cast<Windows::UI::Xaml::Controls::Control^>(component__) != nullptr;

			loaded_event__ = component__->Loaded += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				auto component = getComponent();
				auto rect = Titanium::LayoutEngine::RectMake(
					Canvas::GetLeft(component),
					Canvas::GetTop(component),
					component->ActualWidth,
					component->ActualHeight
				);

				onComponentLoaded(rect);
			});

			size_change_event__ = component__->SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler([this](Platform::Object^ sender, SizeChangedEventArgs^ e) {
				auto component = getComponent();
				auto rect = Titanium::LayoutEngine::RectMake(
					Canvas::GetLeft(component),
					Canvas::GetTop(component),
					e->NewSize.Width,
					e->NewSize.Height
				);

				onComponentSizeChange(rect);
			});

			layout_node__ = new Titanium::LayoutEngine::Node;
			layout_node__->data = this;
			layout_node__->onLayout = onLayoutCallback;

			if (get_defaultWidth() == Titanium::UI::LAYOUT::SIZE) {
				is_width_size__ = true;
				layout_node__->properties.defaultWidthType = Titanium::LayoutEngine::ValueType::Size;
			} else if (get_defaultWidth() == Titanium::UI::LAYOUT::FILL) {
				layout_node__->properties.defaultWidthType = Titanium::LayoutEngine::ValueType::Fill;
			}

			if (get_defaultHeight() == Titanium::UI::LAYOUT::SIZE) {
				is_height_size__ = true;
				layout_node__->properties.defaultHeightType = Titanium::LayoutEngine::ValueType::Size;
			} else if (get_defaultHeight() == Titanium::UI::LAYOUT::FILL) {
				layout_node__->properties.defaultHeightType = Titanium::LayoutEngine::ValueType::Fill;
			}
		}

		void WindowsViewLayoutDelegate::onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name)
		{
			using namespace Windows::UI::Xaml::Controls;
			using namespace Windows::UI::Xaml;
			if (is_height_size__ && rect.height == 0)
				return;
			if (is_width_size__ && rect.width == 0)
				return;
			if (rect.width < 0 || rect.height < 0)
				return;
			if (Titanium::LayoutEngine::RectIsEmpty(rect))
				return;
			if (Titanium::LayoutEngine::RectIsEqualToRect(oldRect__, rect))
				return;

			auto component = getComponent();
			auto panel = is_panel__ ? safe_cast<Panel^>(component) : nullptr;
			auto parentLayout = layout_node__->parent;

			auto setWidth = false;
			auto setHeight = false;
			auto setWidthOnWidget = !is_width_size__;
			auto setHeightOnWidget = !is_height_size__;

			if (!is_panel__ && is_width_size__ && parentLayout != nullptr) {
				if (rect.width > parentLayout->element.measuredWidth && parentLayout->element.measuredWidth > 0) {
					rect.width = parentLayout->element.measuredWidth;
					setWidthOnWidget = true;
				} else if (layout_node__->properties.width.valueType == Titanium::LayoutEngine::Fixed) {
					setWidthOnWidget = true;
				}
			}

			if (!is_panel__ && is_height_size__ && parentLayout != nullptr) {
				if (rect.height > parentLayout->element.measuredHeight && parentLayout->element.measuredHeight > 0) {
					rect.height = parentLayout->element.measuredHeight;
					setHeightOnWidget = true;
				} else if (layout_node__->properties.height.valueType == Titanium::LayoutEngine::Fixed) {
					setHeightOnWidget = true;
				}
			}

			// Use actual size when LayoutEngine does nothing against the component size
			if (rect.height <= 0) {
				rect.height = component->ActualHeight;
			}
			if (rect.width <= 0) {
				rect.width = component->ActualWidth;
			}

			oldRect__ = Titanium::LayoutEngine::RectMake(rect.x, rect.y, rect.width, rect.height);

			if (is_panel__) {
				for (auto child : panel->Children) {
					child->Visibility = Visibility::Collapsed;
				}

				setWidth = true;
				setHeight = true;
			}

			if ((!is_panel__ && setWidthOnWidget) || setWidth) {
				component->Width = rect.width;
			}

			if ((!is_panel__ && setHeightOnWidget) || setHeight) {
				component->Height = rect.height;
			}

			Canvas::SetLeft(component, rect.x);
			Canvas::SetTop(component, rect.y);

			if (is_panel__) {
				for (auto child : panel->Children) {
					child->Visibility = Visibility::Visible;
				}
			}
		}

		void WindowsViewLayoutDelegate::requestLayout(const bool& fire_event)
		{
			auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node__);
			if (root) {
				Titanium::LayoutEngine::nodeLayout(root);
				if (fire_event && postlayout_listening__) {
				 	auto event_delegate = event_delegate__.lock();
				 	if (event_delegate != nullptr) {
						// Fire postlayout event
						JSContext js_context = event_delegate->get_context();
						JSObject  eventArgs = js_context.CreateObject();
						eventArgs.SetProperty("source", event_delegate->get_object());
						event_delegate->fireEvent("postlayout", eventArgs);
					}
				}
			}
		}

		void WindowsViewLayoutDelegate::onComponentLoaded(const Titanium::LayoutEngine::Rect& rect)
		{
			is_loaded__ = true;
			requestLayout(true);
		}

		Titanium::LayoutEngine::Rect WindowsViewLayoutDelegate::computeRelativeSize(const double& x, const double& y, const double& baseWidth, const double& baseHeight) {
			auto width  = baseWidth;
			auto height = baseHeight;

			const auto is_height_size = layout_node__->properties.height.valueType == Titanium::LayoutEngine::Size;
			const auto is_width_size  = layout_node__->properties.width.valueType  == Titanium::LayoutEngine::Size;

			// compute its fixed size when either width or height (not both) is Ti.UI.SIZE
			if ((is_width_size != is_height_size) && (is_width_size || is_height_size)) {
				if (is_width_size) {
					height = layout_node__->properties.height.value;
					width = baseWidth  * (height / baseHeight);
				} else {
					width = layout_node__->properties.width.value;
					height = baseHeight * (width / baseWidth);
				}
			}

			return Titanium::LayoutEngine::RectMake(x, y, width, height);
		}

		void WindowsViewLayoutDelegate::onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect)
		{
			bool needsLayout = false;

			if (is_width_size__ && !is_panel__) {
				layout_node__->properties.width.value = rect.width;
				layout_node__->properties.width.valueType = Titanium::LayoutEngine::Fixed;
				needsLayout = isLoaded();
			}

			if (is_height_size__ && !is_panel__) {
				layout_node__->properties.height.value = rect.height;
				layout_node__->properties.height.valueType = Titanium::LayoutEngine::Fixed;
				needsLayout = isLoaded();
			}

			if (needsLayout) {
				requestLayout(true);
			}
		}


		void WindowsViewLayoutDelegate::setLayoutProperty(const Titanium::LayoutEngine::ValueName& name, const std::string& value)
		{
			Titanium::LayoutEngine::InputProperty prop;
			prop.name = name;
			prop.value = value;

			if (prop.value == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)) {
				prop.value = "UI.SIZE";
			} else if (prop.value == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL)) {
				prop.value = "UI.FILL";
			}

			Titanium::LayoutEngine::populateLayoutPoperties(prop, &layout_node__->properties, 1);

			if (isLoaded()) {
				requestLayout();
			}
		}

		/////////// Color //////////////

		inline bool isASCIIHexDigit(char c)
		{
			return (c >= '0' && c <= '9') || ((c | 0x20) >= 'a' && (c | 0x20) <= 'f');
		}

		inline int toASCIIHexValue(char c)
		{
			return (c & 0xF) + (c < 'A' ? 0 : 9);
		}

		Windows::UI::Color WindowsViewLayoutDelegate::ColorForHexCode(const std::string& hexCode)
		{
			unsigned length = hexCode.size();
			unsigned char alpha = 255;
			if ((length != 3) && (length != 4) && (length != 6) && (length != 7) && (length != 8)) {
				TITANIUM_LOG_WARN("View::ColorForHexCode: invalid hexCode = ", hexCode);
				return Windows::UI::Colors::Transparent;
			}
			unsigned value = 0;

			for (size_t i = 0; i < length; ++i) {
				unsigned char thisChar = hexCode[i];
				if (thisChar == '#')
					continue;
				if (!isASCIIHexDigit(thisChar)) {
					return Windows::UI::Colors::Transparent;
				}
				value <<= 4;
				value |= toASCIIHexValue(thisChar);
			}

			if (length < 6) {
				value = ((value & 0xF000) << 16) |
				        ((value & 0xFF00) << 12) |
				        ((value & 0xFF0) << 8) |
				        ((value & 0xFF) << 4) |
				        (value & 0xF);
			}

			if ((length % 4) == 0) {
				alpha = ((value >> 24) & 0xFF) * 255;
			}

			int red = (value >> 16) & 0xFF;
			int green = (value >> 8) & 0xFF;
			int blue = value & 0xFF;
			return Windows::UI::ColorHelper::FromArgb(alpha, red, green, blue);
		}

#if defined(INSERT_WINDOWS_UI_COLOR)
#error "LOGIC ERROR: INSERT_WINDOWS_UI_COLOR already defined."
#endif

		inline std::string toLowerCase(const std::string& string)
		{
			std::string copy(string);
			std::transform(string.begin(), string.end(), copy.begin(), std::tolower);
			return copy;
		}

#define INSERT_WINDOWS_UI_COLOR(COLOR_NAME) color_name_map.insert(std::make_pair(toLowerCase(#COLOR_NAME), Windows::UI::Colors::##COLOR_NAME));

		// Can this be optimized? MS is giving a lot of choices for colors!
		Windows::UI::Color WindowsViewLayoutDelegate::ColorForName(const std::string& colorName)
		{
			// pre condition
			TITANIUM_ASSERT(!colorName.empty());

			static const Windows::UI::Color defaultColor = Windows::UI::Colors::Transparent;
			using ColorNameMap_t = std::unordered_map<std::string, Windows::UI::Color>;
			static ColorNameMap_t color_name_map;
			static std::once_flag of;
			std::call_once(of, [] {
			INSERT_WINDOWS_UI_COLOR(AliceBlue);
			INSERT_WINDOWS_UI_COLOR(AntiqueWhite);
			INSERT_WINDOWS_UI_COLOR(Aqua);
			INSERT_WINDOWS_UI_COLOR(Aquamarine);
			INSERT_WINDOWS_UI_COLOR(Azure);
			INSERT_WINDOWS_UI_COLOR(Beige);
			INSERT_WINDOWS_UI_COLOR(Bisque);
			INSERT_WINDOWS_UI_COLOR(Black);
			INSERT_WINDOWS_UI_COLOR(BlanchedAlmond);
			INSERT_WINDOWS_UI_COLOR(Blue);
			INSERT_WINDOWS_UI_COLOR(BlueViolet);
			INSERT_WINDOWS_UI_COLOR(Brown);
			INSERT_WINDOWS_UI_COLOR(BurlyWood);
			INSERT_WINDOWS_UI_COLOR(CadetBlue);
			INSERT_WINDOWS_UI_COLOR(Chartreuse);
			INSERT_WINDOWS_UI_COLOR(Chocolate);
			INSERT_WINDOWS_UI_COLOR(Coral);
			INSERT_WINDOWS_UI_COLOR(CornflowerBlue);
			INSERT_WINDOWS_UI_COLOR(Cornsilk);
			INSERT_WINDOWS_UI_COLOR(Crimson);
			INSERT_WINDOWS_UI_COLOR(Cyan);
			INSERT_WINDOWS_UI_COLOR(DarkBlue);
			INSERT_WINDOWS_UI_COLOR(DarkCyan);
			INSERT_WINDOWS_UI_COLOR(DarkGoldenrod);
			INSERT_WINDOWS_UI_COLOR(DarkGray);
			INSERT_WINDOWS_UI_COLOR(DarkGreen);
			INSERT_WINDOWS_UI_COLOR(DarkKhaki);
			INSERT_WINDOWS_UI_COLOR(DarkMagenta);
			INSERT_WINDOWS_UI_COLOR(DarkOliveGreen);
			INSERT_WINDOWS_UI_COLOR(DarkOrange);
			INSERT_WINDOWS_UI_COLOR(DarkOrchid);
			INSERT_WINDOWS_UI_COLOR(DarkRed);
			INSERT_WINDOWS_UI_COLOR(DarkSalmon);
			INSERT_WINDOWS_UI_COLOR(DarkSeaGreen);
			INSERT_WINDOWS_UI_COLOR(DarkSlateBlue);
			INSERT_WINDOWS_UI_COLOR(DarkSlateGray);
			INSERT_WINDOWS_UI_COLOR(DarkTurquoise);
			INSERT_WINDOWS_UI_COLOR(DarkViolet);
			INSERT_WINDOWS_UI_COLOR(DeepPink);
			INSERT_WINDOWS_UI_COLOR(DeepSkyBlue);
			INSERT_WINDOWS_UI_COLOR(DimGray);
			INSERT_WINDOWS_UI_COLOR(DodgerBlue);
			INSERT_WINDOWS_UI_COLOR(Firebrick);
			INSERT_WINDOWS_UI_COLOR(FloralWhite);
			INSERT_WINDOWS_UI_COLOR(ForestGreen);
			INSERT_WINDOWS_UI_COLOR(Fuchsia);
			INSERT_WINDOWS_UI_COLOR(Gainsboro);
			INSERT_WINDOWS_UI_COLOR(GhostWhite);
			INSERT_WINDOWS_UI_COLOR(Gold);
			INSERT_WINDOWS_UI_COLOR(Goldenrod);
			INSERT_WINDOWS_UI_COLOR(Gray);
			INSERT_WINDOWS_UI_COLOR(Green);
			INSERT_WINDOWS_UI_COLOR(GreenYellow);
			INSERT_WINDOWS_UI_COLOR(Honeydew);
			INSERT_WINDOWS_UI_COLOR(HotPink);
			INSERT_WINDOWS_UI_COLOR(IndianRed);
			INSERT_WINDOWS_UI_COLOR(Indigo);
			INSERT_WINDOWS_UI_COLOR(Ivory);
			INSERT_WINDOWS_UI_COLOR(Khaki);
			INSERT_WINDOWS_UI_COLOR(Lavender);
			INSERT_WINDOWS_UI_COLOR(LavenderBlush);
			INSERT_WINDOWS_UI_COLOR(LawnGreen);
			INSERT_WINDOWS_UI_COLOR(LemonChiffon);
			INSERT_WINDOWS_UI_COLOR(LightBlue);
			INSERT_WINDOWS_UI_COLOR(LightCoral);
			INSERT_WINDOWS_UI_COLOR(LightCyan);
			INSERT_WINDOWS_UI_COLOR(LightGoldenrodYellow);
			INSERT_WINDOWS_UI_COLOR(LightGray);
			INSERT_WINDOWS_UI_COLOR(LightGreen);
			INSERT_WINDOWS_UI_COLOR(LightPink);
			INSERT_WINDOWS_UI_COLOR(LightSalmon);
			INSERT_WINDOWS_UI_COLOR(LightSeaGreen);
			INSERT_WINDOWS_UI_COLOR(LightSkyBlue);
			INSERT_WINDOWS_UI_COLOR(LightSlateGray);
			INSERT_WINDOWS_UI_COLOR(LightSteelBlue);
			INSERT_WINDOWS_UI_COLOR(LightYellow);
			INSERT_WINDOWS_UI_COLOR(Lime);
			INSERT_WINDOWS_UI_COLOR(LimeGreen);
			INSERT_WINDOWS_UI_COLOR(Linen);
			INSERT_WINDOWS_UI_COLOR(Magenta);
			INSERT_WINDOWS_UI_COLOR(Maroon);
			INSERT_WINDOWS_UI_COLOR(MediumAquamarine);
			INSERT_WINDOWS_UI_COLOR(MediumBlue);
			INSERT_WINDOWS_UI_COLOR(MediumOrchid);
			INSERT_WINDOWS_UI_COLOR(MediumPurple);
			INSERT_WINDOWS_UI_COLOR(MediumSeaGreen);
			INSERT_WINDOWS_UI_COLOR(MediumSlateBlue);
			INSERT_WINDOWS_UI_COLOR(MediumSpringGreen);
			INSERT_WINDOWS_UI_COLOR(MediumTurquoise);
			INSERT_WINDOWS_UI_COLOR(MediumVioletRed);
			INSERT_WINDOWS_UI_COLOR(MidnightBlue);
			INSERT_WINDOWS_UI_COLOR(MintCream);
			INSERT_WINDOWS_UI_COLOR(MistyRose);
			INSERT_WINDOWS_UI_COLOR(Moccasin);
			INSERT_WINDOWS_UI_COLOR(NavajoWhite);
			INSERT_WINDOWS_UI_COLOR(Navy);
			INSERT_WINDOWS_UI_COLOR(OldLace);
			INSERT_WINDOWS_UI_COLOR(Olive);
			INSERT_WINDOWS_UI_COLOR(OliveDrab);
			INSERT_WINDOWS_UI_COLOR(Orange);
			INSERT_WINDOWS_UI_COLOR(OrangeRed);
			INSERT_WINDOWS_UI_COLOR(Orchid);
			INSERT_WINDOWS_UI_COLOR(PaleGoldenrod);
			INSERT_WINDOWS_UI_COLOR(PaleGreen);
			INSERT_WINDOWS_UI_COLOR(PaleTurquoise);
			INSERT_WINDOWS_UI_COLOR(PaleVioletRed);
			INSERT_WINDOWS_UI_COLOR(PapayaWhip);
			INSERT_WINDOWS_UI_COLOR(PeachPuff);
			INSERT_WINDOWS_UI_COLOR(Peru);
			INSERT_WINDOWS_UI_COLOR(Pink);
			INSERT_WINDOWS_UI_COLOR(Plum);
			INSERT_WINDOWS_UI_COLOR(PowderBlue);
			INSERT_WINDOWS_UI_COLOR(Purple);
			INSERT_WINDOWS_UI_COLOR(Red);
			INSERT_WINDOWS_UI_COLOR(RosyBrown);
			INSERT_WINDOWS_UI_COLOR(RoyalBlue);
			INSERT_WINDOWS_UI_COLOR(SaddleBrown);
			INSERT_WINDOWS_UI_COLOR(Salmon);
			INSERT_WINDOWS_UI_COLOR(SandyBrown);
			INSERT_WINDOWS_UI_COLOR(SeaGreen);
			INSERT_WINDOWS_UI_COLOR(SeaShell);
			INSERT_WINDOWS_UI_COLOR(Sienna);
			INSERT_WINDOWS_UI_COLOR(Silver);
			INSERT_WINDOWS_UI_COLOR(SkyBlue);
			INSERT_WINDOWS_UI_COLOR(SlateBlue);
			INSERT_WINDOWS_UI_COLOR(SlateGray);
			INSERT_WINDOWS_UI_COLOR(Snow);
			INSERT_WINDOWS_UI_COLOR(SpringGreen);
			INSERT_WINDOWS_UI_COLOR(SteelBlue);
			INSERT_WINDOWS_UI_COLOR(Tan);
			INSERT_WINDOWS_UI_COLOR(Teal);
			INSERT_WINDOWS_UI_COLOR(Thistle);
			INSERT_WINDOWS_UI_COLOR(Tomato);
			INSERT_WINDOWS_UI_COLOR(Transparent);
			INSERT_WINDOWS_UI_COLOR(Turquoise);
			INSERT_WINDOWS_UI_COLOR(Violet);
			INSERT_WINDOWS_UI_COLOR(Wheat);
			INSERT_WINDOWS_UI_COLOR(White);
			INSERT_WINDOWS_UI_COLOR(WhiteSmoke);
			INSERT_WINDOWS_UI_COLOR(Yellow);
			INSERT_WINDOWS_UI_COLOR(YellowGreen);
			});

			if (colorName[0] == '#') {
				return ColorForHexCode(colorName.substr(1));
			}

			auto position = color_name_map.find(toLowerCase(colorName));

			Windows::UI::Color color = defaultColor;
			if (position != color_name_map.end()) {
				color = position->second;
			}

			return color;
		}
	} // namespace UI
}  // namespace Titanium
