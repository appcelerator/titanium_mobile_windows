/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Slider.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{
		Slider::Slider(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context, "Ti.UI.Slider"),
		      max__(js_context.CreateNumber(1)),
		      min__(js_context.CreateNumber(0)),
		      value__(js_context.CreateNumber(0))
		{
		}

		TITANIUM_PROPERTY_READWRITE(Slider, double, max)

		TITANIUM_PROPERTY_READWRITE(Slider, double, min)

		TITANIUM_PROPERTY_READWRITE(Slider, double, value)

		void Slider::JSExportInitialize()
		{
			JSExport<Slider>::SetClassVersion(1);
			JSExport<Slider>::SetParent(JSExport<View>::Class());
			TITANIUM_ADD_PROPERTY(Slider, max);
			TITANIUM_ADD_PROPERTY(Slider, min);
			TITANIUM_ADD_PROPERTY(Slider, value);

			TITANIUM_ADD_FUNCTION(Slider, getMax);
			TITANIUM_ADD_FUNCTION(Slider, setMax);
			TITANIUM_ADD_FUNCTION(Slider, getMin);
			TITANIUM_ADD_FUNCTION(Slider, setMin);
			TITANIUM_ADD_FUNCTION(Slider, getValue);
			TITANIUM_ADD_FUNCTION(Slider, setValue);
		}

		TITANIUM_PROPERTY_GETTER(Slider, max)
		{
			return get_context().CreateNumber(get_max());
		}

		TITANIUM_PROPERTY_SETTER(Slider, max)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_max(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Slider, min)
		{
			return get_context().CreateNumber(get_min());
		}

		TITANIUM_PROPERTY_SETTER(Slider, min)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_min(static_cast<double>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(Slider, value)
		{
			return get_context().CreateNumber(get_value());
		}

		TITANIUM_PROPERTY_SETTER(Slider, value)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_value(static_cast<double>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(Slider, getMax, max)
		TITANIUM_FUNCTION_AS_SETTER(Slider, setMax, max)

		TITANIUM_FUNCTION_AS_GETTER(Slider, getMin, min)
		TITANIUM_FUNCTION_AS_SETTER(Slider, setMin, min)

		TITANIUM_FUNCTION_AS_GETTER(Slider, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(Slider, setValue, value)

	} // namespace UI
}  // namespace Titanium
