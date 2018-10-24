/**
* TitaniumKit
*
* Copyright (c) 2017 by Axway. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "Titanium/UI/NavigationWindow.hpp"
#include "Titanium/UI/Window.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{

		NavigationWindow::NavigationWindow(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::Window(js_context, "Ti.UI.NavigationWindow")
		{
			TITANIUM_LOG_DEBUG("NavigationWindow:: ctor ", this);
		}

		TITANIUM_PROPERTY_READWRITE(NavigationWindow, std::shared_ptr<Window>, window);

		void NavigationWindow::closeWindow(const std::shared_ptr<Window>& window) TITANIUM_NOEXCEPT
		{
			window->close(nullptr);
		}

		void NavigationWindow::openWindow(const std::shared_ptr<Window>& window) TITANIUM_NOEXCEPT
		{
			window->open(nullptr);
		}

		void NavigationWindow::JSExportInitialize()
		{
			JSExport<NavigationWindow>::SetClassVersion(1);
			JSExport<NavigationWindow>::SetParent(JSExport<Titanium::UI::Window>::Class());
			TITANIUM_ADD_FUNCTION(NavigationWindow, closeWindow);
			TITANIUM_ADD_FUNCTION(NavigationWindow, openWindow);
			TITANIUM_ADD_FUNCTION(NavigationWindow, close);
			TITANIUM_ADD_FUNCTION(NavigationWindow, open);

			// property
			TITANIUM_ADD_PROPERTY(NavigationWindow, window);

			// accessors
			TITANIUM_ADD_FUNCTION(NavigationWindow, getWindow);
			TITANIUM_ADD_FUNCTION(NavigationWindow, setWindow);
		}

		TITANIUM_FUNCTION(NavigationWindow, closeWindow)
		{
			TITANIUM_ASSERT_AND_THROW(window__ != nullptr, "window parameter is not specified");
			ENSURE_OBJECT_AT_INDEX(window, 0);
			closeWindow(window.GetPrivate<Window>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(NavigationWindow, openWindow)
		{
			TITANIUM_ASSERT_AND_THROW(window__ != nullptr, "window parameter is not specified");
			ENSURE_OBJECT_AT_INDEX(window, 0);

			const auto window_ptr = window.GetPrivate<Window>();
			window_ptr->set_navigationWindow(get_object().GetPrivate<NavigationWindow>());
			openWindow(window_ptr);

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(NavigationWindow, close)
		{
			TITANIUM_ASSERT_AND_THROW(window__ != nullptr, "window parameter is not specified");
			if (window__) {
				auto window_object = window__->get_object();
				return window__->js_close(arguments, window_object);
			}

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(NavigationWindow, open)
		{
			TITANIUM_ASSERT_AND_THROW(window__ != nullptr, "window parameter is not specified");
			// Open root Window
			if (window__) {
				auto window_object = window__->get_object();
				return window__->js_open(arguments, window_object);
			}

			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(NavigationWindow, window)
		{
			if (window__) {
				return window__->get_object();
			}
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_SETTER(NavigationWindow, window)
		{
			if (argument.IsObject()) {
				const auto window_ptr = static_cast<JSObject>(argument).GetPrivate<Window>();
				window_ptr->set_navigationWindow(get_object().GetPrivate<NavigationWindow>());
				set_window(window_ptr);
			}
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(NavigationWindow, getWindow, window);
		TITANIUM_FUNCTION_AS_SETTER(NavigationWindow, setWindow, window);

	} // namespace UI
}  // namespace Titanium
