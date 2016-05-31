/**
 * TitaniumKit CloseWindowParams
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/CloseWindowParams.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		CloseWindowParams::CloseWindowParams(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.CloseWindowParams")
		{
		}

		void CloseWindowParams::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_ASSERT(arguments.size() > 0);
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			const auto params = static_cast<JSObject>(_0);

			if (params.HasProperty("animated")) {
				const auto animated = params.GetProperty("animated");
				TITANIUM_ASSERT(animated.IsBoolean());
				set_animated(static_cast<bool>(animated));
			}
		}

		void CloseWindowParams::JSExportInitialize() {
			JSExport<Module>::SetClassVersion(1);
			JSExport<Module>::SetParent(JSExport<Module>::Class());
		}

		bool CloseWindowParams::get_animated() const TITANIUM_NOEXCEPT
		{
			return animated__;
		}

		void CloseWindowParams::set_animated(const bool& animated) TITANIUM_NOEXCEPT
		{
			animated__ = animated;
		}
	} // namespace UI
} // namespace Titanium
