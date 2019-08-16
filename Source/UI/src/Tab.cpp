/**
 * Titanium.UI.Tab for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Tab.hpp"
#include "TitaniumWindows/UI/Window.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Controls;

		Tab::Tab(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::Tab(js_context)
		{
		}

		void Tab::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Tab::postCallAsConstructor(js_context, arguments);

			pivotItem__ = ref new PivotItem();

			Titanium::UI::Tab::setLayoutDelegate<WindowsViewLayoutDelegate>();
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(pivotItem__, nullptr, false);
		}

		void Tab::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_title(title);
			const auto textBlock = ref new TextBlock();
			textBlock->Text = TitaniumWindows::Utility::ConvertUTF8String(title);
			pivotItem__->Header = textBlock;
		}

		void Tab::openWindow(const std::shared_ptr<Window>& window)
		{
			window_stack__.push_back(window);
		}

		void Tab::closeWindow(const std::shared_ptr<Window>& window)
		{
			if (window_stack__.size() == 1) {
				window_stack__.pop_back();
			} else if (window_stack__.size() > 1) {
				const auto top_window = window_stack__.back();
				const auto is_top_window = (top_window.get() == window.get());
				if (is_top_window) {
					window_stack__.pop_back();
					const auto next_window = window_stack__.back();
					set_window(next_window);
					next_window->focus();
				} else {
					// Window is not on top. Just closing it then.
					for (std::size_t i = 0; i < window_stack__.size(); i++) {
						if (window_stack__.at(i).get() == window.get()) {
							window_stack__.erase(window_stack__.begin() + i);
							break;
						}
					}
				}
			}
		}

		void Tab::set_window(const std::shared_ptr<Titanium::UI::Window>& window) TITANIUM_NOEXCEPT
		{
			if (window != window__) {
				const auto windows_window = dynamic_cast<TitaniumWindows::UI::Window*>(window.get());
				const auto view = windows_window->getComponent();
				pivotItem__->Content = view;
			}

			Titanium::UI::Tab::set_window(window);
		}

		void Tab::blur()
		{
			if (window__) {
				window__->blur();
			}
			Titanium::UI::Tab::blur();
			set_titleColorByState();
		}

		void Tab::focus()
		{
			if (window__) {
				window__->focus();
			}
			Titanium::UI::Tab::focus();
			set_titleColorByState();
		}

		void Tab::set_titleColorByState()
		{
			const auto is_active = Titanium::UI::Tab::get_active();
			std::string colorName;
			if (is_active) {
				colorName = Titanium::UI::Tab::get_activeTitleColor();
			} else {
				colorName = Titanium::UI::Tab::get_titleColor();
			}
			const auto textBlock = safe_cast<Controls::TextBlock^>(pivotItem__->Header);
			if (textBlock == nullptr) {
				return;
			}
			if (colorName.empty()) {
				// if no color specified, try to get "default color" from current theme.
				if (is_active) {
					Platform::String^ key = "PivotHeaderForegroundSelectedBrush";
					if (Application::Current->Resources->HasKey(key)) {
						textBlock->Foreground = static_cast<Windows::UI::Xaml::Media::Brush^>(Application::Current->Resources->Lookup(key));
					}
				} else {
					Platform::String^ key = "PivotHeaderForegroundUnselectedBrush";
					if (Application::Current->Resources->HasKey(key)) {
						textBlock->Foreground = static_cast<Windows::UI::Xaml::Media::Brush^>(Application::Current->Resources->Lookup(key));
					}
				}
			} else {
				const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
				textBlock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
			}
		}

		void Tab::set_activeTitleColor(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_activeTitleColor(colorName);
			set_titleColorByState();
		}

		void Tab::set_titleColor(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_titleColor(colorName);
			set_titleColorByState();
		}

		void Tab::set_backgroundColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundColor(value);
			window__->getViewLayoutDelegate()->set_backgroundColor(value);
		}

		void Tab::set_backgroundImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundImage(value);
			window__->getViewLayoutDelegate()->set_backgroundImage(value);
		}

		void Tab::set_backgroundSelectedColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundSelectedColor(value);
			window__->getViewLayoutDelegate()->set_backgroundSelectedColor(value);
		}

		void Tab::set_backgroundSelectedImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundSelectedImage(value);
			window__->getViewLayoutDelegate()->set_backgroundSelectedImage(value);
		}

		void Tab::set_backgroundDisabledColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundDisabledColor(value);
			window__->getViewLayoutDelegate()->set_backgroundDisabledColor(value);
		}

		void Tab::set_backgroundDisabledImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundDisabledImage(value);
			window__->getViewLayoutDelegate()->set_backgroundDisabledImage(value);
		}

		void Tab::set_backgroundFocusedColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundFocusedColor(value);
			window__->getViewLayoutDelegate()->set_backgroundFocusedColor(value);
		}

		void Tab::set_backgroundFocusedImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_backgroundFocusedImage(value);
			window__->getViewLayoutDelegate()->set_backgroundFocusedImage(value);
		}

		void Tab::JSExportInitialize()
		{
			JSExport<Tab>::SetClassVersion(1);
			JSExport<Tab>::SetParent(JSExport<Titanium::UI::Tab>::Class());
		}

	}  // namespace UI
}  // namespace TitaniumWindows
