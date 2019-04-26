/**
 * Titanium.UI.TabGroup for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/TabGroup.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/UI/Tab.hpp"
#include "TitaniumWindows/UI/Window.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include "TitaniumWindows/WindowsTiImpl.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Platform::Collections;
		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Controls;

		TabGroup::TabGroup(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::TabGroup(js_context)
		{
		}

		void TabGroup::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::TabGroup::postCallAsConstructor(js_context, arguments);	

			// root Window object to make layout work
			window__ = js_context.CreateObject(JSExport<TitaniumWindows::UI::Window>::Class()).CallAsConstructor().GetPrivate<TitaniumWindows::UI::Window>();
			window__->setTabGroupContainer(true);

			static auto WindowEventHandler = js_context.CreateFunction("return function(e) {x.fireEvent(e.type, e);};", {"x"});
			auto handler = static_cast<JSObject>(WindowEventHandler({get_object()}, js_context.get_global_object()));
			auto window = window__->get_object();
			window__->addEventListener("open",  handler, window);
			window__->addEventListener("close", handler, window);

			grid__  = ref new Grid();
			pivot__ = ref new Pivot();

			pivot__->SelectionChanged += ref new SelectionChangedEventHandler([this](Platform::Object^ sender, SelectionChangedEventArgs^ e) {
				try {
					if (tabs__.size() > static_cast<std::size_t>(pivot__->SelectedIndex)) {
						set_activeTab(tabs__.at(pivot__->SelectedIndex), false);
					} else {
						// This could happen when all tabs are removed
						set_activeTab(nullptr);
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error at TabGroup::SelectionChanged");
				}
			});

			pivot__->GotFocus += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				// fire focus event only when there's an active tab
				if (activeTab__) {
					fireEvent("focus");
				}
			});

			pivot__->LostFocus += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				// fire blur event only when there's an active tab
				if (activeTab__) {
					fireEvent("blur");
				}
			});

			grid__->Children->Append(pivot__);
			Titanium::UI::TabGroup::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(grid__);

			window__->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->add(get_object().GetPrivate<Titanium::UI::View>());
		}

		void TabGroup::set_barColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TabGroup::set_barColor(value);
			const auto brush = ref new Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(value));
			pivot__->Background = brush;
		}

		void TabGroup::set_activeTab(const std::shared_ptr<Titanium::UI::Tab>& activeTab) TITANIUM_NOEXCEPT
		{
			set_activeTab(activeTab, true);
		}

		void TabGroup::set_activeTab(const std::shared_ptr<Titanium::UI::Tab>& activeTab, bool updateUI) TITANIUM_NOEXCEPT
		{
			if (updateUI && activeTab && activeTab != activeTab__) {
				const auto tabview = activeTab->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
				pivot__->SelectedItem = tabview;
			}
			Titanium::UI::TabGroup::set_activeTab(activeTab);
		}

		void TabGroup::open() TITANIUM_NOEXCEPT
		{
			window__->open(nullptr);

			Titanium::UI::TabGroup::open();
		}

		void TabGroup::close() TITANIUM_NOEXCEPT
		{
			Titanium::UI::TabGroup::close();
			window__->close(nullptr);
		}

		void TabGroup::set_tabs(const std::vector<std::shared_ptr<Titanium::UI::Tab>>& tabs) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TabGroup::set_tabs(tabs);
			pivot__->Items->Clear();
			for (const auto tab : tabs) {
				appendWindowsTabItem(tab);
			}
		}

		void TabGroup::addTab(const std::shared_ptr<Titanium::UI::Tab>& tab) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TabGroup::addTab(tab);
			appendWindowsTabItem(tab);
		}

		void TabGroup::appendWindowsTabItem(const std::shared_ptr<Titanium::UI::Tab>& tab) TITANIUM_NOEXCEPT
		{
			const auto windows_tab = dynamic_cast<TitaniumWindows::UI::Tab*>(tab.get());
			const auto tabview = windows_tab->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
			if (windows_tab) {
				pivot__->Items->Append(tabview);
			}
		}

		void TabGroup::JSExportInitialize() 
		{
			JSExport<TabGroup>::SetClassVersion(1);
			JSExport<TabGroup>::SetParent(JSExport<Titanium::UI::TabGroup>::Class());
		}

	}  // namespace UI
}  // namespace TitaniumWindows