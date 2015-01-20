/**
 * Titanium.UI.Window for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Window.hpp"
#include "TitaniumWindows/UI/View.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		Window::Window(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : Titanium::UI::Window(js_context, arguments),
		      canvas__(ref new Windows::UI::Xaml::Controls::Canvas())
		{
			setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

			setComponent(canvas__);
			TITANIUM_LOG_DEBUG("Window::ctor CallAsConstructor");
		}

		Window::~Window()
		{
		}

		void Window::hide(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			getComponent()->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		}

		void Window::show(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			getComponent()->Visibility = Windows::UI::Xaml::Visibility::Visible;
		}

		void Window::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			auto nativeView = dynamic_cast<Windows::UI::Xaml::Controls::Panel ^>(getComponent());

			if (nativeView == nullptr) {
				TITANIUM_LOG_DEBUG("Window::add: nativeView = nullptr");
				return;
			}

			auto view_ptr = view.GetPrivate<Titanium::UI::View>();
			auto newView = std::dynamic_pointer_cast<TitaniumWindows::UI::ViewBase>(view_ptr);
			auto nativeChildView = newView->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeAddChild(layout_node_, newView->layout_node_);
				if (isLoaded()) {
					auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
					if (root) {
						Titanium::LayoutEngine::nodeLayout(root);
					}
				}

				canvas__->Children->Append(nativeChildView);
			} else {
				TITANIUM_LOG_DEBUG("Window::add: nativeChildView = nullptr");
			}
		}

		void Window::open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Window::open");

			auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
			auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
			page->Content = canvas__;
		}

		void Window::JSExportInitialize()
		{
			JSExport<Window>::SetClassVersion(1);
			JSExport<Window>::SetParent(JSExport<Titanium::UI::Window>::Class());
		}

		void Window::set_backgroundColor(const std::string& backgroundColorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_backgroundColor(backgroundColorName);
			const auto backgroundColor = ColorForName(backgroundColorName);
			canvas__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
		}

		void Window::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_bottom(bottom);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void Window::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_height(height);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
		}

		void Window::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_left(left);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void Window::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_layout(layout);
			setLayout(layout);
		}

		void Window::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_right(right);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void Window::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_top(top);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void Window::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_width(width);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
		}

		///////////////// Layout //////////////

		void Window::onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect)
		{
			if (layout_node_->parent) {
				ViewBase::onComponentSizeChange(rect);
				return;
			}

			layout_node_->element.measuredHeight = rect.height;
			layout_node_->element.measuredWidth = rect.width;
			auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
			if (root) {
				Titanium::LayoutEngine::nodeLayout(root);
			}

			// TODO: Check if EventPostLayout is set before creating this object
			/*
    Ti::Value val;
    val.setProperty("x", Ti::Value(rect.x));
    val.setProperty("y", Ti::Value(rect.y));
    val.setProperty("width", Ti::Value(rect.width));
    val.setProperty("height", Ti::Value(rect.height));
    fireEvent(Ti::Constants::EventPostLayout, val);
    */
		}

		void Window::onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name)
		{
			// We leave top level window alone unless the window is a child view
			if (layout_node_->parent) {
				ViewBase::onLayoutEngineCallback(rect, name);
				return;
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
