/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Media/MusicPlayer.hpp"
#include "Titanium/detail/TiLogger.hpp"

namespace TitaniumWindows
{
	namespace Media
	{
		MusicPlayer::MusicPlayer(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Media::MusicPlayer(js_context)
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::MusicPlayer::ctor Initialize");
		}

		MusicPlayer::~MusicPlayer()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Media::MusicPlayer::dtor");
		}

		void MusicPlayer::JSExportInitialize()
		{
			JSExport<MusicPlayer>::SetClassVersion(1);
			JSExport<MusicPlayer>::SetParent(JSExport<Titanium::Media::MusicPlayer>::Class());
		}

		void MusicPlayer::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::MusicPlayer::enableEvent(event_name);
		}

		void MusicPlayer::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Media::MusicPlayer::disableEvent(event_name);
		}
	}
}
