/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/UIBase.hpp"

namespace Titanium
{
	namespace UI
	{
		UIBase::UIBase(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
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
			TITANIUM_LOG_DEBUG("UIBase:: ctor ", this);
		}

		UIBase::~UIBase() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("UIBase:: dtor ", this);
		}

		void UIBase::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("UIBase::add");

			// precondition
			auto native_view_ptr = view.GetPrivate<UIBase>();
			TITANIUM_ASSERT(native_view_ptr.get());

			const auto view_count = children__.GetPropertyNames().GetCount();
			children__.SetProperty(static_cast<unsigned>(view_count), view);
		}

		void UIBase::hide(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("UIBase::hide");
		}

		void UIBase::show(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("UIBase::show");
		}

		JSArray UIBase::get_children() const TITANIUM_NOEXCEPT
		{
			return children__;
		}

		std::string UIBase::get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return backgroundColor__;
		}

		void UIBase::set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT
		{
			backgroundColor__ = backgroundColor;
		}

		std::string UIBase::get_top() const TITANIUM_NOEXCEPT
		{
			return top__;
		}

		void UIBase::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			top__ = top;
		}

		std::string UIBase::get_left() const TITANIUM_NOEXCEPT
		{
			return left__;
		}

		void UIBase::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			left__ = left;
		}

		std::string UIBase::get_bottom() const TITANIUM_NOEXCEPT
		{
			return bottom__;
		}

		void UIBase::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			bottom__ = bottom;
		}

		std::string UIBase::get_right() const TITANIUM_NOEXCEPT
		{
			return right__;
		}

		void UIBase::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			right__ = right;
		}

		JSObject UIBase::get_center() const TITANIUM_NOEXCEPT
		{
			return center__;
		}

		void UIBase::set_center(const JSObject& center) TITANIUM_NOEXCEPT
		{
			center__ = center;
		}

		std::string UIBase::get_width() const TITANIUM_NOEXCEPT
		{
			return width__;
		}

		void UIBase::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			width__ = width;
		}

		std::string UIBase::get_height() const TITANIUM_NOEXCEPT
		{
			return height__;
		}

		void UIBase::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			height__ = height;
		}

		std::string UIBase::get_layout() const TITANIUM_NOEXCEPT
		{
			return layout__;
		}

		void UIBase::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			layout__ = layout;
		}

		NativeChildrenList_t UIBase::get_native_children() const TITANIUM_NOEXCEPT
		{
			NativeChildrenList_t native_children_list;

			const auto child_count = children__.GetPropertyNames().GetCount();
			for (unsigned i = 0; i < child_count; ++i) {
				JSValue child_property = children__.GetProperty(i);

				// preconditions
				TITANIUM_ASSERT(child_property.IsObject());

				JSObject child = static_cast<JSObject>(child_property);

				// precondition
				auto native_child_ptr = child.GetPrivate<UIBase>();
				TITANIUM_ASSERT(native_child_ptr);

				native_children_list.push_back(native_child_ptr);
			}

			return native_children_list;
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void UIBase::JSExportInitialize()
		{
			JSExport<UIBase>::SetClassVersion(1);
			JSExport<UIBase>::SetParent(JSExport<Module>::Class());
			JSExport<UIBase>::AddFunctionProperty("add", std::mem_fn(&UIBase::js_add));
			JSExport<UIBase>::AddFunctionProperty("hide", std::mem_fn(&UIBase::js_hide));
			JSExport<UIBase>::AddFunctionProperty("show", std::mem_fn(&UIBase::js_show));
			JSExport<UIBase>::AddValueProperty("children", std::mem_fn(&UIBase::get_children));
			JSExport<UIBase>::AddValueProperty("backgroundColor", std::mem_fn(&UIBase::js_get_backgroundColor), std::mem_fn(&UIBase::js_set_backgroundColor));
			JSExport<UIBase>::AddValueProperty("top", std::mem_fn(&UIBase::js_get_top), std::mem_fn(&UIBase::js_set_top));
			JSExport<UIBase>::AddValueProperty("left", std::mem_fn(&UIBase::js_get_left), std::mem_fn(&UIBase::js_set_left));
			JSExport<UIBase>::AddValueProperty("bottom", std::mem_fn(&UIBase::js_get_bottom), std::mem_fn(&UIBase::js_set_bottom));
			JSExport<UIBase>::AddValueProperty("center", std::mem_fn(&UIBase::get_center), std::mem_fn(&UIBase::js_set_center));
			JSExport<UIBase>::AddValueProperty("right", std::mem_fn(&UIBase::js_get_right), std::mem_fn(&UIBase::js_set_right));
			JSExport<UIBase>::AddValueProperty("width", std::mem_fn(&UIBase::js_get_width), std::mem_fn(&UIBase::js_set_width));
			JSExport<UIBase>::AddValueProperty("height", std::mem_fn(&UIBase::js_get_height), std::mem_fn(&UIBase::js_set_height));
			JSExport<UIBase>::AddValueProperty("layout", std::mem_fn(&UIBase::js_get_layout), std::mem_fn(&UIBase::js_set_layout));
		}

		JSValue UIBase::js_add(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
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

		JSValue UIBase::js_hide(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() == 0);
			hide(this_object);
			return get_context().CreateUndefined();
		}

		JSValue UIBase::js_show(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() == 0);
			show(this_object);
			return get_context().CreateUndefined();
		}

		JSValue UIBase::js_get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(backgroundColor__);
		}

		bool UIBase::js_set_backgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			bool result = false;
			std::string backgroundColorName = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_backgroundColor: backgroundColor = ", backgroundColorName);
			set_backgroundColor(backgroundColorName);
			result = true;
			return result;
		}

		bool UIBase::js_set_center(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("UIBase::js_set_center: Unimplemented");

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

		JSValue UIBase::js_get_top() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(top__);
		}

		bool UIBase::js_set_top(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_top: top = ", value);
			set_top(value);
			result = true;
			return result;
		}

		JSValue UIBase::js_get_left() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(left__);
		}

		bool UIBase::js_set_left(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_left: left = ", value);
			set_left(value);
			result = true;
			return result;
		}

		JSValue UIBase::js_get_width() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(width__);
		}

		bool UIBase::js_set_width(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_width: width = ", value);
			set_width(value);
			result = true;
			return result;
		}

		JSValue UIBase::js_get_height() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(height__);
		}

		bool UIBase::js_set_height(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_height: height = ", value);
			set_height(value);
			result = true;
			return result;
		}

		JSValue UIBase::js_get_bottom() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(bottom__);
		}

		bool UIBase::js_set_bottom(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_bottom: bottom = ", value);
			set_bottom(value);
			result = true;
			return result;
		}

		JSValue UIBase::js_get_right() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(right__);
		}

		bool UIBase::js_set_right(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_right: right = ", value);
			set_right(value);
			result = true;
			return result;
		}

		JSValue UIBase::js_get_layout() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(layout__);
		}

		bool UIBase::js_set_layout(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			bool result = false;
			std::string value = static_cast<std::string>(argument);
			TITANIUM_LOG_INFO("UIBase::js_set_layout: layout = ", value);
			set_layout(value);
			result = true;
			return result;
		}
	} // namespace UI
}  // namespace Titanium
