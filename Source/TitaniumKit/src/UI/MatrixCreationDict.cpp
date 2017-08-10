/**
 * TitaniumKit MatrixCreationDict
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/MatrixCreationDict.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		MatrixCreationDict js_to_MatrixCreationDict(const JSObject& object)
		{
			MatrixCreationDict dict;
			if (object.HasProperty("anchorPoint")) {
				const auto p = object.GetProperty("anchorPoint");
				TITANIUM_ASSERT(p.IsObject());
				dict.anchorPoint = js_to_Point(static_cast<JSObject>(p));
			} else {
				dict.anchorPoint.x = std::to_string(0.5);
				dict.anchorPoint.y = std::to_string(0.5);
			}
			if (object.HasProperty("rotate")) {
				dict.rotate = static_cast<int32_t>(object.GetProperty("rotate"));
			}
			if (object.HasProperty("scale")) {
				dict.scale = static_cast<double>(object.GetProperty("scale"));
			}
			return dict;
		};

		JSObject MatrixCreationDict_to_js(const JSContext& js_context, const MatrixCreationDict& dict)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("anchorPoint", Point_to_js(js_context, dict.anchorPoint));
			object.SetProperty("rotate", js_context.CreateNumber(dict.rotate));
			object.SetProperty("scale", js_context.CreateNumber(dict.scale));
			return object;
		};
	} // namespace UI
} // namespace Titanium
