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

			border__ = ref new Windows::UI::Xaml::Controls::Border();
			border__->Child = scroll_viewer__;

			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate->setStyleComponent(scroll_viewer__);
			layoutDelegate->setComponent(border__, nullptr, border__);

			scroll_viewer__->ViewChanged += ref new Windows::Foundation::EventHandler<Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs ^>(
				[this](Platform::Object ^sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs ^args) {
				currentPage__ = static_cast<std::uint32_t>(scroll_viewer__->HorizontalOffset / getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent()->Width);
			});

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

		void ScrollableView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollableView::enableEvent(event_name);

			if (event_name == "dragend") {
				dragend_event__ = scroll_viewer__->PointerReleased += ref new Windows::UI::Xaml::Input::PointerEventHandler(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e) {
						auto eventArgs = get_context().CreateObject();
						eventArgs.SetProperty("currentPage", get_context().CreateNumber(get_currentPage()));
						eventArgs.SetProperty("view", get_object());
						fireEvent("dragend", eventArgs);
					}
				);
			} else if (event_name == "dragstart") {
				dragstart_event__ = scroll_viewer__->PointerPressed += ref new Windows::UI::Xaml::Input::PointerEventHandler(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e) {
						fireEvent("dragstart");
					}
				);
			} else if (event_name == "scroll") {
				scroll_event__ = scroll_viewer__->ViewChanging += ref new Windows::Foundation::EventHandler<Windows::UI::Xaml::Controls::ScrollViewerViewChangingEventArgs ^>(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangingEventArgs ^args) {
						auto eventArgs = get_context().CreateObject();
						eventArgs.SetProperty("currentPage", get_context().CreateNumber(get_currentPage()));
						float currentPageAsFloat = get_currentPage() + static_cast<float>(scroll_viewer__->HorizontalOffset / scroll_viewer__->Width);
						eventArgs.SetProperty("currentPageAsFloat", get_context().CreateNumber(currentPageAsFloat));
						fireEvent("scroll", eventArgs);
					}
				);
			} else if (event_name == "scrollend") {
				scrollend_event__ = scroll_viewer__->ViewChanged += ref new Windows::Foundation::EventHandler<Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs ^>(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs ^args) {
						auto eventArgs = get_context().CreateObject();
						eventArgs.SetProperty("currentPage", get_context().CreateNumber(get_currentPage()));
						eventArgs.SetProperty("view", get_object());
						fireEvent("scrollend", eventArgs);
					}
				);
			}
		}

		void ScrollableView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollableView::disableEvent(event_name);

			if (event_name == "dragend") {
				scroll_viewer__->PointerReleased -= dragend_event__;
			} else if (event_name == "dragstart") {
				scroll_viewer__->PointerPressed -= dragstart_event__;
			} else if (event_name == "scroll") {
				scroll_viewer__->ViewChanging -= scroll_event__;
			} else if (event_name == "scrollend") {
				scroll_viewer__->ViewChanged -= scrollend_event__;
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

		void ScrollableView::set_scrollingEnabled(const bool& scrollingEnabled) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollableView::set_scrollingEnabled(scrollingEnabled);

			if (scrollingEnabled) {
				scroll_viewer__->HorizontalScrollMode = ScrollMode::Auto;
			} else {
				scroll_viewer__->HorizontalScrollMode = ScrollMode::Disabled;
			}
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