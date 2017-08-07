/**
* Windows module
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_WINDOWSMODULE_HPP_
#define _TITANIUMWINDOWS_WINDOWSMODULE_HPP_

#include "Titanium/Module.hpp"
#include "TitaniumWindows_UI_EXPORT.h"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.Windows implementation
		*/
		class TITANIUMWINDOWS_UI_EXPORT WindowsModule final : public Titanium::Module, public JSExport<WindowsModule>
		{

		public:
			WindowsModule(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~WindowsModule()                = default;
			WindowsModule(const WindowsModule&)            = default;
			WindowsModule& operator=(const WindowsModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WindowsModule(WindowsModule&&)                 = default;
			WindowsModule& operator=(WindowsModule&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_READONLY_DEF(CommandBar);
			TITANIUM_PROPERTY_READONLY_DEF(AppBarButton);
			TITANIUM_PROPERTY_READONLY_DEF(AppBarToggleButton);
			TITANIUM_PROPERTY_READONLY_DEF(AppBarSeparator);
			TITANIUM_PROPERTY_READONLY_DEF(SystemIcon);
			TITANIUM_PROPERTY_READONLY_DEF(ListViewScrollPosition);

			TITANIUM_FUNCTION_DEF(createCommandBar);
			TITANIUM_FUNCTION_DEF(createAppBarButton);
			TITANIUM_FUNCTION_DEF(createAppBarToggleButton);
			TITANIUM_FUNCTION_DEF(createAppBarSeparator);
		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_WINDOWSMODULE_HPP_