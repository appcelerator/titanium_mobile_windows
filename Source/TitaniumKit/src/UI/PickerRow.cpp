/**
 * TitaniumKit Titanium.UI.PickerRow
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/PickerRow.hpp"

namespace Titanium
{
	namespace UI
	{

		PickerRow::PickerRow(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.PickerRow")
			, color__("")
			, title__("")
		{
		}

		TITANIUM_PROPERTY_READWRITE(PickerRow, std::string, color)
		TITANIUM_PROPERTY_READWRITE(PickerRow, Font, font)
		TITANIUM_PROPERTY_READWRITE(PickerRow, std::string, title)

		void PickerRow::JSExportInitialize()
		{
			JSExport<PickerRow>::SetClassVersion(1);
			JSExport<PickerRow>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(PickerRow, color);
			TITANIUM_ADD_PROPERTY(PickerRow, font);
			TITANIUM_ADD_PROPERTY(PickerRow, title);

			TITANIUM_ADD_FUNCTION(PickerRow, add);
			TITANIUM_ADD_FUNCTION(PickerRow, getColor);
			TITANIUM_ADD_FUNCTION(PickerRow, setColor);
			TITANIUM_ADD_FUNCTION(PickerRow, getFont);
			TITANIUM_ADD_FUNCTION(PickerRow, setFont);
			TITANIUM_ADD_FUNCTION(PickerRow, getTitle);
			TITANIUM_ADD_FUNCTION(PickerRow, setTitle);
		}

		TITANIUM_PROPERTY_GETTER_STRING(PickerRow, color)
		TITANIUM_PROPERTY_SETTER_STRING(PickerRow, color)
		TITANIUM_PROPERTY_GETTER_STRUCT(PickerRow, font, Font)
		TITANIUM_PROPERTY_SETTER_STRUCT(PickerRow, font, Font)
		TITANIUM_PROPERTY_GETTER_STRING(PickerRow, title)
		TITANIUM_PROPERTY_SETTER_STRING(PickerRow, title)

		TITANIUM_FUNCTION_AS_GETTER(PickerRow, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(PickerRow, setColor, color)
		TITANIUM_FUNCTION_AS_GETTER(PickerRow, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(PickerRow, setFont, font)
		TITANIUM_FUNCTION_AS_GETTER(PickerRow, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(PickerRow, setTitle, title)

	} // namespace UI
} // namespace Titanium
