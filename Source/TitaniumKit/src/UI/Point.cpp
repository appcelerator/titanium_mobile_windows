/**
 * TitaniumKit Point
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "Titanium/UI/Point.hpp"
#include <boost/algorithm/string/predicate.hpp>

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		double get_Point_value(const std::string& value)
		{
			if (value.empty()) {
				return 0;
			}
			if (boost::ends_with(value, "%")) {
				return std::stod(value) / 100.0;
			}
			return std::stod(value);
		}

		Point js_to_Point(const JSObject& object)
		{
			Point point;
			if (object.HasProperty("x")) {
				const auto x = static_cast<std::string>(object.GetProperty("x"));
				point.x = x.empty() ? "0" : x;
			}
			if (object.HasProperty("y")) {
				const auto y = static_cast<std::string>(object.GetProperty("y"));
				point.y = y.empty() ? "0" : y;
			}
			return point;
		};

		JSObject Point_to_js(const JSContext& js_context, const Point& point)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("x", js_context.CreateString(point.x));
			object.SetProperty("y", js_context.CreateString(point.y));
			return object;
		};
	} // namespace UI
} // namespace Titanium
