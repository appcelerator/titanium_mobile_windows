/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_VIEW_HPP_
#define _TITANIUM_UI_VIEW_HPP_

#include "Titanium/Module.hpp"
#include <vector>
#include <memory>
#include "Titanium/UI/ViewLayoutDelegate.hpp"
#include "Titanium/UI/Point.hpp"
#include "Titanium/UI/Gradient.hpp"

namespace Titanium
{
	class Blob;

	namespace UI
	{
		using namespace HAL;

		class View;
		class Animation;

		/*!
		  @class

		  @discussion This is the Titanium UI View.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.View
		*/
		class TITANIUMKIT_EXPORT View : public Module, public JSExport<View>
		{
		public:

			/*!
			  @property
			  @abstract accessibilityHidden
			  @discussion Whether the view should be "hidden" from (i.e., ignored by) the accessibility service.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, accessibilityHidden);

			/*!
			  @property
			  @abstract accessibilityHint
			  @discussion Briefly describes what performing an action (such as a click) on the view will do.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, accessibilityHint);

			/*!
			  @property
			  @abstract accessibilityLabel
			  @discussion A succint label identifying the view for the device's accessibility service.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, accessibilityLabel);

			/*!
			  @property
			  @abstract accessibilityValue
			  @discussion A string describing the value (if any) of the view for the device's accessibility service.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, accessibilityValue);

			/*!
			  @property
			  @abstract clipMode
			  @discussion View's clipping behavior.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, clipMode);

			/*!
			  @property
			  @abstract focusable
			  @discussion Whether view should be focusable while navigating with the trackball.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, focusable);

			/*!
			  @property
			  @abstract softKeyboardOnFocus
			  @discussion Determines keyboard behavior when this view is focused.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, softKeyboardOnFocus);

			/*!
			  @property
			  @abstract keepScreenOn
			  @discussion Determines whether to keep the device screen on.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, keepScreenOn);

			/*!
			  @property
			  @abstract parent
			  @discussion Return parent view of this view
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<View>, parent);

			/*!
			  @method
			  @abstract toImage
			  @discussion Returns an image of the rendered view, as a Blob.
			*/
			virtual std::shared_ptr<Titanium::Blob> toImage(JSObject& callback, const bool& honorScaleFactor) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract convertPointToView
			  @discussion Translates a point from this view's coordinate system to another view's coordinate system.
			*/
			virtual Point convertPointToView(Point point, std::shared_ptr<View> destinationView) TITANIUM_NOEXCEPT;


			/*!
			  @method

			  @abstract animate( animation, callback ) : void

			  @discussion Animates this view.

			  The Animation object or dictionary passed to this method defines the end state for the animation, the duration of the animation, and other properties.

			  Note that if you use animate to move a view, the view's actual position is changed, but its layout properties, such as top, left, center and so on are not changed--these reflect the original values set by the user, not the actual position of the view.

			  The rect property can be used to determine the actual size and position of the view. Note that on Mobile Web and Tizen, the rect property is not updated after animation. This is a known issue TIMOB-8930.

			  @param animation : Titanium.UI.Animation/Dictionary<Titanium.UI.Animation>
			  Either a dictionary of animation properties or an Animation object.

			  @param callback : Callback<Object>
			  Function to be invoked upon completion of the animation.

			  @result void
			*/
			virtual void animate(const std::shared_ptr<Titanium::UI::Animation>& animation, JSObject& callback) TITANIUM_NOEXCEPT;

			virtual void blur();
			virtual void focus();

			/*!
				This delegates to the layout_delegate__ to add the view, but allows for platform-specific overrides of handling the wrapped view.
				This is important so the underlying platform can handle automatically wrapping/unwrapping native UI widgets mixed with Titanium UI.
			*/
			virtual void add(const JSObject&) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract get_children
			  @discussion Returns array of this view's child views
			*/
			virtual std::vector<std::shared_ptr<Titanium::UI::View>> get_children() const TITANIUM_NOEXCEPT;

			View(const JSContext&, const std::string& apiName = "Titanium.UI.View") TITANIUM_NOEXCEPT;

			virtual ~View() TITANIUM_NOEXCEPT;  //= default;
			View(const View&) = default;
			View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&) = default;
			View& operator=(View&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(accessibilityHidden);
			TITANIUM_PROPERTY_DEF(accessibilityHint);
			TITANIUM_PROPERTY_DEF(accessibilityLabel);
			TITANIUM_PROPERTY_DEF(accessibilityValue);
			TITANIUM_PROPERTY_DEF(anchorPoint);
			TITANIUM_PROPERTY_READONLY_DEF(animatedCenter);
			TITANIUM_PROPERTY_DEF(backgroundDisabledColor);
			TITANIUM_PROPERTY_DEF(backgroundDisabledImage);
			TITANIUM_PROPERTY_DEF(backgroundFocusedColor);
			TITANIUM_PROPERTY_DEF(backgroundFocusedImage);
			TITANIUM_PROPERTY_DEF(backgroundGradient);
			TITANIUM_PROPERTY_DEF(backgroundImage);
			TITANIUM_PROPERTY_DEF(backgroundRepeat);
			TITANIUM_PROPERTY_DEF(backgroundLeftCap);
			TITANIUM_PROPERTY_DEF(backgroundSelectedColor);
			TITANIUM_PROPERTY_DEF(backgroundSelectedImage);
			TITANIUM_PROPERTY_DEF(backgroundTopCap);
			TITANIUM_PROPERTY_DEF(borderColor);
			TITANIUM_PROPERTY_DEF(borderRadius);
			TITANIUM_PROPERTY_DEF(borderWidth);
			TITANIUM_PROPERTY_DEF(clipMode);
			TITANIUM_PROPERTY_DEF(focusable);
			TITANIUM_PROPERTY_DEF(opacity);
			TITANIUM_PROPERTY_DEF(overrideCurrentAnimation);
			TITANIUM_PROPERTY_DEF(pullBackgroundColor);
			TITANIUM_PROPERTY_READONLY_DEF(rect);
			TITANIUM_PROPERTY_READONLY_DEF(size);
			TITANIUM_PROPERTY_DEF(softKeyboardOnFocus);
			TITANIUM_PROPERTY_DEF(tintColor);
			TITANIUM_PROPERTY_DEF(touchEnabled);
			TITANIUM_PROPERTY_DEF(transform);
			TITANIUM_PROPERTY_DEF(viewShadowRadius);
			TITANIUM_PROPERTY_DEF(viewShadowColor);
			TITANIUM_PROPERTY_DEF(viewShadowOffset);
			TITANIUM_PROPERTY_DEF(visible);
			TITANIUM_PROPERTY_DEF(horizontalWrap);
			TITANIUM_PROPERTY_DEF(zIndex);
			TITANIUM_PROPERTY_DEF(keepScreenOn);
			TITANIUM_PROPERTY_READONLY_DEF(children);
			TITANIUM_PROPERTY_DEF(backgroundColor);
			TITANIUM_PROPERTY_DEF(top);
			TITANIUM_PROPERTY_DEF(left);
			TITANIUM_PROPERTY_DEF(bottom);
			TITANIUM_PROPERTY_DEF(center);
			TITANIUM_PROPERTY_DEF(right);
			TITANIUM_PROPERTY_DEF(width);
			TITANIUM_PROPERTY_DEF(height);
			TITANIUM_PROPERTY_DEF(layout);
			TITANIUM_PROPERTY_DEF(parent);

			TITANIUM_FUNCTION_DEF(animate);
			TITANIUM_FUNCTION_DEF(remove);
			TITANIUM_FUNCTION_DEF(removeAllChildren);
			TITANIUM_FUNCTION_DEF(toImage);
			TITANIUM_FUNCTION_DEF(convertPointToView);
			TITANIUM_FUNCTION_DEF(add);
			TITANIUM_FUNCTION_DEF(hide);
			TITANIUM_FUNCTION_DEF(show);
			TITANIUM_FUNCTION_DEF(getAccessibilityHidden);
			TITANIUM_FUNCTION_DEF(setAccessibilityHidden);
			TITANIUM_FUNCTION_DEF(getAccessibilityHint);
			TITANIUM_FUNCTION_DEF(setAccessibilityHint);
			TITANIUM_FUNCTION_DEF(getAccessibilityLabel);
			TITANIUM_FUNCTION_DEF(setAccessibilityLabel);
			TITANIUM_FUNCTION_DEF(getAccessibilityValue);
			TITANIUM_FUNCTION_DEF(setAccessibilityValue);
			TITANIUM_FUNCTION_DEF(getAnchorPoint);
			TITANIUM_FUNCTION_DEF(setAnchorPoint);
			TITANIUM_FUNCTION_DEF(getAnimatedCenter);
			TITANIUM_FUNCTION_DEF(getBackgroundDisabledColor);
			TITANIUM_FUNCTION_DEF(setBackgroundDisabledColor);
			TITANIUM_FUNCTION_DEF(getBackgroundDisabledImage);
			TITANIUM_FUNCTION_DEF(setBackgroundDisabledImage);
			TITANIUM_FUNCTION_DEF(getBackgroundFocusedColor);
			TITANIUM_FUNCTION_DEF(setBackgroundFocusedColor);
			TITANIUM_FUNCTION_DEF(getBackgroundFocusedImage);
			TITANIUM_FUNCTION_DEF(setBackgroundFocusedImage);
			TITANIUM_FUNCTION_DEF(getBackgroundGradient);
			TITANIUM_FUNCTION_DEF(setBackgroundGradient);
			TITANIUM_FUNCTION_DEF(getBackgroundImage);
			TITANIUM_FUNCTION_DEF(setBackgroundImage);
			TITANIUM_FUNCTION_DEF(getBackgroundRepeat);
			TITANIUM_FUNCTION_DEF(setBackgroundRepeat);
			TITANIUM_FUNCTION_DEF(getBackgroundLeftCap);
			TITANIUM_FUNCTION_DEF(setBackgroundLeftCap);
			TITANIUM_FUNCTION_DEF(getBackgroundSelectedColor);
			TITANIUM_FUNCTION_DEF(setBackgroundSelectedColor);
			TITANIUM_FUNCTION_DEF(getBackgroundSelectedImage);
			TITANIUM_FUNCTION_DEF(setBackgroundSelectedImage);
			TITANIUM_FUNCTION_DEF(getBackgroundTopCap);
			TITANIUM_FUNCTION_DEF(setBackgroundTopCap);
			TITANIUM_FUNCTION_DEF(getBorderColor);
			TITANIUM_FUNCTION_DEF(setBorderColor);
			TITANIUM_FUNCTION_DEF(getBorderRadius);
			TITANIUM_FUNCTION_DEF(setBorderRadius);
			TITANIUM_FUNCTION_DEF(getBorderWidth);
			TITANIUM_FUNCTION_DEF(setBorderWidth);
			TITANIUM_FUNCTION_DEF(getClipMode);
			TITANIUM_FUNCTION_DEF(setClipMode);
			TITANIUM_FUNCTION_DEF(getFocusable);
			TITANIUM_FUNCTION_DEF(setFocusable);
			TITANIUM_FUNCTION_DEF(getOpacity);
			TITANIUM_FUNCTION_DEF(setOpacity);
			TITANIUM_FUNCTION_DEF(getOverrideCurrentAnimation);
			TITANIUM_FUNCTION_DEF(setOverrideCurrentAnimation);
			TITANIUM_FUNCTION_DEF(getPullBackgroundColor);
			TITANIUM_FUNCTION_DEF(setPullBackgroundColor);
			TITANIUM_FUNCTION_DEF(getRect);
			TITANIUM_FUNCTION_DEF(getSize);
			TITANIUM_FUNCTION_DEF(getSoftKeyboardOnFocus);
			TITANIUM_FUNCTION_DEF(setSoftKeyboardOnFocus);
			TITANIUM_FUNCTION_DEF(getTintColor);
			TITANIUM_FUNCTION_DEF(setTintColor);
			TITANIUM_FUNCTION_DEF(getTouchEnabled);
			TITANIUM_FUNCTION_DEF(setTouchEnabled);
			TITANIUM_FUNCTION_DEF(getTransform);
			TITANIUM_FUNCTION_DEF(setTransform);
			TITANIUM_FUNCTION_DEF(getViewShadowRadius);
			TITANIUM_FUNCTION_DEF(setViewShadowRadius);
			TITANIUM_FUNCTION_DEF(getViewShadowColor);
			TITANIUM_FUNCTION_DEF(setViewShadowColor);
			TITANIUM_FUNCTION_DEF(getViewShadowOffset);
			TITANIUM_FUNCTION_DEF(setViewShadowOffset);
			TITANIUM_FUNCTION_DEF(getViewById);
			TITANIUM_FUNCTION_DEF(getVisible);
			TITANIUM_FUNCTION_DEF(setVisible);
			TITANIUM_FUNCTION_DEF(getHorizontalWrap);
			TITANIUM_FUNCTION_DEF(setHorizontalWrap);
			TITANIUM_FUNCTION_DEF(getZIndex);
			TITANIUM_FUNCTION_DEF(setZIndex);
			TITANIUM_FUNCTION_DEF(getKeepScreenOn);
			TITANIUM_FUNCTION_DEF(setKeepScreenOn);
			TITANIUM_FUNCTION_DEF(getChildren);
			TITANIUM_FUNCTION_DEF(getBackgroundColor);
			TITANIUM_FUNCTION_DEF(setBackgroundColor);
			TITANIUM_FUNCTION_DEF(getTop);
			TITANIUM_FUNCTION_DEF(setTop);
			TITANIUM_FUNCTION_DEF(getLeft);
			TITANIUM_FUNCTION_DEF(setLeft);
			TITANIUM_FUNCTION_DEF(getBottom);
			TITANIUM_FUNCTION_DEF(setBottom);
			TITANIUM_FUNCTION_DEF(getCenter);
			TITANIUM_FUNCTION_DEF(setCenter);
			TITANIUM_FUNCTION_DEF(getRight);
			TITANIUM_FUNCTION_DEF(setRight);
			TITANIUM_FUNCTION_DEF(getWidth);
			TITANIUM_FUNCTION_DEF(setWidth);
			TITANIUM_FUNCTION_DEF(getHeight);
			TITANIUM_FUNCTION_DEF(setHeight);
			TITANIUM_FUNCTION_DEF(getLayout);
			TITANIUM_FUNCTION_DEF(setLayout);
			TITANIUM_FUNCTION_DEF(getParent);
			TITANIUM_FUNCTION_DEF(setParent);

			TITANIUM_FUNCTION_DEF(insertAt);
			TITANIUM_FUNCTION_DEF(replaceAt);

			virtual void postInitialize(JSObject& this_object) override;
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;

			template<typename T>
			std::shared_ptr<T> getViewLayoutDelegate()
			{
				return std::dynamic_pointer_cast<T>(layoutDelegate__);
			}

			std::shared_ptr<ViewLayoutDelegate> getViewLayoutDelegate()
			{
				return getViewLayoutDelegate<ViewLayoutDelegate>();
			}

		protected:
			template<typename T, typename U, typename... Us>
			void setLayoutDelegate(Us&&... constructor_arguments) TITANIUM_NOEXCEPT
			{
				layoutDelegate__ = std::make_shared<T>(std::forward<Us>(constructor_arguments)...);
				layoutEventDelegate__ = std::make_shared<U>(this);
				layoutDelegate__->setEventDelegate(layoutEventDelegate__);
				layoutDelegate__->postInitialize();
			}
			template<typename T, typename... Us>
			void setLayoutDelegate(Us&&... constructor_arguments) TITANIUM_NOEXCEPT
			{
				setLayoutDelegate<T, ViewLayoutEventDelegate>(std::forward<Us>(constructor_arguments)...);
			}
			void setLayoutDelegate() TITANIUM_NOEXCEPT
			{
				setLayoutDelegate<ViewLayoutDelegate, ViewLayoutEventDelegate>();
			}

#pragma warning(push)
#pragma warning(disable : 4251)
			std::shared_ptr<ViewLayoutEventDelegate> layoutEventDelegate__;
			std::shared_ptr<ViewLayoutDelegate> layoutDelegate__;

			bool accessibilityHidden__ { false };
			std::string accessibilityHint__;
			std::string accessibilityLabel__;
			std::string accessibilityValue__;

			std::uint32_t clipMode__; // iOS specific
			std::uint32_t softKeyboardOnFocus__; // Android specific
			bool focusable__ { true };
			bool keepScreenOn__ { false };
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_VIEW_HPP_
