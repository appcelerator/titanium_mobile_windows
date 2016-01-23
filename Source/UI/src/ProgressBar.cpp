/**
 * Titanium.UI.ProgressBar for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/ProgressBar.hpp"
#include "TitaniumWindows/UI/Label.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml;

		ProgressBarLayoutDelegate::ProgressBarLayoutDelegate(Windows::UI::Xaml::Controls::ProgressBar^ bar) TITANIUM_NOEXCEPT
			: WindowsViewLayoutDelegate()
			, bar__(bar) 
			, isIndeterminate__(bar->IsIndeterminate)
		{
			TITANIUM_LOG_DEBUG("ActivityIndicatorLayoutDelegate::ctor");
		}

		void ProgressBarLayoutDelegate::show() TITANIUM_NOEXCEPT
		{
			WindowsViewLayoutDelegate::show();
			bar__->IsIndeterminate = isIndeterminate__;
		}

		void ProgressBarLayoutDelegate::hide() TITANIUM_NOEXCEPT
		{
			WindowsViewLayoutDelegate::hide();
			// Turn off IsIndeterminate when not needed
			isIndeterminate__ = bar__->IsIndeterminate;
			bar__->IsIndeterminate = false;
		}

		void ProgressBar::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			Titanium::UI::ProgressBar::postCallAsConstructor(js_context, arguments);

			// use stack panel because ProgressBar needs label & bar
			panel__ = ref new Windows::UI::Xaml::Controls::StackPanel();
			panel__->Orientation = Windows::UI::Xaml::Controls::Orientation::Vertical;

			bar__ = ref new Windows::UI::Xaml::Controls::ProgressBar();
			backgroundColorBrush__ = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Gray);
			bar__->Background = backgroundColorBrush__;
			bar__->IsEnabledChanged += ref new Windows::UI::Xaml::DependencyPropertyChangedEventHandler(
				[=](Platform::Object^ sender, DependencyPropertyChangedEventArgs^ e) {
					auto control = dynamic_cast<Windows::UI::Xaml::Controls::Control^>(sender);
					if (control->IsEnabled) {
						control->Background = backgroundColorBrush__;
					} else {
						control->Background = backgroundDisabledColorBrush__;
					}
				}
			);

			label__ = ref new Windows::UI::Xaml::Controls::TextBlock();
			label__->Text = "";

			label__->FontSize = TitaniumWindows::UI::Label::DefaultFontSize;

			// relative position from container should start from top & left
			panel__->VerticalAlignment = VerticalAlignment::Top;
			panel__->HorizontalAlignment = HorizontalAlignment::Left;
			label__->HorizontalAlignment = HorizontalAlignment::Center;

			panel__->Children->Append(label__);
			panel__->Children->Append(bar__);

			Titanium::UI::ProgressBar::setLayoutDelegate<ProgressBarLayoutDelegate>(bar__);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			getViewLayoutDelegate<ProgressBarLayoutDelegate>()->setComponent(panel__);
		}

		ProgressBar::ProgressBar(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::ProgressBar(js_context)
		{
			TITANIUM_LOG_DEBUG("ProgressBar::ctor Initialize");
		}

		void ProgressBar::JSExportInitialize() 
		{
			JSExport<ProgressBar>::SetClassVersion(1);
			JSExport<ProgressBar>::SetParent(JSExport<Titanium::UI::ProgressBar>::Class());
		}

		void ProgressBar::set_message(const std::string& message) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_message(message);
			label__->Text = TitaniumWindows::Utility::ConvertUTF8String(message);
		}

		void ProgressBar::set_min(const double& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_min(value);
			bar__->Minimum = value;
		}

		void ProgressBar::set_max(const double& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_max(value);
			bar__->Maximum = value;
		}

		void ProgressBar::set_value(const double& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_value(value);
			bar__->Value = value;
		}

		void ProgressBar::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_color(colorName);
			bar__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(colorName));
		}

		void ProgressBar::set_backgroundColor(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_backgroundColor(colorName);
			backgroundColorBrush__ = ref new Windows::UI::Xaml::Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(colorName));
			if (bar__->IsEnabled) {
				bar__->Background = backgroundColorBrush__;
			}
		}
		
		void ProgressBar::set_backgroundDisabledColor(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_backgroundDisabledColor(colorName);
			backgroundDisabledColorBrush__ = ref new Windows::UI::Xaml::Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(colorName));
			if (!bar__->IsEnabled) {
				bar__->Background = backgroundDisabledColorBrush__;
			}
		}

	}  // namespace UI
}  // namespace TitaniumWindows