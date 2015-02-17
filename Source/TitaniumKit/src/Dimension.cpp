/**
 * TitaniumKit Dimension
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Dimension.hpp"

namespace Titanium
{
	using namespace HAL;

	Dimension js_to_Dimension(const JSObject& object)
	{
		Dimension dimension;
		if (object.HasProperty("x")) {
			dimension.x = static_cast<double>(object.GetProperty("x"));
		}
		if (object.HasProperty("y")) {
			dimension.y = static_cast<double>(object.GetProperty("y"));
		}
		if (object.HasProperty("width")) {
			dimension.width = static_cast<double>(object.GetProperty("width"));
		}
		if (object.HasProperty("height")) {
			dimension.height = static_cast<double>(object.GetProperty("height"));
		}
		return dimension;
	};
} // namespace Titanium
