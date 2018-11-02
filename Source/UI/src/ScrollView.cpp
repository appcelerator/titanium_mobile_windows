/**
* Titanium.UI.ScrollView for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/ScrollView.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"

using namespace Windows::UI::Xaml;

namespace TitaniumWindows
{
	namespace UI
	{
		ScrollViewLayoutDelegate::ScrollViewLayoutDelegate(ScrollView* scrollview, const JSObject& contentView) TITANIUM_NOEXCEPT
			: WindowsViewLayoutDelegate()
			, contentView__(contentView)
			, scrollview__(scrollview)
			, clickCallback__(CreateClickCallback(contentView))
		{
		}

		JSFunction ScrollViewLayoutDelegate::CreateClickCallback(const JSObject& contentView) TITANIUM_NOEXCEPT
		{
			const std::string script = R"JS(
                 this._ti_scrollview_click_event_source_ = e.source;
            )JS";
			return contentView.get_context().CreateFunction(script, {"e"});
		}

		void ScrollViewLayoutDelegate::requestLayout(const bool& fire_event)
		{
			WindowsViewLayoutDelegate::requestLayout(fire_event);

			// contentOffset should be updated *after* LayoutEngine did the layout.
			scrollview__->set_contentOffset(scrollview__->get_contentOffset());

			contentView__.GetPrivate<View>()->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->requestLayout(fire_event);
		}
		std::shared_ptr<Titanium::UI::View> ScrollViewLayoutDelegate::sourceTest(::Platform::Object ^ source, const std::shared_ptr<Titanium::UI::View>& root)
		{
			const auto sender = WindowsViewLayoutDelegate::sourceTest(source, root);
			if (sender) {
				return sender;
			}

			// ScrollViewer may return one of its child components for click event
			const auto grid = dynamic_cast<Controls::Grid ^>(source);
			if (grid) {
				for (unsigned int i = 0; i < grid->Children->Size; i++) {
					if (dynamic_cast<Controls::ScrollContentPresenter ^>(grid->Children->GetAt(i))) {
						return root;
					}				
				}
			}

			return nullptr;
		}


		
		void ScrollViewLayoutDelegate::add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::add(view);
			contentView__.GetPrivate<View>()->getViewLayoutDelegate()->add(view);

			view->addEventListener("click", clickCallback__, contentView__);

			requestLayout(false);
		}

		void ScrollViewLayoutDelegate::removeAllChildren() TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::removeAllChildren();
			contentView__.GetPrivate<View>()->getViewLayoutDelegate()->removeAllChildren();
			requestLayout(false);
		}

		void ScrollViewLayoutDelegate::remove(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::remove(view);
			contentView__.GetPrivate<View>()->getViewLayoutDelegate()->remove(view);
			requestLayout(false);
		}

		void ScrollViewLayoutDelegate::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			contentView__.GetPrivate<View>()->getViewLayoutDelegate()->set_layout(layout);
		}

		void ScrollView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			using namespace Windows::UI::Xaml::Controls;
			
			Titanium::UI::ScrollView::postCallAsConstructor(js_context, arguments);	
			
			scroll_viewer__ = ref new Windows::UI::Xaml::Controls::ScrollViewer();

			scroll_viewer__->HorizontalScrollBarVisibility = ScrollBarVisibility::Auto;
			scroll_viewer__->VerticalScrollBarVisibility = ScrollBarVisibility::Visible;
			scroll_viewer__->HorizontalScrollMode = ScrollMode::Enabled;
			scroll_viewer__->VerticalScrollMode = ScrollMode::Enabled;

			contentView__.SetProperty("top", get_context().CreateNumber(0));
			contentView__.SetProperty("left", get_context().CreateNumber(0));
			contentView__.SetProperty("width", get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)));
			contentView__.SetProperty("height", get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)));

			auto content = contentView__.GetPrivate<TitaniumWindows::UI::View>();
			scroll_viewer__->SizeChanged += ref new SizeChangedEventHandler([this, content](Platform::Object^ sender, SizeChangedEventArgs^ e) {
				const auto component = content->getComponent();
				component->MinHeight = e->NewSize.Height;
				component->MinWidth  = e->NewSize.Width;
			});
			scroll_viewer__->Content = content->getComponent();

			Titanium::UI::ScrollView::setLayoutDelegate<ScrollViewLayoutDelegate>(this, contentView__);

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			border__ = ref new Windows::UI::Xaml::Controls::Border();
			border__->Child = scroll_viewer__;

			getViewLayoutDelegate<ScrollViewLayoutDelegate>()->setComponent(border__, nullptr, border__);

			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate->setStyleComponent(scroll_viewer__);
			auto nativeChildView = content->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), content->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getLayoutNode());
				if (layoutDelegate->isLoaded()) {
					layoutDelegate->requestLayout();
				}
			} else {
				TITANIUM_LOG_WARN("ScrollView: nativeChildView = nullptr");
			}
		}

		ScrollView::ScrollView(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::ScrollView(js_context),
		      contentView__(get_context().CreateObject(JSExport<TitaniumWindows::UI::View>::Class()).CallAsConstructor())
		{
		}

		void ScrollView::JSExportInitialize()
		{
			JSExport<ScrollView>::SetClassVersion(1);
			JSExport<ScrollView>::SetParent(JSExport<Titanium::UI::ScrollView>::Class());
		}

		void ScrollView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			getViewLayoutDelegate<ScrollViewLayoutDelegate>()->filterEvents({ "click" });

			Titanium::UI::ScrollView::enableEvent(event_name);

			if (event_name == "click") {
				click_event__ = scroll_viewer__->Tapped += ref new Windows::UI::Xaml::Input::TappedEventHandler(
					[this](Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e) {
					try {
						const auto ctx = get_context();
						const auto scroll_viewer = safe_cast<Windows::UI::Xaml::Controls::ScrollViewer^>(sender);
						auto eventArgs = ctx.CreateObject();

						// special property that saves latest click event source
						const std::string source_property_name = "_ti_scrollview_click_event_source_";
						const auto source = contentView__.GetProperty(source_property_name);
						if (source.IsUndefined()) {
							eventArgs.SetProperty("source", get_object());
						} else {
							eventArgs.SetProperty("source", source);
						}

						fireEvent("click", eventArgs);

						// reset latest click event source
						contentView__.SetProperty(source_property_name, ctx.CreateUndefined());
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at ScrollView.click");
					}
				});
			} else if (event_name == "dragend" || event_name == "dragEnd") {
				dragend_event__ = scroll_viewer__->PointerReleased += ref new Windows::UI::Xaml::Input::PointerEventHandler(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e) {
						fireEvent(event_name);
					}
				);
			} else if (event_name == "dragstart" || event_name == "dragStart") {
				dragstart_event__ = scroll_viewer__->PointerPressed += ref new Windows::UI::Xaml::Input::PointerEventHandler(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e) {
						fireEvent(event_name);
					}
				);
			} else if (event_name == "scale") {
				scale_event__ = scroll_viewer__->ViewChanging += ref new Windows::Foundation::EventHandler<Windows::UI::Xaml::Controls::ScrollViewerViewChangingEventArgs ^>(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangingEventArgs ^args) {
					try {
						auto eventArgs = get_context().CreateObject();
						auto scale = args->FinalView->ZoomFactor;
						eventArgs.SetProperty("scale", get_context().CreateNumber(scale));
						fireEvent("scale", eventArgs);
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at ScrollView.scale");
					}
				});
			} else if (event_name == "scroll") {
				scroll_event__ = scroll_viewer__->ViewChanging += ref new Windows::Foundation::EventHandler<Windows::UI::Xaml::Controls::ScrollViewerViewChangingEventArgs ^>(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangingEventArgs ^args) {
					try {
						const auto ctx = get_context();
						auto eventArgs = ctx.CreateObject();
						auto dragging = args->FinalView->HorizontalOffset != 0 || args->FinalView->VerticalOffset != 0;
						auto zoom = args->FinalView->ZoomFactor;
						auto zooming = zoom != 1;

						eventArgs.SetProperty("x", ctx.CreateNumber(args->FinalView->HorizontalOffset));
						eventArgs.SetProperty("y", ctx.CreateNumber(args->FinalView->VerticalOffset));
						eventArgs.SetProperty("dragging", ctx.CreateBoolean(dragging)); // test this
						eventArgs.SetProperty("zooming", ctx.CreateBoolean(zooming)); // test this
						eventArgs.SetProperty("curZoomScale", ctx.CreateNumber(zoom));
						fireEvent("scroll", eventArgs);
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at ScrollView.scroll");
					}
				});
			} else if (event_name == "scrollend" || event_name == "scrollEnd") {
				scrollend_event__ = scroll_viewer__->ViewChanged += ref new Windows::Foundation::EventHandler<Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs ^>(
					[=](Platform::Object ^sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs ^args) {
						fireEvent(event_name);
					}
				);
			}
		}

		void ScrollView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollView::disableEvent(event_name);

			if (event_name == "dragend" || event_name == "dragEnd") {
				scroll_viewer__->PointerReleased -= dragend_event__;
			} else if (event_name == "dragstart" || event_name == "dragStart") {
				scroll_viewer__->PointerPressed -= dragstart_event__;
			} else if (event_name == "scale") {
				scroll_viewer__->ViewChanging -= scale_event__;
			} else if (event_name == "scroll") {
				scroll_viewer__->ViewChanging -= scroll_event__;
			} else if (event_name == "scrollend" || event_name == "scrollEnd") {
				scroll_viewer__->ViewChanged -= scrollend_event__;
			}
		}

		void ScrollView::scrollTo(const double& x, const double& y) TITANIUM_NOEXCEPT
		{
			scroll_viewer__->ChangeView(
				ref new Platform::Box<double>(x),
				ref new Platform::Box<double>(y),
				nullptr,
				true);
		}

		void ScrollView::scrollToBottom() TITANIUM_NOEXCEPT
		{
			scroll_viewer__->ChangeView(
				ref new Platform::Box<double>(0),
				ref new Platform::Box<double>(scroll_viewer__->ScrollableHeight),
				nullptr,
				true);
		}

		void ScrollView::scrollToTop() TITANIUM_NOEXCEPT
		{
			scroll_viewer__->ChangeView(
				ref new Platform::Box<double>(0),
				ref new Platform::Box<double>(0),
				nullptr,
				true);
		}

		std::string ScrollView::get_contentWidth() const TITANIUM_NOEXCEPT
		{
			return static_cast<std::string>(contentView__.GetProperty("width"));
		}

		std::string ScrollView::get_contentHeight() const TITANIUM_NOEXCEPT
		{
			return static_cast<std::string>(contentView__.GetProperty("height"));
		}

		void ScrollView::set_contentWidth(const std::string& width_) TITANIUM_NOEXCEPT
		{
			// "auto" is deprecated, we should use SIZE here
			std::string width;
			if (width_ == "auto") {
				width = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE);
			}
			else {
				width = width_;
			}
			Titanium::UI::ScrollView::set_contentWidth(width);
			contentView__.SetProperty("width", get_context().CreateString(width));
		}

		void ScrollView::set_contentHeight(const std::string& height_) TITANIUM_NOEXCEPT
		{
			// "auto" is deprecated, we should use SIZE here
			std::string height;
			if (height_ == "auto") {
				height = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE);
			} else {
				height = height_;
			}
			Titanium::UI::ScrollView::set_contentHeight(height);
			contentView__.SetProperty("height", get_context().CreateString(height));
		}

		bool ScrollView::get_scrollingEnabled() const TITANIUM_NOEXCEPT
		{
			return scroll_viewer__ && scroll_viewer__->HorizontalScrollMode != Windows::UI::Xaml::Controls::ScrollMode::Disabled;
		}

		void ScrollView::set_scrollingEnabled(const bool& enabled) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollView::set_scrollingEnabled(enabled);
			if (enabled) {
				scroll_viewer__->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Auto;
			} else {
				scroll_viewer__->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled;
			}
		}

		bool ScrollView::get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return scroll_viewer__ && scroll_viewer__->HorizontalScrollBarVisibility != Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
		}

		void ScrollView::set_showHorizontalScrollIndicator(const bool& enabled) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollView::set_showHorizontalScrollIndicator(enabled);
			if (enabled) {
				scroll_viewer__->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto;
			} else {
				scroll_viewer__->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
			}
		}

		bool ScrollView::get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return scroll_viewer__ && scroll_viewer__->VerticalScrollBarVisibility != Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
		}

		void ScrollView::set_showVerticalScrollIndicator(const bool& enabled) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollView::set_showVerticalScrollIndicator(enabled);
			if (enabled) {
				scroll_viewer__->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto;
			} else {
				scroll_viewer__->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
			}
		}

		void ScrollView::set_contentOffset(const Titanium::UI::Point& offset) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ScrollView::set_contentOffset(offset);
			scrollTo(Titanium::UI::get_Point_value(offset.x), Titanium::UI::get_Point_value(offset.y));
		}
	} // namespace UI
} // namespace TitaniumWindows
