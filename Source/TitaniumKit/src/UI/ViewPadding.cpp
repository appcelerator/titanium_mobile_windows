/**
 * TitaniumKit ViewPadding
 *
 * Copyright (c) 2018 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ViewPadding.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		ViewPadding js_to_ViewPadding(const JSObject& object)
		{
			ViewPadding padding;
			if (object.HasProperty("bottom")) {
				padding.bottom = static_cast<double>(object.GetProperty("bottom"));
			}
			if (object.HasProperty("left")) {
				padding.left = static_cast<double>(object.GetProperty("left"));
			}
			if (object.HasProperty("right")) {
				padding.right = static_cast<double>(object.GetProperty("right"));
			}
			if (object.HasProperty("top")) {
				padding.top = static_cast<double>(object.GetProperty("top"));
			}
			return padding;
		};

		JSObject ViewPadding_to_js(const JSContext& context, const ViewPadding& padding)
		{
			auto object = context.CreateObject();
			object.SetProperty("bottom", context.CreateNumber(padding.bottom));
			object.SetProperty("left",   context.CreateNumber(padding.left));
			object.SetProperty("right",  context.CreateNumber(padding.right));
			object.SetProperty("top",    context.CreateNumber(padding.top));
			return object;
		};
	} // namespace UI
} // namespace Titanium
