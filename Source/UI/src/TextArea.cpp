/**
 * Titanium.UI.TextArea for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/TextArea.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Input;

		TextArea::TextArea(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::TextArea(js_context)
		{
		}

		void TextArea::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::TextArea::postCallAsConstructor(js_context, arguments);	
			
			text_box__ = ref new Windows::UI::Xaml::Controls::TextBox();
			text_box__->AcceptsReturn = true;

			border__ = ref new Controls::Border();
			border__->Child = text_box__;

			Titanium::UI::TextArea::setLayoutDelegate<WindowsViewLayoutDelegate>();
			const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			layout->setStyleComponent(text_box__);
			layout->setComponent(border__, nullptr, border__);
		}

		void TextArea::JSExportInitialize() {
			JSExport<TextArea>::SetClassVersion(1);
			JSExport<TextArea>::SetParent(JSExport<Titanium::UI::TextArea>::Class());
		}

		void TextArea::set_autocorrect(const bool& autocorrect) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_autocorrect(autocorrect);
			text_box__->IsSpellCheckEnabled = autocorrect;
		}

		void TextArea::set_color(const std::string& color) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_color(color);
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(color);
			text_box__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
		}

		void TextArea::set_editable(const bool& editable) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_editable(editable);
			text_box__->IsReadOnly = !editable;
		}

		void TextArea::set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_font(font);
			TitaniumWindows::UI::ViewHelper::SetFont<Windows::UI::Xaml::Controls::TextBox^>(get_context(), text_box__, font);
		}

		void TextArea::set_hintText(const std::string& hintText) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_hintText(hintText);
			text_box__->PlaceholderText = TitaniumWindows::Utility::ConvertUTF8String(hintText);
		}

		void TextArea::set_keyboardType(const Titanium::UI::KEYBOARD& keyboardType) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_keyboardType(keyboardType);
			auto scope_name = ref new Windows::UI::Xaml::Input::InputScopeName();
			if (keyboardType == Titanium::UI::KEYBOARD::ASCII) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Default;
			} else if (keyboardType == Titanium::UI::KEYBOARD::DECIMAL_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Number;
			} else if (keyboardType == Titanium::UI::KEYBOARD::DEFAULT) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Default;
			} else if (keyboardType == Titanium::UI::KEYBOARD::EMAIL) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::EmailSmtpAddress;
			} else if (keyboardType == Titanium::UI::KEYBOARD::NAMEPHONE_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::NameOrPhoneNumber;
			} else if (keyboardType == Titanium::UI::KEYBOARD::NUMBERS_PUNCTUATION) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::CurrencyAmountAndSymbol;
			} else if (keyboardType == Titanium::UI::KEYBOARD::NUMBER_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Number;
			} else if (keyboardType == Titanium::UI::KEYBOARD::PHONE_PAD) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::TelephoneNumber;
			} else if (keyboardType == Titanium::UI::KEYBOARD::URL) {
				scope_name->NameValue = Windows::UI::Xaml::Input::InputScopeNameValue::Url;
			} else {
				return;
			}
			auto scope = text_box__->InputScope;
			if (!scope) {
				scope = ref new Windows::UI::Xaml::Input::InputScope();
				text_box__->InputScope = scope;
			}
			scope->Names->Clear();
			scope->Names->Append(scope_name);
		}


		void TextArea::set_maxLength(const int32_t& maxLength) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_maxLength(maxLength);
			text_box__->MaxLength = maxLength;
		}

		Titanium::UI::TextAreaSelectedParams TextArea::get_selection() const TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextAreaSelectedParams params;
			params.location = text_box__->SelectionStart;
			params.length   = text_box__->SelectionLength;
			return params;
		}

		void TextArea::set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_textAlign(textAlign);
			if (textAlign == Titanium::UI::TEXT_ALIGNMENT::CENTER) {
				text_box__->TextAlignment = Windows::UI::Xaml::TextAlignment::Center;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::LEFT) {
				text_box__->TextAlignment = Windows::UI::Xaml::TextAlignment::Left;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::RIGHT) {
				text_box__->TextAlignment = Windows::UI::Xaml::TextAlignment::Right;
			} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::JUSTIFY) {
				text_box__->TextAlignment = Windows::UI::Xaml::TextAlignment::Justify;
			}
		}

		std::string TextArea::get_value() const TITANIUM_NOEXCEPT
		{
			return TitaniumWindows::Utility::ConvertUTF8String(text_box__->Text);
		}

		void TextArea::set_value(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_value(value);
			text_box__->Text = TitaniumWindows::Utility::ConvertUTF8String(value);
		}

		void TextArea::set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::set_verticalAlign(verticalAlign);
			if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM) {
				text_box__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER) {
				text_box__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP) {
				text_box__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
			}
			// TODO Windows supports stretch!
		}

		void TextArea::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::disableEvent(event_name);
			if (event_name == "change") {
				text_box__->TextChanged -= change_event__;
			} else if (event_name == "return") {
				text_box__->KeyDown -= return_event__;
			} else if (event_name == "selected") {
				text_box__->SelectionChanged -= select_event__;
			}
		}

		void TextArea::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextArea::enableEvent(event_name);
			const JSContext ctx = this->get_context();
			if (event_name == "change") {
				change_event__ = text_box__->TextChanged += ref new Controls::TextChangedEventHandler([this, ctx](Platform::Object^ sender, Controls::TextChangedEventArgs^ e) {
					try {
						JSObject eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));
						this->fireEvent("change", eventArgs);
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at TextArea.change");
					}
				});

			} else if (event_name == "return") {
				return_event__ = text_box__->KeyDown += ref new KeyEventHandler([this, ctx](Platform::Object^ sender, KeyRoutedEventArgs^ e) {
					if (e->Key == Windows::System::VirtualKey::Enter) {
						try {
							JSObject eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));
							this->fireEvent("return", eventArgs);
						} catch (...) {
							TITANIUM_LOG_DEBUG("Error at TextArea.return");
						}
					}
				});

			} else if (event_name == "selected") {
				select_event__ = text_box__->SelectionChanged += ref new RoutedEventHandler([this, ctx](Platform::Object^ sender, RoutedEventArgs^ e){
					if (text_box__->SelectionLength > 0) {
						try {
							Titanium::UI::TextAreaSelectedParams params;
							params.location = text_box__->SelectionStart;
							params.length = text_box__->SelectionLength;
							JSObject eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("range", TextAreaSelectedParams_to_js(ctx, params));
							this->fireEvent("selected", eventArgs);
						} catch (...) {
							TITANIUM_LOG_DEBUG("Error at TextArea.selected");
						}
					}
				});
			}
		}

	}  // namespace UI
}  // namespace TitaniumWindows