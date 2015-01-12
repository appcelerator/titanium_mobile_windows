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
		ScrollView::ScrollView(const JSContext& js_context) TITANIUM_NOEXCEPT : View(js_context) {}

		ScrollView::ScrollView(const ScrollView& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : View(rhs, arguments)
		{
		}

		void ScrollView::JSExportInitialize()
		{
			JSExport<ScrollView>::SetClassVersion(1);
			JSExport<ScrollView>::SetParent(JSExport<View>::Class());
			JSExport<ScrollView>::AddFunctionProperty("scrollTo", std::mem_fn(&ScrollView::scrollToArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty("scrollToBottom",
			                                          std::mem_fn(&ScrollView::scrollToBottomArgumentValidator));
			JSExport<ScrollView>::AddValueProperty("contentWidth", std::mem_fn(&ScrollView::getContentWidth),
			                                       std::mem_fn(&ScrollView::setContentWidth));
			JSExport<ScrollView>::AddValueProperty("contentHeight", std::mem_fn(&ScrollView::getContentHeight),
			                                       std::mem_fn(&ScrollView::setContentHeight));
			JSExport<ScrollView>::AddFunctionProperty("setContentWidth",
			                                          std::mem_fn(&ScrollView::setContentWidthArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty("setContentHeight",
			                                          std::mem_fn(&ScrollView::setContentHeightArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty("getContentWidth",
			                                          std::mem_fn(&ScrollView::getContentWidthArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty("getContentHeight",
			                                          std::mem_fn(&ScrollView::getContentHeightArgumentValidator));

			JSExport<ScrollView>::AddValueProperty("scrollingEnabled",
			                                       std::mem_fn(&ScrollView::get_ScrollingEnabledArgumentValidator),
			                                       std::mem_fn(&ScrollView::set_ScrollingEnabledArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty("setScrollingEnabled",
			                                          std::mem_fn(&ScrollView::setScrollingEnabledArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty("getScrollingEnabled",
			                                          std::mem_fn(&ScrollView::getScrollingEnabledArgumentValidator));

			JSExport<ScrollView>::AddValueProperty(
			    "showHorizontalScrollIndicator",
			    std::mem_fn(&ScrollView::get_ShowHorizontalScrollIndicatorArgumentValidator),
			    std::mem_fn(&ScrollView::set_ShowHorizontalScrollIndicatorArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty(
			    "setShowHorizontalScrollIndicator",
			    std::mem_fn(&ScrollView::setShowHorizontalScrollIndicatorArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty(
			    "getShowHorizontalScrollIndicator",
			    std::mem_fn(&ScrollView::getShowHorizontalScrollIndicatorArgumentValidator));

			JSExport<ScrollView>::AddValueProperty(
			    "showVerticalScrollIndicator",
			    std::mem_fn(&ScrollView::get_ShowVerticalScrollIndicatorArgumentValidator),
			    std::mem_fn(&ScrollView::set_ShowVerticalScrollIndicatorArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty(
			    "setShowVerticalScrollIndicator",
			    std::mem_fn(&ScrollView::setShowVerticalScrollIndicatorArgumentValidator));
			JSExport<ScrollView>::AddFunctionProperty(
			    "getShowVerticalScrollIndicator",
			    std::mem_fn(&ScrollView::getShowVerticalScrollIndicatorArgumentValidator));
		}

		void ScrollView::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::add: Unimplemented");
			View::add(view, this_object);
		}

		void ScrollView::scrollTo(double x, double y) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollTo: Unimplemented");
		}

		void ScrollView::scrollToBottom() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollToBottom: Unimplemented");
		}

		JSValue ScrollView::getContentWidth() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::getContentWidth: Unimplemented");
			return get_context().CreateUndefined();
		}
		JSValue ScrollView::getContentHeight() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::getContentHeight: Unimplemented");
			return get_context().CreateUndefined();
		}
		bool ScrollView::setContentWidth(const JSValue& width) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::setContentWidth: Unimplemented");
			return false;
		}
		bool ScrollView::setContentHeight(const JSValue& height) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::setContentHeight: Unimplemented");
			return false;
		}

		bool ScrollView::getScrollingEnabled() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::getScrollingEnabled: Unimplemented");
			return false;
		}

		bool ScrollView::setScrollingEnabled(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::setScrollingEnabled: Unimplemented");
			return false;
		}

		bool ScrollView::getShowHorizontalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::getShowHorizontalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::setShowHorizontalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::setShowHorizontalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::getShowVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::getShowVerticalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::setShowVerticalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::setShowVerticalScrollIndicator: Unimplemented");
			return false;
		}

		JSValue ScrollView::scrollToArgumentValidator(const std::vector<JSValue>& arguments,
		                                              JSObject&) TITANIUM_NOEXCEPT
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

		JSValue ScrollView::scrollToBottomArgumentValidator(const std::vector<JSValue>& arguments,
		                                                    JSObject&) TITANIUM_NOEXCEPT
		{
			scrollToBottom();
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::setContentWidthArgumentValidator(const std::vector<JSValue>& arguments,
		                                                     JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			setContentWidth(_0);
			return get_context().CreateUndefined();
		}
		JSValue ScrollView::getContentWidthArgumentValidator(const std::vector<JSValue>& arguments,
		                                                     JSObject&) TITANIUM_NOEXCEPT
		{
			return getContentWidth();
		}

		JSValue ScrollView::setContentHeightArgumentValidator(const std::vector<JSValue>& arguments,
		                                                      JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			setContentHeight(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::getContentHeightArgumentValidator(const std::vector<JSValue>& arguments,
		                                                      JSObject&) TITANIUM_NOEXCEPT
		{
			return getContentHeight();
		}

		JSValue ScrollView::get_ScrollingEnabledArgumentValidator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(getScrollingEnabled());
		}

		bool ScrollView::set_ScrollingEnabledArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return setScrollingEnabled(static_cast<bool>(argument));
		}

		JSValue ScrollView::setScrollingEnabledArgumentValidator(const std::vector<JSValue>& arguments,
		                                                         JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			set_ScrollingEnabledArgumentValidator(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::getScrollingEnabledArgumentValidator(const std::vector<JSValue>& arguments,
		                                                         JSObject&) TITANIUM_NOEXCEPT
		{
			return get_ScrollingEnabledArgumentValidator();
		}

		JSValue ScrollView::get_ShowHorizontalScrollIndicatorArgumentValidator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(getShowHorizontalScrollIndicator());
		}

		bool ScrollView::set_ShowHorizontalScrollIndicatorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return setShowHorizontalScrollIndicator(static_cast<bool>(argument));
		}

		JSValue ScrollView::setShowHorizontalScrollIndicatorArgumentValidator(const std::vector<JSValue>& arguments,
		                                                                      JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			set_ShowHorizontalScrollIndicatorArgumentValidator(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::getShowHorizontalScrollIndicatorArgumentValidator(const std::vector<JSValue>& arguments,
		                                                                      JSObject&) TITANIUM_NOEXCEPT
		{
			return get_ShowHorizontalScrollIndicatorArgumentValidator();
		}

		JSValue ScrollView::get_ShowVerticalScrollIndicatorArgumentValidator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(getShowVerticalScrollIndicator());
		}

		bool ScrollView::set_ShowVerticalScrollIndicatorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return setShowVerticalScrollIndicator(static_cast<bool>(argument));
		}

		JSValue ScrollView::setShowVerticalScrollIndicatorArgumentValidator(const std::vector<JSValue>& arguments,
		                                                                    JSObject&) TITANIUM_NOEXCEPT
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			set_ShowVerticalScrollIndicatorArgumentValidator(_0);
			return get_context().CreateUndefined();
		}

		JSValue ScrollView::getShowVerticalScrollIndicatorArgumentValidator(const std::vector<JSValue>& arguments,
		                                                                    JSObject&) TITANIUM_NOEXCEPT
		{
			return get_ShowVerticalScrollIndicatorArgumentValidator();
		}
	}
}  // namespace Titanium { namespace UI {
