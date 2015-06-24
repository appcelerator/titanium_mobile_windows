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

	/*!
	  @class

	  @discussion This is the Titanium.UI implementation for Windows.
	*/
	class TITANIUMWINDOWS_UI_EXPORT UIModule final : public Titanium::UIModule, public JSExport<UIModule>
	{
	public:

		virtual void set_backgroundColor(const std::string& color) TITANIUM_NOEXCEPT final override;

		UIModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual void postInitialize(JSObject& js_object) override;

		virtual ~UIModule() TITANIUM_NOEXCEPT;
		UIModule(const UIModule&) = default;
		UIModule& operator=(const UIModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		UIModule(UIModule&&) = default;
		UIModule& operator=(UIModule&&) = default;
#endif

		static void JSExportInitialize();
	private:
		JSObject windows__;
	};
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UIMODULE_HPP_
