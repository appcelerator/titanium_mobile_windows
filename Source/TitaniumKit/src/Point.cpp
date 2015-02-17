/**
 * TitaniumKit Point
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "Titanium/Point.hpp"

namespace Titanium
{
	using namespace HAL;

	Point js_to_Point(const JSObject& object)
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
} // namespace Titanium
