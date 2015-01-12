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
		View::View(const JSContext& js_context) TITANIUM_NOEXCEPT : Module(js_context),
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
			TITANIUM_LOG_DEBUG("View:: ctor 1 ", this);
		}

		View::View(const View& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Module(rhs, arguments),
		      children__(rhs.children__),
		      backgroundColor__(rhs.backgroundColor__),
		      top__(rhs.top__),
		      left__(rhs.left__),
		      bottom__(rhs.bottom__),
		      right__(rhs.right__),
		      center__(rhs.center__),
		      width__(rhs.width__),
		      height__(rhs.height__),
		      layout__(rhs.layout__)
		{
			TITANIUM_LOG_DEBUG("View:: ctor 2 ", this);
		}

		View::~View() TITANIUM_NOEXCEPT { TITANIUM_LOG_DEBUG("View:: dtor ", this); }

		void View::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View::add");

			// precondition
			auto native_view_ptr = view.GetPrivate<View>();
			TITANIUM_ASSERT(native_view_ptr.get());

			const auto view_count = children__.GetPropertyNames().GetCount();
			children__.SetProperty(static_cast<unsigned>(view_count), view);
		}

		void View::hide(JSObject& this_object) TITANIUM_NOEXCEPT { TITANIUM_LOG_DEBUG("View::hide"); }

		void View::show(JSObject& this_object) TITANIUM_NOEXCEPT { TITANIUM_LOG_DEBUG("View::show"); }

		JSArray View::get_children() const TITANIUM_NOEXCEPT { return children__; }

		JSValue View::get_backgroundColor() const TITANIUM_NOEXCEPT { return backgroundColor__; }

		void View::set_backgroundColor(const JSValue& backgroundColor) TITANIUM_NOEXCEPT
		{
			backgroundColor__ = backgroundColor;
		}

		JSValue View::get_top() const TITANIUM_NOEXCEPT { return top__; }

		void View::set_top(const JSValue& top) TITANIUM_NOEXCEPT { top__ = top; }

		JSValue View::get_left() const TITANIUM_NOEXCEPT { return left__; }

		void View::set_left(const JSValue& left) TITANIUM_NOEXCEPT { left__ = left; }

		JSValue View::get_bottom() const TITANIUM_NOEXCEPT { return bottom__; }

		void View::set_bottom(const JSValue& bottom) TITANIUM_NOEXCEPT { bottom__ = bottom; }

		JSValue View::get_right() const TITANIUM_NOEXCEPT { return right__; }

		void View::set_right(const JSValue& right) TITANIUM_NOEXCEPT { right__ = right; }

		JSObject View::get_center() const TITANIUM_NOEXCEPT { return center__; }

		void View::set_center(const JSObject& center) TITANIUM_NOEXCEPT { center__ = center; }

		JSValue View::get_width() const TITANIUM_NOEXCEPT { return width__; }

		void View::set_width(const JSValue& width) TITANIUM_NOEXCEPT { width__ = width; }

		JSValue View::get_height() const TITANIUM_NOEXCEPT { return height__; }

		void View::set_height(const JSValue& height) TITANIUM_NOEXCEPT { height__ = height; }

		JSValue View::get_layout() const TITANIUM_NOEXCEPT { return height__; }

		void View::set_layout(const JSValue& height) TITANIUM_NOEXCEPT { height__ = height; }

		NativeChildrenList_t View::get_native_children() const TITANIUM_NOEXCEPT
		{
			NativeChildrenList_t native_children_list;

			const auto child_count = children__.GetPropertyNames().GetCount();
			for (unsigned i = 0; i < child_count; ++i) {
				JSValue child_property = children__.GetProperty(i);

				// preconditions
				TITANIUM_ASSERT(child_property.IsObject());

				JSObject child = child_property;

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
			JSExport<View>::AddFunctionProperty("add", std::mem_fn(&View::addArgumentValidator));
			JSExport<View>::AddFunctionProperty("hide", std::mem_fn(&View::hideArgumentValidator));
			JSExport<View>::AddFunctionProperty("show", std::mem_fn(&View::showArgumentValidator));
			JSExport<View>::AddValueProperty("children", std::mem_fn(&View::get_children));
			JSExport<View>::AddValueProperty("backgroundColor", std::mem_fn(&View::get_backgroundColor),
			                                 std::mem_fn(&View::setBackgroundColorArgumentValidator));
			JSExport<View>::AddValueProperty("top", std::mem_fn(&View::get_top),
			                                 std::mem_fn(&View::setTopArgumentValidator));
			JSExport<View>::AddValueProperty("left", std::mem_fn(&View::get_left),
			                                 std::mem_fn(&View::setLeftArgumentValidator));
			JSExport<View>::AddValueProperty("bottom", std::mem_fn(&View::get_bottom),
			                                 std::mem_fn(&View::setBottomArgumentValidator));
			JSExport<View>::AddValueProperty("center", std::mem_fn(&View::get_center),
			                                 std::mem_fn(&View::setCenterArgumentValidator));
			JSExport<View>::AddValueProperty("right", std::mem_fn(&View::get_right),
			                                 std::mem_fn(&View::setRightArgumentValidator));
			JSExport<View>::AddValueProperty("width", std::mem_fn(&View::get_width),
			                                 std::mem_fn(&View::setWidthArgumentValidator));
			JSExport<View>::AddValueProperty("height", std::mem_fn(&View::get_height),
			                                 std::mem_fn(&View::setHeightArgumentValidator));
			JSExport<View>::AddValueProperty("layout", std::mem_fn(&View::get_layout),
			                                 std::mem_fn(&View::setLayoutArgumentValidator));
		}

		JSValue View::addArgumentValidator(const std::vector<JSValue>& arguments,
		                                   JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() >= 1);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			JSObject view = _0;
			add(view, this_object);
			return get_context().CreateUndefined();
		}

		JSValue View::hideArgumentValidator(const std::vector<JSValue>& arguments,
		                                    JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() == 0);
			hide(this_object);
			return get_context().CreateUndefined();
		}

		JSValue View::showArgumentValidator(const std::vector<JSValue>& arguments,
		                                    JSObject& this_object) TITANIUM_NOEXCEPT
		{
			// TODO: Validate these precondition checks (which could be
			// automaticaly generated) with the team.
			TITANIUM_ASSERT(arguments.size() == 0);
			show(this_object);
			return get_context().CreateUndefined();
		}

		bool View::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setBackgroundColorArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString());
			// bool result = false;
			// const std::string backgroundColor = static_cast<std::string>(argument);
			// Set the native view's background color to backgroundColor.
			// set_backgroundColor(argument);
			// result = true;
			// return result;

			return false;
		}

		bool View::setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setTopArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			// bool result = false;
			// const std::string top = static_cast<std::string>(argument);
			// Set the native view's position.
			// set_top(argument);
			// result = true;
			// return result;

			return false;
		}

		bool View::setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setLeftArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			// bool result = false;
			// const std::string left = static_cast<std::string>(argument);
			// Set the native view's position.
			// set_left(argument);
			// result = true;
			// return result;

			return false;
		}

		bool View::setBottomArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setBottomArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			// bool result = false;
			// const std::string left = static_cast<std::string>(argument);
			// Set the native view's position.
			// set_bottom(argument);
			// result = true;
			// return result;

			return false;
		}

		bool View::setRightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setRightArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			// bool result = false;
			// const std::string left = static_cast<std::string>(argument);
			// Set the native view's position.
			// set_right(argument);
			// result = true;
			// return result;

			return false;
		}

		bool View::setCenterArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setCenterArgumentValidator: Unimplemented");

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

		bool View::setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setWidthArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			// bool result = false;
			// const std::string width = static_cast<std::string>(argument);
			// Set the native view's position.
			// set_width(argument);
			// result = true;
			// return result;

			return false;
		}

		bool View::setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setHeightArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			// bool result = false;
			// const std::string height = static_cast<std::string>(argument);
			// Set the native view's position.
			// set_height(argument);
			// result = true;
			// return result;

			return false;
		}

		bool View::setLayoutArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("View::setLayoutArgumentValidator: Unimplemented");

			// Base classes must implement this method. This is the minimum
			// functionality that you should perform:
			//
			// TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			// bool result = false;
			// const std::string layout = static_cast<std::string>(argument);
			// Set the native view's layout type.
			// set_layout(argument);
			// result = true;
			// return result;

			return false;
		}
	}
}  // namespace Titanium { namespace UI {
