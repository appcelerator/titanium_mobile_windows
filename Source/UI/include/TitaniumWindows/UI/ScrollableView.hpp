/**
 * Titanium.UI.ScrollableView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_SCROLLABLEVIEW_HPP_
#define _TITANIUMWINDOWS_SCROLLABLEVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/ScrollableView.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		class ScrollableView;

		class TITANIUMWINDOWS_UI_EXPORT ScrollableViewLayoutDelegate : public WindowsViewLayoutDelegate {
		public:
			ScrollableViewLayoutDelegate(ScrollableView*) TITANIUM_NOEXCEPT;
			virtual ~ScrollableViewLayoutDelegate() = default;

			virtual void onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect) override;
		protected:

#pragma warning(push)
#pragma warning(disable : 4251)
			ScrollableView* scrollable_view__;
#pragma warning(pop)
		};

		/*!
		  @class

		  @discussion This is the Titanium.UI.ScrollableView implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ScrollableView final : public Titanium::UI::ScrollableView, public JSExport<ScrollableView>
		{

		public:
			ScrollableView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ScrollableView()                        = default;
			ScrollableView(const ScrollableView&)            = default;
			ScrollableView& operator=(const ScrollableView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ScrollableView(ScrollableView&&)                 = default;
			ScrollableView& operator=(ScrollableView&&)      = default;
#endif

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			std::shared_ptr<WindowsViewLayoutDelegate> getContentViewLayoutDelegate();

			void set_views(const std::vector<std::shared_ptr<View>>& views) TITANIUM_NOEXCEPT override;
			void addView(const std::shared_ptr<View>& view) TITANIUM_NOEXCEPT override;
			void removeView(const std::shared_ptr<View>& view) TITANIUM_NOEXCEPT override;

			virtual void set_currentPage(const std::uint32_t& page) TITANIUM_NOEXCEPT override;

		private:
			Windows::UI::Xaml::Controls::ScrollViewer^ scroll_viewer__;
			JSObject contentView__;

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_SCROLLABLEVIEW_HPP_