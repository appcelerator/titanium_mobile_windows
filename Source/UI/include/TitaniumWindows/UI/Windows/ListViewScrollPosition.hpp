/**
* Windows.ListViewScrollPosition
*
* Copyright (c) 2017 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_WINDOWS_LISTVIEWSCROLLPOSITION_HPP_
#define _TITANIUMWINDOWS_WINDOWS_LISTVIEWSCROLLPOSITION_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/Module.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		// Use WindowsXaml namespace instead of "Windows" because it screws entire namespace in UI...
		namespace WindowsXaml
		{
			using namespace HAL;

			/*!
			  @class

			  @discussion This is the Titanium.UI.Windows.ListViewScrollPosition implementation
			*/
			class TITANIUMWINDOWS_UI_EXPORT ListViewScrollPosition final : public Titanium::Module, public JSExport<ListViewScrollPosition>
			{

			public:
				ListViewScrollPosition(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~ListViewScrollPosition()                = default;
				ListViewScrollPosition(const ListViewScrollPosition&)            = default;
				ListViewScrollPosition& operator=(const ListViewScrollPosition&) = default;
	#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				ListViewScrollPosition(ListViewScrollPosition&&)                 = default;
				ListViewScrollPosition& operator=(ListViewScrollPosition&&)      = default;
	#endif

				TITANIUM_PROPERTY_READONLY_DEF(NONE);
				TITANIUM_PROPERTY_READONLY_DEF(TOP);
				TITANIUM_PROPERTY_READONLY_DEF(BOTTOM);
				TITANIUM_PROPERTY_READONLY_DEF(MIDDLE);

				static void JSExportInitialize();

				enum {
					None,
					Top,
					Middle,
					Bottom
				};

			private:

				JSValue none__;
				JSValue top__;
				JSValue bottom__;
				JSValue middle__;
			};
		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_WINDOWS_LISTVIEWSCROLLPOSITION_HPP_