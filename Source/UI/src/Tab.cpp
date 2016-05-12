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
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			, defaultForeground__(nullptr)
#endif
		{
		}

		void Tab::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Tab::postCallAsConstructor(js_context, arguments);	

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			pivotItem__ = ref new PivotItem();

			Titanium::UI::Tab::setLayoutDelegate<WindowsViewLayoutDelegate>();
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(pivotItem__, nullptr, false);
#else
			grid__ = ref new Grid();
			Titanium::UI::Tab::setLayoutDelegate<WindowsViewLayoutDelegate>();
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(grid__, nullptr, false);
#endif
		}

		void Tab::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_title(title);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			const auto textBlock = ref new TextBlock();
			textBlock->Text = TitaniumWindows::Utility::ConvertUTF8String(title);
			pivotItem__->Header = textBlock;
#else

#endif
		}

		void Tab::set_window(const std::shared_ptr<Titanium::UI::Window>& window) TITANIUM_NOEXCEPT
		{
			if (window != window__) {
				const auto windows_window = dynamic_cast<TitaniumWindows::UI::Window*>(window.get());
				const auto view = windows_window->getComponent();
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
				pivotItem__->Content = view;
#else
				if (grid__->Children->Size > 0) {
					grid__->Children->RemoveAt(0);
				}
				grid__->Children->Append(view);
				grid__->SetColumn(view, 0);
				grid__->SetRow(view, 0);
#endif
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
			std::string colorName;
			if (Titanium::UI::Tab::get_active()) {
				colorName = Titanium::UI::Tab::get_activeColor();
			}
			else {
				colorName = Titanium::UI::Tab::get_titleColor();
			}
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			const auto textBlock = safe_cast<Controls::TextBlock^>(pivotItem__->Header);
			if (defaultForeground__ == nullptr) {
				defaultForeground__ = textBlock->Foreground;
			}
			if (colorName.empty()) {
				// Use the default colors if the new color is empty
				textBlock->Foreground = defaultForeground__;
			} else {
				textBlock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
			}
#else
			// FIXME What do we do for Win 8.1 store?
#endif
		}

		void Tab::set_activeColor(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Tab::set_activeColor(colorName);
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