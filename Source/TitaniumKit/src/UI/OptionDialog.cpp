/**
 * TitaniumKit Titanium.UI.OptionDialog
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/OptionDialog.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Locale.hpp"
#include "Titanium/UI/OptionDialogShowParams.hpp"
#include "Titanium/UI/OptionDialogHideParams.hpp"

namespace Titanium
{
	namespace UI
	{


		OptionDialog::OptionDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.UI.OptionDialog"),
			cancel__(-1),
			destructive__(-1),
			opaquebackground__(false),
			persistent__(true),
			selectedIndex__(0),
			title__(""),
			titleid__("")
		{
		}

		TITANIUM_PROPERTY_READWRITE(OptionDialog, std::shared_ptr<View>, androidView)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, std::vector<std::string>, buttonNames)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, std::int32_t, cancel)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, std::int32_t, destructive)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, std::vector<std::string>, options)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, bool, opaquebackground)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, bool, persistent)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, std::uint32_t, selectedIndex)
		TITANIUM_PROPERTY_READWRITE(OptionDialog, std::string, title)
		TITANIUM_PROPERTY_READ(OptionDialog, std::string, titleid)
		void OptionDialog::set_titleid(const std::string& titleid) TITANIUM_NOEXCEPT
		{
			titleid__ = titleid;
			const auto value = Titanium::Locale::GetString(get_context(), titleid);
			if (value) {
				set_title(*value);
			}
		}

		void OptionDialog::show(const OptionDialogShowParams& params) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("OptionDialog::show");
		}

		void OptionDialog::hide(const OptionDialogHideParams& params) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("OptionDialog::hide");
		}

		void OptionDialog::JSExportInitialize()
		{
			JSExport<OptionDialog>::SetClassVersion(1);
			JSExport<OptionDialog>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(OptionDialog, androidView);
			TITANIUM_ADD_PROPERTY(OptionDialog, buttonNames);
			TITANIUM_ADD_PROPERTY(OptionDialog, cancel);
			TITANIUM_ADD_PROPERTY(OptionDialog, destructive);
			TITANIUM_ADD_PROPERTY(OptionDialog, options);
			TITANIUM_ADD_PROPERTY(OptionDialog, opaquebackground);
			TITANIUM_ADD_PROPERTY(OptionDialog, persistent);
			TITANIUM_ADD_PROPERTY(OptionDialog, selectedIndex);
			TITANIUM_ADD_PROPERTY(OptionDialog, title);
			TITANIUM_ADD_PROPERTY(OptionDialog, titleid);

			TITANIUM_ADD_FUNCTION(OptionDialog, show);
			TITANIUM_ADD_FUNCTION(OptionDialog, hide);
			TITANIUM_ADD_FUNCTION(OptionDialog, getAndroidView);
			TITANIUM_ADD_FUNCTION(OptionDialog, setAndroidView);
			TITANIUM_ADD_FUNCTION(OptionDialog, getButtonNames);
			TITANIUM_ADD_FUNCTION(OptionDialog, setButtonNames);
			TITANIUM_ADD_FUNCTION(OptionDialog, getCancel);
			TITANIUM_ADD_FUNCTION(OptionDialog, setCancel);
			TITANIUM_ADD_FUNCTION(OptionDialog, getDestructive);
			TITANIUM_ADD_FUNCTION(OptionDialog, setDestructive);
			TITANIUM_ADD_FUNCTION(OptionDialog, getOptions);
			TITANIUM_ADD_FUNCTION(OptionDialog, setOptions);
			TITANIUM_ADD_FUNCTION(OptionDialog, getOpaquebackground);
			TITANIUM_ADD_FUNCTION(OptionDialog, setOpaquebackground);
			TITANIUM_ADD_FUNCTION(OptionDialog, getPersistent);
			TITANIUM_ADD_FUNCTION(OptionDialog, setPersistent);
			TITANIUM_ADD_FUNCTION(OptionDialog, getSelectedIndex);
			TITANIUM_ADD_FUNCTION(OptionDialog, setSelectedIndex);
			TITANIUM_ADD_FUNCTION(OptionDialog, getTitle);
			TITANIUM_ADD_FUNCTION(OptionDialog, setTitle);
			TITANIUM_ADD_FUNCTION(OptionDialog, getTitleid);
			TITANIUM_ADD_FUNCTION(OptionDialog, setTitleid);
		}

		TITANIUM_PROPERTY_GETTER_OBJECT(OptionDialog, androidView)
		TITANIUM_PROPERTY_SETTER_OBJECT(OptionDialog, androidView, View)

		TITANIUM_PROPERTY_GETTER_STRING_ARRAY(OptionDialog, buttonNames)
		TITANIUM_PROPERTY_SETTER_STRING_ARRAY(OptionDialog, buttonNames)

		TITANIUM_PROPERTY_GETTER_INT(OptionDialog, cancel)
		TITANIUM_PROPERTY_SETTER_INT(OptionDialog, cancel)

		TITANIUM_PROPERTY_GETTER_INT(OptionDialog, destructive)
		TITANIUM_PROPERTY_SETTER_INT(OptionDialog, destructive)

		TITANIUM_PROPERTY_GETTER_STRING_ARRAY(OptionDialog, options)
		TITANIUM_PROPERTY_SETTER_STRING_ARRAY(OptionDialog, options)

		TITANIUM_PROPERTY_GETTER_BOOL(OptionDialog, opaquebackground)
		TITANIUM_PROPERTY_SETTER_BOOL(OptionDialog, opaquebackground)

		TITANIUM_PROPERTY_GETTER_BOOL(OptionDialog, persistent)
		TITANIUM_PROPERTY_SETTER_BOOL(OptionDialog, persistent)

		TITANIUM_PROPERTY_GETTER_UINT(OptionDialog, selectedIndex)
		TITANIUM_PROPERTY_SETTER_UINT(OptionDialog, selectedIndex)

		TITANIUM_PROPERTY_GETTER_STRING(OptionDialog, title)
		TITANIUM_PROPERTY_SETTER_STRING(OptionDialog, title)

		TITANIUM_PROPERTY_GETTER_STRING(OptionDialog, titleid)
		TITANIUM_PROPERTY_SETTER_STRING(OptionDialog, titleid)

		TITANIUM_FUNCTION(OptionDialog, show)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(params, 0);
			show(js_to_OptionDialogShowParams(params));
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(OptionDialog, hide)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(params, 0);
			hide(js_to_OptionDialogHideParams(params));
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getAndroidView, androidView)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setAndroidView, androidView)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getButtonNames, buttonNames)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setButtonNames, buttonNames)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getCancel, cancel)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setCancel, cancel)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getDestructive, destructive)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setDestructive, destructive)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getOptions, options)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setOptions, options)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getOpaquebackground, opaquebackground)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setOpaquebackground, opaquebackground)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getPersistent, persistent)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setPersistent, persistent)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getSelectedIndex, selectedIndex)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setSelectedIndex, selectedIndex)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setTitle, title)
		TITANIUM_FUNCTION_AS_GETTER(OptionDialog, getTitleid, titleid)
		TITANIUM_FUNCTION_AS_SETTER(OptionDialog, setTitleid, titleid)

	} // namespace UI
} // namespace Titanium
