/**
 * TitaniumKit ViewLayoutDelegate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Animation.hpp"
#include "Titanium/UI/2DMatrix.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/App.hpp"
#include "Titanium/Blob.hpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <windows.h>
#include <ppltasks.h>
#include <concrt.h>
#include <collection.h>

#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include "TitaniumWindows/LogForwarder.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Controls;
		using namespace Windows::UI::Xaml::Input;
		using namespace Windows::UI::Xaml::Media;
		using namespace Windows::Storage::Streams;

		FrameworkElementWrapper::FrameworkElementWrapper(const JSContext& ctx) TITANIUM_NOEXCEPT
			: Titanium::UI::View(ctx, "Windows.UI.Xaml.UIElement") 
		{

		}

		void FrameworkElementWrapper::JSExportInitialize()
		{
			JSExport<FrameworkElementWrapper>::SetClassVersion(1);
			JSExport<FrameworkElementWrapper>::SetParent(JSExport<Titanium::UI::View>::Class());
		}

		void FrameworkElementWrapper::setComponent(FrameworkElement^ element) TITANIUM_NOEXCEPT
		{
			element__ = element;
			Titanium::UI::View::setLayoutDelegate<WindowsViewLayoutDelegate>();
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(element__);

		}

		WindowsViewLayoutDelegate::WindowsViewLayoutDelegate() TITANIUM_NOEXCEPT
			: ViewLayoutDelegate()
		{
			TITANIUM_LOG_DEBUG("WindowsViewLayoutDelegate::ctor ", this);
		}

		WindowsViewLayoutDelegate::~WindowsViewLayoutDelegate() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("WindowsViewLayoutDelegate::dtor ", this);
			if (component__) {
				component__->SizeChanged -= size_change_event__;
				component__->Loaded -= loaded_event__;
				component__->GotFocus -= update_background_event__;
				component__->LostFocus -= reset_background_event__;
				if (is_control__) {
					dynamic_cast<Control^>(component__)->IsEnabledChanged -= enabled_changed_event__;
				}
			}
			// make sure it is deleted from parent node, otherwise LayoutEngine crashes!
			delete layout_node__;
		}

		std::shared_ptr<Titanium::UI::View> WindowsViewLayoutDelegate::rescueGetView(const JSObject& view) TITANIUM_NOEXCEPT
		{
			const auto ctx = view.get_context();
			const auto object_ptr = view.GetPrivate<TitaniumWindows::Platform_Object>();
			if (object_ptr) {
				auto elm_ctor  = ctx.CreateObject(JSExport<TitaniumWindows::UI::FrameworkElementWrapper>::Class());
				const auto elm = elm_ctor.CallAsConstructor();
				const auto elm_ptr = elm.GetPrivate<TitaniumWindows::UI::FrameworkElementWrapper>();
				const auto element = safe_cast<FrameworkElement^>(object_ptr->get_native_object());
				if (element) {
					elm_ptr->setComponent(element);
					return std::dynamic_pointer_cast<Titanium::UI::View>(elm_ptr);
				}
			}
			return nullptr;
		}

		void WindowsViewLayoutDelegate::blur()
		{
			TITANIUM_LOG_WARN("blur() is not supported on Windows");
		}

		void WindowsViewLayoutDelegate::focus()
		{
			if (is_control__) {
				dynamic_cast<Control^>(component__)->Focus(FocusState::Programmatic);
			} else {
				TITANIUM_LOG_WARN("focus() is not supported for this control");
			}
		}

		void WindowsViewLayoutDelegate::remove(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::remove(view);

			TITANIUM_LOG_DEBUG("WindowsViewLayoutDelegate::remove ", view.get(), " for ", this);

			if (!is_panel__) {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::remove: Unknown component");
				return;
			}

			auto newView = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			auto nativeChildView = newView->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeRemoveChild(layout_node__, newView->getLayoutNode());
				if (isLoaded()) {
					requestLayout();
				}
				try {
					uint32_t index = 0;
					auto nativeView = dynamic_cast<Controls::Panel^>(component__);
					auto found = nativeView->Children->IndexOf(nativeChildView, &index);
					if (found) {
						nativeView->Children->RemoveAt(index);
					} else {
						TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::remove: Component not in list of children");
					}
				}
				catch (Platform::Exception^ e) {
					detail::ThrowRuntimeError("remove", Utility::ConvertString(e->Message));
				}
			} else {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::remove: Unknown child component");
			}
		}

		void WindowsViewLayoutDelegate::add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::add(view);

			TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::add ", view.get(), " for ", this);

			if (!is_panel__) {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::add: Unknown component");
				return;
			}

			auto newView = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			TITANIUM_ASSERT(newView != nullptr);
			auto nativeChildView = newView->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeAddChild(layout_node__, newView->getLayoutNode());
				if (isLoaded()) {
					requestLayout();
				}
				try {
					auto nativeView = dynamic_cast<Controls::Panel^>(component__);
					nativeView->Children->Append(nativeChildView);
					newView->set_touchEnabled(get_touchEnabled() && newView->get_touchEnabled());
				} catch (Platform::Exception^ e) {
					detail::ThrowRuntimeError("add", Utility::ConvertString(e->Message));
				}
			} else {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::add: Unknown child component");
			}
		}

		void WindowsViewLayoutDelegate::insertAt(const Titanium::UI::ViewInsertOrReplaceParams& params) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::insertAt(params);

			if (!is_panel__) {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::insertAt: Unknown component");
				return;
			}

			auto newView = params.view->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			auto nativeChildView = newView->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeInsertChildAt(layout_node__, newView->getLayoutNode(), params.position);
				if (isLoaded()) {
					requestLayout();
				}
				try {
					auto nativeView = dynamic_cast<Controls::Panel^>(component__);
					nativeView->Children->InsertAt(params.position, nativeChildView);
				} catch (Platform::Exception^ e) {
					detail::ThrowRuntimeError("insertAt", Utility::ConvertString(e->Message));
				}
			} else {
				TITANIUM_LOG_WARN("WindowsViewLayoutDelegate::insertAt: Unknown child component");
			}
		}

		void WindowsViewLayoutDelegate::replaceAt(const Titanium::UI::ViewInsertOrReplaceParams& params) TITANIUM_NOEXCEPT
		{
			remove(get_children().at(params.position));
			insertAt(params);
		}

		void WindowsViewLayoutDelegate::set_visible(const bool& visible) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_visible(visible);
			getComponent()->Visibility = (visible ? Visibility::Visible : Visibility::Collapsed);
		}

		void WindowsViewLayoutDelegate::ToImage(Windows::UI::Xaml::FrameworkElement^ component, JSObject& callback, const JSObject& this_object)
		{
			using Windows::Graphics::Imaging::BitmapEncoder;

			TitaniumWindows::Utility::RunOnUIThread([component, this_object, callback]() {
				auto renderTargetBitmap = ref new Windows::UI::Xaml::Media::Imaging::RenderTargetBitmap();

				// render component as a BGRA8 bitmap
				concurrency::create_task(renderTargetBitmap->RenderAsync(component)).then([renderTargetBitmap]() {
					return renderTargetBitmap->GetPixelsAsync();

				// obtain rendered pixel data
				}).then([renderTargetBitmap, this_object, callback](concurrency::task<IBuffer^> task) {
					try {
						const auto pixelBuffer = task.get();
						const auto pngStream = ref new InMemoryRandomAccessStream();
						const auto pixelArray = TitaniumWindows::Utility::GetArrayFromBuffer(pixelBuffer);

						// encode pixel data into a PNG
						// NOTE: using PNG encoder to support transparency
						concurrency::create_task(BitmapEncoder::CreateAsync(BitmapEncoder::PngEncoderId, pngStream)).then(
							[renderTargetBitmap, pixelArray, pngStream](BitmapEncoder^ encoder) {
								encoder->SetPixelData(
									Windows::Graphics::Imaging::BitmapPixelFormat::Bgra8,
									Windows::Graphics::Imaging::BitmapAlphaMode::Straight,
									renderTargetBitmap->PixelWidth,
									renderTargetBitmap->PixelHeight,
									0,
									0,
									pixelArray
								);
								return encoder->FlushAsync();
							}

							// obtain encoded PNG stream
							).then([this_object, callback, pngStream](concurrency::task<void> previousTask) {
								try {
									previousTask.get();
									const auto pngBuffer = ref new Windows::Storage::Streams::Buffer(static_cast<unsigned int>(pngStream->Size));

									// write encoded PNG stream to PNG buffer
									concurrency::create_task(pngStream->ReadAsync(pngBuffer, pngBuffer->Capacity, Windows::Storage::Streams::InputStreamOptions::None)).then(
										[this_object, callback, pngBuffer](IBuffer^) {

										// create Titanium.Blob from PNG buffer
										const auto blob = this_object.get_context().CreateObject(JSExport<Titanium::Blob>::Class()).CallAsConstructor();
										const auto blob_ptr = blob.GetPrivate<Titanium::Blob>();
										blob_ptr->construct(TitaniumWindows::Utility::GetContentFromBuffer(pngBuffer));

										// call callback
										const std::vector<JSValue> args = { blob };
										auto cb = static_cast<JSObject>(callback);
										cb(args, this_object);
									});
								} catch (Platform::Exception^ e) {
									TITANIUMWINDOWS_EXCEPTION_SHOW_REDSCREEN(e, this_object);
								}
						});
					} catch (Platform::Exception^ e) {
						TITANIUMWINDOWS_EXCEPTION_SHOW_REDSCREEN(e, this_object);
					}
				});
			});
		}

		std::shared_ptr<Titanium::Blob> WindowsViewLayoutDelegate::toImage(JSObject& callback, const bool& honorScaleFactor, const JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (callback.IsFunction()) {
				ToImage(getComponent(), callback, this_object);
			} else {
				HAL::detail::ThrowRuntimeError("View.toImage", "View.toImage only works using the callback parameter on Windows");
			}
			return nullptr;
		}

		void WindowsViewLayoutDelegate::animate(const std::shared_ptr<Titanium::UI::Animation>& animation, JSObject& callback, const JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (!is_loaded__) {
				// add animate call to queue, layout has not loaded...
				animate_queue__.push_back({animation, callback, this_object});
				return;
			}

			// TIMOB-23209: Multiple layout trasnformations (position or size) can't done at a time.
			const auto hasLayoutTransform = animation->hasLayoutTransform();
			if (hasLayoutTransform && is_transforming_layout__) {
				TITANIUM_MODULE_LOG_WARN("New layout set while view animating");
				return;
			}
			is_transforming_layout__ = hasLayoutTransform;

			// Storyboard where we attach all the animations
			const auto storyboard = ref new Media::Animation::Storyboard();

			// delay
			const std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> delay_ticks = animation->get_delay();
			Windows::Foundation::TimeSpan delay = Windows::Foundation::TimeSpan();
			delay.Duration = delay_ticks.count();
			storyboard->BeginTime = delay; // FIXME This seems to apply to every iteration of repeat, but we probably only want it to happen the first time?

			// duration
			const std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = animation->get_duration();
			Windows::Foundation::TimeSpan duration = Windows::Foundation::TimeSpan();
			duration.Duration = timer_interval_ticks.count();
			storyboard->Duration = duration;

			// autoreverse
			storyboard->AutoReverse = animation->get_autoreverse();

			// repeat
			const double repeat = animation->get_repeat();
			if (repeat == 0) {
				storyboard->RepeatBehavior = Media::Animation::RepeatBehaviorHelper::Forever;
			} else if (repeat != 1) {
				storyboard->RepeatBehavior = Media::Animation::RepeatBehaviorHelper::FromCount(repeat);
			}

			// curve/ease
			const auto curve = animation->get_curve();
			// TODO Expand the set of animation curves available to encompass all the ones from Windows!
			// http://iphonedevelopment.blogspot.com/2010/12/more-animation-curves-than-you-can.html
			// Here's where iOS defines it's Bezier control points!
			// https://developer.apple.com/library/mac/documentation/Cocoa/Reference/CAMediaTimingFunction_class/index.html#//apple_ref/doc/constant_group/Predefined_Timing_Functions
			// There are no equivalent easing functions on Windows!!!! They look/behave differently.
			// You can compare the values used here: http://easings.net/
			Media::Animation::EasingFunctionBase^ ease;
			switch (curve) {
			case Titanium::UI::ANIMATION_CURVE::EASE_IN:
				ease = ref new Media::Animation::CubicEase();
				ease->EasingMode = Media::Animation::EasingMode::EaseIn;
				break;
			case Titanium::UI::ANIMATION_CURVE::EASE_IN_OUT:
				ease = ref new Media::Animation::CubicEase();
				ease->EasingMode = Media::Animation::EasingMode::EaseInOut;
				break;
			case Titanium::UI::ANIMATION_CURVE::EASE_OUT:
				ease = ref new Media::Animation::CubicEase();
				ease->EasingMode = Media::Animation::EasingMode::EaseOut;
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
				const auto group = ref new Media::TransformGroup();
				const auto translate = ref new Media::TranslateTransform();
				const auto rotate = ref new Media::RotateTransform();
				const auto composite = ref new Media::CompositeTransform(); // cheat and use composite to do scale and then skew
				group->Children->Append(translate);
				group->Children->Append(rotate);
				group->Children->Append(composite);

				component->RenderTransform = group;

				const auto rotation_anim = ref new Media::Animation::DoubleAnimation();
				rotation_anim->To = rotation;
				rotation_anim->EasingFunction = ease;
				rotation_anim->Duration = duration;
				storyboard->SetTargetProperty(rotation_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[1].(RotateTransform.Angle)");
				storyboard->SetTarget(rotation_anim, component);
				storyboard->Children->Append(rotation_anim);

				const auto scale_x_anim = ref new Media::Animation::DoubleAnimation();
				scale_x_anim->To = a;
				scale_x_anim->EasingFunction = ease;
				scale_x_anim->Duration = duration;
				storyboard->SetTargetProperty(scale_x_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleX)");
				storyboard->SetTarget(scale_x_anim, component);
				storyboard->Children->Append(scale_x_anim);

				const auto scale_y_anim = ref new Media::Animation::DoubleAnimation();
				scale_y_anim->To = d;
				scale_y_anim->EasingFunction = ease;
				scale_y_anim->Duration = duration;
				storyboard->SetTargetProperty(scale_y_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleY)");
				storyboard->SetTarget(scale_y_anim, component);
				storyboard->Children->Append(scale_y_anim);

				const auto tx_anim = ref new Media::Animation::DoubleAnimation();
				tx_anim->To = animation->get_transform()->get_tx();
				tx_anim->EasingFunction = ease;
				tx_anim->Duration = duration;
				storyboard->SetTargetProperty(tx_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateX)");
				storyboard->SetTarget(tx_anim, component);
				storyboard->Children->Append(tx_anim);

				const auto ty_anim = ref new Media::Animation::DoubleAnimation();
				ty_anim->To = animation->get_transform()->get_ty();
				ty_anim->EasingFunction = ease;
				ty_anim->Duration = duration;
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
				const auto group = ref new Media::TransformGroup();
				const auto translate = ref new Media::TranslateTransform();
				const auto rotate = ref new Media::RotateTransform();
				const auto composite = ref new Media::CompositeTransform(); // cheat and use composite to do scale and then skew
				const auto properties = std::make_shared<Titanium::LayoutEngine::LayoutProperties>();
				group->Children->Append(translate);
				group->Children->Append(rotate);
				group->Children->Append(composite);

				component->RenderTransform = group;

				const auto top = animation->get_top();
				if (top) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, *top, properties);
					const auto type = properties->top.valueType;
					auto value = properties->top.value;

					if (type == Titanium::LayoutEngine::ValueType::Percent) {
						value *= layout_node__->parent->element.measuredHeight;
					}

					const auto current_top = Controls::Canvas::GetTop(component);
					const auto diff = value - current_top;

					const auto top_anim = ref new Media::Animation::DoubleAnimation();
					top_anim->To = diff;
					top_anim->EasingFunction = ease;
					top_anim->Duration = duration;
					storyboard->SetTargetProperty(top_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateY)");
					storyboard->SetTarget(top_anim, component);
					storyboard->Children->Append(top_anim);
				}

				const auto bottom = animation->get_bottom();
				if (bottom) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, *bottom, properties);
					const auto type = properties->bottom.valueType;
					auto value = properties->bottom.value;

					if (type == Titanium::LayoutEngine::ValueType::Percent) {
						value *= layout_node__->parent->element.measuredHeight;
					}

					const auto current_top = Controls::Canvas::GetTop(component);
					const auto parent_height = layout_node__->parent->element.measuredHeight;
					const auto current_height = layout_node__->element.measuredHeight;
					const auto diff = (parent_height - current_height - value) - current_top;

					const auto bottom_anim = ref new Media::Animation::DoubleAnimation();
					bottom_anim->To = diff;
					bottom_anim->EasingFunction = ease;
					bottom_anim->Duration = duration;
					storyboard->SetTargetProperty(bottom_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateY)");
					storyboard->SetTarget(bottom_anim, component);
					storyboard->Children->Append(bottom_anim);
				}

				// TODO if they specify top AND bottom and DON'T specify height, we should translate top, and treat bottom - top as height.
				// If they specify bottom AND height, BUT NOT top; we should translate bottom and scale height?
				// If they specify just bottom, no top or height, just translate bottom?

				const auto left = animation->get_left();
				if (left) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, *left, properties);
					const auto type = properties->left.valueType;
					auto value = properties->left.value;

					if (type == Titanium::LayoutEngine::ValueType::Percent) {
						value *= layout_node__->parent->element.measuredWidth;
					}

					const auto current_left = Controls::Canvas::GetLeft(component);
					const auto diff = value - current_left;

					const auto left_anim = ref new Media::Animation::DoubleAnimation();
					left_anim->To = diff;
					left_anim->EasingFunction = ease;
					left_anim->Duration = duration;
					storyboard->SetTargetProperty(left_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateX)");
					storyboard->SetTarget(left_anim, component);
					storyboard->Children->Append(left_anim);
				}

				const auto right = animation->get_right();
				if (right) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, *right, properties);
					const auto type = properties->right.valueType;
					auto value = properties->right.value;

					if (type == Titanium::LayoutEngine::ValueType::Percent) {
						value *= layout_node__->parent->element.measuredWidth;
					}

					const auto current_left = Controls::Canvas::GetLeft(component);
					const auto parent_width = layout_node__->parent->element.measuredWidth;
					const auto current_width = layout_node__->element.measuredWidth;
					const auto diff = (parent_width - current_width - value) - current_left;

					const auto right_anim = ref new Media::Animation::DoubleAnimation();
					right_anim->To = diff;
					right_anim->EasingFunction = ease;
					right_anim->Duration = duration;
					storyboard->SetTargetProperty(right_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateX)");
					storyboard->SetTarget(right_anim, component);
					storyboard->Children->Append(right_anim);
				}

				const auto center = animation->get_center();
				if (center) {
					// x-axis
					auto x_value = center->x;
					if (!center->x_percent.empty()) {
						setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, center->x_percent, properties);
						x_value = properties->left.value;
						const auto x_type = properties->left.valueType;
						if (x_type == Titanium::LayoutEngine::ValueType::Percent) {
							x_value *= layout_node__->parent->element.measuredWidth;
						}
					}
					const auto current_left = Controls::Canvas::GetLeft(component);
					const auto x_diff = x_value - current_left;
					const auto x_anim = ref new Media::Animation::DoubleAnimation();
					x_anim->To = x_diff;
					x_anim->EasingFunction = ease;
					x_anim->Duration = duration;
					storyboard->SetTargetProperty(x_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateX)");
					storyboard->SetTarget(x_anim, component);
					storyboard->Children->Append(x_anim);

					//y-axis
					auto y_value = center->y;
					if (!center->y_percent.empty()) {
						setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, center->y_percent, properties);
						y_value = properties->right.value;
						const auto y_type = properties->right.valueType;
						if (y_type == Titanium::LayoutEngine::ValueType::Percent) {
							y_value *= layout_node__->parent->element.measuredHeight;
						}
					}
					const auto current_top = Controls::Canvas::GetTop(component);
					const auto y_diff = y_value - current_top;
					const auto y_anim = ref new Media::Animation::DoubleAnimation();
					y_anim->To = y_diff;
					y_anim->EasingFunction = ease;
					y_anim->Duration = duration;
					storyboard->SetTargetProperty(y_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(TranslateTransform.TranslateY)");
					storyboard->SetTarget(y_anim, component);
					storyboard->Children->Append(y_anim);
				}

				// For width and height, we have to calculate the scale to use to achieve desired height/width, since animating the Height or Width properties are ppor performance-wise and best avoided.
				const auto height = animation->get_height();
				if (height) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, *height, properties);
					const auto type = properties->height.valueType;
					auto value = properties->height.value;

					if (type == Titanium::LayoutEngine::ValueType::Percent) {
						value *= layout_node__->parent->element.measuredHeight;
					}

					const auto height_anim = ref new Media::Animation::DoubleAnimation();
					const auto current_height = component->Height > 0 ? component->Height : 1;
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, std::to_string(current_height));
					const auto scaleY = value / current_height;
					height_anim->To = scaleY;  // TODO Need to determine scale to use to achieve the desired height!
					height_anim->EasingFunction = ease;
					height_anim->Duration = duration;
					storyboard->SetTargetProperty(height_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleY)");
					storyboard->SetTarget(height_anim, component);
					storyboard->Children->Append(height_anim);
				}

				const auto width = animation->get_width();
				if (width) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, *width, properties);
					const auto type = properties->width.valueType;
					auto value = properties->width.value;

					if (type == Titanium::LayoutEngine::ValueType::Percent) {
						value *= layout_node__->parent->element.measuredWidth;
					}

					const auto width_anim = ref new Media::Animation::DoubleAnimation();
					const auto current_width = component->Width > 0 ? component->Width : 1;
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, std::to_string(current_width));
					const auto scaleX = value / current_width;
					width_anim->To = scaleX;
					width_anim->EasingFunction = ease;
					width_anim->Duration = duration;
					storyboard->SetTargetProperty(width_anim, "(UIElement.RenderTransform).(TransformGroup.Children)[2].(CompositeTransform.ScaleX)");
					storyboard->SetTarget(width_anim, component);
					storyboard->Children->Append(width_anim);
				}
			}

			// backgroundColor
			const auto bg_color = animation->get_backgroundColor();
			if (!bg_color.empty()) {
				const auto color_anim = ref new Media::Animation::ColorAnimation();
				const auto color = ColorForName(bg_color);
				color_anim->To = color;
				color_anim->EasingFunction = ease;
				color_anim->Duration = duration;

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
				const auto color_anim = ref new Media::Animation::ColorAnimation();
				const auto color = ColorForName(fg_color);
				color_anim->To = color;
				color_anim->EasingFunction = ease;
				color_anim->Duration = duration;

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
				const auto double_anim = ref new Media::Animation::DoubleAnimation();
				double_anim->To = *opacity;
				double_anim->EasingFunction = ease;
				double_anim->Duration = duration;

				storyboard->SetTargetProperty(double_anim, "Opacity");
				storyboard->SetTarget(double_anim, component);
				storyboard->Children->Append(double_anim);
			}

			// zIndex
			const auto zIndex = animation->get_zIndex();
			if (zIndex) {
				const auto zIndex_anim = ref new Media::Animation::ObjectAnimationUsingKeyFrames();
				zIndex_anim->Duration = duration;

				const auto current_zIndex = Controls::Canvas::GetZIndex(component);
				// FIXME This just transitions from current zIndex to new all at once at end of animation. We need to do our own interpolation based on the curve!
				const auto start_frame = ref new Media::Animation::DiscreteObjectKeyFrame();
				start_frame->Value = current_zIndex;
				Windows::Foundation::TimeSpan start_timespan;
				start_timespan.Duration = 0;
				Media::Animation::KeyTime start_time;
				start_time.TimeSpan = start_timespan;
				start_frame->KeyTime = start_time;
				zIndex_anim->KeyFrames->Append(start_frame);

				const auto end_frame = ref new Media::Animation::DiscreteObjectKeyFrame();
				end_frame->Value = *zIndex;
				end_frame->KeyTime = Media::Animation::KeyTimeHelper::FromTimeSpan(duration);
				zIndex_anim->KeyFrames->Append(end_frame);

				storyboard->SetTargetProperty(zIndex_anim, "(Canvas.ZIndex)");
				storyboard->SetTarget(zIndex_anim, component);
				storyboard->Children->Append(zIndex_anim);
			}

			storyboard->Completed += ref new Windows::Foundation::EventHandler<Platform::Object ^>([callback, animation, this_object, this](Platform::Object^ sender, Platform::Object ^ e) mutable {
				const auto storyboard = dynamic_cast<Media::Animation::Storyboard^>(sender);
				const auto component = getComponent();

				//
				// Make sure to update the position of the view because StoryBoard doesn't change actual position of it.
				//
				const auto top = animation->get_top();
				const auto bottom = animation->get_bottom();
				if (top) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, *top);
				} else if (bottom) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, "NONE");
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, *bottom);
				}

				const auto left = animation->get_left();
				const auto right = animation->get_right();
				if (left) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, *left);
				} else if (right) {
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, "NONE");
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, *right);
				}

				const auto center = animation->get_center();
				if (center) {
					std::string x = center->x_percent.empty() ? std::to_string(center->x) : center->x_percent;
					std::string y = center->y_percent.empty() ? std::to_string(center->y) : center->y_percent;
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, x);
					setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, y);
				}

				const auto opacity = animation->get_opacity();
				if (opacity) {
					set_opacity(*opacity);
				}

				// Make sure to clear the StoryBoard because transform made by StoryBoard remains.
				storyboard->Stop();

				is_transforming_layout__ = false;

				if (callback.IsFunction()) {
					callback(this_object);
				}
				animation->fireEvent("complete");
			});
			animation->fireEvent("start");
			storyboard->Begin();
		}

		void WindowsViewLayoutDelegate::updateBackgroundGradient()
		{
			if (backgroundLinearGradientBrush__ != nullptr) {
				// if gradient has '%', let's update associated values
				if (!backgroundGradient__.startPoint.x_percent.empty()) {
					backgroundGradient__.startPoint.x = (std::strtod(backgroundGradient__.startPoint.x_percent.c_str(), nullptr) / 100.0);
				}
				if (!backgroundGradient__.startPoint.y_percent.empty()) {
					backgroundGradient__.startPoint.y = (std::strtod(backgroundGradient__.startPoint.y_percent.c_str(), nullptr) / 100.0);
				}
				if (!backgroundGradient__.endPoint.x_percent.empty()) {
					backgroundGradient__.endPoint.x = (std::strtod(backgroundGradient__.endPoint.x_percent.c_str(), nullptr) / 100.0);
				}
				if (!backgroundGradient__.endPoint.y_percent.empty()) {
					backgroundGradient__.endPoint.y = (std::strtod(backgroundGradient__.endPoint.y_percent.c_str(), nullptr) / 100.0);
				}
				const auto startPoint = Windows::Foundation::Point(static_cast<float>(backgroundGradient__.startPoint.x), static_cast<float>(backgroundGradient__.startPoint.y));
				const auto endPoint = Windows::Foundation::Point(static_cast<float>(backgroundGradient__.endPoint.x), static_cast<float>(backgroundGradient__.endPoint.y));
				backgroundLinearGradientBrush__->StartPoint = startPoint;
				backgroundLinearGradientBrush__->EndPoint = endPoint;
			}
		}

		void WindowsViewLayoutDelegate::set_backgroundGradient(const Titanium::UI::Gradient& backgroundGradient) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundGradient(backgroundGradient);
			if (backgroundGradient__.type == Titanium::UI::GRADIENT_TYPE::LINEAR) {
				const auto startPoint = Windows::Foundation::Point(static_cast<float>(backgroundGradient__.startPoint.x), static_cast<float>(backgroundGradient__.startPoint.y));
				const auto endPoint = Windows::Foundation::Point(static_cast<float>(backgroundGradient__.endPoint.x), static_cast<float>(backgroundGradient__.endPoint.y));
				backgroundLinearGradientBrush__ = ref new LinearGradientBrush();
				backgroundLinearGradientBrush__->StartPoint = startPoint;
				backgroundLinearGradientBrush__->EndPoint = endPoint;
				for (auto color : backgroundGradient__.colors) {
					auto stop = ref new GradientStop();
					stop->Color = ColorForName(color.color);
					stop->Offset = color.offset;
					backgroundLinearGradientBrush__->GradientStops->Append(stop);
				}
				updateBackground(backgroundLinearGradientBrush__);
			} else {
				TITANIUM_MODULE_LOG_WARN("WindowsViewLayoutDelegate::set_backgroundGradient: Only \"linear\" is supported for gradient type on Windows");
			}
		}

		ImageBrush^ WindowsViewLayoutDelegate::CreateImageBrushFromBitmapImage(Media::Imaging::BitmapImage^ image)
		{
			auto brush = ref new ImageBrush();
			brush->ImageSource = image;
			brush->Stretch = Stretch::Fill;

			return brush;
		}

		ImageBrush^ WindowsViewLayoutDelegate::CreateImageBrushFromPath(const std::string& path)
		{
			if (path.empty()) {
				return nullptr;
			}
			const auto uri = TitaniumWindows::Utility::GetUriFromPath(path);
			return CreateImageBrushFromBitmapImage(ref new Media::Imaging::BitmapImage(uri));
		}

		ImageBrush^ WindowsViewLayoutDelegate::CreateImageBrushFromBlob(const std::shared_ptr<Titanium::Blob>& blob)
		{
			if (blob == nullptr) {
				return nullptr;
			}
			auto data = blob->getData();

			const auto stream = ref new InMemoryRandomAccessStream();
			const auto writer = ref new DataWriter(stream);
			writer->WriteBytes(Platform::ArrayReference<std::uint8_t>(&data[0], data.size()));

			concurrency::event event;
			concurrency::create_task(writer->StoreAsync()).then([writer](std::uint32_t) {
				return writer->FlushAsync();
			}).then([&event](concurrency::task<bool> task) {
				try {
					task.get();
				} catch (Platform::Exception^ e) {
					TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(e->Message));
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			stream->Seek(0);

			auto image = ref new Media::Imaging::BitmapImage();
			image->SetSource(stream);

			return CreateImageBrushFromBitmapImage(image);
		}

		void WindowsViewLayoutDelegate::updateBackground(Brush^ brush)
		{
			if (underlying_control__) {
				underlying_control__->Background = brush;
			} else if ((is_grid__ || is_border__) && border__) {
				border__->Background = brush;
			} else if (is_panel__) {
				dynamic_cast<Panel^>(component__)->Background = brush;
			} else if (is_control__) {
				dynamic_cast<Control^>(component__)->Background = brush;
			} else {
				TITANIUM_LOG_WARN("Unable to set background: Unknown component");
			}
		}

		//
		// Show selected image/color when it is tapped. It is cleared once it losts focus.
		//
		void WindowsViewLayoutDelegate::updateSelectedBackground()
		{
			if (backgroundSelectedImageBrush__) {
				updateBackground(backgroundSelectedImageBrush__);
			} else if (backgroundSelectedColorBrush__) {
				updateBackground(backgroundSelectedColorBrush__);
			}
		}

		void WindowsViewLayoutDelegate::updateDisabledBackground()
		{
			if (get_touchEnabled()) {
				if (previousBackgroundBrush__ != nullptr) {
					updateBackground(previousBackgroundBrush__);
				}
			} else {
				previousBackgroundBrush__ = getBackground();

				if (backgroundDisabledImageBrush__ != nullptr) {
					updateBackground(backgroundDisabledImageBrush__);
				} else if (backgroundDisabledColorBrush__ != nullptr) {
					updateBackground(backgroundDisabledColorBrush__);
				}
			}
		}

		Brush^ WindowsViewLayoutDelegate::getBackground()
		{
			if (backgroundImageBrush__ != nullptr) {
				return backgroundImageBrush__;
			} else if (backgroundColorBrush__ != nullptr) {
				return backgroundColorBrush__;
			}
			return nullptr;
		}

		void WindowsViewLayoutDelegate::set_backgroundImage(const std::string& backgroundImage) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundImage(backgroundImage);
			backgroundImageBrush__ = CreateImageBrushFromPath(backgroundImage);
			if (get_touchEnabled()) {
				updateBackground(backgroundImageBrush__);
			}
		}

		void WindowsViewLayoutDelegate::set_backgroundImage(const std::shared_ptr<Titanium::Blob>& backgroundImage) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundImage("");
			backgroundImageBrush__ = CreateImageBrushFromBlob(backgroundImage);
			if (get_touchEnabled()) {
				updateBackground(backgroundImageBrush__);
			}
		}

		void WindowsViewLayoutDelegate::set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundColor(backgroundColor);

			backgroundColorBrush__ = ref new Media::SolidColorBrush(ColorForName(backgroundColor));
			if (get_touchEnabled()) {
				updateBackground(backgroundColorBrush__);
			}
		}

		void WindowsViewLayoutDelegate::set_backgroundDisabledColor(const std::string& backgroundDisabledColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundDisabledColor(backgroundDisabledColor);
			backgroundDisabledColorBrush__ = ref new Media::SolidColorBrush(ColorForName(backgroundDisabledColor));
			updateDisabledBackground();
		}

		void WindowsViewLayoutDelegate::set_backgroundDisabledImage(const std::string& backgroundDisabledImage) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundDisabledImage(backgroundDisabledImage);
			backgroundDisabledImageBrush__ = CreateImageBrushFromPath(backgroundDisabledImage);
			updateDisabledBackground();
		}

		void WindowsViewLayoutDelegate::set_backgroundFocusedColor(const std::string& backgroundFocusedColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundFocusedColor(backgroundFocusedColor);
			backgroundFocusedColorBrush__ = ref new Media::SolidColorBrush(ColorForName(backgroundFocusedColor));
		}

		void WindowsViewLayoutDelegate::set_backgroundFocusedImage(const std::string& backgroundFocusedImage) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundFocusedImage(backgroundFocusedImage);
			backgroundFocusedImageBrush__ = CreateImageBrushFromPath(backgroundFocusedImage);
		}

		void WindowsViewLayoutDelegate::set_backgroundSelectedColor(const std::string& backgroundSelectedColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundSelectedColor(backgroundSelectedColor);
			backgroundSelectedColorBrush__ = ref new Media::SolidColorBrush(ColorForName(backgroundSelectedColor));
		}

		void WindowsViewLayoutDelegate::set_backgroundSelectedImage(const std::string& backgroundSelectedImage) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_backgroundSelectedImage(backgroundSelectedImage);
			backgroundSelectedImageBrush__ = CreateImageBrushFromPath(backgroundSelectedImage);
		}

		void WindowsViewLayoutDelegate::set_borderRadius(const double& borderRadius) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_borderRadius(borderRadius);
			set_borderWidth(get_borderWidth()); // update brush
		}

		void WindowsViewLayoutDelegate::set_borderColor(const std::string& borderColor) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_borderColor(borderColor);
			set_borderWidth(get_borderWidth()); // update brush
		}

		void WindowsViewLayoutDelegate::set_borderWidth(const uint32_t& borderWidth) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_borderWidth(borderWidth);

			auto color = get_borderColor().empty() ? get_backgroundColor() : get_borderColor();
			if (color.empty()) {
				color = "black";
			}
			borderColorBrush__ = ref new SolidColorBrush(ColorForName(color));

			if (is_control__ || underlying_control__) {
				// Xaml::Control descendant has its own border property.
				// Use it then, it usually works better than Xaml::Border. Note that it doesn't support border radius though...
				const auto control = underlying_control__ ? underlying_control__ : dynamic_cast<Control^>(component__);
				control->BorderBrush = borderColorBrush__;
				control->BorderThickness = borderWidth;
			} else if (border__) {
				border__->BorderBrush = borderColorBrush__;
				border__->BorderThickness = borderWidth;
				border__->CornerRadius = CornerRadiusHelper::FromUniformRadius(get_borderRadius());
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
			setLayoutProperty(Titanium::LayoutEngine::ValueName::CenterX, std::to_string(center.x));
			setLayoutProperty(Titanium::LayoutEngine::ValueName::CenterY, std::to_string(center.y));
		}

		void WindowsViewLayoutDelegate::set_touchEnabled(const bool& enabled) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_touchEnabled(enabled);
			if (is_control__ || underlying_control__) {
				if (underlying_control__) {
					underlying_control__->IsEnabled = enabled;
				} else {
					dynamic_cast<Control^>(component__)->IsEnabled = enabled;
				}
			}
			updateDisabledBackground();

			for (auto child : get_children()) {
				child->getViewLayoutDelegate()->set_touchEnabled(enabled);
			}
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

		void WindowsViewLayoutDelegate::set_zIndex(const int32_t& zIndex) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::set_zIndex(zIndex);
			Controls::Canvas::SetZIndex(component__, zIndex);
		}

		void WindowsViewLayoutDelegate::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			const auto component = getEventComponent();
			if (event_name == "touchmove") {
				component->ManipulationDelta -= touchmove_event__;
			} else if (event_name == "touchstart") {
				component->PointerPressed -= touchstart_event__;
			} else if (event_name == "touchcancel") {
				component->PointerCanceled -= touchcancel_event__;
				component->PointerCaptureLost -= touchcancel_lost_event__;
			} else if (event_name == "touchend") {
				component->PointerReleased -= touchend_event__;
			} else if (event_name == "click") {
				if (is_button__) {
					dynamic_cast<Controls::Button^>(underlying_control__)->Click -= click_event__;
				} else {
					component->Tapped -= click_event__;
				}
			} else if (event_name == "dblclick") {
				component->DoubleTapped -= dblclick_event__;
			} else if (event_name == "singletap") {
				component->Tapped -= singletap_event__;
			} else if (event_name == "doubletap") {
				component->DoubleTapped -= doubletap_event__;
			} else if (event_name == "longpress") {
				component->Holding -= longpress_event__;
			} else if (event_name == "focus") {
				component->GotFocus -= focus_event__;
			} else if (event_name == "blur") {
				component->LostFocus -= blur_event__;
			} else if (event_name == "postlayout") {
				postlayout_listening__ = false;
			} else if (event_name == "keypressed") {
				component->KeyDown -= keypressed_event__;
			}
		}

		void WindowsViewLayoutDelegate::fireSimplePositionEvent(const std::string& event_name, FrameworkElement^ component, Windows::Foundation::Point position)
		{
			const auto event_delegate = event_delegate__.lock();
			TITANIUM_ASSERT(event_delegate != nullptr);
			const auto ctx = event_delegate->get_context();

			JSObject  eventArgs = ctx.CreateObject();
			eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
			eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

			event_delegate->fireEvent(event_name, eventArgs);
		}

		void WindowsViewLayoutDelegate::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			if (std::find(filtered_events__.begin(), filtered_events__.end(), event_name) != filtered_events__.end()) {
				return;
			}

			const auto component = getEventComponent();

			if (event_name == "touchmove") {
				component->ManipulationMode = ManipulationModes::All;
				touchmove_event__ = component->ManipulationDelta += ref new ManipulationDeltaEventHandler([this](Platform::Object^ sender, ManipulationDeltaRoutedEventArgs^ e) {
					const auto event_delegate = event_delegate__.lock();
					auto ctx = event_delegate->get_context();
					JSObject  delta = ctx.CreateObject();
					delta.SetProperty("x", ctx.CreateNumber(e->Delta.Translation.X));
					delta.SetProperty("y", ctx.CreateNumber(e->Delta.Translation.Y));

					JSObject  eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("x", ctx.CreateNumber(e->Position.X));
					eventArgs.SetProperty("y", ctx.CreateNumber(e->Position.Y));
					eventArgs.SetProperty("delta", delta);

					event_delegate->fireEvent("touchmove", eventArgs);
				});
			} else if (event_name == "touchstart") {
				component->PointerPressed += ref new PointerEventHandler([this](Platform::Object^ sender, PointerRoutedEventArgs^ e) {
					const auto component = safe_cast<FrameworkElement^>(sender);
					const auto point = Windows::UI::Input::PointerPoint::GetCurrentPoint(e->Pointer->PointerId);
					fireSimplePositionEvent("touchstart", component, point->Position);
				});
			} else if (event_name == "touchcancel") {
				//
				// Note: PointerCanceled or PointerCaptureLost may be fired instead of PointerReleased
				//
				const auto cancel_handler = ref new PointerEventHandler([this](Platform::Object^ sender, PointerRoutedEventArgs^ e) {
					const auto component = safe_cast<FrameworkElement^>(sender);
					const auto point = Windows::UI::Input::PointerPoint::GetCurrentPoint(e->Pointer->PointerId);
					fireSimplePositionEvent("touchcancel", component, point->Position);
				});
				component->PointerCanceled    += cancel_handler;
				component->PointerCaptureLost += cancel_handler;
			} else if (event_name == "touchend") {
				component->PointerReleased += ref new PointerEventHandler([this](Platform::Object^ sender, PointerRoutedEventArgs^ e) {
					const auto component = safe_cast<FrameworkElement^>(sender);
					const auto point = Windows::UI::Input::PointerPoint::GetCurrentPoint(e->Pointer->PointerId);
					fireSimplePositionEvent("touchend", component, point->Position);
				});
			} else if (event_name == "click") {
				if (is_button__) {
					click_event__ = dynamic_cast<Controls::Button^>(underlying_control__)->Click += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
						const auto button = safe_cast<Controls::Button^>(sender);
						// Set center of the button since Button::Click does not provide position info
						Windows::Foundation::Point pos;
						pos.X = static_cast<float>(button->Width  * 0.5);
						pos.Y = static_cast<float>(button->Height * 0.5);
						fireSimplePositionEvent("click", button, pos);
					});
				} else {
					click_event__ = component->Tapped += ref new TappedEventHandler([this](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
						const auto component = safe_cast<FrameworkElement^>(sender);
						fireSimplePositionEvent("click", component, e->GetPosition(component));
					});
				}
			} else if (event_name == "dblclick") {
				dblclick_event__ = component->DoubleTapped += ref new DoubleTappedEventHandler([this](Platform::Object^ sender, DoubleTappedRoutedEventArgs^ e) {
					const auto component = safe_cast<FrameworkElement^>(sender);
					fireSimplePositionEvent("dblclick", component, e->GetPosition(component));
				});
			} else if (event_name == "singletap") {
				singletap_event__ = component->Tapped += ref new TappedEventHandler([this](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
					const auto component = safe_cast<FrameworkElement^>(sender);
					fireSimplePositionEvent("singletap", component, e->GetPosition(component));
				});
			} else if (event_name == "doubletap") {
				doubletap_event__ = component->DoubleTapped += ref new DoubleTappedEventHandler([this](Platform::Object^ sender, DoubleTappedRoutedEventArgs^ e) {
					const auto component = safe_cast<FrameworkElement^>(sender);
					fireSimplePositionEvent("doubletap", component, e->GetPosition(component));
				});
			} else if (event_name == "longpress") {
				longpress_event__ = component->Holding += ref new HoldingEventHandler([this](Platform::Object^ sender, HoldingRoutedEventArgs^ e) {
					// fires event only when it started
					if (e->HoldingState == Windows::UI::Input::HoldingState::Started) {
						const auto component = safe_cast<FrameworkElement^>(sender);
						fireSimplePositionEvent("longpress", component, e->GetPosition(component));
					}
				});
			} else if (event_name == "focus") {
				focus_event__ = component->GotFocus += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				 	const auto event_delegate = event_delegate__.lock();
				 	if (event_delegate != nullptr) {
					 	JSContext js_context = event_delegate->get_context();
						JSObject eventArgs = js_context.CreateObject();
						eventArgs.SetProperty("source", event_delegate->get_object());
						event_delegate->fireEvent("focus", eventArgs);
				 	}
				});
			} else if (event_name == "blur") {
				blur_event__ = component->LostFocus += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
					const auto event_delegate = event_delegate__.lock();
					if (event_delegate != nullptr) {
						JSContext js_context = event_delegate->get_context();
						JSObject eventArgs = js_context.CreateObject();
						eventArgs.SetProperty("source", event_delegate->get_object());
						event_delegate->fireEvent("blur", eventArgs);
					}
				});
			} else if (event_name == "postlayout") {
				postlayout_listening__ = true;
			} else if (event_name == "keypressed") {
				keypressed_event__ = component->KeyDown += ref new KeyEventHandler([this](Platform::Object^, KeyRoutedEventArgs^ e){
					const auto event_delegate = event_delegate__.lock();
					if (event_delegate != nullptr) {
						//
						// Sends "virtual key" code for Windows. See following link for details.
						// https://msdn.microsoft.com/library/windows/apps/windows.system.virtualkey%28v=win.10%29.aspx
						//
						JSContext js_context = event_delegate->get_context();
						JSObject eventArgs = js_context.CreateObject();
						eventArgs.SetProperty("source", event_delegate->get_object());
						eventArgs.SetProperty("keyCode", js_context.CreateNumber(static_cast<std::uint32_t>(e->Key)));
						event_delegate->fireEvent("keypressed", eventArgs);
					}
				});
			}
		}

		static void onLayoutCallback(Titanium::LayoutEngine::Node* node)
		{
			const auto view = static_cast<WindowsViewLayoutDelegate*>(node->data);
			auto rect = Titanium::LayoutEngine::RectMake(node->element.measuredLeft, node->element.measuredTop, node->element.measuredWidth, node->element.measuredHeight);
			view->onLayoutEngineCallback(rect, node->name);

			// update gradient when needed
			view->updateBackgroundGradient();
		}

		void WindowsViewLayoutDelegate::setDefaultBackground()
		{
			if (get_touchEnabled()) {
				if (backgroundImageBrush__) {
					updateBackground(backgroundImageBrush__);
				} else if (backgroundColorBrush__) {
					updateBackground(backgroundColorBrush__);
				} else if (backgroundLinearGradientBrush__) {
					updateBackground(backgroundLinearGradientBrush__);
				} else {
					updateBackground(nullptr); // delete background
				}
			}
		}

		void WindowsViewLayoutDelegate::setComponent(FrameworkElement^ component, Windows::UI::Xaml::Controls::Control^ underlying_control, const bool& enableBorder)
		{
			Border^ border = nullptr;
			if (enableBorder) {
				border = ref new Border();
				border->Child = component;
			}
			setComponent(component, underlying_control, border);
		}

		void WindowsViewLayoutDelegate::setComponent(FrameworkElement^ component, Windows::UI::Xaml::Controls::Control^ underlying_control, Windows::UI::Xaml::Controls::Border^ border)
		{
			TITANIUM_ASSERT(component__ == nullptr);
			TITANIUM_ASSERT(underlying_control__ == nullptr);
			TITANIUM_ASSERT(border__ == nullptr);

			component__  = component;
			underlying_control__ = underlying_control;
			border__ = border;

			is_panel__   = dynamic_cast<Controls::Panel^>(component__) != nullptr;
			is_control__ = dynamic_cast<Controls::Control^>(component__) != nullptr;
			is_scrollview__ = dynamic_cast<Controls::ScrollViewer^>(component__) != nullptr;
			is_grid__    = dynamic_cast<Controls::Grid^>(component__) != nullptr;
			is_border__ = dynamic_cast<Controls::Border^>(component__) != nullptr;
			is_button__  = dynamic_cast<Controls::Button^>(underlying_control__) != nullptr;

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

			size_change_event__ = component__->SizeChanged += ref new SizeChangedEventHandler([this](Platform::Object^ sender, SizeChangedEventArgs^ e) {
				auto component = getComponent();
				auto rect = Titanium::LayoutEngine::RectMake(
					Canvas::GetLeft(component),
					Canvas::GetTop(component),
					e->NewSize.Width,
					e->NewSize.Height
				);

				onComponentSizeChange(rect);
			});

			update_background_event__ = component__->GotFocus += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				//
				// check if background is set, show it one again.
				// we prefer "focused" one here.
				//
				if (backgroundFocusedImageBrush__) {
					updateBackground(backgroundFocusedImageBrush__);
				} else if (backgroundFocusedColorBrush__) {
					updateBackground(backgroundFocusedColorBrush__);
				} else {
					setDefaultBackground();
				}
			});

			reset_background_event__ = component__->LostFocus += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				//
				// bring back background image in case we have shown "focused" or "selected" image
				//
				const auto imagesSet = (!get_backgroundFocusedImage().empty()) || (!get_backgroundFocusedColor().empty()) || (!get_backgroundSelectedImage().empty()) || (!get_backgroundSelectedColor().empty());
				if (imagesSet) {
					setDefaultBackground();
				}
			});

			if (is_button__) {
				selected_event__ = dynamic_cast<Controls::Button^>(underlying_control__)->Click += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
					updateSelectedBackground();
				});
			} else {
				selected_event__ = component__->Tapped += ref new TappedEventHandler([this](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
					updateSelectedBackground();
				});
			}

			if (is_control__) {
				enabled_changed_event__ = dynamic_cast<Control^>(component__)->IsEnabledChanged += ref new DependencyPropertyChangedEventHandler([this](Platform::Object^ sender, DependencyPropertyChangedEventArgs^ e){
					auto control = dynamic_cast<Control^>(sender);
					if (control->IsEnabled) {
						setDefaultBackground();
					} else {
						//
						// show "disabled" background image if any
						//
						if (backgroundDisabledImageBrush__) {
							updateBackground(backgroundDisabledImageBrush__);
						} else if (backgroundDisabledColorBrush__) {
							updateBackground(backgroundDisabledColorBrush__);
						}
					}
				});
			}

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


		bool WindowsViewLayoutDelegate::shouldUseOwnWidth() const TITANIUM_NOEXCEPT
		{
			// Check if parent can't decide its width and this component doesn't have fixed width property & handles its width
			if (use_own_size__ && layout_node__->parent != nullptr) {
				return get_width().empty()
					&& layout_node__->parent->properties.right.valueType == Titanium::LayoutEngine::ValueType::None
					&& layout_node__->parent->properties.width.valueType == Titanium::LayoutEngine::ValueType::Size;
			}
			return false;
		}

		bool WindowsViewLayoutDelegate::shouldUseOwnHeight() const TITANIUM_NOEXCEPT
		{
			// Check if parent can't decide its height and this component doesn't have fixed height property & handles its height
			if (use_own_size__ && layout_node__->parent != nullptr) {
				return get_height().empty()
					&& layout_node__->parent->properties.bottom.valueType == Titanium::LayoutEngine::ValueType::None
					&& layout_node__->parent->properties.height.valueType == Titanium::LayoutEngine::ValueType::Size;
			}
			return false;
		}

		void WindowsViewLayoutDelegate::onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name)
		{
			auto skipHeight = shouldUseOwnHeight() || (is_height_size__ && rect.height == 0);
			auto skipWidth  = shouldUseOwnWidth()  || (is_width_size__  && rect.width  == 0);

			if (rect.width < 0 || rect.height < 0)
				return;
			if (Titanium::LayoutEngine::RectIsEmpty(rect))
				return;
			if (Titanium::LayoutEngine::RectIsEqualToRect(oldRect__, rect))
				return;

			auto component = getComponent();
			auto panel = is_panel__ ? safe_cast<Panel^>(component__) : nullptr;
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
			if (!skipHeight && rect.height <= 0) {
				rect.height = component->ActualHeight;
			}
			if (!skipWidth && rect.width <= 0) {
				rect.width = component->ActualWidth;
			}

			if (is_panel__) {
				setWidth = true;
				setHeight = true;
			}

			if (!skipWidth && ((!is_panel__ && setWidthOnWidget) || setWidth)) {
				if (get_width().empty() &&
					layout_node__->properties.left.valueType != Titanium::LayoutEngine::None &&
					layout_node__->properties.right.valueType != Titanium::LayoutEngine::None &&
					component->ActualWidth == rect.width) {
					rect.width = oldRect__.width;
				}
				component->Width = rect.width;
			}

			if (!skipHeight && ((!is_panel__ && setHeightOnWidget) || setHeight)) {
				if (get_height().empty() &&
					layout_node__->properties.top.valueType != Titanium::LayoutEngine::None &&
					layout_node__->properties.bottom.valueType != Titanium::LayoutEngine::None &&
					component->ActualHeight == rect.height) {
					rect.height = oldRect__.height;
				}
				component->Height = rect.height;
			}

			Canvas::SetLeft(component, rect.x);
			Canvas::SetTop(component, rect.y);

			if (!is_scrollview__ && !std::isnan(component->Width) && !std::isnan(component->Height)) {
				auto clipRect = ref new Media::RectangleGeometry();
				clipRect->Rect = Windows::Foundation::Rect(
					static_cast<float>(0),
					static_cast<float>(0),
					static_cast<float>(rect.width),
					static_cast<float>(rect.height));
				component->Clip = clipRect;
			}

			oldRect__ = Titanium::LayoutEngine::RectMake(rect.x, rect.y, rect.width, rect.height);
		}

		void WindowsViewLayoutDelegate::requestLayout(const bool& fire_event)
		{
			const auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node__);
			if (root) {
				Titanium::LayoutEngine::nodeLayout(root);

				if (is_panel__) {
					const auto panel = dynamic_cast<Panel^>(component__);
					for (auto child : panel->Children) {
						// ScrollViewer should not be clipped
						if (dynamic_cast<ScrollViewer^>(static_cast<UIElement^>(child)) != nullptr) {
							continue;
						}
						// ignore when width and/or height is NaN
						if (std::isnan(panel->Width) || std::isnan(panel->Height)) {
							continue;
						}
						auto clipRect = ref new Media::RectangleGeometry();
						clipRect->Rect = Windows::Foundation::Rect(
							static_cast<float>(-Canvas::GetLeft(child)),
							static_cast<float>(-Canvas::GetTop(child)),
							static_cast<float>(panel->Width),
							static_cast<float>(panel->Height));
						child->Clip = clipRect;
					}
				}

				if (fire_event) {
					firePostLayoutEvent();
				}
			}
		}

		void WindowsViewLayoutDelegate::firePostLayoutEvent()
		{
			if (postlayout_listening__) {
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

		void WindowsViewLayoutDelegate::onComponentLoaded(const Titanium::LayoutEngine::Rect& rect)
		{
			is_loaded__ = true;
			requestLayout(true);

			// layout has loaded, expel animation queue
			for (auto animation : animate_queue__) {
				animate(animation.animation, animation.callback, animation.this_object);
			}
			animate_queue__.clear();
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

			if (is_width_size__ && (is_grid__ || is_border__ || !is_panel__)) {
				layout_node__->properties.width.value = rect.width;
				layout_node__->properties.width.valueType = Titanium::LayoutEngine::Fixed;
				needsLayout = isLoaded();
			}

			if (is_height_size__ && (is_grid__ || is_border__ || !is_panel__)) {
				layout_node__->properties.height.value = rect.height;
				layout_node__->properties.height.valueType = Titanium::LayoutEngine::Fixed;
				needsLayout = isLoaded();
			}

			if (needsLayout) {
				requestLayout(true);
			} else if (isLoaded()) {
				firePostLayoutEvent();
			}

		}


		void WindowsViewLayoutDelegate::setLayoutProperty(const Titanium::LayoutEngine::ValueName& name, const std::string& value, const std::shared_ptr<Titanium::LayoutEngine::LayoutProperties> properties)
		{
			Titanium::LayoutEngine::InputProperty prop;
			prop.name = name;
			prop.value = value;

			if (prop.value == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)) {
				prop.value = "UI.SIZE";
			}
			else if (prop.value == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL)) {
				prop.value = "UI.FILL";
			}

			auto info = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
			double ppi = info->LogicalDpi;
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			switch (name) {
			case Titanium::LayoutEngine::ValueName::CenterX:
			case Titanium::LayoutEngine::ValueName::Left:
			case Titanium::LayoutEngine::ValueName::Right:
			case Titanium::LayoutEngine::ValueName::Width:
			case Titanium::LayoutEngine::ValueName::MinWidth:
				ppi = info->RawDpiX / info->RawPixelsPerViewPixel;
				break;
			case Titanium::LayoutEngine::ValueName::CenterY:
			case Titanium::LayoutEngine::ValueName::Top:
			case Titanium::LayoutEngine::ValueName::Bottom:
			case Titanium::LayoutEngine::ValueName::Height:
			case Titanium::LayoutEngine::ValueName::MinHeight:
				ppi = info->RawDpiY / info->RawPixelsPerViewPixel;
				break;
			}
#endif

			// Get the defaultUnits from ti.ui.defaultUnit!
			std::string defaultUnits = "px";
			auto event_delegate = event_delegate__.lock();
		 	if (event_delegate != nullptr) {
			 	JSContext js_context = event_delegate->get_context();

			 	JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
				JSObject Titanium = static_cast<JSObject>(Titanium_property);

				JSValue App_property = Titanium.GetProperty("App");
				TITANIUM_ASSERT(App_property.IsObject());  // precondition
				JSObject App = static_cast<JSObject>(App_property);

				const auto object_ptr = App.GetPrivate<Titanium::AppModule>();
				defaultUnits = object_ptr->defaultUnit();
		 	}
			Titanium::LayoutEngine::populateLayoutProperties(prop, properties ? properties.get() : &layout_node__->properties, ppi, defaultUnits);

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
			std::transform(string.begin(), string.end(), copy.begin(), tolower);
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
