/**
* TitaniumKit
*
* Copyright (c) 2017 by Axway. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUM_UI_NAVIGATIONWINDOW_HPP_
#define _TITANIUM_UI_NAVIGATIONWINDOW_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Window.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		@class

		@discussion This is the Titanium UI Window.

		See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Window
		*/
		class TITANIUMKIT_EXPORT NavigationWindow : public Titanium::UI::Window, public JSExport<NavigationWindow>
		{
		public:
			/*!
			  @method
			  @abstract closeWindow( [window] ) : void
			  @discussion Closes a window and removes it from the navigation window.
			  @param window Window to close.
			  @result void
			*/
			virtual void closeWindow(const std::shared_ptr<Window>& window) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract openWindow( [window] ) : void
			  @discussion Opens a window within the navigation window.
			  @param window Window to open.
			  @result void
			*/
			virtual void openWindow(const std::shared_ptr<Window>& window) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract title : String
			  @discussion Title of the window.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Window> , window);

			NavigationWindow(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~NavigationWindow() TITANIUM_NOEXCEPT = default;
			NavigationWindow(const NavigationWindow&) = default;
			NavigationWindow& operator=(const NavigationWindow&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			NavigationWindow(NavigationWindow&&) = default;
			NavigationWindow& operator=(NavigationWindow&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_FUNCTION_DEF(close);
			TITANIUM_FUNCTION_DEF(open);
			TITANIUM_FUNCTION_DEF(closeWindow);
			TITANIUM_FUNCTION_DEF(openWindow);

			TITANIUM_PROPERTY_DEF(window);
			TITANIUM_FUNCTION_DEF(getWindow);
			TITANIUM_FUNCTION_DEF(setWindow);

		protected:
			// Silence 4251 on Windows since private member variables do not
			// need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable : 4251)
			std::shared_ptr<Window> window__ { nullptr };
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_NAVIGATIONWINDOW_HPP_
