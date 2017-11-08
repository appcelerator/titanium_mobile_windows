/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_SCROLLVIEW_HPP_
#define _TITANIUM_UI_SCROLLVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Point.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium UI ScrollView.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ScrollView
		*/
		class TITANIUMKIT_EXPORT ScrollView : public View, public JSExport<ScrollView>
		{
		public:
			/*!
			  @method

			  @abstract contentWidth : Number/String

			  @discussion Width of the scrollable region.

			  While auto and absolute dimensions are supported, relative values, such as those provided in percentages, are not. The minimum value for contentWidth is the width of the scroll view.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, contentWidth);

			/*!
			  @method

			  @abstract contentHeight : Number/String

			  @discussion Height of the scrollable region.

			  While auto and absolute dimensions are supported, relative values, such as those provided in percentages, are not. The minimum value for contentHeight is the height of the scroll view.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, contentHeight);

			/*!
			  @method

			  @abstract scrollingEnabled : Boolean

			  @discussion Determines whether scrolling is enabled for the view.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, scrollingEnabled);

			/*!
			  @method

			  @abstract showHorizontalScrollIndicator : Boolean

			  @discussion Determines whether the horizontal scroll indicator is visible.

			  Set to true to show the horizontal scroll indicator.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, showHorizontalScrollIndicator);

			/*!
			  @method

			  @abstract showVerticalScrollIndicator : Boolean

			  @discussion Determines whether the vertical scroll indicator is visible.

			  Set to true to show the vertical scroll indicator.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, showVerticalScrollIndicator);

			/*!
			  @property
			  @abstract canCancelEvents
			  @discussion Determines whether this scroll view can cancel subview touches in order to scroll instead.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, canCancelEvents);

			/*!
			  @property
			  @abstract contentOffset
			  @discussion X and Y coordinates to which to reposition the top-left point of the scrollable region.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Point, contentOffset);

			/*!
			  @property
			  @abstract decelerationRate
			  @discussion The deceleration rate of the ScrollView.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::int32_t, decelerationRate);

			/*!
			  @property
			  @abstract disableBounce
			  @discussion Determines whether scroll bounce of the scrollable region is enabled.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, disableBounce);

			/*!
			  @property
			  @abstract horizontalBounce
			  @discussion Determines whether horizontal scroll bounce of the scrollable region is enabled.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, horizontalBounce);

			/*!
			  @property
			  @abstract maxZoomScale
			  @discussion Maximum scaling factor of the scrollable region and its content.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, maxZoomScale);

			/*!
			  @property
			  @abstract minZoomScale
			  @discussion Minimum scaling factor of the scrollable region and its content.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, minZoomScale);

			/*!
			  @property
			  @abstract overScrollMode
			  @discussion Determines the behavior when the user overscolls the view.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::int32_t, overScrollMode);

			/*!
			  @property
			  @abstract scrollsToTop
			  @discussion Controls whether the scroll-to-top gesture is effective.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, scrollsToTop);

			/*!
			  @property
			  @abstract scrollType
			  @discussion Limits the direction of the scrollable region, overriding the deduced setting. Set to `horizontal` or `vertical`.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, scrollType);


			/*!
			  @property
			  @abstract scrollIndicatorStyle
			  @discussion Style of the scrollbar.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::int32_t, scrollIndicatorStyle);

			/*!
			  @property
			  @abstract verticalBounce
			  @discussion Determines whether vertical scroll bounce of the scrollable region is enabled.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, verticalBounce);

			/*!
			  @property
			  @abstract zoomScale
			  @discussion Scaling factor of the scroll view's content.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, zoomScale);

			/*!
			  @method
			  @abstract scrollTo
			  @discussion Moves the specified coordinate of the scrollable region into the viewable area.
			*/
			virtual void scrollTo(const double& x, const double& y) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract scrollToBottom
			  @discussion Moves the end of the scrollable region into the viewable area.
			*/
			virtual void scrollToBottom() TITANIUM_NOEXCEPT;

			/*!
			@method
			@abstract scrollToTop
			@discussion Moves the top of the scrollable region into the viewable area.
			*/
			virtual void scrollToTop() TITANIUM_NOEXCEPT;

			ScrollView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ScrollView() = default;
			ScrollView(const ScrollView&) = default;
			ScrollView& operator=(const ScrollView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ScrollView(ScrollView&&) = default;
			ScrollView& operator=(ScrollView&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(canCancelEvents);
			TITANIUM_PROPERTY_DEF(contentOffset);
			TITANIUM_PROPERTY_DEF(disableBounce);
			TITANIUM_PROPERTY_DEF(horizontalBounce);
			TITANIUM_PROPERTY_DEF(maxZoomScale);
			TITANIUM_PROPERTY_DEF(minZoomScale);
			TITANIUM_PROPERTY_DEF(scrollsToTop);
			TITANIUM_PROPERTY_DEF(scrollType);
			TITANIUM_PROPERTY_DEF(verticalBounce);
			TITANIUM_PROPERTY_DEF(zoomScale);
			TITANIUM_PROPERTY_DEF(contentWidth);
			TITANIUM_PROPERTY_DEF(contentHeight);
			TITANIUM_PROPERTY_DEF(scrollingEnabled);
			TITANIUM_PROPERTY_DEF(showHorizontalScrollIndicator);
			TITANIUM_PROPERTY_DEF(showVerticalScrollIndicator);
			TITANIUM_PROPERTY_DEF(decelerationRate);
			TITANIUM_PROPERTY_DEF(overScrollMode);
			TITANIUM_PROPERTY_DEF(scrollIndicatorStyle);

			TITANIUM_FUNCTION_DEF(getDecelerationRate);
			TITANIUM_FUNCTION_DEF(setDecelerationRate);
			TITANIUM_FUNCTION_DEF(getOverScrollMode);
			TITANIUM_FUNCTION_DEF(setOverScrollMode);
			TITANIUM_FUNCTION_DEF(getScrollIndicatorStyle);
			TITANIUM_FUNCTION_DEF(setScrollIndicatorStyle);
			TITANIUM_FUNCTION_DEF(scrollTo);
			TITANIUM_FUNCTION_DEF(scrollToBottom);
			TITANIUM_FUNCTION_DEF(scrollToTop);
			TITANIUM_FUNCTION_DEF(getCanCancelEvents);
			TITANIUM_FUNCTION_DEF(setCanCancelEvents);
			TITANIUM_FUNCTION_DEF(getContentOffset);
			TITANIUM_FUNCTION_DEF(setContentOffset);
			TITANIUM_FUNCTION_DEF(getDisableBounce);
			TITANIUM_FUNCTION_DEF(setDisableBounce);
			TITANIUM_FUNCTION_DEF(getHorizontalBounce);
			TITANIUM_FUNCTION_DEF(setHorizontalBounce);
			TITANIUM_FUNCTION_DEF(getMaxZoomScale);
			TITANIUM_FUNCTION_DEF(setMaxZoomScale);
			TITANIUM_FUNCTION_DEF(getMinZoomScale);
			TITANIUM_FUNCTION_DEF(setMinZoomScale);
			TITANIUM_FUNCTION_DEF(getScrollsToTop);
			TITANIUM_FUNCTION_DEF(setScrollsToTop);
			TITANIUM_FUNCTION_DEF(getScrollType);
			TITANIUM_FUNCTION_DEF(setScrollType);
			TITANIUM_FUNCTION_DEF(getVerticalBounce);
			TITANIUM_FUNCTION_DEF(setVerticalBounce);
			TITANIUM_FUNCTION_DEF(getZoomScale);
			TITANIUM_FUNCTION_DEF(setZoomScale);
			TITANIUM_FUNCTION_DEF(getContentWidth);
			TITANIUM_FUNCTION_DEF(setContentWidth);
			TITANIUM_FUNCTION_DEF(getContentHeight);
			TITANIUM_FUNCTION_DEF(setContentHeight);
			TITANIUM_FUNCTION_DEF(getScrollingEnabled);
			TITANIUM_FUNCTION_DEF(setScrollingEnabled);
			TITANIUM_FUNCTION_DEF(getShowHorizontalScrollIndicator);
			TITANIUM_FUNCTION_DEF(setShowHorizontalScrollIndicator);
			TITANIUM_FUNCTION_DEF(getShowVerticalScrollIndicator);
			TITANIUM_FUNCTION_DEF(setShowVerticalScrollIndicator);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			bool canCancelEvents__;
			Point contentOffset__;
			bool disableBounce__;
			bool horizontalBounce__;
			double maxZoomScale__;
			double minZoomScale__;
			bool scrollsToTop__;
			std::string scrollType__;
			bool verticalBounce__;
			double zoomScale__;
			std::string contentWidth__;
			std::string contentHeight__;
			bool scrollingEnabled__;
			bool showHorizontalScrollIndicator__;
			bool showVerticalScrollIndicator__;
			std::int32_t decelerationRate__;
			std::int32_t overScrollMode__;
			std::int32_t scrollIndicatorStyle__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_SCROLLVIEW_HPP_
