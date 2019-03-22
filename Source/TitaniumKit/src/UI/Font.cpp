/**
 * TitaniumKit Font
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Font.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		Font js_to_Font(const JSObject& object)
		{
			Font font {"","15px",FONT_STYLE::NORMAL,FONT_WEIGHT::NORMAL,TEXT_STYLE::BODY};
			if (object.HasProperty("fontFamily")) {
				font.fontFamily = static_cast<std::string>(object.GetProperty("fontFamily"));
			}
			if (object.HasProperty("fontSize")) {
				font.fontSize = static_cast<std::string>(object.GetProperty("fontSize"));
			}
			if (object.HasProperty("fontStyle")) {
				auto fontStyle = object.GetProperty("fontStyle");
				if (fontStyle.IsNumber()) {
					font.fontStyle = Constants::to_FONT_STYLE(static_cast<std::underlying_type<FONT_STYLE>::type>(fontStyle));
				} else {
					font.fontStyle = Constants::to_FONT_STYLE(static_cast<std::string>(fontStyle));
				}
			}
			if (object.HasProperty("fontWeight")) {
				auto fontWeight = object.GetProperty("fontWeight");
				if (fontWeight.IsNumber()) {
					font.fontWeight = Constants::to_FONT_WEIGHT(static_cast<std::underlying_type<FONT_WEIGHT>::type>(fontWeight));
				} else {
					font.fontWeight = Constants::to_FONT_WEIGHT(static_cast<std::string>(fontWeight));
				}
			}
			if (object.HasProperty("textStyle")) {
				auto textStyle = object.GetProperty("textStyle");
				if (textStyle.IsNumber()) {
					font.textStyle = Constants::to_TEXT_STYLE(static_cast<std::underlying_type<TEXT_STYLE>::type>(textStyle));
				} else {
					font.textStyle = Constants::to_TEXT_STYLE(static_cast<std::string>(textStyle));
				}
			}
			return font;
		};

		JSObject Font_to_js(const JSContext& js_context, const Font& font)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("fontFamily", js_context.CreateString(font.fontFamily));
			object.SetProperty("fontStyle",  js_context.CreateNumber(static_cast<std::underlying_type<FONT_STYLE>::type>(font.fontStyle)));
			object.SetProperty("fontWeight", js_context.CreateNumber(static_cast<std::underlying_type<FONT_WEIGHT>::type>(font.fontWeight)));
			object.SetProperty("textStyle",  js_context.CreateNumber(static_cast<std::underlying_type<TEXT_STYLE>::type>(font.textStyle)));

			const auto fontSize = font.fontSize;
			if (std::all_of(fontSize.begin(), fontSize.end(), isdigit)) {
				object.SetProperty("fontSize", js_context.CreateNumber(atof(fontSize.c_str())));
			} else {
				object.SetProperty("fontSize", js_context.CreateString(fontSize));
			}

			return object;
		}
	} // namespace UI
} // namespace Titanium
