/**
 * TitaniumKit Titanium.UI.ActivityIndicator
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ActivityIndicator.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{

		ActivityIndicator::ActivityIndicator(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.ActivityIndicator")
			, color__("")
			, message__("")
			, messageid__("")
			, style__(ACTIVITY_INDICATOR_STYLE::PLAIN)
		{
		}

		TITANIUM_PROPERTY_READWRITE(ActivityIndicator, std::string, color);
		TITANIUM_PROPERTY_READWRITE(ActivityIndicator, Font, font);
		TITANIUM_PROPERTY_READWRITE(ActivityIndicator, std::string, message);
		TITANIUM_PROPERTY_READWRITE(ActivityIndicator, std::string, messageid);
		TITANIUM_PROPERTY_READWRITE(ActivityIndicator, ACTIVITY_INDICATOR_STYLE, style);
		TITANIUM_PROPERTY_READWRITE(ActivityIndicator, std::string, indicatorColor);
		TITANIUM_PROPERTY_READWRITE(ActivityIndicator, std::string, indicatorDiameter);

		void ActivityIndicator::JSExportInitialize() {
			JSExport<ActivityIndicator>::SetClassVersion(1);
			JSExport<ActivityIndicator>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(ActivityIndicator, color);
			TITANIUM_ADD_PROPERTY(ActivityIndicator, font);
			TITANIUM_ADD_PROPERTY(ActivityIndicator, message);
			TITANIUM_ADD_PROPERTY(ActivityIndicator, messageid);
			TITANIUM_ADD_PROPERTY(ActivityIndicator, style);
			TITANIUM_ADD_PROPERTY(ActivityIndicator, indicatorColor);
			TITANIUM_ADD_PROPERTY(ActivityIndicator, indicatorDiameter);

			TITANIUM_ADD_FUNCTION(ActivityIndicator, getColor);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, setColor);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, getFont);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, setFont);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, getMessage);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, setMessage);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, getMessageid);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, setMessageid);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, getStyle);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, setStyle);

			TITANIUM_ADD_FUNCTION(ActivityIndicator, getIndicatorColor);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, setIndicatorColor);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, getIndicatorDiameter);
			TITANIUM_ADD_FUNCTION(ActivityIndicator, setIndicatorDiameter);
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicator, color)
		{
			return get_context().CreateString(get_color());
		}

		TITANIUM_PROPERTY_SETTER(ActivityIndicator, color)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicator, font)
		{
			JSObject font = Titanium::UI::Font_to_js(get_context(), get_font());
			return static_cast<JSValue>(font);
		}

		TITANIUM_PROPERTY_SETTER(ActivityIndicator, font)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_font(Titanium::UI::js_to_Font(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicator, message)
		{
			return get_context().CreateString(get_message());
		}

		TITANIUM_PROPERTY_SETTER(ActivityIndicator, message)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_message(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicator, messageid)
		{
			return get_context().CreateString(get_messageid());
		}

		TITANIUM_PROPERTY_SETTER(ActivityIndicator, messageid)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_messageid(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicator, style)
		{
			return get_context().CreateNumber(static_cast<std::uint32_t>(get_style()));
		}

		TITANIUM_PROPERTY_SETTER(ActivityIndicator, style)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_style(static_cast<ACTIVITY_INDICATOR_STYLE>(static_cast<std::uint32_t>(argument)));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicator, indicatorColor)
		{
			return get_context().CreateString(get_indicatorColor());
		}

		TITANIUM_PROPERTY_SETTER(ActivityIndicator, indicatorColor)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_indicatorColor(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ActivityIndicator, indicatorDiameter)
		{
			return get_context().CreateString(get_indicatorDiameter());
		}

		TITANIUM_PROPERTY_SETTER(ActivityIndicator, indicatorDiameter)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_indicatorDiameter(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(ActivityIndicator, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(ActivityIndicator, setColor, color)

		TITANIUM_FUNCTION_AS_GETTER(ActivityIndicator, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(ActivityIndicator, setFont, font)

		TITANIUM_FUNCTION_AS_GETTER(ActivityIndicator, getMessage, message)
		TITANIUM_FUNCTION_AS_SETTER(ActivityIndicator, setMessage, message)

		TITANIUM_FUNCTION_AS_GETTER(ActivityIndicator, getMessageid, messageid)
		TITANIUM_FUNCTION_AS_SETTER(ActivityIndicator, setMessageid, messageid)

		TITANIUM_FUNCTION_AS_GETTER(ActivityIndicator, getStyle, style)
		TITANIUM_FUNCTION_AS_SETTER(ActivityIndicator, setStyle, style)

		TITANIUM_FUNCTION_AS_GETTER(ActivityIndicator, getIndicatorColor, indicatorColor)
		TITANIUM_FUNCTION_AS_SETTER(ActivityIndicator, setIndicatorColor, indicatorColor)

		TITANIUM_FUNCTION_AS_GETTER(ActivityIndicator, getIndicatorDiameter, indicatorDiameter)
		TITANIUM_FUNCTION_AS_SETTER(ActivityIndicator, setIndicatorDiameter, indicatorDiameter)

	} // namespace UI
} // namespace Titanium
