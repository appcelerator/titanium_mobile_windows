/**
 * TitaniumKit Dimension
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DIMENSION_HPP_
#define _TITANIUM_DIMENSION_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @struct
	  @discussion An abstract datatype for specifying a dimension.
	  This is an abstract type. Any object meeting this description can be used where this type is used.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Dimension
	*/
	struct Dimension
	{
		double x {0};
		double y {0};
		double width  {0};
		double height {0};
	};
	
	Dimension js_to_Dimension(const JSObject& object);
} // namespace Titanium
#endif // _TITANIUM_DIMENSION_HPP_
