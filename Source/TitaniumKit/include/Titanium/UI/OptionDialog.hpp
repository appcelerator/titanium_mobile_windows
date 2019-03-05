/**
 * TitaniumKit Titanium.UI.OptionDialog
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_OPTIONDIALOG_HPP_
#define _TITANIUM_UI_OPTIONDIALOG_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/OptionDialogShowParams.hpp"
#include "Titanium/UI/OptionDialogHideParams.hpp"

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium OptionDialog Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.OptionDialog
		*/
		class TITANIUMKIT_EXPORT OptionDialog : public Module, public JSExport<OptionDialog>
		{

		public:

			/*!
			  @property
			  @abstract androidView
			  @discussion View to load inside the message area, to create a custom layout.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::UI::View>, androidView);

			/*!
			  @property
			  @abstract buttonNames
			  @discussion List of button names.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::string>, buttonNames);

			/*!
			  @property
			  @abstract cancel
			  @discussion Index to define the cancel option.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::int32_t, cancel);

			/*!
			  @property
			  @abstract destructive
			  @discussion Index to define the destructive option, indicated by a visual cue when rendered.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::int32_t, destructive);

			/*!
			  @property
			  @abstract options
			  @discussion List of option names to display in the dialog.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<std::string>, options);

			/*!
			  @property
			  @abstract opaquebackground
			  @discussion Boolean value indicating if the option dialog should have an opaque background.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, opaquebackground);

			/*!
			  @property
			  @abstract persistent
			  @discussion Boolean value indicating if the option dialog should only be cancelled by user gesture or by hide method.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, persistent);

			/*!
			  @property
			  @abstract selectedIndex
			  @discussion Defines the default selected option.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, selectedIndex);

			/*!
			  @property
			  @abstract title
			  @discussion Title of the dialog.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);

			/*!
			  @property
			  @abstract titleid
			  @discussion Key identifying a string in the locale file to use for the title text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, titleid);

			/*!
			  @method
			  @abstract show
			  @discussion Shows this dialog.
			*/
			virtual void show(const OptionDialogShowParams& params) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract hide
			  @discussion Hides this dialog.
			*/
			virtual void hide(const OptionDialogHideParams& params) TITANIUM_NOEXCEPT;

			OptionDialog(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~OptionDialog() = default;
			OptionDialog(const OptionDialog&) = default;
			OptionDialog& operator=(const OptionDialog&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			OptionDialog(OptionDialog&&)                 = default;
			OptionDialog& operator=(OptionDialog&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(androidView);
			TITANIUM_PROPERTY_DEF(buttonNames);
			TITANIUM_PROPERTY_DEF(cancel);
			TITANIUM_PROPERTY_DEF(destructive);
			TITANIUM_PROPERTY_DEF(options);
			TITANIUM_PROPERTY_DEF(opaquebackground);
			TITANIUM_PROPERTY_DEF(persistent);
			TITANIUM_PROPERTY_DEF(selectedIndex);
			TITANIUM_PROPERTY_DEF(title);
			TITANIUM_PROPERTY_DEF(titleid);

			TITANIUM_FUNCTION_DEF(show);
			TITANIUM_FUNCTION_DEF(hide);
			TITANIUM_FUNCTION_DEF(getAndroidView);
			TITANIUM_FUNCTION_DEF(setAndroidView);
			TITANIUM_FUNCTION_DEF(getButtonNames);
			TITANIUM_FUNCTION_DEF(setButtonNames);
			TITANIUM_FUNCTION_DEF(getCancel);
			TITANIUM_FUNCTION_DEF(setCancel);
			TITANIUM_FUNCTION_DEF(getDestructive);
			TITANIUM_FUNCTION_DEF(setDestructive);
			TITANIUM_FUNCTION_DEF(getOptions);
			TITANIUM_FUNCTION_DEF(setOptions);
			TITANIUM_FUNCTION_DEF(getOpaquebackground);
			TITANIUM_FUNCTION_DEF(setOpaquebackground);
			TITANIUM_FUNCTION_DEF(getPersistent);
			TITANIUM_FUNCTION_DEF(setPersistent);
			TITANIUM_FUNCTION_DEF(getSelectedIndex);
			TITANIUM_FUNCTION_DEF(setSelectedIndex);
			TITANIUM_FUNCTION_DEF(getTitle);
			TITANIUM_FUNCTION_DEF(setTitle);
			TITANIUM_FUNCTION_DEF(getTitleid);
			TITANIUM_FUNCTION_DEF(setTitleid);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::shared_ptr<Titanium::UI::View> androidView__;
			std::vector<std::string> buttonNames__;
			std::int32_t cancel__;
			std::int32_t destructive__;
			std::vector<std::string> options__;
			bool opaquebackground__;
			bool persistent__;
			std::uint32_t selectedIndex__;
			std::string title__;
			std::string titleid__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_OPTIONDIALOG_HPP_