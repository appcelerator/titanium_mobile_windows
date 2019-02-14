/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Media/Item.hpp"

namespace TitaniumWindows
{
	namespace Media
	{
		Item::Item(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Media::Item(js_context)
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::Item::ctor Initialize");
		}

		Item::~Item()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::Item::dtor");
		}

		void Item::JSExportInitialize()
		{
			JSExport<Item>::SetClassVersion(1);
			JSExport<Item>::SetParent(JSExport<Titanium::Media::Item>::Class());
		}

		void Item::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::Item::enableEvent(event_name);
		}

		void Item::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::Item::disableEvent(event_name);
		}
	}
}
