/**
 * TitaniumKit Titanium.UI.Clipboard
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Clipboard.hpp"

namespace Titanium
{
	namespace UI
	{

		Clipboard::Clipboard(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.Clipboard")
		{
		}

		void Clipboard::clearData(const std::string& type) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::clearData: Unimplemented");
		}

		void Clipboard::clearText() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::clearText: Unimplemented");
		}

		JSObject Clipboard::getData(const std::string& type) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::getData: Unimplemented");
			return get_context().CreateObject();
		}

		std::string Clipboard::getText() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::getText: Unimplemented");
			return "";
		}

		bool Clipboard::hasData(const std::string& type) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::hasData: Unimplemented");
			return false;
		}

		bool Clipboard::hasText() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::hasText: Unimplemented");
			return false;
		}

		void Clipboard::setData(const std::string& type, JSObject data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::setData: Unimplemented");
		}

		void Clipboard::setText(const std::string& text) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Clipboard::setText: Unimplemented");
		}

		void Clipboard::JSExportInitialize() {
			JSExport<Clipboard>::SetClassVersion(1);
			JSExport<Clipboard>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_FUNCTION(Clipboard, clearData);
			TITANIUM_ADD_FUNCTION(Clipboard, clearText);
			TITANIUM_ADD_FUNCTION(Clipboard, getData);
			TITANIUM_ADD_FUNCTION(Clipboard, getText);
			TITANIUM_ADD_FUNCTION(Clipboard, hasData);
			TITANIUM_ADD_FUNCTION(Clipboard, hasText);
			TITANIUM_ADD_FUNCTION(Clipboard, setData);
			TITANIUM_ADD_FUNCTION(Clipboard, setText);
		}

		TITANIUM_FUNCTION(Clipboard, clearData)
		{
			ENSURE_OPTIONAL_STRING_AT_INDEX(type, 0, "");
			clearData(type);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Clipboard, clearText)
		{
			clearText();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Clipboard, getData)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_STRING_AT_INDEX(type, 0);
			return getData(type);
		}

		TITANIUM_FUNCTION(Clipboard, getText)
		{
			return get_context().CreateString(getText());
		}

		TITANIUM_FUNCTION(Clipboard, hasData)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_STRING_AT_INDEX(type, 0);
			return get_context().CreateBoolean(hasData(type));
		}

		TITANIUM_FUNCTION(Clipboard, hasText)
		{
			return get_context().CreateBoolean(hasText());
		}

		TITANIUM_FUNCTION(Clipboard, setData)
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			}

			ENSURE_STRING_AT_INDEX(type, 0);
			ENSURE_OBJECT_AT_INDEX(data, 1);
			setData(type, data);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(Clipboard, setText)
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();
			}

			ENSURE_STRING_AT_INDEX(text, 0);
			setText(text);
			return get_context().CreateUndefined();
		}

	} // namespace UI
} // namespace Titanium
