/**
 * TitaniumKit Titanium.UI.TextArea
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TextArea.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/AttributedString.hpp"

namespace Titanium
{
	namespace UI
	{
		TextAreaSelectedParams js_to_TextAreaSelectedParams(const JSObject& object)
		{
			TextAreaSelectedParams params;
			if (object.HasProperty("length")) {
				params.length = static_cast<std::uint32_t>(object.GetProperty("length"));
			}
			if (object.HasProperty("location")) {
				params.location = static_cast<std::uint32_t>(object.GetProperty("location"));
			}
			return params;
		};

		JSObject TextAreaSelectedParams_to_js(const JSContext& js_context, const TextAreaSelectedParams& params)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("length",   js_context.CreateNumber(params.length));
			object.SetProperty("location", js_context.CreateNumber(params.location));
			return object;
		}

		TextAreaPadding js_to_TextAreaPadding(const JSObject& object)
		{
			TextAreaPadding params;
			if (object.HasProperty("bottom")) {
				params.bottom = static_cast<double>(object.GetProperty("bottom"));
			}
			if (object.HasProperty("top")) {
				params.top = static_cast<double>(object.GetProperty("top"));
			}
			if (object.HasProperty("left")) {
				params.left = static_cast<double>(object.GetProperty("left"));
			}
			if (object.HasProperty("right")) {
				params.right = static_cast<double>(object.GetProperty("right"));
			}
			return params;
		};

		JSObject TextAreaPadding_to_js(const JSContext& js_context, const TextAreaPadding& params)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("bottom", js_context.CreateNumber(params.bottom));
			object.SetProperty("top", js_context.CreateNumber(params.top));
			object.SetProperty("left", js_context.CreateNumber(params.left));
			object.SetProperty("right", js_context.CreateNumber(params.right));
			return object;
		}

		TextArea::TextArea(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.TextArea"),
			appearance__(KEYBOARD_APPEARANCE::DEFAULT),
			autocapitalization__(TEXT_AUTOCAPITALIZATION::NONE),
			autocorrect__(false),
			autoLink__({AUTOLINK::NONE}),
			clearOnEdit__(false),
			color__(""),
			editable__(true),
			ellipsize__(false),
			enableReturnKey__(false),
			hintText__(""),
			handleLinks__(false),
			keyboardToolbar__(js_context.CreateUndefined()),
			keyboardToolbarColor__(""),
			keyboardToolbarHeight__(0),
			keyboardType__(KEYBOARD::DEFAULT),
			maxLength__(-1),
			returnKeyType__(RETURNKEY::DEFAULT),
			scrollsToTop__(true),
			suppressReturn__(false),
			scrollable__(true),
			textAlign__(TEXT_ALIGNMENT::LEFT),
			value__(""),
			verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER)
		{
		}

		TITANIUM_PROPERTY_READWRITE(TextArea, KEYBOARD_APPEARANCE, appearance)
		TITANIUM_PROPERTY_READWRITE(TextArea, TEXT_AUTOCAPITALIZATION, autocapitalization)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, autocorrect)
		TITANIUM_PROPERTY_READWRITE(TextArea, std::unordered_set<AUTOLINK>, autoLink)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, clearOnEdit)
		TITANIUM_PROPERTY_READWRITE(TextArea, std::string, color)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, editable)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, ellipsize)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, enableReturnKey)
		TITANIUM_PROPERTY_READWRITE(TextArea, Font, font)
		TITANIUM_PROPERTY_READWRITE(TextArea, std::string, hintText)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, handleLinks)
		TITANIUM_PROPERTY_READWRITE(TextArea, JSValue, keyboardToolbar)
		TITANIUM_PROPERTY_READWRITE(TextArea, std::string, keyboardToolbarColor)
		TITANIUM_PROPERTY_READWRITE(TextArea, double, keyboardToolbarHeight)
		TITANIUM_PROPERTY_READWRITE(TextArea, KEYBOARD, keyboardType)
		TITANIUM_PROPERTY_READWRITE(TextArea, int32_t, maxLength)
		TITANIUM_PROPERTY_READWRITE(TextArea, RETURNKEY, returnKeyType)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, scrollsToTop)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, suppressReturn)
		TITANIUM_PROPERTY_READWRITE(TextArea, std::string, value)
		TITANIUM_PROPERTY_READWRITE(TextArea, bool, scrollable)
		TITANIUM_PROPERTY_READWRITE(TextArea, std::shared_ptr<AttributedString>, attributedString)
		TITANIUM_PROPERTY_READWRITE(TextArea, TextAreaPadding, padding)

		TextAreaSelectedParams TextArea::get_selection() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::get_selection: Unimplemented");
			TextAreaSelectedParams params;
			return params;
		}

		TITANIUM_PROPERTY_READWRITE(TextArea, TEXT_ALIGNMENT, textAlign)
		TITANIUM_PROPERTY_READWRITE(TextArea, TEXT_VERTICAL_ALIGNMENT, verticalAlign)

		void TextArea::blur() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::blur: Unimplemented");
		}

		void TextArea::focus() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("TextArea::focus: Unimplemented");
		}

		bool TextArea::hasText() TITANIUM_NOEXCEPT
		{
			return !get_value().empty();
		}

		void TextArea::JSExportInitialize() {
			JSExport<TextArea>::SetClassVersion(1);
			JSExport<TextArea>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(TextArea, appearance);
			TITANIUM_ADD_PROPERTY(TextArea, attributedString);
			TITANIUM_ADD_PROPERTY(TextArea, autocapitalization);
			TITANIUM_ADD_PROPERTY(TextArea, autocorrect);
			TITANIUM_ADD_PROPERTY(TextArea, autoLink);
			TITANIUM_ADD_PROPERTY(TextArea, clearOnEdit);
			TITANIUM_ADD_PROPERTY(TextArea, color);
			TITANIUM_ADD_PROPERTY(TextArea, editable);
			TITANIUM_ADD_PROPERTY(TextArea, ellipsize);
			TITANIUM_ADD_PROPERTY(TextArea, enableReturnKey);
			TITANIUM_ADD_PROPERTY(TextArea, font);
			TITANIUM_ADD_PROPERTY(TextArea, hintText);
			TITANIUM_ADD_PROPERTY(TextArea, handleLinks);
			TITANIUM_ADD_PROPERTY(TextArea, keyboardToolbar);
			TITANIUM_ADD_PROPERTY(TextArea, keyboardToolbarColor);
			TITANIUM_ADD_PROPERTY(TextArea, keyboardToolbarHeight);
			TITANIUM_ADD_PROPERTY(TextArea, keyboardType);
			TITANIUM_ADD_PROPERTY(TextArea, maxLength);
			TITANIUM_ADD_PROPERTY(TextArea, returnKeyType);
			TITANIUM_ADD_PROPERTY(TextArea, scrollsToTop);
			TITANIUM_ADD_PROPERTY(TextArea, suppressReturn);
			TITANIUM_ADD_PROPERTY(TextArea, scrollable);
			TITANIUM_ADD_PROPERTY_READONLY(TextArea, selection);
			TITANIUM_ADD_PROPERTY(TextArea, textAlign);
			TITANIUM_ADD_PROPERTY(TextArea, value);
			TITANIUM_ADD_PROPERTY(TextArea, verticalAlign);
			TITANIUM_ADD_PROPERTY(TextArea, padding);

			TITANIUM_ADD_FUNCTION(TextArea, blur);
			TITANIUM_ADD_FUNCTION(TextArea, focus);
			TITANIUM_ADD_FUNCTION(TextArea, hasText);
			TITANIUM_ADD_FUNCTION(TextArea, getAppearance);
			TITANIUM_ADD_FUNCTION(TextArea, setAppearance);
			TITANIUM_ADD_FUNCTION(TextArea, getAttributedString);
			TITANIUM_ADD_FUNCTION(TextArea, setAttributedString);
			TITANIUM_ADD_FUNCTION(TextArea, getAutocapitalization);
			TITANIUM_ADD_FUNCTION(TextArea, setAutocapitalization);
			TITANIUM_ADD_FUNCTION(TextArea, getAutocorrect);
			TITANIUM_ADD_FUNCTION(TextArea, setAutocorrect);
			TITANIUM_ADD_FUNCTION(TextArea, getAutoLink);
			TITANIUM_ADD_FUNCTION(TextArea, setAutoLink);
			TITANIUM_ADD_FUNCTION(TextArea, getClearOnEdit);
			TITANIUM_ADD_FUNCTION(TextArea, setClearOnEdit);
			TITANIUM_ADD_FUNCTION(TextArea, getColor);
			TITANIUM_ADD_FUNCTION(TextArea, setColor);
			TITANIUM_ADD_FUNCTION(TextArea, getEditable);
			TITANIUM_ADD_FUNCTION(TextArea, setEditable);
			TITANIUM_ADD_FUNCTION(TextArea, getEllipsize);
			TITANIUM_ADD_FUNCTION(TextArea, setEllipsize);
			TITANIUM_ADD_FUNCTION(TextArea, getEnableReturnKey);
			TITANIUM_ADD_FUNCTION(TextArea, setEnableReturnKey);
			TITANIUM_ADD_FUNCTION(TextArea, getFont);
			TITANIUM_ADD_FUNCTION(TextArea, setFont);
			TITANIUM_ADD_FUNCTION(TextArea, getHintText);
			TITANIUM_ADD_FUNCTION(TextArea, setHintText);
			TITANIUM_ADD_FUNCTION(TextArea, getHandleLinks);
			TITANIUM_ADD_FUNCTION(TextArea, setHandleLinks);
			TITANIUM_ADD_FUNCTION(TextArea, getKeyboardToolbar);
			TITANIUM_ADD_FUNCTION(TextArea, setKeyboardToolbar);
			TITANIUM_ADD_FUNCTION(TextArea, getKeyboardToolbarColor);
			TITANIUM_ADD_FUNCTION(TextArea, setKeyboardToolbarColor);
			TITANIUM_ADD_FUNCTION(TextArea, getKeyboardToolbarHeight);
			TITANIUM_ADD_FUNCTION(TextArea, setKeyboardToolbarHeight);
			TITANIUM_ADD_FUNCTION(TextArea, getKeyboardType);
			TITANIUM_ADD_FUNCTION(TextArea, setKeyboardType);
			TITANIUM_ADD_FUNCTION(TextArea, getMaxLength);
			TITANIUM_ADD_FUNCTION(TextArea, setMaxLength);
			TITANIUM_ADD_FUNCTION(TextArea, getReturnKeyType);
			TITANIUM_ADD_FUNCTION(TextArea, setReturnKeyType);
			TITANIUM_ADD_FUNCTION(TextArea, getScrollsToTop);
			TITANIUM_ADD_FUNCTION(TextArea, setScrollsToTop);
			TITANIUM_ADD_FUNCTION(TextArea, getSuppressReturn);
			TITANIUM_ADD_FUNCTION(TextArea, setSuppressReturn);
			TITANIUM_ADD_FUNCTION(TextArea, getValue);
			TITANIUM_ADD_FUNCTION(TextArea, setValue);
			TITANIUM_ADD_FUNCTION(TextArea, getScrollable);
			TITANIUM_ADD_FUNCTION(TextArea, setScrollable);
			TITANIUM_ADD_FUNCTION(TextArea, getSelection);
			TITANIUM_ADD_FUNCTION(TextArea, getTextAlign);
			TITANIUM_ADD_FUNCTION(TextArea, setTextAlign);
			TITANIUM_ADD_FUNCTION(TextArea, getVerticalAlign);
			TITANIUM_ADD_FUNCTION(TextArea, setVerticalAlign);
			TITANIUM_ADD_FUNCTION(TextArea, getPadding);
			TITANIUM_ADD_FUNCTION(TextArea, setPadding);
		}

		TITANIUM_PROPERTY_GETTER(TextArea, appearance)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<KEYBOARD_APPEARANCE>::type>(get_appearance()));
		}

		TITANIUM_PROPERTY_SETTER(TextArea, appearance)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			appearance__ = Constants::to_KEYBOARD_APPEARANCE(static_cast<std::underlying_type<KEYBOARD_APPEARANCE>::type>(argument));
			set_appearance(appearance__);
			return true;
		}

		TITANIUM_PROPERTY_GETTER_OBJECT(TextArea, attributedString)
		TITANIUM_PROPERTY_SETTER_OBJECT(TextArea, attributedString, AttributedString)

		TITANIUM_PROPERTY_GETTER_STRUCT(TextArea, padding, TextAreaPadding)
		TITANIUM_PROPERTY_SETTER_STRUCT(TextArea, padding, TextAreaPadding)

		TITANIUM_PROPERTY_GETTER(TextArea, autocapitalization)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(get_autocapitalization()));
		}

		TITANIUM_PROPERTY_SETTER(TextArea, autocapitalization)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			autocapitalization__ = Constants::to_TEXT_AUTOCAPITALIZATION(static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(argument));
			set_autocapitalization(autocapitalization__);
			return true;
		}

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, autocorrect)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, autocorrect)

		TITANIUM_PROPERTY_GETTER(TextArea, autoLink)
		{
			return get_context().CreateNumber(Constants::to_underlying_type(get_autoLink()));
		}

		TITANIUM_PROPERTY_SETTER(TextArea, autoLink)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			autoLink__ = Constants::to_AUTOLINK(static_cast<std::underlying_type<AUTOLINK>::type>(argument));
			set_autoLink(autoLink__);
			return true;
		}

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, clearOnEdit)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, clearOnEdit)

		TITANIUM_PROPERTY_GETTER_STRING(TextArea, color)
		TITANIUM_PROPERTY_SETTER_STRING(TextArea, color)

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, editable)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, editable)

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, ellipsize)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, ellipsize)

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, enableReturnKey)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, enableReturnKey)

		TITANIUM_PROPERTY_GETTER_STRUCT(TextArea, font, Font)
		TITANIUM_PROPERTY_SETTER_STRUCT(TextArea, font, Font)

		TITANIUM_PROPERTY_GETTER_STRING(TextArea, hintText)
		TITANIUM_PROPERTY_SETTER_STRING(TextArea, hintText)

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, handleLinks)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, handleLinks)

		TITANIUM_PROPERTY_GETTER(TextArea, keyboardToolbar)
		{
			return keyboardToolbar__;
		}

		TITANIUM_PROPERTY_SETTER(TextArea, keyboardToolbar)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_keyboardToolbar(static_cast<JSObject>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER_STRING(TextArea, keyboardToolbarColor)
		TITANIUM_PROPERTY_SETTER_STRING(TextArea, keyboardToolbarColor)

		TITANIUM_PROPERTY_GETTER_DOUBLE(TextArea, keyboardToolbarHeight)
		TITANIUM_PROPERTY_SETTER_DOUBLE(TextArea, keyboardToolbarHeight)

		TITANIUM_PROPERTY_GETTER(TextArea, keyboardType)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<KEYBOARD>::type>(get_keyboardType()));
		}

		TITANIUM_PROPERTY_SETTER(TextArea, keyboardType)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			keyboardType__ = Constants::to_KEYBOARD(static_cast<std::underlying_type<KEYBOARD>::type>(argument));
			set_keyboardType(keyboardType__);
			return true;
		}

		TITANIUM_PROPERTY_GETTER_INT(TextArea, maxLength)
		TITANIUM_PROPERTY_SETTER_INT(TextArea, maxLength)

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, scrollsToTop)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, scrollsToTop)

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, suppressReturn)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, suppressReturn)

		TITANIUM_PROPERTY_GETTER_STRING(TextArea, value)
		TITANIUM_PROPERTY_SETTER_STRING(TextArea, value)

		TITANIUM_PROPERTY_GETTER_BOOL(TextArea, scrollable)
		TITANIUM_PROPERTY_SETTER_BOOL(TextArea, scrollable)

		TITANIUM_PROPERTY_GETTER(TextArea, selection)
		{
			return TextAreaSelectedParams_to_js(get_context(), get_selection());
		}

		TITANIUM_PROPERTY_GETTER(TextArea, returnKeyType)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<RETURNKEY>::type>(get_returnKeyType()));
		}

		TITANIUM_PROPERTY_SETTER(TextArea, returnKeyType)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			returnKeyType__ = Constants::to_RETURNKEY(static_cast<std::underlying_type<RETURNKEY>::type>(argument));
			set_returnKeyType(returnKeyType__);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(TextArea, textAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		TITANIUM_PROPERTY_SETTER(TextArea, textAlign)
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

		TITANIUM_PROPERTY_GETTER(TextArea, verticalAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		TITANIUM_PROPERTY_SETTER(TextArea, verticalAlign)
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

		TITANIUM_FUNCTION(TextArea, blur)
		{
			blur();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TextArea, focus)
		{
			focus();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(TextArea, hasText)
		{
			return get_context().CreateBoolean(hasText());
		}

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getAppearance, appearance)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setAppearance, appearance)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getAttributedString, attributedString)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setAttributedString, attributedString)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getAutocapitalization, autocapitalization)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setAutocapitalization, autocapitalization)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getAutocorrect, autocorrect)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setAutocorrect, autocorrect)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getAutoLink, autoLink)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setAutoLink, autoLink)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getClearOnEdit, clearOnEdit)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setClearOnEdit, clearOnEdit)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setColor, color)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getEditable, editable)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setEditable, editable)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getEllipsize, ellipsize)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setEllipsize, ellipsize)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getEnableReturnKey, enableReturnKey)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setEnableReturnKey, enableReturnKey)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setFont, font)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getHintText, hintText)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setHintText, hintText)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getHandleLinks, handleLinks)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setHandleLinks, handleLinks)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getKeyboardToolbar, keyboardToolbar)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setKeyboardToolbar, keyboardToolbar)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getKeyboardToolbarColor, keyboardToolbarColor)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setKeyboardToolbarColor, keyboardToolbarColor)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getKeyboardToolbarHeight, keyboardToolbarHeight)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setKeyboardToolbarHeight, keyboardToolbarHeight)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getKeyboardType, keyboardType)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setKeyboardType, keyboardType)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getMaxLength, maxLength)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setMaxLength, maxLength)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getScrollsToTop, scrollsToTop)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setScrollsToTop, scrollsToTop)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getSuppressReturn, suppressReturn)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setSuppressReturn, suppressReturn)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getScrollable, scrollable)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setScrollable, scrollable)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getSelection, selection)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getReturnKeyType, returnKeyType)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setReturnKeyType, returnKeyType)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getTextAlign, textAlign)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setTextAlign, textAlign)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setValue, value)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getVerticalAlign, verticalAlign)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setVerticalAlign, verticalAlign)

		TITANIUM_FUNCTION_AS_GETTER(TextArea, getPadding, padding)
		TITANIUM_FUNCTION_AS_SETTER(TextArea, setPadding, padding)

	} // namespace UI
} // namespace Titanium
