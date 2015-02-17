/**
 * Titanium.UI.ListSection for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/ListSection.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		ListSection::ListSection(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::ListSection(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("ListSection::ctor Initialize");
		}

		void ListSection::JSExportInitialize() {
			JSExport<ListSection>::SetClassVersion(1);
			JSExport<ListSection>::SetParent(JSExport<Titanium::UI::ListSection>::Class());
		}

	}  // namespace UI
}  // namespace TitaniumWindows