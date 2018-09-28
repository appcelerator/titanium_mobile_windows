/**
 * TitaniumKit Gradient
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Gradient.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <vector>

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		GradientColorRef js_to_GradientColorRef(const std::string& color)
		{
			GradientColorRef colorRef;
			colorRef.color = color;
			return colorRef;
		}

		GradientColorRef js_to_GradientColorRef(const JSObject& object)
		{
			GradientColorRef colorRef;
			if (object.HasProperty("color")) {
				colorRef.color = static_cast<std::string>(object.GetProperty("color"));
			}
			if (object.HasProperty("offset")) {
				colorRef.offset = static_cast<double>(object.GetProperty("offset"));
			}
			return colorRef;
		}

		JSObject GradientColorRef_to_js(const JSContext& js_context, const GradientColorRef& gradientColorRef)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("color", js_context.CreateString(gradientColorRef.color));
			object.SetProperty("offsest", js_context.CreateNumber(gradientColorRef.offset));
			return object;
		}

		Gradient js_to_Gradient(const JSObject& object)
		{
			Gradient gradient;
			if (object.HasProperty("backfillEnd")) {
				gradient.backfillEnd = static_cast<bool>(object.GetProperty("backfillEnd"));
			}
			if (object.HasProperty("backfillStart")) {
				gradient.backfillStart = static_cast<bool>(object.GetProperty("backfillStart"));
			}
			if (object.HasProperty("endRadius")) {
				gradient.endRadius = static_cast<double>(object.GetProperty("endRadius"));
			}
			if (object.HasProperty("startRadius")) {
				gradient.startRadius = static_cast<double>(object.GetProperty("startRadius"));
			}
			if (object.HasProperty("endPoint")) {
				auto end_property = object.GetProperty("endPoint");
				if (end_property.IsObject()) {
					gradient.endPoint = js_to_Point(static_cast<JSObject>(end_property));
				} else {
					TITANIUM_LOG_WARN("js_to_Gradient: Invalid endPoint");
				}
			}
			if (object.HasProperty("startPoint")) {
				auto start_property = object.GetProperty("startPoint");
				if (start_property.IsObject()) {
					gradient.startPoint = js_to_Point(static_cast<JSObject>(start_property));
				} else {
					TITANIUM_LOG_WARN("js_to_Gradient: Invalid startPoint");
				}
			}
			if (object.HasProperty("type")) {
				auto type_property = object.GetProperty("type");
				if (type_property.IsNumber()) {
					gradient.type = Constants::to_GRADIENT_TYPE(static_cast<std::underlying_type<GRADIENT_TYPE>::type>(type_property));
				} else {
					gradient.type = Constants::to_GRADIENT_TYPE(static_cast<std::string>(type_property));
				}
			}
			if (object.HasProperty("colors")) {
				auto color_property = object.GetProperty("colors");
				if (color_property.IsString()) {
					gradient.colors.push_back(js_to_GradientColorRef(static_cast<std::string>(color_property)));
				} else if (color_property.IsObject()) {
					auto js_color = static_cast<JSObject>(color_property);
					if (js_color.IsArray()) {
						const auto length = static_cast<uint32_t>(js_color.GetProperty("length"));
						for (uint32_t i = 0; i < length; i++) {
							auto item = js_color.GetProperty(i);
							TITANIUM_ASSERT(item.IsObject());
							if (item.IsObject()) {
								gradient.colors.push_back(js_to_GradientColorRef(static_cast<JSObject>(item)));
							} else if (item.IsString()) {
								GradientColorRef color;
								color.color = static_cast<std::string>(item);
								gradient.colors.push_back(color);
							} else {
								TITANIUM_LOG_WARN("js_to_Gradient: Invalid GradientColorRef");
							}
						}
					} else {
						gradient.colors.push_back(js_to_GradientColorRef(static_cast<std::string>(color_property)));
					}
				}

			}
			return gradient;
		};

		JSObject Gradient_to_js(const JSContext& js_context, const Gradient& gradient)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("type", js_context.CreateString(Constants::to_string(gradient.type)));
			object.SetProperty("backfillStart", js_context.CreateBoolean(gradient.backfillStart));
			object.SetProperty("backfillEnd", js_context.CreateBoolean(gradient.backfillEnd));
			object.SetProperty("endRadius", js_context.CreateNumber(gradient.endRadius));
			object.SetProperty("startRadius", js_context.CreateNumber(gradient.startRadius));
			object.SetProperty("startPoint", Point_to_js(js_context, gradient.startPoint));
			object.SetProperty("endPoint", Point_to_js(js_context, gradient.endPoint));
			std::vector<JSValue> colors;
			for (auto color : gradient.colors) {
				colors.push_back(GradientColorRef_to_js(js_context, color));
			}
			object.SetProperty("colors", js_context.CreateArray(colors));
			return object;
		}
	} // namespace UI
} // namespace Titanium
