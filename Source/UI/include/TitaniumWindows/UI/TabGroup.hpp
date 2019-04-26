/**
 * Titanium.UI.TabGroup for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_TABGROUP_HPP_
#define _TITANIUMWINDOWS_TABGROUP_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/TabGroup.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <collection.h>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		class Window;

		/*!
		  @class Tab
		  @ingroup Titanium.UI.TabGroup

		  @discussion This is the Titanium.UI.TabGroup implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT TabGroup final : public Titanium::UI::TabGroup, public JSExport<TabGroup>
		{

		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(activity);
			TITANIUM_PROPERTY_UNIMPLEMENTED(allowUserCustomization);
			TITANIUM_PROPERTY_UNIMPLEMENTED(translucent);
			TITANIUM_PROPERTY_UNIMPLEMENTED(titleAttributes);
			TITANIUM_PROPERTY_UNIMPLEMENTED(navTintColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(editButtonTitle);
			TITANIUM_PROPERTY_UNIMPLEMENTED(exitOnClose);
			TITANIUM_PROPERTY_UNIMPLEMENTED(navBarHidden);
			TITANIUM_PROPERTY_UNIMPLEMENTED(swipeable);
			TITANIUM_PROPERTY_UNIMPLEMENTED(smoothScrollOnTabClick);
			TITANIUM_PROPERTY_UNIMPLEMENTED(windowSoftInputMode);
			TITANIUM_PROPERTY_UNIMPLEMENTED(tabsTintColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(shadowImage);
			TITANIUM_PROPERTY_UNIMPLEMENTED(activeTabIconTint);
			TITANIUM_PROPERTY_UNIMPLEMENTED(tabDividerColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(tabDividerWidth);
			TITANIUM_PROPERTY_UNIMPLEMENTED(tabHeight);
			TITANIUM_PROPERTY_UNIMPLEMENTED(tabsAtBottom);
			TITANIUM_FUNCTION_UNIMPLEMENTED(disableTabNavigation);

			TabGroup(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~TabGroup()                  = default;
			TabGroup(const TabGroup&)            = default;
			TabGroup& operator=(const TabGroup&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TabGroup(TabGroup&&)                 = default;
			TabGroup& operator=(TabGroup&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual void addTab(const std::shared_ptr<Titanium::UI::Tab>& tab) TITANIUM_NOEXCEPT override;
			virtual void open() TITANIUM_NOEXCEPT override;
			virtual void close() TITANIUM_NOEXCEPT override;
			virtual void set_tabs(const std::vector<std::shared_ptr<Titanium::UI::Tab>>& tabs) TITANIUM_NOEXCEPT override;
			virtual void set_activeTab(const std::shared_ptr<Titanium::UI::Tab>& activeTab) TITANIUM_NOEXCEPT override;
			virtual void set_activeTab(const std::shared_ptr<Titanium::UI::Tab>& activeTab, const bool updateUI) TITANIUM_NOEXCEPT;
			virtual void set_barColor(const std::string&) TITANIUM_NOEXCEPT override;

		private:
			void appendWindowsTabItem(const std::shared_ptr<Titanium::UI::Tab>& tab) TITANIUM_NOEXCEPT;

#pragma warning(push)
#pragma warning(disable : 4251)
			std::shared_ptr<TitaniumWindows::UI::Window> window__;
			Windows::UI::Xaml::Controls::Grid^  grid__;
			Windows::UI::Xaml::Controls::Pivot^ pivot__;
#pragma warning(pop)

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_TABGROUP_HPP_
