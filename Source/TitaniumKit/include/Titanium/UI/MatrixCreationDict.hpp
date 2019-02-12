/**
 * TitaniumKit MatrixCreationDict
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_MATRIXCREATIONDICT_HPP_
#define _TITANIUM_UI_MATRIXCREATIONDICT_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/UI/Point.hpp"

// TODO: Move into 2DMatrix.hpp, move impl into 2DMatrix.cpp
namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the MatrixCreationDict.
		  Extend this struct to implement platform-specific properties like animation style.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/MatrixCreationDict
		*/
		struct MatrixCreationDict
		{
			Point anchorPoint;
			int32_t rotate {0};
			double scale {1};
		};

		TITANIUMKIT_EXPORT MatrixCreationDict js_to_MatrixCreationDict(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject MatrixCreationDict_to_js(const JSContext& js_context, const MatrixCreationDict& dict);
		
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_MATRIXCREATIONDICT_HPP_
