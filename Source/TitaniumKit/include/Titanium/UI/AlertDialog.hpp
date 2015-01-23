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
			virtual void hide(JSObject& this_object) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract show() : void

			  @discussion Shows this dialog.

			  @param 

			  @result void
			*/
			virtual void show(JSObject& this_object) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract buttonNames : String[]

			  @discussion Name of each button to create.
			*/
			virtual std::vector<std::string> get_buttonNames() const TITANIUM_NOEXCEPT final;
			virtual void set_buttonNames(const std::vector<std::string>& buttonNames) TITANIUM_NOEXCEPT final;
			virtual void addButton(const std::string& buttonName) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract message : String

			  @discussion Dialog message.
			*/
			virtual std::string get_message() const TITANIUM_NOEXCEPT final;
			virtual void set_message(const std::string& message) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract title : String

			  @discussion Title of the dialog.
			*/
			virtual std::string get_title() const TITANIUM_NOEXCEPT final;
			virtual void set_title(const std::string& title) TITANIUM_NOEXCEPT;

			AlertDialog(const JSContext& js_context) TITANIUM_NOEXCEPT;
			AlertDialog(const AlertDialog&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

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

			virtual JSValue js_hide(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_show(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_buttonNames() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_buttonNames(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_message() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_message(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_title() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_title(const JSValue& argument) TITANIUM_NOEXCEPT final;

		private:
#pragma warning(push)
#pragma warning(disable: 4251)
			std::vector<std::string> buttonNames__;
			std::string message__;
			std::string title__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_ALERTDIALOG_HPP_
