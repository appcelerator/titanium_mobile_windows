/**
* Titanium.UI.PickerRow for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/PickerRow.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace Windows::UI::Xaml::Controls;

		PickerRow::PickerRow(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::PickerRow(js_context)
		{
			TITANIUM_LOG_DEBUG("PickerRow::ctor ", this);
		}

		PickerRow::~PickerRow() 
		{
			TITANIUM_LOG_DEBUG("PickerRow::dtor ", this);
		}

		void PickerRow::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::PickerRow::postCallAsConstructor(js_context, arguments);
			item__  = ref new ComboBoxItem();
			label__ = ref new TextBlock();
			item__->Content = label__;

			Titanium::UI::PickerRow::setLayoutDelegate<WindowsViewLayoutDelegate>();
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(item__, nullptr, false);
		}

		void PickerRow::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::PickerRow::set_color(colorName);
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
			label__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void PickerRow::set_title(const std::string& text) TITANIUM_NOEXCEPT
		{
			Titanium::UI::PickerRow::set_title(text);
			label__->Text = TitaniumWindows::Utility::ConvertUTF8String(text);
		}

		void PickerRow::set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT
		{
			Titanium::UI::PickerRow::set_font(font);
			TitaniumWindows::UI::ViewHelper::SetFont(get_context(), label__, font);
		}

		void PickerRow::JSExportInitialize()
		{
			JSExport<PickerRow>::SetClassVersion(1);
			JSExport<PickerRow>::SetParent(JSExport<Titanium::UI::PickerRow>::Class());
		}

	} // namespace UI
} // namespace TitaniumWindows
