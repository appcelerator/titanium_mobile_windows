/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Label.hpp"

namespace Titanium
{
	namespace UI
	{
		Label::Label(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : UIBase(js_context),
		      color__(js_context.CreateString()),
		      text__(js_context.CreateString()),
		      textAlign__(TEXT_ALIGNMENT::LEFT),
		      verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER),
		      wordWrap__(js_context.CreateBoolean(true)),
		      font__(js_context.CreateObject())
		{
		}

		std::string Label::get_text() const TITANIUM_NOEXCEPT
		{
			return text__;
		}

		void Label::set_text(const std::string& text) TITANIUM_NOEXCEPT
		{
			text__ = text;
		}

		TEXT_ALIGNMENT Label::get_textAlign() const TITANIUM_NOEXCEPT
		{
			return textAlign__;
		}

		void Label::set_textAlign(const TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			textAlign__ = textAlign;
		}

		TEXT_VERTICAL_ALIGNMENT Label::get_verticalAlign() const TITANIUM_NOEXCEPT
		{
			return verticalAlign__;
		}

		void Label::set_verticalAlign(const TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			verticalAlign__ = verticalAlign;
		}

		bool Label::get_wordWrap() const TITANIUM_NOEXCEPT
		{
			return wordWrap__;
		}

		void Label::set_wordWrap(const bool& wordWrap) TITANIUM_NOEXCEPT
		{
			wordWrap__ = wordWrap;
		}

		std::string Label::get_color() const TITANIUM_NOEXCEPT
		{
			return color__;
		}

		void Label::set_color(const std::string& color) TITANIUM_NOEXCEPT
		{
			color__ = color;
		}

		JSValue Label::get_font() const TITANIUM_NOEXCEPT
		{
			return font__;
		}

		void Label::set_fontFamily(const std::string& family) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_fontFamily: Unimplemented");
		}

		void Label::set_fontSize(const JSValue& size) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_fontSize: Unimplemented");
		}

		void Label::set_fontStyle(const std::string& style) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_fontStyle: Unimplemented");
		}

		void Label::set_fontWeight(const std::string& weight) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_fontWeight: Unimplemented");
		}

		void Label::set_textStyle(const TEXT_STYLE& textStyle) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_textStyle: Unimplemented");
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void Label::JSExportInitialize()
		{
			JSExport<Label>::SetClassVersion(1);
			JSExport<Label>::SetParent(JSExport<UIBase>::Class());
			JSExport<Label>::AddValueProperty("color", std::mem_fn(&Label::js_get_color), std::mem_fn(&Label::js_set_color));
			JSExport<Label>::AddValueProperty("font", std::mem_fn(&Label::js_get_font), std::mem_fn(&Label::js_set_font));
			JSExport<Label>::AddValueProperty("text", std::mem_fn(&Label::js_get_text), std::mem_fn(&Label::js_set_text));
			JSExport<Label>::AddValueProperty("textAlign", std::mem_fn(&Label::js_get_textAlign), std::mem_fn(&Label::js_set_textAlign));
			JSExport<Label>::AddValueProperty("verticalAlign", std::mem_fn(&Label::js_get_verticalAlign), std::mem_fn(&Label::js_set_verticalAlign));
			JSExport<Label>::AddValueProperty("wordWrap", std::mem_fn(&Label::js_get_wordWrap), std::mem_fn(&Label::js_set_wordWrap));
		}

		JSValue Label::js_get_color() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_color());
		}

		bool Label::js_set_color(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		JSValue Label::js_get_font() const TITANIUM_NOEXCEPT
		{
			return get_font();
		}

		bool Label::js_set_font(const JSValue& font) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(font.IsObject());
			// FIXME Should we save the individual values? We're not making a copy of the object here!
			font__ = static_cast<JSObject>(font);

			// Number/String
			if (font__.HasProperty("fontSize")) {
				const auto font_size = font__.GetProperty("fontSize");
				TITANIUM_ASSERT(font_size.IsString() || font_size.IsNumber());
				set_fontSize(font_size);
			}

			// bold or normal
			if (font__.HasProperty("fontWeight")) {
				const auto font_weight = font__.GetProperty("fontWeight");
				TITANIUM_ASSERT(font_weight.IsString());
				set_fontWeight(static_cast<std::string>(font_weight));
			}

			// italic or normal
			if (font__.HasProperty("fontStyle")) {
				const auto font_style = font__.GetProperty("fontStyle");
				TITANIUM_ASSERT(font_style.IsString());
				set_fontFamily(static_cast<std::string>(font_style));
			}

			// String
			if (font__.HasProperty("fontFamily")) {
				const auto font_family = font__.GetProperty("fontFamily");
				TITANIUM_ASSERT(font_family.IsString());
				set_fontFamily(static_cast<std::string>(font_family));
			}

			// String Titanium::UI::TEXT_STYLE constants
			if (font__.HasProperty("textStyle")) {
				const auto font_text_style = font__.GetProperty("textStyle");
				TITANIUM_ASSERT(font_text_style.IsString());
				set_textStyle(Constants::to_TEXT_STYLE(static_cast<std::string>(font_text_style)));
			}

			return true;
		}

		JSValue Label::js_get_text() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(text__);
		}

		bool Label::js_set_text(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_text(static_cast<std::string>(argument));
			return true;
		}

		JSValue Label::js_get_textAlign() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		bool Label::js_set_textAlign(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			bool result = false;
			if (argument.IsNumber()) {
				set_textAlign(Constants::to_TEXT_ALIGNMENT(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(argument)));
				result = true;
			} else if (argument.IsString()) {
				set_textAlign(Constants::to_TEXT_ALIGNMENT(static_cast<std::string>(argument)));
				result = true;
			}

			return result;
		}

		JSValue Label::js_get_verticalAlign() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		bool Label::js_set_verticalAlign(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			bool result = false;
			if (argument.IsNumber()) {
				set_verticalAlign(Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(argument)));
				result = true;
			} else if (argument.IsString()) {
				set_verticalAlign(Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::string>(argument)));
				result = true;
			}

			return result;
		}

		JSValue Label::js_get_wordWrap() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(wordWrap__);
		}

		bool Label::js_set_wordWrap(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_wordWrap(static_cast<bool>(argument));
			return true;
		}
	} // namespace UI
}  // namespace Titanium
