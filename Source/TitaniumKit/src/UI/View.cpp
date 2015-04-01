/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Point.hpp"

namespace Titanium
{
	namespace UI
	{
		View::View(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context)
		{
		}

		View::~View() TITANIUM_NOEXCEPT
		{
		}

		void View::postInitialize(JSObject& this_object)
		{
			Titanium::Module::postInitialize(this_object);
		}

		void View::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::Module::postCallAsConstructor(js_context, arguments);	
			setLayoutDelegate();
		}

		void View::animate(JSObject& animation, JSObject& callback) TITANIUM_NOEXCEPT
		{
			layoutDelegate__->animate(animation, callback, get_object());
		}

		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Module>::Class());
			// methods

			TITANIUM_MODULE_ADD_FUNCTION(View, add);
			TITANIUM_MODULE_ADD_FUNCTION(View, animate);
			TITANIUM_MODULE_ADD_FUNCTION(View, hide);
			TITANIUM_MODULE_ADD_FUNCTION(View, show);

			// properties
			TITANIUM_MODULE_ADD_PROPERTY(View, backgroundColor);
			TITANIUM_MODULE_ADD_PROPERTY(View, borderColor);
			TITANIUM_MODULE_ADD_PROPERTY(View, borderRadius);
			TITANIUM_MODULE_ADD_PROPERTY(View, borderWidth);
			TITANIUM_MODULE_ADD_PROPERTY(View, bottom);
			TITANIUM_MODULE_ADD_PROPERTY(View, center);
			TITANIUM_MODULE_ADD_PROPERTY_READONLY(View, children);
			TITANIUM_MODULE_ADD_PROPERTY(View, height);
			TITANIUM_MODULE_ADD_PROPERTY(View, layout);
			TITANIUM_MODULE_ADD_PROPERTY(View, left);
			TITANIUM_MODULE_ADD_PROPERTY(View, opacity);
			TITANIUM_MODULE_ADD_PROPERTY_READONLY(View, rect);
			TITANIUM_MODULE_ADD_PROPERTY(View, right);
			TITANIUM_MODULE_ADD_PROPERTY_READONLY(View, size);
			TITANIUM_MODULE_ADD_PROPERTY(View, tintColor);
			TITANIUM_MODULE_ADD_PROPERTY(View, top);
			TITANIUM_MODULE_ADD_PROPERTY(View, touchEnabled);
			TITANIUM_MODULE_ADD_PROPERTY(View, visible);
			TITANIUM_MODULE_ADD_PROPERTY(View, width);
		}

		TITANIUM_MODULE_FUNCTION(View, add)
		{
			ENSURE_OBJECT_AT_INDEX(view, 0);
			layoutDelegate__->add(view.GetPrivate<View>());
			return get_context().CreateUndefined();
		}

		TITANIUM_MODULE_FUNCTION(View, animate)
		{
			ENSURE_OBJECT_AT_INDEX(animation, 0);
			// TODO Convert the animation object into a Ti.UI.Animation if it isn't one already?

			ENSURE_OPTIONAL_OBJECT_AT_INDEX(callback, 1);
			TITANIUM_ASSERT(callback.IsFunction());

			animate(animation, callback);
			return get_context().CreateUndefined();
		}

		TITANIUM_MODULE_FUNCTION(View, hide)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			layoutDelegate__->hide();
			return get_context().CreateUndefined();
		}

		TITANIUM_MODULE_FUNCTION(View, show)
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			layoutDelegate__->show();
			return get_context().CreateUndefined();
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, backgroundColor)
		{
			return get_context().CreateString(layoutDelegate__->get_backgroundColor());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, backgroundColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, borderColor)
		{
			return get_context().CreateString(layoutDelegate__->get_borderColor());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, borderColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_borderColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, borderRadius)
		{
			return get_context().CreateNumber(layoutDelegate__->get_borderRadius());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, borderRadius)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			layoutDelegate__->set_borderRadius(static_cast<uint32_t>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, borderWidth)
		{
			return get_context().CreateNumber(layoutDelegate__->get_borderWidth());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, borderWidth)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			layoutDelegate__->set_borderWidth(static_cast<uint32_t>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, bottom)
		{
			return get_context().CreateString(layoutDelegate__->get_bottom());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, bottom)
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_bottom(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, center)
		{
			TITANIUM_ASSERT(argument.IsObject());
			layoutDelegate__->set_center(js_to_Point(static_cast<JSObject>(argument)));
			return true;
		}
		
		TITANIUM_MODULE_PROPERTY_GETTER(View, center)
		{
			return Point_to_js(get_context(), layoutDelegate__->get_center());
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, children)
		{
			std::vector<JSValue> js_children;
			const auto children = layoutDelegate__->get_children();
			for (auto child : children) {
				js_children.push_back(child->get_object());
			}
			return get_context().CreateArray(js_children);
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, height)
		{
			return get_context().CreateString(layoutDelegate__->get_height());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, height)
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_height(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, layout)
		{
			return get_context().CreateString(layoutDelegate__->get_layout());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, layout)
		{
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_layout(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, left)
		{
			return get_context().CreateString(layoutDelegate__->get_left());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, left)
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_left(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, opacity)
		{
			return get_context().CreateNumber(layoutDelegate__->get_opacity());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, opacity)
		{
			if (argument.IsNumber()) {
				layoutDelegate__->set_opacity(static_cast<double>(argument));
			}
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, rect)
		{
			return Titanium::UI::Dimension_to_js(get_context(), layoutDelegate__->get_rect());
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, right)
		{
			return get_context().CreateString(layoutDelegate__->get_right());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, right)
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_right(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, size)
		{
			return Titanium::UI::Dimension_to_js(get_context(), layoutDelegate__->get_size());
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, tintColor)
		{
			return get_context().CreateString(layoutDelegate__->get_tintColor());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, tintColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_tintColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, top)
		{
			return get_context().CreateString(layoutDelegate__->get_top());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, top)
		{
			// FIXME What does setting top to null mean? Because corporate directory does it...
			if (argument.IsNull()) {
				return false;
			}
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_top(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, touchEnabled)
		{
			return get_context().CreateBoolean(layoutDelegate__->get_touchEnabled());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, touchEnabled)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			layoutDelegate__->set_touchEnabled(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, visible)
		{
			return get_context().CreateBoolean(layoutDelegate__->get_visible());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, visible)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			layoutDelegate__->set_visible(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_MODULE_PROPERTY_GETTER(View, width)
		{
			return get_context().CreateString(layoutDelegate__->get_width());
		}

		TITANIUM_MODULE_PROPERTY_SETTER(View, width)
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_width(static_cast<std::string>(argument));
			return true;
		}

		void View::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			layoutDelegate__->disableEvent(event_name);
		}

		void View::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			layoutDelegate__->enableEvent(event_name);
		}

	} // namespace UI
}  // namespace Titanium
