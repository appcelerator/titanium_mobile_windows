/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TextArea.hpp"
#include <type_traits>

namespace Titanium
{
	namespace UI
	{
		TextArea::TextArea(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : View(js_context, arguments),
		      autoLink__({AUTOLINK::NONE}),
		      returnKeyType__(RETURNKEY::DEFAULT),
		      textAlign__(TEXT_ALIGNMENT::LEFT),
		      autoCapitalization__(TEXT_AUTOCAPITALIZATION::NONE),
		      verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER)
		{
		}

		std::unordered_set<AUTOLINK> TextArea::get_autoLink() const TITANIUM_NOEXCEPT
		{
			return autoLink__;
		}

		void TextArea::set_autoLink(const std::unordered_set<AUTOLINK>& autoLink) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::set_autoLink: Unimplemented");
		}

		KEYBOARD TextArea::get_keyboardType() const TITANIUM_NOEXCEPT
		{
			return keyboardType__;
		}

		void TextArea::set_keyboardType(const KEYBOARD& keyboardType) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::set_keyboardType: Unimplemented");
		}

		RETURNKEY TextArea::get_returnKeyType() const TITANIUM_NOEXCEPT
		{
			return returnKeyType__;
		}

		void TextArea::set_returnKeyType(const RETURNKEY& keyboardType) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::get_returnKeyType: Unimplemented");
		}

		TEXT_ALIGNMENT TextArea::get_textAlign() const TITANIUM_NOEXCEPT
		{
			return textAlign__;
		}

		void TextArea::set_textAlign(const TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::set_textAlign: Unimplemented");
		}

		TEXT_AUTOCAPITALIZATION TextArea::get_autoCapitalization() const TITANIUM_NOEXCEPT
		{
			return autoCapitalization__;
		}

		void TextArea::set_autoCapitalization(const TEXT_AUTOCAPITALIZATION& textAlign) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::set_autoCapitalization: Unimplemented");
		}

		TEXT_VERTICAL_ALIGNMENT TextArea::get_verticalAlign() const TITANIUM_NOEXCEPT
		{
			return verticalAlign__;
		}

		void TextArea::set_verticalAlign(const TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::set_verticalAlign: Unimplemented");
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void TextArea::JSExportInitialize()
		{
			JSExport<TextArea>::SetClassVersion(1);
			JSExport<TextArea>::SetParent(JSExport<View>::Class());
			JSExport<TextArea>::AddValueProperty("autoLink", std::mem_fn(&TextArea::js_get_autoLink), std::mem_fn(&TextArea::js_set_autoLink));
			JSExport<TextArea>::AddValueProperty("keyboardType", std::mem_fn(&TextArea::js_get_keyboardType), std::mem_fn(&TextArea::js_set_keyboardType));
			JSExport<TextArea>::AddValueProperty("returnKeyType", std::mem_fn(&TextArea::js_get_returnKeyType), std::mem_fn(&TextArea::js_set_returnKeyType));
			JSExport<TextArea>::AddValueProperty("textAlign", std::mem_fn(&TextArea::js_get_textAlign), std::mem_fn(&TextArea::js_set_textAlign));
			JSExport<TextArea>::AddValueProperty("autocapitalization", std::mem_fn(&TextArea::js_get_autoCapitalization), std::mem_fn(&TextArea::js_set_autoCapitalization));
			JSExport<TextArea>::AddValueProperty("verticalAlign", std::mem_fn(&TextArea::js_get_verticalAlign), std::mem_fn(&TextArea::js_set_verticalAlign));
		}

		JSValue TextArea::js_get_autoLink() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(Constants::to_underlying_type(autoLink__));
		}

		bool TextArea::js_set_autoLink(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			autoLink__ = Constants::to_AUTOLINK(static_cast<std::underlying_type<AUTOLINK>::type>(argument));
			set_autoLink(autoLink__);
			return true;
		}

		JSValue TextArea::js_get_keyboardType() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<KEYBOARD>::type>(get_keyboardType()));
		}

		bool TextArea::js_set_keyboardType(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			keyboardType__ = Constants::to_KEYBOARD(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
			set_keyboardType(keyboardType__);
			return true;
		}

		JSValue TextArea::js_get_returnKeyType() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<RETURNKEY>::type>(get_returnKeyType()));
		}

		bool TextArea::js_set_returnKeyType(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			returnKeyType__ = Constants::to_RETURNKEY(static_cast<std::underlying_type<RETURNKEY>::type>(argument));
			set_returnKeyType(returnKeyType__);
			return true;
		}

		JSValue TextArea::js_get_textAlign() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		bool TextArea::js_set_textAlign(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			bool result = false;
			if (argument.IsNumber()) {
				textAlign__ = Constants::to_TEXT_ALIGNMENT(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(argument));
				set_textAlign(textAlign__);
				result = true;
			} else if (argument.IsString()) {
				textAlign__ = Constants::to_TEXT_ALIGNMENT(static_cast<std::string>(argument));
				set_textAlign(textAlign__);
				result = true;
			}

			return result;
		}

		JSValue TextArea::js_get_autoCapitalization() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(get_autoCapitalization()));
		}

		bool TextArea::js_set_autoCapitalization(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			autoCapitalization__ = Constants::to_TEXT_AUTOCAPITALIZATION(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(argument));
			set_autoCapitalization(autoCapitalization__);
			return true;
		}

		JSValue TextArea::js_get_verticalAlign() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		bool TextArea::js_set_verticalAlign(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			bool result = false;
			if (argument.IsNumber()) {
				verticalAlign__ = Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(argument));
				set_verticalAlign(verticalAlign__);
				result = true;
			} else if (argument.IsString()) {
				verticalAlign__ = Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::string>(argument));
				set_verticalAlign(verticalAlign__);
				result = true;
			}

			return result;
		}
	} // namespace UI
}  // namespace Titanium
