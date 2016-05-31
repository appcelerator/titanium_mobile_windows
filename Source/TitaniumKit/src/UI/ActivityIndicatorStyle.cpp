/**
 * TitaniumKit Titanium.UI.ActivityIndicatorStyle
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ActivityIndicatorStyle.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{

		ActivityIndicatorStyle::ActivityIndicatorStyle(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.ActivityIndicatorStyle")
			, big__(js_context.CreateNumber(static_cast<std::uint32_t>(ACTIVITY_INDICATOR_STYLE::BIG)))
			, big_dark__(js_context.CreateNumber(static_cast<std::uint32_t>(ACTIVITY_INDICATOR_STYLE::BIG_DARK)))
			, dark__(js_context.CreateNumber(static_cast<std::uint32_t>(ACTIVITY_INDICATOR_STYLE::DARK)))
			, plain__(js_context.CreateNumber(static_cast<std::uint32_t>(ACTIVITY_INDICATOR_STYLE::PLAIN)))
		{

		}

		void ActivityIndicatorStyle::JSExportInitialize() {
			JSExport<ActivityIndicatorStyle>::SetClassVersion(1);
			JSExport<ActivityIndicatorStyle>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_PROPERTY_READONLY(ActivityIndicatorStyle, BIG);
			TITANIUM_ADD_PROPERTY_READONLY(ActivityIndicatorStyle, BIG_DARK);
			TITANIUM_ADD_PROPERTY_READONLY(ActivityIndicatorStyle, DARK);
			TITANIUM_ADD_PROPERTY_READONLY(ActivityIndicatorStyle, PLAIN);
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicatorStyle, BIG)
		{
			return big__;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicatorStyle, BIG_DARK)
		{
			return big_dark__;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicatorStyle, DARK)
		{
			return dark__;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicatorStyle, PLAIN)
		{
			return plain__;
		}

	} // namespace UI
} // namespace Titanium
