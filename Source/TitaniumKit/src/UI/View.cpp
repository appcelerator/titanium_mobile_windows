/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Animation.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/UI/2DMatrix.hpp"
#include "Titanium/UI/3DMatrix.hpp"

#define CHECK_UI_DELEGATE_GETTER if (!layoutDelegate__) return get_context().CreateUndefined();
#define CHECK_UI_DELEGATE_SETTER if (!layoutDelegate__) return false;

namespace Titanium
{
	namespace UI
	{
		View::View(const JSContext& js_context, const std::string& apiName) TITANIUM_NOEXCEPT
		    : Module(js_context, apiName)
		{
			TITANIUM_LOG_DEBUG("View::ctor ", this);
		}

		View::~View() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View::dtor ", this);
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

		TITANIUM_PROPERTY_READWRITE(View, bool, accessibilityHidden)
		TITANIUM_PROPERTY_READWRITE(View, std::string, accessibilityHint)
		TITANIUM_PROPERTY_READWRITE(View, std::string, accessibilityLabel)
		TITANIUM_PROPERTY_READWRITE(View, std::string, accessibilityValue)
		TITANIUM_PROPERTY_READWRITE(View, std::uint32_t, clipMode)
		TITANIUM_PROPERTY_READWRITE(View, std::uint32_t, softKeyboardOnFocus)
		TITANIUM_PROPERTY_READWRITE(View, bool, focusable)
		TITANIUM_PROPERTY_READWRITE(View, bool, keepScreenOn)

		void View::set_parent(const std::shared_ptr<View>& parent) TITANIUM_NOEXCEPT
		{
			if (layoutDelegate__) {
				layoutDelegate__->set_parent(parent);
			}
		}

		std::shared_ptr<View> View::get_parent() const TITANIUM_NOEXCEPT
		{
			if (layoutDelegate__) {
				return layoutDelegate__->get_parent();
			}
			return nullptr;
		}

		std::shared_ptr<Titanium::Blob> View::toImage(JSObject& callback, const bool& honorScaleFactor) TITANIUM_NOEXCEPT
		{
			if (layoutDelegate__) {
				return layoutDelegate__->toImage(callback, honorScaleFactor, get_object());
			}
			return nullptr;
		}

		Point View::convertPointToView(Point point, std::shared_ptr<View> destinationView) TITANIUM_NOEXCEPT
		{
			Point viewPoint;
			if (destinationView != nullptr) {
				const auto viewRect = getViewLayoutDelegate()->get_rect();
				const auto destRect = destinationView->getViewLayoutDelegate()->get_rect();
				viewPoint.x = std::to_string(viewRect.x + get_Point_value(point.x) - destRect.x);
				viewPoint.y = std::to_string(viewRect.y + get_Point_value(point.y) - destRect.y);
			}
			return viewPoint;
		}

		void View::animate(const std::shared_ptr<Animation>& animation, JSObject& callback) TITANIUM_NOEXCEPT
		{
			if (layoutDelegate__) {
				layoutDelegate__->animate(animation, callback, get_object());
			}
		}

		void View::blur()
		{
			if (layoutDelegate__) {
				layoutDelegate__->blur();
			}
		}

		void View::focus()
		{
			if (layoutDelegate__) {
				layoutDelegate__->focus();
			}
		}

		void View::add(const JSObject& view) TITANIUM_NOEXCEPT
		{
			if (!layoutDelegate__) {
				return;
			}
			auto view_ptr = view.GetPrivate<View>();

			// For mixing Ti.Ui.View and native view.
			if (view_ptr == nullptr) {
				view_ptr = layoutDelegate__->rescueGetView(view);
			}

			TITANIUM_ASSERT(view_ptr != nullptr);

			const auto parent_view_ptr = this->get_object().GetPrivate<View>();

			// Compare parent, this indicates you're trying to add it before it's removed
			if (view_ptr->get_parent() == parent_view_ptr) {
				TITANIUM_LOG_WARN("View.add: This indicates this component is already added");
				return;
			}

			view_ptr->set_parent(parent_view_ptr);

			layoutDelegate__->add(view_ptr);
		}

		std::vector<std::shared_ptr<Titanium::UI::View>> View::get_children() const TITANIUM_NOEXCEPT
		{
			if (layoutDelegate__) {
				return layoutDelegate__->get_children();
			}
			return std::vector<std::shared_ptr<Titanium::UI::View>>();
		}


		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(View, accessibilityHidden);
			TITANIUM_ADD_PROPERTY(View, accessibilityHint);
			TITANIUM_ADD_PROPERTY(View, accessibilityLabel);
			TITANIUM_ADD_PROPERTY(View, accessibilityValue);
			TITANIUM_ADD_PROPERTY(View, anchorPoint);
			TITANIUM_ADD_PROPERTY_READONLY(View, animatedCenter);
			TITANIUM_ADD_PROPERTY(View, backgroundDisabledColor);
			TITANIUM_ADD_PROPERTY(View, backgroundDisabledImage);
			TITANIUM_ADD_PROPERTY(View, backgroundFocusedColor);
			TITANIUM_ADD_PROPERTY(View, backgroundFocusedImage);
			TITANIUM_ADD_PROPERTY(View, backgroundGradient);
			TITANIUM_ADD_PROPERTY(View, backgroundImage);
			TITANIUM_ADD_PROPERTY(View, backgroundRepeat);
			TITANIUM_ADD_PROPERTY(View, backgroundLeftCap);
			TITANIUM_ADD_PROPERTY(View, backgroundSelectedColor);
			TITANIUM_ADD_PROPERTY(View, backgroundSelectedImage);
			TITANIUM_ADD_PROPERTY(View, backgroundTopCap);
			TITANIUM_ADD_PROPERTY(View, borderColor);
			TITANIUM_ADD_PROPERTY(View, borderRadius);
			TITANIUM_ADD_PROPERTY(View, borderWidth);
			TITANIUM_ADD_PROPERTY(View, clipMode);
			TITANIUM_ADD_PROPERTY(View, focusable);
			TITANIUM_ADD_PROPERTY(View, opacity);
			TITANIUM_ADD_PROPERTY(View, overrideCurrentAnimation);
			TITANIUM_ADD_PROPERTY(View, pullBackgroundColor);
			TITANIUM_ADD_PROPERTY_READONLY(View, rect);
			TITANIUM_ADD_PROPERTY_READONLY(View, size);
			TITANIUM_ADD_PROPERTY(View, softKeyboardOnFocus);
			TITANIUM_ADD_PROPERTY(View, tintColor);
			TITANIUM_ADD_PROPERTY(View, touchEnabled);
			TITANIUM_ADD_PROPERTY(View, transform);
			TITANIUM_ADD_PROPERTY(View, viewShadowRadius);
			TITANIUM_ADD_PROPERTY(View, viewShadowColor);
			TITANIUM_ADD_PROPERTY(View, viewShadowOffset);
			TITANIUM_ADD_PROPERTY(View, visible);
			TITANIUM_ADD_PROPERTY(View, horizontalWrap);
			TITANIUM_ADD_PROPERTY(View, zIndex);
			TITANIUM_ADD_PROPERTY(View, keepScreenOn);
			TITANIUM_ADD_PROPERTY(View, backgroundColor);
			TITANIUM_ADD_PROPERTY(View, top);
			TITANIUM_ADD_PROPERTY(View, left);
			TITANIUM_ADD_PROPERTY(View, bottom);
			TITANIUM_ADD_PROPERTY(View, center);
			TITANIUM_ADD_PROPERTY(View, right);
			TITANIUM_ADD_PROPERTY(View, width);
			TITANIUM_ADD_PROPERTY(View, height);
			TITANIUM_ADD_PROPERTY(View, layout);
			TITANIUM_ADD_PROPERTY_READONLY_NOENUMERABLE(View, children);
			TITANIUM_ADD_PROPERTY_NOENUMERABLE(View, parent);

			TITANIUM_ADD_FUNCTION(View, animate);
			TITANIUM_ADD_FUNCTION(View, remove);
			TITANIUM_ADD_FUNCTION(View, removeAllChildren);
			TITANIUM_ADD_FUNCTION(View, toImage);
			TITANIUM_ADD_FUNCTION(View, convertPointToView);
			TITANIUM_ADD_FUNCTION(View, add);
			TITANIUM_ADD_FUNCTION(View, hide);
			TITANIUM_ADD_FUNCTION(View, show);
			TITANIUM_ADD_FUNCTION(View, getAccessibilityHidden);
			TITANIUM_ADD_FUNCTION(View, setAccessibilityHidden);
			TITANIUM_ADD_FUNCTION(View, getAccessibilityHint);
			TITANIUM_ADD_FUNCTION(View, setAccessibilityHint);
			TITANIUM_ADD_FUNCTION(View, getAccessibilityLabel);
			TITANIUM_ADD_FUNCTION(View, setAccessibilityLabel);
			TITANIUM_ADD_FUNCTION(View, getAccessibilityValue);
			TITANIUM_ADD_FUNCTION(View, setAccessibilityValue);
			TITANIUM_ADD_FUNCTION(View, getAnchorPoint);
			TITANIUM_ADD_FUNCTION(View, setAnchorPoint);
			TITANIUM_ADD_FUNCTION(View, getAnimatedCenter);
			TITANIUM_ADD_FUNCTION(View, getBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(View, setBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(View, getBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(View, setBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(View, getBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(View, setBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(View, getBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(View, setBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(View, getBackgroundGradient);
			TITANIUM_ADD_FUNCTION(View, setBackgroundGradient);
			TITANIUM_ADD_FUNCTION(View, getBackgroundImage);
			TITANIUM_ADD_FUNCTION(View, setBackgroundImage);
			TITANIUM_ADD_FUNCTION(View, getBackgroundRepeat);
			TITANIUM_ADD_FUNCTION(View, setBackgroundRepeat);
			TITANIUM_ADD_FUNCTION(View, getBackgroundLeftCap);
			TITANIUM_ADD_FUNCTION(View, setBackgroundLeftCap);
			TITANIUM_ADD_FUNCTION(View, getBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(View, setBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(View, getBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(View, setBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(View, getBackgroundTopCap);
			TITANIUM_ADD_FUNCTION(View, setBackgroundTopCap);
			TITANIUM_ADD_FUNCTION(View, getBorderColor);
			TITANIUM_ADD_FUNCTION(View, setBorderColor);
			TITANIUM_ADD_FUNCTION(View, getBorderRadius);
			TITANIUM_ADD_FUNCTION(View, setBorderRadius);
			TITANIUM_ADD_FUNCTION(View, getBorderWidth);
			TITANIUM_ADD_FUNCTION(View, setBorderWidth);
			TITANIUM_ADD_FUNCTION(View, getClipMode);
			TITANIUM_ADD_FUNCTION(View, setClipMode);
			TITANIUM_ADD_FUNCTION(View, getFocusable);
			TITANIUM_ADD_FUNCTION(View, setFocusable);
			TITANIUM_ADD_FUNCTION(View, getOpacity);
			TITANIUM_ADD_FUNCTION(View, setOpacity);
			TITANIUM_ADD_FUNCTION(View, getOverrideCurrentAnimation);
			TITANIUM_ADD_FUNCTION(View, setOverrideCurrentAnimation);
			TITANIUM_ADD_FUNCTION(View, getPullBackgroundColor);
			TITANIUM_ADD_FUNCTION(View, setPullBackgroundColor);
			TITANIUM_ADD_FUNCTION(View, getRect);
			TITANIUM_ADD_FUNCTION(View, getSize);
			TITANIUM_ADD_FUNCTION(View, getSoftKeyboardOnFocus);
			TITANIUM_ADD_FUNCTION(View, setSoftKeyboardOnFocus);
			TITANIUM_ADD_FUNCTION(View, getTintColor);
			TITANIUM_ADD_FUNCTION(View, setTintColor);
			TITANIUM_ADD_FUNCTION(View, getTouchEnabled);
			TITANIUM_ADD_FUNCTION(View, setTouchEnabled);
			TITANIUM_ADD_FUNCTION(View, getTransform);
			TITANIUM_ADD_FUNCTION(View, setTransform);
			TITANIUM_ADD_FUNCTION(View, getViewShadowRadius);
			TITANIUM_ADD_FUNCTION(View, setViewShadowRadius);
			TITANIUM_ADD_FUNCTION(View, getViewShadowColor);
			TITANIUM_ADD_FUNCTION(View, setViewShadowColor);
			TITANIUM_ADD_FUNCTION(View, getViewShadowOffset);
			TITANIUM_ADD_FUNCTION(View, setViewShadowOffset);
			TITANIUM_ADD_FUNCTION(View, getViewById);
			TITANIUM_ADD_FUNCTION(View, getVisible);
			TITANIUM_ADD_FUNCTION(View, setVisible);
			TITANIUM_ADD_FUNCTION(View, getHorizontalWrap);
			TITANIUM_ADD_FUNCTION(View, setHorizontalWrap);
			TITANIUM_ADD_FUNCTION(View, getZIndex);
			TITANIUM_ADD_FUNCTION(View, setZIndex);
			TITANIUM_ADD_FUNCTION(View, getKeepScreenOn);
			TITANIUM_ADD_FUNCTION(View, setKeepScreenOn);
			TITANIUM_ADD_FUNCTION(View, getChildren);
			TITANIUM_ADD_FUNCTION(View, getBackgroundColor);
			TITANIUM_ADD_FUNCTION(View, setBackgroundColor);
			TITANIUM_ADD_FUNCTION(View, getTop);
			TITANIUM_ADD_FUNCTION(View, setTop);
			TITANIUM_ADD_FUNCTION(View, getLeft);
			TITANIUM_ADD_FUNCTION(View, setLeft);
			TITANIUM_ADD_FUNCTION(View, getBottom);
			TITANIUM_ADD_FUNCTION(View, setBottom);
			TITANIUM_ADD_FUNCTION(View, getCenter);
			TITANIUM_ADD_FUNCTION(View, setCenter);
			TITANIUM_ADD_FUNCTION(View, getRight);
			TITANIUM_ADD_FUNCTION(View, setRight);
			TITANIUM_ADD_FUNCTION(View, getWidth);
			TITANIUM_ADD_FUNCTION(View, setWidth);
			TITANIUM_ADD_FUNCTION(View, getHeight);
			TITANIUM_ADD_FUNCTION(View, setHeight);
			TITANIUM_ADD_FUNCTION(View, getLayout);
			TITANIUM_ADD_FUNCTION(View, setLayout);
			TITANIUM_ADD_FUNCTION(View, getParent);
			TITANIUM_ADD_FUNCTION(View, setParent);

			TITANIUM_ADD_FUNCTION(View, insertAt);
			TITANIUM_ADD_FUNCTION(View, replaceAt);

		}

		TITANIUM_PROPERTY_GETTER(View, parent)
		{
			const auto parent = get_parent();
			if (parent) {
				return parent->get_object();
			}
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_SETTER(View, parent)
		{
			if (argument.IsObject()) {
				set_parent(static_cast<JSObject>(argument).GetPrivate<View>());
			} else {
				set_parent(nullptr);
			}
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, anchorPoint)
		{
			CHECK_UI_DELEGATE_GETTER
			return Point_to_js(get_context(), layoutDelegate__->get_anchorPoint());
		}

		TITANIUM_PROPERTY_SETTER(View, anchorPoint)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsObject());
			layoutDelegate__->set_anchorPoint(js_to_Point(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, animatedCenter)
		{
			CHECK_UI_DELEGATE_GETTER
			return Point_to_js(get_context(), layoutDelegate__->get_animatedCenter());
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundDisabledColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundDisabledColor());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundDisabledColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundDisabledColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundDisabledImage)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundDisabledImage());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundDisabledImage)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundDisabledImage(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundFocusedColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundFocusedColor());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundFocusedColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundFocusedColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundFocusedImage)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundFocusedImage());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundFocusedImage)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundFocusedImage(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundGradient)
		{
			CHECK_UI_DELEGATE_GETTER
			return Gradient_to_js(get_context(), layoutDelegate__->get_backgroundGradient());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundGradient)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsObject());
			layoutDelegate__->set_backgroundGradient(js_to_Gradient(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundRepeat)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateBoolean(layoutDelegate__->get_backgroundRepeat());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundRepeat)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsBoolean());
			layoutDelegate__->set_backgroundRepeat(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundLeftCap)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateNumber(layoutDelegate__->get_backgroundLeftCap());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundLeftCap)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsNumber());
			layoutDelegate__->set_backgroundLeftCap(static_cast<std::uint32_t>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundSelectedColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundSelectedColor());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundSelectedColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundSelectedColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundSelectedImage)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundSelectedImage());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundSelectedImage)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundSelectedImage(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundTopCap)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateNumber(layoutDelegate__->get_backgroundTopCap());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundTopCap)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsNumber());
			layoutDelegate__->set_backgroundTopCap(static_cast<std::uint32_t>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, overrideCurrentAnimation)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateBoolean(layoutDelegate__->get_overrideCurrentAnimation());
		}

		TITANIUM_PROPERTY_SETTER(View, overrideCurrentAnimation)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsBoolean());
			layoutDelegate__->set_overrideCurrentAnimation(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, pullBackgroundColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_pullBackgroundColor());
		}

		TITANIUM_PROPERTY_SETTER(View, pullBackgroundColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_pullBackgroundColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, transform)
		{
			CHECK_UI_DELEGATE_GETTER

			const auto t2d = layoutDelegate__->get_transform2D();
			if (t2d) {
				return t2d->get_object();
			}
			const auto t3d = layoutDelegate__->get_transform3D();
			if (t3d) {
				return t3d->get_object();
			}
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_SETTER(View, transform)
		{
			CHECK_UI_DELEGATE_SETTER;
			if (argument.IsObject()) {
				const auto object = static_cast<JSObject>(argument);
				const auto matrix2d = object.GetPrivate<TwoDMatrix>();
				const auto matrix3d = object.GetPrivate<ThreeDMatrix>();
				if (matrix2d) {
					layoutDelegate__->set_transform2D(matrix2d);
				} else if (matrix3d) {
					layoutDelegate__->set_transform3D(matrix3d);
				}
			} else {
				layoutDelegate__->set_transform3D(nullptr);
			}
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, viewShadowRadius)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateNumber(layoutDelegate__->get_viewShadowRadius());
		}

		TITANIUM_PROPERTY_SETTER(View, viewShadowRadius)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsNumber());
			layoutDelegate__->set_viewShadowRadius(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, viewShadowColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_viewShadowColor());
		}

		TITANIUM_PROPERTY_SETTER(View, viewShadowColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_viewShadowColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, viewShadowOffset)
		{
			CHECK_UI_DELEGATE_GETTER
			return Point_to_js(get_context(), layoutDelegate__->get_viewShadowOffset());
		}

		TITANIUM_PROPERTY_SETTER(View, viewShadowOffset)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsObject());
			layoutDelegate__->set_viewShadowOffset(js_to_Point(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, horizontalWrap)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateBoolean(layoutDelegate__->get_horizontalWrap());
		}

		TITANIUM_PROPERTY_SETTER(View, horizontalWrap)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsBoolean());
			layoutDelegate__->set_horizontalWrap(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION(View, removeAllChildren)
		{
			CHECK_UI_DELEGATE_GETTER
			layoutDelegate__->removeAllChildren();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(View, add)
		{
			ENSURE_OBJECT_AT_INDEX(view, 0);

			// Support single view, or an array of views
			std::vector<JSObject> views;
			if (view.IsArray()) {
				auto js_array = static_cast<std::vector<JSValue>>(static_cast<JSArray>(view));
				for (auto v : js_array) {
					views.push_back(static_cast<JSObject>(v));
				}
			} else {
				views.push_back(view);
			}

			for (auto v : views) {
				add(v);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(View, animate)
		{
			ENSURE_OBJECT_AT_INDEX(object, 0);
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(callback, 1);

			// Convert the animation object into a Ti.UI.Animation if it isn't one already
			auto animation = object.GetPrivate<Titanium::UI::Animation>();
			if (animation == nullptr) {
				// It's not already backed by a native class, we need to generate one from it!
				JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(Titanium_property.IsObject());
				JSObject Titanium = static_cast<JSObject>(Titanium_property);

				JSValue UI_property = Titanium.GetProperty("UI");
				TITANIUM_ASSERT(UI_property.IsObject());
				JSObject UI = static_cast<JSObject>(UI_property);

				JSValue Animation_property = UI.GetProperty("Animation");
				TITANIUM_ASSERT(Animation_property.IsObject());
				JSObject Animation_Class = static_cast<JSObject>(Animation_property);

				auto instance = Animation_Class.CallAsConstructor();
				Titanium::Module::applyProperties(object, instance);
				animation = instance.GetPrivate<Titanium::UI::Animation>();
			}

			animate(animation, callback);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(View, hide)
		{
			CHECK_UI_DELEGATE_GETTER
			TITANIUM_ASSERT(arguments.size() == 0);
			layoutDelegate__->hide();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(View, remove)
		{
			CHECK_UI_DELEGATE_GETTER
			ENSURE_OBJECT_AT_INDEX(view, 0);
			const auto view_ptr = view.GetPrivate<View>();
			view_ptr->set_parent(nullptr);
			layoutDelegate__->remove(view_ptr);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(View, show)
		{
			CHECK_UI_DELEGATE_GETTER
			TITANIUM_ASSERT(arguments.size() == 0);
			layoutDelegate__->show();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(View, insertAt)
		{
			CHECK_UI_DELEGATE_GETTER
			ENSURE_OBJECT_AT_INDEX(params, 0);

			const auto viewInsertParams = js_to_ViewInsertOrReplaceParams(params);
			const auto view_ptr = viewInsertParams.view;

			const auto parent_view_ptr = this->get_object().GetPrivate<View>();

			// Compare parent, this indicates you're trying to add it before it's removed
			if (view_ptr->get_parent() == parent_view_ptr) {
				TITANIUM_LOG_WARN("View.add: This indicates this component is already added");
				return get_context().CreateUndefined();
			}

			view_ptr->set_parent(this->get_object().GetPrivate<View>());

			layoutDelegate__->insertAt(viewInsertParams);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(View, replaceAt)
		{
			CHECK_UI_DELEGATE_GETTER
			ENSURE_OBJECT_AT_INDEX(params, 0);

			const auto viewInsertParams = js_to_ViewInsertOrReplaceParams(params);
			const auto view_ptr = viewInsertParams.view;
			view_ptr->set_parent(this->get_object().GetPrivate<View>());

			layoutDelegate__->replaceAt(viewInsertParams);
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundImage)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundImage());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundImage)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundImage(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, backgroundColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_backgroundColor());
		}

		TITANIUM_PROPERTY_SETTER(View, backgroundColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_backgroundColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, borderColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_borderColor());
		}

		TITANIUM_PROPERTY_SETTER(View, borderColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_borderColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, borderRadius)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_borderRadius());
		}

		TITANIUM_PROPERTY_SETTER(View, borderRadius)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_borderRadius(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, borderWidth)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_borderWidth());
		}

		TITANIUM_PROPERTY_SETTER(View, borderWidth)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_borderWidth(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, bottom)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_bottom());
		}

		TITANIUM_PROPERTY_SETTER(View, bottom)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_bottom(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_SETTER(View, center)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsObject());
			layoutDelegate__->set_center(js_to_Point(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, center)
		{
			CHECK_UI_DELEGATE_GETTER
			return Point_to_js(get_context(), layoutDelegate__->get_center());
		}

		TITANIUM_PROPERTY_GETTER(View, children)
		{
			CHECK_UI_DELEGATE_GETTER
			std::vector<JSValue> js_children;
			const auto children = get_children();
			for (auto child : children) {
				js_children.push_back(child->get_object());
			}
			return get_context().CreateArray(js_children);
		}

		TITANIUM_PROPERTY_GETTER(View, height)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_height());
		}

		TITANIUM_PROPERTY_SETTER(View, height)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_height(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, layout)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_layout());
		}

		TITANIUM_PROPERTY_SETTER(View, layout)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_layout(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, left)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_left());
		}

		TITANIUM_PROPERTY_SETTER(View, left)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_left(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, opacity)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateNumber(layoutDelegate__->get_opacity());
		}

		TITANIUM_PROPERTY_SETTER(View, opacity)
		{
			CHECK_UI_DELEGATE_SETTER;
			if (argument.IsNumber()) {
				layoutDelegate__->set_opacity(static_cast<double>(argument));
			}
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, rect)
		{
			CHECK_UI_DELEGATE_GETTER
			return Titanium::UI::Dimension_to_js(get_context(), layoutDelegate__->get_rect());
		}

		TITANIUM_PROPERTY_GETTER(View, right)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_right());
		}

		TITANIUM_PROPERTY_SETTER(View, right)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_right(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, size)
		{
			CHECK_UI_DELEGATE_GETTER
			return Titanium::UI::Dimension_to_js(get_context(), layoutDelegate__->get_size());
		}

		TITANIUM_PROPERTY_GETTER(View, tintColor)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_tintColor());
		}

		TITANIUM_PROPERTY_SETTER(View, tintColor)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString());
			layoutDelegate__->set_tintColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, top)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_top());
		}

		TITANIUM_PROPERTY_SETTER(View, top)
		{
			CHECK_UI_DELEGATE_SETTER;
			// FIXME What does setting top to null mean? Because corporate directory does it...
			if (argument.IsNull()) {
				return false;
			}
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_top(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, touchEnabled)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateBoolean(layoutDelegate__->get_touchEnabled());
		}

		TITANIUM_PROPERTY_SETTER(View, touchEnabled)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsBoolean());
			layoutDelegate__->set_touchEnabled(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, visible)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateBoolean(layoutDelegate__->get_visible());
		}

		TITANIUM_PROPERTY_SETTER(View, visible)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsBoolean());
			layoutDelegate__->set_visible(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, width)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateString(layoutDelegate__->get_width());
		}

		TITANIUM_PROPERTY_SETTER(View, width)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_width(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(View, zIndex)
		{
			CHECK_UI_DELEGATE_GETTER
			return get_context().CreateNumber(layoutDelegate__->get_zIndex());
		}

		TITANIUM_PROPERTY_SETTER(View, zIndex)
		{
			CHECK_UI_DELEGATE_SETTER;
			TITANIUM_ASSERT(argument.IsNumber());
			layoutDelegate__->set_zIndex(static_cast<std::int32_t>(argument));
			return true;
		}

		void View::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			if (layoutDelegate__) {
				layoutDelegate__->disableEvent(event_name);
			}
		}

		void View::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			if (layoutDelegate__) {
				layoutDelegate__->enableEvent(event_name);
			}
		}

		TITANIUM_FUNCTION(View, toImage)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(callback, 0);
			ENSURE_OPTIONAL_BOOL_AT_INDEX(honorScaleFactor, 1, true);
			const auto image = toImage(callback, honorScaleFactor);
			if (image) {
				return image->get_object();
			} else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_FUNCTION(View, convertPointToView)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_OBJECT_AT_INDEX(point, 0);
			ENSURE_OBJECT_AT_INDEX(destinationView, 1);
			return Point_to_js(get_context(), convertPointToView(js_to_Point(point), destinationView.GetPrivate<View>()));
		}

		TITANIUM_FUNCTION(View, getViewById)
		{
			ENSURE_STRING_AT_INDEX(id, 0);
			const auto children = get_children();
			for (const auto child : children) {
				if (child->get_children().size() > 0) {
					const auto parentChild = child->js_getViewById(arguments, this_object);
					if (!parentChild.IsNull()) {
						return parentChild;
					}
				}
				const auto js_child = child->get_object();
				const auto childId  = js_child.GetProperty("id");
				if (childId.IsString() && static_cast<std::string>(childId) == id) {
					return js_child;
				}
			}
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_GETTER_BOOL(View, accessibilityHidden)
		TITANIUM_PROPERTY_SETTER_BOOL(View, accessibilityHidden)
		TITANIUM_PROPERTY_GETTER_STRING(View, accessibilityHint)
		TITANIUM_PROPERTY_SETTER_STRING(View, accessibilityHint)
		TITANIUM_PROPERTY_GETTER_STRING(View, accessibilityLabel)
		TITANIUM_PROPERTY_SETTER_STRING(View, accessibilityLabel)
		TITANIUM_PROPERTY_GETTER_STRING(View, accessibilityValue)
		TITANIUM_PROPERTY_SETTER_STRING(View, accessibilityValue)
		TITANIUM_PROPERTY_GETTER_UINT(View, clipMode)
		TITANIUM_PROPERTY_SETTER_UINT(View, clipMode)
		TITANIUM_PROPERTY_GETTER_BOOL(View, focusable)
		TITANIUM_PROPERTY_SETTER_BOOL(View, focusable)
		TITANIUM_PROPERTY_GETTER_UINT(View, softKeyboardOnFocus)
		TITANIUM_PROPERTY_SETTER_UINT(View, softKeyboardOnFocus)
		TITANIUM_PROPERTY_GETTER_BOOL(View, keepScreenOn)
		TITANIUM_PROPERTY_SETTER_BOOL(View, keepScreenOn)

		TITANIUM_FUNCTION_AS_GETTER(View, getAccessibilityHidden, accessibilityHidden)
		TITANIUM_FUNCTION_AS_SETTER(View, setAccessibilityHidden, accessibilityHidden)
		TITANIUM_FUNCTION_AS_GETTER(View, getAccessibilityHint, accessibilityHint)
		TITANIUM_FUNCTION_AS_SETTER(View, setAccessibilityHint, accessibilityHint)
		TITANIUM_FUNCTION_AS_GETTER(View, getAccessibilityLabel, accessibilityLabel)
		TITANIUM_FUNCTION_AS_SETTER(View, setAccessibilityLabel, accessibilityLabel)
		TITANIUM_FUNCTION_AS_GETTER(View, getAccessibilityValue, accessibilityValue)
		TITANIUM_FUNCTION_AS_SETTER(View, setAccessibilityValue, accessibilityValue)
		TITANIUM_FUNCTION_AS_GETTER(View, getAnchorPoint, anchorPoint)
		TITANIUM_FUNCTION_AS_SETTER(View, setAnchorPoint, anchorPoint)
		TITANIUM_FUNCTION_AS_GETTER(View, getAnimatedCenter, animatedCenter)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundDisabledColor, backgroundDisabledColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundDisabledColor, backgroundDisabledColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundDisabledImage, backgroundDisabledImage)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundDisabledImage, backgroundDisabledImage)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundFocusedColor, backgroundFocusedColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundFocusedColor, backgroundFocusedColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundFocusedImage, backgroundFocusedImage)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundFocusedImage, backgroundFocusedImage)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundGradient, backgroundGradient)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundGradient, backgroundGradient)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundImage, backgroundImage)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundImage, backgroundImage)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundRepeat, backgroundRepeat)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundRepeat, backgroundRepeat)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundLeftCap, backgroundLeftCap)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundLeftCap, backgroundLeftCap)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundSelectedColor, backgroundSelectedColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundSelectedColor, backgroundSelectedColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundSelectedImage, backgroundSelectedImage)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundSelectedImage, backgroundSelectedImage)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundTopCap, backgroundTopCap)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundTopCap, backgroundTopCap)
		TITANIUM_FUNCTION_AS_GETTER(View, getBorderColor, borderColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setBorderColor, borderColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getBorderRadius, borderRadius)
		TITANIUM_FUNCTION_AS_SETTER(View, setBorderRadius, borderRadius)
		TITANIUM_FUNCTION_AS_GETTER(View, getBorderWidth, borderWidth)
		TITANIUM_FUNCTION_AS_SETTER(View, setBorderWidth, borderWidth)
		TITANIUM_FUNCTION_AS_GETTER(View, getClipMode, clipMode)
		TITANIUM_FUNCTION_AS_SETTER(View, setClipMode, clipMode)
		TITANIUM_FUNCTION_AS_GETTER(View, getFocusable, focusable)
		TITANIUM_FUNCTION_AS_SETTER(View, setFocusable, focusable)
		TITANIUM_FUNCTION_AS_GETTER(View, getOpacity, opacity)
		TITANIUM_FUNCTION_AS_SETTER(View, setOpacity, opacity)
		TITANIUM_FUNCTION_AS_GETTER(View, getOverrideCurrentAnimation, overrideCurrentAnimation)
		TITANIUM_FUNCTION_AS_SETTER(View, setOverrideCurrentAnimation, overrideCurrentAnimation)
		TITANIUM_FUNCTION_AS_GETTER(View, getPullBackgroundColor, pullBackgroundColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setPullBackgroundColor, pullBackgroundColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getRect, rect)
		TITANIUM_FUNCTION_AS_GETTER(View, getSize, size)
		TITANIUM_FUNCTION_AS_GETTER(View, getSoftKeyboardOnFocus, softKeyboardOnFocus)
		TITANIUM_FUNCTION_AS_SETTER(View, setSoftKeyboardOnFocus, softKeyboardOnFocus)
		TITANIUM_FUNCTION_AS_GETTER(View, getTintColor, tintColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setTintColor, tintColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getTouchEnabled, touchEnabled)
		TITANIUM_FUNCTION_AS_SETTER(View, setTouchEnabled, touchEnabled)
		TITANIUM_FUNCTION_AS_GETTER(View, getTransform, transform)
		TITANIUM_FUNCTION_AS_SETTER(View, setTransform, transform)
		TITANIUM_FUNCTION_AS_GETTER(View, getViewShadowRadius, viewShadowRadius)
		TITANIUM_FUNCTION_AS_SETTER(View, setViewShadowRadius, viewShadowRadius)
		TITANIUM_FUNCTION_AS_GETTER(View, getViewShadowColor, viewShadowColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setViewShadowColor, viewShadowColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getViewShadowOffset, viewShadowOffset)
		TITANIUM_FUNCTION_AS_SETTER(View, setViewShadowOffset, viewShadowOffset)
		TITANIUM_FUNCTION_AS_GETTER(View, getVisible, visible)
		TITANIUM_FUNCTION_AS_SETTER(View, setVisible, visible)
		TITANIUM_FUNCTION_AS_GETTER(View, getHorizontalWrap, horizontalWrap)
		TITANIUM_FUNCTION_AS_SETTER(View, setHorizontalWrap, horizontalWrap)
		TITANIUM_FUNCTION_AS_GETTER(View, getZIndex, zIndex)
		TITANIUM_FUNCTION_AS_SETTER(View, setZIndex, zIndex)
		TITANIUM_FUNCTION_AS_GETTER(View, getKeepScreenOn, keepScreenOn)
		TITANIUM_FUNCTION_AS_SETTER(View, setKeepScreenOn, keepScreenOn)
		TITANIUM_FUNCTION_AS_GETTER(View, getChildren, children)
		TITANIUM_FUNCTION_AS_GETTER(View, getBackgroundColor, backgroundColor)
		TITANIUM_FUNCTION_AS_SETTER(View, setBackgroundColor, backgroundColor)
		TITANIUM_FUNCTION_AS_GETTER(View, getTop, top)
		TITANIUM_FUNCTION_AS_SETTER(View, setTop, top)
		TITANIUM_FUNCTION_AS_GETTER(View, getLeft, left)
		TITANIUM_FUNCTION_AS_SETTER(View, setLeft, left)
		TITANIUM_FUNCTION_AS_GETTER(View, getBottom, bottom)
		TITANIUM_FUNCTION_AS_SETTER(View, setBottom, bottom)
		TITANIUM_FUNCTION_AS_GETTER(View, getCenter, center)
		TITANIUM_FUNCTION_AS_SETTER(View, setCenter, center)
		TITANIUM_FUNCTION_AS_GETTER(View, getRight, right)
		TITANIUM_FUNCTION_AS_SETTER(View, setRight, right)
		TITANIUM_FUNCTION_AS_GETTER(View, getWidth, width)
		TITANIUM_FUNCTION_AS_SETTER(View, setWidth, width)
		TITANIUM_FUNCTION_AS_GETTER(View, getHeight, height)
		TITANIUM_FUNCTION_AS_SETTER(View, setHeight, height)
		TITANIUM_FUNCTION_AS_GETTER(View, getLayout, layout)
		TITANIUM_FUNCTION_AS_SETTER(View, setLayout, layout)
		TITANIUM_FUNCTION_AS_GETTER(View, getParent, parent)
		TITANIUM_FUNCTION_AS_SETTER(View, setParent, parent)

	} // namespace UI
}  // namespace Titanium
