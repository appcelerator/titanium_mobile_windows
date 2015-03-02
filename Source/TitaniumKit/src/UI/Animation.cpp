/**
 * Titanium.UI.Animation for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Animation.hpp"

namespace Titanium
{
	namespace UI
	{


		Animation::Animation(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context),
			autoreverse__(false),
			backgroundColor__(""),
			bottom__(0),
			center__(js_context.CreateObject()),
			color__(""),
			curve__(ANIMATION_CURVE::EASE_IN),
			delay__(0),
			duration__(0),
			height__(0),
			left__(0),
			opacity__(0),
			opaque__(true),
			repeat__(1),
			right__(0),
			top__(0),
			transform__(js_context.CreateNull()),
			transition__(0),
			view__(js_context.CreateNull()),
			visible__(true),
			width__(0),
			zIndex__(1)
		{
			TITANIUM_LOG_DEBUG("Animation:: ctor ", this);
		}

		void Animation::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			HAL_LOG_DEBUG("Animation:: postCallAsConstructor ", this);
		}

		bool Animation::get_autoreverse() const TITANIUM_NOEXCEPT
		{
			return autoreverse__;
		}

		void Animation::set_autoreverse(const bool& autoreverse) TITANIUM_NOEXCEPT
		{
			autoreverse__ = autoreverse;
		}

		std::string Animation::get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return backgroundColor__;
		}

		void Animation::set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT
		{
			backgroundColor__ = backgroundColor;
		}

		double Animation::get_bottom() const TITANIUM_NOEXCEPT
		{
			return bottom__;
		}

		void Animation::set_bottom(const double& bottom) TITANIUM_NOEXCEPT
		{
			bottom__ = bottom;
		}

		JSObject Animation::get_center() const TITANIUM_NOEXCEPT
		{
			return center__;
		}

		void Animation::set_center(const JSObject& center) TITANIUM_NOEXCEPT
		{
			center__ = center;
		}

		std::string Animation::get_color() const TITANIUM_NOEXCEPT
		{
			return color__;
		}

		void Animation::set_color(const std::string& color) TITANIUM_NOEXCEPT
		{
			color__ = color;
		}

		ANIMATION_CURVE Animation::get_curve() const TITANIUM_NOEXCEPT
		{
			return curve__;
		}

		void Animation::set_curve(const ANIMATION_CURVE& curve) TITANIUM_NOEXCEPT
		{
			curve__ = curve;
		}

		std::chrono::milliseconds Animation::get_delay() const TITANIUM_NOEXCEPT
		{
			return delay__;
		}
		
		void Animation::set_delay(const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT
		{
			delay__ = delay;
		}

		std::chrono::milliseconds Animation::get_duration() const TITANIUM_NOEXCEPT
		{
			return duration__;
		}

		void Animation::set_duration(const std::chrono::milliseconds& duration) TITANIUM_NOEXCEPT
		{
			duration__ = duration;
		}

		double Animation::get_height() const TITANIUM_NOEXCEPT
		{
			return height__;
		}

		void Animation::set_height(const double& height) TITANIUM_NOEXCEPT
		{
			height__ = height;
		}

		double Animation::get_left() const TITANIUM_NOEXCEPT
		{
			return left__;
		}

		void Animation::set_left(const double& left) TITANIUM_NOEXCEPT
		{
			left__ = left;
		}

		double Animation::get_opacity() const TITANIUM_NOEXCEPT
		{
			return opacity__;
		}

		void Animation::set_opacity(const double& opacity) TITANIUM_NOEXCEPT
		{
			opacity__ = opacity;
		}

		bool Animation::get_opaque() const TITANIUM_NOEXCEPT
		{
			return opaque__;
		}

		void Animation::set_opaque(const bool& opaque) TITANIUM_NOEXCEPT
		{
			opaque__ = opaque;
		}

		uint32_t Animation::get_repeat() const TITANIUM_NOEXCEPT
		{
			return repeat__;
		}

		void Animation::set_repeat(const uint32_t& repeat) TITANIUM_NOEXCEPT
		{
			repeat__ = repeat;
		}

		double Animation::get_right() const TITANIUM_NOEXCEPT
		{
			return right__;
		}

		void Animation::set_right(const double& right) TITANIUM_NOEXCEPT
		{
			right__ = right;
		}

		double Animation::get_top() const TITANIUM_NOEXCEPT
		{
			return top__;
		}

		void Animation::set_top(const double& top) TITANIUM_NOEXCEPT
		{
			top__ = top;
		}

		JSValue Animation::get_transform() const TITANIUM_NOEXCEPT
		{
			return transform__;
		}

		void Animation::set_transform(const JSValue& transform) TITANIUM_NOEXCEPT
		{
			transform__ = transform;
		}

		uint32_t Animation::get_transition() const TITANIUM_NOEXCEPT
		{
			return transition__;
		}

		void Animation::set_transition(const uint32_t& transition) TITANIUM_NOEXCEPT
		{
			transition__ = transition;
		}

		JSValue Animation::get_view() const TITANIUM_NOEXCEPT
		{
			return view__;
		}

		void Animation::set_view(const JSValue& view) TITANIUM_NOEXCEPT
		{
			view__ = view;
		}

		bool Animation::get_visible() const TITANIUM_NOEXCEPT
		{
			return visible__;
		}

		void Animation::set_visible(const bool& visible) TITANIUM_NOEXCEPT
		{
			visible__ = visible;
		}

		double Animation::get_width() const TITANIUM_NOEXCEPT
		{
			return width__;
		}

		void Animation::set_width(const double& width) TITANIUM_NOEXCEPT
		{
			width__ = width;
		}

		uint32_t Animation::get_zIndex() const TITANIUM_NOEXCEPT
		{
			return zIndex__;
		}
		
		void Animation::set_zIndex(const uint32_t& zIndex) TITANIUM_NOEXCEPT
		{
			zIndex__ = zIndex;
		}

		void Animation::JSExportInitialize() {
			JSExport<Animation>::SetClassVersion(1);
			JSExport<Animation>::SetParent(JSExport<Module>::Class());

			JSExport<Animation>::AddValueProperty("autoreverse", std::mem_fn(&Animation::js_get_autoreverse), std::mem_fn(&Animation::js_set_autoreverse));
			JSExport<Animation>::AddValueProperty("backgroundColor", std::mem_fn(&Animation::js_get_backgroundColor), std::mem_fn(&Animation::js_set_backgroundColor));
			JSExport<Animation>::AddValueProperty("bottom", std::mem_fn(&Animation::js_get_bottom), std::mem_fn(&Animation::js_set_bottom));
			JSExport<Animation>::AddValueProperty("center", std::mem_fn(&Animation::js_get_center), std::mem_fn(&Animation::js_set_center));
			JSExport<Animation>::AddValueProperty("color", std::mem_fn(&Animation::js_get_color), std::mem_fn(&Animation::js_set_color));
			JSExport<Animation>::AddValueProperty("curve", std::mem_fn(&Animation::js_get_curve), std::mem_fn(&Animation::js_set_curve));
			JSExport<Animation>::AddValueProperty("delay", std::mem_fn(&Animation::js_get_delay), std::mem_fn(&Animation::js_set_delay));
			JSExport<Animation>::AddValueProperty("duration", std::mem_fn(&Animation::js_get_duration), std::mem_fn(&Animation::js_set_duration));
			JSExport<Animation>::AddValueProperty("height", std::mem_fn(&Animation::js_get_height), std::mem_fn(&Animation::js_set_height));
			JSExport<Animation>::AddValueProperty("left", std::mem_fn(&Animation::js_get_left), std::mem_fn(&Animation::js_set_left));
			JSExport<Animation>::AddValueProperty("opacity", std::mem_fn(&Animation::js_get_opacity), std::mem_fn(&Animation::js_set_opacity));
			JSExport<Animation>::AddValueProperty("opaque", std::mem_fn(&Animation::js_get_opaque), std::mem_fn(&Animation::js_set_opaque));
			JSExport<Animation>::AddValueProperty("repeat", std::mem_fn(&Animation::js_get_repeat), std::mem_fn(&Animation::js_set_repeat));
			JSExport<Animation>::AddValueProperty("right", std::mem_fn(&Animation::js_get_right), std::mem_fn(&Animation::js_set_right));
			JSExport<Animation>::AddValueProperty("top", std::mem_fn(&Animation::js_get_top), std::mem_fn(&Animation::js_set_top));
			JSExport<Animation>::AddValueProperty("transform", std::mem_fn(&Animation::js_get_transform), std::mem_fn(&Animation::js_set_transform));
			JSExport<Animation>::AddValueProperty("transition", std::mem_fn(&Animation::js_get_transition), std::mem_fn(&Animation::js_set_transition));
			JSExport<Animation>::AddValueProperty("view", std::mem_fn(&Animation::js_get_view), std::mem_fn(&Animation::js_set_view));
			JSExport<Animation>::AddValueProperty("visible", std::mem_fn(&Animation::js_get_visible), std::mem_fn(&Animation::js_set_visible));
			JSExport<Animation>::AddValueProperty("width", std::mem_fn(&Animation::js_get_width), std::mem_fn(&Animation::js_set_width));
			JSExport<Animation>::AddValueProperty("zIndex", std::mem_fn(&Animation::js_get_zIndex), std::mem_fn(&Animation::js_set_zIndex));

			JSExport<Animation>::AddFunctionProperty("getAutoreverse", std::mem_fn(&Animation::js_getAutoreverse));
			JSExport<Animation>::AddFunctionProperty("setAutoreverse", std::mem_fn(&Animation::js_setAutoreverse));
			JSExport<Animation>::AddFunctionProperty("getBackgroundColor", std::mem_fn(&Animation::js_getBackgroundColor));
			JSExport<Animation>::AddFunctionProperty("setBackgroundColor", std::mem_fn(&Animation::js_setBackgroundColor));
			JSExport<Animation>::AddFunctionProperty("getBottom", std::mem_fn(&Animation::js_getBottom));
			JSExport<Animation>::AddFunctionProperty("setBottom", std::mem_fn(&Animation::js_setBottom));
			JSExport<Animation>::AddFunctionProperty("getCenter", std::mem_fn(&Animation::js_getCenter));
			JSExport<Animation>::AddFunctionProperty("setCenter", std::mem_fn(&Animation::js_setCenter));
			JSExport<Animation>::AddFunctionProperty("getColor", std::mem_fn(&Animation::js_getColor));
			JSExport<Animation>::AddFunctionProperty("setColor", std::mem_fn(&Animation::js_setColor));
			JSExport<Animation>::AddFunctionProperty("getCurve", std::mem_fn(&Animation::js_getCurve));
			JSExport<Animation>::AddFunctionProperty("setCurve", std::mem_fn(&Animation::js_setCurve));
			JSExport<Animation>::AddFunctionProperty("getDelay", std::mem_fn(&Animation::js_getDelay));
			JSExport<Animation>::AddFunctionProperty("setDelay", std::mem_fn(&Animation::js_setDelay));
			JSExport<Animation>::AddFunctionProperty("getDuration", std::mem_fn(&Animation::js_getDuration));
			JSExport<Animation>::AddFunctionProperty("setDuration", std::mem_fn(&Animation::js_setDuration));
			JSExport<Animation>::AddFunctionProperty("getHeight", std::mem_fn(&Animation::js_getHeight));
			JSExport<Animation>::AddFunctionProperty("setHeight", std::mem_fn(&Animation::js_setHeight));
			JSExport<Animation>::AddFunctionProperty("getLeft", std::mem_fn(&Animation::js_getLeft));
			JSExport<Animation>::AddFunctionProperty("setLeft", std::mem_fn(&Animation::js_setLeft));
			JSExport<Animation>::AddFunctionProperty("getOpacity", std::mem_fn(&Animation::js_getOpacity));
			JSExport<Animation>::AddFunctionProperty("setOpacity", std::mem_fn(&Animation::js_setOpacity));
			JSExport<Animation>::AddFunctionProperty("getOpaque", std::mem_fn(&Animation::js_getOpaque));
			JSExport<Animation>::AddFunctionProperty("setOpaque", std::mem_fn(&Animation::js_setOpaque));
			JSExport<Animation>::AddFunctionProperty("getRepeat", std::mem_fn(&Animation::js_getRepeat));
			JSExport<Animation>::AddFunctionProperty("setRepeat", std::mem_fn(&Animation::js_setRepeat));
			JSExport<Animation>::AddFunctionProperty("getRight", std::mem_fn(&Animation::js_getRight));
			JSExport<Animation>::AddFunctionProperty("setRight", std::mem_fn(&Animation::js_setRight));
			JSExport<Animation>::AddFunctionProperty("getTop", std::mem_fn(&Animation::js_getTop));
			JSExport<Animation>::AddFunctionProperty("setTop", std::mem_fn(&Animation::js_setTop));
			JSExport<Animation>::AddFunctionProperty("getTransform", std::mem_fn(&Animation::js_getTransform));
			JSExport<Animation>::AddFunctionProperty("setTransform", std::mem_fn(&Animation::js_setTransform));
			JSExport<Animation>::AddFunctionProperty("getTransition", std::mem_fn(&Animation::js_getTransition));
			JSExport<Animation>::AddFunctionProperty("setTransition", std::mem_fn(&Animation::js_setTransition));
			JSExport<Animation>::AddFunctionProperty("getView", std::mem_fn(&Animation::js_getView));
			JSExport<Animation>::AddFunctionProperty("setView", std::mem_fn(&Animation::js_setView));
			JSExport<Animation>::AddFunctionProperty("getVisible", std::mem_fn(&Animation::js_getVisible));
			JSExport<Animation>::AddFunctionProperty("setVisible", std::mem_fn(&Animation::js_setVisible));
			JSExport<Animation>::AddFunctionProperty("getWidth", std::mem_fn(&Animation::js_getWidth));
			JSExport<Animation>::AddFunctionProperty("setWidth", std::mem_fn(&Animation::js_setWidth));
			JSExport<Animation>::AddFunctionProperty("getZIndex", std::mem_fn(&Animation::js_getZIndex));
			JSExport<Animation>::AddFunctionProperty("setZIndex", std::mem_fn(&Animation::js_setZIndex));
		}

		JSValue Animation::js_get_autoreverse() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_autoreverse());
		}

		bool Animation::js_set_autoreverse(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_autoreverse(static_cast<bool>(argument));
			return true;
		}

		JSValue Animation::js_get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_backgroundColor());
		}

		bool Animation::js_set_backgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_backgroundColor(static_cast<std::string>(argument));
			return true;
		}

		JSValue Animation::js_get_bottom() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_bottom());
		}

		bool Animation::js_set_bottom(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_bottom(static_cast<double>(argument));
			return true;
		}

		JSValue Animation::js_get_center() const TITANIUM_NOEXCEPT
		{
			return get_center();
		}

		bool Animation::js_set_center(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_center(static_cast<JSObject>(argument));
			return true;
		}

		JSValue Animation::js_get_color() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_color());
		}

		bool Animation::js_set_color(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		JSValue Animation::js_get_curve() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<ANIMATION_CURVE>::type>(get_curve()));
		}

		bool Animation::js_set_curve(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_curve(Constants::to_ANIMATION_CURVE(static_cast<std::underlying_type<ANIMATION_CURVE>::type>(argument)));
			return true;
		}

		JSValue Animation::js_get_delay() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<double>(get_delay().count()));
		}

		bool Animation::js_set_delay(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			const auto delay = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(argument)));
			set_delay(delay);
			return true;
		}

		JSValue Animation::js_get_duration() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<double>(get_duration().count()));
		}

		bool Animation::js_set_duration(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			const auto duration = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(argument)));
			set_duration(duration);
			return true;
		}

		JSValue Animation::js_get_height() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_height());
		}

		bool Animation::js_set_height(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_height(static_cast<double>(argument));
			return true;
		}

		JSValue Animation::js_get_left() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_left());
		}

		bool Animation::js_set_left(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_left(static_cast<double>(argument));
			return true;
		}

		JSValue Animation::js_get_opacity() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_opacity());
		}

		bool Animation::js_set_opacity(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_opacity(static_cast<double>(argument));
			return true;
		}

		JSValue Animation::js_get_opaque() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_opaque());
		}

		bool Animation::js_set_opaque(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_opaque(static_cast<bool>(argument));
			return true;
		}

		JSValue Animation::js_get_repeat() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_repeat());
		}

		bool Animation::js_set_repeat(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_repeat(static_cast<uint32_t>(argument));
			return true;
		}

		JSValue Animation::js_get_right() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_right());
		}

		bool Animation::js_set_right(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_right(static_cast<double>(argument));
			return true;
		}

		JSValue Animation::js_get_top() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_top());
		}

		bool Animation::js_set_top(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_top(static_cast<double>(argument));
			return true;
		}

		JSValue Animation::js_get_transform() const TITANIUM_NOEXCEPT
		{
			return get_transform();
		}

		bool Animation::js_set_transform(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_transform(static_cast<JSObject>(argument));
			return true;
		}

		JSValue Animation::js_get_transition() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_transition());
		}

		bool Animation::js_set_transition(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_transition(static_cast<uint32_t>(argument));
			return true;
		}

		JSValue Animation::js_get_view() const TITANIUM_NOEXCEPT
		{
			return get_view();
		}

		bool Animation::js_set_view(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_view(static_cast<JSObject>(argument));
			return true;
		}

		JSValue Animation::js_get_visible() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_visible());
		}

		bool Animation::js_set_visible(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_visible(static_cast<bool>(argument));
			return true;
		}

		JSValue Animation::js_get_width() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_width());
		}

		bool Animation::js_set_width(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_width(static_cast<double>(argument));
			return true;
		}

		JSValue Animation::js_get_zIndex() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_zIndex());
		}

		bool Animation::js_set_zIndex(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_zIndex(static_cast<uint32_t>(argument));
			return true;
		}

		JSValue Animation::js_getAutoreverse(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getAutoreverse is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setAutoreverse(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_autoreverse(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getBackgroundColor(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getBackgroundColor is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setBackgroundColor(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_backgroundColor(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getBottom(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getBottom is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setBottom(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_bottom(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getCenter(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getCenter is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setCenter(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_center(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getColor(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getColor is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setColor(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_color(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getCurve(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getCurve is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setCurve(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_curve(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getDelay(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getDelay is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setDelay(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_delay(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getDuration(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getDuration is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setDuration(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_duration(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getHeight(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getHeight is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setHeight(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_height(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getLeft(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getLeft is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setLeft(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_left(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getOpacity(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getOpacity is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setOpacity(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_opacity(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getOpaque(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getOpaque is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setOpaque(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_opaque(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getRepeat(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getRepeat is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setRepeat(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_repeat(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getRight(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getRight is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setRight(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_right(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getTop(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getTop is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setTop(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_top(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getTransform(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getTransform is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setTransform(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_transform(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getTransition(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getTransition is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setTransition(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_transition(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getView is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setView(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_view(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getVisible(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getVisible is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setVisible(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_visible(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getWidth(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getWidth is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setWidth(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_width(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_getZIndex(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Animation.getZIndex is not implemented yet");
			return get_context().CreateUndefined();
		}

		JSValue Animation::js_setZIndex(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.size() >= 1) {
				js_set_zIndex(arguments.at(0));
			}
			return get_context().CreateUndefined();
		}

	} // namespace UI
} // namespace Titanium