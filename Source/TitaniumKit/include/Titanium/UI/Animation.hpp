/**
 * TitaniumKit Titanium.UI.Animation
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_ANIMATION_HPP_
#define _TITANIUM_ANIMATION_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/Point.hpp"
#include <boost/optional.hpp>

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		class View;
		class TwoDMatrix;

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
			  @abstract anchorPoint
			  @discussion Coordinate of the view about which to pivot an animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Point, anchorPoint);

			/*!
			  @property
			  @abstract autoreverse
			  @discussion Specifies if the animation should be replayed in reverse upon completion.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, autoreverse);

			/*!
			  @property
			  @abstract backgroundColor
			  @discussion Value of the `backgroundColor` property at the end of the animation, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundColor);

			/*!
			  @property
			  @abstract bottom
			  @discussion Value of the `bottom` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::string>, bottom);

			/*!
			  @property
			  @abstract center
			  @discussion Value of the `center` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Point, center);

			/*!
			  @property
			  @abstract color
			  @discussion Value of the `color` property at the end of the animation, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, color);

			/*!
			  @property
			  @abstract curve
			  @discussion Animation curve or easing function to apply to the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(ANIMATION_CURVE, curve);

			/*!
			  @property
			  @abstract delay
			  @discussion Delay, in milliseconds before starting the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::chrono::milliseconds, delay);

			/*!
			  @property
			  @abstract duration
			  @discussion Duration of the animation, in milliseconds.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::chrono::milliseconds, duration);

			/*!
			  @property
			  @abstract height
			  @discussion Value of the `height` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::string>, height);

			/*!
			  @property
			  @abstract left
			  @discussion Value of the `left` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::string>, left);

			/*!
			  @property
			  @abstract opacity
			  @discussion Value of the `opacity` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<double>, opacity);

			/*!
			  @property
			  @abstract opaque
			  @discussion Value of the `opaque` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, opaque);

			/*!
			  @property
			  @abstract repeat
			  @discussion Number of times the animation should be performed.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(uint32_t, repeat);

			/*!
			  @property
			  @abstract right
			  @discussion Value of the `right` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::string>, right);

			/*!
			  @property
			  @abstract top
			  @discussion Value of the `top` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::string>, top);

			/*!
			  @property
			  @abstract transform
			  @discussion Animate the view from its current transform to the specified transform.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::UI::TwoDMatrix>, transform);

			/*!
			  @property
			  @abstract transition
			  @discussion Transition type to use during a transition animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(uint32_t, transition);

			/*!
			  @property
			  @abstract view
			  @discussion New view to transition to.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::UI::View>, view);

			/*!
			  @property
			  @abstract visible
			  @discussion Value of the `visible` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, visible);

			/*!
			  @property
			  @abstract width
			  @discussion Value of the `width` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<std::string>, width);

			/*!
			  @property
			  @abstract zIndex
			  @discussion Value of the `zIndex` property at the end of the animation.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(boost::optional<uint32_t>, zIndex);

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

			TITANIUM_PROPERTY_DEF(anchorPoint);
			TITANIUM_FUNCTION_DEF(getAnchorPoint);
			TITANIUM_FUNCTION_DEF(setAnchorPoint);

			TITANIUM_PROPERTY_DEF(autoreverse);
			TITANIUM_FUNCTION_DEF(getAutoreverse);
			TITANIUM_FUNCTION_DEF(setAutoreverse);

			TITANIUM_PROPERTY_DEF(backgroundColor);
			TITANIUM_FUNCTION_DEF(getBackgroundColor);
			TITANIUM_FUNCTION_DEF(setBackgroundColor);

			TITANIUM_PROPERTY_DEF(bottom);
			TITANIUM_FUNCTION_DEF(getBottom);
			TITANIUM_FUNCTION_DEF(setBottom);

			TITANIUM_PROPERTY_DEF(center);
			TITANIUM_FUNCTION_DEF(getCenter);
			TITANIUM_FUNCTION_DEF(setCenter);

			TITANIUM_PROPERTY_DEF(color);
			TITANIUM_FUNCTION_DEF(getColor);
			TITANIUM_FUNCTION_DEF(setColor);

			TITANIUM_PROPERTY_DEF(curve);
			TITANIUM_FUNCTION_DEF(getCurve);
			TITANIUM_FUNCTION_DEF(setCurve);

			TITANIUM_PROPERTY_DEF(delay);
			TITANIUM_FUNCTION_DEF(getDelay);
			TITANIUM_FUNCTION_DEF(setDelay);

			TITANIUM_PROPERTY_DEF(duration);
			TITANIUM_FUNCTION_DEF(getDuration);
			TITANIUM_FUNCTION_DEF(setDuration);

			TITANIUM_PROPERTY_DEF(height);
			TITANIUM_FUNCTION_DEF(getHeight);
			TITANIUM_FUNCTION_DEF(setHeight);

			TITANIUM_PROPERTY_DEF(left);
			TITANIUM_FUNCTION_DEF(getLeft);
			TITANIUM_FUNCTION_DEF(setLeft);

			TITANIUM_PROPERTY_DEF(opacity);
			TITANIUM_FUNCTION_DEF(getOpacity);
			TITANIUM_FUNCTION_DEF(setOpacity);

			TITANIUM_PROPERTY_DEF(opaque);
			TITANIUM_FUNCTION_DEF(getOpaque);
			TITANIUM_FUNCTION_DEF(setOpaque);

			TITANIUM_PROPERTY_DEF(repeat);
			TITANIUM_FUNCTION_DEF(getRepeat);
			TITANIUM_FUNCTION_DEF(setRepeat);

			TITANIUM_PROPERTY_DEF(right);
			TITANIUM_FUNCTION_DEF(getRight);
			TITANIUM_FUNCTION_DEF(setRight);

			TITANIUM_PROPERTY_DEF(top);
			TITANIUM_FUNCTION_DEF(getTop);
			TITANIUM_FUNCTION_DEF(setTop);

			TITANIUM_PROPERTY_DEF(transform);
			TITANIUM_FUNCTION_DEF(getTransform);
			TITANIUM_FUNCTION_DEF(setTransform);

			TITANIUM_PROPERTY_DEF(transition);
			TITANIUM_FUNCTION_DEF(getTransition);
			TITANIUM_FUNCTION_DEF(setTransition);

			TITANIUM_PROPERTY_DEF(view);
			TITANIUM_FUNCTION_DEF(getView);
			TITANIUM_FUNCTION_DEF(setView);

			TITANIUM_PROPERTY_DEF(visible);
			TITANIUM_FUNCTION_DEF(getVisible);
			TITANIUM_FUNCTION_DEF(setVisible);

			TITANIUM_PROPERTY_DEF(width);
			TITANIUM_FUNCTION_DEF(getWidth);
			TITANIUM_FUNCTION_DEF(setWidth);

			TITANIUM_PROPERTY_DEF(zIndex);
			TITANIUM_FUNCTION_DEF(getZIndex);
			TITANIUM_FUNCTION_DEF(setZIndex);

			protected:
#pragma warning(push)
#pragma warning(disable : 4251)
				Point anchorPoint__;
				bool autoreverse__;
				std::string backgroundColor__;
				boost::optional<std::string> bottom__;
				Point center__;
				std::string color__;
				ANIMATION_CURVE curve__;
				std::chrono::milliseconds delay__;
				std::chrono::milliseconds duration__;
				boost::optional<std::string> height__;
				boost::optional<std::string> left__;
				boost::optional<double> opacity__;
				bool opaque__;
				uint32_t repeat__;
				boost::optional<std::string> right__;
				boost::optional<std::string> top__;
				std::shared_ptr<Titanium::UI::TwoDMatrix> transform__;
				uint32_t transition__;
				std::shared_ptr<Titanium::UI::View> view__;
				bool visible__;
				boost::optional<std::string> width__;
				boost::optional<uint32_t> zIndex__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_ANIMATION_HPP_