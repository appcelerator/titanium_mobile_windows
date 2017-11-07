/**
* Titanium.UI.TextField for Windows
*
* Copyright (c) 2014-2016 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/TextField.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <windows.h>
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Input;

		TextField::TextField(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::TextField(js_context)
		{
		}

		void TextField::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::TextField::postCallAsConstructor(js_context, arguments);

			Titanium::UI::TextField::setLayoutDelegate<WindowsViewLayoutDelegate>();

			// Parent of the text box.
			// TextField have to deal with multiple controls. (TextBox & PasswordBox)
			border__ = ref new Controls::Border();

			text_box__ = ref new Controls::TextBox();
			text_box__->AcceptsReturn = false;
			text_box__->IsSpellCheckEnabled = true;

			border__->Child = text_box__;

			const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			layout->setComponent(border__, nullptr, border__);
			layout->setStyleComponent(text_box__);
			initTextComponent();
		}

		void TextField::initTextComponent()
		{
			// TIMOB-19143: reset MinWidth to fix size issues
			if (text_box__) {
				text_box__->MinWidth = 0;
			} else if (password_box__) {
				password_box__->MinWidth = 0;
			}

		}

		void TextField::JSExportInitialize()
		{
			JSExport<TextField>::SetClassVersion(1);
			JSExport<TextField>::SetParent(JSExport<Titanium::UI::TextField>::Class());

			JSExport<TextField>::AddValueProperty("width", std::mem_fn(&js_get_width), std::mem_fn(&js_set_width_min));
		}

		void TextField::set_passwordMask(const bool& passwordMask) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_passwordMask(passwordMask);

			// password mask is little bit tricky here, because Xaml uses different component for it.
			// Now we need to dispose TextBox and inherit properties from it.
			// Don't forget to update layout delegate too...
			if (passwordMask && text_box__) {
				password_box__ = ref new Controls::PasswordBox();
				//password_box__->Foreground = ref new Media::SolidColorBrush(Windows::UI::Colors::Black);

				// set password box
				border__->Child = password_box__;

				// copy properties which we interested in
				password_box__->PlaceholderText = text_box__->PlaceholderText;
				password_box__->Password = text_box__->Text;
				password_box__->MaxLength = text_box__->MaxLength;
				password_box__->Width = text_box__->Width;
				password_box__->Height = text_box__->Height;

				password_box__->IsEnabled = !text_box__->IsReadOnly;
				password_box__->VerticalAlignment = text_box__->VerticalAlignment;

				// Update color based on property string
				set_color(get_color());

				// Update underlying control
				getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setUnderlyingControl(password_box__);

				text_box__ = nullptr;
			} else if (!passwordMask && password_box__) {
				text_box__ = ref new Controls::TextBox();
				text_box__->AcceptsReturn = false;
				text_box__->IsSpellCheckEnabled = true;

				// set text box
				border__->Child = text_box__;

				// copy properties which we interested in
				text_box__->PlaceholderText = password_box__->PlaceholderText;
				text_box__->Text = password_box__->Password;
				text_box__->MaxLength = password_box__->MaxLength;
				text_box__->Width = password_box__->Width;
				text_box__->Height = password_box__->Height;
				text_box__->IsReadOnly = !password_box__->IsEnabled;
				text_box__->VerticalAlignment = password_box__->VerticalAlignment;

				// Update color based on property string
				set_color(get_color());

				// Update underlying control
				getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setUnderlyingControl(password_box__);

				password_box__ = nullptr;
			}

			initTextComponent();
		}

		void TextField::set_color(const std::string& colorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_color(colorName);
			const auto color_obj = WindowsViewLayoutDelegate::ColorForName(colorName);
			const auto color_brush = ref new Media::SolidColorBrush(color_obj);
			if (text_box__) {
				text_box__->Foreground = color_brush;
			} else if (password_box__) {
				password_box__->Foreground = color_brush;
			}
		}

		void TextField::set_editable(const bool& editable) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_editable(editable);
			if (text_box__) {
				text_box__->IsReadOnly = !editable;
			} else if (password_box__) {
				// there's no IsReadOnly property in PasswordBox.
				password_box__->IsEnabled = !editable;
			}
		}

		void TextField::set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_font(font);
			if (text_box__) {
				TitaniumWindows::UI::ViewHelper::SetFont<Controls::TextBox^>(get_context(), text_box__, font);
			} else if (password_box__) {
				TitaniumWindows::UI::ViewHelper::SetFont<Controls::PasswordBox^>(get_context(), password_box__, font);
			}
		}

		void TextField::set_hintText(const std::string& hintText) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_hintText(hintText);
			if (text_box__) {
				text_box__->PlaceholderText = TitaniumWindows::Utility::ConvertUTF8String(hintText);
			} else if (password_box__) {
				password_box__->PlaceholderText = TitaniumWindows::Utility::ConvertUTF8String(hintText);
			}
		}

		void TextField::set_keyboardType(const Titanium::UI::KEYBOARD& keyboardType) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_keyboardType(keyboardType);
			if (text_box__) {
				auto scope_name = ref new InputScopeName();
				if (keyboardType == Titanium::UI::KEYBOARD::ASCII) {
					scope_name->NameValue = InputScopeNameValue::Default;
				} else if (keyboardType == Titanium::UI::KEYBOARD::DECIMAL_PAD) {
					scope_name->NameValue = InputScopeNameValue::Number;
				} else if (keyboardType == Titanium::UI::KEYBOARD::DEFAULT) {
					scope_name->NameValue = InputScopeNameValue::Default;
				} else if (keyboardType == Titanium::UI::KEYBOARD::EMAIL) {
					scope_name->NameValue = InputScopeNameValue::EmailSmtpAddress;
				} else if (keyboardType == Titanium::UI::KEYBOARD::NAMEPHONE_PAD) {
					scope_name->NameValue = InputScopeNameValue::NameOrPhoneNumber;
				} else if (keyboardType == Titanium::UI::KEYBOARD::NUMBERS_PUNCTUATION) {
					scope_name->NameValue = InputScopeNameValue::CurrencyAmountAndSymbol;
				} else if (keyboardType == Titanium::UI::KEYBOARD::NUMBER_PAD) {
					scope_name->NameValue = InputScopeNameValue::Number;
				} else if (keyboardType == Titanium::UI::KEYBOARD::PHONE_PAD) {
					scope_name->NameValue = InputScopeNameValue::TelephoneNumber;
				} else if (keyboardType == Titanium::UI::KEYBOARD::URL) {
					scope_name->NameValue = InputScopeNameValue::Url;
				} else {
					return;
				}
				auto scope = text_box__->InputScope;
				if (!scope) {
					scope = ref new InputScope();
					text_box__->InputScope = scope;
				}
				text_box__->InputScope->Names->Clear();
				text_box__->InputScope->Names->Append(scope_name);
			} else {
				TITANIUM_MODULE_LOG_WARN("TextField.keyboardType can not be used with passwordMask");
			}
		}

		void TextField::set_maxLength(const int32_t& maxLength) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_maxLength(maxLength);
			if (text_box__) {
				text_box__->MaxLength = maxLength;
			} else if (password_box__) {
				password_box__->MaxLength = maxLength;
			}
		}

		void TextField::set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_textAlign(textAlign);
			if (text_box__) {
				if (textAlign == Titanium::UI::TEXT_ALIGNMENT::CENTER) {
					text_box__->TextAlignment = TextAlignment::Center;
				} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::LEFT) {
					text_box__->TextAlignment = TextAlignment::Left;
				} else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::RIGHT) {
					text_box__->TextAlignment = TextAlignment::Right;
				}
				// TODO Windows supports JUSTIFY!
			} else {
				TITANIUM_LOG_WARN("TexeField.textAlign can not be used with passwordMask");
			}
		}

		std::string TextField::get_value() const TITANIUM_NOEXCEPT
		{
			if (text_box__) {
				return TitaniumWindows::Utility::ConvertUTF8String(text_box__->Text);
			} else if (password_box__) {
				return TitaniumWindows::Utility::ConvertUTF8String(password_box__->Password);
			}
			return "";
		}

		void TextField::set_value(const std::string& value) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_value(value);
			if (text_box__) {
				text_box__->Text = TitaniumWindows::Utility::ConvertUTF8String(value);
			} else if (password_box__) {
				password_box__->Password = TitaniumWindows::Utility::ConvertUTF8String(value);
			}
		}

		void TextField::set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::set_verticalAlign(verticalAlign);
			auto align = VerticalAlignment::Center;
			if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM) {
				align = VerticalAlignment::Bottom;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER) {
				align = VerticalAlignment::Center;
			} else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP) {
				align = VerticalAlignment::Top;
			}
			// TODO Windows supports stretch!

			if (text_box__) {
				text_box__->VerticalAlignment = align;
			} else if (password_box__) {
				password_box__->VerticalAlignment = align;
			}
		}

		void TextField::focus() TITANIUM_NOEXCEPT
		{
			if (text_box__) {
				text_box__->Focus(FocusState::Programmatic);
			} else if (password_box__) {
				password_box__->Focus(FocusState::Programmatic);
			}
		}

		bool TextField::hasText() TITANIUM_NOEXCEPT
		{
			if (text_box__) {
				return !text_box__->Text->IsEmpty();
			} else if (password_box__) {
				return !password_box__->Password->IsEmpty();
			}
			return false;
		}

		void TextField::setSelection(const std::uint32_t& start, const std::uint32_t& end) TITANIUM_NOEXCEPT
		{
			if (text_box__) {
				// We just ignore invalid range. Use native Length() method to avoid manual unicode handling
				if (start >= text_box__->Text->Length() || end > text_box__->Text->Length()) {
					return;
				}
				text_box__->Select(start, (end - start));
			} else if (password_box__) {
				//
				// Windows PasswordBox doesn't support selection with range. 
				//
				TITANIUM_LOG_WARN("TextField.setSelection doesn't work with passwordMask on Windows");
			}
		}


		void TextField::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::disableEvent(event_name);
			if (event_name == "change") {
				if (text_box__) {
					text_box__->TextChanged -= change_event__;
				} else if (password_box__) {
					password_box__->PasswordChanged -= change_event__;
				}
			} else if (event_name == "return") {
				if (text_box__) {
					text_box__->KeyDown -= return_event__;
				} else if (password_box__) {
					password_box__->KeyDown -= return_event__;
				}
			}
		}

		void TextField::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TextField::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			if (event_name == "change") {
				if (text_box__) {
					change_event__ = text_box__->TextChanged += ref new Controls::TextChangedEventHandler([this, ctx](Platform::Object^ sender, Controls::TextChangedEventArgs^ e) {
						try {
							JSObject eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));

							this->fireEvent("change", eventArgs);
						} catch (...) {
							TITANIUM_LOG_DEBUG("Error at TextField.change");
						}
					});
				} else if (password_box__) {
					change_event__ = password_box__->PasswordChanged += ref new RoutedEventHandler([this, ctx](Platform::Object^ sender, RoutedEventArgs^ e){
						try {
							JSObject eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));

							this->fireEvent("change", eventArgs);
						} catch (...) {
							TITANIUM_LOG_DEBUG("Error at TextField.change");
						}
					});
				}
			} else if (event_name == "return") {
				const auto keydown = ref new KeyEventHandler([this, ctx](Platform::Object^ sender, KeyRoutedEventArgs^ e) {
					try {
						// TIMOB-24371: Enter event fired twice due to a bug in Xaml KeyDown event, here's a workaround
						if (e->Key == Windows::System::VirtualKey::Enter && e->KeyStatus.RepeatCount == 0) {
							JSObject eventArgs = ctx.CreateObject();
							eventArgs.SetProperty("value", ctx.CreateString(this->get_value()));

							this->fireEvent("return", eventArgs);
						}
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at TextField.change");
					}
				});
				if (text_box__) {
					return_event__ = text_box__->KeyDown += keydown;
				} else if (password_box__) {
					return_event__ = password_box__->KeyDown += keydown;
				}
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
