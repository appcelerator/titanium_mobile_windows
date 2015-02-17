/**
 * Titanium.UI.ListItem for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/ListItem.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		ListItem::ListItem(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::ListItem(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("ListItem::ctor Initialize");
		}

		void ListItem::JSExportInitialize() {
			JSExport<ListItem>::SetClassVersion(1);
			JSExport<ListItem>::SetParent(JSExport<Titanium::UI::ListItem>::Class());
		}

	}  // namespace UI
}  // namespace TitaniumWindows