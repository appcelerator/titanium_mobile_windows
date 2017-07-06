/**
 * TitaniumKit ViewLayoutDelegate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ViewLayoutDelegate.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/detail/TiLogger.hpp"

namespace Titanium
{
	namespace UI
	{
		ViewLayoutDelegate::ViewLayoutDelegate() TITANIUM_NOEXCEPT :
			opacity__(1.0),
			borderWidth__("0"),
			borderRadius__("0"),
			touchEnabled__(true),
			visible__(true),
			defaultWidth__(Titanium::UI::LAYOUT::SIZE),
			defaultHeight__(Titanium::UI::LAYOUT::SIZE),
			autoLayoutForHeight__(defaultHeight__),
			autoLayoutForWidth__(defaultWidth__)
		{
			TITANIUM_LOG_DEBUG("ViewLayoutDelegate::ctor ", this);
		}

		ViewLayoutDelegate::~ViewLayoutDelegate()
		{
			TITANIUM_LOG_DEBUG("ViewLayoutDelegate::dtor ", this, " with ", children__.size(), " children");
		}

		void ViewLayoutDelegate::add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			auto it = std::find(children__.begin(), children__.end(), view);
			if (it == children__.end()) {
				children__.push_back(view);
			}
		}

		void ViewLayoutDelegate::remove(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			auto it = std::find(children__.begin(), children__.end(), view);
			if (it != children__.end()) {
				children__.erase(it);
			}
		}

		void ViewLayoutDelegate::removeAllChildren() TITANIUM_NOEXCEPT
		{
			children__.clear();
		}

		void ViewLayoutDelegate::insertAt(const ViewInsertOrReplaceParams& params) TITANIUM_NOEXCEPT
		{
			children__.insert(children__.begin() + params.position, params.view);
		}

		void ViewLayoutDelegate::replaceAt(const ViewInsertOrReplaceParams& params) TITANIUM_NOEXCEPT
		{
			children__.erase(children__.begin() + params.position);
			children__.insert(children__.begin() + params.position, params.view);
		}

		void ViewLayoutDelegate::animate(const std::shared_ptr<Titanium::UI::Animation>& animation, JSObject& callback, const JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ViewLayoutDelegate::animate: Unimplemented");
		}

		std::shared_ptr<Titanium::Blob> ViewLayoutDelegate::toImage(JSObject& callback, const bool& honorScaleFactor, const JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ViewLayoutDelegate::toImage: Unimplemented");
			return nullptr;
		}

		void ViewLayoutDelegate::hide() TITANIUM_NOEXCEPT
		{
			set_visible(false);
		}

		void ViewLayoutDelegate::show() TITANIUM_NOEXCEPT
		{
			set_visible(true);
		}

		/*!
		  @property
		  @abstract anchorPoint
		  @discussion Coordinate of the view about which to pivot an animation.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, Point, anchorPoint);

		/*!
		  @property
		  @abstract animatedCenter
		  @discussion Current position of the view during an animation.
		*/
		TITANIUM_PROPERTY_READ(ViewLayoutDelegate, Point, animatedCenter);

		/*!
		  @property
		  @abstract backgroundDisabledColor
		  @discussion Disabled background color of the view, as a color name or hex triplet.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, backgroundDisabledColor);

		/*!
		  @property
		  @abstract backgroundDisabledImage
		  @discussion Disabled background image for the view, specified as a local file path or URL.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, backgroundDisabledImage);

		/*!
		  @property
		  @abstract backgroundFocusedColor
		  @discussion Focused background color of the view, as a color name or hex triplet.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, backgroundFocusedColor);

		/*!
		  @property
		  @abstract backgroundFocusedImage
		  @discussion Focused background image for the view, specified as a local file path or URL.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, backgroundFocusedImage);

		/*!
		  @property
		  @abstract backgroundGradient
		  @discussion A background gradient for the view.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, Gradient, backgroundGradient);

		/*!
		  @property
		  @abstract backgroundRepeat
		  @discussion Determines whether to tile a background across a view.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, bool, backgroundRepeat);

		/*!
		  @property
		  @abstract backgroundLeftCap
		  @discussion Size of the left end cap.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, double, backgroundLeftCap);

		/*!
		  @property
		  @abstract backgroundSelectedColor
		  @discussion Selected background color of the view, as a color name or hex triplet.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, backgroundSelectedColor);

		/*!
		  @property
		  @abstract backgroundSelectedImage
		  @discussion Selected background image url for the view, specified as a local file path or URL.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, backgroundSelectedImage);

		/*!
		  @property
		  @abstract backgroundTopCap
		  @discussion Size of the top end cap.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, double, backgroundTopCap);

		/*!
		  @property
		  @abstract overrideCurrentAnimation
		  @discussion When on, animate call overrides current animation if applicable.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, bool, overrideCurrentAnimation);

		/*!
		  @property
		  @abstract pullBackgroundColor
		  @discussion Background color of the wrapper view when this view is used as either <Titanium.UI.ListView.pullView> or <Titanium.UI.TableView.headerPullView>.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, pullBackgroundColor);

		/*!
		  @property
		  @abstract transform
		  @discussion Transformation matrix to apply to the view.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::shared_ptr<TwoDMatrix>, transform2D);
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::shared_ptr<ThreeDMatrix>, transform3D);

		/*!
		  @property
		  @abstract viewShadowRadius
		  @discussion Determines the blur radius used to create the shadow.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, double, viewShadowRadius);

		/*!
		  @property
		  @abstract viewShadowColor
		  @discussion Determines the color of the shadow.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, std::string, viewShadowColor);

		/*!
		  @property
		  @abstract viewShadowOffset
		  @discussion Determines the offset for the shadow of the view.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, Point, viewShadowOffset);

		/*!
		  @property
		  @abstract horizontalWrap
		  @discussion Determines whether the layout has wrapping behavior.
		*/
		TITANIUM_PROPERTY_READWRITE(ViewLayoutDelegate, bool, horizontalWrap);

		std::vector<std::shared_ptr<Titanium::UI::View>> ViewLayoutDelegate::get_children() const TITANIUM_NOEXCEPT
		{
			return children__;
		}

		std::string ViewLayoutDelegate::get_backgroundImage() const TITANIUM_NOEXCEPT
		{
			return backgroundImage__;
		}

		void ViewLayoutDelegate::set_backgroundImage(const std::string& backgroundImage) TITANIUM_NOEXCEPT
		{
			backgroundImage__ = backgroundImage;
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

		std::string ViewLayoutDelegate::get_borderRadius() const TITANIUM_NOEXCEPT
		{
			return borderRadius__;
		}

		void ViewLayoutDelegate::set_borderRadius(const std::string& borderRadius) TITANIUM_NOEXCEPT
		{
			borderRadius__ = borderRadius;
		}

		std::string ViewLayoutDelegate::get_borderWidth() const TITANIUM_NOEXCEPT
		{
			return borderWidth__;
		}

		void ViewLayoutDelegate::set_borderWidth(const std::string& borderWidth) TITANIUM_NOEXCEPT
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

		Titanium::UI::LAYOUT ViewLayoutDelegate::get_autoLayoutForWidth() const TITANIUM_NOEXCEPT
		{
			return autoLayoutForWidth__;
		}

		void ViewLayoutDelegate::set_autoLayoutForWidth(const Titanium::UI::LAYOUT& value) TITANIUM_NOEXCEPT
		{
			autoLayoutForWidth__ = value;
		}

		Titanium::UI::LAYOUT ViewLayoutDelegate::get_autoLayoutForHeight() const TITANIUM_NOEXCEPT
		{
			return autoLayoutForHeight__;
		}

		void ViewLayoutDelegate::set_autoLayoutForHeight(const Titanium::UI::LAYOUT& value) TITANIUM_NOEXCEPT
		{
			autoLayoutForHeight__ = value;
		}

		int32_t ViewLayoutDelegate::get_zIndex() const TITANIUM_NOEXCEPT
		{
			return zIndex__;
		}

		void ViewLayoutDelegate::set_zIndex(const int32_t& zIndex) TITANIUM_NOEXCEPT
		{
			zIndex__ = zIndex;
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

		void ViewLayoutEventDelegate::fireEvent(const std::string& name, const JSObject& e)
		{
			view__->fireEvent(name, e);
		}
	} // namespace UI
}  // namespace Titanium
