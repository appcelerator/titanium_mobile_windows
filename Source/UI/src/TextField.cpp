/**
* Titanium.UI.TextField for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/TextField.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		TextField::TextField(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::TextField(js_context)
		{
		}

		void TextField::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::TextField::postCallAsConstructor(js_context, arguments);	
			
			text_box__ = ref new Windows::UI::Xaml::Controls::TextBox();
			text_box__->AcceptsReturn = false;
			text_box__->IsSpellCheckEnabled = true;

			Titanium::UI::TextField::setLayoutDelegate<WindowsViewLayoutDelegate>();
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(text_box__);
		}

		void TextField::JSExportInitialize()
		{
			JSExport<TextField>::SetClassVersion(1);
			JSExport<TextField>::SetParent(JSExport<Titanium::UI::TextField>::Class());

			JSExport<TextField>::AddValueProperty("width", std::mem_fn(&js_get_width), std::mem_fn(&js_set_width_min));
		}

		void TextField::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_color(colorName);
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
			text_box__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void TextField::set_editable(const bool& editable) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_editable(editable);
			text_box__->IsReadOnly = !editable;
		}

		void TextField::set_hintText(const std::string& hintText) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_hintText(hintText);
			text_box__->PlaceholderText = TitaniumWindows::Utility::ConvertUTF8String(hintText);
		}

		void TextField::set_keyboardType(const Titanium::UI::KEYBOARD& keyboardType) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_keyboardType(keyboardType);
			auto scope_name = ref new Windows::UI::Xaml::Input::InputScopeName();
			if (keyboardType == Titanium::UI::KEYBOARD::ASCII) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Default;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::DECIMAL_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Number;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::DEFAULT) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Default;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::EMAIL) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::EmailSmtpAddress;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::NAMEPHONE_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::NameOrPhoneNumber;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::NUMBERS_PUNCTUATION) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::CurrencyAmountAndSymbol;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::NUMBER_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Number;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::PHONE_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::TelephoneNumber;
			}
			else if (keyboardType == Titanium::UI::KEYBOARD::URL) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Url;
			}
			else {
				return;
			}
			text_box__->InputScope->Names->Clear();
			text_box__->InputScope->Names->Append(scope_name);
		}

		void TextField::set_maxLength(const int32_t& maxLength) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_maxLength(maxLength);
			text_box__->MaxLength = maxLength;
		}

		void TextField::set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_textAlign(textAlign);
			if (textAlign == Titanium::UI::TEXT_ALIGNMENT::CENTER) {
				text_box__->TextAlignment = Windows::UI::Xaml::TextAlignment::Center;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::LEFT) {
				text_box__->TextAlignment = Windows::UI::Xaml::TextAlignment::Left;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::RIGHT) {
				text_box__->TextAlignment = Windows::UI::Xaml::TextAlignment::Right;
			}
			// TODO Windows supports JUSTIFY!
		}

		std::string TextField::get_value() const TITANIUM_NOEXCEPT
		{
			return TitaniumWindows::Utility::ConvertUTF8String(text_box__->Text);
		}

		void TextField::set_value(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_value(value);
			text_box__->Text = TitaniumWindows::Utility::ConvertUTF8String(value);
		}

		void TextField::set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_verticalAlign(verticalAlign);
			if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM) {
				text_box__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER) {
				text_box__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP) {
				text_box__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
			}
			// TODO Windows supports stretch!
		}

		void TextField::blur() TITANIUM_NOEXCEPT
		{
			// TODO Windows doesn't allow forcibly losing focus, need to set focus on another control to achieve it! Can we set focus on the window or parent or something?
		}

		void TextField::focus() TITANIUM_NOEXCEPT
		{
			text_box__->Focus(Windows::UI::Xaml::FocusState::Programmatic);
		}

		bool TextField::hasText() TITANIUM_NOEXCEPT
		{
			return !text_box__->Text->IsEmpty();
		}

		void TextField::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			if (event_name == "blur") {
				blur_event_ = text_box__->LostFocus += ref new RoutedEventHandler([this, ctx](Platform::Object^ sender, RoutedEventArgs^ e) {
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));

					this->fireEvent("blur", eventArgs);
				});
				return;
			} else if (event_name == "change") {
				change_event_ = text_box__->TextChanged += ref new Controls::TextChangedEventHandler([this, ctx](Platform::Object^ sender, Controls::TextChangedEventArgs^ e) {
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));

					this->fireEvent("change", eventArgs);
				});
				return;
			} else if (event_name == "focus") {
				focus_event_ = text_box__->GotFocus += ref new RoutedEventHandler([this, ctx](Platform::Object^ sender, RoutedEventArgs^ e) {
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));

					this->fireEvent("focus", eventArgs);
				});
				return;
			} else if (event_name == "return") {
				return_event_ = text_box__->KeyDown += ref new KeyEventHandler([this, ctx](Platform::Object^ sender, KeyRoutedEventArgs^ e) {
					if (e->Key == Windows::System::VirtualKey::Enter) {
						JSObject eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));

						this->fireEvent("return", eventArgs);
					}
				});
				return;
			}
		}

		bool TextField::js_set_width_min(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			js_set_width(argument);
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			layoutDelegate__->set_minWidth(static_cast<std::string>(argument));
			return true;
		}

	} // namespace UI
} // namespace TitaniumWindows
