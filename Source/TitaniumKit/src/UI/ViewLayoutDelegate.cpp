/**
 * TitaniumKit ViewLayoutDelegate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ViewLayoutDelegate.hpp"
#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		ViewLayoutDelegate::ViewLayoutDelegate() TITANIUM_NOEXCEPT :
			opacity__(1.0),
			borderRadius__(0),
			borderWidth__(0),
			touchEnabled__(true),
			visible__(true),
			defaultWidth__(Titanium::UI::LAYOUT::SIZE),
			defaultHeight__(Titanium::UI::LAYOUT::SIZE)
		{

		}

		ViewLayoutDelegate::~ViewLayoutDelegate() 
		{

		}

		void ViewLayoutDelegate::add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			children__.push_back(view);
		}

		void ViewLayoutDelegate::animate(const JSObject& animation, JSObject& callback, const JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ViewLayoutDelegate::animate: Unimplemented");
		}

		void ViewLayoutDelegate::hide() TITANIUM_NOEXCEPT
		{
			set_visible(false);
		}

		void ViewLayoutDelegate::show() TITANIUM_NOEXCEPT
		{
			set_visible(true);
		}

		std::vector<std::shared_ptr<Titanium::UI::View>> ViewLayoutDelegate::get_children() const TITANIUM_NOEXCEPT
		{
			return children__;
		}

		std::string ViewLayoutDelegate::get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return backgroundColor__;
		}

		void ViewLayoutDelegate::set_backgroundColor(const std::string& backgroundColor) TITANIUM_NOEXCEPT
		{
			backgroundColor__ = backgroundColor;
		}

		std::string ViewLayoutDelegate::get_borderColor() const TITANIUM_NOEXCEPT
		{
			return borderColor__;
		}

		void ViewLayoutDelegate::set_borderColor(const std::string& borderColor) TITANIUM_NOEXCEPT
		{
			borderColor__ = borderColor;
		}

		uint32_t ViewLayoutDelegate::get_borderRadius() const TITANIUM_NOEXCEPT
		{
			return borderRadius__;
		}

		void ViewLayoutDelegate::set_borderRadius(const uint32_t& borderRadius) TITANIUM_NOEXCEPT
		{
			borderRadius__ = borderRadius;
		}

		uint32_t ViewLayoutDelegate::get_borderWidth() const TITANIUM_NOEXCEPT
		{
			return borderWidth__;
		}

		void ViewLayoutDelegate::set_borderWidth(const uint32_t& borderWidth) TITANIUM_NOEXCEPT
		{
			borderWidth__ = borderWidth;
		}

		double ViewLayoutDelegate::get_opacity() const TITANIUM_NOEXCEPT
		{
			return opacity__;
		}

		void ViewLayoutDelegate::set_opacity(const double& opacity) TITANIUM_NOEXCEPT
		{
			opacity__ = opacity;
		}

		Dimension ViewLayoutDelegate::get_rect() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ViewLayoutDelegate::get_rect: Unimplemented");
			Dimension dimension;
			return dimension;
		}

		Dimension ViewLayoutDelegate::get_size() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ViewLayoutDelegate::get_size: Unimplemented");
			Dimension dimension;
			return dimension;
		}

		bool ViewLayoutDelegate::get_visible() const TITANIUM_NOEXCEPT
		{
			return visible__;
		}

		void ViewLayoutDelegate::set_visible(const bool& visible) TITANIUM_NOEXCEPT
		{
			visible__ = visible;
		}

		std::string ViewLayoutDelegate::get_tintColor() const TITANIUM_NOEXCEPT
		{
			return tintColor__;
		}

		void ViewLayoutDelegate::set_tintColor(const std::string& tintColor) TITANIUM_NOEXCEPT
		{
			tintColor__ = tintColor;
		}

		bool ViewLayoutDelegate::get_touchEnabled() const TITANIUM_NOEXCEPT
		{
			return touchEnabled__;
		}

		void ViewLayoutDelegate::set_touchEnabled(const bool& touchEnabled) TITANIUM_NOEXCEPT
		{
			touchEnabled__ = touchEnabled;
		}

		std::string ViewLayoutDelegate::get_top() const TITANIUM_NOEXCEPT
		{
			return top__;
		}

		void ViewLayoutDelegate::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			top__ = top;
		}

		std::string ViewLayoutDelegate::get_left() const TITANIUM_NOEXCEPT
		{
			return left__;
		}

		void ViewLayoutDelegate::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			left__ = left;
		}

		std::string ViewLayoutDelegate::get_bottom() const TITANIUM_NOEXCEPT
		{
			return bottom__;
		}

		void ViewLayoutDelegate::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			bottom__ = bottom;
		}

		std::string ViewLayoutDelegate::get_right() const TITANIUM_NOEXCEPT
		{
			return right__;
		}

		void ViewLayoutDelegate::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			right__ = right;
		}

		Point ViewLayoutDelegate::get_center() const TITANIUM_NOEXCEPT
		{
			return center__;
		}

		void ViewLayoutDelegate::set_center(const Point& center) TITANIUM_NOEXCEPT
		{
			center__ = center;
		}

		std::string ViewLayoutDelegate::get_width() const TITANIUM_NOEXCEPT
		{
			return width__;
		}

		void ViewLayoutDelegate::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			width__ = width;
		}

		std::string ViewLayoutDelegate::get_minWidth() const TITANIUM_NOEXCEPT
		{
			return minWidth__;
		}

		void ViewLayoutDelegate::set_minWidth(const std::string& width) TITANIUM_NOEXCEPT
		{
			minWidth__ = width;
		}

		std::string ViewLayoutDelegate::get_height() const TITANIUM_NOEXCEPT
		{
			return height__;
		}

		void ViewLayoutDelegate::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			height__ = height;
		}

		std::string ViewLayoutDelegate::get_minHeight() const TITANIUM_NOEXCEPT
		{
			return minHeight__;
		}

		void ViewLayoutDelegate::set_minHeight(const std::string& height) TITANIUM_NOEXCEPT
		{
			minHeight__ = height;
		}

		std::string ViewLayoutDelegate::get_layout() const TITANIUM_NOEXCEPT
		{
			return layout__;
		}

		void ViewLayoutDelegate::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			layout__ = layout;
		}

		Titanium::UI::LAYOUT ViewLayoutDelegate::get_defaultWidth() const TITANIUM_NOEXCEPT
		{
			return defaultWidth__;
		}

		void ViewLayoutDelegate::set_defaultWidth(const Titanium::UI::LAYOUT& value) TITANIUM_NOEXCEPT
		{
			defaultWidth__ = value;
		}

		Titanium::UI::LAYOUT ViewLayoutDelegate::get_defaultHeight() const TITANIUM_NOEXCEPT
		{
			return defaultHeight__;
		}

		void ViewLayoutDelegate::set_defaultHeight(const Titanium::UI::LAYOUT& value) TITANIUM_NOEXCEPT
		{
			defaultHeight__ = value;
		}

		void ViewLayoutDelegate::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ViewLayoutDelegate::disableEvent: Unimplemented");
		}
		
		void ViewLayoutDelegate::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ViewLayoutDelegate::enableEvent: Unimplemented");
		}

		ViewLayoutEventDelegate::ViewLayoutEventDelegate(View* view) TITANIUM_NOEXCEPT :
			view__(view)	
		{

		}

		JSObject ViewLayoutEventDelegate::get_object() const TITANIUM_NOEXCEPT
		{
			return view__->get_object();
		}

		JSContext ViewLayoutEventDelegate::get_context() const TITANIUM_NOEXCEPT
		{
			return view__->get_context();
		}
		
		void ViewLayoutEventDelegate::fireEvent(const std::string& name, const JSObject& event_args)
		{
			try {
				view__->fireEvent(name, event_args);
			} catch (const HAL::detail::js_runtime_error& e) {
				std::ostringstream os;
				os << "Titanium_RedScreenOfDeath({"
					<< "  message:'Runtime Error during " << name << " event: "
					<< e.js_message() << "'"
				  << "});";
				get_context().JSEvaluateScript(os.str());
			}
		}
	} // namespace UI
}  // namespace Titanium
