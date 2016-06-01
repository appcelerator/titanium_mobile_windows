/**
 * TitaniumKit Titanium.UI.Switch
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Switch.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		Switch::Switch(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.Switch"),
			enabled__(true),
			titleOff__("Off"),
			titleOn__("On"),
			value__(false)
		{
		}

		TITANIUM_PROPERTY_READWRITE(Switch, std::string, color)

		TITANIUM_PROPERTY_READWRITE(Switch, bool, enabled)

		TITANIUM_PROPERTY_READWRITE(Switch, std::string, titleOff)

		TITANIUM_PROPERTY_READWRITE(Switch, std::string, titleOn)

		TITANIUM_PROPERTY_READWRITE(Switch, bool, value)

		void Switch::JSExportInitialize() {
			JSExport<Switch>::SetClassVersion(1);
			JSExport<Switch>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(Switch, color);
			TITANIUM_ADD_FUNCTION(Switch, getColor);
			TITANIUM_ADD_FUNCTION(Switch, setColor);

			TITANIUM_ADD_PROPERTY(Switch, enabled);
			TITANIUM_ADD_FUNCTION(Switch, getEnabled);
			TITANIUM_ADD_FUNCTION(Switch, setEnabled);

			TITANIUM_ADD_PROPERTY(Switch, titleOff);
			TITANIUM_ADD_FUNCTION(Switch, getTitleOff);
			TITANIUM_ADD_FUNCTION(Switch, setTitleOff);

			TITANIUM_ADD_PROPERTY(Switch, titleOn);
			TITANIUM_ADD_FUNCTION(Switch, getTitleOn);
			TITANIUM_ADD_FUNCTION(Switch, setTitleOn);

			TITANIUM_ADD_PROPERTY(Switch, value);
			TITANIUM_ADD_FUNCTION(Switch, getValue);
			TITANIUM_ADD_FUNCTION(Switch, setValue);
		}

		TITANIUM_PROPERTY_GETTER_STRING(Switch, color)
		TITANIUM_PROPERTY_SETTER_STRING(Switch, color)

		TITANIUM_FUNCTION_AS_GETTER(Switch, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(Switch, setColor, color)

		TITANIUM_PROPERTY_GETTER_BOOL(Switch, enabled)
		TITANIUM_PROPERTY_SETTER_BOOL(Switch, enabled)

		TITANIUM_FUNCTION_AS_GETTER(Switch, getEnabled, enabled)
		TITANIUM_FUNCTION_AS_SETTER(Switch, setEnabled, enabled)

		TITANIUM_PROPERTY_GETTER_STRING(Switch, titleOff)
		TITANIUM_PROPERTY_SETTER_STRING(Switch, titleOff)

		TITANIUM_FUNCTION_AS_GETTER(Switch, getTitleOff, titleOff)
		TITANIUM_FUNCTION_AS_SETTER(Switch, setTitleOff, titleOff)

		TITANIUM_PROPERTY_GETTER_STRING(Switch, titleOn)
		TITANIUM_PROPERTY_SETTER_STRING(Switch, titleOn)

		TITANIUM_FUNCTION_AS_GETTER(Switch, getTitleOn, titleOn)
		TITANIUM_FUNCTION_AS_SETTER(Switch, setTitleOn, titleOn)

		TITANIUM_PROPERTY_GETTER_BOOL(Switch, value)
		TITANIUM_PROPERTY_SETTER_BOOL(Switch, value)

		TITANIUM_FUNCTION_AS_GETTER(Switch, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(Switch, setValue, value)

	} // namespace UI
} // namespace Titanium
