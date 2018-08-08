/**
 * TitaniumKit Gradient
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_GRADIENT_HPP_
#define _TITANIUM_UI_GRADIENT_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/UI/Point.hpp"
#include "Titanium/UI/Constants.hpp"
#include <vector>

namespace Titanium
{
	namespace UI
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
			std::string color{""};
			double      offset{ -1 };
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
			Point endPoint {"0.0", "1.0"};
			Point startPoint{ "0.0", "0.0" };
			GRADIENT_TYPE type;
			std::vector<GradientColorRef> colors;
		};

		TITANIUMKIT_EXPORT GradientColorRef js_to_GradientColorRef(const std::string& color);
		TITANIUMKIT_EXPORT GradientColorRef js_to_GradientColorRef(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject GradientColorRef_to_js(const JSContext& js_context, const GradientColorRef& gradientColorRef);
		TITANIUMKIT_EXPORT Gradient js_to_Gradient(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject Gradient_to_js(const JSContext& js_context, const Gradient& gradient);
		
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_GRADIENT_HPP_
