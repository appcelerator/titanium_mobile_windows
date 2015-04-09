/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Window.hpp"

namespace Titanium
{
	namespace UI
	{
		Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context),
		      openWindowParams_ctor__(js_context.CreateObject(JSExport<Titanium::UI::OpenWindowParams>::Class())),
		      closeWindowParams_ctor__(js_context.CreateObject(JSExport<Titanium::UI::CloseWindowParams>::Class())),
		      barColor__(""),
		      exitOnClose__(false),
		      extendEdges__({EXTEND_EDGE::NONE}),
		      fullscreen__(false),
		      hideShadow__(false),
		      modal__(false),
		      navBarHidden__(false),
		      navTintColor__(""),
		      orientationModes__(),
		      theme__(""),
		      translucent__(false)
		{
			TITANIUM_LOG_DEBUG("Window:: ctor ", this);
		}

		Window::~Window() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Window:: dtor ", this);
		}

		void Window::close(const std::shared_ptr<CloseWindowParams>& params) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::close: Unimplemented");
		}

		void Window::open(const std::shared_ptr<OpenWindowParams>& params) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::open: Unimplemented");
		}

		bool Window::get_exitOnClose() const TITANIUM_NOEXCEPT
		{
			return exitOnClose__;
		}

		void Window::set_exitOnClose(const bool& exitOnClose) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_exitOnClose: Unimplemented");
			exitOnClose__ = exitOnClose;
		}

		std::unordered_set<EXTEND_EDGE> Window::get_extendEdges() const TITANIUM_NOEXCEPT
		{
			return extendEdges__;
		}

		void Window::set_extendEdges(const std::unordered_set<EXTEND_EDGE>& extendEdges) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_extendEdges: Unimplemented");
		}

		bool Window::get_fullscreen() const TITANIUM_NOEXCEPT
		{
			return fullscreen__;
		}

		void Window::set_fullscreen(const bool& fullscreen) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_fullscreen: Unimplemented");
			fullscreen__ = fullscreen;
		}

		bool Window::get_hideShadow() const TITANIUM_NOEXCEPT
		{
			return hideShadow__;
		}

		void Window::set_hideShadow(const bool& hideShadow) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_hideShadow: Unimplemented");
			hideShadow__ = hideShadow;
		}

		bool Window::get_modal() const TITANIUM_NOEXCEPT
		{
			return modal__;
		}

		void Window::set_modal(const bool& modal) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_modal: Unimplemented");
			modal__ = modal;
		}

		bool Window::get_navBarHidden() const TITANIUM_NOEXCEPT
		{
			return navBarHidden__;
		}

		void Window::set_navBarHidden(const bool& navBarHidden) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_navBarHidden: Unimplemented");
			navBarHidden__ = navBarHidden;
		}

		std::string Window::get_navTintColor() const TITANIUM_NOEXCEPT
		{
			return navTintColor__;
		}

		void Window::set_navTintColor(const std::string &navTintColor) TITANIUM_NOEXCEPT
		{
			navTintColor__ = navTintColor;
		}

		std::vector<ORIENTATION> Window::get_orientationModes() const TITANIUM_NOEXCEPT
		{
			return orientationModes__;
		}

		void Window::set_orientationModes(const std::vector<ORIENTATION>& orientationModes) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_orientationModes: Unimplemented");
		}

		std::string Window::get_theme() const TITANIUM_NOEXCEPT
		{
			return theme__;
		}

		void Window::set_theme(const std::string& theme) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_theme: Unimplemented");
			theme__ = theme;
		}

		TitleAttributesParams Window::get_titleAttributes() const TITANIUM_NOEXCEPT
		{
			return titleAttributes__;
		}

		void Window::set_titleAttributes(const TitleAttributesParams& titleAttributes) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_titleAttributes: Unimplemented");
			titleAttributes__ = titleAttributes;
		}

		bool Window::get_translucent() const TITANIUM_NOEXCEPT
		{
			return translucent__;
		}

		void Window::set_translucent(const bool& translucent) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_translucent: Unimplemented");
			translucent__ = translucent;
		}

		std::string Window::get_barColor() const TITANIUM_NOEXCEPT 
		{
			return barColor__;
		}
		void Window::set_barColor(const std::string& barColor) TITANIUM_NOEXCEPT 
		{
			barColor__ = barColor;
		}

		void Window::JSExportInitialize()
		{
			JSExport<Window>::SetClassVersion(1);
			JSExport<Window>::SetParent(JSExport<View>::Class());
			TITANIUM_ADD_FUNCTION(Window, close);
			TITANIUM_ADD_FUNCTION(Window, open);
			TITANIUM_ADD_PROPERTY(Window, barColor);
			TITANIUM_ADD_PROPERTY(Window, exitOnClose);
			TITANIUM_ADD_PROPERTY(Window, extendEdges);
			TITANIUM_ADD_PROPERTY(Window, fullscreen);
			TITANIUM_ADD_PROPERTY(Window, hideShadow);
			TITANIUM_ADD_PROPERTY(Window, modal);
			TITANIUM_ADD_PROPERTY(Window, navBarHidden);
			TITANIUM_ADD_PROPERTY(Window, navTintColor);
			TITANIUM_ADD_PROPERTY(Window, orientationModes);
			TITANIUM_ADD_PROPERTY(Window, theme);
			TITANIUM_ADD_PROPERTY(Window, titleAttributes);
			TITANIUM_ADD_PROPERTY(Window, translucent);
		}

		TITANIUM_FUNCTION(Window, close)
		{
			auto js_context = this_object.get_context();
			auto params = js_context.CreateObject();
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());

				params = closeWindowParams_ctor__.CallAsConstructor({_0});
			}


			close(params.GetPrivate<CloseWindowParams>());
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Window, open)
		{
			auto js_context = this_object.get_context();
			auto params = js_context.CreateObject();
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());

				params = openWindowParams_ctor__.CallAsConstructor({_0});
			}

			open(params.GetPrivate<OpenWindowParams>());
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(Window, barColor)
		{
			return get_context().CreateString(get_barColor());
		}

		TITANIUM_PROPERTY_SETTER(Window, barColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_barColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, exitOnClose)
		{
			return get_context().CreateBoolean(exitOnClose__);
		}

		TITANIUM_PROPERTY_SETTER(Window, exitOnClose)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_exitOnClose(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, extendEdges)
		{
			return get_context().CreateNumber(Constants::to_underlying_type(extendEdges__));
		}

		TITANIUM_PROPERTY_SETTER(Window, extendEdges)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			extendEdges__ = Constants::to_EXTEND_EDGE(static_cast<std::underlying_type<EXTEND_EDGE>::type>(argument));
			set_extendEdges(extendEdges__);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, fullscreen)
		{
			return get_context().CreateBoolean(fullscreen__);
		}

		TITANIUM_PROPERTY_SETTER(Window, fullscreen)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_fullscreen(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, hideShadow)
		{
			return get_context().CreateBoolean(hideShadow__);
		}

		TITANIUM_PROPERTY_SETTER(Window, hideShadow)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_hideShadow(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, modal)
		{
			return get_context().CreateBoolean(modal__);
		}

		TITANIUM_PROPERTY_SETTER(Window, modal)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_modal(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, navBarHidden)
		{
			return get_context().CreateBoolean(navBarHidden__);
		}

		TITANIUM_PROPERTY_SETTER(Window, navBarHidden)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_navBarHidden(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, navTintColor)
		{
			return get_context().CreateString(navTintColor__);
		}

		TITANIUM_PROPERTY_SETTER(Window, navTintColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_navTintColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, orientationModes)
		{
			std::vector<JSValue> modes;
			for (auto mode : orientationModes__) {
				modes.push_back(get_context().CreateNumber(Constants::to_underlying_type(mode)));
			}
			return get_context().CreateArray(modes);
		}

		TITANIUM_PROPERTY_SETTER(Window, orientationModes)
		{
			TITANIUM_ASSERT(argument.IsObject());
			auto js_arg = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(js_arg.IsArray());
			auto modes = static_cast<JSArray>(js_arg);
			auto js_modes= static_cast<std::vector<JSValue>>(modes);
			std::vector<ORIENTATION> orientationModes;
			for (auto mode : js_modes) {
				orientationModes.push_back(Constants::to_ORIENTATION(static_cast<std::underlying_type<ORIENTATION>::type>(mode)));
			}
			set_orientationModes(orientationModes);

			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, theme)
		{
			return get_context().CreateString(theme__);
		}

		TITANIUM_PROPERTY_SETTER(Window, theme)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_theme(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, titleAttributes)
		{
			return TitleAttributesParams_to_js(get_context(), titleAttributes__);
		}

		TITANIUM_PROPERTY_SETTER(Window, titleAttributes)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_titleAttributes(js_to_TitleAttributesParams(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Window, translucent)
		{
			return get_context().CreateBoolean(translucent__);
		}

		TITANIUM_PROPERTY_SETTER(Window, translucent)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_translucent(static_cast<bool>(argument));
			return true;
		}
	} // namespace UI
}  // namespace Titanium
