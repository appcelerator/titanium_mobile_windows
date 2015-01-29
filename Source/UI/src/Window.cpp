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
  			  TitaniumWindows::UI::ViewBase(js_context, arguments),
		      canvas__(ref new Windows::UI::Xaml::Controls::Canvas())
		{
			TITANIUM_LOG_DEBUG("Window::ctor");

			setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

			setComponent(canvas__);
		}

		Window::~Window()
		{
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
