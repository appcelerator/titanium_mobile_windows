/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_ALERTDIALOG_HPP_
#define _TITANIUM_UI_ALERTDIALOG_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium UI AlertDialog.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.AlertDialog
		*/
		class TITANIUMKIT_EXPORT AlertDialog : public Module, public JSExport<AlertDialog>
		{
		public:

			/*!
			  @method

			  @abstract hide() : void

			  @discussion Hides this dialog.

			  @param 

			  @result void
			*/
			virtual void hide() TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract show() : void

			  @discussion Shows this dialog.

			  @param 

			  @result void
			*/
			virtual void show() TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract buttonNames : String[]

			  @discussion Name of each button to create.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::string>, buttonNames);

			/*!
			  @method

			  @abstract cancel : Number

			  @discussion Index to define the cancel button.

			  On iOS and Mobile Web, set to -1 to disable the cancel option.

			  Default: undefined (Android), -1 (iOS, Mobile Web)
			*/
			TITANIUM_PROPERTY_IMPL_DEF(int32_t, cancel);

			/*!
			  @method

			  @abstract message : String

			  @discussion Dialog message.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, message);

			/*!
			@method

			@abstract title : String

			@discussion Key identifying a string in the locale file to use for the title text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, titleid);

			/*!
			  @method

			  @abstract title : String

			  @discussion Title of the dialog.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);

			AlertDialog(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~AlertDialog() TITANIUM_NOEXCEPT;  //= default;
			AlertDialog(const AlertDialog&) = default;
			AlertDialog& operator=(const AlertDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			AlertDialog(AlertDialog&&) = default;
			AlertDialog& operator=(AlertDialog&&) = default;
#endif

			// TODO: The following functions can automatically be generated
			// from the YAML API docs.
			static void JSExportInitialize();

			TITANIUM_FUNCTION_DEF(hide);
			TITANIUM_FUNCTION_DEF(show);

			TITANIUM_PROPERTY_DEF(buttonNames);
			TITANIUM_PROPERTY_DEF(cancel);
			TITANIUM_PROPERTY_DEF(message);
			TITANIUM_PROPERTY_DEF(title);
			TITANIUM_PROPERTY_DEF(titleid);

			TITANIUM_FUNCTION_DEF(getButtonNames);
			TITANIUM_FUNCTION_DEF(setButtonNames);
			TITANIUM_FUNCTION_DEF(getCancel);
			TITANIUM_FUNCTION_DEF(setCancel);
			TITANIUM_FUNCTION_DEF(getMessage);
			TITANIUM_FUNCTION_DEF(setMessage);
			TITANIUM_FUNCTION_DEF(getTitle);
			TITANIUM_FUNCTION_DEF(setTitle);
			TITANIUM_FUNCTION_DEF(getTitleid);
			TITANIUM_FUNCTION_DEF(setTitleid);

		protected:
#pragma warning(push)
#pragma warning(disable: 4251)
			std::vector<std::string> buttonNames__;
			int32_t cancel__;
			std::string message__;
			std::string title__;
			std::string titleid__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_ALERTDIALOG_HPP_
