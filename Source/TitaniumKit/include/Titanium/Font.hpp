/**
 * TitaniumKit Font
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_FONT_HPP_
#define _TITANIUM_FONT_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @struct
	  @discussion An abstract datatype for specifying a text font.
	  This is an abstract type. Any object meeting this description can be used where this type is used.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Font
	*/
	struct Font
	{
		std::string fontFamily;
		std::string fontSize;
		std::string fontStyle;
		std::string fontWeight;
		std::string textStyle;
	};
	
	Font js_to_Font(const JSObject& object);
	JSObject Font_to_js(const JSContext& js_context, Font font);
	
} // namespace Titanium
#endif // _TITANIUM_FONT_HPP_
