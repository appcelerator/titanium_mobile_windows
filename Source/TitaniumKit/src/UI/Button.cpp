/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Button.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Blob.hpp"

namespace Titanium
{
	namespace UI
	{
		Button::Button(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context, "Ti.UI.Button"),
			  color__(js_context.CreateString()),
			  image__(js_context.CreateString()),
			  textAlign__(TEXT_ALIGNMENT::LEFT),
			  title__(js_context.CreateString()),
			  verticalAlign__(TEXT_VERTICAL_ALIGNMENT::CENTER)
		{
			TITANIUM_LOG_DEBUG("Button:: ctor ", this);
		}

		Button::~Button() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Button:: dtor ", this);
		}

		TITANIUM_PROPERTY_READWRITE(Button, std::string, color)
		TITANIUM_PROPERTY_READWRITE(Button, Font, font)
		TITANIUM_PROPERTY_READWRITE(Button, std::string, image)
		TITANIUM_PROPERTY_READWRITE(Button, std::shared_ptr<Titanium::Blob>, imageAsBlob)
		TITANIUM_PROPERTY_READWRITE(Button, TEXT_ALIGNMENT, textAlign)
		TITANIUM_PROPERTY_READWRITE(Button, std::string, title)
		TITANIUM_PROPERTY_READWRITE(Button, TEXT_VERTICAL_ALIGNMENT, verticalAlign)

		void Button::JSExportInitialize()
		{
			JSExport<Button>::SetClassVersion(1);
			JSExport<Button>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(Button, color);
			TITANIUM_ADD_PROPERTY(Button, font);
			TITANIUM_ADD_PROPERTY(Button, image);
			TITANIUM_ADD_PROPERTY(Button, textAlign);
			TITANIUM_ADD_PROPERTY(Button, title);
			TITANIUM_ADD_PROPERTY(Button, verticalAlign);

			TITANIUM_ADD_FUNCTION(Button, getColor);
			TITANIUM_ADD_FUNCTION(Button, setColor);
			TITANIUM_ADD_FUNCTION(Button, getFont);
			TITANIUM_ADD_FUNCTION(Button, setFont);
			TITANIUM_ADD_FUNCTION(Button, getImage);
			TITANIUM_ADD_FUNCTION(Button, setImage);
			TITANIUM_ADD_FUNCTION(Button, getTextAlign);
			TITANIUM_ADD_FUNCTION(Button, setTextAlign);
			TITANIUM_ADD_FUNCTION(Button, getTitle);
			TITANIUM_ADD_FUNCTION(Button, setTitle);
			TITANIUM_ADD_FUNCTION(Button, getVerticalAlign);
			TITANIUM_ADD_FUNCTION(Button, setVerticalAlign);
		}

		TITANIUM_PROPERTY_GETTER(Button, color)
		{
			return get_context().CreateString(get_color());
		}

		TITANIUM_PROPERTY_SETTER(Button, color)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Button, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(Button, setColor, color)

		TITANIUM_PROPERTY_GETTER(Button, font)
		{
			JSObject font = Titanium::UI::Font_to_js(get_context(), get_font());
			return static_cast<JSValue>(font);
		}

		TITANIUM_PROPERTY_SETTER(Button, font)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_font(Titanium::UI::js_to_Font(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Button, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(Button, setFont, font)

		TITANIUM_PROPERTY_GETTER(Button, image)
		{
			const auto ctx = get_context();
			if (imageAsBlob__ != nullptr) {
				return imageAsBlob__->get_object();
			} else if (!image__.empty()) {
				return ctx.CreateString(get_image());
			} else {
				return ctx.CreateNull();
			}
		}

		TITANIUM_PROPERTY_SETTER(Button, image)
		{
			if (argument.IsString()) {
				set_image(static_cast<std::string>(argument));
				imageAsBlob__ = nullptr;
			} else if (argument.IsObject()) {
				const auto object = static_cast<JSObject>(argument);
				set_imageAsBlob(object.GetPrivate<Titanium::Blob>());
				image__ = "";
			} else {
				TITANIUM_LOG_WARN("Button.image should be either string or Blob");
			}
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Button, getImage, image)
		TITANIUM_FUNCTION_AS_SETTER(Button, setImage, image)

		TITANIUM_PROPERTY_GETTER(Button, textAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(get_textAlign()));
		}

		TITANIUM_PROPERTY_SETTER(Button, textAlign)
		{
			bool result = false;
			if (argument.IsNumber()) {
				set_textAlign(Constants::to_TEXT_ALIGNMENT(static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(argument)));
				result = true;
			} else if (argument.IsString()) {
				set_textAlign(Constants::to_TEXT_ALIGNMENT(static_cast<std::string>(argument)));
				result = true;
			}

			return result;
		}

		TITANIUM_FUNCTION_AS_GETTER(Button, getTextAlign, textAlign)
		TITANIUM_FUNCTION_AS_SETTER(Button, setTextAlign, textAlign)

		TITANIUM_PROPERTY_GETTER(Button, title)
		{
			return get_context().CreateString(get_title());
		}

		TITANIUM_PROPERTY_SETTER(Button, title)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_title(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Button, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(Button, setTitle, title)

		TITANIUM_PROPERTY_GETTER(Button, verticalAlign)
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(get_verticalAlign()));
		}

		TITANIUM_PROPERTY_SETTER(Button, verticalAlign)
		{
			bool result = false;
			if (argument.IsNumber()) {
				set_verticalAlign(Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(argument)));
				result = true;
			} else if (argument.IsString()) {
				set_verticalAlign(Constants::to_TEXT_VERTICAL_ALIGNMENT(static_cast<std::string>(argument)));
				result = true;
			}

			return result;
		}

		TITANIUM_FUNCTION_AS_GETTER(Button, getVerticalAlign, verticalAlign)
		TITANIUM_FUNCTION_AS_SETTER(Button, setVerticalAlign, verticalAlign)

	} // namespace UI
}  // namespace Titanium
