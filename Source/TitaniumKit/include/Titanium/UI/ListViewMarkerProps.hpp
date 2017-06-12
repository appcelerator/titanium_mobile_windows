/**
 * TitaniumKit ListViewMarkerProps
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTVIEWMARKERPROPS_HPP_
#define _TITANIUM_UI_LISTVIEWMARKERPROPS_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the ListViewAnimationProperties
		  See http://docs.appcelerator.com/titanium/latest/#!/api/ListViewAnimationProperties
		*/
		struct ListViewMarkerProps
		{
			int32_t itemIndex {0};
			int32_t sectionIndex {0};
			//
			// This indicates marker event is fired for this marker
			//
			bool fired { false };
		};
		
		TITANIUMKIT_EXPORT ListViewMarkerProps js_to_ListViewMarkerProps(const JSObject& object);
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_LISTVIEWMARKERPROPS_HPP_
