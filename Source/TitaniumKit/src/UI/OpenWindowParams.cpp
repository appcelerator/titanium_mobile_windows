/**
 * TitaniumKit OpenWindowParams
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/OpenWindowParams.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		OpenWindowParams::OpenWindowParams(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.OpenWindowParams")
		{
		}

		void OpenWindowParams::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
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

			if (params.HasProperty("fullscreen")) {
				const auto fullscreen = params.GetProperty("fullscreen");
				TITANIUM_ASSERT(fullscreen.IsBoolean());
				set_fullscreen(static_cast<bool>(fullscreen));
			}

			if (params.HasProperty("modal")) {
				const auto modal = params.GetProperty("modal");
				TITANIUM_ASSERT(modal.IsBoolean());
				set_modal(static_cast<bool>(modal));
			}

			if (params.HasProperty("navBarHidden")) {
				const auto navBarHidden = params.GetProperty("modal");
				TITANIUM_ASSERT(navBarHidden.IsBoolean());
				set_navBarHidden(static_cast<bool>(navBarHidden));
			}

			if (params.HasProperty("top")) {
				const auto top = params.GetProperty("top");
				set_top(static_cast<std::string>(top));
			}

			if (params.HasProperty("bottom")) {
				const auto bottom = params.GetProperty("bottom");
				set_bottom(static_cast<std::string>(bottom));
			}

			if (params.HasProperty("left")) {
				const auto left = params.GetProperty("left");
				set_left(static_cast<std::string>(left));
			}

			if (params.HasProperty("right")) {
				const auto right = params.GetProperty("right");
				set_right(static_cast<std::string>(right));
			}

			if (params.HasProperty("width")) {
				const auto width = params.GetProperty("width");
				set_width(static_cast<std::string>(width));
			}

			if (params.HasProperty("height")) {
				const auto height = params.GetProperty("height");
				set_height(static_cast<std::string>(height));
			}
		}

		void OpenWindowParams::JSExportInitialize() {
			JSExport<Module>::SetClassVersion(1);
			JSExport<Module>::SetParent(JSExport<Module>::Class());
		}

		bool OpenWindowParams::get_animated() const TITANIUM_NOEXCEPT
		{
			return animated__;
		}

		void OpenWindowParams::set_animated(const bool& animated) TITANIUM_NOEXCEPT
		{
			animated__ = animated;
		}

		bool OpenWindowParams::get_fullscreen() const TITANIUM_NOEXCEPT
		{
			return fullscreen__;
		}

		void OpenWindowParams::set_fullscreen(const bool& fullscreen) TITANIUM_NOEXCEPT
		{
			fullscreen__ = fullscreen;
		}

		bool OpenWindowParams::get_modal() const TITANIUM_NOEXCEPT
		{
			return modal__;
		}

		void OpenWindowParams::set_modal(const bool& modal) TITANIUM_NOEXCEPT
		{
			modal__ = modal;
		}

		bool OpenWindowParams::get_navBarHidden() const TITANIUM_NOEXCEPT
		{
			return navBarHidden__;
		}

		void OpenWindowParams::set_navBarHidden(const bool& navBarHidden) TITANIUM_NOEXCEPT
		{
			navBarHidden__ = navBarHidden;
		}

		std::string OpenWindowParams::get_top() const TITANIUM_NOEXCEPT
		{
			return top__;
		}

		void OpenWindowParams::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			top__ = top;
		}

		std::string OpenWindowParams::get_bottom() const TITANIUM_NOEXCEPT
		{
			return bottom__;
		}

		void OpenWindowParams::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			bottom__ = bottom;
		}

		std::string OpenWindowParams::get_left() const TITANIUM_NOEXCEPT
		{
			return left__;
		}

		void OpenWindowParams::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			left__ = left;
		}

		std::string OpenWindowParams::get_right() const TITANIUM_NOEXCEPT
		{
			return right__;
		}

		void OpenWindowParams::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			right__ = right;
		}

		std::string OpenWindowParams::get_width() const TITANIUM_NOEXCEPT
		{
			return width__;
		}

		void OpenWindowParams::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			width__ = width;
		}

		std::string OpenWindowParams::get_height() const TITANIUM_NOEXCEPT
		{
			return height__;
		}

		void OpenWindowParams::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			height__ = height;
		}

	} // namespace UI
} // namespace Titanium
