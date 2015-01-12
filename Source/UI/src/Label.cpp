/**
* Titanium.UI.Label for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Label.hpp"

#define DEFAULT_FONT_SIZE 20

namespace TitaniumWindows { namespace UI {

  Label::Label(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::UI::Label(js_context)
    , label__(ref new Windows::UI::Xaml::Controls::TextBlock()) {
    TITANIUM_LOG_DEBUG("Label::ctor Initialize");
  }

  Label::Label(const Label& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		: Titanium::UI::Label(rhs, arguments)
    , label__(ref new Windows::UI::Xaml::Controls::TextBlock()) {
	label__->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
	label__->TextTrimming = Windows::UI::Xaml::TextTrimming::Clip;
	label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
	label__->FontSize = DEFAULT_FONT_SIZE;
	setComponent(label__);
    TITANIUM_LOG_DEBUG("Label::ctor CallAsConstructor");
  }

  void Label::JSExportInitialize() {
    JSExport<Label>::SetClassVersion(1);
    JSExport<Label>::SetParent(JSExport<Titanium::UI::Label>::Class());
  }

  void Label::set_color(const JSValue& color) TITANIUM_NOEXCEPT {
    Titanium::UI::Label::set_color(color);
    std::string colorName = static_cast<std::string>(color);
    const auto color_obj = ColorForName(colorName);
    label__->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(color_obj);
  }

  void Label::set_text(const JSValue& text) TITANIUM_NOEXCEPT {
    Titanium::UI::Label::set_text(text);
    std::string text_string = static_cast<std::string>(text);
    label__->Text = ref new Platform::String(std::wstring(text_string.begin(), text_string.end()).c_str());
  }

  void Label::set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT {
    Titanium::UI::Label::set_textAlign(textAlign);
    if (textAlign == Titanium::UI::TEXT_ALIGNMENT::CENTER) {
      label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Center;
    }
    else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::LEFT) {
      label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Left;
    }
    else if (textAlign == Titanium::UI::TEXT_ALIGNMENT::RIGHT) {
      label__->TextAlignment = Windows::UI::Xaml::TextAlignment::Right;
    }
    // TODO Windows supports JUSTIFY!
  }

  void Label::set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT {
    Titanium::UI::Label::set_verticalAlign(verticalAlign);
    if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM) {
      label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;
    }
    else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER) {
      label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
    }
    else if (verticalAlign == Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP) {
      label__->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
    }
    // TODO Windows supports stretch!
  }

  void Label::set_wordWrap(const JSValue& wordWrap) TITANIUM_NOEXCEPT {
    Titanium::UI::Label::set_wordWrap(wordWrap);
    bool is_wrapping = static_cast<bool>(wordWrap);
    label__->TextWrapping = is_wrapping ? Windows::UI::Xaml::TextWrapping::Wrap : Windows::UI::Xaml::TextWrapping::NoWrap;
  }

  void Label::set_fontFamily(const JSValue& family) TITANIUM_NOEXCEPT {
    std::string text_string = static_cast<std::string>(family);
    label__->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily(ref new Platform::String(std::wstring(text_string.begin(), text_string.end()).c_str()));
  }

  void Label::set_fontSize(const JSValue& size) TITANIUM_NOEXCEPT {
    label__->FontSize = static_cast<double>(size);
  }

  void Label::set_fontStyle(const JSValue& style) TITANIUM_NOEXCEPT {
    std::string text_string = static_cast<std::string>(style);
    if (text_string == "italic") {
      label__->FontStyle = Windows::UI::Text::FontStyle::Italic;
    }
    else if (text_string == "normal") {
      label__->FontStyle = Windows::UI::Text::FontStyle::Normal;
    }
    // TODO Windows supports Oblique: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontstyle.aspx
  }

  void Label::set_fontWeight(const JSValue& weight) TITANIUM_NOEXCEPT {
    std::string text_string = static_cast<std::string>(weight);
    if (text_string == "bold") {
      label__->FontWeight = Windows::UI::Text::FontWeights::Bold;
    }
    else if (text_string == "normal") {
      label__->FontWeight = Windows::UI::Text::FontWeights::Normal;
    }
    else if (text_string == "semibold") {
      label__->FontWeight = Windows::UI::Text::FontWeights::SemiBold;
    }
    // TODO Windows supports a large number of other weights: http://msdn.microsoft.com/en-us/library/windows/apps/windows.ui.text.fontweights
  }

  void Label::set_textStyle(const Titanium::UI::TEXT_STYLE& textStyle) TITANIUM_NOEXCEPT {
    Titanium::UI::Label::set_textStyle(textStyle);
  }

  bool Label::setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Label::setTopArgumentValidator: top = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, static_cast<std::string>(argument));
    set_top(argument);
    result = true;
    return result;
  }

  bool Label::setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Label::setLeftArgumentValidator: left = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, static_cast<std::string>(argument));
    set_left(argument);
    result = true;
    return result;
  }

  bool Label::setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Label::setWidthArgumentValidator: width = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, static_cast<std::string>(argument));
    set_width(argument);
    result = true;
    return result;
  }

  bool Label::setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
    TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
    bool result = false;
    std::string value = static_cast<std::string>(argument);
    TITANIUM_LOG_INFO("Label::setHeightArgumentValidator: height = ", value);
    setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, static_cast<std::string>(argument));
    set_height(argument);
    result = true;
    return result;
  }

  void Label::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT {
    TITANIUM_LOG_DEBUG("Label::enableEvent: (event name '", event_name, "'");

    const JSContext  ctx = this->get_context();

    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml;

    if (event_name == "click") {
      if (click_event_count_ == 0) {
        click_event_ = getComponent()->Tapped += ref new TappedEventHandler([this, ctx](Platform::Object ^ sender, TappedRoutedEventArgs ^ e) {
          auto component = safe_cast<FrameworkElement^>(sender);
          auto position = e->GetPosition(component);

          JSObject  eventArgs = ctx.CreateObject();
          eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
          eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

          this->fireEvent("click", eventArgs);
        });
      }

      ++click_event_count_;

      return;
    }
  }

}}  // namespace TitaniumWindows { namespace UI {
