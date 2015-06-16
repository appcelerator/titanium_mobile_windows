/**
 * TitaniumKit Point
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "Titanium/UI/Point.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		TITANIUMKIT_EXPORT Point js_to_Point(const JSObject& object)
		{
			Point point;
			if (object.HasProperty("x")) {
				point.x = static_cast<double>(object.GetProperty("x"));
			}
			if (object.HasProperty("y")) {
				point.y = static_cast<double>(object.GetProperty("y"));
			}
			return point;
		};

		TITANIUMKIT_EXPORT JSObject Point_to_js(const JSContext& js_context, const Point& point)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("x", js_context.CreateNumber(point.x));
			object.SetProperty("y", js_context.CreateNumber(point.y));
			return object;
		};
	} // namespace UI
} // namespace Titanium
