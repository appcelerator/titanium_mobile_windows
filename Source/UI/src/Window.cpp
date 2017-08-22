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
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/Windows/CommandBar.hpp"
#include "TitaniumWindows/UI/Tab.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"
#include "Titanium/UI/OpenWindowParams.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::Foundation;
		using namespace Windows::UI::Core;

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

#if defined(IS_WINDOWS_10)
			const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			rootFrame->Navigated += ref new Windows::UI::Xaml::Navigation::NavigatedEventHandler([this](Platform::Object^, Windows::UI::Xaml::Navigation::NavigationEventArgs^) {
				try {
					// Resizing Window should be available only on Windows 10 Store App
					if (!IS_WINDOWS_MOBILE) {
						updateWindowSize();
					}
					// Update back button visibility. Note that back button is available on Store App too.
					SystemNavigationManager::GetForCurrentView()->AppViewBackButtonVisibility = AppViewBackButtonVisibility::Visible;
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error at root frame Navigated");
				}
			});
			rootFrame->SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler([this](Platform::Object^, Windows::UI::Xaml::SizeChangedEventArgs^) {
				try {
					if (!IS_WINDOWS_MOBILE) {
						const auto children = get_children();
						for (const auto child : children) {
							const auto layout = child->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
							if (layout) {
								layout->requestLayout(true);
							}
						}
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error at root frame SizeChanged");
				}
			});
#endif

#if defined(IS_WINDOWS_10) || defined(IS_WINDOWS_PHONE)
			// Setup back button press event
			static std::once_flag of;
			std::call_once(of, [this]() {
#if defined(IS_WINDOWS_10)
				SystemNavigationManager::GetForCurrentView()->BackRequested += ref new EventHandler<BackRequestedEventArgs^>([](Platform::Object^ sender, BackRequestedEventArgs^ e) {
#elif defined(IS_WINDOWS_PHONE)
				using namespace Windows::Phone::UI::Input;
				backpressed_event__ = HardwareButtons::BackPressed += ref new EventHandler<BackPressedEventArgs^>([](Platform::Object ^sender, BackPressedEventArgs ^e) {
#endif
					try {
						if (TitaniumWindows::UI::Window::window_stack__.size() > 0) {
							// Issue back event on the top window
							const auto top_window = TitaniumWindows::UI::Window::window_stack__.back();

							// For backward complatibility, we fires "windows:back" as well as "back".
							top_window->fireEvent("windows:back");
							top_window->fireEvent("back");

							top_window->close(nullptr);
						}
						e->Handled = true;
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at BackRequested");
					}
				});
			});	
#endif
	}

		Window::~Window() 
		{
#if defined(IS_WINDOWS_PHONE)
			if (canvas__) {
				Windows::Phone::UI::Input::HardwareButtons::BackPressed -= backpressed_event__;
			}
#endif
		}

#if !defined(IS_WINDOWS_PHONE)
		void Window::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Window::set_title(title);
			const auto view = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();
			if (view) {
				view->Title = TitaniumWindows::Utility::ConvertUTF8String(title);
			}
		}
#endif

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

			SetActiveTabWindow(get_object().GetPrivate<Window>());

			// Xaml Canvas doesn't actually fire GotFocus. Let's fire Ti event manually
			fireEvent("focus");
		}

		void Window::SetActiveTabWindow(const std::shared_ptr<TitaniumWindows::UI::Window>& window)
		{
			// Tracking Window of active Tab
			if (window->tab__) {
				// Current Window of active Tab will be always on top of the stack
				if (window_stack__.size() > 0) {
					const auto top_window = std::dynamic_pointer_cast<Window>(window_stack__.back());
					if (top_window->tab__) {
						window_stack__.pop_back();
					}
				}
				window_stack__.push_back(window);
			}
		}

		void Window::close(const std::shared_ptr<Titanium::UI::CloseWindowParams>& params) TITANIUM_NOEXCEPT
		{
			if (!restarting__) {
				// Fire blur & close event on this window
				blur();
				fireEvent("close");
			}

			// disable all events further because it doesn't make sense.
			disableEvents();

			bool is_last_window = false;
			if (tab__) {
				const auto tab = std::dynamic_pointer_cast<Tab>(tab__);
				tab->closeWindow(get_object().GetPrivate<Window>());
				is_last_window = tab->isLastWindow();
				tab__ = nullptr;
			}

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
						TITANIUM_LOG_WARN("Window.close: Window is not opened or already closed");
					}

				} else {
					window_stack__.pop_back();
					auto next_window = std::dynamic_pointer_cast<Window>(window_stack__.back());
					if (next_window->tab__) {
						const auto tab = next_window;
						window_stack__.pop_back();
						next_window = std::dynamic_pointer_cast<Window>(window_stack__.back());
						tab->open(nullptr);
					}

					if (is_last_window) {
						ExitApp(get_context());
						return;
					} else {
						const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
						rootFrame->GoBack();

						try {
							rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
							auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
							page->Content = next_window->getComponent();
						} catch (Platform::Exception^ e) {
							// This may happen when current window is not actually opened yet. In this case we just can skip it.
							// TODO: Is there any way to avoid this exception by checking if page content is valid?
							TITANIUM_LOG_ERROR("Window.close: failed to set content for the new Window");
						}
					}

					// start accepting events for the new Window
					next_window->enableEvents();
					next_window->focus();
					next_window->set_fullscreen(next_window->get_fullscreen());
				}

				Titanium::UI::Window::close(params);
			} else if (is_top_window) {
				ExitApp(get_context());
			}
		}

		void Window::ExitApp(const JSContext& js_context) 
		{
			window_stack__.clear();

			if (restarting__) {
				try {
					const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
					if (rootFrame->CanGoBack) {
						rootFrame->GoBack();
					}
					rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
					auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
					page->Content = ref new Windows::UI::Xaml::Controls::Canvas();
				} catch (Platform::Exception^ e) {
					TITANIUM_LOG_ERROR("Window.close: failed to set content for the new Window");
				}
				return;
			}

			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());
			JSObject Titanium = static_cast<JSObject>(Titanium_property);
			JSValue App_property = Titanium.GetProperty("App");
			TITANIUM_ASSERT(App_property.IsObject());
			std::shared_ptr<Titanium::AppModule> App = static_cast<JSObject>(App_property).GetPrivate<Titanium::AppModule>();

			// fire pause events
			App->fireEvent("pause");
			App->fireEvent("paused");

			TitaniumWindows::LogForwarder::done__ = true;

			// exit the app because there's no window to navigate back
			Windows::UI::Xaml::Application::Current->Exit();
		}

#if defined(IS_WINDOWS_10)
		void Window::updateWindowSize() TITANIUM_NOEXCEPT
		{
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
		}
#endif

		void Window::open(const std::shared_ptr<Titanium::UI::OpenWindowParams>& params) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Window::open(params);

			if (tab__) {
				const auto tab = std::dynamic_pointer_cast<Tab>(tab__);
				tab->openWindow(get_object().GetPrivate<Window>());
			} else {
				auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
				rootFrame->Navigate(Windows::UI::Xaml::Controls::Page::typeid);
				auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
				page->Content = canvas__;
			}

			if (params) {
				set_fullscreen(params->get_fullscreen());
			} else {
				set_fullscreen(get_fullscreen());
			}

			if (window_stack__.size() > 0) {
				// Fire blur on the last window
				auto lastwin = std::dynamic_pointer_cast<Window>(window_stack__.back());
				lastwin->blur();

				// disable all events further for the old Window
				lastwin->disableEvents();
			}

			// Tab.open should not increase window stack. Tab.focus event does it instead.
			if (tab__ == nullptr) {
				window_stack__.push_back(this->get_object().GetPrivate<Window>());
			}

			// start accepting events
			enableEvents();

			// Fire open event on this window
			fireEvent("open");

			// Fire focus event on this window
			focus();
		}

		void Window::set_orientationModes(const std::vector<Titanium::UI::ORIENTATION>& modes) TITANIUM_NOEXCEPT
		{
			Windows::Graphics::Display::DisplayOrientations orientations = Windows::Graphics::Display::DisplayOrientations::None;
			for (const auto mode : modes) {
				switch (mode) {
				case Titanium::UI::ORIENTATION::LANDSCAPE_LEFT:  /* home button on left */
					orientations = orientations | Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped;
					break;
				case Titanium::UI::ORIENTATION::LANDSCAPE_RIGHT: /* home button on right */
					orientations = orientations | Windows::Graphics::Display::DisplayOrientations::Landscape;
					break;
				case Titanium::UI::ORIENTATION::PORTRAIT:
					orientations = orientations | Windows::Graphics::Display::DisplayOrientations::Portrait;
					break;
				case Titanium::UI::ORIENTATION::UPSIDE_PORTRAIT:
					orientations = orientations | Windows::Graphics::Display::DisplayOrientations::PortraitFlipped;
					break;
				}
			}

			Windows::Graphics::Display::DisplayInformation::AutoRotationPreferences = orientations;
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
				if (ui_view) {
					ui_view->set_parent(this->get_object().GetPrivate<View>());
					layoutDelegate__->add(ui_view);
				} else {
					HAL::detail::ThrowRuntimeError("Window::add", "Window.add: Unable to get native view from View");
				}
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

			// fullscreen works for active Window only
			if (is_opened__) {
#if defined(IS_WINDOWS_PHONE)
				auto statusBar = Windows::UI::ViewManagement::StatusBar::GetForCurrentView();
				fullscreen ? statusBar->HideAsync() : statusBar->ShowAsync();
#elif defined(IS_WINDOWS_10)
				auto view = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();
				if (fullscreen) {
					if (view->TryEnterFullScreenMode()) {
						Windows::UI::ViewManagement::ApplicationView::PreferredLaunchWindowingMode = Windows::UI::ViewManagement::ApplicationViewWindowingMode::FullScreen;
					} else {
						TITANIUM_LOG_WARN("Unable to enter fullscreen mode");
					}
				} else {
					view->ExitFullScreenMode();
					Windows::UI::ViewManagement::ApplicationView::PreferredLaunchWindowingMode = Windows::UI::ViewManagement::ApplicationViewWindowingMode::Auto;
				}
#endif
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
