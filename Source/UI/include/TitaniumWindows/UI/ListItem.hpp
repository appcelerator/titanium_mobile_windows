/**
 * Titanium.UI.ListItem for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_LISTITEM_HPP_
#define _TITANIUMWINDOWS_UI_LISTITEM_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.ListItem implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ListItem final : public Titanium::UI::ListItem, public JSExport<ListItem>
		{

		public:
			ListItem(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ListItem()                  = default;
			ListItem(const ListItem&)            = default;
			ListItem& operator=(const ListItem&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListItem(ListItem&&)                 = default;
			ListItem& operator=(ListItem&&)      = default;
#endif

			static void JSExportInitialize();

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_UI_LISTITEM_HPP_