/**
 * TitaniumKit Font
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Font.hpp"

namespace Titanium
{
	using namespace HAL;

	Font js_to_Font(const JSObject& object)
	{
		Font font;
		if (object.HasProperty("fontFamily")) {
			font.fontFamily = static_cast<std::string>(object.GetProperty("fontFamily"));
		}
		if (object.HasProperty("fontSize")) {
			font.fontSize = static_cast<std::string>(object.GetProperty("fontSize"));
		}
		if (object.HasProperty("fontStyle")) {
			font.fontStyle = static_cast<std::string>(object.GetProperty("fontStyle"));
		}
		if (object.HasProperty("fontWeight")) {
			font.fontWeight = static_cast<std::string>(object.GetProperty("fontWeight"));
		}
		if (object.HasProperty("textStyle")) {
			font.textStyle = static_cast<std::string>(object.GetProperty("textStyle"));
		}
		return font;
	};

	JSObject Font_to_js(const JSContext& js_context, Font font)
	{
		auto object = js_context.CreateObject();
		object.SetProperty("fontFamily", js_context.CreateString(font.fontFamily));
		object.SetProperty("fontSize",   js_context.CreateString(font.fontSize));
		object.SetProperty("fontStyle",  js_context.CreateString(font.fontStyle));
		object.SetProperty("fontWeight", js_context.CreateString(font.fontWeight));
		object.SetProperty("textStyle",  js_context.CreateString(font.textStyle));
		return object;
	}
} // namespace Titanium
