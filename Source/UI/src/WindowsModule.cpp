/**
* Windows module
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/WindowsModule.hpp"
#include "TitaniumWindows/UI/Windows/CommandBar.hpp"
#include "TitaniumWindows/UI/Windows/AppBarButton.hpp"
#include "TitaniumWindows/UI/Windows/AppBarToggleButton.hpp"
#include "TitaniumWindows/UI/Windows/AppBarSeparator.hpp"
#include "TitaniumWindows/UI/Windows/SystemIcon.hpp"
#include "TitaniumWindows/UI/Windows/Style.hpp"
#include "TitaniumWindows/UI/Windows/ListViewScrollPosition.hpp"
#include "Titanium/detail/TiImpl.hpp"

#define CREATE_TITANIUM_UI_WINDOWS(NAME) \
  static auto NAME##_ctor = this_object; \
  static std::once_flag of; \
  std::call_once(of, [=] {\
  JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue UI_property = Titanium.GetProperty("UI"); \
  TITANIUM_ASSERT(UI_property.IsObject()); \
  JSObject UI = static_cast<JSObject>(UI_property); \
  JSValue UI_WIN_property = UI.GetProperty("Windows"); \
  TITANIUM_ASSERT(UI_WIN_property.IsObject()); \
  JSObject UI_WIN = static_cast<JSObject>(UI_WIN_property); \
  JSValue NAME##_property = UI_WIN.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  NAME##_ctor = static_cast<JSObject>(NAME##_property); \
  });\
  auto NAME##_obj = NAME##_ctor.CallAsConstructor(); \
  applyProperties(parameters, NAME##_obj); \
  return NAME##_obj;

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace ::Windows::UI::Xaml;

		WindowsModule::WindowsModule(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Module(js_context)
		{
			TITANIUM_LOG_DEBUG("WindowsModule::ctor Initialize");
		}

		void WindowsModule::JSExportInitialize() 
		{
			JSExport<WindowsModule>::SetClassVersion(1);
			JSExport<WindowsModule>::SetParent(JSExport<Titanium::Module>::Class());
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, CommandBar);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, AppBarButton);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, AppBarSeparator);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, AppBarToggleButton);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, SystemIcon);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, Style);
			TITANIUM_ADD_CONSTANT_PROPERTY(WindowsModule, ListViewScrollPosition);
			TITANIUM_ADD_FUNCTION(WindowsModule, createCommandBar);
			TITANIUM_ADD_FUNCTION(WindowsModule, createAppBarButton);
			TITANIUM_ADD_FUNCTION(WindowsModule, createAppBarToggleButton);
			TITANIUM_ADD_FUNCTION(WindowsModule, createAppBarSeparator);
			TITANIUM_ADD_FUNCTION(WindowsModule, createStyle);
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, CommandBar)
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::UI::WindowsXaml::CommandBar>::Class());
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, AppBarButton)
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::UI::WindowsXaml::AppBarButton>::Class());
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, AppBarSeparator)
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::UI::WindowsXaml::AppBarSeparator>::Class());
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, AppBarToggleButton)
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::UI::WindowsXaml::AppBarToggleButton>::Class());
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, SystemIcon) 
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::UI::WindowsXaml::SystemIcon>::Class());
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, Style)
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::UI::WindowsXaml::Style>::Class());
		}

		TITANIUM_PROPERTY_GETTER(WindowsModule, ListViewScrollPosition)
		{
			return get_context().CreateObject(JSExport<TitaniumWindows::UI::WindowsXaml::ListViewScrollPosition>::Class());
		}

		TITANIUM_FUNCTION(WindowsModule, createCommandBar) 
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_UI_WINDOWS(CommandBar);
		}

		TITANIUM_FUNCTION(WindowsModule, createAppBarButton) 
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_UI_WINDOWS(AppBarButton);
		}

		TITANIUM_FUNCTION(WindowsModule, createAppBarToggleButton) 
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_UI_WINDOWS(AppBarToggleButton);
		}

		TITANIUM_FUNCTION(WindowsModule, createAppBarSeparator) 
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_UI_WINDOWS(AppBarSeparator);
		}

		TITANIUM_FUNCTION(WindowsModule, createStyle)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
			CREATE_TITANIUM_UI_WINDOWS(Style);
		}

	}  // namespace UI
}  // namespace TitaniumWindows
