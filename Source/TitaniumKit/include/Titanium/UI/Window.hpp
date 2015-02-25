/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_WINDOW_HPP_
#define _TITANIUM_UI_WINDOW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Constants.hpp"

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
		class TITANIUMKIT_EXPORT Window : public View, public JSExport<Window>
		{
		public:
			/*!
			  @method

			  @abstract open( [params] ) : void

			  @discussion Opens the window.

			  @param params Optimized animation or display properties to use
			  when opening the window. (openWindowParams)

			  @result void
			*/
			virtual void open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract barColor : String

			  @discussion Background color for the nav bar, as a color name or hex triplet.

			  For information about color values, see the "Colors" section of Titanium.UI.
			*/
			virtual std::string get_barColor() const TITANIUM_NOEXCEPT final;
			virtual void set_barColor(const std::string& barColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract exitOnClose : Boolean

			  @discussion Boolean value indicating if the application should exit when the Android Back button is pressed while the window is being shown or when the window is closed programmatically.

			  Starting in 3.4.2 you can set this property at any time. In earlier releases you can only set this as a createWindow({...}) option.

			  Default: true if this is the first window launched else false; prior to Release 3.3.0, the default was always false.
			*/
			virtual bool get_exitOnClose() const TITANIUM_NOEXCEPT final;
			virtual void set_exitOnClose(const bool& exitOnClose) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract extendEdges : Number[]

			  @discussion An array of supported values specified using the EXTEND_EDGE constants in Titanium.UI.
			*/
			virtual std::unordered_set<EXTEND_EDGE> get_extendEdges() const TITANIUM_NOEXCEPT final;
			virtual void set_extendEdges(const std::unordered_set<EXTEND_EDGE>& extendEdges) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract fullscreen : Boolean

			  @discussion Boolean value indicating if the window is fullscreen.

			  A fullscreen window occupies all of the screen space, hiding the status bar. Must be specified at creation time or in the options dictionary passed to the Window.open method.

			  On iOS the behavior of this property has changed. Starting from 3.1.3, if this property is undefined then the property is set to the value for UIStatusBarHidden defined in tiapp.xml. If that is not defined it is treated as explicit false. On earlier versions, opening a window with this property undefined would not effect the status bar appearance.

			  On Android, setting this property forces the creation of a heavyweight window before Titanium 3.2.0. See "Android Heavyweight and Lightweight Windows" in the main description of this class for more information.

			  Default: false
			*/
			virtual bool get_fullscreen() const TITANIUM_NOEXCEPT final;
			virtual void set_fullscreen(const bool& fullscreen) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract hideShadow : Boolean

			  @discussion Set this to true to hide the shadow image of the navigation bar.

			  This property is only honored if a valid value is specified for the barImage property.

			  Default: false
			*/
			virtual bool get_hideShadow() const TITANIUM_NOEXCEPT final;
			virtual void set_hideShadow(const bool& hideShadow) TITANIUM_NOEXCEPT;

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
			virtual bool get_modal() const TITANIUM_NOEXCEPT final;
			virtual void set_modal(const bool& modal) TITANIUM_NOEXCEPT;

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
			virtual bool get_navBarHidden() const TITANIUM_NOEXCEPT final;
			virtual void set_navBarHidden(const bool& navBarHidden) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract navTintColor : String

			  @discussion The tintColor to apply to the navigation bar. This property is applicable on iOS 7 and greater.

			  This property is a direct correspondant of the tintColor property of NavigationBar on iOS.
			*/
			virtual std::string get_navTintColor() const TITANIUM_NOEXCEPT final;
			virtual void set_navTintColor(const std::string& navTintColor) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract orientationModes : Number[]

			  @discussion Array of supported orientation modes, specified using the orientation constants defined in Titanium.UI.

			  Note: Using the orientationModes property to force the orientation of non-modal windows is considered a bad practice and will not be supported, including forcing the orientation of windows inside a NavigationWindow or TabGroup.

			  To restrict this window to a certain set of orientations, specify one or more of the orientation constants LANDSCAPE_LEFT, LANDSCAPE_RIGHT, PORTRAIT, UPSIDE_PORTRAIT.

			  orientationModes must be set before opening the window.

			  To determine the current orientation of the window, see Window.orientation. To determine the current orientation of the device, see Gesture.orientation. To be notified when the device's current orientation changes, add a listener for the Titanium.Gesture.orientationchange event.
			*/
			virtual std::unordered_set<ORIENTATION> get_orientationModes() const TITANIUM_NOEXCEPT final;
			virtual void set_orientationModes(const std::unordered_set<ORIENTATION>& orientationModes) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract theme : String

			  @discussion Name of the theme to apply to the window.

			  Set the theme of the window. It can be either a built-in theme or a custom theme.
			*/
			virtual std::string get_theme() const TITANIUM_NOEXCEPT final;
			virtual void set_theme(const std::string& theme) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract titleAttributes : titleAttributesParams

			  @discussion Title text attributes of the window.

			  Use this property to specify the color, font and shadow attributes of the title.
			*/
			// FIXME Generate a struct for http://docs.appcelerator.com/titanium/3.0/#!/api/titleAttributesParams once Font struct is in
			virtual JSObject get_titleAttributes() const TITANIUM_NOEXCEPT final;
			virtual void set_titleAttributes(const JSObject& titleAttributes) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract translucent : Boolean

			  @discussion Boolean value indicating if the nav bar is translucent.

			  Default: true on iOS7 and above, false otherwise.
			*/
			virtual bool get_translucent() const TITANIUM_NOEXCEPT final;
			virtual void set_translucent(const bool& translucent) TITANIUM_NOEXCEPT;

			Window(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~Window() TITANIUM_NOEXCEPT;  //= default;
			Window(const Window&) = default;
			Window& operator=(const Window&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Window(Window&&) = default;
			Window& operator=(Window&&) = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_open(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_barColor() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_barColor(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_exitOnClose() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_exitOnClose(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_extendEdges() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_extendEdges(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_fullscreen() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_fullscreen(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_hideShadow() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_hideShadow(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_modal() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_modal(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_navBarHidden() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_navBarHidden(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_navTintColor() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_navTintColor(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_orientationModes() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_orientationModes(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_theme() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_theme(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_titleAttributes() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_titleAttributes(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_translucent() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_translucent(const JSValue& argument) TITANIUM_NOEXCEPT final;

		private:
// Silence 4251 on Windows since private member variables do not
// need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string barColor__;
			bool exitOnClose__;
			std::unordered_set<EXTEND_EDGE> extendEdges__;
			bool fullscreen__;
			bool hideShadow__;
			bool modal__;
			bool navBarHidden__;
			std::string navTintColor__;
			std::unordered_set<ORIENTATION> orientationModes__;
			std::string theme__;
			JSObject titleAttributes__;
			bool translucent__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_WINDOW_HPP_
