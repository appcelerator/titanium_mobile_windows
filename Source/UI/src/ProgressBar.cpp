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

		void ProgressBarLayoutDelegate::set_borderWidth(const std::string& borderWidth) TITANIUM_NOEXCEPT
		{
			WindowsViewLayoutDelegate::set_borderWidth(borderWidth);

			// set margin to the progress bar to make both border and bar shown.
			auto margin = bar__->Margin;
			margin.Bottom = Titanium::LayoutEngine::parseUnitValue(borderWidth, Titanium::LayoutEngine::ValueType::Fixed, WindowsViewLayoutDelegate::ComputePPI(Titanium::LayoutEngine::ValueName::Width), "px") * 2;
			bar__->Margin = margin;
		}

		void ProgressBar::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) 
		{
			Titanium::UI::ProgressBar::postCallAsConstructor(js_context, arguments);

			// use stack panel because ProgressBar needs label & bar
			panel__ = ref new Windows::UI::Xaml::Controls::StackPanel();
			panel__->Orientation = Windows::UI::Xaml::Controls::Orientation::Vertical;

			bar__ = ref new Windows::UI::Xaml::Controls::ProgressBar();
			bar__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Gray);

			sizechanged_event__ = panel__->SizeChanged += ref new SizeChangedEventHandler([this](Platform::Object^ sender, SizeChangedEventArgs^ e) {
				try {
					const auto fill = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL);
					const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();

					if (layout->get_height() != fill) {
						// relative position from container should start from top & left
						panel__->VerticalAlignment = VerticalAlignment::Top;
						layout->set_height(std::to_string(e->NewSize.Height));
					}
					else {
						panel__->VerticalAlignment = VerticalAlignment::Stretch;
					}

					if (layout->get_width() != fill) {
						// relative position from container should start from top & left
						panel__->HorizontalAlignment = HorizontalAlignment::Left;
						layout->set_width(std::to_string(e->NewSize.Width));
					}
					else {
						panel__->HorizontalAlignment = HorizontalAlignment::Stretch;
					}
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error while ProgressBar::SizeChanged");
				}
			});

			label__ = ref new Windows::UI::Xaml::Controls::TextBlock();
			label__->Text = "";

			label__->FontSize = TitaniumWindows::UI::Label::DefaultFontSize;
			label__->HorizontalAlignment = HorizontalAlignment::Center;

			panel__->Children->Append(label__);
			panel__->Children->Append(bar__);

			Titanium::UI::ProgressBar::setLayoutDelegate<ProgressBarLayoutDelegate>(bar__);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::SIZE);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::SIZE);
			getViewLayoutDelegate<ProgressBarLayoutDelegate>()->setComponent(panel__);
		}

		ProgressBar::ProgressBar(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::ProgressBar(js_context)
		{
			TITANIUM_LOG_DEBUG("ProgressBar::ctor Initialize");
		}

		ProgressBar::~ProgressBar()
		{
			if (panel__) {
				panel__->SizeChanged -= sizechanged_event__;
			}
		}

		void ProgressBar::JSExportInitialize() 
		{
			JSExport<ProgressBar>::SetClassVersion(1);
			JSExport<ProgressBar>::SetParent(JSExport<Titanium::UI::ProgressBar>::Class());
		}

		void ProgressBar::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_color(colorName);
			label__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(colorName));
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

		void ProgressBar::set_tintColor(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_tintColor(colorName);
			bar__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(colorName));
		}

		void ProgressBar::set_trackTintColor(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_trackTintColor(colorName);
			bar__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(colorName));
		}

		void ProgressBar::set_value(const double& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ProgressBar::set_value(value);
			bar__->Value = value;
		}

	}  // namespace UI
}  // namespace TitaniumWindows