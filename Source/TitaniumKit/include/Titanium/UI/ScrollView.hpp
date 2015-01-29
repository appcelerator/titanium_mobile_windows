/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_SCROLLVIEW_HPP_
#define _TITANIUM_UI_SCROLLVIEW_HPP_

#include "Titanium/UI/View.hpp"

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
		class TITANIUMKIT_EXPORT ScrollView : public virtual View, public JSExport<ScrollView>
		{
		public:
			virtual void add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT override;
			virtual void scrollTo(double x, double y) TITANIUM_NOEXCEPT;
			virtual void scrollToBottom() TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract contentWidth : Number/String

			  @discussion Width of the scrollable region.

			  While auto and absolute dimensions are supported, relative values, such as those provided in percentages, are not. The minimum value for contentWidth is the width of the scroll view.
			*/
			virtual std::string get_contentWidth() const TITANIUM_NOEXCEPT;
			virtual bool set_contentWidth(const std::string& width) TITANIUM_NOEXCEPT;
			virtual bool set_contentWidth(const double& width) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract contentHeight : Number/String

			  @discussion Height of the scrollable region.

			  While auto and absolute dimensions are supported, relative values, such as those provided in percentages, are not. The minimum value for contentHeight is the height of the scroll view.
			*/
			virtual std::string get_contentHeight() const TITANIUM_NOEXCEPT;
			virtual bool set_contentHeight(const std::string& height) TITANIUM_NOEXCEPT;
			virtual bool set_contentHeight(const double& height) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract scrollingEnabled : Boolean

			  @discussion Determines whether scrolling is enabled for the view.
			*/
			virtual bool get_scrollingEnabled() const TITANIUM_NOEXCEPT;
			virtual bool set_scrollingEnabled(bool enabled) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract showHorizontalScrollIndicator : Boolean

			  @discussion Determines whether the horizontal scroll indicator is visible.

			  Set to true to show the horizontal scroll indicator.
			*/
			virtual bool get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT;
			virtual bool set_showHorizontalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract showVerticalScrollIndicator : Boolean

			  @discussion Determines whether the vertical scroll indicator is visible.

			  Set to true to show the vertical scroll indicator.
			*/
			virtual bool get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT;
			virtual bool set_showVerticalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT;

			ScrollView(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ScrollView() = default;
			ScrollView(const ScrollView&) = default;
			ScrollView& operator=(const ScrollView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ScrollView(ScrollView&&) = default;
			ScrollView& operator=(ScrollView&&) = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_contentWidth() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_contentWidth(const JSValue& width) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_contentHeight() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_contentHeight(const JSValue& width) TITANIUM_NOEXCEPT final;

			virtual JSValue js_setContentWidth(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getContentWidth(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_setContentHeight(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getContentHeight(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_scrollTo(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_scrollToBottom(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_scrollingEnabled() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_scrollingEnabled(const JSValue& width) TITANIUM_NOEXCEPT final;

			virtual JSValue js_setScrollingEnabled(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getScrollingEnabled(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_showHorizontalScrollIndicator(const JSValue& width) TITANIUM_NOEXCEPT final;

			virtual JSValue js_setShowHorizontalScrollIndicator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getShowHorizontalScrollIndicator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_showVerticalScrollIndicator(const JSValue& width) TITANIUM_NOEXCEPT final;

			virtual JSValue js_setShowVerticalScrollIndicator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getShowVerticalScrollIndicator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		private:
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_SCROLLVIEW_HPP_
