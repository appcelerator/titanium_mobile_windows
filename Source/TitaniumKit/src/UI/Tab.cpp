/**
 * TitaniumKit Titanium.UI.Tab
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Tab.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/Window.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/UI/OpenWindowParams.hpp"
#include "Titanium/UI/CloseWindowParams.hpp"
#include "Titanium/Locale.hpp"

namespace Titanium
{
	namespace UI
	{
		Tab::Tab(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.Tab")
		{
		}

		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundDisabledColor)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundDisabledImage)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundFocusedColor)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundFocusedImage)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundImage)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundSelectedColor)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundSelectedImage)
		TITANIUM_PROPERTY_READWRITE(Tab, bool, touchEnabled)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, backgroundColor)
		TITANIUM_PROPERTY_READWRITE(Tab, bool, active)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, activeTitleColor)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, activeIcon)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, badge)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, icon)
		TITANIUM_PROPERTY_READWRITE(Tab, bool, iconIsMask)
		TITANIUM_PROPERTY_READWRITE(Tab, bool, activeIconIsMask)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, title)
		TITANIUM_PROPERTY_READWRITE(Tab, std::string, titleColor)
		TITANIUM_PROPERTY_READWRITE(Tab, std::shared_ptr<Window>, window)

		TITANIUM_PROPERTY_READ(Tab, std::string, titleid)
		void Tab::set_titleid(const std::string& titleid) TITANIUM_NOEXCEPT
		{
			titleid__ = titleid;
			const auto value = Titanium::Locale::GetString(get_context(), titleid);
			if (value) {
				set_title(*value);
			}
		}

		void Tab::focus()
		{
			Titanium::UI::View::focus();

			// Update Ti.UI.currentTab
			static std::shared_ptr<Titanium::UIModule> UI;
			static std::once_flag of;
			std::call_once(of, [=] {
				const auto Ti = static_cast<JSObject>(get_context().get_global_object().GetProperty("Titanium"));
				UI = static_cast<JSObject>(Ti.GetProperty("UI")).GetPrivate<Titanium::UIModule>();
			});
			UI->set_currentTab(get_object().GetPrivate<Titanium::UI::Tab>());

			set_active(true);

			fireEvent("focus");
		}

		void Tab::blur()
		{
			Titanium::UI::View::blur();

			// Update Ti.UI.currentTab
			static std::shared_ptr<Titanium::UIModule> UI;
			static std::once_flag of;
			std::call_once(of, [=] {
				const auto Ti = static_cast<JSObject>(get_context().get_global_object().GetProperty("Titanium"));
				UI = static_cast<JSObject>(Ti.GetProperty("UI")).GetPrivate<Titanium::UIModule>();
			});
			UI->set_currentTab(nullptr);

			set_active(false);

			fireEvent("blur");
		}

		void Tab::open(const std::shared_ptr<OpenWindowParams>& options) TITANIUM_NOEXCEPT
		{
			if (window__) {
				window__->set_tab(get_object().GetPrivate<Tab>());
				window__->open(options);
				fireEvent("open");
			} else {
				TITANIUM_LOG_WARN("Tab::open() failed: no window is attached");
			}
		}

		void Tab::open(const std::shared_ptr<Window>& window, const std::shared_ptr<OpenWindowParams>& options) TITANIUM_NOEXCEPT
		{
			set_window(window);
			open(options);
		}

		void Tab::close(const std::shared_ptr<CloseWindowParams>& options) TITANIUM_NOEXCEPT
		{
			if (window__) {
				window__->close(options);
				fireEvent("close");
			} else {
				TITANIUM_LOG_WARN("Tab::close() failed: no window is attached");
			}
		}

		void Tab::close(const std::shared_ptr<Window>& window, const std::shared_ptr<CloseWindowParams>& options) TITANIUM_NOEXCEPT
		{
			set_window(window);
			close(options);
		}

		void Tab::JSExportInitialize()
		{
			JSExport<Tab>::SetClassVersion(1);
			JSExport<Tab>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(Tab, backgroundDisabledColor);
			TITANIUM_ADD_PROPERTY(Tab, backgroundDisabledImage);
			TITANIUM_ADD_PROPERTY(Tab, backgroundFocusedColor);
			TITANIUM_ADD_PROPERTY(Tab, backgroundFocusedImage);
			TITANIUM_ADD_PROPERTY(Tab, backgroundImage);
			TITANIUM_ADD_PROPERTY(Tab, backgroundSelectedColor);
			TITANIUM_ADD_PROPERTY(Tab, backgroundSelectedImage);
			TITANIUM_ADD_PROPERTY(Tab, touchEnabled);
			TITANIUM_ADD_PROPERTY(Tab, backgroundColor);
			TITANIUM_ADD_PROPERTY(Tab, active);
			TITANIUM_ADD_PROPERTY(Tab, activeTitleColor);
			TITANIUM_ADD_PROPERTY(Tab, activeIcon);
			TITANIUM_ADD_PROPERTY(Tab, badge);
			TITANIUM_ADD_PROPERTY(Tab, icon);
			TITANIUM_ADD_PROPERTY(Tab, iconIsMask);
			TITANIUM_ADD_PROPERTY(Tab, activeIconIsMask);
			TITANIUM_ADD_PROPERTY(Tab, title);
			TITANIUM_ADD_PROPERTY(Tab, titleColor);
			TITANIUM_ADD_PROPERTY(Tab, titleid);
			TITANIUM_ADD_PROPERTY(Tab, window);

			TITANIUM_ADD_FUNCTION(Tab, open);
			TITANIUM_ADD_FUNCTION(Tab, close);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundImage);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundImage);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(Tab, getTouchEnabled);
			TITANIUM_ADD_FUNCTION(Tab, setTouchEnabled);
			TITANIUM_ADD_FUNCTION(Tab, getBackgroundColor);
			TITANIUM_ADD_FUNCTION(Tab, setBackgroundColor);
			TITANIUM_ADD_FUNCTION(Tab, getActive);
			TITANIUM_ADD_FUNCTION(Tab, setActive);
			TITANIUM_ADD_FUNCTION(Tab, getActiveTitleColor);
			TITANIUM_ADD_FUNCTION(Tab, setActiveTitleColor);
			TITANIUM_ADD_FUNCTION(Tab, getActiveIcon);
			TITANIUM_ADD_FUNCTION(Tab, setActiveIcon);
			TITANIUM_ADD_FUNCTION(Tab, getBadge);
			TITANIUM_ADD_FUNCTION(Tab, setBadge);
			TITANIUM_ADD_FUNCTION(Tab, getIcon);
			TITANIUM_ADD_FUNCTION(Tab, setIcon);
			TITANIUM_ADD_FUNCTION(Tab, getIconIsMask);
			TITANIUM_ADD_FUNCTION(Tab, setIconIsMask);
			TITANIUM_ADD_FUNCTION(Tab, getActiveIconIsMask);
			TITANIUM_ADD_FUNCTION(Tab, setActiveIconIsMask);
			TITANIUM_ADD_FUNCTION(Tab, getTitle);
			TITANIUM_ADD_FUNCTION(Tab, setTitle);
			TITANIUM_ADD_FUNCTION(Tab, getTitleColor);
			TITANIUM_ADD_FUNCTION(Tab, setTitleColor);
			TITANIUM_ADD_FUNCTION(Tab, getTitleid);
			TITANIUM_ADD_FUNCTION(Tab, setTitleid);
			TITANIUM_ADD_FUNCTION(Tab, getWindow);
			TITANIUM_ADD_FUNCTION(Tab, setWindow);
		}

		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundDisabledColor)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundDisabledColor)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundDisabledImage)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundDisabledImage)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundFocusedColor)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundFocusedColor)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundFocusedImage)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundFocusedImage)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundImage)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundImage)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundSelectedColor)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundSelectedColor)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundSelectedImage)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundSelectedImage)
		TITANIUM_PROPERTY_GETTER_BOOL(Tab, touchEnabled)
		TITANIUM_PROPERTY_SETTER_BOOL(Tab, touchEnabled)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, backgroundColor)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, backgroundColor)
		TITANIUM_PROPERTY_GETTER_BOOL(Tab, active)
		TITANIUM_PROPERTY_SETTER_BOOL(Tab, active)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, activeTitleColor)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, activeTitleColor)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, activeIcon)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, activeIcon)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, badge)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, badge)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, icon)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, icon)
		TITANIUM_PROPERTY_GETTER_BOOL(Tab, iconIsMask)
		TITANIUM_PROPERTY_SETTER_BOOL(Tab, iconIsMask)
		TITANIUM_PROPERTY_GETTER_BOOL(Tab, activeIconIsMask)
		TITANIUM_PROPERTY_SETTER_BOOL(Tab, activeIconIsMask)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, title)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, title)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, titleColor)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, titleColor)
		TITANIUM_PROPERTY_GETTER_STRING(Tab, titleid)
		TITANIUM_PROPERTY_SETTER_STRING(Tab, titleid)
		TITANIUM_PROPERTY_GETTER_OBJECT(Tab, window)
		TITANIUM_PROPERTY_SETTER_OBJECT(Tab, window, Window)

		TITANIUM_FUNCTION(Tab, open)
		{
			ENSURE_OBJECT_AT_INDEX(window, 0);
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(options, 1);

			open(window.GetPrivate<Window>(), options.GetPrivate<OpenWindowParams>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Tab, close)
		{
			ENSURE_OBJECT_AT_INDEX(window, 0);
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(options, 1);

			close(window.GetPrivate<Window>(), options.GetPrivate<CloseWindowParams>());

			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundDisabledColor, backgroundDisabledColor)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundDisabledColor, backgroundDisabledColor)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundDisabledImage, backgroundDisabledImage)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundDisabledImage, backgroundDisabledImage)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundFocusedColor, backgroundFocusedColor)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundFocusedColor, backgroundFocusedColor)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundFocusedImage, backgroundFocusedImage)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundFocusedImage, backgroundFocusedImage)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundImage, backgroundImage)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundImage, backgroundImage)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundSelectedColor, backgroundSelectedColor)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundSelectedColor, backgroundSelectedColor)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundSelectedImage, backgroundSelectedImage)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundSelectedImage, backgroundSelectedImage)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getTouchEnabled, touchEnabled)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setTouchEnabled, touchEnabled)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBackgroundColor, backgroundColor)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBackgroundColor, backgroundColor)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getActive, active)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setActive, active)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getActiveTitleColor, activeTitleColor)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setActiveTitleColor, activeTitleColor)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getActiveIcon, activeIcon)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setActiveIcon, activeIcon)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getBadge, badge)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setBadge, badge)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getIcon, icon)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setIcon, icon)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getIconIsMask, iconIsMask)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setIconIsMask, iconIsMask)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getActiveIconIsMask, activeIconIsMask)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setActiveIconIsMask, activeIconIsMask)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setTitle, title)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getTitleColor, titleColor)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setTitleColor, titleColor)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getTitleid, titleid)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setTitleid, titleid)
		TITANIUM_FUNCTION_AS_GETTER(Tab, getWindow, window)
		TITANIUM_FUNCTION_AS_SETTER(Tab, setWindow, window)

	} // namespace UI
} // namespace Titanium
