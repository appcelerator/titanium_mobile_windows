/**
 * TitaniumKit Titanium.Map.Route
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Map/Route.hpp"

namespace Titanium
{
	namespace Map
	{

		Route::Route(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Map.Route")
		{
		}

		void Route::JSExportInitialize() {
			JSExport<Route>::SetClassVersion(1);
			JSExport<Route>::SetParent(JSExport<Module>::Class());
		}

	} // namespace Map
} // namespace Titanium
