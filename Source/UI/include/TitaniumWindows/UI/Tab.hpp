/**
 * Titanium.UI.Tab for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_TAB_HPP_
#define _TITANIUMWINDOWS_TAB_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Tab.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		class Window;

		/*!
		  @class Tab
		  @ingroup Titanium.UI.Tab

		  @discussion This is the Titanium.UI.Tab implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Tab final : public Titanium::UI::Tab, public JSExport<Tab>
		{

		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(touchEnabled);
			TITANIUM_PROPERTY_UNIMPLEMENTED(activeIcon);
			TITANIUM_PROPERTY_UNIMPLEMENTED(badge);
			TITANIUM_PROPERTY_UNIMPLEMENTED(icon);
			TITANIUM_PROPERTY_UNIMPLEMENTED(iconIsMask);
			TITANIUM_PROPERTY_UNIMPLEMENTED(activeIconIsMask);

			Tab(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~Tab()                  = default;
			Tab(const Tab&)            = default;
			Tab& operator=(const Tab&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Tab(Tab&&)                 = default;
			Tab& operator=(Tab&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual void set_title(const std::string& title) TITANIUM_NOEXCEPT override;
			virtual void set_window(const std::shared_ptr<Titanium::UI::Window>& window) TITANIUM_NOEXCEPT override;
			virtual void set_activeTitleColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundImage(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundSelectedColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundSelectedImage(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundDisabledColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundDisabledImage(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundFocusedColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_backgroundFocusedImage(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_titleColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void blur()  override;
			virtual void focus() override;

			void openWindow(const std::shared_ptr<Window>& window);
			void closeWindow(const std::shared_ptr<Window>& window);

			bool isLastWindow()
			{
				return (window_stack__.size() == 0);
			}
		private:
			void set_titleColorByState();
#pragma warning(push)
#pragma warning(disable : 4251)
			std::vector<std::shared_ptr<Window>> window_stack__;
			Windows::UI::Xaml::Controls::PivotItem^ pivotItem__;
#pragma warning(pop)
		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_TAB_HPP_
