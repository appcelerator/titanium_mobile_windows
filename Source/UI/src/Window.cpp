/**
 * Titanium.UI.Window for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Window.hpp"
#include "Titanium/App.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UIModule.hpp"
#include <windows.h>
#include "TitaniumWindows/WindowsMacros.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/Windows/CommandBar.hpp"
#include "TitaniumWindows/UI/Tab.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::Foundation;

		std::vector<std::shared_ptr<Window>> Window::window_stack__;

		Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
  			: Titanium::UI::Window(js_context)
		{
		}

		void Window::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Window::postCallAsConstructor(js_context, arguments);	
			
			canvas__ = ref new Windows::UI::Xaml::Controls::Canvas();

			Titanium::UI::Window::setLayoutDelegate<WindowLayoutDelegate>();

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);

			// Window is considered as "root" of the view and it doesn't support border.
			// Don't set Border to Xaml Frame content, otherwise you'll see runtime exception.
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(canvas__, nullptr, false);

			const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			rootFrame->Navigated += ref new Windows::UI::Xaml::Navigation::NavigatedEventHandler([this](Platform::Object^, Windows::UI::Xaml::Navigation::NavigationEventArgs^) {
				updateWindowSize();
			});

#if defined(IS_WINDOWS_PHONE)
			using namespace Windows::Phone::UI::Input;

			backpressed_event__ = HardwareButtons::BackPressed += ref new EventHandler<BackPressedEventArgs^>([this](Platform::Object ^sender, BackPressedEventArgs ^e) {
				if (is_window_event_active__) {
					// close current window when there's no back button listener
					if (is_custom_backpress_event__) {
						fireEvent("windows:back");
					} else {
						close(nullptr);
					}
					e->Handled = true;
				}
			});
#endif
		}

		Window::~Window() 
		{
#if defined(IS_WINDOWS_PHONE)
			Windows::Phone::UI::Input::HardwareButtons::BackPressed -= backpressed_event__;
#endif
		}

		void Window::updateWindowsCommandBar(const std::shared_ptr<TitaniumWindows::UI::WindowsXaml::CommandBar>& commandbar)
		{
			const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			const auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
			if (page) {
				if (commandbar) {
					page->BottomAppBar = commandbar->getComponent();
				} else {
					page->BottomAppBar = nullptr;
				}
			}
		}

		std::shared_ptr<TitaniumWindows::UI::WindowsXaml::CommandBar> Window::getBottomAppBar() TITANIUM_NOEXCEPT
		{
			// if this Window is parent container of TabGroup,
			// let's get CommandBar from active Tab.
			if (isTabGroupContainer()) {
				const auto Ti = static_cast<JSObject>(get_context().get_global_object().GetProperty("Titanium"));
				const auto UI = static_cast<JSObject>(Ti.GetProperty("UI")).GetPrivate<Titanium::UIModule>();
				const auto tab = UI->get_currentTab();
				if (tab != nullptr) {
					const auto activeTab = dynamic_cast<TitaniumWindows::UI::Tab*>(tab.get());
					TITANIUM_ASSERT(activeTab != nullptr);
					const auto win = activeTab->get_window();
					if (win != nullptr) {
						const auto tabWindow = dynamic_cast<TitaniumWindows::UI::Window*>(win.get());
						TITANIUM_ASSERT(tabWindow != nullptr);
						return tabWindow->getBottomAppBar();
					}
				}
			}

			return bottomAppBar__;
		}

		void Window::blur() 
		{
			// Xaml Canvas doesn't actually fire LostFocus. Let's fire Ti event manually
			fireEvent("blur");
			updateWindowsCommandBar(nullptr);
		}

		void Window::focus() 
		{
			updateWindowsCommandBar(getBottomAppBar());
			// Xaml Canvas doesn't actually fire GotFocus. Let's fire Ti event manually
			fireEvent("focus");
		}

		void Window::close(const std::shared_ptr<Titanium::UI::CloseWindowParams>& params) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Window::close(params);

			// Fire blur & close event on this window
			blur();
			fireEvent("close");

			// disable all events further because it doesn't make sense.
			disableEvents();

			const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			const auto top_window = window_stack__.back();
			const auto is_top_window = (top_window.get() == this); // check if window.close has been issued onto the top window

			if (!get_exitOnClose() && window_stack__.size() > 1) {

				// Check if stack-top is not a current Window.
				// This usually means new windows is opened before current windows is closed,
				// or user explicitly closes a window which is not on top.
				// In this case we don't want to GoBack().
				if (!is_top_window) {

					// Iterate over the stack to search for shared_ptr for "this" because std::find does not work in this case.
					// Assuming this reasonable as we don't usually open too many windows...
					auto found = false;
					for (std::size_t i = 0; i < window_stack__.size(); i++) {
						const auto w = window_stack__.at(i);
						if (w.get() == this) {
							window_stack__.erase(window_stack__.begin() + i);
							found = true;
							break;
						}
					}

					if (!found) {
						TITANIUM_MODULE_LOG_WARN("Window.close: Window is not opened or already closed");
					}

				} else {
					window_stack__.pop_back();
					rootFrame->GoBack();
					
					const auto next_window = window_stack__.back();

					try {
						rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
						auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
						page->Content = next_window->getComponent();
					} catch (Platform::COMException^ e) {
						// This may happen when current window is not actually opened yet. In this case we just can skip it.
						// TODO: Is there any way to avoid this exception by checking if page content is valid?
						TITANIUM_LOG_ERROR("Window.close: failed to set content for the new Window");
					}

					// start accepting events for the new Window
					next_window->enableEvents();
					next_window->focus();
				}
			} else if (is_top_window) {
				JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
				TITANIUM_ASSERT(Titanium_property.IsObject());
				JSObject Titanium = static_cast<JSObject>(Titanium_property);
				JSValue App_property = Titanium.GetProperty("App");
				TITANIUM_ASSERT(App_property.IsObject());
				std::shared_ptr<Titanium::AppModule> App = static_cast<JSObject>(App_property).GetPrivate<Titanium::AppModule>();

				// fire pause events
				App->fireEvent("pause");
				App->fireEvent("paused");

				// exit the app because there's no window to navigate back
				window_stack__.clear();
				Windows::UI::Xaml::Application::Current->Exit();
			}
		}

		void Window::updateWindowSize() TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_10)
			const auto currentBounds = Windows::UI::Xaml::Window::Current->Bounds;

			const auto layout    = getViewLayoutDelegate();
			const auto strWidth  = layout->get_width();
			const auto strHeight = layout->get_height();

			// use current bounds if we don't get numeric size
			float width  = currentBounds.Width;
			float height = currentBounds.Height;

			if (!strWidth.empty() && std::all_of(strWidth.begin(), strWidth.end(), ::isdigit)) {
				width = std::stof(strWidth);
			}
			if (!strHeight.empty() && std::all_of(strHeight.begin(), strHeight.end(), ::isdigit)) {
				height = std::stof(strHeight);
			}

			// TryResizeView returns false when given size is too small/big. We don't have a way to get valid range here unfortunately.
			if (!Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->TryResizeView(Size(width, height))) {
				TITANIUM_LOG_WARN("Titanium::Window: Unable to resize root Window with size ", width, "x", height);
			}
#endif
		}

		void Window::open(const std::shared_ptr<Titanium::UI::OpenWindowParams>& params) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Window::open(params);

			auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
			auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
			page->Content = canvas__;

			if (window_stack__.size() > 0) {
				// Fire blur on the last window
				auto lastwin = window_stack__.back();
				lastwin->blur();

				// disable all events further for the old Window
				lastwin->disableEvents();
			}

			window_stack__.push_back(this->get_object().GetPrivate<Window>());

			// start accepting events
			enableEvents();

			// Fire open event on this window
			fireEvent("open");

			// Fire focus event on this window
			focus();
		}

		void Window::JSExportInitialize()
		{
			JSExport<Window>::SetClassVersion(1);
			JSExport<Window>::SetParent(JSExport<Titanium::UI::Window>::Class());
			TITANIUM_ADD_FUNCTION(Window, add);
		}

		TITANIUM_FUNCTION(Window, add) 
		{
			ENSURE_OBJECT_AT_INDEX(viewObj, 0);

			// handle view array
			if (viewObj.IsArray()) {
				auto js_views = static_cast<JSArray>(viewObj);
				auto views = static_cast<std::vector<JSValue>>(js_views);
				for (size_t i = 0; i < views.size(); i++) {
					auto view_obj = static_cast<JSObject>(views.at(i));
					add(view_obj);
				}
				return get_context().CreateUndefined();
			}

			// check if it's command bar
			const auto commandBar = viewObj.GetPrivate<TitaniumWindows::UI::WindowsXaml::CommandBar>();
			if (commandBar == nullptr) {
				// delegate to parent
				auto ui_view = viewObj.GetPrivate<Titanium::UI::View>();
				if (ui_view == nullptr) {
					ui_view = layoutDelegate__->rescueGetView(viewObj);
				}
				layoutDelegate__->add(ui_view);
				return get_context().CreateUndefined();
			}

			// TODO: assuming bottom bar here...but Windows app accepts both top and bottom.
			bottomAppBar__ = commandBar;

			const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			const auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
			if (page != nullptr) {
				page->BottomAppBar = commandBar->getComponent();
			}

			return get_context().CreateUndefined();
		}

		void Window::set_fullscreen(const bool& fullscreen) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Window::set_fullscreen(fullscreen);
#if defined(IS_WINDOWS_PHONE)
			auto statusBar = Windows::UI::ViewManagement::StatusBar::GetForCurrentView();
			fullscreen ? statusBar->HideAsync() : statusBar->ShowAsync();
#elif defined(IS_WINDOWS_10)
			auto view = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();
			fullscreen ? view->TryEnterFullScreenMode() : view->ExitFullScreenMode();
#endif
		}

		void Window::enableEvents() TITANIUM_NOEXCEPT
		{
			Titanium::Module::enableEvents();
			is_window_event_active__ = true;
		}

		void Window::disableEvents() TITANIUM_NOEXCEPT
		{
			Titanium::Module::disableEvents();
			is_window_event_active__ = false;
		}

		void Window::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Window::enableEvent(event_name);
			if (event_name == "windows:back") {
				is_custom_backpress_event__ = true;
			}
		}

		void Window::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Window::disableEvent(event_name);
			if (event_name == "windows:back") {
				is_custom_backpress_event__ = false;
			}
		}

		WindowLayoutDelegate::WindowLayoutDelegate() TITANIUM_NOEXCEPT
			: WindowsViewLayoutDelegate()
		{
			
		}

		void WindowLayoutDelegate::onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect)
		{
			if (layout_node__->parent) {
				WindowsViewLayoutDelegate::onComponentSizeChange(rect);
				return;
			}

			layout_node__->element.measuredHeight = rect.height;
			layout_node__->element.measuredWidth = rect.width;

			requestLayout(true);
		}

		void WindowLayoutDelegate::onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name)
		{
			// We leave top level window alone unless the window is a child view
			if (layout_node__->parent) {
				WindowsViewLayoutDelegate::onLayoutEngineCallback(rect, name);
				return;
			}
			oldRect__ = Titanium::LayoutEngine::RectMake(rect.x, rect.y, rect.width, rect.height);
		}
	} // namespace UI
} // namespace TitaniumWindows
