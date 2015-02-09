/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ScrollView.hpp"

namespace Titanium
{
	namespace UI
	{
		ScrollView::ScrollView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : UIBase(js_context)
		{
		}

		void ScrollView::JSExportInitialize()
		{
			JSExport<ScrollView>::SetClassVersion(1);
			JSExport<ScrollView>::SetParent(JSExport<UIBase>::Class());
			JSExport<ScrollView>::AddFunctionProperty("scrollTo", std::mem_fn(&ScrollView::js_scrollTo));
			JSExport<ScrollView>::AddFunctionProperty("scrollToBottom", std::mem_fn(&ScrollView::js_scrollToBottom));
			JSExport<ScrollView>::AddValueProperty("contentWidth", std::mem_fn(&ScrollView::js_get_contentWidth), std::mem_fn(&ScrollView::js_set_contentWidth));
			JSExport<ScrollView>::AddValueProperty("contentHeight", std::mem_fn(&ScrollView::js_get_contentHeight), std::mem_fn(&ScrollView::js_set_contentHeight));
			JSExport<ScrollView>::AddFunctionProperty("setContentWidth", std::mem_fn(&ScrollView::js_setContentWidth));
			JSExport<ScrollView>::AddFunctionProperty("setContentHeight", std::mem_fn(&ScrollView::js_setContentHeight));
			JSExport<ScrollView>::AddFunctionProperty("getContentWidth", std::mem_fn(&ScrollView::js_getContentWidth));
			JSExport<ScrollView>::AddFunctionProperty("getContentHeight", std::mem_fn(&ScrollView::js_getContentHeight));

			JSExport<ScrollView>::AddValueProperty("scrollingEnabled", std::mem_fn(&ScrollView::js_get_scrollingEnabled), std::mem_fn(&ScrollView::js_set_scrollingEnabled));
			JSExport<ScrollView>::AddFunctionProperty("setScrollingEnabled", std::mem_fn(&ScrollView::js_setScrollingEnabled));
			JSExport<ScrollView>::AddFunctionProperty("getScrollingEnabled", std::mem_fn(&ScrollView::js_getScrollingEnabled));

			JSExport<ScrollView>::AddValueProperty("showHorizontalScrollIndicator", std::mem_fn(&ScrollView::js_get_showHorizontalScrollIndicator), std::mem_fn(&ScrollView::js_set_showHorizontalScrollIndicator));
			JSExport<ScrollView>::AddFunctionProperty("setShowHorizontalScrollIndicator", std::mem_fn(&ScrollView::js_setShowHorizontalScrollIndicator));
			JSExport<ScrollView>::AddFunctionProperty("getShowHorizontalScrollIndicator", std::mem_fn(&ScrollView::js_getShowHorizontalScrollIndicator));

			JSExport<ScrollView>::AddValueProperty("showVerticalScrollIndicator", std::mem_fn(&ScrollView::js_get_showVerticalScrollIndicator), std::mem_fn(&ScrollView::js_set_showVerticalScrollIndicator));
			JSExport<ScrollView>::AddFunctionProperty("setShowVerticalScrollIndicator", std::mem_fn(&ScrollView::js_setShowVerticalScrollIndicator));
			JSExport<ScrollView>::AddFunctionProperty("getShowVerticalScrollIndicator", std::mem_fn(&ScrollView::js_getShowVerticalScrollIndicator));
		}

		void ScrollView::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::add: Unimplemented");
			UIBase::add(view, this_object);
		}

		void ScrollView::scrollTo(double x, double y) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollTo: Unimplemented");
		}

		void ScrollView::scrollToBottom() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollToBottom: Unimplemented");
		}

		std::string ScrollView::get_contentWidth() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_contentWidth: Unimplemented");
			return "";
		}

		std::string ScrollView::get_contentHeight() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_contentHeight: Unimplemented");
			return "";
		}

		bool ScrollView::set_contentWidth(const std::string& width) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentWidth(std::string): Unimplemented");
			return false;
		}

		bool ScrollView::set_contentHeight(const std::string& height) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentHeight(std::string): Unimplemented");
			return false;
		}

		bool ScrollView::set_contentWidth(const double& width) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentWidth(double): Unimplemented");
			return false;
		}

		bool ScrollView::set_contentHeight(const double& height) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentHeight(double): Unimplemented");
			return false;
		}

		bool ScrollView::get_scrollingEnabled() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_scrollingEnabled: Unimplemented");
			return false;
		}

		bool ScrollView::set_scrollingEnabled(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_scrollingEnabled: Unimplemented");
			return false;
		}

		bool ScrollView::get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_showHorizontalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::set_showHorizontalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_showHorizontalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_showVerticalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::set_showVerticalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_showVerticalScrollIndicator: Unimplemented");
			return false;
		}

		JSValue ScrollView::js_scrollTo(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_0.IsNumber());
			TITANIUM_ASSERT(_1.IsNumber());
			scrollTo(static_cast<double>(_0), static_cast<double>(_1));
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::js_scrollToBottom(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			scrollToBottom();
			return get_context().CreateUndefined();
		}

		bool ScrollView::js_set_contentWidth(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			if (argument.IsNumber()) {
				set_contentWidth(static_cast<double>(argument));
			} else {
				set_contentWidth(static_cast<std::string>(argument));
			}
			return true;
		}

		JSValue ScrollView::js_setContentWidth(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_contentWidth(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::js_get_contentWidth() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_contentWidth());
		}

		JSValue ScrollView::js_getContentWidth(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			return js_get_contentWidth();
		}

		bool ScrollView::js_set_contentHeight(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			if (argument.IsNumber()) {
				set_contentHeight(static_cast<double>(argument));
			} else {
				set_contentHeight(static_cast<std::string>(argument));
			}
			return true;
		}

		JSValue ScrollView::js_setContentHeight(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_contentHeight(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::js_get_contentHeight() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_contentHeight());
		}

		JSValue ScrollView::js_getContentHeight(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			return js_get_contentHeight();
		}

		JSValue ScrollView::js_get_scrollingEnabled() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_scrollingEnabled());
		}

		JSValue ScrollView::js_getScrollingEnabled(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			return js_get_scrollingEnabled();
		}

		bool ScrollView::js_set_scrollingEnabled(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return set_scrollingEnabled(static_cast<bool>(argument));
		}

		JSValue ScrollView::js_setScrollingEnabled(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_scrollingEnabled(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::js_get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_showHorizontalScrollIndicator());
		}

		JSValue ScrollView::js_getShowHorizontalScrollIndicator(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			return js_get_showHorizontalScrollIndicator();
		}

		bool ScrollView::js_set_showHorizontalScrollIndicator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return set_showHorizontalScrollIndicator(static_cast<bool>(argument));
		}

		JSValue ScrollView::js_setShowHorizontalScrollIndicator(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_showHorizontalScrollIndicator(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::js_get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_showVerticalScrollIndicator());
		}

		JSValue ScrollView::js_getShowVerticalScrollIndicator(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			return js_get_showVerticalScrollIndicator();
		}

		bool ScrollView::js_set_showVerticalScrollIndicator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return set_showVerticalScrollIndicator(static_cast<bool>(argument));
		}

		JSValue ScrollView::js_setShowVerticalScrollIndicator(const std::vector<JSValue>& arguments, JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_showVerticalScrollIndicator(_0);
			return get_context().CreateUndefined();
		}
	} // namespace UI
}  // namespace Titanium
