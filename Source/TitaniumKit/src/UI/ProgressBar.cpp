/**
 * TitaniumKit Titanium.UI.ProgressBar
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ProgressBar.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{


		ProgressBar::ProgressBar(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.ProgressBar"),
			color__(""),
			max__(1.0),
			message__(""),
			min__(0.0),
			tintColor__(""),
			trackTintColor__(""),
			value__(0.0)
		{
		}

		TITANIUM_PROPERTY_READWRITE(ProgressBar, std::string, color)
		TITANIUM_PROPERTY_READWRITE(ProgressBar, Font, font)
		TITANIUM_PROPERTY_READWRITE(ProgressBar, double, max)
		TITANIUM_PROPERTY_READWRITE(ProgressBar, std::string, message)
		TITANIUM_PROPERTY_READWRITE(ProgressBar, double, min)
		TITANIUM_PROPERTY_READWRITE(ProgressBar, std::string, tintColor)
		TITANIUM_PROPERTY_READWRITE(ProgressBar, std::string, trackTintColor)
		TITANIUM_PROPERTY_READWRITE(ProgressBar, double, value)

		void ProgressBar::JSExportInitialize()
		{
			JSExport<ProgressBar>::SetClassVersion(1);
			JSExport<ProgressBar>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(ProgressBar, color);
			TITANIUM_ADD_PROPERTY(ProgressBar, font);
			TITANIUM_ADD_PROPERTY(ProgressBar, max);
			TITANIUM_ADD_PROPERTY(ProgressBar, message);
			TITANIUM_ADD_PROPERTY(ProgressBar, min);
			TITANIUM_ADD_PROPERTY(ProgressBar, style);
			TITANIUM_ADD_PROPERTY(ProgressBar, tintColor);
			TITANIUM_ADD_PROPERTY(ProgressBar, trackTintColor);
			TITANIUM_ADD_PROPERTY(ProgressBar, value);

			TITANIUM_ADD_FUNCTION(ProgressBar, getColor);
			TITANIUM_ADD_FUNCTION(ProgressBar, setColor);
			TITANIUM_ADD_FUNCTION(ProgressBar, getFont);
			TITANIUM_ADD_FUNCTION(ProgressBar, setFont);
			TITANIUM_ADD_FUNCTION(ProgressBar, getMax);
			TITANIUM_ADD_FUNCTION(ProgressBar, setMax);
			TITANIUM_ADD_FUNCTION(ProgressBar, getMessage);
			TITANIUM_ADD_FUNCTION(ProgressBar, setMessage);
			TITANIUM_ADD_FUNCTION(ProgressBar, getMin);
			TITANIUM_ADD_FUNCTION(ProgressBar, setMin);
			TITANIUM_ADD_FUNCTION(ProgressBar, getStyle);
			TITANIUM_ADD_FUNCTION(ProgressBar, setStyle);
			TITANIUM_ADD_FUNCTION(ProgressBar, getTintColor);
			TITANIUM_ADD_FUNCTION(ProgressBar, setTintColor);
			TITANIUM_ADD_FUNCTION(ProgressBar, getTrackTintColor);
			TITANIUM_ADD_FUNCTION(ProgressBar, setTrackTintColor);
			TITANIUM_ADD_FUNCTION(ProgressBar, getValue);
			TITANIUM_ADD_FUNCTION(ProgressBar, setValue);
		}

		TITANIUM_PROPERTY_GETTER_STRING(ProgressBar, color)
		TITANIUM_PROPERTY_SETTER_STRING(ProgressBar, color)

		TITANIUM_PROPERTY_GETTER_STRUCT(ProgressBar, font, Font)
		TITANIUM_PROPERTY_SETTER_STRUCT(ProgressBar, font, Font)

		TITANIUM_PROPERTY_GETTER_DOUBLE(ProgressBar, max)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ProgressBar, max)

		TITANIUM_PROPERTY_GETTER_STRING(ProgressBar, message)
		TITANIUM_PROPERTY_SETTER_STRING(ProgressBar, message)

		TITANIUM_PROPERTY_GETTER_DOUBLE(ProgressBar, min)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ProgressBar, min)

		TITANIUM_PROPERTY_GETTER_DOUBLE(ProgressBar, value)
		TITANIUM_PROPERTY_SETTER_DOUBLE(ProgressBar, value)

		TITANIUM_PROPERTY_GETTER_STRING(ProgressBar, tintColor)
		TITANIUM_PROPERTY_SETTER_STRING(ProgressBar, tintColor)

		TITANIUM_PROPERTY_GETTER_STRING(ProgressBar, trackTintColor)
		TITANIUM_PROPERTY_SETTER_STRING(ProgressBar, trackTintColor)

		TITANIUM_PROPERTY_GETTER_UNIMPLEMENTED(ProgressBar, style)
		TITANIUM_PROPERTY_SETTER_UNIMPLEMENTED(ProgressBar, style)

		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setColor, color)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setFont, font)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getMax, max)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setMax, max)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getMessage, message)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setMessage, message)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getMin, min)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setMin, min)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getStyle, style)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setStyle, style)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getTintColor, tintColor)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setTintColor, tintColor)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getTrackTintColor, trackTintColor)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setTrackTintColor, trackTintColor)
		TITANIUM_FUNCTION_AS_GETTER(ProgressBar, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(ProgressBar, setValue, value)

	} // namespace UI
} // namespace Titanium
