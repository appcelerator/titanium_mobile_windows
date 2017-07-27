/**
* Titanium.UI for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UIMODULE_HPP_
#define _TITANIUMWINDOWS_UIMODULE_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UIModule.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	// declare what's unimplemented regarding this modules.
	// Make sure to remove once it's implemented
	TITANIUM_MODULE_UNIMPLEMENTED(Titanium.UI.3DMatrix);
	TITANIUM_MODULE_UNIMPLEMENTED(Titanium.UI.ButtonBar);
	TITANIUM_MODULE_UNIMPLEMENTED(Titanium.UI.DashboardItem);
	TITANIUM_MODULE_UNIMPLEMENTED(Titanium.UI.DashboardView);
	TITANIUM_MODULE_UNIMPLEMENTED(Titanium.UI.MaskedImage);
	TITANIUM_MODULE_UNIMPLEMENTED(Titanium.UI.RefreshControl);

	/*!
	  @class UIModule
	  @ingroup Titanium.UI

	  @discussion This is the Titanium.UI implementation for Windows.
	*/
	class TITANIUMWINDOWS_UI_EXPORT UIModule final : public Titanium::UIModule, public JSExport<UIModule>
	{
	public:
		TITANIUM_PROPERTY_READONLY_DEF(Windows);

		virtual void set_backgroundColor(const std::string& color) TITANIUM_NOEXCEPT final override;

		UIModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~UIModule() TITANIUM_NOEXCEPT;
		UIModule(const UIModule&) = default;
		UIModule& operator=(const UIModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		UIModule(UIModule&&) = default;
		UIModule& operator=(UIModule&&) = default;
#endif

		static void JSExportInitialize();
	};
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UIMODULE_HPP_
