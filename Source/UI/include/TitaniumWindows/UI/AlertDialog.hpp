/**
* Titanium.UI.AlertDialog for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_ALERTDIALOG_HPP_
#define _TITANIUMWINDOWS_UI_ALERTDIALOG_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/AlertDialog.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <functional>
#include <agile.h>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class AlertDialog
		  @ingroup Titanium.UI.AlertDialog

		  @discussion This is the Titanium.UI.AlertDialog implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT AlertDialog final : public Titanium::UI::AlertDialog, public JSExport<AlertDialog>
		{
		public:
			TITANIUM_FUNCTION_UNIMPLEMENTED(hide);
			
			AlertDialog(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~AlertDialog() = default;
			AlertDialog(const AlertDialog&) = default;
			AlertDialog& operator=(const AlertDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			AlertDialog(AlertDialog&&) = default;
			AlertDialog& operator=(AlertDialog&&) = default;
#endif

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void show() TITANIUM_NOEXCEPT override;
			virtual void hide() TITANIUM_NOEXCEPT override;

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			::Platform::Agile<Windows::UI::Popups::MessageDialog^> dialog__;
			static std::vector<std::shared_ptr<AlertDialog>> dialog_queue__;
			Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand^>^ dialog_task__{nullptr};
			std::function<void(Windows::UI::Popups::IUICommand^)> on_click__;

#if defined(IS_WINDOWS_PHONE)
			static const std::uint32_t MaxButtonCount = 2;
#else
			static const std::uint32_t MaxButtonCount = 3;
#endif
#pragma warning(pop)
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_ALERTDIALOG_HPP_
