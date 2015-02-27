/**
 * Titanium.UI.Animation for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_ANIMATION_HPP_
#define _TITANIUM_ANIMATION_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Animation Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Animation
		*/
		class TITANIUMKIT_EXPORT Animation : public Module, public JSExport<Animation>
		{

		public:

			/*!
			  @property
			  @abstract autoreverse
			  @discussion Specifies if the animation should be replayed in reverse upon completion.
			*/
			virtual bool get_autoreverse() const TITANIUM_NOEXCEPT final;
			virtual void set_autoreverse(const bool& autoreverse) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract backgroundColor
			  @discussion Value of the `backgroundColor` property at the end of the animation, as a color name or hex triplet.
			*/
			virtual std::string get_backgroundColor() const TITANIUM_NOEXCEPT final;
			virtual void set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract bottom
			  @discussion Value of the `bottom` property at the end of the animation.
			*/
			virtual double get_bottom() const TITANIUM_NOEXCEPT final;
			virtual void set_bottom(const double& bottom) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract center
			  @discussion Value of the `center` property at the end of the animation.
			*/
			virtual JSObject get_center() const TITANIUM_NOEXCEPT final;
			virtual void set_center(const JSObject& center) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract color
			  @discussion Value of the `color` property at the end of the animation, as a color name or hex triplet.
			*/
			virtual std::string get_color() const TITANIUM_NOEXCEPT final;
			virtual void set_color(const std::string& color) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract curve
			  @discussion Animation curve or easing function to apply to the animation.
			*/
			virtual ANIMATION_CURVE get_curve() const TITANIUM_NOEXCEPT final;
			virtual void set_curve(const ANIMATION_CURVE& curve) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract delay
			  @discussion Delay, in milliseconds before starting the animation.
			*/
			virtual std::chrono::milliseconds get_delay() const TITANIUM_NOEXCEPT final;
			virtual void set_delay(const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract duration
			  @discussion Duration of the animation, in milliseconds.
			*/
			virtual std::chrono::milliseconds get_duration() const TITANIUM_NOEXCEPT final;
			virtual void set_duration(const std::chrono::milliseconds& duration) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract height
			  @discussion Value of the `height` property at the end of the animation.
			*/
			virtual double get_height() const TITANIUM_NOEXCEPT final;
			virtual void set_height(const double& height) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract left
			  @discussion Value of the `left` property at the end of the animation.
			*/
			virtual double get_left() const TITANIUM_NOEXCEPT final;
			virtual void set_left(const double& left) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract opacity
			  @discussion Value of the `opacity` property at the end of the animation.
			*/
			virtual double get_opacity() const TITANIUM_NOEXCEPT final;
			virtual void set_opacity(const double& opacity) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract opaque
			  @discussion Value of the `opaque` property at the end of the animation.
			*/
			virtual bool get_opaque() const TITANIUM_NOEXCEPT final;
			virtual void set_opaque(const bool& opaque) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract repeat
			  @discussion Number of times the animation should be performed.
			*/
			virtual uint32_t get_repeat() const TITANIUM_NOEXCEPT final;
			virtual void set_repeat(const uint32_t& repeat) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract right
			  @discussion Value of the `right` property at the end of the animation.
			*/
			virtual double get_right() const TITANIUM_NOEXCEPT final;
			virtual void set_right(const double& right) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract top
			  @discussion Value of the `top` property at the end of the animation.
			*/
			virtual double get_top() const TITANIUM_NOEXCEPT final;
			virtual void set_top(const double& top) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract transform
			  @discussion Animate the view from its current tranform to the specified transform.
			*/
			virtual JSValue get_transform() const TITANIUM_NOEXCEPT final;
			virtual void set_transform(const JSValue& transform) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract transition
			  @discussion Transition type to use during a transition animation.
			*/
			virtual uint32_t get_transition() const TITANIUM_NOEXCEPT final;
			virtual void set_transition(const uint32_t& transition) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract view
			  @discussion New view to transition to.
			*/
			virtual JSValue get_view() const TITANIUM_NOEXCEPT final;
			virtual void set_view(const JSValue& view) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract visible
			  @discussion Value of the `visible` property at the end of the animation.
			*/
			virtual bool get_visible() const TITANIUM_NOEXCEPT final;
			virtual void set_visible(const bool& visible) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract width
			  @discussion Value of the `width` property at the end of the animation.
			*/
			virtual double get_width() const TITANIUM_NOEXCEPT final;
			virtual void set_width(const double& width) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract zIndex
			  @discussion Value of the `zIndex` property at the end of the animation.
			*/
			virtual uint32_t get_zIndex() const TITANIUM_NOEXCEPT final;
			virtual void set_zIndex(const uint32_t& width) TITANIUM_NOEXCEPT;

			Animation(const JSContext&) TITANIUM_NOEXCEPT;
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual ~Animation() = default;
			Animation(const Animation&) = default;
			Animation& operator=(const Animation&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Animation(Animation&&)                 = default;
			Animation& operator=(Animation&&)      = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_autoreverse() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_autoreverse(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getAutoreverse(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setAutoreverse(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_backgroundColor() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_backgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getBackgroundColor(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setBackgroundColor(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_bottom() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_bottom(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getBottom(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setBottom(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_center() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_center(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getCenter(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setCenter(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_color() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_color(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getColor(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setColor(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_curve() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_curve(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getCurve(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setCurve(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_delay() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_delay(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getDelay(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setDelay(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_duration() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_duration(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getDuration(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setDuration(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_height() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_height(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHeight(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHeight(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_left() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_left(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getLeft(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setLeft(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_opacity() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_opacity(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOpacity(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setOpacity(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_opaque() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_opaque(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getOpaque(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setOpaque(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_repeat() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_repeat(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getRepeat(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setRepeat(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_right() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_right(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getRight(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setRight(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_top() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_top(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getTop(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setTop(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_transform() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_transform(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getTransform(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setTransform(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_transition() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_transition(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getTransition(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setTransition(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_view() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_view(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_visible() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_visible(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getVisible(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setVisible(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_width() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_width(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getWidth(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setWidth(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_zIndex() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_zIndex(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getZIndex(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setZIndex(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			protected:
#pragma warning(push)
#pragma warning(disable : 4251)
				bool autoreverse__;
				std::string backgroundColor__;
				double bottom__;
				JSObject center__;
				std::string color__;
				ANIMATION_CURVE curve__;
				std::chrono::milliseconds delay__;
				std::chrono::milliseconds duration__;
				double height__;
				double left__;
				double opacity__;
				bool opaque__;
				uint32_t repeat__;
				double right__;
				double top__;
				JSValue transform__;
				uint32_t transition__;
				JSValue view__;
				bool visible__;
				double width__;
				uint32_t zIndex__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_ANIMATION_HPP_