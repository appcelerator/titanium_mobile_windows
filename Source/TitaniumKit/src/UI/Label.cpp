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
		Label::Label(const JSContext& js_context) TITANIUM_NOEXCEPT : View(js_context),
		                                                              color__(js_context.CreateString()),
		                                                              text__(js_context.CreateString()),
		                                                              textAlign__(TEXT_ALIGNMENT::LEFT),
		                                                              verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER),
		                                                              wordWrap__(js_context.CreateBoolean(true)),
		                                                              font__(js_context.CreateObject())
		{
		}

		Label::Label(const Label& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : View(rhs, arguments),
		      color__(rhs.color__),
		      text__(rhs.text__),
		      textAlign__(rhs.textAlign__),
		      verticalAlign__(rhs.verticalAlign__),
		      wordWrap__(rhs.wordWrap__),
		      font__(rhs.font__)
		{
		}

		JSValue Label::get_text() const TITANIUM_NOEXCEPT { return text__; }

		void Label::set_text(const JSValue& text) TITANIUM_NOEXCEPT { text__ = text; }

		TEXT_ALIGNMENT Label::get_textAlign() const TITANIUM_NOEXCEPT { return textAlign__; }

		void Label::set_textAlign(const TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT { textAlign__ = textAlign; }

		TEXT_VERTICAL_ALIGNMENT Label::get_verticalAlign() const TITANIUM_NOEXCEPT { return verticalAlign__; }

		void Label::set_verticalAlign(const TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			verticalAlign__ = verticalAlign;
		}

		JSValue Label::get_wordWrap() const TITANIUM_NOEXCEPT { return wordWrap__; }

		void Label::set_wordWrap(const JSValue& wordWrap) TITANIUM_NOEXCEPT { wordWrap__ = wordWrap; }

		JSValue Label::get_color() const TITANIUM_NOEXCEPT { return color__; }

		void Label::set_color(const JSValue& color) TITANIUM_NOEXCEPT { color__ = color; }

		JSValue Label::get_font() const TITANIUM_NOEXCEPT { return font__; }

		void Label::set_fontFamily(const JSValue& family) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_fontFamily: Unimplemented");
		}

		void Label::set_fontSize(const JSValue& size) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_fontSize: Unimplemented");
		}

		void Label::set_fontStyle(const JSValue& style) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Label::set_fontStyle: Unimplemented");
		}

		void Label::set_fontWeight(const JSValue& weight) TITANIUM_NOEXCEPT
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
			JSExport<Label>::SetParent(JSExport<View>::Class());
			JSExport<Label>::AddValueProperty("color", std::mem_fn(&Label::getColorArgumentValidator),
			                                  std::mem_fn(&Label::setColorArgumentValidator));
			JSExport<Label>::AddValueProperty("font", std::mem_fn(&Label::getFontArgumentValidator),
			                                  std::mem_fn(&Label::setFontArgumentValidator));
			JSExport<Label>::AddValueProperty("text", std::mem_fn(&Label::getTextArgumentValidator),
			                                  std::mem_fn(&Label::setTextArgumentValidator));
			JSExport<Label>::AddValueProperty("textAlign", std::mem_fn(&Label::getTextAlignArgumentValidator),
			                                  std::mem_fn(&Label::setTextAlignArgumentValidator));
			JSExport<Label>::AddValueProperty("verticalAlign", std::mem_fn(&Label::getVerticalAlignArgumentValidator),
			                                  std::mem_fn(&Label::setVerticalAlignArgumentValidator));
			JSExport<Label>::AddValueProperty("wordWrap", std::mem_fn(&Label::getWordWrapArgumentValidator),
			                                  std::mem_fn(&Label::setWordWrapArgumentValidator));
		}

		JSValue Label::getColorArgumentValidator() const TITANIUM_NOEXCEPT { return get_color(); }

		bool Label::setColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			color__ = get_context().CreateString(static_cast<std::string>(argument));
			set_color(color__);
			return true;
		}

		JSValue Label::getFontArgumentValidator() const TITANIUM_NOEXCEPT { return get_font(); }

		bool Label::setFontArgumentValidator(const JSValue& font) TITANIUM_NOEXCEPT
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
				set_fontWeight(font_weight);
			}

			// italic or normal
			if (font__.HasProperty("fontStyle")) {
				const auto font_style = font__.GetProperty("fontStyle");
				TITANIUM_ASSERT(font_style.IsString());
				set_fontFamily(font_style);
			}

			// String
			if (font__.HasProperty("fontFamily")) {
				const auto font_family = font__.GetProperty("fontFamily");
				TITANIUM_ASSERT(font_family.IsString());
				set_fontFamily(font_family);
			}

			// String Titanium::UI::TEXT_STYLE constants
			if (font__.HasProperty("textStyle")) {
				const auto font_text_style = font__.GetProperty("textStyle");
				TITANIUM_ASSERT(font_text_style.IsString());
				const auto font_text_style_enum = Constants::to_TEXT_STYLE(static_cast<std::string>(font_text_style));
				set_textStyle(font_text_style_enum);
			}

			return true;
		}

		JSValue Label::getTextArgumentValidator() const TITANIUM_NOEXCEPT { return get_text(); }

		bool Label::setTextArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			text__ = get_context().CreateString(static_cast<std::string>(argument));
			set_text(text__);
			return true;
		}

		JSValue Label::getTextAlignArgumentValidator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		bool Label::setTextAlignArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			bool result = false;
			if (argument.IsNumber()) {
				textAlign__ =
				    Constants::to_TEXT_ALIGNMENT(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(argument));
				set_textAlign(textAlign__);
				result = true;
			} else if (argument.IsString()) {
				textAlign__ = Constants::to_TEXT_ALIGNMENT(static_cast<std::string>(argument));
				set_textAlign(textAlign__);
				result = true;
			}

			return result;
		}

		JSValue Label::getVerticalAlignArgumentValidator() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(
			    static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		bool Label::setVerticalAlignArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			bool result = false;
			if (argument.IsNumber()) {
				verticalAlign__ = Constants::to_TEXT_VERTICAL_ALIGNMENT(
				    static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(argument));
				set_verticalAlign(verticalAlign__);
				result = true;
			} else if (argument.IsString()) {
				verticalAlign__ = Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::string>(argument));
				set_verticalAlign(verticalAlign__);
				result = true;
			}

			return result;
		}

		JSValue Label::getWordWrapArgumentValidator() const TITANIUM_NOEXCEPT { return get_wordWrap(); }

		bool Label::setWordWrapArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			wordWrap__ = get_context().CreateBoolean(static_cast<bool>(argument));
			set_wordWrap(wordWrap__);
			return true;
		}
	}
}  // namespace Titanium { namespace UI {
