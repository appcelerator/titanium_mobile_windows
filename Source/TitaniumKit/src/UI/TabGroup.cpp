/**
 * TitaniumKit Titanium.UI.TabGroup
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TabGroup.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/Tab.hpp"

namespace Titanium
{
	namespace UI
	{
		TabGroup::TabGroup(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.TabGroup")
			, activity__(js_context.CreateUndefined())
		{
		}

		TITANIUM_PROPERTY_READ(TabGroup, std::shared_ptr<Tab>, activeTab)
		void TabGroup::set_activeTab(const std::shared_ptr<Tab>& activeTab) TITANIUM_NOEXCEPT
		{
			if (activeTab == activeTab__) {
				return;
			}
			if (activeTab__ != nullptr) {
				activeTab__->blur();
			}
			activeTab__ = activeTab;

			if (activeTab__ == nullptr) {
				return;
			}

			if (!activeTabBackgroundColor__.empty()) {
				activeTab__->set_backgroundColor(activeTabBackgroundColor__);
			}
			if (!activeTabBackgroundDisabledColor__.empty()) {
				activeTab__->set_backgroundDisabledColor(activeTabBackgroundDisabledColor__);
			}
			if (!activeTabBackgroundFocusedColor__.empty()) {
				activeTab__->set_backgroundFocusedColor(activeTabBackgroundFocusedColor__);
			}
			if (!activeTabBackgroundSelectedColor__.empty()) {
				activeTab__->set_backgroundSelectedColor(activeTabBackgroundSelectedColor__);
			}
			if (!activeTabBackgroundImage__.empty()) {
				activeTab__->set_backgroundImage(activeTabBackgroundImage__);
			}
			if (!activeTabBackgroundDisabledImage__.empty()) {
				activeTab__->set_backgroundDisabledImage(activeTabBackgroundDisabledImage__);
			}
			if (!activeTabBackgroundFocusedImage__.empty()) {
				activeTab__->set_backgroundFocusedImage(activeTabBackgroundFocusedImage__);
			}
			if (!activeTabBackgroundSelectedImage__.empty()) {
				activeTab__->set_backgroundSelectedImage(activeTabBackgroundSelectedImage__);
			}

			activeTab__->focus();
		}

		TITANIUM_PROPERTY_READ(TabGroup, JSValue, activity)
		TITANIUM_PROPERTY_READWRITE(TabGroup, bool, allowUserCustomization)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, barColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, bool, translucent)
		TITANIUM_PROPERTY_READWRITE(TabGroup, TitleAttributesParams, titleAttributes)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, navTintColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, editButtonTitle)
		TITANIUM_PROPERTY_READWRITE(TabGroup, bool, exitOnClose)
		TITANIUM_PROPERTY_READWRITE(TabGroup, bool, navBarHidden)
		TITANIUM_PROPERTY_READWRITE(TabGroup, bool, swipeable)
		TITANIUM_PROPERTY_READWRITE(TabGroup, bool, smoothScrollOnTabClick)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::vector<std::shared_ptr<Tab>>, tabs)
		TITANIUM_PROPERTY_READWRITE(TabGroup, double, windowSoftInputMode)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, tabsTintColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, title)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, shadowImage)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabIconTint)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, tabDividerColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, tabDividerWidth)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, tabHeight)
		TITANIUM_PROPERTY_READWRITE(TabGroup, bool, tabsAtBottom)

		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundColor)
		void TabGroup::set_tabsBackgroundColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundColor__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundColor(value);
			}
		}
		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundImage)
		void TabGroup::set_tabsBackgroundImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundImage__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundImage(value);
			}
		}
		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundDisabledColor)
		void TabGroup::set_tabsBackgroundDisabledColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundDisabledColor__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundDisabledColor(value);
			}
		}
		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundDisabledImage)
		void TabGroup::set_tabsBackgroundDisabledImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundDisabledImage__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundDisabledImage(value);
			}
		}
		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundFocusedColor)
		void TabGroup::set_tabsBackgroundFocusedColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundFocusedColor__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundFocusedColor(value);
			}
		}
		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundFocusedImage)
		void TabGroup::set_tabsBackgroundFocusedImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundFocusedImage__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundFocusedImage(value);
			}
		}
		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundSelectedColor)
		void TabGroup::set_tabsBackgroundSelectedColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundSelectedColor__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundSelectedColor(value);
			}
		}
		TITANIUM_PROPERTY_READ(TabGroup, std::string, tabsBackgroundSelectedImage)
		void TabGroup::set_tabsBackgroundSelectedImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			tabsBackgroundSelectedImage__ = value;
			for (const auto tab : tabs__) {
				tab->set_backgroundSelectedImage(value);
			}
		}

		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundImage)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundDisabledColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundDisabledImage)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundFocusedColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundFocusedImage)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundSelectedColor)
		TITANIUM_PROPERTY_READWRITE(TabGroup, std::string, activeTabBackgroundSelectedImage)

		void TabGroup::addTab(const std::shared_ptr<Tab>& tab) TITANIUM_NOEXCEPT
		{
			tabs__.push_back(tab);
		}

		void TabGroup::close() TITANIUM_NOEXCEPT
		{
			if (activeTab__) {
				activeTab__->blur();
			}

			// closes all Tabs
			for (const auto tab : tabs__) {
				tab->close();
			}
		}

		void TabGroup::disableTabNavigation(const bool& disable) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TabGroup::disableTabNavigation: Unimplemented");
		}

		void TabGroup::open() TITANIUM_NOEXCEPT
		{
			// opens all Tabs according to iOS implementation
			for (const auto tab : tabs__) {
				tab->open();
			}

			if (tabs__.size() > 0) {
				set_activeTab(tabs__.at(0));
			}
		}

		void TabGroup::removeTab(const std::shared_ptr<Tab>& tab) TITANIUM_NOEXCEPT
		{
			tabs__.erase(find(tabs__.begin(), tabs__.end(), tab));
		}

		void TabGroup::JSExportInitialize()
		{
			JSExport<TabGroup>::SetClassVersion(1);
			JSExport<TabGroup>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(TabGroup, activeTab);
			TITANIUM_ADD_PROPERTY_READONLY(TabGroup, activity);
			TITANIUM_ADD_PROPERTY(TabGroup, allowUserCustomization);
			TITANIUM_ADD_PROPERTY(TabGroup, barColor);
			TITANIUM_ADD_PROPERTY(TabGroup, translucent);
			TITANIUM_ADD_PROPERTY(TabGroup, titleAttributes);
			TITANIUM_ADD_PROPERTY(TabGroup, navTintColor);
			TITANIUM_ADD_PROPERTY(TabGroup, editButtonTitle);
			TITANIUM_ADD_PROPERTY(TabGroup, exitOnClose);
			TITANIUM_ADD_PROPERTY(TabGroup, navBarHidden);
			TITANIUM_ADD_PROPERTY(TabGroup, swipeable);
			TITANIUM_ADD_PROPERTY(TabGroup, smoothScrollOnTabClick);
			TITANIUM_ADD_PROPERTY(TabGroup, tabs);
			TITANIUM_ADD_PROPERTY(TabGroup, windowSoftInputMode);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundColor);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsTintColor);
			TITANIUM_ADD_PROPERTY(TabGroup, title);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundImage);
			TITANIUM_ADD_PROPERTY(TabGroup, shadowImage);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabIconTint);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundDisabledColor);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundDisabledImage);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundFocusedColor);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundFocusedImage);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundSelectedColor);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsBackgroundSelectedImage);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundColor);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundImage);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundDisabledColor);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundDisabledImage);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundFocusedColor);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundFocusedImage);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundSelectedColor);
			TITANIUM_ADD_PROPERTY(TabGroup, activeTabBackgroundSelectedImage);
			TITANIUM_ADD_PROPERTY(TabGroup, tabDividerColor);
			TITANIUM_ADD_PROPERTY(TabGroup, tabDividerWidth);
			TITANIUM_ADD_PROPERTY(TabGroup, tabHeight);
			TITANIUM_ADD_PROPERTY(TabGroup, tabsAtBottom);

			TITANIUM_ADD_FUNCTION(TabGroup, addTab);
			TITANIUM_ADD_FUNCTION(TabGroup, close);
			TITANIUM_ADD_FUNCTION(TabGroup, disableTabNavigation);
			TITANIUM_ADD_FUNCTION(TabGroup, open);
			TITANIUM_ADD_FUNCTION(TabGroup, removeTab);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTab);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTab);
			TITANIUM_ADD_FUNCTION(TabGroup, getActivity);
			TITANIUM_ADD_FUNCTION(TabGroup, getAllowUserCustomization);
			TITANIUM_ADD_FUNCTION(TabGroup, setAllowUserCustomization);
			TITANIUM_ADD_FUNCTION(TabGroup, getBarColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setBarColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getTranslucent);
			TITANIUM_ADD_FUNCTION(TabGroup, setTranslucent);
			TITANIUM_ADD_FUNCTION(TabGroup, getTitleAttributes);
			TITANIUM_ADD_FUNCTION(TabGroup, setTitleAttributes);
			TITANIUM_ADD_FUNCTION(TabGroup, getNavTintColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setNavTintColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getEditButtonTitle);
			TITANIUM_ADD_FUNCTION(TabGroup, setEditButtonTitle);
			TITANIUM_ADD_FUNCTION(TabGroup, getExitOnClose);
			TITANIUM_ADD_FUNCTION(TabGroup, setExitOnClose);
			TITANIUM_ADD_FUNCTION(TabGroup, getNavBarHidden);
			TITANIUM_ADD_FUNCTION(TabGroup, setNavBarHidden);
			TITANIUM_ADD_FUNCTION(TabGroup, getSwipeable);
			TITANIUM_ADD_FUNCTION(TabGroup, setSwipeable);
			TITANIUM_ADD_FUNCTION(TabGroup, getSmoothScrollOnTabClick);
			TITANIUM_ADD_FUNCTION(TabGroup, setSmoothScrollOnTabClick);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabs);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabs);
			TITANIUM_ADD_FUNCTION(TabGroup, getWindowSoftInputMode);
			TITANIUM_ADD_FUNCTION(TabGroup, setWindowSoftInputMode);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsTintColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsTintColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getTitle);
			TITANIUM_ADD_FUNCTION(TabGroup, setTitle);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getShadowImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setShadowImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabIconTint);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabIconTint);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundDisabledColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundDisabledImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundFocusedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundFocusedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundSelectedColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getActiveTabBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, setActiveTabBackgroundSelectedImage);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabDividerColor);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabDividerColor);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabDividerWidth);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabDividerWidth);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabHeight);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabHeight);
			TITANIUM_ADD_FUNCTION(TabGroup, getTabsAtBottom);
			TITANIUM_ADD_FUNCTION(TabGroup, setTabsAtBottom);
		}

		TITANIUM_PROPERTY_GETTER_OBJECT(TabGroup, activeTab)
		TITANIUM_PROPERTY_SETTER_OBJECT(TabGroup, activeTab, Tab)
		TITANIUM_PROPERTY_GETTER(TabGroup, activity)
		{
			return activity__;
		}
		TITANIUM_PROPERTY_GETTER_BOOL(TabGroup, allowUserCustomization)
		TITANIUM_PROPERTY_SETTER_BOOL(TabGroup, allowUserCustomization)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, barColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, barColor)
		TITANIUM_PROPERTY_GETTER_BOOL(TabGroup, translucent)
		TITANIUM_PROPERTY_SETTER_BOOL(TabGroup, translucent)
		TITANIUM_PROPERTY_GETTER_STRUCT(TabGroup, titleAttributes, TitleAttributesParams)
		TITANIUM_PROPERTY_SETTER_STRUCT(TabGroup, titleAttributes, TitleAttributesParams)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, navTintColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, navTintColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, editButtonTitle)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, editButtonTitle)
		TITANIUM_PROPERTY_GETTER_BOOL(TabGroup, exitOnClose)
		TITANIUM_PROPERTY_SETTER_BOOL(TabGroup, exitOnClose)
		TITANIUM_PROPERTY_GETTER_BOOL(TabGroup, navBarHidden)
		TITANIUM_PROPERTY_SETTER_BOOL(TabGroup, navBarHidden)
		TITANIUM_PROPERTY_GETTER_BOOL(TabGroup, swipeable)
		TITANIUM_PROPERTY_SETTER_BOOL(TabGroup, swipeable)
		TITANIUM_PROPERTY_GETTER_BOOL(TabGroup, smoothScrollOnTabClick)
		TITANIUM_PROPERTY_SETTER_BOOL(TabGroup, smoothScrollOnTabClick)
		TITANIUM_PROPERTY_GETTER_OBJECT_ARRAY(TabGroup, tabs);
		TITANIUM_PROPERTY_SETTER_OBJECT_ARRAY(TabGroup, tabs, Titanium::UI::Tab);
		TITANIUM_PROPERTY_GETTER_INT(TabGroup, windowSoftInputMode)
		TITANIUM_PROPERTY_SETTER_INT(TabGroup, windowSoftInputMode)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsTintColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsTintColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, title)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, title)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, shadowImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, shadowImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabIconTint)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabIconTint)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundDisabledColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundDisabledColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundDisabledImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundDisabledImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundFocusedColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundFocusedColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundFocusedImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundFocusedImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundSelectedColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundSelectedColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabsBackgroundSelectedImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabsBackgroundSelectedImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundDisabledColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundDisabledColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundDisabledImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundDisabledImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundFocusedColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundFocusedColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundFocusedImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundFocusedImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundSelectedColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundSelectedColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, activeTabBackgroundSelectedImage)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, activeTabBackgroundSelectedImage)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabDividerColor)
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabDividerColor)
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabDividerWidth);
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabDividerWidth);
		TITANIUM_PROPERTY_GETTER_STRING(TabGroup, tabHeight);
		TITANIUM_PROPERTY_SETTER_STRING(TabGroup, tabHeight);
		TITANIUM_PROPERTY_GETTER_BOOL(TabGroup, tabsAtBottom);
		TITANIUM_PROPERTY_SETTER_BOOL(TabGroup, tabsAtBottom);

		TITANIUM_FUNCTION(TabGroup, addTab)
		{
			ENSURE_OBJECT_AT_INDEX(tab, 0);
			addTab(tab.GetPrivate<Tab>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TabGroup, close)
		{
			close();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TabGroup, disableTabNavigation)
		{
			ENSURE_BOOL_AT_INDEX(disable, 0);
			disableTabNavigation(disable);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TabGroup, open)
		{
			open();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TabGroup, removeTab)
		{
			ENSURE_OBJECT_AT_INDEX(tab, 0);
			removeTab(tab.GetPrivate<Tab>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTab, activeTab)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTab, activeTab)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActivity, activity)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getAllowUserCustomization, allowUserCustomization)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setAllowUserCustomization, allowUserCustomization)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getBarColor, barColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setBarColor, barColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTranslucent, translucent)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTranslucent, translucent)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTitleAttributes, titleAttributes)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTitleAttributes, titleAttributes)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getNavTintColor, navTintColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setNavTintColor, navTintColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getEditButtonTitle, editButtonTitle)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setEditButtonTitle, editButtonTitle)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getExitOnClose, exitOnClose)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setExitOnClose, exitOnClose)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getNavBarHidden, navBarHidden)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setNavBarHidden, navBarHidden)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getSwipeable, swipeable)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setSwipeable, swipeable)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getSmoothScrollOnTabClick, smoothScrollOnTabClick)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setSmoothScrollOnTabClick, smoothScrollOnTabClick)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabs, tabs)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabs, tabs)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getWindowSoftInputMode, windowSoftInputMode)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setWindowSoftInputMode, windowSoftInputMode)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundColor, tabsBackgroundColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundColor, tabsBackgroundColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsTintColor, tabsTintColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsTintColor, tabsTintColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTitle, title)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundImage, tabsBackgroundImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundImage, tabsBackgroundImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getShadowImage, shadowImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setShadowImage, shadowImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabIconTint, activeTabIconTint)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabIconTint, activeTabIconTint)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundDisabledColor, tabsBackgroundDisabledColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundDisabledColor, tabsBackgroundDisabledColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundDisabledImage, tabsBackgroundDisabledImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundDisabledImage, tabsBackgroundDisabledImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundFocusedColor, tabsBackgroundFocusedColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundFocusedColor, tabsBackgroundFocusedColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundFocusedImage, tabsBackgroundFocusedImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundFocusedImage, tabsBackgroundFocusedImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundSelectedColor, tabsBackgroundSelectedColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundSelectedColor, tabsBackgroundSelectedColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsBackgroundSelectedImage, tabsBackgroundSelectedImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsBackgroundSelectedImage, tabsBackgroundSelectedImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundColor, activeTabBackgroundColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundColor, activeTabBackgroundColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundImage, activeTabBackgroundImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundImage, activeTabBackgroundImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundDisabledColor, activeTabBackgroundDisabledColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundDisabledColor, activeTabBackgroundDisabledColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundDisabledImage, activeTabBackgroundDisabledImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundDisabledImage, activeTabBackgroundDisabledImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundFocusedColor, activeTabBackgroundFocusedColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundFocusedColor, activeTabBackgroundFocusedColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundFocusedImage, activeTabBackgroundFocusedImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundFocusedImage, activeTabBackgroundFocusedImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundSelectedColor, activeTabBackgroundSelectedColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundSelectedColor, activeTabBackgroundSelectedColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getActiveTabBackgroundSelectedImage, activeTabBackgroundSelectedImage)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setActiveTabBackgroundSelectedImage, activeTabBackgroundSelectedImage)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabDividerColor, tabDividerColor)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabDividerColor, tabDividerColor)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabDividerWidth, tabDividerWidth)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabDividerWidth, tabDividerWidth)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabHeight, tabHeight)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabHeight, tabHeight)
		TITANIUM_FUNCTION_AS_GETTER(TabGroup, getTabsAtBottom, tabsAtBottom)
		TITANIUM_FUNCTION_AS_SETTER(TabGroup, setTabsAtBottom, tabsAtBottom)

	} // namespace UI
} // namespace Titanium
