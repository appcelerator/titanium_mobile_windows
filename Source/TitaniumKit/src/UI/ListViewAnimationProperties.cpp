/**
 * TitaniumKit ListViewAnimationProperties
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListViewAnimationProperties.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		ListViewAnimationProperties js_to_ListViewAnimationProperties(const JSObject& object)
		{
			ListViewAnimationProperties animation;
			if (object.HasProperty("animated")) {
				animation.animated = static_cast<bool>(object.GetProperty("animated"));
			}
			if (object.HasProperty("animationStyle")) {
				animation.animationStyle = static_cast<uint32_t>(object.GetProperty("animationStyle"));
			}
			if (object.HasProperty("position")) {
				animation.position = static_cast<uint32_t>(object.GetProperty("position"));
			}
			return animation;
		};
	} // namespace UI
} // namespace Titanium
