/**
* Titanium.UI.ScrollView for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/ScrollView.hpp"
#include "TitaniumWindows/UI/View.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		ScrollViewLayoutDelegate::ScrollViewLayoutDelegate(const std::shared_ptr<WindowsViewLayoutDelegate>& contentView) TITANIUM_NOEXCEPT
			: WindowsViewLayoutDelegate()
			, contentView__(contentView)
		{
		}
		
		void ScrollViewLayoutDelegate::add(const std::shared_ptr<Titanium::UI::View>& view) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ViewLayoutDelegate::add(view);
			contentView__->add(view);
		}

		void ScrollViewLayoutDelegate::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			contentView__->set_layout(layout);
		}

		void ScrollView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			using namespace Windows::UI::Xaml::Controls;
			
			Titanium::UI::ScrollView::postCallAsConstructor(js_context, arguments);	
			
			scroll_viewer__ = ref new Windows::UI::Xaml::Controls::ScrollViewer();

			scroll_viewer__->HorizontalScrollBarVisibility = ScrollBarVisibility::Auto;
			scroll_viewer__->VerticalScrollBarVisibility = ScrollBarVisibility::Auto;
			scroll_viewer__->HorizontalScrollMode = ScrollMode::Enabled;
			scroll_viewer__->VerticalScrollMode = ScrollMode::Enabled;

			contentView__.SetProperty("top", get_context().CreateNumber(0));
			contentView__.SetProperty("left", get_context().CreateNumber(0));
			contentView__.SetProperty("width", get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)));
			contentView__.SetProperty("height", get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)));

			auto content = contentView__.GetPrivate<TitaniumWindows::UI::View>();
			scroll_viewer__->Content = content->getComponent();

			Titanium::UI::ScrollView::setLayoutDelegate<ScrollViewLayoutDelegate>(content->getViewLayoutDelegate<WindowsViewLayoutDelegate>());

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<ScrollViewLayoutDelegate>()->setComponent(scroll_viewer__);

			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			auto nativeChildView = content->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), content->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getLayoutNode());
				if (layoutDelegate->isLoaded()) {
					layoutDelegate->requestLayout();
				}
			} else {
				TITANIUM_LOG_DEBUG("ScrollView::setupViewer: nativeChildView = nullptr");
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

		void ScrollView::scrollTo(double x, double y)
		{
			scroll_viewer__->ChangeView(
			    ref new Platform::Box<double>(x),
			    ref new Platform::Box<double>(y),
			    nullptr,
			    true /* disableAnimation: should we support scroll animation? */);
		}

		void ScrollView::scrollToBottom()
		{
			scroll_viewer__->ChangeView(nullptr, ref new Platform::Box<double>(scroll_viewer__->ScrollableHeight), nullptr);
		}

		std::string ScrollView::get_contentWidth() const
		{
			return static_cast<std::string>(contentView__.GetProperty("width"));
		}

		std::string ScrollView::get_contentHeight() const
		{
			return static_cast<std::string>(contentView__.GetProperty("height"));
		}

		bool ScrollView::set_contentWidth(const double& width)
		{
			auto content = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(contentView__.GetPrivate<Titanium::UI::View>());
			bool result = false;
			content->getComponent()->Width = width;
			contentView__.SetProperty("width", get_context().CreateNumber(width));
			result = true;
			return result;
		}

		bool ScrollView::set_contentHeight(const double& height)
		{
			auto content = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(contentView__.GetPrivate<Titanium::UI::View>());
			bool result = false;
			content->getComponent()->Height = height;
			contentView__.SetProperty("height", get_context().CreateNumber(height));
			result = true;
			return result;
		}

		bool ScrollView::get_scrollingEnabled() const TITANIUM_NOEXCEPT
		{
			return scroll_viewer__->HorizontalScrollMode != Windows::UI::Xaml::Controls::ScrollMode::Disabled;
		}

		bool ScrollView::set_scrollingEnabled(bool enabled) TITANIUM_NOEXCEPT
		{
			if (enabled) {
				scroll_viewer__->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Auto;
			} else {
				scroll_viewer__->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled;
			}
			return true;
		}

		bool ScrollView::get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return scroll_viewer__->HorizontalScrollBarVisibility != Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
		}

		bool ScrollView::set_showHorizontalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			if (enabled) {
				scroll_viewer__->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto;
			} else {
				scroll_viewer__->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
			}
			return true;
		}

		bool ScrollView::get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			return scroll_viewer__->VerticalScrollBarVisibility != Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
		}

		bool ScrollView::set_showVerticalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			if (enabled) {
				scroll_viewer__->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto;
			} else {
				scroll_viewer__->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
			}
			return true;
		}
	} // namespace UI
} // namespace TitaniumWindows
