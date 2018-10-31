/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Label.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/AttributedString.hpp"
#include "Titanium/Locale.hpp"

namespace Titanium
{
	namespace UI
	{
		Label::Label(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context, "Ti.UI.Label"),
		      autoLink__({AUTOLINK::NONE}),
		      color__(js_context.CreateString()),
		      ellipsize__(false),
		      text__(js_context.CreateString()),
		      textAlign__(TEXT_ALIGNMENT::LEFT),
		      verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER),
		      wordWrap__(js_context.CreateBoolean(true))
			, minimumFontSize__(0)
			, maxLines__(0)
		{
		}

		TITANIUM_PROPERTY_READWRITE(Label, std::unordered_set<AUTOLINK>, autoLink)
		TITANIUM_PROPERTY_READWRITE(Label, std::string, text)
		TITANIUM_PROPERTY_READWRITE(Label, TEXT_ALIGNMENT, textAlign)
		TITANIUM_PROPERTY_READWRITE(Label, TEXT_VERTICAL_ALIGNMENT, verticalAlign)
		TITANIUM_PROPERTY_READWRITE(Label, bool, wordWrap)
		TITANIUM_PROPERTY_READWRITE(Label, std::string, color)
		TITANIUM_PROPERTY_READWRITE(Label, bool, ellipsize)
		TITANIUM_PROPERTY_READWRITE(Label, Font, font)
		TITANIUM_PROPERTY_READWRITE(Label, std::shared_ptr<AttributedString>, attributedString)
		TITANIUM_PROPERTY_READWRITE(Label, double, minimumFontSize)
		TITANIUM_PROPERTY_READWRITE(Label, std::uint32_t, maxLines)

		TITANIUM_PROPERTY_READ(Label, std::string, textid)
		void Label::set_textid(const std::string& textid) TITANIUM_NOEXCEPT
		{
			textid__ = textid;
			const auto value = Titanium::Locale::GetString(get_context(), textid);
			if (value) {
				set_text(*value);
			}
		}

		void Label::JSExportInitialize()
		{
			JSExport<Label>::SetClassVersion(1);
			JSExport<Label>::SetParent(JSExport<View>::Class());
			TITANIUM_ADD_PROPERTY(Label, autoLink);
			TITANIUM_ADD_PROPERTY(Label, color);
			TITANIUM_ADD_PROPERTY(Label, ellipsize);
			TITANIUM_ADD_PROPERTY(Label, font);
			TITANIUM_ADD_PROPERTY(Label, textid);
			TITANIUM_ADD_PROPERTY(Label, text);
			TITANIUM_ADD_PROPERTY(Label, textAlign);
			TITANIUM_ADD_PROPERTY(Label, verticalAlign);
			TITANIUM_ADD_PROPERTY(Label, wordWrap);
			TITANIUM_ADD_PROPERTY(Label, attributedString);
			TITANIUM_ADD_PROPERTY(Label, minimumFontSize);
			TITANIUM_ADD_PROPERTY(Label, maxLines);

			TITANIUM_ADD_FUNCTION(Label, getAutoLink);
			TITANIUM_ADD_FUNCTION(Label, setAutoLink);
			TITANIUM_ADD_FUNCTION(Label, getColor);
			TITANIUM_ADD_FUNCTION(Label, setColor);
			TITANIUM_ADD_FUNCTION(Label, getEllipsize);
			TITANIUM_ADD_FUNCTION(Label, setEllipsize);
			TITANIUM_ADD_FUNCTION(Label, getFont);
			TITANIUM_ADD_FUNCTION(Label, setFont);
			TITANIUM_ADD_FUNCTION(Label, getTextid);
			TITANIUM_ADD_FUNCTION(Label, setTextid);
			TITANIUM_ADD_FUNCTION(Label, getText);
			TITANIUM_ADD_FUNCTION(Label, setText);
			TITANIUM_ADD_FUNCTION(Label, getTextAlign);
			TITANIUM_ADD_FUNCTION(Label, setTextAlign);
			TITANIUM_ADD_FUNCTION(Label, getVerticalAlign);
			TITANIUM_ADD_FUNCTION(Label, setVerticalAlign);
			TITANIUM_ADD_FUNCTION(Label, getWordWrap);
			TITANIUM_ADD_FUNCTION(Label, setWordWrap);
			TITANIUM_ADD_FUNCTION(Label, getAttributedString);
			TITANIUM_ADD_FUNCTION(Label, setAttributedString);
			TITANIUM_ADD_FUNCTION(Label, getMinimumFontSize);
			TITANIUM_ADD_FUNCTION(Label, setMinimumFontSize);
			TITANIUM_ADD_FUNCTION(Label, getMaxLines);
			TITANIUM_ADD_FUNCTION(Label, setMaxLines);
		}

		TITANIUM_PROPERTY_GETTER(Label, autoLink)
		{
			return get_context().CreateNumber(Constants::to_underlying_type(get_autoLink()));
		}

		TITANIUM_PROPERTY_SETTER(Label, autoLink)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			autoLink__ = Constants::to_AUTOLINK(static_cast<std::underlying_type<AUTOLINK>::type>(argument));
			set_autoLink(autoLink__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Label, getAutoLink, autoLink)
		TITANIUM_FUNCTION_AS_SETTER(Label, setAutoLink, autoLink)

		TITANIUM_PROPERTY_GETTER_STRING(Label, color)
		TITANIUM_PROPERTY_SETTER_STRING(Label, color)

		TITANIUM_PROPERTY_GETTER_BOOL(Label, ellipsize)
		TITANIUM_PROPERTY_SETTER_BOOL(Label, ellipsize)

		TITANIUM_PROPERTY_GETTER(Label, font)
		{
			JSObject font = Titanium::UI::Font_to_js(get_context(), get_font());
			return static_cast<JSValue>(font);
		}

		TITANIUM_PROPERTY_SETTER(Label, font)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_font(Titanium::UI::js_to_Font(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER_STRING(Label, textid)
		TITANIUM_PROPERTY_SETTER_STRING(Label, textid)

		TITANIUM_PROPERTY_GETTER_STRING(Label, text)
		TITANIUM_PROPERTY_SETTER_STRING(Label, text)

		TITANIUM_PROPERTY_GETTER(Label, textAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		TITANIUM_PROPERTY_SETTER(Label, textAlign)
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

		TITANIUM_PROPERTY_GETTER(Label, verticalAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		TITANIUM_PROPERTY_SETTER(Label, verticalAlign)
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

		TITANIUM_PROPERTY_GETTER_BOOL(Label, wordWrap)
		TITANIUM_PROPERTY_SETTER_BOOL(Label, wordWrap)

		TITANIUM_PROPERTY_GETTER_OBJECT(Label, attributedString)
		TITANIUM_PROPERTY_SETTER_OBJECT(Label, attributedString, AttributedString)

		TITANIUM_PROPERTY_GETTER_DOUBLE(Label, minimumFontSize)
		TITANIUM_PROPERTY_SETTER_DOUBLE(Label, minimumFontSize)
		TITANIUM_PROPERTY_GETTER_UINT(Label, maxLines)
		TITANIUM_PROPERTY_SETTER_UINT(Label, maxLines)

		TITANIUM_FUNCTION_AS_GETTER(Label, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(Label, setColor, color)

		TITANIUM_FUNCTION_AS_GETTER(Label, getEllipsize, ellipsize)
		TITANIUM_FUNCTION_AS_SETTER(Label, setEllipsize, ellipsize)

		TITANIUM_FUNCTION_AS_GETTER(Label, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(Label, setFont, font)

		TITANIUM_FUNCTION_AS_GETTER(Label, getTextid, textid)
		TITANIUM_FUNCTION_AS_SETTER(Label, setTextid, textid)

		TITANIUM_FUNCTION_AS_GETTER(Label, getText, text)
		TITANIUM_FUNCTION_AS_SETTER(Label, setText, text)

		TITANIUM_FUNCTION_AS_GETTER(Label, getTextAlign, textAlign)
		TITANIUM_FUNCTION_AS_SETTER(Label, setTextAlign, textAlign)

		TITANIUM_FUNCTION_AS_GETTER(Label, getVerticalAlign, verticalAlign)
		TITANIUM_FUNCTION_AS_SETTER(Label, setVerticalAlign, verticalAlign)

		TITANIUM_FUNCTION_AS_GETTER(Label, getWordWrap, wordWrap)
		TITANIUM_FUNCTION_AS_SETTER(Label, setWordWrap, wordWrap)

		TITANIUM_FUNCTION_AS_GETTER(Label, getAttributedString, attributedString)
		TITANIUM_FUNCTION_AS_SETTER(Label, setAttributedString, attributedString)

		TITANIUM_FUNCTION_AS_GETTER(Label, getMinimumFontSize, minimumFontSize)
		TITANIUM_FUNCTION_AS_SETTER(Label, setMinimumFontSize, minimumFontSize)

		TITANIUM_FUNCTION_AS_GETTER(Label, getMaxLines, maxLines)
		TITANIUM_FUNCTION_AS_SETTER(Label, setMaxLines, maxLines)

	} // namespace UI
}  // namespace Titanium
