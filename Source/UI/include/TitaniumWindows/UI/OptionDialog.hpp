/**
 * Titanium.UI.OptionDialog for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_OPTIONDIALOG_HPP_
#define _TITANIUMWINDOWS_OPTIONDIALOG_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/OptionDialog.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.OptionDialog implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT OptionDialog final : public Titanium::UI::OptionDialog, public JSExport<OptionDialog>
		{

		public:
			OptionDialog(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~OptionDialog()                      = default;
			OptionDialog(const OptionDialog&)            = default;
			OptionDialog& operator=(const OptionDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			OptionDialog(OptionDialog&&)                 = default;
			OptionDialog& operator=(OptionDialog&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void show(const Titanium::UI::OptionDialogShowParams& params) TITANIUM_NOEXCEPT override;
			virtual void hide(const Titanium::UI::OptionDialogHideParams& params) TITANIUM_NOEXCEPT override;

		private:

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_OPTIONDIALOG_HPP_