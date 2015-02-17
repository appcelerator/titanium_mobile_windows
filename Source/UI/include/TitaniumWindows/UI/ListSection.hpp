/**
 * Titanium.UI.ListSection for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_LISTSECTION_HPP_
#define _TITANIUMWINDOWS_UI_LISTSECTION_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.ListSection implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ListSection final : public Titanium::UI::ListSection, public JSExport<ListSection>
		{

		public:
			ListSection(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ListSection()                  = default;
			ListSection(const ListSection&)            = default;
			ListSection& operator=(const ListSection&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListSection(ListSection&&)                 = default;
			ListSection& operator=(ListSection&&)      = default;
#endif

			static void JSExportInitialize();

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_UI_LISTSECTION_HPP_
