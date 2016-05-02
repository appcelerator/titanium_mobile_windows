/**
 * TitaniumKit Titanium.UI.SearchBar
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/SearchBar.hpp"
#include "Titanium/UI/TableViewRow.hpp"

namespace Titanium
{
	namespace UI
	{
		SearchBar::SearchBar(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Titanium.UI.SearchBar")
			, autocapitalization__(TEXT_AUTOCAPITALIZATION::NONE)
			, autocorrect__(false)
			, barColor__("")
			, hintText__("")
			, hinttextid__("")
			, keyboardType__(KEYBOARD::DEFAULT)
			, keyboardAppearance__(KEYBOARD_APPEARANCE::DEFAULT)
			, prompt__("")
			, promptid__("")
			, showBookmark__(false)
			, showCancel__(false)
			, value__("")
			, querySubmitted__(nullptr)
			, suggestionRequested__(nullptr)
		{
		}

		TITANIUM_PROPERTY_READWRITE(SearchBar, TEXT_AUTOCAPITALIZATION, autocapitalization)
		TITANIUM_PROPERTY_READWRITE(SearchBar, bool, autocorrect)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::string, barColor)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::string, hintText)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::string, hinttextid)
		TITANIUM_PROPERTY_READWRITE(SearchBar, KEYBOARD, keyboardType)
		TITANIUM_PROPERTY_READWRITE(SearchBar, KEYBOARD_APPEARANCE, keyboardAppearance)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::string, prompt)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::string, promptid)
		TITANIUM_PROPERTY_READWRITE(SearchBar, bool, showBookmark)
		TITANIUM_PROPERTY_READWRITE(SearchBar, bool, showCancel)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::string, value)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::function<void(const std::string&)>, querySubmitted)
		TITANIUM_PROPERTY_READWRITE(SearchBar, std::function<std::vector<std::string>(const std::string&)>, suggestionRequested)

		void SearchBar::JSExportInitialize()
		{
			JSExport<SearchBar>::SetClassVersion(1);
			JSExport<SearchBar>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(SearchBar, autocapitalization);
			TITANIUM_ADD_PROPERTY(SearchBar, autocorrect);
			TITANIUM_ADD_PROPERTY(SearchBar, barColor);
			TITANIUM_ADD_PROPERTY(SearchBar, hintText);
			TITANIUM_ADD_PROPERTY(SearchBar, hinttextid);
			TITANIUM_ADD_PROPERTY(SearchBar, keyboardType);
			TITANIUM_ADD_PROPERTY(SearchBar, keyboardAppearance);
			TITANIUM_ADD_PROPERTY(SearchBar, prompt);
			TITANIUM_ADD_PROPERTY(SearchBar, promptid);
			TITANIUM_ADD_PROPERTY(SearchBar, showBookmark);
			TITANIUM_ADD_PROPERTY(SearchBar, showCancel);
			TITANIUM_ADD_PROPERTY(SearchBar, value);

			TITANIUM_ADD_FUNCTION(SearchBar, getAutocapitalization);
			TITANIUM_ADD_FUNCTION(SearchBar, setAutocapitalization);
			TITANIUM_ADD_FUNCTION(SearchBar, getAutocorrect);
			TITANIUM_ADD_FUNCTION(SearchBar, setAutocorrect);
			TITANIUM_ADD_FUNCTION(SearchBar, getBarColor);
			TITANIUM_ADD_FUNCTION(SearchBar, setBarColor);
			TITANIUM_ADD_FUNCTION(SearchBar, getHintText);
			TITANIUM_ADD_FUNCTION(SearchBar, setHintText);
			TITANIUM_ADD_FUNCTION(SearchBar, getHinttextid);
			TITANIUM_ADD_FUNCTION(SearchBar, setHinttextid);
			TITANIUM_ADD_FUNCTION(SearchBar, getKeyboardType);
			TITANIUM_ADD_FUNCTION(SearchBar, setKeyboardType);
			TITANIUM_ADD_FUNCTION(SearchBar, getPrompt);
			TITANIUM_ADD_FUNCTION(SearchBar, setPrompt);
			TITANIUM_ADD_FUNCTION(SearchBar, getPromptid);
			TITANIUM_ADD_FUNCTION(SearchBar, setPromptid);
			TITANIUM_ADD_FUNCTION(SearchBar, getShowBookmark);
			TITANIUM_ADD_FUNCTION(SearchBar, setShowBookmark);
			TITANIUM_ADD_FUNCTION(SearchBar, getShowCancel);
			TITANIUM_ADD_FUNCTION(SearchBar, setShowCancel);
			TITANIUM_ADD_FUNCTION(SearchBar, getValue);
			TITANIUM_ADD_FUNCTION(SearchBar, setValue);
		}

		TITANIUM_PROPERTY_GETTER_ENUM(SearchBar, autocapitalization);
		TITANIUM_PROPERTY_SETTER_ENUM(SearchBar, autocapitalization, TEXT_AUTOCAPITALIZATION);
		TITANIUM_PROPERTY_GETTER_BOOL(SearchBar, autocorrect);
		TITANIUM_PROPERTY_SETTER_BOOL(SearchBar, autocorrect)
		TITANIUM_PROPERTY_GETTER_STRING(SearchBar, barColor);
		TITANIUM_PROPERTY_SETTER_STRING(SearchBar, barColor);
		TITANIUM_PROPERTY_GETTER_STRING(SearchBar, hintText);
		TITANIUM_PROPERTY_SETTER_STRING(SearchBar, hintText);
		TITANIUM_PROPERTY_GETTER_STRING(SearchBar, hinttextid);
		TITANIUM_PROPERTY_SETTER_STRING(SearchBar, hinttextid);
		TITANIUM_PROPERTY_GETTER_ENUM(SearchBar, keyboardType);
		TITANIUM_PROPERTY_SETTER_ENUM(SearchBar, keyboardType, KEYBOARD);
		TITANIUM_PROPERTY_GETTER_ENUM(SearchBar, keyboardAppearance);
		TITANIUM_PROPERTY_SETTER_ENUM(SearchBar, keyboardAppearance, KEYBOARD_APPEARANCE);
		TITANIUM_PROPERTY_GETTER_STRING(SearchBar, prompt);
		TITANIUM_PROPERTY_SETTER_STRING(SearchBar, prompt);
		TITANIUM_PROPERTY_GETTER_STRING(SearchBar, promptid);
		TITANIUM_PROPERTY_SETTER_STRING(SearchBar, promptid);
		TITANIUM_PROPERTY_GETTER_BOOL(SearchBar, showBookmark);
		TITANIUM_PROPERTY_SETTER_BOOL(SearchBar, showBookmark);
		TITANIUM_PROPERTY_GETTER_BOOL(SearchBar, showCancel);
		TITANIUM_PROPERTY_SETTER_BOOL(SearchBar, showCancel);
		TITANIUM_PROPERTY_GETTER_STRING(SearchBar, value);
		TITANIUM_PROPERTY_SETTER_STRING(SearchBar, value);

		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getAutocapitalization, autocapitalization)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setAutocapitalization, autocapitalization)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getAutocorrect, autocorrect)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setAutocorrect, autocorrect)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getBarColor, barColor)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setBarColor, barColor)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getHintText, hintText)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setHintText, hintText)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getHinttextid, hinttextid)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setHinttextid, hinttextid)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getKeyboardType, keyboardType)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setKeyboardType, keyboardType)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getKeyboardAppearance, keyboardAppearance)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setKeyboardAppearance, keyboardAppearance)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getPrompt, prompt)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setPrompt, prompt)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getPromptid, promptid)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setPromptid, promptid)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getShowBookmark, showBookmark)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setShowBookmark, showBookmark)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getShowCancel, showCancel)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setShowCancel, showCancel)
		TITANIUM_FUNCTION_AS_GETTER(SearchBar, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(SearchBar, setValue, value)

	} // namespace UI
} // namespace Titanium
