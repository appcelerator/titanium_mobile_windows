/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ScrollView.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		ScrollView::ScrollView(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context, "Ti.UI.ScrollView")
		{
		}

		void ScrollView::scrollTo(const double& x, const double& y) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollTo: Unimplemented");
		}

		void ScrollView::scrollToBottom() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollToBottom: Unimplemented");
		}

		void ScrollView::scrollToTop() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollToTop: Unimplemented");
		}

		TITANIUM_PROPERTY_READWRITE(ScrollView, std::int32_t, decelerationRate)
		TITANIUM_PROPERTY_READWRITE(ScrollView, std::int32_t, overScrollMode)
		TITANIUM_PROPERTY_READWRITE(ScrollView, std::int32_t, scrollIndicatorStyle)

		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, canCancelEvents)
		TITANIUM_PROPERTY_READWRITE(ScrollView, Point, contentOffset)
		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, disableBounce)
		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, horizontalBounce)
		TITANIUM_PROPERTY_READWRITE(ScrollView, double, maxZoomScale)
		TITANIUM_PROPERTY_READWRITE(ScrollView, double, minZoomScale)
		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, scrollsToTop)
		TITANIUM_PROPERTY_READWRITE(ScrollView, std::string, scrollType)
		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, verticalBounce)
		TITANIUM_PROPERTY_READWRITE(ScrollView, double, zoomScale)
		TITANIUM_PROPERTY_READWRITE(ScrollView, std::string, contentWidth)
		TITANIUM_PROPERTY_READWRITE(ScrollView, std::string, contentHeight)
		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, scrollingEnabled)
		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, showHorizontalScrollIndicator)
		TITANIUM_PROPERTY_READWRITE(ScrollView, bool, showVerticalScrollIndicator)

		void ScrollView::JSExportInitialize()
		{
			JSExport<ScrollView>::SetClassVersion(1);
			JSExport<ScrollView>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(ScrollView, canCancelEvents);
			TITANIUM_ADD_PROPERTY(ScrollView, contentOffset);
			TITANIUM_ADD_PROPERTY(ScrollView, disableBounce);
			TITANIUM_ADD_PROPERTY(ScrollView, horizontalBounce);
			TITANIUM_ADD_PROPERTY(ScrollView, maxZoomScale);
			TITANIUM_ADD_PROPERTY(ScrollView, minZoomScale);
			TITANIUM_ADD_PROPERTY(ScrollView, scrollsToTop);
			TITANIUM_ADD_PROPERTY(ScrollView, scrollType);
			TITANIUM_ADD_PROPERTY(ScrollView, verticalBounce);
			TITANIUM_ADD_PROPERTY(ScrollView, zoomScale);
			TITANIUM_ADD_PROPERTY(ScrollView, contentWidth);
			TITANIUM_ADD_PROPERTY(ScrollView, contentHeight);
			TITANIUM_ADD_PROPERTY(ScrollView, scrollingEnabled);
			TITANIUM_ADD_PROPERTY(ScrollView, showHorizontalScrollIndicator);
			TITANIUM_ADD_PROPERTY(ScrollView, showVerticalScrollIndicator);
			TITANIUM_ADD_PROPERTY(ScrollView, decelerationRate);
			TITANIUM_ADD_PROPERTY(ScrollView, overScrollMode);
			TITANIUM_ADD_PROPERTY(ScrollView, scrollIndicatorStyle);

			TITANIUM_ADD_FUNCTION(ScrollView, scrollTo);
			TITANIUM_ADD_FUNCTION(ScrollView, scrollToBottom);
			TITANIUM_ADD_FUNCTION(ScrollView, scrollToTop);
			TITANIUM_ADD_FUNCTION(ScrollView, getCanCancelEvents);
			TITANIUM_ADD_FUNCTION(ScrollView, setCanCancelEvents);
			TITANIUM_ADD_FUNCTION(ScrollView, getContentOffset);
			TITANIUM_ADD_FUNCTION(ScrollView, setContentOffset);
			TITANIUM_ADD_FUNCTION(ScrollView, getDisableBounce);
			TITANIUM_ADD_FUNCTION(ScrollView, setDisableBounce);
			TITANIUM_ADD_FUNCTION(ScrollView, getHorizontalBounce);
			TITANIUM_ADD_FUNCTION(ScrollView, setHorizontalBounce);
			TITANIUM_ADD_FUNCTION(ScrollView, getMaxZoomScale);
			TITANIUM_ADD_FUNCTION(ScrollView, setMaxZoomScale);
			TITANIUM_ADD_FUNCTION(ScrollView, getMinZoomScale);
			TITANIUM_ADD_FUNCTION(ScrollView, setMinZoomScale);
			TITANIUM_ADD_FUNCTION(ScrollView, getScrollsToTop);
			TITANIUM_ADD_FUNCTION(ScrollView, setScrollsToTop);
			TITANIUM_ADD_FUNCTION(ScrollView, getScrollType);
			TITANIUM_ADD_FUNCTION(ScrollView, setScrollType);
			TITANIUM_ADD_FUNCTION(ScrollView, getVerticalBounce);
			TITANIUM_ADD_FUNCTION(ScrollView, setVerticalBounce);
			TITANIUM_ADD_FUNCTION(ScrollView, getZoomScale);
			TITANIUM_ADD_FUNCTION(ScrollView, setZoomScale);
			TITANIUM_ADD_FUNCTION(ScrollView, getContentWidth);
			TITANIUM_ADD_FUNCTION(ScrollView, setContentWidth);
			TITANIUM_ADD_FUNCTION(ScrollView, getContentHeight);
			TITANIUM_ADD_FUNCTION(ScrollView, setContentHeight);
			TITANIUM_ADD_FUNCTION(ScrollView, getScrollingEnabled);
			TITANIUM_ADD_FUNCTION(ScrollView, setScrollingEnabled);
			TITANIUM_ADD_FUNCTION(ScrollView, getShowHorizontalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, setShowHorizontalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, getShowVerticalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, setShowVerticalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, getDecelerationRate);
			TITANIUM_ADD_FUNCTION(ScrollView, setDecelerationRate);
			TITANIUM_ADD_FUNCTION(ScrollView, getOverScrollMode);
			TITANIUM_ADD_FUNCTION(ScrollView, setOverScrollMode);
			TITANIUM_ADD_FUNCTION(ScrollView, getScrollIndicatorStyle);
			TITANIUM_ADD_FUNCTION(ScrollView, setScrollIndicatorStyle);
		}

		TITANIUM_FUNCTION(ScrollView, scrollTo)
		{
			ENSURE_ARGUMENT_INDEX(1);
			ENSURE_DOUBLE_AT_INDEX(x, 0);
			ENSURE_DOUBLE_AT_INDEX(y, 1);
			scrollTo(x, y);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ScrollView, scrollToBottom)
		{
			scrollToBottom();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ScrollView, scrollToTop)
		{
			scrollToTop();
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER_INT(ScrollView, decelerationRate)
		TITANIUM_PROPERTY_SETTER_INT(ScrollView, decelerationRate)
		TITANIUM_PROPERTY_GETTER_INT(ScrollView, overScrollMode)
		TITANIUM_PROPERTY_SETTER_INT(ScrollView, overScrollMode)
		TITANIUM_PROPERTY_GETTER_INT(ScrollView, scrollIndicatorStyle)
		TITANIUM_PROPERTY_SETTER_INT(ScrollView, scrollIndicatorStyle)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, canCancelEvents)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, canCancelEvents)
		TITANIUM_PROPERTY_GETTER_STRUCT(ScrollView, contentOffset, Point)
		TITANIUM_PROPERTY_SETTER_STRUCT(ScrollView, contentOffset, Point)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, disableBounce)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, disableBounce)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, horizontalBounce)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, horizontalBounce)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ScrollView, maxZoomScale)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ScrollView, maxZoomScale)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ScrollView, minZoomScale)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ScrollView, minZoomScale)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, scrollsToTop)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, scrollsToTop)
		TITANIUM_PROPERTY_GETTER_STRING(ScrollView, scrollType)
		TITANIUM_PROPERTY_SETTER_STRING(ScrollView, scrollType)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, verticalBounce)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, verticalBounce)
		TITANIUM_PROPERTY_GETTER_DOUBLE(ScrollView, zoomScale)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ScrollView, zoomScale)
		TITANIUM_PROPERTY_GETTER_STRING(ScrollView, contentWidth)
		TITANIUM_PROPERTY_SETTER_STRING(ScrollView, contentWidth)
		TITANIUM_PROPERTY_GETTER_STRING(ScrollView, contentHeight)
		TITANIUM_PROPERTY_SETTER_STRING(ScrollView, contentHeight)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, scrollingEnabled)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, scrollingEnabled)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, showHorizontalScrollIndicator)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, showHorizontalScrollIndicator)
		TITANIUM_PROPERTY_GETTER_BOOL(ScrollView, showVerticalScrollIndicator)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollView, showVerticalScrollIndicator)

		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getDecelerationRate, decelerationRate)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setDecelerationRate, decelerationRate)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getOverScrollMode, overScrollMode)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setOverScrollMode, overScrollMode)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getScrollIndicatorStyle, scrollIndicatorStyle)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setScrollIndicatorStyle, scrollIndicatorStyle)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getCanCancelEvents, canCancelEvents)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setCanCancelEvents, canCancelEvents)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getContentOffset, contentOffset)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setContentOffset, contentOffset)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getDisableBounce, disableBounce)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setDisableBounce, disableBounce)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getHorizontalBounce, horizontalBounce)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setHorizontalBounce, horizontalBounce)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getMaxZoomScale, maxZoomScale)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setMaxZoomScale, maxZoomScale)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getMinZoomScale, minZoomScale)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setMinZoomScale, minZoomScale)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getScrollsToTop, scrollsToTop)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setScrollsToTop, scrollsToTop)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getScrollType, scrollType)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setScrollType, scrollType)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getVerticalBounce, verticalBounce)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setVerticalBounce, verticalBounce)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getZoomScale, zoomScale)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setZoomScale, zoomScale)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getContentWidth, contentWidth)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setContentWidth, contentWidth)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getContentHeight, contentHeight)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setContentHeight, contentHeight)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getScrollingEnabled, scrollingEnabled)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setScrollingEnabled, scrollingEnabled)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getShowHorizontalScrollIndicator, showHorizontalScrollIndicator)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setShowHorizontalScrollIndicator, showHorizontalScrollIndicator)
		TITANIUM_FUNCTION_AS_GETTER(ScrollView, getShowVerticalScrollIndicator, showVerticalScrollIndicator)
		TITANIUM_FUNCTION_AS_SETTER(ScrollView, setShowVerticalScrollIndicator, showVerticalScrollIndicator)


	} // namespace UI
}  // namespace Titanium
