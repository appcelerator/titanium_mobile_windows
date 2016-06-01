/**
 * TitaniumKit Titanium.UI.ScrollableView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ScrollableView.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{


		ScrollableView::ScrollableView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.ScrollableView"),
			cacheSize__(0),
			currentPage__(0),
			disableBounce__(false),
			pagingControlColor__("black"),
			pagingControlHeight__(20),
			showPagingControl__(false),
			pagingControlTimeout__(3000),
			pagingControlAlpha__(1),
			pagingControlOnTop__(false),
			overlayEnabled__(false),
			scrollingEnabled__(false),
			clipViews__(true)
		{
		}

		TITANIUM_PROPERTY_READWRITE(ScrollableView, std::uint32_t, cacheSize)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, std::uint32_t, currentPage)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, bool, disableBounce)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, std::string, pagingControlColor)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, std::uint32_t, pagingControlHeight)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, bool, showPagingControl)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, std::chrono::milliseconds, pagingControlTimeout)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, double, pagingControlAlpha)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, bool, pagingControlOnTop)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, bool, overlayEnabled)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, bool, scrollingEnabled)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, bool, clipViews)
		TITANIUM_PROPERTY_READWRITE(ScrollableView, Dimension, hitRect)

		TITANIUM_PROPERTY_READWRITE(ScrollableView, std::vector<std::shared_ptr<View>>, views)

		void ScrollableView::addView(const std::shared_ptr<View>& view) TITANIUM_NOEXCEPT
		{
			views__.push_back(view);
		}

		void ScrollableView::removeView(const std::shared_ptr<View>& view) TITANIUM_NOEXCEPT
		{
			const auto it = std::find(views__.begin(), views__.end(), view);
			if (it != views__.end()) {
				views__.erase(it);
			}
		}

		void ScrollableView::moveNext() TITANIUM_NOEXCEPT
		{
			if (currentPage__ < views__.size() - 1) {
				set_currentPage(++currentPage__);
			}
		}

		void ScrollableView::movePrevious() TITANIUM_NOEXCEPT
		{
			if (currentPage__ > 0) {
				set_currentPage(--currentPage__);
			}
		}

		void ScrollableView::scrollToView(const std::shared_ptr<View>& view) TITANIUM_NOEXCEPT
		{
			const auto it = std::find(views__.begin(), views__.end(), view);
			if (it != views__.end()) {
				set_currentPage(static_cast<uint32_t>(std::distance(views__.begin(), it)));
			}
		}

		void ScrollableView::JSExportInitialize()
		{
			JSExport<ScrollableView>::SetClassVersion(1);
			JSExport<ScrollableView>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(ScrollableView, cacheSize);
			TITANIUM_ADD_PROPERTY(ScrollableView, currentPage);
			TITANIUM_ADD_PROPERTY(ScrollableView, disableBounce);
			TITANIUM_ADD_PROPERTY(ScrollableView, overScrollMode);
			TITANIUM_ADD_PROPERTY(ScrollableView, pagingControlColor);
			TITANIUM_ADD_PROPERTY(ScrollableView, pagingControlHeight);
			TITANIUM_ADD_PROPERTY(ScrollableView, showPagingControl);
			TITANIUM_ADD_PROPERTY(ScrollableView, pagingControlTimeout);
			TITANIUM_ADD_PROPERTY(ScrollableView, pagingControlAlpha);
			TITANIUM_ADD_PROPERTY(ScrollableView, pagingControlOnTop);
			TITANIUM_ADD_PROPERTY(ScrollableView, overlayEnabled);
			TITANIUM_ADD_PROPERTY(ScrollableView, scrollingEnabled);
			TITANIUM_ADD_PROPERTY(ScrollableView, views);
			TITANIUM_ADD_PROPERTY(ScrollableView, clipViews);
			TITANIUM_ADD_PROPERTY(ScrollableView, hitRect);

			TITANIUM_ADD_FUNCTION(ScrollableView, addView);
			TITANIUM_ADD_FUNCTION(ScrollableView, moveNext);
			TITANIUM_ADD_FUNCTION(ScrollableView, movePrevious);
			TITANIUM_ADD_FUNCTION(ScrollableView, removeView);
			TITANIUM_ADD_FUNCTION(ScrollableView, scrollToView);
			TITANIUM_ADD_FUNCTION(ScrollableView, getCacheSize);
			TITANIUM_ADD_FUNCTION(ScrollableView, setCacheSize);
			TITANIUM_ADD_FUNCTION(ScrollableView, getCurrentPage);
			TITANIUM_ADD_FUNCTION(ScrollableView, setCurrentPage);
			TITANIUM_ADD_FUNCTION(ScrollableView, getDisableBounce);
			TITANIUM_ADD_FUNCTION(ScrollableView, setDisableBounce);
			TITANIUM_ADD_FUNCTION(ScrollableView, getOverScrollMode);
			TITANIUM_ADD_FUNCTION(ScrollableView, setOverScrollMode);
			TITANIUM_ADD_FUNCTION(ScrollableView, getPagingControlColor);
			TITANIUM_ADD_FUNCTION(ScrollableView, setPagingControlColor);
			TITANIUM_ADD_FUNCTION(ScrollableView, getPagingControlHeight);
			TITANIUM_ADD_FUNCTION(ScrollableView, setPagingControlHeight);
			TITANIUM_ADD_FUNCTION(ScrollableView, getShowPagingControl);
			TITANIUM_ADD_FUNCTION(ScrollableView, setShowPagingControl);
			TITANIUM_ADD_FUNCTION(ScrollableView, getPagingControlTimeout);
			TITANIUM_ADD_FUNCTION(ScrollableView, setPagingControlTimeout);
			TITANIUM_ADD_FUNCTION(ScrollableView, getPagingControlAlpha);
			TITANIUM_ADD_FUNCTION(ScrollableView, setPagingControlAlpha);
			TITANIUM_ADD_FUNCTION(ScrollableView, getPagingControlOnTop);
			TITANIUM_ADD_FUNCTION(ScrollableView, setPagingControlOnTop);
			TITANIUM_ADD_FUNCTION(ScrollableView, getOverlayEnabled);
			TITANIUM_ADD_FUNCTION(ScrollableView, setOverlayEnabled);
			TITANIUM_ADD_FUNCTION(ScrollableView, getScrollingEnabled);
			TITANIUM_ADD_FUNCTION(ScrollableView, setScrollingEnabled);
			TITANIUM_ADD_FUNCTION(ScrollableView, getViews);
			TITANIUM_ADD_FUNCTION(ScrollableView, setViews);
			TITANIUM_ADD_FUNCTION(ScrollableView, getClipViews);
			TITANIUM_ADD_FUNCTION(ScrollableView, setClipViews);
			TITANIUM_ADD_FUNCTION(ScrollableView, getHitRect);
			TITANIUM_ADD_FUNCTION(ScrollableView, setHitRect);
		}

		TITANIUM_PROPERTY_GETTER_UINT(ScrollableView, cacheSize)
		TITANIUM_PROPERTY_SETTER_UINT(ScrollableView, cacheSize)

		TITANIUM_PROPERTY_GETTER_UINT(ScrollableView, currentPage)
		TITANIUM_PROPERTY_SETTER_UINT(ScrollableView, currentPage)

		TITANIUM_PROPERTY_GETTER_BOOL(ScrollableView, disableBounce)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollableView, disableBounce)

		TITANIUM_PROPERTY_GETTER_UNIMPLEMENTED(ScrollableView, overScrollMode)
		TITANIUM_PROPERTY_SETTER_UNIMPLEMENTED(ScrollableView, overScrollMode)

		TITANIUM_PROPERTY_GETTER_STRING(ScrollableView, pagingControlColor)
		TITANIUM_PROPERTY_SETTER_STRING(ScrollableView, pagingControlColor)

		TITANIUM_PROPERTY_GETTER_UINT(ScrollableView, pagingControlHeight)
		TITANIUM_PROPERTY_SETTER_UINT(ScrollableView, pagingControlHeight)

		TITANIUM_PROPERTY_GETTER_BOOL(ScrollableView, showPagingControl)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollableView, showPagingControl)

		TITANIUM_PROPERTY_GETTER_TIME(ScrollableView, pagingControlTimeout)
		TITANIUM_PROPERTY_SETTER_TIME(ScrollableView, pagingControlTimeout)

		TITANIUM_PROPERTY_GETTER_DOUBLE(ScrollableView, pagingControlAlpha)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ScrollableView, pagingControlAlpha)

		TITANIUM_PROPERTY_GETTER_BOOL(ScrollableView, pagingControlOnTop)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollableView, pagingControlOnTop)

		TITANIUM_PROPERTY_GETTER_BOOL(ScrollableView, overlayEnabled)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollableView, overlayEnabled)

		TITANIUM_PROPERTY_GETTER_BOOL(ScrollableView, scrollingEnabled)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollableView, scrollingEnabled)

		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(ScrollableView, views)
		TITANIUM_PROPERTY_SETTER_OBJECT_ARRAY(ScrollableView, views, View)

		TITANIUM_PROPERTY_GETTER_BOOL(ScrollableView, clipViews)
		TITANIUM_PROPERTY_SETTER_BOOL(ScrollableView, clipViews)

		TITANIUM_PROPERTY_GETTER_STRUCT(ScrollableView, hitRect, Dimension)
		TITANIUM_PROPERTY_SETTER_STRUCT(ScrollableView, hitRect, Dimension)

		TITANIUM_FUNCTION(ScrollableView, addView)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_OBJECT_AT_INDEX(view, 0);
			addView(view.GetPrivate<View>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ScrollableView, moveNext)
		{
			moveNext();
			return get_context().CreateUndefined();
		}
		TITANIUM_FUNCTION(ScrollableView, movePrevious)
		{
			movePrevious();
			return get_context().CreateUndefined();
		}
		TITANIUM_FUNCTION(ScrollableView, removeView)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_OBJECT_AT_INDEX(view, 0);
			removeView(view.GetPrivate<View>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ScrollableView, scrollToView)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_OBJECT_AT_INDEX(view, 0);
			scrollToView(view.GetPrivate<View>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getCacheSize, cacheSize)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setCacheSize, cacheSize)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getCurrentPage, currentPage)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setCurrentPage, currentPage)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getDisableBounce, disableBounce)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setDisableBounce, disableBounce)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getOverScrollMode, overScrollMode)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setOverScrollMode, overScrollMode)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getPagingControlColor, pagingControlColor)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setPagingControlColor, pagingControlColor)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getPagingControlHeight, pagingControlHeight)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setPagingControlHeight, pagingControlHeight)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getShowPagingControl, showPagingControl)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setShowPagingControl, showPagingControl)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getPagingControlTimeout, pagingControlTimeout)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setPagingControlTimeout, pagingControlTimeout)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getPagingControlAlpha, pagingControlAlpha)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setPagingControlAlpha, pagingControlAlpha)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getPagingControlOnTop, pagingControlOnTop)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setPagingControlOnTop, pagingControlOnTop)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getOverlayEnabled, overlayEnabled)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setOverlayEnabled, overlayEnabled)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getScrollingEnabled, scrollingEnabled)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setScrollingEnabled, scrollingEnabled)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getViews, views)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setViews, views)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getClipViews, clipViews)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setClipViews, clipViews)
		TITANIUM_FUNCTION_AS_GETTER(ScrollableView, getHitRect, hitRect)
		TITANIUM_FUNCTION_AS_SETTER(ScrollableView, setHitRect, hitRect)

	} // namespace UI
} // namespace Titanium
