/**
 * TitaniumKit Titanium.UI.Animation
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Animation.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/UI/2DMatrix.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{


		Animation::Animation(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.Animation"),
			autoreverse__(false),
			backgroundColor__(""),
			color__(""),
			curve__(ANIMATION_CURVE::EASE_IN), // FIXME on iOS, leaving the default value actually uses dfeault ease here: https://developer.apple.com/library/mac/documentation/Cocoa/Reference/CAMediaTimingFunction_class/index.html#//apple_ref/doc/constant_group/Predefined_Timing_Functions
			// which is NOT lineaer, and NOT the same as that used for EASE_IN. Basically it's an unexposed "other" ease function!
			delay__(0),
			duration__(0),
			opaque__(true),
			repeat__(1),
			transition__(0),
			visible__(true)
		{
			TITANIUM_LOG_DEBUG("Animation:: ctor ", this);
		}

		void Animation::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Animation:: postCallAsConstructor ", this);
		}

		TITANIUM_PROPERTY_READWRITE(Animation, Point, anchorPoint)

		TITANIUM_PROPERTY_READWRITE(Animation, bool, autoreverse)

		TITANIUM_PROPERTY_READWRITE(Animation, std::string, backgroundColor)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<double>, bottom)

		TITANIUM_PROPERTY_READWRITE(Animation, Point, center)

		TITANIUM_PROPERTY_READWRITE(Animation, std::string, color)

		TITANIUM_PROPERTY_READWRITE(Animation, ANIMATION_CURVE, curve)

		TITANIUM_PROPERTY_READWRITE(Animation, std::chrono::milliseconds, delay)

		TITANIUM_PROPERTY_READWRITE(Animation, std::chrono::milliseconds, duration)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<double>, height)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<double>, left)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<double>, opacity)

		TITANIUM_PROPERTY_READWRITE(Animation, bool, opaque)

		TITANIUM_PROPERTY_READWRITE(Animation, uint32_t, repeat)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<double>, right)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<double>, top)

		TITANIUM_PROPERTY_READWRITE(Animation, std::shared_ptr<TwoDMatrix>, transform)

		TITANIUM_PROPERTY_READWRITE(Animation, uint32_t, transition)

		TITANIUM_PROPERTY_READWRITE(Animation, std::shared_ptr<View>, view)

		TITANIUM_PROPERTY_READWRITE(Animation, bool, visible)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<double>, width)

		TITANIUM_PROPERTY_READWRITE(Animation, boost::optional<uint32_t>, zIndex)

		void Animation::JSExportInitialize() {
			JSExport<Animation>::SetClassVersion(1);
			JSExport<Animation>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(Animation, anchorPoint);
			TITANIUM_ADD_PROPERTY(Animation, autoreverse);
			TITANIUM_ADD_PROPERTY(Animation, backgroundColor);
			TITANIUM_ADD_PROPERTY(Animation, bottom);
			TITANIUM_ADD_PROPERTY(Animation, center);
			TITANIUM_ADD_PROPERTY(Animation, color);
			TITANIUM_ADD_PROPERTY(Animation, curve);
			TITANIUM_ADD_PROPERTY(Animation, delay);
			TITANIUM_ADD_PROPERTY(Animation, duration);
			TITANIUM_ADD_PROPERTY(Animation, height);
			TITANIUM_ADD_PROPERTY(Animation, left);
			TITANIUM_ADD_PROPERTY(Animation, opacity);
			TITANIUM_ADD_PROPERTY(Animation, opaque);
			TITANIUM_ADD_PROPERTY(Animation, repeat);
			TITANIUM_ADD_PROPERTY(Animation, right);
			TITANIUM_ADD_PROPERTY(Animation, top);
			TITANIUM_ADD_PROPERTY(Animation, transform);
			TITANIUM_ADD_PROPERTY(Animation, transition);
			TITANIUM_ADD_PROPERTY(Animation, view);
			TITANIUM_ADD_PROPERTY(Animation, visible);
			TITANIUM_ADD_PROPERTY(Animation, width);
			TITANIUM_ADD_PROPERTY(Animation, zIndex);

			TITANIUM_ADD_FUNCTION(Animation, getAnchorPoint);
			TITANIUM_ADD_FUNCTION(Animation, setAnchorPoint);
			TITANIUM_ADD_FUNCTION(Animation, getAutoreverse);
			TITANIUM_ADD_FUNCTION(Animation, setAutoreverse);
			TITANIUM_ADD_FUNCTION(Animation, getBackgroundColor);
			TITANIUM_ADD_FUNCTION(Animation, setBackgroundColor);
			TITANIUM_ADD_FUNCTION(Animation, getBottom);
			TITANIUM_ADD_FUNCTION(Animation, setBottom);
			TITANIUM_ADD_FUNCTION(Animation, getCenter);
			TITANIUM_ADD_FUNCTION(Animation, setCenter);
			TITANIUM_ADD_FUNCTION(Animation, getColor);
			TITANIUM_ADD_FUNCTION(Animation, setColor);
			TITANIUM_ADD_FUNCTION(Animation, getCurve);
			TITANIUM_ADD_FUNCTION(Animation, setCurve);
			TITANIUM_ADD_FUNCTION(Animation, getDelay);
			TITANIUM_ADD_FUNCTION(Animation, setDelay);
			TITANIUM_ADD_FUNCTION(Animation, getDuration);
			TITANIUM_ADD_FUNCTION(Animation, setDuration);
			TITANIUM_ADD_FUNCTION(Animation, getHeight);
			TITANIUM_ADD_FUNCTION(Animation, setHeight);
			TITANIUM_ADD_FUNCTION(Animation, getLeft);
			TITANIUM_ADD_FUNCTION(Animation, setLeft);
			TITANIUM_ADD_FUNCTION(Animation, getOpacity);
			TITANIUM_ADD_FUNCTION(Animation, setOpacity);
			TITANIUM_ADD_FUNCTION(Animation, getOpaque);
			TITANIUM_ADD_FUNCTION(Animation, setOpaque);
			TITANIUM_ADD_FUNCTION(Animation, getRepeat);
			TITANIUM_ADD_FUNCTION(Animation, setRepeat);
			TITANIUM_ADD_FUNCTION(Animation, getRight);
			TITANIUM_ADD_FUNCTION(Animation, setRight);
			TITANIUM_ADD_FUNCTION(Animation, getTop);
			TITANIUM_ADD_FUNCTION(Animation, setTop);
			TITANIUM_ADD_FUNCTION(Animation, getTransform);
			TITANIUM_ADD_FUNCTION(Animation, setTransform);
			TITANIUM_ADD_FUNCTION(Animation, getTransition);
			TITANIUM_ADD_FUNCTION(Animation, setTransition);
			TITANIUM_ADD_FUNCTION(Animation, getView);
			TITANIUM_ADD_FUNCTION(Animation, setView);
			TITANIUM_ADD_FUNCTION(Animation, getVisible);
			TITANIUM_ADD_FUNCTION(Animation, setVisible);
			TITANIUM_ADD_FUNCTION(Animation, getWidth);
			TITANIUM_ADD_FUNCTION(Animation, setWidth);
			TITANIUM_ADD_FUNCTION(Animation, getZIndex);
			TITANIUM_ADD_FUNCTION(Animation, setZIndex);
		}

		TITANIUM_PROPERTY_GETTER(Animation, anchorPoint)
		{
			return Point_to_js(get_context(), get_anchorPoint());
		}

		TITANIUM_PROPERTY_SETTER(Animation, anchorPoint)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_anchorPoint(js_to_Point(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, autoreverse)
		{
			return get_context().CreateBoolean(get_autoreverse());
		}

		TITANIUM_PROPERTY_SETTER(Animation, autoreverse)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_autoreverse(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, backgroundColor)
		{
			return get_context().CreateString(get_backgroundColor());
		}

		TITANIUM_PROPERTY_SETTER(Animation, backgroundColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_backgroundColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, bottom)
		{
			auto bottom = get_bottom();
			if (bottom) {
				return get_context().CreateNumber(*bottom);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, bottom)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_bottom(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, center)
		{
			return Point_to_js(get_context(), get_center());
		}

		TITANIUM_PROPERTY_SETTER(Animation, center)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_center(js_to_Point(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, color)
		{
			return get_context().CreateString(get_color());
		}

		TITANIUM_PROPERTY_SETTER(Animation, color)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, curve)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<ANIMATION_CURVE>::type>(get_curve()));
		}

		TITANIUM_PROPERTY_SETTER(Animation, curve)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_curve(Constants::to_ANIMATION_CURVE(static_cast<std::underlying_type<ANIMATION_CURVE>::type>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, delay)
		{
			return get_context().CreateNumber(static_cast<double>(get_delay().count()));
		}

		TITANIUM_PROPERTY_SETTER(Animation, delay)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			const auto delay = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(argument)));
			set_delay(delay);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, duration)
		{
			return get_context().CreateNumber(static_cast<double>(get_duration().count()));
		}

		TITANIUM_PROPERTY_SETTER(Animation, duration)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			const auto duration = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(argument)));
			set_duration(duration);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, height)
		{
			auto height = get_height();
			if (height) {
				return get_context().CreateNumber(*height);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, height)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_height(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, left)
		{
			auto left = get_left();
			if (left) {
				return get_context().CreateNumber(*left);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, left)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_left(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, opacity)
		{
			auto opacity = get_opacity();
			if (opacity) {
				return get_context().CreateNumber(*opacity);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, opacity)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_opacity(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, opaque)
		{
			return get_context().CreateBoolean(get_opaque());
		}

		TITANIUM_PROPERTY_SETTER(Animation, opaque)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_opaque(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, repeat)
		{
			return get_context().CreateNumber(get_repeat());
		}

		TITANIUM_PROPERTY_SETTER(Animation, repeat)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_repeat(static_cast<uint32_t>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, right)
		{
			auto right = get_right();
			if (right) {
				return get_context().CreateNumber(*right);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, right)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_right(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, top)
		{
			auto top = get_top();
			if (top) {
				get_context().CreateNumber(*top);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, top)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_top(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, transform)
		{
			return static_cast<JSValue>(get_transform()->get_object());
		}

		TITANIUM_PROPERTY_SETTER(Animation, transform)
		{
			TITANIUM_ASSERT(argument.IsObject());
			const auto object = static_cast<JSObject>(argument);
			set_transform(object.GetPrivate<Titanium::UI::TwoDMatrix>());
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, transition)
		{
			return get_context().CreateNumber(get_transition());
		}

		TITANIUM_PROPERTY_SETTER(Animation, transition)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_transition(static_cast<uint32_t>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, view)
		{
			return static_cast<JSValue>(get_view()->get_object());
		}

		TITANIUM_PROPERTY_SETTER(Animation, view)
		{
			TITANIUM_ASSERT(argument.IsObject());
			const auto object = static_cast<JSObject>(argument);
			set_view(object.GetPrivate<Titanium::UI::View>());
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, visible)
		{
			return get_context().CreateBoolean(get_visible());
		}

		TITANIUM_PROPERTY_SETTER(Animation, visible)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_visible(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, width)
		{
			auto width = get_width();
			if (width) {
				return get_context().CreateNumber(*width);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, width)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_width(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Animation, zIndex)
		{
			auto zIndex = get_zIndex();
			if (zIndex) {
				return get_context().CreateNumber(*zIndex);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(Animation, zIndex)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_zIndex(static_cast<uint32_t>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Animation, getAnchorPoint, anchorPoint)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setAnchorPoint, anchorPoint)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getAutoreverse, autoreverse)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setAutoreverse, autoreverse)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getBackgroundColor, backgroundColor)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setBackgroundColor, backgroundColor)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getBottom, bottom)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setBottom, bottom)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getCenter, center)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setCenter, center)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setColor, color)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getCurve, curve)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setCurve, curve)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getDelay, delay)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setDelay, delay)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getDuration, duration)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setDuration, duration)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getHeight, height)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setHeight, height)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getLeft, left)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setLeft, left)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getOpacity, opacity)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setOpacity, opacity)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getOpaque, opaque)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setOpaque, opaque)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getRepeat, repeat)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setRepeat, repeat)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getRight, right)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setRight, right)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getTop, top)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setTop, top)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getTransform, transform)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setTransform, transform)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getTransition, transition)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setTransition, transition)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getView, view)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setView, view)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getVisible, visible)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setVisible, visible)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getWidth, width)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setWidth, width)

		TITANIUM_FUNCTION_AS_GETTER(Animation, getZIndex, zIndex)
		TITANIUM_FUNCTION_AS_SETTER(Animation, setZIndex, zIndex)

	} // namespace UI
} // namespace Titanium
