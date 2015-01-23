/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Slider.hpp"

namespace Titanium
{
	namespace UI
	{
		Slider::Slider(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context),
		      max__(js_context.CreateNumber(1)),
		      min__(js_context.CreateNumber(0)),
		      value__(js_context.CreateNumber(0))
		{
		}

		Slider::Slider(const Slider& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : View(rhs, arguments),
		      max__(rhs.max__),
		      min__(rhs.min__),
		      value__(rhs.value__)
		{
		}

		double Slider::get_max() const TITANIUM_NOEXCEPT
		{
			return max__;
		}

		void Slider::set_max(const double& max) TITANIUM_NOEXCEPT
		{
			max__ = max;
		}

		double Slider::get_min() const TITANIUM_NOEXCEPT
		{
			return min__;
		}

		void Slider::set_min(const double& min) TITANIUM_NOEXCEPT
		{
			min__ = min;
		}

		double Slider::get_value() const TITANIUM_NOEXCEPT
		{
			return value__;
		}

		void Slider::set_value(const double& value) TITANIUM_NOEXCEPT
		{
			value__ = value;
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void Slider::JSExportInitialize()
		{
			JSExport<Slider>::SetClassVersion(1);
			JSExport<Slider>::SetParent(JSExport<View>::Class());
			JSExport<Slider>::AddValueProperty("max", std::mem_fn(&Slider::js_get_max), std::mem_fn(&Slider::js_set_max));
			JSExport<Slider>::AddValueProperty("min", std::mem_fn(&Slider::js_get_min), std::mem_fn(&Slider::js_set_min));
			JSExport<Slider>::AddValueProperty("value", std::mem_fn(&Slider::js_get_value), std::mem_fn(&Slider::js_set_value));
		}

		JSValue Slider::js_get_max() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(max__);
		}

		bool Slider::js_set_max(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_max(static_cast<double>(argument));
			return true;
		}

		JSValue Slider::js_get_min() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(min__);
		}

		bool Slider::js_set_min(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_min(static_cast<double>(argument));
			return true;
		}

		JSValue Slider::js_get_value() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(value__);
		}

		bool Slider::js_set_value(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_value(static_cast<double>(argument));
			return true;
		}
	} // namespace UI
}  // namespace Titanium
