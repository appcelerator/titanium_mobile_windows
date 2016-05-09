/**
 * TitaniumKit Titanium.UI.Tab
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_TAB_HPP_
#define _TITANIUM_UI_TAB_HPP_

#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		class Window;
		class OpenWindowParams;
		class CloseWindowParams;

		/*!
		  @class
		  @discussion This is the Titanium Tab Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Tab
		*/
		class TITANIUMKIT_EXPORT Tab : public View, public JSExport<Tab>
		{

		public:

			/*!
			  @property
			  @abstract backgroundDisabledColor
			  @discussion Disabled background color of the view, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundDisabledColor);

			/*!
			  @property
			  @abstract backgroundDisabledImage
			  @discussion Disabled background image for the view, specified as a local file path or URL.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundDisabledImage);

			/*!
			  @property
			  @abstract backgroundFocusedColor
			  @discussion Sets the color of the tab when it is focused.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundFocusedColor);

			/*!
			  @property
			  @abstract backgroundFocusedImage
			  @discussion Focused background image for the view, specified as a local file path or URL.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundFocusedImage);

			/*!
			  @property
			  @abstract backgroundImage
			  @discussion Background image for the view, specified as a local file path or URL.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundImage);

			/*!
			  @property
			  @abstract backgroundSelectedImage
			  @discussion Selected background image url for the view, specified as a local file path or URL.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundSelectedImage);

			/*!
			  @property
			  @abstract backgroundSelectedColor
			  @discussion Selected background color for the view
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundSelectedColor);

			/*!
			  @property
			  @abstract touchEnabled
			  @discussion Determines whether view should receive touch events.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, touchEnabled);

			/*!
			  @property
			  @abstract backgroundColor
			  @discussion Sets the color of the tab when it is inactive.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundColor);

			/*!
			  @property
			  @abstract active
			  @discussion `true` if this tab is active, `false` if it is not. 
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, active);

			/*!
			  @property
			  @abstract activeColor
			  @discussion Defines the color of the title of tab when it's active.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string , activeColor);

			/*!
			  @property
			  @abstract activeIcon
			  @discussion Icon URL for this tab when active.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, activeIcon);

			/*!
			  @property
			  @abstract badge
			  @discussion Badge value for this tab. `null` indicates no badge.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, badge);

			/*!
			  @property
			  @abstract icon
			  @discussion Icon URL for this tab.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, icon);

			/*!
			  @property
			  @abstract iconIsMask
			  @discussion Defines if the icon property of the tab must be used as a mask. This property is applicable on iOS 7 and greater.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, iconIsMask);

			/*!
			  @property
			  @abstract activeIconIsMask
			  @discussion Defines if the active icon property of the tab must be used as a mask. This property is applicable on iOS 7 and greater.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, activeIconIsMask);

			/*!
			  @property
			  @abstract title
			  @discussion Title for this tab.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);

			/*!
			  @property
			  @abstract titleColor
			  @discussion Defines the color of the title of tab when it's inactive.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, titleColor);

			/*!
			  @property
			  @abstract titleid
			  @discussion Key identifying a string from the locale file to use for the tab title. Only one of `title` or `titleid` should be specified.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, titleid);

			/*!
			  @property
			  @abstract window
			  @discussion Root-level tab window.  All tabs must have at least one root-level tab window.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Window>, window);

			/*!
			  @method
			  @abstract open
			  @discussion Opens a new window.
			*/
			virtual void open(const std::shared_ptr<Window>& window, const std::shared_ptr<OpenWindowParams>& options) TITANIUM_NOEXCEPT;

			/*!
			@method
			@abstract open
			@discussion Opens current window.
			*/
			virtual void open(const std::shared_ptr<OpenWindowParams>& options = nullptr) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract close
			  @discussion Closes the top-level window for this tab.
			*/
			virtual void close(const std::shared_ptr<Window>& window, const std::shared_ptr<CloseWindowParams>& options) TITANIUM_NOEXCEPT;

			/*!
			@method
			@abstract close
			@discussion Closes current window.
			*/
			virtual void close(const std::shared_ptr<CloseWindowParams>& options = nullptr) TITANIUM_NOEXCEPT;

			virtual void blur()  override;
			virtual void focus() override;

			Tab(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Tab() = default;
			Tab(const Tab&) = default;
			Tab& operator=(const Tab&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Tab(Tab&&)                 = default;
			Tab& operator=(Tab&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(backgroundDisabledColor);
			TITANIUM_PROPERTY_DEF(backgroundDisabledImage);
			TITANIUM_PROPERTY_DEF(backgroundFocusedColor);
			TITANIUM_PROPERTY_DEF(backgroundFocusedImage);
			TITANIUM_PROPERTY_DEF(backgroundColor);
			TITANIUM_PROPERTY_DEF(backgroundImage);
			TITANIUM_PROPERTY_DEF(backgroundSelectedColor);
			TITANIUM_PROPERTY_DEF(backgroundSelectedImage);
			TITANIUM_PROPERTY_DEF(touchEnabled);
			TITANIUM_PROPERTY_DEF(active);
			TITANIUM_PROPERTY_DEF(activeColor);
			TITANIUM_PROPERTY_DEF(activeIcon);
			TITANIUM_PROPERTY_DEF(badge);
			TITANIUM_PROPERTY_DEF(icon);
			TITANIUM_PROPERTY_DEF(iconIsMask);
			TITANIUM_PROPERTY_DEF(activeIconIsMask);
			TITANIUM_PROPERTY_DEF(title);
			TITANIUM_PROPERTY_DEF(titleColor);
			TITANIUM_PROPERTY_DEF(titleid);
			TITANIUM_PROPERTY_DEF(window);

			TITANIUM_FUNCTION_DEF(open);
			TITANIUM_FUNCTION_DEF(close);
			TITANIUM_FUNCTION_DEF(getBackgroundDisabledColor);
			TITANIUM_FUNCTION_DEF(setBackgroundDisabledColor);
			TITANIUM_FUNCTION_DEF(getBackgroundDisabledImage);
			TITANIUM_FUNCTION_DEF(setBackgroundDisabledImage);
			TITANIUM_FUNCTION_DEF(getBackgroundFocusedColor);
			TITANIUM_FUNCTION_DEF(setBackgroundFocusedColor);
			TITANIUM_FUNCTION_DEF(getBackgroundFocusedImage);
			TITANIUM_FUNCTION_DEF(setBackgroundFocusedImage);
			TITANIUM_FUNCTION_DEF(getBackgroundColor);
			TITANIUM_FUNCTION_DEF(setBackgroundColor);
			TITANIUM_FUNCTION_DEF(getBackgroundImage);
			TITANIUM_FUNCTION_DEF(setBackgroundImage);
			TITANIUM_FUNCTION_DEF(getBackgroundSelectedColor);
			TITANIUM_FUNCTION_DEF(setBackgroundSelectedColor);
			TITANIUM_FUNCTION_DEF(getBackgroundSelectedImage);
			TITANIUM_FUNCTION_DEF(setBackgroundSelectedImage);
			TITANIUM_FUNCTION_DEF(getTouchEnabled);
			TITANIUM_FUNCTION_DEF(setTouchEnabled);
			TITANIUM_FUNCTION_DEF(getActive);
			TITANIUM_FUNCTION_DEF(setActive);
			TITANIUM_FUNCTION_DEF(getActiveColor);
			TITANIUM_FUNCTION_DEF(setActiveColor);
			TITANIUM_FUNCTION_DEF(getActiveIcon);
			TITANIUM_FUNCTION_DEF(setActiveIcon);
			TITANIUM_FUNCTION_DEF(getBadge);
			TITANIUM_FUNCTION_DEF(setBadge);
			TITANIUM_FUNCTION_DEF(getIcon);
			TITANIUM_FUNCTION_DEF(setIcon);
			TITANIUM_FUNCTION_DEF(getIconIsMask);
			TITANIUM_FUNCTION_DEF(setIconIsMask);
			TITANIUM_FUNCTION_DEF(getActiveIconIsMask);
			TITANIUM_FUNCTION_DEF(setActiveIconIsMask);
			TITANIUM_FUNCTION_DEF(getTitle);
			TITANIUM_FUNCTION_DEF(setTitle);
			TITANIUM_FUNCTION_DEF(getTitleColor);
			TITANIUM_FUNCTION_DEF(setTitleColor);
			TITANIUM_FUNCTION_DEF(getTitleid);
			TITANIUM_FUNCTION_DEF(setTitleid);
			TITANIUM_FUNCTION_DEF(getWindow);
			TITANIUM_FUNCTION_DEF(setWindow);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string backgroundDisabledColor__;
			std::string backgroundDisabledImage__;
			std::string backgroundFocusedColor__;
			std::string backgroundFocusedImage__;
			std::string backgroundColor__;
			std::string backgroundImage__;
			std::string backgroundSelectedColor__;
			std::string backgroundSelectedImage__;
			bool touchEnabled__;
			bool active__;
			std::string activeColor__;
			std::string activeIcon__;
			std::string badge__;
			std::string icon__;
			bool iconIsMask__;
			bool activeIconIsMask__;
			std::string title__;
			std::string titleColor__;
			std::string titleid__;
			std::shared_ptr<Window> window__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_TAB_HPP_