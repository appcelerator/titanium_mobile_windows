/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Window.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/UI/OpenWindowParams.hpp"
#include "Titanium/UI/CloseWindowParams.hpp"
#include "Titanium/UI/Tab.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Locale.hpp"

#define GET_UI() \
  const auto Titanium_property = get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  const auto Titanium = static_cast<JSObject>(Titanium_property); \
  const auto UI_property = Titanium.GetProperty("UI"); \
  TITANIUM_ASSERT(UI_property.IsObject()); \
  const auto UI = static_cast<JSObject>(UI_property);

namespace Titanium
{
	namespace UI
	{

		std::vector<std::shared_ptr<Window>> Window::window_stack__;
		bool Window::restarting__(false);

		Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context, "Ti.UI.Window"),
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
		      title__(""),
		      titleid__(""),
		      translucent__(false),
		      tab__(nullptr)
		{
			TITANIUM_LOG_DEBUG("Window:: ctor ", this);
		}

		Window::~Window() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Window:: dtor ", this);
		}

		void Window::Restart() TITANIUM_NOEXCEPT
		{
			restarting__ = true;
			while (!window_stack__.empty()) {
				auto window = window_stack__.at(0);
				window->disableEvents();
				window->close(nullptr);
			}
			restarting__ = false;
		}

		void Window::close(const std::shared_ptr<CloseWindowParams>& params) TITANIUM_NOEXCEPT
		{
			tab__ = nullptr;
			is_opened__ = false;
		}

		void Window::open(const std::shared_ptr<OpenWindowParams>& params) TITANIUM_NOEXCEPT
		{
			GET_UI();
			const auto ui_ptr = UI.GetPrivate<Titanium::UIModule>();
			ui_ptr->set_currentWindow(this->get_object().GetPrivate<Titanium::UI::Window>());
			is_opened__ = true;
		}

		TITANIUM_PROPERTY_READWRITE(Window, bool, exitOnClose)
		TITANIUM_PROPERTY_READWRITE(Window, std::unordered_set<EXTEND_EDGE>, extendEdges)
		TITANIUM_PROPERTY_READWRITE(Window, bool, fullscreen)
		TITANIUM_PROPERTY_READWRITE(Window, bool, hideShadow)
		TITANIUM_PROPERTY_READWRITE(Window, bool, modal)
		TITANIUM_PROPERTY_READWRITE(Window, bool, navBarHidden)
		TITANIUM_PROPERTY_READWRITE(Window, std::string, navTintColor)
		TITANIUM_PROPERTY_READWRITE(Window, std::vector<ORIENTATION>, orientationModes)
		TITANIUM_PROPERTY_READWRITE(Window, std::string, theme)
		TITANIUM_PROPERTY_READWRITE(Window, TitleAttributesParams, titleAttributes)
		TITANIUM_PROPERTY_READWRITE(Window, bool, translucent)
		TITANIUM_PROPERTY_READWRITE(Window, std::string, barColor)
		TITANIUM_PROPERTY_READWRITE(Window, std::shared_ptr<Tab>, tab)
		TITANIUM_PROPERTY_READWRITE(Window, std::string, title)
		TITANIUM_PROPERTY_READ(Window, std::string, titleid)
		void Window::set_titleid(const std::string& titleid) TITANIUM_NOEXCEPT
		{
			titleid__ = titleid;
			const auto value = Titanium::Locale::GetString(get_context(), titleid);
			if (value) {
				set_title(*value);
			}
		}

		void Window::JSExportInitialize()
		{
			JSExport<Window>::SetClassVersion(1);
			JSExport<Window>::SetParent(JSExport<View>::Class());
			// methods
			TITANIUM_ADD_FUNCTION(Window, close);
			TITANIUM_ADD_FUNCTION(Window, open);
			// properties
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
			TITANIUM_ADD_PROPERTY(Window, title);
			TITANIUM_ADD_PROPERTY(Window, titleid);

			// accessors
			TITANIUM_ADD_FUNCTION(Window, getBarColor);
			TITANIUM_ADD_FUNCTION(Window, setBarColor);
			TITANIUM_ADD_FUNCTION(Window, getExitOnClose);
			TITANIUM_ADD_FUNCTION(Window, setExitOnClose);
			TITANIUM_ADD_FUNCTION(Window, getExtendEdges);
			TITANIUM_ADD_FUNCTION(Window, setExtendEdges);
			TITANIUM_ADD_FUNCTION(Window, getFullscreen);
			TITANIUM_ADD_FUNCTION(Window, setFullscreen);
			TITANIUM_ADD_FUNCTION(Window, getHideShadow);
			TITANIUM_ADD_FUNCTION(Window, setHideShadow);
			TITANIUM_ADD_FUNCTION(Window, getModal);
			TITANIUM_ADD_FUNCTION(Window, setModal);
			TITANIUM_ADD_FUNCTION(Window, getNavBarHidden);
			TITANIUM_ADD_FUNCTION(Window, setNavBarHidden);
			TITANIUM_ADD_FUNCTION(Window, getNavTintColor);
			TITANIUM_ADD_FUNCTION(Window, setNavTintColor);
			TITANIUM_ADD_FUNCTION(Window, getOrientationModes);
			TITANIUM_ADD_FUNCTION(Window, setOrientationModes);
			TITANIUM_ADD_FUNCTION(Window, getTheme);
			TITANIUM_ADD_FUNCTION(Window, setTheme);
			TITANIUM_ADD_FUNCTION(Window, getTitle);
			TITANIUM_ADD_FUNCTION(Window, setTitle);
			TITANIUM_ADD_FUNCTION(Window, getTitleid);
			TITANIUM_ADD_FUNCTION(Window, setTitleid);
			TITANIUM_ADD_FUNCTION(Window, getTitleAttributes);
			TITANIUM_ADD_FUNCTION(Window, setTitleAttributes);
			TITANIUM_ADD_FUNCTION(Window, getTranslucent);
			TITANIUM_ADD_FUNCTION(Window, setTranslucent);
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
				if (_0.IsObject()) {
					params = openWindowParams_ctor__.CallAsConstructor({ _0 });
				}
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

		TITANIUM_FUNCTION_AS_GETTER(Window, getBarColor, barColor)
		TITANIUM_FUNCTION_AS_SETTER(Window, setBarColor, barColor)

		TITANIUM_PROPERTY_GETTER(Window, exitOnClose)
		{
			return get_context().CreateBoolean(get_exitOnClose());
		}

		TITANIUM_PROPERTY_SETTER(Window, exitOnClose)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_exitOnClose(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getExitOnClose, exitOnClose)
		TITANIUM_FUNCTION_AS_SETTER(Window, setExitOnClose, exitOnClose)

		TITANIUM_PROPERTY_GETTER(Window, extendEdges)
		{
			return get_context().CreateNumber(Constants::to_underlying_type(get_extendEdges()));
		}

		TITANIUM_PROPERTY_SETTER(Window, extendEdges)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			extendEdges__ = Constants::to_EXTEND_EDGE(static_cast<std::underlying_type<EXTEND_EDGE>::type>(argument));
			set_extendEdges(extendEdges__);
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getExtendEdges, extendEdges)
		TITANIUM_FUNCTION_AS_SETTER(Window, setExtendEdges, extendEdges)

		TITANIUM_PROPERTY_GETTER(Window, fullscreen)
		{
			return get_context().CreateBoolean(get_fullscreen());
		}

		TITANIUM_PROPERTY_SETTER(Window, fullscreen)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_fullscreen(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getFullscreen, fullscreen)
		TITANIUM_FUNCTION_AS_SETTER(Window, setFullscreen, fullscreen)

		TITANIUM_PROPERTY_GETTER(Window, hideShadow)
		{
			return get_context().CreateBoolean(get_hideShadow());
		}

		TITANIUM_PROPERTY_SETTER(Window, hideShadow)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_hideShadow(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getHideShadow, hideShadow)
		TITANIUM_FUNCTION_AS_SETTER(Window, setHideShadow, hideShadow)

		TITANIUM_PROPERTY_GETTER(Window, modal)
		{
			return get_context().CreateBoolean(get_modal());
		}

		TITANIUM_PROPERTY_SETTER(Window, modal)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_modal(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getModal, modal)
		TITANIUM_FUNCTION_AS_SETTER(Window, setModal, modal)

		TITANIUM_PROPERTY_GETTER(Window, navBarHidden)
		{
			return get_context().CreateBoolean(get_navBarHidden());
		}

		TITANIUM_PROPERTY_SETTER(Window, navBarHidden)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_navBarHidden(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getNavBarHidden, navBarHidden)
		TITANIUM_FUNCTION_AS_SETTER(Window, setNavBarHidden, navBarHidden)

		TITANIUM_PROPERTY_GETTER(Window, navTintColor)
		{
			return get_context().CreateString(get_navTintColor());
		}

		TITANIUM_PROPERTY_SETTER(Window, navTintColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_navTintColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getNavTintColor, navTintColor)
		TITANIUM_FUNCTION_AS_SETTER(Window, setNavTintColor, navTintColor)

		TITANIUM_PROPERTY_GETTER(Window, orientationModes)
		{
			std::vector<JSValue> modes;
			for (auto mode : get_orientationModes()) {
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
			auto js_modes = static_cast<std::vector<JSValue>>(modes);
			std::vector<ORIENTATION> orientationModes;
			for (auto mode : js_modes) {
				orientationModes.push_back(Constants::to_ORIENTATION(static_cast<std::underlying_type<ORIENTATION>::type>(mode)));
			}
			set_orientationModes(orientationModes);

			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getOrientationModes, orientationModes)
		TITANIUM_FUNCTION_AS_SETTER(Window, setOrientationModes, orientationModes)

		TITANIUM_PROPERTY_GETTER(Window, theme)
		{
			return get_context().CreateString(get_theme());
		}

		TITANIUM_PROPERTY_SETTER(Window, theme)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_theme(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getTheme, theme)
		TITANIUM_FUNCTION_AS_SETTER(Window, setTheme, theme)

		TITANIUM_PROPERTY_GETTER(Window, titleAttributes)
		{
			return TitleAttributesParams_to_js(get_context(), get_titleAttributes());
		}

		TITANIUM_PROPERTY_SETTER(Window, titleAttributes)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_titleAttributes(js_to_TitleAttributesParams(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getTitleAttributes, titleAttributes)
		TITANIUM_FUNCTION_AS_SETTER(Window, setTitleAttributes, titleAttributes)

		TITANIUM_PROPERTY_GETTER(Window, translucent)
		{
			return get_context().CreateBoolean(get_translucent());
		}

		TITANIUM_PROPERTY_SETTER(Window, translucent)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_translucent(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Window, getTranslucent, translucent)
		TITANIUM_FUNCTION_AS_SETTER(Window, setTranslucent, translucent)

		TITANIUM_PROPERTY_GETTER_STRING(Window, title)
		TITANIUM_PROPERTY_SETTER_STRING(Window, title)
		TITANIUM_FUNCTION_AS_GETTER(Window, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(Window, setTitle, title)

		TITANIUM_PROPERTY_GETTER_STRING(Window, titleid)
		TITANIUM_PROPERTY_SETTER_STRING(Window, titleid)
		TITANIUM_FUNCTION_AS_GETTER(Window, getTitleid, titleid)
		TITANIUM_FUNCTION_AS_SETTER(Window, setTitleid, titleid)
	} // namespace UI
}  // namespace Titanium
