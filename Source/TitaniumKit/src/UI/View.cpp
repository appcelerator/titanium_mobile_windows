/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		View::View(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: UIBase(js_context)
		{
			TITANIUM_LOG_DEBUG("View:: ctor ", this);
		}

		View::~View() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View:: dtor ", this);
		}

		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<UIBase>::Class());			
		}

		
	} // namespace UI
}  // namespace Titanium
