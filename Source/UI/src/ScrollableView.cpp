/**
 * Titanium.UI.ScrollableView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/ScrollableView.hpp"
#include "TitaniumWindows/UI/View.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml::Controls;

		ScrollableViewLayoutDelegate::ScrollableViewLayoutDelegate(ScrollableView* scrollable_view) TITANIUM_NOEXCEPT
			: WindowsViewLayoutDelegate()
			, scrollable_view__(scrollable_view)
		{

		}

		void ScrollableViewLayoutDelegate::onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect)
		{
			WindowsViewLayoutDelegate::onComponentSizeChange(rect);

			const auto contentLayout = scrollable_view__->getContentViewLayoutDelegate();
			const auto content = contentLayout->getComponent();

			const auto scrollableViewLayout = scrollable_view__->getViewLayoutDelegate<WindowsViewLayoutDelegate>();

			const auto views = scrollable_view__->get_views();

			// adjust content view size
			content->Width = scrollableViewLayout->getComponent()->Width * views.size();
		}

		void ScrollableView::set_views(const std::vector<std::shared_ptr<View>>& views) TITANIUM_NOEXCEPT
		{
			const auto layout = getContentViewLayoutDelegate();

			// remove existing views
			for (auto view : get_views()) {
				layout->remove(view);
			}

			// update views
			Titanium::UI::ScrollableView::set_views(views);

			for (auto view : views) {
				layout->add(view);
			}
		}

		void ScrollableView::addView(const std::shared_ptr<View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollableView::addView(view);
			getContentViewLayoutDelegate()->add(view);
		}

		void ScrollableView::removeView(const std::shared_ptr<View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollableView::removeView(view);
			getContentViewLayoutDelegate()->remove(view);
		}

		std::shared_ptr<WindowsViewLayoutDelegate> ScrollableView::getContentViewLayoutDelegate() 
		{
			const auto content = contentView__.GetPrivate<TitaniumWindows::UI::View>();
			return content->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
		}

		void ScrollableView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
		{
			using namespace Windows::UI::Xaml::Controls;

			Titanium::UI::ScrollableView::postCallAsConstructor(js_context, arguments);

			scroll_viewer__ = ref new Windows::UI::Xaml::Controls::ScrollViewer();

			scroll_viewer__->HorizontalScrollBarVisibility = ScrollBarVisibility::Hidden;
			scroll_viewer__->VerticalScrollBarVisibility = ScrollBarVisibility::Hidden;
			scroll_viewer__->HorizontalScrollMode = ScrollMode::Auto;
			scroll_viewer__->VerticalScrollMode = ScrollMode::Disabled;

			contentView__.SetProperty("layout", get_context().CreateString("horizontal"));
			contentView__.SetProperty("top", get_context().CreateNumber(0));
			contentView__.SetProperty("left", get_context().CreateNumber(0));
			contentView__.SetProperty("width", get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)));
			contentView__.SetProperty("height", get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)));

			auto content = contentView__.GetPrivate<TitaniumWindows::UI::View>();
			scroll_viewer__->Content = content->getComponent();

			Titanium::UI::ScrollableView::setLayoutDelegate<ScrollableViewLayoutDelegate>(this);

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate->setComponent(scroll_viewer__);

			auto contentLayoutDelegate = getContentViewLayoutDelegate();

			auto nativeChildView = content->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), contentLayoutDelegate->getLayoutNode());
				if (layoutDelegate->isLoaded()) {
					layoutDelegate->requestLayout();
				}
			} else {
				TITANIUM_LOG_WARN("ScrollableView: nativeChildView = nullptr");
			}
		}

		void ScrollableView::set_currentPage(const std::uint32_t& page) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollableView::set_currentPage(page);

			scroll_viewer__->ChangeView(
			ref new Platform::Box<double>(currentPage__ * getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent()->Width),
			ref new Platform::Box<double>(0),
			nullptr,
			false);
		}

		ScrollableView::ScrollableView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::ScrollableView(js_context)
			, contentView__(get_context().CreateObject(JSExport<TitaniumWindows::UI::View>::Class()).CallAsConstructor())
		{
			TITANIUM_LOG_DEBUG("ScrollableView::ctor Initialize");
		}

		void ScrollableView::JSExportInitialize() 
		{
			JSExport<ScrollableView>::SetClassVersion(1);
			JSExport<ScrollableView>::SetParent(JSExport<Titanium::UI::ScrollableView>::Class());
		}

	}  // namespace UI
}  // namespace TitaniumWindows