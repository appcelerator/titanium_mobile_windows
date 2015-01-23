/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_SLIDER_HPP_
#define _TITANIUM_UI_SLIDER_HPP_

#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium UI Slider.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Slider
		*/
		class TITANIUMKIT_EXPORT Slider : public View, public JSExport<Slider>
		{
		public:
			/*!
			  @method

			  @abstract max : Number

			  @discussion Maximum value of the slider.

			  Specifies the value of the slider when the thumb is all the way to the right. This value is inclusive.
			*/
			virtual double get_max() const TITANIUM_NOEXCEPT final;
			virtual void set_max(const double& max) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract min : Number

			  @discussion Minimum value of the slider.

			  Specifies the value of the slider when the thumb is all the way to the left. This value is inclusive.
			*/
			virtual double get_min() const TITANIUM_NOEXCEPT final;
			virtual void set_min(const double& min) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract value : String

			  @discussion Current value of the slider.
			*/
			virtual double get_value() const TITANIUM_NOEXCEPT final;
			virtual void set_value(const double& value) TITANIUM_NOEXCEPT;

			Slider(const JSContext& js_context) TITANIUM_NOEXCEPT;
			Slider(const Slider&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

			virtual ~Slider() = default;
			Slider(const Slider&) = default;
			Slider& operator=(const Slider&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Slider(Slider&&) = default;
			Slider& operator=(Slider&&) = default;
#endif

			// TODO: The following functions can automatically be generated
			// from the YAML API docs.
			static void JSExportInitialize();

			virtual JSValue js_get_max() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_max(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_min() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_min(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_value() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_value(const JSValue& argument) TITANIUM_NOEXCEPT final;

		private:
			double max__;
			double min__;
			double value__;
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_SLIDER_HPP_
