/**
 * Titanium.Map for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_MAP_HPP_
#define _TITANIUMWINDOWS_MAP_HPP_

#include "TitaniumWindows/detail/MapBase.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
		@class

		@discussion This is the Titanium.Map implementation for Windows.
	*/
	class TITANIUMWINDOWS_MAP_EXPORT MapModule final : public Titanium::MapModule, public JSExport<MapModule>
	{

	public:
		MapModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
		virtual ~MapModule()                  = default;
		MapModule(const MapModule&)            = default;
		MapModule& operator=(const MapModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		MapModule(MapModule&&)                 = default;
		MapModule& operator=(MapModule&&)      = default;
#endif

		static void JSExportInitialize();

	private:

	};
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_MAP_HPP_