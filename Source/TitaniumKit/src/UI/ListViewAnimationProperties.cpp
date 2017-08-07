/**
 * TitaniumKit ListViewAnimationProperties
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListViewAnimationProperties.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		ListViewAnimationProperties::ListViewAnimationProperties(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.ListViewAnimationProperties")
		{
		}

		void ListViewAnimationProperties::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_ASSERT(arguments.size() > 0);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			const auto js_animations = static_cast<JSObject>(_0);

			// animated property
			if (js_animations.HasProperty("animated")) {
				const auto animated = js_animations.GetProperty("animated");
				TITANIUM_ASSERT(animated.IsBoolean());
				set_animated(static_cast<bool>(animated));
			}

			// position property
			if (js_animations.HasProperty("position")) {
				const auto position = js_animations.GetProperty("position");
				TITANIUM_ASSERT(position.IsNumber());
				set_position(static_cast<std::uint32_t>(position));
			}

		}

		void ListViewAnimationProperties::JSExportInitialize() 
		{
			JSExport<Module>::SetClassVersion(1);
			JSExport<Module>::SetParent(JSExport<Module>::Class());
		}

		bool ListViewAnimationProperties::get_animated() const TITANIUM_NOEXCEPT
		{
			return animated__;
		}

		void ListViewAnimationProperties::set_animated(const bool& animated) TITANIUM_NOEXCEPT
		{
			animated__ = animated;
		}

		std::uint32_t ListViewAnimationProperties::get_position() const TITANIUM_NOEXCEPT
		{
			return position__;
		}

		void ListViewAnimationProperties::set_position(const std::uint32_t& position) TITANIUM_NOEXCEPT
		{
			position__ = position;
		}
	} // namespace UI
} // namespace Titanium
