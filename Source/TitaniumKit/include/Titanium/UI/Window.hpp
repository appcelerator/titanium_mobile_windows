/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_WINDOW_HPP_
#define _TITANIUM_UI_WINDOW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/TitleAttributesParams.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		class OpenWindowParams;
		class CloseWindowParams;
		class Tab;

		/*!
		  @class

		  @discussion This is the Titanium UI Window.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Window
		*/
		class TITANIUMKIT_EXPORT Window : public View, public JSExport<Window>
		{
		public:
			/*!
			  @method

			  @abstract close( [params] ) : void

			  @discussion Closes the window.

			  @param params Animation or display properties to use when closing the window.

			  @result void
			*/
			virtual void close(const std::shared_ptr<CloseWindowParams>& params) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract open( [params] ) : void

			  @discussion Opens the window.

			  @param params Optimized animation or display properties to use
			  when opening the window. (openWindowParams)

			  @result void
			*/
			virtual void open(const std::shared_ptr<OpenWindowParams>& params) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract barColor : String

			  @discussion Background color for the nav bar, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, barColor);

			/*!
			  @method

			  @abstract exitOnClose : Boolean

			  @discussion Boolean value indicating if the application should exit when the Android Back button is pressed while the window is being shown or when the window is closed programmatically.

			  Starting in 3.4.2 you can set this property at any time. In earlier releases you can only set this as a createWindow({...}) option.

			  Default: true if this is the first window launched else false; prior to Release 3.3.0, the default was always false.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, exitOnClose);

			/*!
			  @method

			  @abstract extendEdges : Number[]

			  @discussion An array of supported values specified using the EXTEND_EDGE constants in Titanium.UI.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::unordered_set<EXTEND_EDGE>, extendEdges);

			/*!
			  @method

			  @abstract fullscreen : Boolean

			  @discussion Boolean value indicating if the window is fullscreen.

			  A fullscreen window occupies all of the screen space, hiding the status bar. Must be specified at creation time or in the options dictionary passed to the Window.open method.

			  On iOS the behavior of this property has changed. Starting from 3.1.3, if this property is undefined then the property is set to the value for UIStatusBarHidden defined in tiapp.xml. If that is not defined it is treated as explicit false. On earlier versions, opening a window with this property undefined would not effect the status bar appearance.

			  On Android, setting this property forces the creation of a heavyweight window before Titanium 3.2.0. See "Android Heavyweight and Lightweight Windows" in the main description of this class for more information.

			  Default: false
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, fullscreen);

			/*!
			  @method

			  @abstract hideShadow : Boolean

			  @discussion Set this to true to hide the shadow image of the navigation bar.

			  This property is only honored if a valid value is specified for the barImage property.

			  Default: false
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, hideShadow);

			/*!
			  @method

			  @abstract modal : Boolean

			  @discussion Indicates to open a modal window or not.

			  Set to true to create a modal window.

			  Must be specified at creation time or in the dictionary passed to the Window.open method.

			  In the user interface, a modal window is a window that blocks the main application UI until the modal window is dismissed. A modal window requires the user to interact with it to resume the normal flow of the application.

			  See the "Modal Windows" section for platform-specific information.

			  Default: false
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, modal);

			/*!
			  @method

			  @abstract navBarHidden : Boolean

			  @discussion Hides the nav bar (true) or shows the nav bar (false).

			  Must be specified at creation time or in the options dictionary passed to the Window.open method.

			  Android Platform Notes
			  Since Release 3.3.0, due to changes to support the appcompat library, this property has no effect. By default, the action bar is always displayed. To hide the action bar, see the Android Action Bar guide.

			  Prior to Release 3.2.0, setting this property forces the creation of a heavyweight window. See "Android Heavyweight and Lightweight Windows" in the main description of this class for more information. Setting this property to true disables the Action Bar since it is part of the navigation title bar.

			  iOS Platform Notes
			  Since Release 3.1.3, this is no longer a valid parameter passed to the Window.open method. Modal windows on iOS no longer have a navigation controller and hence do not have a nav bar.

			  Default: false
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, navBarHidden);

			/*!
			  @method

			  @abstract navTintColor : String

			  @discussion The tintColor to apply to the navigation bar. This property is applicable on iOS 7 and greater.

			  This property is a direct correspondant of the tintColor property of NavigationBar on iOS.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, navTintColor);

			/*!
			  @method

			  @abstract orientationModes : Number[]

			  @discussion Array of supported orientation modes, specified using the orientation constants defined in Titanium.UI.

			  Note: Using the orientationModes property to force the orientation of non-modal windows is considered a bad practice and will not be supported, including forcing the orientation of windows inside a NavigationWindow or TabGroup.

			  To restrict this window to a certain set of orientations, specify one or more of the orientation constants LANDSCAPE_LEFT, LANDSCAPE_RIGHT, PORTRAIT, UPSIDE_PORTRAIT.

			  orientationModes must be set before opening the window.

			  To determine the current orientation of the window, see Window.orientation. To determine the current orientation of the device, see Gesture.orientation. To be notified when the device's current orientation changes, add a listener for the Titanium.Gesture.orientationchange event.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<ORIENTATION>, orientationModes);

			/*!
			  @method

			  @abstract theme : String

			  @discussion Name of the theme to apply to the window.

			  Set the theme of the window. It can be either a built-in theme or a custom theme.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, theme);

			/*!
			  @method

			  @abstract titleAttributes : titleAttributesParams

			  @discussion Title text attributes of the window.

			  Use this property to specify the color, font and shadow attributes of the title.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TitleAttributesParams, titleAttributes);

			/*!
			@method

			@abstract title : String

			@discussion Title of the window.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);

			/*!
			@method

			@abstract titleid : String

			@discussion Key identifying a string from the locale file to use for the window title.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, titleid);

			/*!
			  @method

			  @abstract translucent : Boolean

			  @discussion Boolean value indicating if the nav bar is translucent.

			  Default: true on iOS7 and above, false otherwise.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, translucent);

			/*!
			@method

			@abstract tab : Tab

			@discussion Tab that attaches this Window
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Tab>, tab);


			Window(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Window() TITANIUM_NOEXCEPT;  //= default;
			Window(const Window&) = default;
			Window& operator=(const Window&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Window(Window&&) = default;
			Window& operator=(Window&&) = default;
#endif

			static void JSExportInitialize();

			static void Restart() TITANIUM_NOEXCEPT;

			TITANIUM_FUNCTION_DEF(close);
			TITANIUM_FUNCTION_DEF(open);

			TITANIUM_PROPERTY_DEF(barColor);
			TITANIUM_FUNCTION_DEF(getBarColor);
			TITANIUM_FUNCTION_DEF(setBarColor);

			TITANIUM_PROPERTY_DEF(exitOnClose);
			TITANIUM_FUNCTION_DEF(getExitOnClose);
			TITANIUM_FUNCTION_DEF(setExitOnClose);

			TITANIUM_PROPERTY_DEF(extendEdges);
			TITANIUM_FUNCTION_DEF(getExtendEdges);
			TITANIUM_FUNCTION_DEF(setExtendEdges);

			TITANIUM_PROPERTY_DEF(fullscreen);
			TITANIUM_FUNCTION_DEF(getFullscreen);
			TITANIUM_FUNCTION_DEF(setFullscreen);

			TITANIUM_PROPERTY_DEF(hideShadow);
			TITANIUM_FUNCTION_DEF(getHideShadow);
			TITANIUM_FUNCTION_DEF(setHideShadow);

			TITANIUM_PROPERTY_DEF(modal);
			TITANIUM_FUNCTION_DEF(getModal);
			TITANIUM_FUNCTION_DEF(setModal);

			TITANIUM_PROPERTY_DEF(navBarHidden);
			TITANIUM_FUNCTION_DEF(getNavBarHidden);
			TITANIUM_FUNCTION_DEF(setNavBarHidden);

			TITANIUM_PROPERTY_DEF(navTintColor);
			TITANIUM_FUNCTION_DEF(getNavTintColor);
			TITANIUM_FUNCTION_DEF(setNavTintColor);

			TITANIUM_PROPERTY_DEF(orientationModes);
			TITANIUM_FUNCTION_DEF(getOrientationModes);
			TITANIUM_FUNCTION_DEF(setOrientationModes);

			TITANIUM_PROPERTY_DEF(theme);
			TITANIUM_FUNCTION_DEF(getTheme);
			TITANIUM_FUNCTION_DEF(setTheme);

			TITANIUM_PROPERTY_DEF(titleAttributes);
			TITANIUM_FUNCTION_DEF(getTitleAttributes);
			TITANIUM_FUNCTION_DEF(setTitleAttributes);

			TITANIUM_PROPERTY_DEF(title);
			TITANIUM_FUNCTION_DEF(getTitle);
			TITANIUM_FUNCTION_DEF(setTitle);

			TITANIUM_PROPERTY_DEF(titleid);
			TITANIUM_FUNCTION_DEF(getTitleid);
			TITANIUM_FUNCTION_DEF(setTitleid);

			TITANIUM_PROPERTY_DEF(translucent);
			TITANIUM_FUNCTION_DEF(getTranslucent);
			TITANIUM_FUNCTION_DEF(setTranslucent);

		protected:
// Silence 4251 on Windows since private member variables do not
// need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable : 4251)
			static std::vector<std::shared_ptr<Window>> window_stack__;
			static bool restarting__;
			std::string barColor__;
			bool exitOnClose__;
			std::unordered_set<EXTEND_EDGE> extendEdges__;
			bool fullscreen__;
			bool hideShadow__;
			bool modal__;
			bool navBarHidden__;
			std::string navTintColor__;
			std::vector<ORIENTATION> orientationModes__;
			std::string theme__;
			TitleAttributesParams titleAttributes__;
			std::string title__;
			std::string titleid__;
			bool translucent__;
			JSObject openWindowParams_ctor__;
			JSObject closeWindowParams_ctor__;

			std::shared_ptr<Tab> tab__;
			bool is_opened__ { false }; // Indicates this window is already opened
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_WINDOW_HPP_
