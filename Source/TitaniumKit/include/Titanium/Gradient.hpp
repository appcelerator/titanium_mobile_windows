/**
 * TitaniumKit Gradient
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GRADIENT_HPP_
#define _TITANIUM_GRADIENT_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/Point.hpp"
#include <vector>

namespace Titanium
{
	using namespace HAL;

	/*!
	 @struct
	 @discussion A simple object consisting of a color and an offset.
	 This is an abstract type. Any object meeting this description can be used where this type is used.
	 See http://docs.appcelerator.com/titanium/latest/#!/api/GradientColorRef
	 */
	struct GradientColorRef
	{
		std::string color;
		double      offset;
	};

	/*!
	  @struct
	  @discussion A simple object defining a color gradient. 
	  This is an abstract type. Any object meeting this description can be used where this type is used.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Gradient
	*/
	struct Gradient
	{
		bool backfillEnd   {false};
		bool backfillStart {false};
		double endRadius   {0};
		double startRadius {0};
		Point endPoint;
		Point startPoint;
		std::string type;
		std::vector<GradientColorRef> color;
	};

	GradientColorRef js_to_GradientColorRef(const std::string& color);
	GradientColorRef js_to_GradientColorRef(const JSObject& object);
	Gradient js_to_Gradient(const JSObject& object);
	JSObject Gradient_to_js(const JSContext& js_context, Gradient gradient);
	
} // namespace Titanium
#endif // _TITANIUM_GRADIENT_HPP_
