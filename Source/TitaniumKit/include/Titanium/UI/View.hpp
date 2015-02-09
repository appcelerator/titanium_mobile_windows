/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_VIEW_HPP_
#define _TITANIUM_UI_VIEW_HPP_

#include "Titanium/UI/UIBase.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium UI View.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.View
		*/
		class TITANIUMKIT_EXPORT View : public UIBase, public JSExport<View>
		{
		public:
		

			View(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~View() TITANIUM_NOEXCEPT;  //= default;
			View(const View&) = default;
			View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&) = default;
			View& operator=(View&&) = default;
#endif

			// TODO: The following functions can automatically be generated
			// from the YAML API docs.
			static void JSExportInitialize();
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_VIEW_HPP_
