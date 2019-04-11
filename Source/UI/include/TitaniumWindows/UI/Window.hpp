/**
 * Titanium.UI.Window for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_WINDOW_HPP_
#define _TITANIUMWINDOWS_UI_WINDOW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Window.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		namespace WindowsXaml
		{
			class CommandBar;
		}

		/*!
		  @class Window
		  @ingroup Titanium.UI.Window

		  @discussion This is the Titanium.UI.Window implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Window final : public Titanium::UI::Window, public JSExport<Window>
		{
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(barColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(extendEdges);
			TITANIUM_PROPERTY_UNIMPLEMENTED(hideShadow);
			TITANIUM_PROPERTY_UNIMPLEMENTED(modal);
			TITANIUM_PROPERTY_UNIMPLEMENTED(navBarHidden);
			TITANIUM_PROPERTY_UNIMPLEMENTED(navTintColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(orientationModes);
			TITANIUM_PROPERTY_UNIMPLEMENTED(theme);
			TITANIUM_PROPERTY_UNIMPLEMENTED(titleAttributes);
			TITANIUM_PROPERTY_UNIMPLEMENTED(translucent);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderRadius);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderWidth);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderColor);

			TITANIUM_FUNCTION_DEF(add);

			virtual void close(const std::shared_ptr<Titanium::UI::CloseWindowParams>&) TITANIUM_NOEXCEPT override final;
			virtual void open(const std::shared_ptr<Titanium::UI::OpenWindowParams>&) TITANIUM_NOEXCEPT override final;
			virtual void set_fullscreen(const bool& fullscreen) TITANIUM_NOEXCEPT override final;
			virtual void blur()  override;
			virtual void focus() override;
			virtual void set_orientationModes(const std::vector<Titanium::UI::ORIENTATION>& modes) TITANIUM_NOEXCEPT override final;

			Window(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Window();
			Window(const Window&) = default;
			Window& operator=(const Window&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Window(Window&&) = default;
			Window& operator=(Window&&) = default;
#endif

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual Windows::UI::Xaml::Controls::Canvas^ getComponent() const TITANIUM_NOEXCEPT
			{
				return canvas__;
			}

			// return true if this Window is parent container of TabGroup
			virtual bool isTabGroupContainer() const TITANIUM_NOEXCEPT  
			{
				return is_tabgroup_container__;
			}

			virtual void setTabGroupContainer(const bool& value) TITANIUM_NOEXCEPT
			{
				is_tabgroup_container__ = value;
			}

			virtual std::shared_ptr<TitaniumWindows::UI::WindowsXaml::CommandBar> getBottomAppBar() TITANIUM_NOEXCEPT;

			void updateWindowsCommandBar(const std::shared_ptr<TitaniumWindows::UI::WindowsXaml::CommandBar>& commandbar);
			void updateWindowTitle();

#if defined(IS_WINDOWS_10)
			void updateWindowSize() TITANIUM_NOEXCEPT;
#endif

			static void SetActiveTabWindow(const std::shared_ptr<TitaniumWindows::UI::Window>& window);
			static void ExitApp(const JSContext& js_context);
			static void NavigateBack();
		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			Windows::UI::Xaml::Controls::Canvas^ canvas__;
			std::shared_ptr<TitaniumWindows::UI::WindowsXaml::CommandBar> bottomAppBar__;
			Windows::Foundation::EventRegistrationToken backpressed_event__;
			bool is_tabgroup_container__ { false };
#pragma warning(pop)
		};

		class TITANIUMWINDOWS_UI_EXPORT WindowLayoutDelegate : public WindowsViewLayoutDelegate {
		public:
			WindowLayoutDelegate() TITANIUM_NOEXCEPT;
			virtual ~WindowLayoutDelegate() = default;

			virtual void onComponentSizeChange(const Windows::Foundation::Size& size) override;
			virtual void onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name) override;
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_WINDOW_HPP_
