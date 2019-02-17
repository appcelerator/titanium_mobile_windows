/**
* Windows.ListViewScrollPosition
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/ListViewScrollPosition.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml 
		{
			ListViewScrollPosition::ListViewScrollPosition(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.UI.Windows.ListViewScrollPosition")
				, none__(js_context.CreateNumber(None))
				, top__(js_context.CreateNumber(Top))
				, middle__(js_context.CreateNumber(Middle))
				, bottom__(js_context.CreateNumber(Bottom))
			{
				TITANIUM_LOG_DEBUG("ListViewScrollPosition::ctor Initialize");
			}

			void ListViewScrollPosition::JSExportInitialize()
			{
				JSExport<ListViewScrollPosition>::SetClassVersion(1);
				JSExport<ListViewScrollPosition>::SetParent(JSExport<Titanium::Module>::Class());
				TITANIUM_ADD_PROPERTY_READONLY(ListViewScrollPosition, NONE);
				TITANIUM_ADD_PROPERTY_READONLY(ListViewScrollPosition, TOP);
				TITANIUM_ADD_PROPERTY_READONLY(ListViewScrollPosition, BOTTOM);
				TITANIUM_ADD_PROPERTY_READONLY(ListViewScrollPosition, MIDDLE);
			}

			TITANIUM_PROPERTY_GETTER(ListViewScrollPosition, NONE)
			{
				return none__;
			}
			TITANIUM_PROPERTY_GETTER(ListViewScrollPosition, TOP)
			{
				return top__;
			}
			TITANIUM_PROPERTY_GETTER(ListViewScrollPosition, BOTTOM)
			{
				return bottom__;
			}
			TITANIUM_PROPERTY_GETTER(ListViewScrollPosition, MIDDLE)
			{
				return middle__;
			}

		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
