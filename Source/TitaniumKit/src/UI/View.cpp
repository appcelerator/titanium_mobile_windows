/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		View::View(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Module(js_context),
		      children__(js_context.CreateArray()),
		      backgroundColor__(js_context.CreateString()),
		      top__(js_context.CreateString()),
		      left__(js_context.CreateString()),
		      bottom__(js_context.CreateString()),
		      right__(js_context.CreateString()),
		      center__(js_context.CreateObject()),
		      width__(js_context.CreateString()),
		      height__(js_context.CreateString()),
		      layout__(js_context.CreateString())
		{
			TITANIUM_LOG_DEBUG("View:: ctor ", this);
		}

		View::~View() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View:: dtor ", this);
		}

		void View::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View::add");

			// precondition
			auto native_view_ptr = view.GetPrivate<View>();
			TITANIUM_ASSERT(native_view_ptr.get());

			const auto view_count = children__.GetPropertyNames().GetCount();
			children__.SetProperty(static_cast<unsigned>(view_count), view);
		}

		void View::hide(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View::hide");
		}

		void View::show(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View::show");
		}

		JSArray View::get_children() const TITANIUM_NOEXCEPT
		{
			return children__;
		}

		std::string View::get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return backgroundColor__;
		}

		void View::set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT
		{
			backgroundColor__ = backgroundColor;
		}

		std::string View::get_top() const TITANIUM_NOEXCEPT
		{
			return top__;
		}

		void View::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			top__ = top;
		}

		std::string View::get_left() const TITANIUM_NOEXCEPT
		{
			return left__;
		}

		void View::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			left__ = left;
		}

		std::string View::get_bottom() const TITANIUM_NOEXCEPT
		{
			return bottom__;
		}

		void View::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			bottom__ = bottom;
		}

		std::string View::get_right() const TITANIUM_NOEXCEPT
		{
			return right__;
		}

		void View::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			right__ = right;
		}

		JSObject View::get_center() const TITANIUM_NOEXCEPT
		{
			return center__;
		}

		void View::set_center(const JSObject& center) TITANIUM_NOEXCEPT
		{
			center__ = center;
		}

		std::string View::get_width() const TITANIUM_NOEXCEPT
		{
			return width__;
		}

		void View::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			width__ = width;
		}

		std::string View::get_height() const TITANIUM_NOEXCEPT
		{
			return height__;
		}

		void View::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			height__ = height;
		}

		std::string View::get_layout() const TITANIUM_NOEXCEPT
		{
			return layout__;
		}

		void View::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			layout__ = layout;
		}

		NativeChildrenList_t View::get_native_children() const TITANIUM_NOEXCEPT
		{
			NativeChildrenList_t native_children_list;

			const auto child_count = children__.GetPropertyNames().GetCount();
			for (unsigned i = 0; i < child_count; ++i) {
				JSValue child_property = children__.GetProperty(i);

				// preconditions
				TITANIUM_ASSERT(child_property.IsObject());

				JSObject child = static_cast<JSObject>(child_property);

				// precondition
				auto native_child_ptr = child.GetPrivate<View>();
				TITANIUM_ASSERT(native_child_ptr);

				native_children_list.push_back(native_child_ptr);
			}

			return native_children_list;
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Module>::Class());
			JSExport<View>::AddFunctionProperty("add", std::mem_fn(&View::js_add));
			JSExport<View>::AddFunctionProperty("hide", std::mem_fn(&View::js_hide));
			JSExport<View>::AddFunctionProperty("show", std::mem_fn(&View::js_show));
			JSExport<View>::AddValueProperty("children", std::mem_fn(&View::get_children));
			JSExport<View>::AddValueProperty("backgroundColor", std::mem_fn(&View::js_get_backgroundColor), std::mem_fn(&View::js_set_backgroundColor));
			JSExport<View>::AddValueProperty("top", std::mem_fn(&View::js_get_top), std::mem_fn(&View::js_set_top));
			JSExport<View>::AddValueProperty("left", std::mem_fn(&View::js_get_left), std::mem_fn(&View::js_set_left));
			JSExport<View>::AddValueProperty("bottom", std::mem_fn(&View::js_get_bottom), std::mem_fn(&View::js_set_bottom));
			JSExport<View>::AddValueProperty("center", std::mem_fn(&View::get_center), std::mem_fn(&View::js_set_center));
			JSExport<View>::AddValueProperty("right", std::mem_fn(&View::js_get_right), std::mem_fn(&View::js_set_right));
			JSExport<View>::AddValueProperty("width", std::mem_fn(&View::js_get_width), std::mem_fn(&View::js_set_width));
			JSExport<View>::AddValueProperty("height", std::mem_fn(&View::js_get_height), std::mem_fn(&View::js_set_height));
			JSExport<View>::AddValueProperty("layout", std::mem_fn(&View::js_get_layout), std::mem_fn(&View::js_set_layout));
		}

		JSValue View::js_add(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() >= 1);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			JSObject view = static_cast<JSObject>(_0);
			add(view, this_object);
			return get_context().CreateUndefined();
		}

		JSValue View::js_hide(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() == 0);
			hide(this_object);
			return get_context().CreateUndefined();
		}

		JSValue View::js_show(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() == 0);
			show(this_object);
			return get_context().CreateUndefined();
		}

		JSValue View::js_get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(backgroundColor__);
		}

		bool View::js_set_backgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			bool result = false;
			std::string backgroundColorName = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_backgroundColor: backgroundColor = ", backgroundColorName);
			set_backgroundColor(backgroundColorName);
			result = true;
			return result;
		}

		bool View::js_set_center(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::js_set_center: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsObject();
			// bool result = false;
			// JSObject center = argument;
			// TITANIUM_ASSERT(center.HasProperty("x");
			// TITANIUM_ASSERT(center.HasProperty("y");
			// const std::string x = static_cast<std::string>(center.GetProperty("x"));
			// const std::string y = static_cast<std::string>(center.GetProperty("y"));
			// Set the native view's position.
			// set_center(center);
			// result = true;
			// return result;

			return false;
		}

		JSValue View::js_get_top() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(top__);
		}

		bool View::js_set_top(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			// FIXME What does setting top to null mean? Because corporate directory does it...
			if (argument.IsNull()) {
				return false;
			}
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_top: top = ", value);
			set_top(value);
			result = true;
			return result;
		}

		JSValue View::js_get_left() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(left__);
		}

		bool View::js_set_left(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_left: left = ", value);
			set_left(value);
			result = true;
			return result;
		}

		JSValue View::js_get_width() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(width__);
		}

		bool View::js_set_width(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_width: width = ", value);
			set_width(value);
			result = true;
			return result;
		}

		JSValue View::js_get_height() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(height__);
		}

		bool View::js_set_height(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_height: height = ", value);
			set_height(value);
			result = true;
			return result;
		}

		JSValue View::js_get_bottom() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(bottom__);
		}

		bool View::js_set_bottom(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_bottom: bottom = ", value);
			set_bottom(value);
			result = true;
			return result;
		}

		JSValue View::js_get_right() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(right__);
		}

		bool View::js_set_right(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_right: right = ", value);
			set_right(value);
			result = true;
			return result;
		}

		JSValue View::js_get_layout() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(layout__);
		}

		bool View::js_set_layout(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("View::js_set_layout: layout = ", value);
			set_layout(value);
			result = true;
			return result;
		}
	} // namespace UI
}  // namespace Titanium
