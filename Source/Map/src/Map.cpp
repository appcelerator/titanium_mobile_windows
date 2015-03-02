/**
 * Titanium.Map for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Map.hpp"
#include "Titanium/detail/TiBase.hpp"

namespace TitaniumWindows
{
	MapModule::MapModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::MapModule(js_context)
	{
		TITANIUM_LOG_DEBUG("Map::ctor Initialize");
	}

	void MapModule::JSExportInitialize() {
		JSExport<MapModule>::SetClassVersion(1);
		JSExport<MapModule>::SetParent(JSExport<Titanium::MapModule>::Class());
	}

}  // namespace TitaniumWindows