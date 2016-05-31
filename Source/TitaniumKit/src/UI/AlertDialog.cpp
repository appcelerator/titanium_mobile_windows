/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/AlertDialog.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		AlertDialog::AlertDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context, "Ti.UI.AlertDialog"),
			  cancel__(-1),
		      message__(js_context.CreateString()),
		      title__(js_context.CreateString())
		{
			TITANIUM_LOG_DEBUG("AlertDialog:: ctor ", this);
		}

		AlertDialog::~AlertDialog() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog:: dtor ", this);
		}

		void AlertDialog::hide() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog::hide");
		}

		void AlertDialog::show() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog::show");
		}

		TITANIUM_PROPERTY_READWRITE(AlertDialog, std::vector<std::string>, buttonNames)
		TITANIUM_PROPERTY_READWRITE(AlertDialog, int32_t, cancel)
		TITANIUM_PROPERTY_READWRITE(AlertDialog, std::string, message)
		TITANIUM_PROPERTY_READWRITE(AlertDialog, std::string, title)

		void AlertDialog::JSExportInitialize()
		{
			JSExport<AlertDialog>::SetClassVersion(1);
			JSExport<AlertDialog>::SetParent(JSExport<Module>::Class());
			TITANIUM_ADD_FUNCTION(AlertDialog, hide);
			TITANIUM_ADD_FUNCTION(AlertDialog, show);
			TITANIUM_ADD_PROPERTY(AlertDialog, buttonNames);
			TITANIUM_ADD_PROPERTY(AlertDialog, cancel);
			TITANIUM_ADD_PROPERTY(AlertDialog, message);
			TITANIUM_ADD_PROPERTY(AlertDialog, title);

			TITANIUM_ADD_FUNCTION(AlertDialog, getButtonNames);
			TITANIUM_ADD_FUNCTION(AlertDialog, setButtonNames);
			TITANIUM_ADD_FUNCTION(AlertDialog, getCancel);
			TITANIUM_ADD_FUNCTION(AlertDialog, setCancel);
			TITANIUM_ADD_FUNCTION(AlertDialog, getMessage);
			TITANIUM_ADD_FUNCTION(AlertDialog, setMessage);
			TITANIUM_ADD_FUNCTION(AlertDialog, getTitle);
			TITANIUM_ADD_FUNCTION(AlertDialog, setTitle);
		}

		TITANIUM_FUNCTION(AlertDialog, hide)
		{
			hide();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(AlertDialog, show)
		{
			show();
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER_STRING_ARRAY(AlertDialog, buttonNames)
		TITANIUM_PROPERTY_SETTER_STRING_ARRAY(AlertDialog, buttonNames)

		TITANIUM_PROPERTY_GETTER_INT(AlertDialog, cancel)
		TITANIUM_PROPERTY_SETTER_INT(AlertDialog, cancel)

		TITANIUM_PROPERTY_GETTER_STRING(AlertDialog, title)
		TITANIUM_PROPERTY_SETTER_STRING(AlertDialog, title)

		TITANIUM_PROPERTY_GETTER_STRING(AlertDialog, message)
		TITANIUM_PROPERTY_SETTER_STRING(AlertDialog, message)

		TITANIUM_FUNCTION_AS_GETTER(AlertDialog, getButtonNames, buttonNames)
		TITANIUM_FUNCTION_AS_SETTER(AlertDialog, setButtonNames, buttonNames)
		TITANIUM_FUNCTION_AS_GETTER(AlertDialog, getCancel, cancel)
		TITANIUM_FUNCTION_AS_SETTER(AlertDialog, setCancel, cancel)
		TITANIUM_FUNCTION_AS_GETTER(AlertDialog, getMessage, message)
		TITANIUM_FUNCTION_AS_SETTER(AlertDialog, setMessage, message)
		TITANIUM_FUNCTION_AS_GETTER(AlertDialog, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(AlertDialog, setTitle, title)

	} // namespace UI
}  // namespace Titanium
