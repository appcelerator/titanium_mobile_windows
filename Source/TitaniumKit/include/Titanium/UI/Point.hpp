/**
 * TitaniumKit Point
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_POINT_HPP_
#define _TITANIUM_UI_POINT_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion An abstract datatype for specifying a point.
	  	  This is an abstract type. Any object meeting this description can be used where this type is used.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Point
		*/
		struct Point
		{
			double x {0};
			double y {0};
		};
		
		TITANIUMKIT_EXPORT Point js_to_Point(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject Point_to_js(const JSContext& js_context, const Point& point);
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_POINT_HPP_
