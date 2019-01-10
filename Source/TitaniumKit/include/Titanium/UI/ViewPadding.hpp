/**
 * TitaniumKit ViewPadding
 *
 * Copyright (c) 2018 by Axway. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_VIEWPADDING_HPP_
#define _TITANIUM_VIEWPADDING_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion Dictionary object of parameters for the padding applied to all kinds of views.
		  This is an abstract type. Any object meeting this description can be used where this type is used.
		  See https://docs.appcelerator.com/platform/latest/#!/api/ViewPadding
		  */
		struct ViewPadding {
			double bottom  { 0.0 };
			double left    { 0.0 };
			double right   { 0.0 };
			double top     { 0.0 };
		};

		TITANIUMKIT_EXPORT ViewPadding js_to_ViewPadding(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject ViewPadding_to_js(const JSContext& js_context, const ViewPadding& padding);
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_VIEWPADDING_HPP_
